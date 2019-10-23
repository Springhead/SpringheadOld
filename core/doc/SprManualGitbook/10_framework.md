
## �T�v





\includegraphics[width=.7\hsize]{fig/framework.eps}

\caption{Framework data structure}


Framework�̓��W���[���Ԃ̘A�g�𑣐i���ăA�v���P�[�V�����̍쐬���x�����邽�߂̃��W���[���ł��DFramework���W���[���̃f�[�^�\����Fig.\,\ref{fig_framework}�Ɏ����܂��D�ŏ�ʂɂ̓A�v���P�[�V�����N���X*FWApp*������܂��D���[�U��*FWApp*���p�����邱�ƂœƎ��̃A�v���P�[�V�������쐬���܂��D*FWApp*���̒��Ƀg�b�v���x���E�B���h�E(*FWWin*)�̔z��CFramework SDK (*FWSdk*)�C����уE�B���h�E�}�l�W��(*FWGraphicsAdaptee*)�������܂��D*FWWin*�̓g�b�v���x���E�B���h�E�ŁC���̃E�B���h�E�ɑΉ�������̓f�o�C�X��r���[�|�[�g����ێ����郌���_���C���̃E�B���h�E�Ɗ֘A�t����ꂽ�V�[���ւ̎Q�ƂȂǂ������܂��D�܂��C�}���ł͏ȗ�����Ă��܂����T�u�E�B���h�E��GUI�R���g���[���������Ƃ��ł��܂��D*FWSdk*�̖����͎��Ӄ��W���[���̋@�\�����ł��D���̒��Ɏ��Ӄ��W���[����SDK�N���X��Framework�V�[��(*FWScene*)�̔z��������܂��D�E�B���h�E�}�l�W���͏����n�Ɉˑ�����f�o�C�X�̏�������C�x���g�n���h�����O���s���܂��D�E�B���h�E�}�l�W���̓C���^�t�F�[�X�����J���Ă��܂���̂Ń��[�U�͂��̑��݂�z�Ɉӎ�����K�v�͂���܂���D�}�ł̓f�[�^�\���̐����̂��߂ɂ����ċL�ڂ��Ă��܂��D�ȉ��ł͌X�̍\���v�f�ɂ��Đ������Ă����܂��D
## Framework SDK
Framework���W���[���̂��ׂẴI�u�W�F�N�g��SDK�N���X*FWSdk*�ɂ���ĊǗ�����܂��D*FWSdk*�N���X�́C�v���O�����̎��s��ʂ��Ă����P�̃I�u�W�F�N�g�����݂���V���O���g���N���X�ł��D*FWSdk*�I�u�W�F�N�g���쐬����ɂ͈ȉ��̂悤�ɂ��܂��D
```
FWSdkIf* fwSdk = FWSdkIf::CreateSdk();
```
�ʏ킱�̑���̓v���O�����̏��������Ɉ�x�������s���܂��D*FWSdk*���쐬����ƁC������*PHSdk*�C*GRSdk*�C*FISdk*�C*HISdk*���쐬����܂��D���������Ă��������[�U���蓮�ō쐬����K�v�͂���܂���D�e���W���[���̋@�\�ɃA�N�Z�X����ɂ͈ȉ��̊֐��ɂ��SDK���擾���܂��D\noindent\begin{tabular}{p{1.0\hsize}}\\*FWSdkIf*				\\ \midrule*PHSdkIf* GetPHSdk()*	\\Physics SDK���擾����D			\\\\*GRSdkIf* GetGRSdk()*	\\Graphics SDK���擾����D		\\\\*FISdkIf* GetFISdk()*	\\FileIO SDK���擾����D			\\\\*HISdkIf* GetHISdk()*	\\HumanInterface SDK���擾����D	\\\\\end{tabular}
## Framework �V�[��





\includegraphics[width=.9\hsize]{fig/fwscene.eps}

\caption{Data structure of Framework, Physics and Graphics modules}


Framework���W���[���̎�ȋ@�\��1��Physics�V�[����Graphics�V�[���̓���������܂��DFig.\,\ref{fig_fwscene}��3�̃��W���[����SDK�ƃV�[���̊֌W�������܂��D*FWSdk*�͔C�ӂ̐��̃V�[���i*FWScene*�N���X�j��ێ����܂��D�܂��C�V�[���͔C�ӂ̐��̃I�u�W�F�N�g�i*FWObject*�N���X�j��ێ����܂��DFig.\,\ref{fig_fwscene}�Ɏ����悤�ɁC�I�u�W�F�N�g��Physics���W���[���̍��̂�Graphics���W���[���̃g�b�v�t���[������Έ�ɑΉ��Â��܂��D�����Ńg�b�v�t���[���Ƃ̓��[���h�t���[���̒����ɂ���t���[���̂��Ƃł��D�����V�~�����[�V�����ɂ��v�Z����鍄�̂̉^�����t���[���̍��W�ϊ��ɔ��f�����邱�ƂŁC�V�~�����[�V�����̗l�q��Graphics���W���[���̋@�\�𗘗p���ĉ������邱�Ƃ��ł���悤�ɂȂ�܂��D�V�[���쐬�Ɋւ���*FWSdk*�̊֐����ȉ��Ɏ����܂��D\noindent\begin{tabular}{p{1.0\hsize}}\\*HITrackballIf*														\\ \midrule*FWSceneIf* CreateScene(const PHSceneDesc\&, const GRSceneDesc\&)*	\\�V�[�����쐬����D															\\\\*int NScene()*	\\�V�[���̐����擾����	\\\\*FWSceneIf* GetScene(int i)*	\\*i*�Ԗڂ̃V�[�����擾����D	\\\\*void MergeScene(FWSceneIf* scene0, FWSceneIf* scene1)*	\\*scene1*�̎q�I�u�W�F�N�g��*scene0*�Ɉڂ��D		\\\\\end{tabular}�V�[�����쐬����ɂ͈ȉ��̂悤�ɂ��܂��D
```
FWSceneIf* fwScene = fwSdk->CreateScene();
```
*FWScene*���쐬����ƁC������*PHScene*��*GRScene*���쐬����C*FWScene*�ƃ����N����܂��D*CreateScene*�Ƀf�B�X�N���v�^���w�肷�邱�Ƃ��ł��܂��D*NScene*�͍쐬�����V�[���̐���Ԃ��܂��D�V�[�����擾����ɂ�*GetScene*���g���܂��D*GetScene*�Ɏw�肷�鐮���͍쐬���ꂽ���ԂɃV�[���ɗ^������ʂ��ԍ��ł��D
```
fwSdk->CreateScene();               // create two scenes
fwSdk->CreateScene();
FWSceneIf *fwScene0, *fwScene1;
fwScene0 = fwSdk->GetScene(0);      // get 1st scene
fwScene1 = fwSdk->GetScene(1);      // get 2nd scene
```
*MergeScene*���g����2�̃V�[���𓝍�����1�̃V�[���ɂł��܂��D
```
fwSdk->MergeScene(fwScene0, fwScene1);
```
��̃R�[�h�ł�*scene1*������*FWObject*��*scene0*�Ɉڂ���C�����ɃV�[�����Q�Ƃ���*PHScene*��*GRScene*�Ɋւ��Ă����ꂼ���*MergeScene*�֐��ɂ�蓝�����s���܂��D���ɁC*FWScene*�̊�{�@�\���ȉ��Ɏ����܂��D\noindent\begin{tabular}{p{.6\hsize}p{.3\hsize}}\\*FWSceneIf*													\\ \midrule*void SetPHScene(PHSceneIf*)*	& Physics�V�[���̐ݒ�		\\*PHSceneIf* GetPHScene()*		& Physics�V�[���̎擾		\\*void SetGRScene(GRSceneIf*)*	& Graphics�V�[���̐ݒ�		\\*GRSceneIf* GetGRScene()*		& Graphics�V�[���̎擾		\\*FWObjectIf* CreateFWObject()*	& �I�u�W�F�N�g�̍쐬		\\*int NObject()const*				& �I�u�W�F�N�g�̐�			\\*FWObjectIf** GetObjects()*		& �I�u�W�F�N�g�z��̎擾	\\*void Sync(bool)*				& ����						\\\\\end{tabular}*[Set|Get][PH|GR]Scene*�֐��̓V�[���Ɋ��蓖�Ă�ꂽ*PHScene*��*GRScene*���擾������C�ʂ̃V�[�������蓖�Ă��肷��̂Ɏg�p���܂��D*CreateFWObject*�֐���*FWObject*�I�u�W�F�N�g���쐬���܂��D���̂Ƃ��C�V���ɍ쐬���ꂽ*FWObject*�ɂ�*PHSolid*�����*GRFrame*�͊��蓖�Ă��Ă��Ȃ���ԂɂȂ��Ă���̂Œ��ӂ��Ă��������D�����������ɍ쐬����ɂ́C�ȉ��̃R�[�h��1�Z�b�g�Ŏ��s���܂��D
```
FWObjectIf* fwObj = fwScene->CreateFWObject();
fwObj->SetPHSolid(fwScene->GetPHScene()->CreateSolid());
fwObj->SetGRFrame(
    fwScene->GetGRScene()->CreateVisual(GRFrameDesc())->Cast);
```
*Sync*�֐���*PHScene*��*GRScene*�̓����ɗp���܂��D
```
fwScene->Sync(true);
```
�Ƃ���ƁC���̃V�[�����Q�Ƃ���*PHScene*���̍��̂̈ʒu�ƌ������C���������̃V�[�����Q�Ƃ���*GRScene*���̃g�b�v�t���[���̈ʒu�ƌ����ɔ��f����܂��D���̂Ƃ��̍��̂ƃg�b�v�t���[���Ƃ̑Ή��֌W��*FWObject*�ɂ���`����܂��D�t��
```
fwScene->Sync(false);
```
�Ƃ���ƁC���l�̃��J�j�Y���Ŋe�g�b�v�t���[���̈ʒu�ƌ������Ή����鍄�̂ɔ��f����܂��D
## �V�[���̃��[�h�ƃZ�[�u
FileIO���W���[���𗘗p���ăV�[�������[�h�C�Z�[�u���邽�߂̊֐����p�ӂ���Ă��܂��D�܂����[�h�ɂ͈ȉ��̊֐���p���܂��D\noindent\begin{tabular}{p{1.0\hsize}}\\*FWSdkIf*														\\ \midrule*bool LoadScene(UTString path, ImportIf* imp, const IfInfo* ii, ObjectIfs* objs)*	\\�V�[�������[�h����D		\\\\\end{tabular}*path*�̓��[�h����t�@�C���ւ̃p�X���i�[����������ł��D*imp*�ɂ̓C���|�[�g�����i�[���邽�߂�*Import*�I�u�W�F�N�g��^���܂��D�C���|�[�g�����L������K�v�̂Ȃ��ꍇ��*NULL*�ō\���܂���D*ii*�̓��[�h����t�@�C���̎�ނ𖾎����邽�߂̌^���ł��D*NULL*���w�肷��ƃp�X�̊g���q���玩�����ʂ���܂��D*objs*�̓��[�h�ɂ���č쐬�����I�u�W�F�N�g�c���[�̐e�I�u�W�F�N�g���i�[�����z��ł��D���[�h�ɐ��������*true*�C���s�����*false*���Ԃ���܂��D���[�h���ꂽ�V�[����*FWSdk*�̃V�[���z��̖����ɉ������܂��D���ɁC�V�[�����Z�[�u����ɂ͈ȉ��̊֐����g���܂��D\noindent\begin{tabular}{p{1.0\hsize}}\\*FWSdkIf*														\\ \midrule*bool SaveScene(UTString path, ImportIf* imp, const IfInfo* ii, ObjectIfs* objs)*	\\�V�[�����Z�[�u����D		\\\\\end{tabular}�����̈Ӗ���*LoadScene*�Ɠ��l�ł��D*imp*�ɂ̓��[�h���ɋL�������C���|�[�g����^���܂��D�ȗ�����ƃV�[���S�̂��P��̃t�@�C���ɃZ�[�u����܂��D�Z�[�u�ɐ��������*true*�C���s�����*false*���Ԃ���܂��D
## Framework �I�u�W�F�N�g
*FWObject*��*PHSolid*��*GRFrame*�̋��n������Ȗ����ł��̂ŁC���ꎩ�̂͂���قǑ����̋@�\�������Ă��܂���D
## �A�v���P�[�V�����N���X
Springhead�𗘗p����A�v���P�[�V�����̍쐬��e�Ղɂ��邽�߂ɁC�A�v���P�[�V�����N���X*FWApp*���p�ӂ���Ă��܂��D\ref{sec_create_application}��*FWApp*���g���ĊȒP�ȃA�v���P�[�V�������쐬������@�ɂ��Đ������܂����̂ł���������킹�ĎQ�l�ɂ��Ă��������D�`���Ő��������ʂ�CSpringhead�̂قƂ�ǂ̃I�u�W�F�N�g�́C�e�I�u�W�F�N�g��*Create*�n�֐����g���č쐬���܂����C*FWApp*�͗�O�I�ɁCC++�̃N���X�p����p���ă��[�U�̃A�v���P�[�V�����N���X���`������@���Ƃ�܂��D���̕������z�֐��ɂ���ē���̃J�X�^�}�C�Y���t���L�V�u���ɍs���邩��ł��D�ȉ��ł�*FWApp*�̋@�\�⃆�[�U���������ׂ����z�֐��ɂ��ď��Ɍ��Ă����܂��D
### ������
*FWApp*�̏����������͉��z�֐�*Init*�ōs���܂��D\noindent\begin{tabular}{p{.7\hsize}p{.2\hsize}}\\*FWApp*											\\ \midrule*virtual void Init(int argc, char* argv[])*	&	\\\\\end{tabular}�ȉ���*Init*�֐��̃f�t�H���g�̎����������܂��D
```
void FWApp::Init(int argc, char* argv[]){
    // create SDK
    CreateSdk();
    // create a single scene
    GetSdk()->CreateScene();
    // initialize window manager
    GRInit(argc, argv);
    // create main window
    CreateWin();
    // create timer
    CreateTimer();
}
```
�͂��߂�
```
    CreateSdk();
```
��SDK���쐬���܂��D����
```
    GRInit(argc, argv);
```
�ŃE�B���h�E�}�l�W�����쐬����܂��D�f�t�H���g�ł�GLUT��p����E�B���h�E�}�l�W�����쐬����܂��D�����
```
    GetSdk()->CreateScene();
```
��*FWScene*��1�쐬���܂��D�Â���
```
    CreateWin();
```
�Ń��C���E�B���h�E���쐬���܂��D�Ō��
```
    CreateTimer();
```
�Ń^�C�}���쐬���܂��D���̊�{�����ɒǉ����ĂȂ�炩�̏������s���ꍇ��
```
virtual void Init(int argc = 0, char* argv[] = 0){
    // select GLUI window manager
    SetGRAdaptee(TypeGLUI);

    // call base Init
    FWApp::Init(argc, argv);

    // do extra initialization here


}
```
�̂悤�ɁC*FWApp:Init*�����s���Ă���ǉ��̏������s���̂��ǂ��ł��傤�D����C�ȉ��ɋ�����悤�ȃJ�X�^�}�C�Y���K�v�ȏꍇ��*Init*�֐��̏����S�̂�h���N���X�ɋL�q����K�v������܂��D

-  �V�[���������J�X�^�}�C�Y������
-  �E�B���h�E�̏����T�C�Y��^�C�g����ύX������
-  �قȂ��ނ̃^�C�}���g������

���̏ꍇ�́C��ɍڂ���*Init*�̃f�t�H���g���������ƂɕK�v�ȕ����ɏC����������̂��ǂ��ł��傤�D�v���O�����̑S�̂̍\���͒ʏ�ȉ��̂悤�ɂȂ�܂��D
```
MyApp app;

int main(int argc, char* argv[]){
    app.Init(argc, argv);
    app.StartMainLoop();
    return 0;
}
```
������*MyApp*�̓��[�U����`����*FWApp*�̔h���N���X�ł��i������񑼂̖��O�ł��\���܂���j�D*MyApp*�̃C���X�^���X���O���[�o���ϐ��Ƃ��Ē�`���C*main*�֐���*Init*�C*StartMainLoop*���������s���܂��D*StartMainLoop*�֐��̓A�v���P�[�V�����̃��C�����[�v���J�n���܂��D
### �^�C�}
�^�C�}�̍쐬�ɂ�*CreateTimer*�֐����g���܂��D�ʏ�C*CreateTimer*��*Init*�̒��ŌĂт܂��D\noindent\begin{tabular}{p{.7\hsize}p{.2\hsize}}\\*FWApp*												\\ \midrule*UTTimerIf* CreateTimer(UTTimerIf::Mode mode)*	&	\\\\\end{tabular}����*mode*�Ɏw��ł���l��*UTTimer*��*SetMode*�Ɠ����ł��D\ref{sec_uttimer}�߂��Q�Ƃ��Ă��������D�߂�l�Ƃ���*UTTimer*�̃C���^�t�F�[�X���Ԃ���܂��D�����Ȃǂ̐ݒ�͂��̃C���^�t�F�[�X����čs���܂��D�V�~�����[�V�����p�ƕ`��p��2�̃^�C�}���쐬�������ȉ��Ɏ����܂��D
```
UTTimerIf *timerSim, *timerDraw;
timerSim = CreateTimer(MULTIMEDIA);
timerSim->SetInterval(10);
timerDraw = CreateTimer(FRAMEWORK);
timerDraw->SetInterval(50);
```
���̗�ł̓V�~�����[�V�����p�ɂ͎�����$10$[ms]�̃}���`���f�B�A�^�C�}���g���C�`��p�ɂ͎���$50$[ms]�̃t���[�����[�N�^�C�}�iGLUT�^�C�}�j���g���Ă��܂��D�^�C�}���n������ƁC�������ƂɈȉ��̉��z�֐����Ă΂�܂��D\noindent\begin{tabular}{p{.7\hsize}p{.2\hsize}}\\*FWApp*								\\ \midrule*virtual void TimerFunc(int id)*	&	\\\\\end{tabular}�^�C�}�̔��ʂ͈���$id$�ōs���܂��D*TimerFunc*�̃f�t�H���g�̐U�镑���ł́C�J�����g�E�B���h�E�̃V�[����*Step*���ĂсC����*PostRedisplay*�ōĕ`��v���𔭍s���܂��i���̌��ʁC�����*Display*�֐����Ăяo����܂��j�D���̐U�镑�����J�X�^�}�C�Y�������ꍇ��*TimerFunc*�֐����I�[�o���C�h���܂��D
```
void TimerFunc(int id){
    // proceed simulation of scene attached to current window
    if(id == timerSim->GetID()){
        GetCurrentWin()->GetScene()->Step();
    }
    // generate redisplay request
    else if(id == timerDraw->GetID()){
        PostRedisplay();
    }
}
```
���̗�ł̓V�~�����[�V�����ƕ`��ɈقȂ�2�̃^�C�}���g�p���Ă��܂��D
### �`��
�`�揈���͎��̉��z�֐��ōs���܂��D\noindent\begin{tabular}{p{.7\hsize}p{.2\hsize}}\\*FWApp*						\\ \midrule*virtual void Display()*	&	\\\\\end{tabular}*Display*�͕`��v�������s���ꂽ�Ƃ��ɌĂяo����܂��D�`��v����*PostRedisplay*�֐��ōs���܂��D\noindent\begin{tabular}{p{.7\hsize}p{.2\hsize}}\\*FWApp*							\\ \midrule*virtual void PostRedisplay()*	&	\\\\\end{tabular}*Display*�֐��̃f�t�H���g�̐U�镑���ł̓J�����g�E�B���h�E��*Display*�֐����Ă΂�܂��D
### �L�[�{�[�h�E�}�E�X�C�x���g
*FWApp*�͊e�E�B���h�E�Ɋ֘A�t����ꂽ���z�L�[�{�[�h�E�}�E�X�f�o�C�X*DVKeyMouse*�ɃR�[���o�b�N�o�^����Ă��܂��D���������Ĉȉ��̉��z�֐����I�[�o���C�h���邱�ƂŃL�[�{�[�h�E�}�E�X�C�x���g�������ł��܂��D\noindent\begin{tabular}{p{1.0\hsize}}\\*FWApp*							\\ \midrule*virtual bool OnMouse(int button, int state, int x, int y)*	\\*virtual bool OnDoubleClick(int button, int x, int y)*	\\*virtual bool OnMouseMove(int state, int x, int y, int zdelta)*	\\*virtual bool OnKey(int state, int key, int x, int y)*	\\\\\end{tabular}�e�C�x���g�n���h���̏ڍׂɂ��Ă�\ref{sec_hi_keymouse}�߂��Q�Ƃ��ĉ������D
## �E�B���h�E
�E�B���h�E�₻�̑���GUI�R���g���[���̍쐬��Framework�ɂ���ăT�|�[�g����Ă��܂��D���łɏq�ׂĂ����Ƃ���C*FWApp*�̓g�b�v���x���E�B���h�E�̔z��������܂��D
## Framework��p�����V�~�����[�V�����ƕ`��
Framework���W���[������ĕ����V�~�����[�V�������s���ɂ͈ȉ��̊֐����g���܂��D\noindent\begin{tabular}{p{.7\hsize}p{.2\hsize}}\\*FWSdkIf*			\\ \midrule*void Step()*	& 	\\\end{tabular}\noindent*FWSdk*��*Step*�̓A�N�e�B�u�V�[����*Step*���Ăт܂��D����������*GetScene()->Step()*�Ɠ����ł��D���*FWScene*��*Step*�́C�ێ����Ă���*PHScene*��*Step*���Ăт܂��D����������*GetPHScene()->Step()*�Ɠ����ł��D�����Ƃ��������b�p�[�֐��ł����C���[�U�̃^�C�v�񐔐ߖ�̂��߂ɗp�ӂ���Ă��܂��DFramework��p�����`��ɂ�2�ʂ�̕��@������܂��D1��Graphics�̃V�[���O���t��p������@�C����1��Physics�V�[���𒼐ڕ`�悷����@�ł��D��҂̓f�o�b�O�`��Ƃ��Ă΂�Ă��܂��D\noindent\begin{tabular}{p{.7\hsize}p{.2\hsize}}\\*FWSdkIf*						\\ \midrule*void Draw()*				&	\\*void SetDebugMode(bool)*	& 	\\*bool GetDebugMode()*		&	\\\\\end{tabular}*Draw*�֐��͕`�惂�[�h�ɉ������`�揈�����s���܂��D*Draw*�͒ʏ�A�v���P�[�V�����̕`��n���h������Ăяo���܂��D*[Set|Get]DebugMode*�͒ʏ�`�惂�[�h(*false*)�ƃf�o�b�O�`�惂�[�h(*true*)��؂�ւ��܂��D�ʏ�`�惂�[�h�ɂ�����*Draw*�֐����ĂԂƁC�͂��߂ɃA�N�e�B�u�V�[���ɂ���*Sync(true)*���Ă΂�C���̂̏�Ԃ��V�[���O���t�ɔ��f����܂��D���ɃA�N�e�B�u�V�[�����Q�Ƃ���*GRScene*��*Render*�֐����Ă΂�C�V�[���O���t���`�悳��܂��D���̕��@�ł̓V�[���O���t�������C�g��e�N�X�`���Ȃǂ̏����ő�����p���ăt�H�g���A���X�e�B�b�N�ȕ`�悪�\�ł��D���̔��ʁC�����V�~�����[�V��������ړI�ł���ꍇ�ɂ̓V�[���O���t�̍\�z�Ƃ����t���I�ȃR�X�g���x����Ȃ���΂Ȃ�Ȃ��Ƃ����f�����b�g������܂��D�f�o�b�O�`��ɂ��Ă͎��߂Ő������܂��D
## �f�o�b�O�`��
�f�o�b�O�`�惂�[�h�ł�*PHScene*�̏�񂾂���p���ĕ`�悪�s����̂ŁC�V�[���O���t�\�z�̎�Ԃ��Ȃ��܂��D�܂��C���̂ɉ����͂Ȃǂ̕����V�~�����[�V�����Ɋւ�������������邱�Ƃ��ł��܂��D����ŁC�\��F�����g���Ȃ��ȂǁC�`��̎��R�x�ɂ͈��̐��񂪐����܂��D�f�o�b�O�`�惂�[�h�ł�*FWScene*��*DrawPHScene*�֐��ɂ��`�揈�����s���܂��D\noindent\begin{tabular}{p{.7\hsize}p{.2\hsize}}\\*FWSceneIf*									\\ \midrule*void DrawPHScene(GRRenderIf* render)*	&	\\\\\end{tabular}*DrawPHScene*�́C�e���̂Ɋ��蓖�Ă��Ă���Փ˔���`��C���W���C��p���Ă���́C�ڐG�f�ʂȂǂ�`�悵�܂��D���ڕʂɕ`����s������C�`��F��ݒ肷��ɂ͌�q����`�搧��֐���p���܂��D
### �f�o�b�O�`�掞�̃J�����ƃ��C�g
�f�o�b�O�`��ɂ����Ă��J�����̏���*GRScene*���Q�Ƃ���܂��D����*GRScene*���J������ۗL���Ă���ꍇ�͂��̃J������*Render*���Ă΂�C���_�Ɠ��e�ϊ����ݒ肳��܂��D*GRScene*���J�����������Ȃ��ꍇ�͎蓮�Őݒ肷��K�v������܂��D���C�g�ɂ��ẮC�����O���Ń����_���ɑ΂��ă��C�g�ݒ肪����Ă���ꍇ�͂��̐ݒ肪�D�悳��C�����_����1�����C�g�������Ȃ��ꍇ�͓����Ńf�t�H���g���C�g���ݒ肳��܂��D
### �ʂ̕`��
�ȉ��̊֐���*DrawPHScene*����Ăяo����܂����C���[�U���ʂɌĂяo�����Ƃ��ł��܂��D\noindent\begin{tabular}{p{.7\hsize}p{.2\hsize}}\\*FWSceneIf*												\\ \midrule*void DrawSolid(GRRenderIf*, PHSolidIf*, bool)*		&	���̂�`��\\*void DrawShape(GRRenderIf*, CDShapeIf*, bool)*		&	�`���`��\\*void DrawConstraint(GRRenderIf*, PHConstraintIf*)*	&	�S����`��\\*void DrawContact(GRRenderIf*, PHContactPointIf*)*	&	�ڐG��`��\\*void DrawIK(GRRenderIf*, PHIKEngineIf*)*			&	IK����`��\\\\\end{tabular}
### �`�搧��
�ȉ��̊֐��͕`���On/Off��؂�ւ��܂��D\noindent\begin{tabular}{p{.8\hsize}p{.1\hsize}}\\*FWSceneIf*													\\ \midrule*void SetRenderMode(bool solid, bool wire)*					&	\\*void EnableRender(ObjectIf* obj, bool enable)*				&	\\*void EnableRenderAxis(bool world, bool solid, bool con)*	&	\\*void EnableRenderForce(bool solid, bool con)*				&	\\*void EnableRenderContact(bool enable)*						&	\\*void EnableRenderGrid(bool x, bool y, bool z)*				&	\\*void EnableRenderIK(bool enable)*							&	\\\\\end{tabular}*SetRenderMode*�̓\���b�h�`��i�ʂ�h��Ԃ��j�ƃ��C���t���[���`��i�ʂ̗֊s�j��On/Off��؂�ւ��܂��D*EnableRender*�͎w�肵���I�u�W�F�N�g�̕`���On/Off��؂�ւ��܂��D���ڂł͂Ȃ��I�u�W�F�N�g���x���ŕ`�搧�䂵�����ꍇ�ɕ֗��ł��D*obj*�Ɏw��ł���͍̂���(*PHSolidIf**)���S��(*PHConstraintIf**)�ł��D*EnableRenderAxis*�͍��ڕʂɍ��W���̕`���ݒ肵�܂��D*world*�̓��[���h���W���C*solid*�͍��́C*con*�͍S���̍��W���ł��D*EnableRenderForce*�͗͂ƃ��[�����g�̕`���ݒ肵�܂��D*solid*�͍��̂ɉ����́i�������O�݂͂̂ōS���͂͏����j�C*con*�͍S���͂ł��D*EnableRenderGrid*�͊e���Ɋւ��ăO���b�h�̕`���ݒ肵�܂��D*EnableRenderIK*��IK���̕`���ݒ肵�܂��D�ȉ��̊֐��͕`�摮�����w�肷��̂Ɏg���܂��D\noindent\begin{tabular}{p{.8\hsize}p{.1\hsize}}\\*FWSceneIf*																\\ \midrule*void SetSolidMaterial(int mat, PHSolidIf* solid)*						&	\\*void SetWireMaterial (int mat, PHSolidIf* solid)*						&	\\*void SetAxisMaterial(int matX, int matY, int matZ)*						&	\\*void SetAxisScale(float world, float solid, float con)*					&	\\*void SetAxisStyle(int style)*											&	\\*void SetForceMaterial(int matForce, int matMoment)*						&	\\*void SetForceScale(float scaleForce, float scaleMoment)*				&	\\*void SetContactMaterial(int mat)*										&	\\*void SetGridOption(char axis, float offset, float size, int slice)*		&	\\*void SetGridMaterial(int matX, int matY, int matZ)*						&	\\*void SetIKMaterial(int mat)*											&	\\*void SetIKScale(float scale)*											&	\\\\\end{tabular}*SetSolidMaterial*�͎w�肵�����̂̃\���b�h�`��F���w�肵�܂��D*mat*�Ɏw��ł���l��\ref{sec_grmaterial}�߂ŏq�ׂ��\��F�ł��D*solid*��*NULL*���w�肷��Ƃ��ׂĂ̍��̂̐F���w�肳�ꂽ�l�ɂȂ�܂��D*SetWireMaterial*�͓��l�ɍ��̂̃��C���t���[���`��F���w�肵�܂��D*SetAxisMaterial*�͍��W���̐F��x, y, z�ʂɎw�肵�܂��D*SetAxisScale*�͍��W���̏k�ڂ��w�肵�܂��D*SetAxisStyle*�͍��W���̃X�^�C�����w�肵�܂��D*SetForceMaterial*�C*SetForceScale*�͂��ꂼ��́i���i�͂ƃ��[�����g�j�̕`��F�Ək�ڂ��w�肵�܂��D*SetContactMaterial*�͐ڐG�f�ʂ̕`��F���w�肵�܂��D*SetGridOption*�̓O���b�h�̃I�v�V�������w�肵�܂��D*SetGridMaterial*�̓O���b�h�̕`��F���w�肵�܂��D*SetIKMaterial*�C*SetIKScale*��IK���̕`��F�Ək�ڂ��w�肵�܂��D
## �͊o�C���^���N�V�����̂��߂̃A�v���P�[�V����
Springhead2�ɂ̓V�[���Ƃ̗͊o�C���^���N�V�����̂��߂̃G���W��*PHHapticEngine*���܂܂�Ă��܂��D�����ł͗͊o�C���^���N�V�����̂��߂̃A�v���P�[�V�����̍쐬���@�ɂ��Đ������܂��D�܂��́C�ʏ��*Framework*�A�v���P�[�V�����̍쐬�Ɠ��l�ɁC�ЂȌ`�N���X�ł���*FWApp*���p�����ăA�v���P�[�V�������쐬���܂��D�����āC*Init*�֐����ŗ͊o�C���^���N�V������L�����ƁC�͊o�C���^���N�V�����V�X�e���̃��[�h��ݒ肵�܂��D
```
	// given PHSceneIf* phScene,
    phScene->GetHapticEngine()->EnableHapticEngine(true);
    phScene->GetHapticEngine()->
    SetHapticEngineMode(PHHapticEngineDesc::MULTI_THREAD);
```
�͊o�C���^���N�V�����V�X�e���̃��[�h�̓V���O���X���b�h�A�v���P�[�V�����̂��߂�*SINGLE\_THREAD*�C�}���`���f�B�A�A�v���P�[�V�����̂��߂�*MULTI\_THREAD*�C�Ǐ��V�~�����[�V�����𗘗p����*LOCAL\_DYNAMICS*��3��ނ�����܂��D�W���ł�*MULTI\_THREAD*���ݒ肳��Ă��܂��D*MULTI\_THREAD*�C*LOCAL\_DYNAMICS*�̃��[�h�̓}���`�X���b�h�𗘗p�����A�v���P�[�V�����ƂȂ�C�����V�~�����[�V���������s���镨���X���b�h�C�͊o�����_�����O�����s����͊o�X���b�h������ɓ����܂��D���̂��߁C���ꂼ��̃X���b�h���R�[���o�b�N���邽�߂Ƀ^�C�}��ݒ肵�����K�v������܂��D\clearpage
```
	// given PHSceneIf* phScene,
	int physicsTimerID, hapticTimerID // �e�^�C�}��ID
	// FWApp::TimerFunc���I�[�o���C�h�����R�[���o�b�N�֐�
	void MyApp::TimerFunc(int id){
        if(hapticTimerID == id){
            // �͊o�X���b�h�̃R�[���o�b�N
            phScene->StepHapticLoop();	
        }else{
            // �����X���b�h�̃R�[���o�b�N
            phScene->GetHapticEngine()->StepPhysicsSimulation();	
            PostRedisplay();	// �`��
        }	
	}	
```
���Ƀ��[�U���I�u�W�F�N�g�ƃC���^���N�V�������邽�߂̃|�C���^�C�͊o�|�C���^*PHHapticPointer*�����܂��D�����āC�ǂ̃C���^�t�F�[�X�ƌ�������̂���ݒ肵�܂��D*PHHapticPointer*��*PHScene*�����邱�Ƃ��ł��܂��D*PHHapticPointer*��*PHSolid*���p�������N���X��*PHSolid*�̊֐��𗘗p���āC���ʁC�����e���\���C�`��Ȃǂ����킹�Đݒ肵�܂��D�Ⴆ��Spidar-G6�Ɛڑ�����ꍇ�ɂ́C
```
	// given PHSceneIf* phScene,
	// given HISpidarIf* spg,
    PHHapticPointerIf* pointer = phScene->CreateHapticPointer();
    /*
        ���ʁC�����e���\���C�`��Ȃǂ�ݒ肷��
    */
    pointer->SetHumanInterface(spg);
```
�Ƃ��܂��D�����PHHapticPointer�ɂ��Ĉȉ��̊֐���p���āC�͊o�񎦂̂��߂̃p�����[�^��ݒ肵�܂��D\noindent\begin{tabular}{p{.8\hsize}p{.1\hsize}}\\*PHHapticPointerIf*													\\ \midrule*void SetHumanInterface(HIBaseIf* interface)*						&	\\*void SetDefaultPose(Posed pose)*									&	\\*void SetPosScale(double scale)*										&	\\*void SetReflexSpring(float s)*										&	\\*void SetReflexDamper(float s)*										&	\\*void EnableFriction(bool b)*										&	\\*void EnableVibration(bool b)*										&	\\*void SetLocalRange(float s)*										&	\\*void SetHapticRenderMode(PHHapticPointerDesc::HapticRenderMode m )*	&	\\\\\end{tabular}*SetHumanInterface*�͗͊o�|�C���^�Ƀq���[�}���C���^�t�F�[�X�����蓖�Ă܂��D*SetDefaultPose*�̓V�[�����ł̗͊o�|�C���^�̏����ʒu���w�肵�܂��D*SetPosScale*�̓V�[�����ł̗͊o�|�C���^�̉��X�P�[�����w�肵�܂��D*SetReflexSpring*�͗͊o�����_�����O�i���͌v�Z�j�̂��߂̃o�l�W���l��ݒ肵�܂��D*SetReflexDamper*�͗͊o�����_�����O�̂��߂̃_���p�W���l��ݒ肵�܂��D*EnableFriction*�͗͊o�|�C���^�̖��C�͒񎦂�L�������܂��D*EnableVibration*�͗͊o�|�C���^�̐U���񎦂�L�������܂��D*SetLocalRange*�͋Ǐ��V�~�����[�V�����V�X�e�����g�p���̋Ǐ��V�~�����[�V�����͈͂��w�肵�܂��D*SetHapticRenderMode*�͗͊o�����_�����O�̃��[�h���w�肵�܂��D�Ō��*SetHapticRenderMode*�ɂ�*PENALTY*�C*CONSTRAINT*�̃��[�h������܂��D*PENALTY*�͗͊o�|�C���^�����̂ɐڐG�������̊e�ڐG�_�̐N���ʂƃo�l�_���p�W�����悶�����̂𑫂����킹�����̂����͂Ƃ��Čv�Z����C�C���^�t�F�[�X����o�͂���܂��D*CONSTRAINT*�͗͊o�|�C���^�����̂ɐN�����Ă��Ȃ���ԁi�v���L�V�j�����߁C�͊o�|�C���^�ƃv���L�V�̋����̍����Ƀo�l�_���p�W�����悶�����̂𔽗͂Ƃ��Čv�Z���܂��D
