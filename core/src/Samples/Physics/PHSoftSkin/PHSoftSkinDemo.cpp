/*
 *  Copyright (c) 2003-2012, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */

#include "PHSoftSkinDemo.h"
#include "Physics/PHOpSpHashColliAgent.h"
#include "Physics/PHOpEngine.h"
#include <Foundation/UTClapack.h>
#include "Graphics/GRMesh.h"
#include <iomanip>

#define USE_SPRFILE

//#define USE_AVG_RADIUS



#ifdef	__unix__
  #define fopen_s(fptr,name,mode)	*(fptr) = fopen(name,mode)
  #define loadFromFile(o,s,t,v)		loadFromFile(o,(char*)s,t,v)
  #define saveToFile(o,s,v)		saveToFile(o,(char*)s,v)
#endif

using namespace std;

int hapticObjId;

PHSoftSkinDemo::PHSoftSkinDemo(){
#ifdef  HAPTIC_DEMO
	fileName = "./files/sceneSampleHaptic.spr";
#endif
//	fileName = "./files/sceneSample.spr";

	gravity = false;
	drawVertex = false;
	drawPs = false;
	drawFaces = false;
	fileVersion = 2.1f;
}

void PHSoftSkinDemo::Init(int argc, char* argv[]){
	CreateSdk();			// SDKの作成
	UTRef<ImportIf> import = GetSdk()->GetFISdk()->CreateImport();
	GetSdk()->LoadScene(fileName, import);			// ファイルのロード
	//GetSdk()->SaveScene("save.spr", import);		// ファイルのセーブテスト
	GRInit(argc, argv);		// ウィンドウマネジャ初期化
	CreateWin();			// ウィンドウを作成
	CreateTimer();			// タイマを作成
	InitCameraView();		// カメラビューの初期化
	GetSdk()->SetDebugMode(false);						// デバックモードの無効化
	GetSdk()->GetScene()->EnableRenderAxis(true);		// 座標軸の表示
	GetSdk()->GetScene()->EnableRenderContact(true);	// 接触領域の表示
	HISdkIf* hisdk = GetSdk()->GetHISdk();
	manualModeSpeedScalar = 0.03f;
	
	
	//initial op objects
	FWOpObjIf *tmp = GetSdk()->GetScene()->FindObject("fwCylinder")->Cast();
//#ifdef _3DOF
	tmp->CreateOpObjWithRadius(0.2f);
//#endif


	
	PHOpEngineIf* opEngineif = GetSdk()->GetScene()->GetPHScene()->GetOpEngine()->Cast();
#ifdef HAPTIC_DEMO
	//initial for haptic
	

	////for clip
	//int objid;
	//
	//hapticObjId = opEngine->AddOpObj();
	//PHOpObjIf *opObjIf = opEngine->GetOpObjIf(hapticObjId);
	//Vec3f* vArr;
	//vArr = new Vec3f[((GRMesh*)tmp->GetGRMesh())->vertices.size()];
	////vector<int> a;
	//for (int vi = 0; vi<((GRMesh*)tmp->GetGRMesh())->vertices.size(); vi++) {
	//	Vec3f v;// = new Vec3f();
	//	v.x = ((GRMesh*)tmp->GetGRMesh())->vertices[vi].x;
	//	v.y = ((GRMesh*)tmp->GetGRMesh())->vertices[vi].y;
	//	v.z = ((GRMesh*)tmp->GetGRMesh())->vertices[vi].z;

	//	opObjIf->AddVertextoLocalBuffer(v);
	//}
	//opObjIf->InitialObjUsingLocalBuffer(0.5f);
#ifdef _6DOF
	use6DOF = true;
	opEngineif->Initial6DOFHapticRenderer(0);//6DOF haptic renderer
#endif
#ifdef _3DOF
	use6DOF = false;
	opEngineif->Initial3DOFHapticRenderer();
#endif
	FWOpHapticHandlerIf* opHapticHandler = GetSdk()->GetScene()->CreateOpHapticHandler();
	//InitInterface();
	opHapticHandler->SetHumanInterface(spg);
	
	PHOpHapticControllerIf* opHc = (PHOpHapticControllerIf*)opEngineif->GetOpHapticController();
	opHc->setC_ObstacleRadius(0.02f);
	PHOpHapticRendererIf* opHr = (PHOpHapticRendererIf*)opEngineif->GetOpHapticRenderer();
	
	//for clip
	//opEngine->InitialHapticRenderer(1, hisdk);
	//PHOpHapticRendererIf* opHr = (PHOpHapticRendererIf*)opEngine->GetOpHapticRenderer();

	////for rigid Clip
	//opHr->SetRigid(true);

	//opAnimator = (PHOpAnimationIf*)opEngine->GetOpAnimator();
	//opAnimator->AddAnimationP(1, 38, Vec3f(0, -300, 0), 100);
	//for (int pi = 48; pi < 56; pi++)
	//{
	//	opAnimator->AddAnimationP(1, pi, Vec3f(0, -300, 0), 100);
	//}
	PHOpObjIf *opObjIf = opEngineif->GetOpObjIf(0);
	opObjIf->SetBound(3);

	opHrDesc = DCAST(PHOpHapticRenderer, opHr);
#endif

#ifdef COLLISION_DEMO

	FWOpObjIf *tmp2 = GetSdk()->GetScene()->FindObject("fwSLBunny2")->Cast();
	tmp2->CreateOpObj();

	//initial collision detection
	PHOpSpHashColliAgentIf* spIf;
	spIf = GetSdk()->GetScene()->GetPHScene() -> GetOpColliAgent();

	CDBounds bounds;
	float boundcube = ((PHOpObjIf*)tmp->GetOpObj())->GetBoundLength();
	bounds.min.x = -boundcube;
	bounds.min.y = -boundcube;
	bounds.min.z = -boundcube;
	bounds.max.x = boundcube;
	bounds.max.y = boundcube;
	bounds.max.z = boundcube;

	
#endif
	
	PHOpEngine* opEngine = DCAST(PHOpEngine, opEngineif);


	PHOpObjDesc* obj1 = opEngine->opObjs[0];
	std::cout << "obji = 0" << "pNum" << obj1->assPsNum << "gNum" << obj1->assGrpNum << std::endl;
	obj1->objAverRadius *= 0.5f;
#ifdef COLLISION_DEMO
	PHOpObjDesc* obj2 = opEngine->opObjs[1];
	cout << "obji = 1" << "pNum" << obj2->assPsNum << "gNum" << obj2->assGrpNum << endl;
	obj2->objAverRadius *= 0.5f;
#endif

#ifdef COLLISION_DEMO
	//define general ellipsoid radius to make stable collision result(not the radius calculated from PCA)
	for (int pi = 0; pi < obj1->assPsNum; pi++)
	{
		PHOpParticle* dp1 = &opEngine->opObjs[0]->objPArr[pi];

		dp1->pMainRadius = 0.4f;
		dp1->pSecRadius = 0.4f;
		dp1->pThrRadius = 0.2f;
	}
	for (int pi = 0; pi < obj2->assPsNum; pi++)
	{
		PHOpParticle* dp1 = &opEngine->opObjs[1]->objPArr[pi];

		dp1->pMainRadius = 0.4f;
		dp1->pSecRadius = 0.4f;
		dp1->pThrRadius = 0.2f;
	}
	spIf->Initial(0.5f, bounds);

	spIf->EnableCollisionDetection(false);
#endif

	DrawHelpInfo = true;
	checkPtclInfo = true;
	useMouseSelect = false;
	useMouseSelect = false;
	useMouseSlcObj = false;
	useAnime = false;
	pgroupEditionModel = false;
	fixPs = false;
	mouseX = 0.0f;
	mouseY = 0.0f;
	recX = 0.0f;
	recY = 0.0f;
	mouseHit = false;
	mouseLbtn = false;
	mouseVertmotion = false;
	pgroupEditionModel = false;
	runByStep = false;
	addGrpLink = true;
	ediFirP = true;
	render = GetCurrentWin()->GetRender();
	radiusCoe = 1.0f;
	
	//STEPタイマ作成
	UTTimerIf* SimuTimer = CreateTimer(UTTimerIf::FRAMEWORK);
	int intervaltime = 10;
	SimuTimer->SetInterval(intervaltime);
	SimuTimer->SetResolution(1);
	opSimuTimerId = SimuTimer->GetID();

	//カメラ位置調整
	Vec3d pos = Vec3d(0.0, 5.0, 10.0);		// カメラ初期位置
	GetCurrentWin()->GetTrackball()->SetPosition(pos);	// カメラ初期位置の設定
	float rmin, rmax;
	GetCurrentWin()->GetTrackball()->GetLongitudeRange(rmin, rmax);
	rmin *= 2; rmax *= 2;
	GetCurrentWin()->GetTrackball()->SetLongitudeRange(rmin, rmax);

}
bool PHSoftSkinDemo::OnMouse(int button, int state, int x, int y)
{
	MouseButton(button, state, x, y);
	return true;
}
void PHSoftSkinDemo::InitCameraView(){
	Vec3d pos = Vec3d(-0.978414, 11.5185, 24.4473);		// カメラ初期位置
	GetCurrentWin()->GetTrackball()->SetPosition(pos);	// カメラ初期位置の設定
}

void PHSoftSkinDemo::Reset(){
	GetSdk()->Clear();
	GetSdk()->LoadScene(fileName);
	GetCurrentWin()->SetScene(GetSdk()->GetScene());
}

void PHSoftSkinDemo::TimerFunc(int id)
{
	
	PHOpEngineIf* opEngine = GetSdk()->GetScene()->GetPHScene()->GetOpEngine()->Cast();
	PHOpObjIf *opObjIf = opEngine->GetOpObjIf(0);
	
	FWApp::TimerFunc(id);
	if (id == opSimuTimerId)
	{
#ifdef HAPTIC_DEMO

		//HapticUpdate 
		GetSdk()->GetScene()->UpdateOpHapticHandler();


#endif
		//OpのシミュレーションStepをコール
		PHOpEngineIf* opEngine = GetSdk()->GetScene()->GetPHScene()->GetOpEngine()->Cast();
		//opEngine->Step();
		if (!runByStep)
		opEngine->StepWithBlend();
		PostRedisplay();

	}
	

	/*if (useAnime)
		opAnimator->AnimationStep(opEngine->GetDescAddress());*/
}
void PHSoftSkinDemo::InitInterface(){
	HISdkIf* hiSdk = GetSdk()->GetHISdk();

	if (humanInterface == SPIDAR){
		// x86
		DRUsb20SimpleDesc usbSimpleDesc;
		hiSdk->AddRealDevice(DRUsb20SimpleIf::GetIfInfoStatic(), &usbSimpleDesc);
		DRUsb20Sh4Desc usb20Sh4Desc;
		for (int i = 0; i< 10; ++i){
			usb20Sh4Desc.channel = i;
			hiSdk->AddRealDevice(DRUsb20Sh4If::GetIfInfoStatic(), &usb20Sh4Desc);
		}
		// x64
		DRCyUsb20Sh4Desc cyDesc;
		for(int i=0; i<10; ++i){
			cyDesc.channel = i;
			hiSdk->AddRealDevice(DRCyUsb20Sh4If::GetIfInfoStatic(), &cyDesc);
		}
		hiSdk->AddRealDevice(DRKeyMouseWin32If::GetIfInfoStatic());
		hiSdk->Print(DSTR);
		hiSdk->Print(std::cout);

		spg = hiSdk->CreateHumanInterface(HISpidarGIf::GetIfInfoStatic())->Cast();
#ifdef	_MSC_VER
		spg->Init(&HISpidarGDesc("SpidarG6X3R"));
#else
		HISpidarGDesc tmpdesc = HISpidarGDesc((char *) "SpidarG6X3R");
		spg->Init(&tmpdesc);
#endif
		spg->Calibration();
	}
	else if (humanInterface == XBOX){
		spg = hiSdk->CreateHumanInterface(HIXbox360ControllerIf::GetIfInfoStatic())->Cast();
	}
	else if (humanInterface == FALCON){
		spg = hiSdk->CreateHumanInterface(HINovintFalconIf::GetIfInfoStatic())->Cast();
		spg->Init(NULL);
	}
}

