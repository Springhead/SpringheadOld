EmbPython���W���[���́C�X�N���v�g����Python�Ƃ̘A�g�@�\��񋟂��܂��DPython�C���^�v���^����Springhead�̋@�\���Ăяo������CSpringhead�A�v���P�[�V������Python�C���^�v���^��g�ݍ���ŃX�N���v�e�B���O�G���W���Ƃ��Ďg�p����Ƃ����������ł��܂��DEmbPython���W���[���̎g�p�ɂ��CPython�C���^�v���^���Springhead API�N���X�ւ̃C���^�t�F�[�X�N���X���񋟂���܂��D���[�U��Python�C���^�t�F�[�X�N���X���g�p����Springhead�̊e�@�\�ɃA�N�Z�X���܂��DPython�C���^�t�F�[�X�N���X�͓����I��Springhead�̋@�\���Ăяo���C���ʂ�Python�C���^�t�F�[�X�N���X�ɕϊ����ĕԂ��܂��D
## ���p�@
�傫�������ē�ʂ�̗��p�@��z�肵�Ă��܂��D��́CC++�Ŏ������ꂽSpringhead�A�v���P�[�V�����ɑ΂��CPython�C���^�v���^��g�ݍ��ނ��Ƃł��DSpringhead�A�v���P�[�V�����̋@�\�̈ꕔ��Python�X�N���v�g�L�q���C�g���������߂܂��D������́CPython�C���^�v���^�ɑ΂���O���g�����W���[��(Python DLL, pyd)�Ƃ��Ē񋟂��ꂽSpringhead�𗘗p���邱�ƂŁCPython�A�v���P�[�V������Springhead�̋@�\��g�ݍ��ޗ��p�@�ł��D�ǂ���̏ꍇ�ɂ����Ă��CEmbPython���W���[����Python������Springhead�̊֐����Ăяo�����߂̃C���^�t�F�[�X��񋟂��܂��D�֌W��\Fig{epoverview}�Ɏ����܂��D\begin{fig}\epscapopt{epoverview}{Python�A�g��EmbPython���W���[���̈ʒu�Â�}{width=0.8\hsize}\end{fig}
### ���ϐ�PATH�̐ݒ�
Springhead�̓���́A`Springhead2\core\bin\win64`�t�H���_�A�����`Springhead2\dependency\bin\win64`�t�H���_����dll�Q�Ɉˑ����Ă��܂��B�����̃t�H���_�̐�΃p�X�����ϐ�PATH�ɒǉ����Ă��������B
### Springhead�ւ�Python�g����
Springhead�A�v���P�[�V������Python�C���^�v���^��g�ݍ���ŗ��p������@��������܂��D�{�߂ł͂܂�Springhead�ɓ������ꂽPython�C���^�v���^�g�ݍ��݃T���v�����Љ�C�ȒP�Ȏg������������܂��D���̌�C�T���v���ɂ�����Python�C���^�v���^�g�ݍ��݂̂��߂̃\�[�X�R�[�h�ɂ��ĉ�����܂��D
#### PythonSpr�T���v���̃r���h�Ǝ��s
Python�C���^�v���^�g�ݍ��݃T���v���� `src\Samples\EmbPython\PythonSpr` �ɂ���܂��D�r���h����� `PythonSpr.exe` ���ł��܂��D*PythonSpr*�T���v���͕W���I��Springhead�T���v���A�v���P�[�V�����t���[�����[�N��Python�C���^�v���^��g�ݍ��񂾂��̂ŁC�����V�[�����\�z�E�V�~�����[�V�����E�`�悷�鎖���ł��܂��DPython�C���^�v���^�����*phSdk*��*fwSdk*�ɃA�N�Z�X���邱�Ƃ��ł��C�\���@�\��؂�ւ�����V�[���ɃI�u�W�F�N�g���쐬������Ƃ��������Ƃ�Python����s���܂��D���s�̑O�ɁC���ϐ���ݒ肵�܂��D����́CSpringhead�A�v���P�[�V�����ɑg�ݍ��܂ꂽPython�C���^�v���^��Python�̕W�����C�u�����Q�ɃA�N�Z�X���邽�߂ɕK�v�ł��D\begin{description}- [*SPRPYTHONPATH*���ϐ�]~Springhead�����[�X��W�J�����t�H���_����`bin\src\Python32\Lib`�ւ̃t���p�X���w�肵�܂��DPython3.2��`c:\Python32`�ɃC���X�g�[�����Ă���ꍇ�C`C:\Python32\Lib`�ł����܂��܂���D\end{description}`PythonSpr.exe`�����s����Ǝ��̂悤�ȉ�ʂ�����܂��D���X�N���[���V���b�g���E��Springhead�̎��s��ʁC���̃R���\�[����Python�v�����v�g�ł��D�N�����ɂ́CSpringhead���s��ʂɂ͉��̃V�[�����\�z����Ă��Ȃ����߁C���[���h���W�n���������݂̂��`�悳��Ă��܂��D����@�͈ȉ��̒ʂ�ł��D\begin{description}- [�}�E�X ���h���b�O] ���_�ύX�i��]�j- [�}�E�X �E�h���b�O] ���_�ύX�i�g��k���j- [�X�y�[�X�L�[] �V�~�����[�V�����J�n�E�ꎞ��~�i�N������͒�~���Ă��܂��j\end{description}
#### PythonSpr�T���v���̗V�ѕ�
���̐߂ł́CPython�R�[�h�𒆐S�Ƃ���Springhead�̋@�\�𗘗p�����̓I�ȕ��@���Љ�܂��DPython�����Springhead API���p�Ɋւ���ڂ����d�l��\SECTION{pythonsprAPI}���Q�Ƃ��Ă��������DPython�v�����v�g���Springhead�̃R�[�h����͂��Ď��s���邱�Ƃ��ł��܂��D�ȉ��̂悤�ɓ��͂��ăV�~�����[�V�������J�n�i�X�y�[�X�L�[�j����ƁC���̂��쐬����ė����Ă����܂��D
```
# ���̂������邾���̃T���v��

>>> fwScene   �� ������ԂŒ�`����Ă���ϐ��ŁC�A�v���P�[�V�������ێ�����fwScene�ɃA�N�Z�X�ł��܂�
<Framework.FWScene object at 0x05250A40>
>>> phScene = fwScene.GetPHScene()
>>> desc = Spr.PHSolidDesc()
>>> desc.mass = 2.0
>>> solid0 = phScene.CreateSolid(desc)
```
�`���^���邱�Ƃ��ł��܂��D�Ȃ��C�Ō�̍s��*solid0.AddShape(box0)*�����s����܂ō��̂Ɍ`��͊��蓖�Ă��Ȃ��̂ŁC���̍s����͂��I���܂ł̓X�y�[�X�L�[���������ɃV�~�����[�V�������ꎞ��~��Ԃɂ��Ă����Ƃ悢�ł��傤�D
```
# �`��̂��鍄�̂������邾���̃T���v��

>>> phScene = fwScene.GetPHScene()
>>> phSdk   = phScene.GetSdk()
>>> descSolid = Spr.PHSolidDesc()
>>> solid0 = phScene.CreateSolid(descSolid)
>>> descBox = Spr.CDBoxDesc()
>>> descBox.boxsize = Spr.Vec3f(1,2,3)
>>> box0 = phSdk.CreateShape(Spr.CDBox.GetIfInfoStatic(), descBox)
>>> solid0.AddShape(box0)
```
���i�ʒu���Œ肳�ꂽ���́j���쐬����ƁC����ɂ���炵���Ȃ�܂��D
```
>>> phScene = fwScene.GetPHScene()
>>> phSdk   = phScene.GetSdk()

# ��������
>>> descSolid = Spr.PHSolidDesc()
>>> solid0 = phScene.CreateSolid(descSolid)
>>> descBox = Spr.CDBoxDesc()
>>> descBox.boxsize = Spr.Vec3f(10,2,10)
>>> boxifinfo = Spr.CDBox.GetIfInfoStatic()
>>> solid0.AddShape(phSdk.CreateShape(boxifinfo, descBox))
>>> solid0.SetFramePosition(Spr.Vec3d(0,-1,0))
>>> solid0.SetDynamical(False)

# ���̏�ɔ��������čڂ���
>>> solid1 = phScene.CreateSolid(descSolid)
>>> descBox.boxsize = Spr.Vec3f(1,1,1)
>>> boxifinfo = Spr.CDBox.GetIfInfoStatic()
>>> solid1.AddShape(phSdk.CreateShape(boxifinfo, descBox))
```
�͂������邱�Ƃ��ł��܂��D
```
>>> solid1.AddForce(Spr.Vec3d(0,200,0))
```
Python��For��While���g���Čp�����ė͂������邱�Ƃ��ł��܂��D
```
>>> import time
>>> for i in range(0,100):
>>>     solid1.AddForce(Spr.Vec3d(0,20,0))
>>>     time.sleep(0.01)
```
���p�Ƃ��āC�ȒP�Ȑ��䃋�[�v�𑖂点�邱�Ƃ��ł��܂��D
```
>>> import time
>>> for i in range(0,500):
>>>   y  = solid1.GetPose().getPos().y
>>>   dy = solid1.GetVelocity().y
>>>   kp = 20.0
>>>   kd =  3.0
>>>   solid1.AddForce(Spr.Vec3d(0, (2.0 - y)*kp - dy*kd, 0))
>>>   time.sleep(0.01)
```
�����܂ł͍��݂̂̂ł������C�֐߂��쐬�ł��܂��D
```
>>> phScene = fwScene.GetPHScene()
>>> phSdk   = phScene.GetSdk()

>>> descSolid = Spr.PHSolidDesc()
>>> solid0 = phScene.CreateSolid(descSolid)
>>> descBox = Spr.CDBoxDesc()
>>> descBox.boxsize = Spr.Vec3f(1,1,1)
>>> boxifinfo = Spr.CDBox.GetIfInfoStatic()
>>> solid0.AddShape(phSdk.CreateShape(boxifinfo, descBox))
>>> solid0.SetDynamical(False)

>>> solid1 = phScene.CreateSolid(descSolid)
>>> solid1.AddShape(phSdk.CreateShape(boxifinfo, descBox))

>>> descJoint = Spr.PHHingeJointDesc()
>>> descJoint.poseSocket = Spr.Posed(1,0,0,0, 0,-1,0)
>>> descJoint.posePlug   = Spr.Posed(1,0,0,0, 0, 1,0)
>>> hingeifinfo = Spr.PHHingeJoint.GetIfInfoStatic()
>>> joint = phScene.CreateJoint(solid0, solid1, hingeifinfo, descJoint)
```
PythonSpr.exe�Ɉ�����^����ƁCpython�t�@�C����ǂݍ���Ŏ��s���邱�Ƃ��ł��܂��D�����܂łɏ��������e�� *test.py* �Ƃ����t�@�C���ɏ����ĕۑ����C�R�}���h�v�����v�g����ȉ��̂悤�Ɏ��s����ƁCtest.py�ɏ��������e�����s����܂��i�X�y�[�X�L�[�������܂ŃV�~�����[�V�����͊J�n����Ȃ����Ƃɒ��ӂ��Ă��������j�D
```
C:\src\Samples\EmbPython\PythonSpr> Release\PythonSpr.exe test.py
>>>
```

#### Python�C���^�v���^�g�ݍ��݂̂��߂̃R�[�h��
PythonSpr�T���v���ɂ����āCPython�C���^�v���^��g�ݍ��ނ��߂̃R�[�h�ɂ��ďЉ�܂��D\begin{tips}Python�C���^�v���^�g�ݍ��݂̏ڍׂ𗝉����邽�߂ɂ�Springhead�����łȂ�Python��C����API�ɂ��Ēm��K�v������܂��D�ڂ����m�肽������Python/C API���t�@�����X�}�j���A��$^{*1}$�����Q�Ƃ��Ă��������D{\footnotesize *1 ... `http://docs.python.org/py3k/c-api/index.html`}\end{tips}PythonSpr�T���v���ɂ����āCPython�g�ݍ��݂̂��߂̃R�[�h�� *main.cpp* �ɋL�q����Ă��܂��D�֘A�ӏ��𔲐����ďЉ�܂��DPython�g�ݍ��݊֘A�̋@�\���g�p����ɂ́C*EmbPython.h* �w�b�_���C���N���[�h���܂��D
```
#include <EmbPython/EmbPython.h>
```
Python�C���^�v���^�́CSpringhead�A�v���P�[�V�����{�̂Ƃ͈قȂ�X���b�h�œ��삵�܂��D�����V�~�����[�V�����X�e�b�v�̎��s����`��̍Œ���Python���f�[�^�����������Ă��܂����Ƃ��Ȃ��悤�C�r�����b�N�������ĕی삵�܂��D
```
virtual void OnStep(){
  UTAutoLock critical(EPCriticalSection);
  ...
}
virtual void OnDraw(GRRenderIf* render) {
  UTAutoLock critical(EPCriticalSection);
  ...
}
virtual void OnAction(int menu, int id){
  UTAutoLock critical(EPCriticalSection);
  ...
}
```
*EPCriticalSection*�̓A�v���P�[�V�����Ɉ�������݂��Ȃ��C���X�^���X�ŁC*EPCriticalSection*�ɂ��r�����b�N���擾�ł���̂͑S�A�v���P�[�V�������ň�̃X�R�[�v�݂̂ł��DPython����Springhead�̋@�\���Ăяo�����ۂɂ͕K��*EPCriticalSection*�̎擾��҂悤�ɂȂ��Ă���̂ŁC�r�����b�N���擾����*OnStep*�̎��s����Python��Springhead�̋@�\�����s���邱�Ƃ͂���܂���\footnote{�i�C�[�u�Ȏ����̂��ߏ��X�ߏ�ȃ��b�N�ƂȂ��Ă��܂��D���ۂ̋������\�[�X�ɍ��������r�����䂪�ł���悤�C�����̃o�[�W�����ŕύX���Ȃ����\��������܂��D}�D���ɁCPython�C���^�v���^�������p�̊֐����`���܂��D
```
void EPLoopInit(void* arg) {
  PythonSprApp* app = (PythonSprApp*)arg;

  // Python�Ń��W���[���̎g�p�錾
  PyRun_SimpleString("import Spr");
        
  // Python����C�̕ϐ��ɃA�N�Z�X�\�ɂ��鏀��
  PyObject *m = PyImport_AddModule("__main__");
  PyObject *dict = PyModule_GetDict(m);

  // Python����fwScene�ɃA�N�Z�X�\�ɂ���
  PyObject* pyObj = (PyObject*)newEPFWSceneIf(app->fwScene);
  Py_INCREF(pyObj);
  PyDict_SetItemString(dict, "fwScene", pyObj);

  // Python�t�@�C�������[�h���Ď��s����
  if (app->argc == 2) {
    ostringstream loadfile;
    loadfile << "__mainfilename__ ='";
    loadfile << app->argv[1];
    loadfile << "'";
    PyRun_SimpleString("import codecs");
    PyRun_SimpleString(loadfile.str().c_str());
    PyRun_SimpleString(
      "__mainfile__ = codecs.open(__mainfilename__,'r','utf-8')");
    PyRun_SimpleString(
      "exec(compile( __mainfile__.read() , __mainfilename__, 'exec')"
      ",globals()"
      ",locals())" );
    PyRun_SimpleString("__mainfile__.close()");
  }
}
```
���̊֐��͊֐��|�C���^�̌`�ŃC���^�v���^�I�u�W�F�N�g�ɓn����C���s�J�n���ɃR�[���o�b�N����܂��D���g��Python���Springhead���g�p�\�ɂ��邽�߂̎葱���ƁCC��̕ϐ����u���b�W���邽�߂̃R�[�h�C�����ċN�����Ɏw�肳�ꂽ.py�t�@�C�������[�h����R�[�h�Ȃǂł��D��̗�ł�*app->fwScene*�݂̂�Python�ɓn���Ă��܂����C���ɂ��󂯓n�������ϐ��������o�Ă����ꍇ�́C�ȉ��̂悤�ȃ}�N�����֗��ł��傤�D
```
#define ACCESS_SPR_FROM_PY(cls, name, obj)           \
{                                                    \
    PyObject* pyObj = (PyObject*)newEP##cls((obj));  \
    Py_INCREF(pyObj);                                \
    PyDict_SetItemString(dict, #name, pyObj);        \
}                                                    \

// �g����:
// ACCESS_SPR_FROM_PY(�^��, Python���ł̕ϐ���, �A�N�Z�X����ϐ�)
ACCESS_SPR_FROM_PY(FWSceneIf, fwScene, app->fwScene);
```
���ۂ�PythonSpr�T���v���ł́C���̃}�N����p���Ă������̕ϐ���Python����Ăяo����悤�ɂ��Ă��܂��D���[�v�֐�����`���܂��D����ɂ��Ă͕ύX���邱�Ƃ͋H�ł��傤�D
```
void EPLoop(void* arg) {
	PyRun_InteractiveLoop(stdin,"SpringheadPython Console");
}
```
�Ō�ɁC*main*�֐�����Python�C���^�v���^�N���X�ł���*EPInterpreter*���쐬���ăR�[���o�b�N��ݒ肵�C�������E���s���s���܂��D
```
int main(int argc, char *argv[]) {
  app.Init(argc, argv);

  EPInterpreter* interpreter = EPInterpreter::Create();
  interpreter->Initialize();
  interpreter->EPLoopInit = EPLoopInit;
  interpreter->EPLoop = EPLoop;
  interpreter->Run(&app);

  app.StartMainLoop();
  return 0;
}
```

### Python�ւ�Springhead�g����
Python��DLL�C���|�[�g�@�\�𗘗p����Springhead��Python�Ƀ��[�h���ėp���邱�Ƃ��ł��܂��DSpringhead�̋@�\��*Spr.pyd*�Ƃ���DLL�t�@�C���ɂ܂Ƃ߂��Ă��܂��D*Spr.pyd*�́C`bin\win32\Spr.pyd`�܂���`bin\win64\Spr.pyd`�Ƃ���Springhead�����[�X�Ɋ܂܂�Ă��܂����C`src\EmbPython\SprPythonDLL.sln`���r���h���Đ������邱�Ƃ��ł��܂��D
#### *Spr.pyd*�̎g����
*Spr.pyd* �́CPython�̃C���X�g�[���t�H���_���ɂ���*DLLs*�t�H���_�ɃR�s�[���ėp���܂��Dimport�Ń��[�h���܂��D
```
Python 3.2.2 [MSC v.1500 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> import Spr
```
Springhead�A�v���P�[�V�����ɑg�ݍ��ޏꍇ�ƈႢ�C���[�h���_�ł͉��̃I�u�W�F�N�g����������Ă��܂���D�܂�*PHSdk*�𐶐����C����*PHScene*�𐶐����邱�ƂŁC*PHSolid*�������ł���悤�ɂȂ�܂��D
```
>>> phSdk = Spr.PHSdk.CreateSdk()
>>> phScene = phSdk.CreateScene(Spr.PHSceneDesc())
>>> solid0 = phScene.CreateSolid(Spr.PHSolidDesc())
>>> for i in range(0,10):
...     print(solid0.GetPose().getPos())
...     phScene.Step()
... 
Vec3d(0.000,0.000,0.000)
Vec3d(0.000,-0.000,0.000)
Vec3d(0.000,-0.001,0.000)
...(����)...
Vec3d(0.000,-0.011,0.000)
>>>
```
API�̌Ăяo������Springhead�A�v���P�[�V�����g�ݍ��݂̏ꍇ�ƕς��܂���D�������C���̏�Ԃł̓O���t�B�N�X�\�����g���Ȃ����ߏo�͂̓e�L�X�g��t�@�C���Ɍ����܂��D�O���t�B�N�X�\�����g�����߂ɂ́Cpyopengl���̕`�惉�C�u�����Ƒg�ݍ��킹��R�[�h�������K�v������܂��D
#### ���p��
*Spr.pyd*�̉��p��̈��SprBlender������܂��D

\epsopt{epsprblender}{width=0.5\hsize}

SprBlender�́C3DCG�\�t�gBlender�Ƀ��[�h���邱�Ƃ�Springhead���g�p�\�ɂ���g���@�\�ŁCSpringhead�J���`�[���ɂ���Č����ɊJ������Ă��܂��DBlender��UI�@�\�̑唼��Python�ŋL�q����Ă���C���J���ꂽPython API��ʂ��Ċe��̋@�\�𗘗p���邱�Ƃ��ł��܂��D�����ŁCBlender���Python��*Spr.pyd*�����[�h���CBlender���CG�I�u�W�F�N�g��Springhead�ŃV�~�����[�V�����ł���悤�ɏ����ꂽPython�X�N���v�g��SprBlender�ł��D�ڂ�����Web�T�C�g\footnote{`http://springhead.info/wiki/SprBlender`}���Q�Ƃ��Ă��������D
## Python�����Springhead API�g�p�@
Python����Springhead API���Ăяo���ۂ̏ڍׂȕ��@�Ƃ������̒��ӓ_�ɂ��ĉ�����܂��D
#### Spr���W���[���ɂ���
Springhead�̑S�N���X��*Spr*���W���[���Ƀp�b�P�[�W����Ă��܂��D
```
import Spr
```
���s�����ƂŎg�p�\�ƂȂ�܂��iSpringhead�A�v���P�[�V�����ɑg�ݍ��ޏꍇ��*EPLoopInit*�̒��ŃC���|�[�g�����s���܂��j�DSpringhead�Ɋ֘A����N���X�͑S��Spr���W���[���̒����ɒ�`����܂��DSpringhead�̃C���^�t�F�[�X�N���X�̓N���X������If�����������(******If*��*******)�C�x�N�g����N�H�[�^�j�I�����͂��̂܂܂̃N���X���Œ�`����Ă��܂��D�����_�ł́C���ׂĂ�Springhead�N���X��Python����̗��p�ɑΉ����Ă���킯�ł͂���܂���DPython���痘�p�ł���Springhead�N���X�́C*dir*�֐��Ŋm�F�ł��܂��D
```
>>> import Spr
>>> dir(Spr)
```

#### �I�u�W�F�N�g�̐���
C++��Springhead�𗘗p����ꍇ�Ɠ��l�C�܂���Sdk���쐬����K�v������܂��DSdk���쐬����ɂ́CPHSdk�N���X�̃C���X�^���X����*CreateSdk*���Ăяo���K�v������܂��D
```
phSdk = Spr.PHSdk().CreateSdk()
grSdk = Spr.GRSdk().CreateSdk()
# ... etc.
```
�V�[����Create��Springhead���lsdk�̃C���X�^���X����s���܂��D
```
phScene = phSdk.CreateScene(Spr.PHSceneDesc())
grScene = grSdk.CreateScene(Spr.GRSceneDesc())
# ... etc.
```

#### IfInfo�C�����_�E���L���X�g
�I�u�W�F�N�g��Create����API�̒��ɂ́C�����n���f�B�X�N���v�^�̌^�ɂ���Đ�������I�u�W�F�N�g�̎�ނ𔻕ʂ�����̂�����܂��D�Ⴆ��*PHScene::CreateJoint*�́C*PHHingeJointDesc*��n���ƃq���W�W���C���g�𐶐����C*PHBallJointDesc*��n���ƃ{�[���W���C���g�𐶐����܂��D������Create�֐���Python���痘�p����ꍇ�C�f�B�X�N���v�^�̌^�𔻕ʂ���@�\�͌����_�ł͗p�ӂ���Ă��Ȃ����߁C�����������I�u�W�F�N�g�̌^�ɑΉ�����IfInfo�I�u�W�F�N�g�𓯎��Ɉ����ɓn���܂��D
```
# Hinge
phScene.CreateJoint(so1,so2, Spr.PHHingeJoint.GetIfInfoStatic(), desc)

# Ball
phScene.CreateJoint(so1,so2, Spr.PHBallJoint.GetIfInfoStatic(),  desc)
``` 
IfInfo�I�u�W�F�N�g��*�N���X��.GetIfInfoStatic()*�Ŏ擾���邱�Ƃ��ł��܂��D��萳�m�ɂ́C�f�B�X�N���v�^�^�ɂ���ĕԂ��I�u�W�F�N�g��ς���悤��Create�֐��́C�ȉ��̂悤��API�w�b�_�t�@�C���ɂ����ăe���v���[�g��p���ċL�q����Ă��܂��DPython API�ł́C��e���v���[�g�ł�Create�֐��݂̂��|�[�g����Ă��邽�߁C*IfInfo* ii* �ɑ�������������K�v�ɂȂ�܂��D
```
// in SprPHScene.h
PHJointIf* CreateJoint(PHSolidIf* lhs, PHSolidIf* rhs,
  const IfInfo* ii, const PHJointDesc& desc);

template <class T> PHJointIf* CreateJoint
(PHSolidIf* lhs, PHSolidIf* rhs, const T& desc){
  return CreateJoint(lhs, rhs, T::GetIfInfo(), desc);
}
```
�Ȃ��C������ނ̃N���X�̃I�u�W�F�N�g��Ԃ�����API�֐��̏ꍇ�CC++�ł͋��ʂ���X�[�p�[�N���X(�֐߂Ȃ�*PHJointIf*�Ȃ�)���Ԃ邽�ߎ�����*DCAST*����p���ă_�E���L���X�g����K�v������܂����CPython�ɂ����Ă͂͂��߂���X�̃N���X(*PHHingeJoint*, *PHBallJoint*�Ȃ�)�̌^�������悤�Ɏ����I�Ƀ_�E���L���X�g���ꂽ���̂��Ԃ���܂��D����āC���[�U���ӎ����ă_�E���L���X�g����K�v�͂���܂���D
#### enum�̈���
*PHSceneIf::SetContactMode*�̂悤�ɁCenum�^�������ɂƂ�֐�������܂��D�c�O�Ȃ���C�����_�ł�enum�̒�`��Python�փ|�[�g����Ă��܂���D�����̊֐����Ăяo���ꍇ�́C�Ή����鐮���l��n���Ă��������D
```
# C++�ł� phScene->SetContactMode(so1, so2, PHSceneDesc::MODE_NONE) �Ɠ���
phScene.SetContactMode(so1, so2, 0)
```

#### �x�N�g���C�|�[�Y
*Vec3d*�C*Quaterniond*�C*Posed*����Springhead�Ɠ����N���X���Ŏg�p�ł��܂��D�e�v�f�� *.x* *.y* ���̃v���p�e�B�ɂ��A�N�Z�X�ł��C�l�̕ύX���\�ł��D
```
>>> v = Spr.Vec3d(1,2,3)
>>> v
(1.000,2.000,3.000)
>>> v.x
1.0
>>> v.x = 4.0
>>> v
(4.000,2.000,3.000)
```
*Posed*, *Posef*�ɂ��ẮC*w, x, y, z*�v���p�e�B���N�H�[�^�j�I�������C*px, py, pz*�v���p�e�B���x�N�g�������ւ̃A�N�Z�X�ƂȂ�܂��D�܂��C*Posed::Pos()*, *Posed::Ori()*�ɑΉ�����֐��Ƃ���

-  *.getOri()*
-  *.setOri()*
-  *.getPos()*
-  *.setPos()*

���p�ӂ���Ă��܂��D
