Springhead���_�E�����[�h���Ă���g����悤�ɂ���܂ł̗����������܂��D
## �_�E�����[�h
Springhead�̃E�F�u�T�C�g`http://springhead.info/wiki/`����zip�A�[�J�C�u���_�E�����[�h�ł��܂��D�������C�A�[�J�C�u�̍X�V�͕K�������p�ɂł͂���܂��� (�悭�Ȃ����Ƃł���) �̂ŁC�ŐV�̃R�[�h������ł��Ȃ��\��������܂��D��ɍŐV�̃R�[�h���g�p�������l�́C���ɐ�������GitHub���|�W�g������R�[�h����肵�Ă��������D
## GitHub������肷��
Springhead��GitHub��p���ăo�[�W�����Ǘ����s���Ă��܂��D���̕����̎��M���_��Springhead��GitHub���|�W�g����

`https://github.com/sprphys/Springhead`

�ł��D���|�W�g������̃R�[�h�̃_�E�����[�h/�N���[���͔C�ӂ̃��[�U���s���܂����C�R�[�h���R�~�b�g����ɂ͊J���҂Ƃ��ēo�^����Ă���K�v������܂��D
## �J����
Springhead�͏����n��ˑ��̎v�z�̂��ƂŊJ������Ă��܂��D���̂��߁C�����I�ɂ�Windows, macOS, unix�Ȃǂ̑����̏����n�œ��삷��͂��ł��D�������Ȃ���C�قƂ�ǂ̊J�������o�[��Windows���Visual Studio��p���ĊJ�����s���Ă��邽�߁C����ȊO�̊��Ŗ�薳�����삷��ۏ؂͎c�O�Ȃ��炠��܂��� (���������Ȃ��ł��傤)�D���������āC����ł̓��[�U�[�ɂ�Windows + Visual Studio�Ƃ������ł̎g�p�𐄏����܂��DWindows��Visual Studio�̃o�[�W�����ɂ��ẮCWindows 7/10, Visual Studio 2015/2017�ł͖��Ȃ����삵�܂��D
## ���C�u�����̃r���h
�ȉ��ł́CSpringhead��ۑ������f�B���N�g����`C:\Springhead`�Ɖ��肵�Ęb��i�߂܂��DSpringhead����肵����C�܂����C�u�������r���h���܂��D�������C�T���v���v���O�������r���h����ꍇ�Ɍ��肱���ł̍�Ƃ͕s�v�ł� (���C�u�����͎����I�ɍ쐬����܂�)�D�܂��CVisual Studio�ňȉ��̃\�����[�V�����t�@�C�����J���ĉ������D

`C:\Springhead\core\src\Springhead15.0.sln`


\framebox{\small{%
\begin{minipage}{0.9\hsize}
�y�⑫�z �t�@�C���������̐����� Visual Studio �̃o�[�W�����ԍ��������Ă��܂��D
���̑��̃\�����[�V�����t�@�C���C�v���W�F�N�g�t�@�C����
���l�̋K���Ńi���o�����O���Ă���܂��D
Visual Studio 2017 ���ȑO�� Visual Studio���g�p����ꍇ�ɂ͓K�X�ǂݑւ��Ă��������D
\end{minipage}
}}





\includegraphics[width=.6\hsize]{fig/libbuild.eps}

\caption{Building the library}


�\�����[�V�������J������Fig.\,\ref{fig_libbuild}�Ɏ����悤��`Springhead`�v���W�F�N�g���r���h���Ă��������D�r���h�ɐ���������`C:\Springhead\generated\lib\win32\`�܂���`C:\Springhead\generated\lib\win64\`�f�B���N�g���Ƀ��C�u�����t�@�C�����쐬�����͂��ł��DTable\,\ref{table_solution_config} �Ɏ����悤�ɁC�r���h�̐ݒ育�ƂɈقȂ邢�����̍\�����p�ӂ���Ă��܂��D���[�U�A�v���P�[�V�����̓s���ɍ��킹�Ďg�������Ă��������D\begin{table}[t]\caption{Build configurations}

\begin{tabular}{lll}
\toprule
�\����	      & �r���h�ݒ�		& �쐬����郉�C�u�����t�@�C���� \\ \midrule
`Release` & multithread, DLL	& `Springhead\# \#.lib`	 \\
`Debug`   & multithread, Debug, DLL	& `Springhead\# \#D.lib`	 \\
`Trace`   & multithread, Debug, DLL	& `Springhead\# \#T.lib`	 \\ \bottomrule
\multicolumn{3}{l}
{\footnotesize{%
\vbox{\vbox to 1mm{}
    \hbox{�E `\# \#`��Visual Studio�o�[�W������
	  �v���b�g�t�H�[����\��`Win32`����`x64`�̑g�ݍ��킹}
    \hbox{\phantom{�E }�ƂȂ�܂�("15.0x64" �Ȃ�)�D}
    \hbox{�E `Trace`�\���Ƃ́C�t���[���|�C���^���t��`Release`�\���̂��Ƃł��D}}}}
\end{tabular}

\end{table}
















## �T���v���v���O�����̃r���h
�T���v���v���O�����́C`C:\Springhead\core\src\Samples`�ȉ��ɂ���܂��D�c�O�Ȃ��Ƃł����C���ׂẴT���v���v���O���������Ȃ����삷���Ԃɂ͈ێ�����Ă��܂���D`Physics\BoxStack`��`Physics\Joints`����r�I�ǂ������e�i���X����Ă��܂��̂Ŏ����Ă݂Ă��������D�Ⴆ�΁C`Physics\BoxStack`���r���h����ɂ́C

`C:\Springhead\core\src\Samples\Physics\BoxStack\ `

�Ɉړ�����`BoxStack15.0.sln`���J���܂��D`BoxStack`���X�^�[�g�A�b�v�v���W�F�N�g�ɐݒ肵�C�r���h�C���s���Ă��������D���s����DLL��������Ȃ����߂ɃG���[���N���邩������܂���B���̏ꍇ�ɂ́C32�r�b�g���Ȃ��

`Springhead\core\bin\win32`, `Springhead\dependency\bin\win32`

64�r�b�g���Ȃ��

`Springhead\core\bin\win64`�C`Springhead\dependency\bin\win64`\\
`Springhead\core\bin\win32`�C`Springhead\dependency\bin\win32`

�̂��ׂĂ�Path��ʂ��Ă��������B
## �A�v���P�[�V�����̍쐬





\includegraphics[width=.6\hsize]{fig/newproject1.eps}

\caption{Create new project}







\includegraphics[width=.6\hsize]{fig/newproject2.eps}

\caption{Project configuration}







\includegraphics[width=.6\hsize]{fig/newproject3.eps}

\caption{Create source file}


Springhead���g���ĊȒP�ȃA�v���P�[�V�����v���O�������쐬���铹�؂�������܂��D�ȉ��ł�Visual Studio 2017��z�肵�܂��D
### �v���W�F�N�g�̍쐬
�uVisual C++ Windows >  �f�X�N�g�b�v �E�B�U�[�h�v���쐬���܂��D�쐬����f�B���N�g���� `C:\Experiments` �Ɖ��肵�܂��D���̃f�B���N�g���ɍ쐬����ꍇ�ɂ́C�v���W�F�N�g�Ɏw�肷��C���N���[�h�t�@�C���y�у��C�u�����t�@�C���̃p�X���C�ۑ�����Springhead�𐳂����Q�Ƃ���悤�ɒ��ӂ��Ă��������D�v���W�F�N�g���͍D���Ȗ��O��t���Ă��������D�A�v���P�[�V�����̐ݒ�Łu�R���\�[���A�v���P�[�V�����v��I�сC��̃v���W�F�N�g���`�F�b�N���܂��D
\framebox{\small{%
\begin{minipage}{0.9\hsize}
�y�⑫�z Visual Studio 2015���g�p�����ꍇ�A
Fig.\,\ref{fig_newproject1}�AFig.\,\ref{fig_newproject2}�Ƃ�
�قȂ�E�B���h�E���\������܂��B
���̏ꍇ�ɂ́uWin32�v���W�F�N�g >  ���ցv�Ɛi��ŁA
�u�R���\�[���A�v���P�[�V�����v�A�u��̃v���W�F�N�g�v���`�F�b�N���܂��B
\end{minipage}
}}
�v���W�F�N�g���쐬������u�v���W�F�N�g >  �V�������ڂ̒ǉ� >  C++�t�@�C��(.cpp)�v�Ƃ��ă\�[�X�t�@�C�����쐬���܂��D�����ł͉���`main.cpp`�Ƃ��܂��D
### �\�[�X�R�[�h�̕ҏW
\begin{table}[t]\caption{Simplest program code}{\small
```
#include <Springhead.h>
#include <Framework/SprFWApp.h>
using namespace Spr;

class MyApp : public FWApp{
public:
    virtual void Init(int argc = 0, char* argv[] = 0){
        FWApp::Init(argc, argv);

        PHSdkIf* phSdk = GetSdk()->GetPHSdk();
        PHSceneIf* phscene = GetSdk()->GetScene()->GetPHScene();
        CDBoxDesc bd;
        
        // �����쐬
        PHSolidIf* floor = phscene->CreateSolid();
        floor->SetDynamical(false);
        bd.boxsize = Vec3f(5.0f, 1.0f, 5.0f);
        floor->AddShape(phSdk->CreateShape(bd));
        floor->SetFramePosition(Vec3d(0, -1.0, 0));
    
        // �����쐬
        PHSolidIf* box = phscene->CreateSolid();
        bd.boxsize = Vec3f(0.2f, 0.2f, 0.2f);
        box->AddShape(phSdk->CreateShape(bd));
        box->SetFramePosition(Vec3d(0.0, 1.0, 0.0));

        GetSdk()->SetDebugMode(true);
    }
} app;

int main(int argc, char* argv[]){
    app.Init(argc, argv);
    app.StartMainLoop();
    return 0;
}
```
}\end{table}�쐬����`main.cpp`��Table\,\ref{table_simplest_code}�Ɏ����R�[�h����������ł��������D���ꂪSpringhead���g�p���� (�ق�) �ŏ��̃v���O�����R�[�h�ł��D
## �v���W�F�N�g�ݒ�





\includegraphics[width=.6\hsize]{fig/newproject4.eps}

\caption{Add include path}







\includegraphics[width=.6\hsize]{fig/newproject5.eps}

\caption{Add library path}







\begin{tabular}{c}
\includegraphics[width=.6\hsize]{fig/newproject6_truncate.eps} \\
\includegraphics[width=.6\hsize]{fig/newproject7_truncate.eps}
\end{tabular}

\caption{Specify library file}







\includegraphics[width=.6\hsize]{fig/newproject8.eps}

\caption{Program running}


�r���h����܂��ɂ������̃v���W�F�N�g�ݒ肪�K�v�ł��D64�r�b�g�v���b�g�t�H�[�����g�p����ꍇ�ɂ́C�v���p�e�B�[�y�[�W�́u�\���}�l�[�W���[�v�Łu`x64`�v�v���b�g�t�H�[����V�K�쐬���đI�����Ă����܂��D�܂��C\ref{libbuild} �Ő����������C�u�����̃r���h�͍ς�ł�����̂Ƃ��܂��D�܂��v���W�F�N�g�̃v���p�e�B�y�[�W���J���C�\�����u���ׂĂ̍\���v�Ƃ��Ă��������D���ɁuC/C++ >  �S�� >  �ǉ��̃C���N���[�h�f�B���N�g���v�ɁCFig.\,\ref{fig_newproject4}�̂悤��Springhead�̃C���N���[�h�t�@�C���ւ̃p�X���w�肵�Ă��������D����ɁC�u�����J�[ >  �S�� >  �ǉ��̃��C�u�����f�B���N�g���v��Fig.\,\ref{fig_newproject5}�̂悤��Springhead�̃��C�u�����t�@�C���ւ̃p�X���w�肵�܂�(64�r�b�g�\���̏ꍇ��`win32`�̑����`win64`���w�肵�܂�)�D���x�͍\�����uDebug�v�ɂ��܂��D�uC/C++ >  �R�[�h���� >  �����^�C�����C�u�����v���u�}���`�X���b�h �f�o�b�O DLL(`/MDd`)�v�ɂ��܂��D���Ɂu�����J�[ >  ���� >  �ǉ��̈ˑ��t�@�C���v��`Springhead15.0DWin32.lib` (�܂���`Springhead15.0Dx64.lib`)��ǉ����Ă��������D�Ō�ɍ\�����uRelease�v�ɐ؂�ւ��ē��l�̐ݒ�����܂��D�����^�C�����C�u�������u�}���`�X���b�h DLL(`/MD`)�v�Ƃ��āC�ǉ��̈ˑ��t�@�C����`Springhead15.0Win32.lib` (�܂���`Springhead15.0Dx64.lib`)��ǉ����܂��D
## �r���h�E���s
�ȏ�ŏ��������ł��D�r���h(F7)���āC���s(F5)���Ă݂Ă��������DFig.\,\ref{fig_newproject8}�̂悤�ȉ�ʂ��o�Ă���ΐ����ł��D
