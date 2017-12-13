/*
 *  Copyright (c) 2003-2006, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */

/* ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----
<<EmbPython�pswig�����O�̃N���X�ɂ��g�p����T���v��>>

Springhead��If�N���X�����łȂ��C�A�v���P�[�V�����ɂ����Ď��O�ŗp�ӂ����N���X���C
swig��p����Python����A�N�Z�X�\�ɂ��邱�Ƃ��ł��܂��D

0. ���W���[���������߂�
- ���̃T���v���ł� MyEPApp �ł��D
-- �܂܂��N���X���Ƃ͕K��������v���Ȃ��č\���܂���D

1. �p�ӂ���t�@�C��
- �N���X�w�b�_�i���W���[����.h)
- .i�t�@�C���i���W���[����.i�j %module �� %ignore ��K�؂ɗp�ӂ��C �Ō�� %include "���W���[����.h"
- %module:���W���[����
- %ignore:python����A�N�Z�X���Ȃ��ėǂ�MyEPApp�N���X�̃��\�b�h or �R���p�C�����ʂ�Ȃ����\�b�h�̏��O(UTRef�܂��ŋN����j

2. ����������t�@�C��
- RunSwig.bat �̐擪�iMODULE��BIN��K�؂ɃZ�b�g����j

3. �r���h�̕��@
- RunSwig.bat�𑖂点��
- �O���[�R�[�h�CSprEP���W���[����.h, EP���W���[����.h�CEP���W���[����.cpp�����������
- �r���h����

4. ���s�O��
-SprEP���W���[����.h��EP���W���[����.h���C���N���[�h����(�����炭main.cpp)
-main�֐�����interpreter->Initialize();�̂��ƂŊ֐�Init���W���[����();���Ă�
-���̊֐���SprEP���W���[����.h�Ő錾����Ă���
-*Springhead�֌W��interpreter->Initialize();�ŏ���������邪�C
	���O�̂��̂͏���������Ȃ��̂ł����ł���Ă���

----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- */

#include "MyEPApp.h"

#include "SprEPMyEPApp.h" 
#include "EPMyEPApp.h"

#pragma  hdrstop

using namespace Spr;
using namespace std;

// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// �}���`�X���b�h�p
#ifdef _WIN32
/// std::max�Ȃǂ��g���̂ɕK�v(windows.h�Ƌ������邩��)
#define NOMINMAX 
#include <windows.h>
#endif

// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// WndProc���������p
LRESULT CALLBACK NewWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
WNDPROC OldWndProc;

// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// �A�v���P�[�V�����N���X
void MyEPApp::Init(int argc, char* argv[]) {
	this->argc = argc;
	this->argv = argv;

	SampleApp::Init(argc, argv);
	ToggleAction(MENU_ALWAYS, ID_RUN);
	curScene = 0;

	hiSdk = HISdkIf::CreateSdk();

	// --- --- --- --- ---
	// SpaceNavigator

	HWND hWnd = FindWindow((LPCSTR) "GLUT", (LPCSTR) "Python with Springhead");
	HISpaceNavigatorDesc descSN;
	descSN.hWnd = &hWnd;

	spaceNavigator0 = hiSdk->CreateHumanInterface(HISpaceNavigatorIf::GetIfInfoStatic())->Cast();
	spaceNavigator0->Init(&descSN);
	spaceNavigator0->SetPose(Posef(Vec3f(0,0,5.0), Quaternionf()));

	spaceNavigator1 = hiSdk->CreateHumanInterface(HISpaceNavigatorIf::GetIfInfoStatic())->Cast();
	spaceNavigator1->Init(&descSN);
	spaceNavigator1->SetPose(Posef(Vec3f(0,0,-5.0), Quaternionf()));

	// �E�B���h�E�v���V�[�W����u������
	OldWndProc = (WNDPROC)(GetWindowLongPtr(hWnd, GWLP_WNDPROC));
	SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)(NewWndProc));

	GetFWScene()->GetPHScene()->GetConstraintEngine()->SetBSaveConstraints(true);

	GetCurrentWin()->GetTrackball()->SetPosition(Vec3f(6.5,6,20));
}

MyEPApp app;

// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// ���[�v�̒��g(������Ă΂��
void EPLoop(void* arg) {
	//�C���^���N�e�B�u���[�h�ŋN��
	PyRun_InteractiveLoop(stdin,"SpringheadPython Console");
}

// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// Python <=> Springhead �ϐ��ڑ��p
#define ACCESS_SPR_FROM_PY(cls, name, obj)							\
	{																\
		PyObject* pyObj = (PyObject*)newEP##cls((obj));				\
		Py_INCREF(pyObj);											\
		PyDict_SetItemString(dict, #name, pyObj);					\
	}																\

// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// ���[�v���s���O�ɂP�x�����Ă΂��
void EPLoopInit(void* arg) {
	MyEPApp* app = (MyEPApp*)arg;

	////Python�Ń��W���[���̎g�p�錾
	PyRun_SimpleString("import Spr");
		
	// c��pyobject��python�œǂ߂�悤�ɂ���
	PyObject *m = PyImport_AddModule("__main__");
	PyObject *dict = PyModule_GetDict(m);

	ACCESS_SPR_FROM_PY(MyEPApp,				app,				app										);
	ACCESS_SPR_FROM_PY(FWSceneIf,			fwScene,			app->GetFWScene()						);
	ACCESS_SPR_FROM_PY(HITrackballIf,		hiTrackball,		app->GetCurrentWin()->GetTrackball()	);
	ACCESS_SPR_FROM_PY(HISpaceNavigatorIf,	spaceNavigator0,	app->spaceNavigator0					);
	ACCESS_SPR_FROM_PY(HISpaceNavigatorIf,	spaceNavigator1,	app->spaceNavigator1					);

	if (app->argc == 2) {
		ostringstream loadfile;
		loadfile << "__mainfilename__ ='";
		loadfile << app->argv[1];
		loadfile << "'";
		PyRun_SimpleString("import codecs");
		PyRun_SimpleString(loadfile.str().c_str());
		PyRun_SimpleString("__mainfile__ = codecs.open(__mainfilename__,'r','utf-8')");
		PyRun_SimpleString("exec(compile( __mainfile__.read() , __mainfilename__, 'exec'),globals(),locals())");
		PyRun_SimpleString("__mainfile__.close()");
	}
}

// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// �u�������pWndProc
LRESULT CALLBACK NewWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	MSG m;
	m.hwnd		= hWnd;
	m.message	= msg;
	m.wParam	= wParam;
	m.lParam	= lParam;
	if (app.spaceNavigator0->PreviewMessage(&m)) {
		return 0L;
	}
	if (app.spaceNavigator1->PreviewMessage(&m)) {
		return 0L;
	}
	return CallWindowProc(OldWndProc, hWnd, msg, wParam, lParam);
}


// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---
/**
 brief		���C���֐�
 param		<in/--> argc�@�@�R�}���h���C�����͂̌�
 param		<in/--> argv�@�@�R�}���h���C������
 return		0 (����I��)
 */
#if _MSC_VER <= 1500
#include <GL/glut.h>
#endif
int __cdecl main(int argc, char *argv[]) {
	app.Init(argc, argv);

	EPInterpreter* interpreter = EPInterpreter::Create();

	interpreter->Initialize();
	initMyEPApp();

	interpreter->EPLoop = EPLoop;
	interpreter->EPLoopInit = EPLoopInit;
	interpreter->Run(&app);

	app.StartMainLoop();
	return 0;
}
