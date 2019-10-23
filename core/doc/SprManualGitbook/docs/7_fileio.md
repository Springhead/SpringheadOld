
## �T�v
FileIO�̓t�@�C�����o�͋@�\��񋟂��郂�W���[���ł��DFramework���痘�p����̂��ȒP�ł����A�P�̂ŗp����Ƃ��ׂ��ȍ�Ƃ��ł��܂��B
## FileIO SDK
FileIO���W���[���̂��ׂẴI�u�W�F�N�g��SDK�N���X*FISdk*�ɂ���ĊǗ�����܂��D*FISdk*�N���X�́C�v���O�����̎��s��ʂ��Ă����P�̃I�u�W�F�N�g�����݂���V���O���g���N���X�ł��D*FISdk*�I�u�W�F�N�g���쐬����ɂ͈ȉ��̂悤�ɂ��܂��D
```
FISdkIf* fiSdk = FISdkIf::CreateSdk();
```
�ʏ킱�̑���̓v���O�����̏��������Ɉ�x�������s���܂��D�܂��CFramework���W���[�����g�p����ꍇ�̓��[�U������*FISdk*���쐬����K�v�͂���܂���D*FISdk*�ɂ͈ȉ���2�̋@�\������܂��D

-  �t�@�C���I�u�W�F�N�g�̍쐬
-  �C���|�[�g�I�u�W�F�N�g�̍쐬






\includegraphics[width=.6\hsize]{fig/fifile.eps}

\caption{Class hierarchy of file objects}


�t�@�C���I�u�W�F�N�g�́C�t�@�C������̃V�[���̃��[�h����уZ�[�u��S���܂��D�t�@�C���̊��N���X��*FIFile*�ŁC�t�@�C���t�H�[�}�b�g�̎�ނ��Ƃɐ�p�̃t�@�C���N���X���h�����܂�(\Fig{fifile})�D�t�@�C���쐬�Ɋւ���*FISdk*�̊֐����ȉ��Ɏ����܂��D

\begin{tabular}{p{.3\hsize}p{.6\hsize}}
*FISdkIf*															\\ \midrule
*FIFileSprIf**		& *CreateFileSpr()*						\\
*FIFileBinaryIf** 	& *CreateFileBinary()*					\\
*FIFileXIf**			& *CreateFileX()*						\\
*FIFileVRMLIf**		& *CreateFileVRML()*						\\
*FIFileCOLLADAIf**	& *CreateFileCOLLADA()*					\\
*FIFileIf**			& *CreateFileFromExt(UTString filename)*	\\
\end{tabular}

*CreateFileFromExt*��*filename*�̊g���q����t�@�C���t�H�[�}�b�g�𔻕ʂ��đΉ�����t�@�C���I�u�W�F�N�g���쐬���܂��D
## �t�@�C���t�H�[�}�b�g
���̐߂ł�Springhead�Ń��[�h�E�Z�[�u�ł���t�@�C���̃t�@�C���t�H�[�}�b�g���Љ�܂��B
### spr�t�@�C��
�g���q .spr �̃t�@�C���́ASpringhead�Ǝ��̃t�@�C���`���ł��B�l���ǂݏ������₷���ASpringhead�̎d�l���ω����Ă��]��e�����󂯂Ȃ��悤�Ȍ`���ɂȂ��Ă��܂��B�t�@�C�����菑������ꍇ�͂��̌`�����g���Ă��������Bspr�t�@�C���̓m�[�h��`�̌J��Ԃ��ł��Bspr�t�@�C���̗�������܂��B
```
PHSdk{                  #PHSdk�m�[�h
    CDSphere sphere{    #���̎q�m�[�h��CDSphere�m�[�h��ǉ�
        material = {    # CDSphere �� material(PHMaterial�^)��
            mu = 0.2    # ���C�W�� mu ��0.2����
        }
        radius = 0.5    # radius��0.5����
    }
    CDBox bigBox{
        boxsize = 2.0 1.1 0.9
    }
}
```
Spr�t�@�C���̃m�[�h�̓f�B�X�N���v�^�i\SECTION{if_desc})���Q�Ɓj�ɂP�΂P�őΉ����܂��B�f�B�X�N���v�^�����p�ӂ���Ύ����I�Ɏg����m�[�h�̌^�������܂��B�t�@�C���Œl�������Ȃ��ƁA�f�B�X�N���v�^�̏����l�ɂȂ�܂��B��̗�ł́A*PHSdk*�ɒǉ������*sphere*(*CDSphere*�^)�́A
```
CDSphereDesc desc;
desc.material.mu = 0.2;
desc.radius = 0.5;
```
�Ƃ����f�B�X�N���v�^ *desc* �ō��̂Ɠ������ƂɂȂ�܂��BSpr�t�@�C���̕��@��BNF�{���K�\���ŏ�����
```
spr   = node*
node  = node type, (node id)?, block
block = '{' (node|refer|data)*  '}'
refer = '*' node id
data  = field id, '=', (block | right)
right = '[' value*, ']' | value
value = bool | int | real | str | right
```
�ƂȂ�܂��B*right*�ȍ~�̉��߂�*field*�̌^�Ɉˑ����܂��B
### X�t�@�C��
�u X �t�@�C�� �v�́ADirect3D�̃t�@�C���t�H�[�}�b�g�ŁA�g���q�� .x �ł��B���f�����O�\�t�gXSI�Ŏg���Ă���A�����̃��f�����O�c�[���ŏo�͂ł��܂��B3D�̌`��f�[�^�A�}�e���A���A�e�N�X�`���A�{�[���Ȃǂ��܂߂邱�Ƃ��ł��܂��BSpringhead2�ł́A�W���I��X�t�@�C���̃��[�h�ƁASpringhead2�Ǝ��̃m�[�h�̃��[�h�ƃZ�[�u���ł��܂��B�������Ǝ��m�[�h���菑������ꍇ�� Spr�t�@�C���̕��������₷���֗��ł��̂ł�����̎g�p���������߂��܂��BX�t�@�C���̗�������܂��B
```
xof 0302txt 0064        #�ŏ��̍s�͂��ꂩ��n�܂�

#    �m�[�h�́C
#        �^���C�m�[�h�� { �t�B�[���h�̌J��Ԃ�   �q�m�[�h }
#    ����Ȃ�D
PHScene scene1{
    0.01;0;;            #�t�B�[���h �� �l; �̌J��Ԃ�
    1;0;-9.8;0;;        #�l�� ���l�C������܂��̓t�B�[���h
    PHSolid soFloor{    #�q�m�[�h�́C�m�[�h�Ɠ���
        (�ȗ�)
    }
}
# �R�����g�� #�ȊO�� // ���g����
```

#### �Ǝ��m�[�h�̒�`
Springhead2 �̒ʏ�̃m�[�h�́C�I�u�W�F�N�g�̃f�B�X�N���v�^�i\SECTION{if_desc}�߁j�ɂP�΂P�őΉ����܂��D���[�h���ɂ́C�f�B�X�N���v�^�ɑΉ�����I�u�W�F�N�g����������C�V�[���O���t�ɒǉ�����܂��D�Z�[�u���ɂ́C�I�u�W�F�N�g����f�B�X�N���v�^��ǂݏo���C�m�[�h�̌`���Ńt�@�C���ɕۑ�����܂��D�I�u�W�F�N�g�̃f�B�X�N���v�^�ɂ́C�K���Ή�����m�[�h������܂��D�Ⴆ�΁C*SprPHScene.h* �ɂ́C
```
struct PHSceneState{
    double timeStep;      ///< �ϕ��X�e�b�v
    unsigned count;       ///< �ϕ�������
};
struct PHSceneDesc:PHSceneState{
    /// �ڐG�E�S�������G���W���̎��
    enum ContactMode{ MODE_NONE, MODE_PENALTY, MODE_LCP};
    Vec3f gravity;      ///< �d�͉����x�x�N�g���D�f�t�H���g�l��(0.0f, -9.8f,0.0f)�D
};
```
�̂悤�ɁC�X�e�[�g�ƃf�B�X�N���v�^���錾����Ă��܂��D���� *PHSceneDesc* �ɑΉ����� X �t�@�C���̃m�[�h�́C
```
PHScene scene1{                                                                     0.01;     #PHSceneState::timeStep
    0;;       #PHSceneState::count     �Ō��;��PHSceneState���̏I���������D
    1;        #PHSceneDesc::ContactMode
    0;-9.8;0;;#PHSceneDesc::gravity    �Ō��;��PHSceneDesc���̏I���������D
}
```
�̂悤�ɂȂ�܂��D�N���X�̃����o�ϐ������̂܂܃t�B�[���h�ɂȂ�܂��D�܂��C��{�N���X�́C�擪�Ƀt�B�[���h���ǉ����ꂽ�`�ɂȂ�܂��D�ʏ�m�[�h�̈ꗗ�� \URL{TBU: �f�X�N���v�^�ꗗ�̃y�[�W} ���Q�Ɖ������D
#### X�t�@�C���̃m�[�h
Springhead2�̓Ǝ��m�[�h�����łȂ��A���ʂ�X�t�@�C���̃m�[�h�����[�h�ł��܂��BX�t�@�C���ɂ́A
```
Frame{
    FrameTransfromMatrix{ 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1; }
}
```
�̂悤�ȃt���[���̃m�[�h�^������܂����ASprinhead2 �ɂ͑Ή�����f�B�X�N���v�^��I�u�W�F�N�g������܂���D�����ŁC�����́A*GRFrame*��*PHFrame*�ɕϊ�����ă��[�h����܂��D\URL{TBW �m�[�h�ꗗ�̃y�[�W(pageNodeDefList)} ���Q�Ɖ������D
## �t�@�C���̃��[�h�E�Z�[�u





\includegraphics*[width=.95\hsize]{fig/fileOperation.eps}

\caption{Overview of file operation}


\Fig{fileOperation}�́A�t�@�C���̃��[�h�E�Z�[�u�̎菇�������Ă��܂��B���[�h���ɂ͂܂��t�@�C�����p�[�X���ăf�B�X�N���v�^�̃c���[�����܂��B���Ƀf�B�X�N���v�^�̃c���[�����ǂ�Ȃ���A�I�u�W�F�N�g�̃c���[�����܂��B����A�Z�[�u���ɂ́A�f�B�X�N���v�^�c���[�͍��܂���B�I�u�W�F�N�g�c���[�����ǂ�Ȃ���I�u�W�F�N�g����f�B�X�N���v�^�����A���̏�Ńt�@�C���ɏ��������Ă����܂��B�t�@�C���̃m�[�h�ƃf�B�X�N���v�^�c���[�̃m�[�h�͂P�΂P�ɑΉ����܂����A�I�u�W�F�N�g�̃c���[�ł͂����Ƃ͌���܂���B
### �t�@�C�����[�h�̎d�g��

#### �t�@�C���̃p�[�X
�t�@�C���̃��[�h�́A*FIFileSpr*��*FIFileX*�̂悤��*FIFile*�̔h���N���X��*LoadImp()*���\�b�h���s���܂��B�t�@�C���p�[�X�̎����́Aboost::spirit��p���Ď�������Ă��܂��B*Init()*���\�b�h�Ńp�[�T�̕��@���`���Ă��܂��B
#### �f�B�X�N���v�^�̐���
�p�[�T��*FILoadContext*���R���e�L�X�g�Ƃ��ėp���Ȃ���p�[�X��i�߂܂��B*fieldIts*�Ƀ��[�h���̃f�[�^�̌^�����Z�b�g���Ă����܂��B�m�[�h���⃁���o������f�B�X�N���v�^�⃁���o�̌^��m��K�v������܂����A�r���h����SWIG�Ő������Ă���f�B�X�N���v�^�̌^����*??Sdk::RegisterSdk()*���o�^�������̂�p���Ă��܂��B�V�����m�[�h���o�Ă���x��*FILoadContext::datas*�Ƀf�B�X�N���v�^��p�ӂ��A�f�[�^�����[�h����Ƃ����ɒl���Z�b�g���Ă����܂��B���̃m�[�h�ւ̎Q�Ƃ́A���̎��_�ł̓m�[�h���̕�����ŋL�^���Ă����܂��B
#### �Q�Ƃ̃����N
�t�@�C�������ׂă��[�h���I���ƁA*LoadImp()*���甲���āA*FIFile::Load(FILoadContext*)*�ɖ߂��Ă��܂��B���̃m�[�h(���̃f�B�X�N���v�^)�ւ̎Q�Ƃ��m�[�h���̕�����𗊂�Ƀ|�C���^�łȂ��ł����܂��B
#### �I�u�W�F�N�g�̐���
�I�u�W�F�N�g�����́A*FILoadContext::CreateScene()*���A�f�B�X�N���v�^�c���[�����{���炽�ǂ�Ȃ��珇�ɍs���܂��B�f�B�X�N���v�^����I�u�W�F�N�g�𐶐�����̂́A���̃I�u�W�F�N�g�̐�c�I�u�W�F�N�g�ł��B��c�I�u�W�F�N�g�������ł��Ȃ��ꍇ��SDK�̐��������݂܂��BSDK�ȊO����ԍ��{�ɂ���t�@�C�������[�h���邽�߂ɂ́A�\�ߐ�c�I�u�W�F�N�g��p�ӂ��Ă����K�v������܂��B*FIFile::Load(ObjectIfs\& objs, const char* fn)*��*objs*�����͂��̖��������܂��B�������ꂽ�I�u�W�F�N�g�́A�e��*AddChildObject()*�ł����Ɏq�Ƃ��Ēǉ�����܂��B
#### �Q�Ƃ̃����N
�f�B�X�N���v�^�Ԃ̎Q�Ƃ̓|�C���^�ɂȂ��Ă��܂����A�V�[���O���t�͌q�����Ă��܂���B�f�B�X�N���v�^�̎Q�Ƃɏ]���āA�f�B�X�N���v�^���琶�����ꂽ�I�u�W�F�N�g�ԂɎQ�Ƃ�ǉ����܂��B�����N�́A*AddChildObject()*�֐����Ăяo�����Ƃōs���܂��B�e�q�ƎQ�Ƃ̋�ʂ͂��Ȃ��Ȃ�܂��B����m�[�h�̉��Ɏq�m�[�h�������Ă��A�ʂ̂Ƃ���ɏ������m�[�h�ւ̎Q�Ƃ������Ă������V�[�O���t�ɂȂ�킯�ł��B
### �t�@�C�����[�h�̎���
Framework���g���̂ƊȒP�ł��B
```
virtual void FWMyApp::Init(int argc, char* argv[]){
    UTRef<ImportIf> import = GetSdk()->GetFISdk()->CreateImport();
    GetSdk()->LoadScene(fileName, import);  // �t�@�C���̃��[�h
    GetSdk()->SaveScene("save.spr", import);// �t�@�C���̃Z�[�u�e�X�g
```
FISdk�P�̂Ŏg���ꍇ�͎��̂悤�ɂȂ�܂��B
```
int main(){
    //  �t�@�C�����[�_�Ő����ł���悤�ɁA�eSDK�̌^����o�^
    PHSdkIf::RegisterSdk();
    GRSdkIf::RegisterSdk();
    FWSdkIf::RegisterSdk();
    //  �t�@�C���̃��[�h
    UTRef<FISdkIf> fiSdk = FISdkIf::CreateSdk();
    FIFileIf* file = fiSdk->CreateFileFromExt(".spr");
    ObjectIfs objs; //  ���[�h�p�I�u�W�F�N�g�X�^�b�N
    fwSdk = FWSdkIf::CreateSdk();   //  FWSDK��p��
    //  �q�I�u�W�F�N�g�쐬�p��fwSdk���X�^�b�N�ɐς�
    objs.push_back(fwSdk);
    //  FWSDK�ȉ��S�̂��t�@�C�����烍�[�h
    if (! file->Load(objs, "test.spr") ) {  
        DSTR << "Error: Cannot open load file. " << std::endl;
        exit(-1);
    }
    //  �t�@�C�����̃��[�g�m�[�h�i�����̉\������j��objs�ɐς܂��B
    for(unsigned  i=0; i<objs.size(); ++i){ 
        objs[i]->Print(DSTR);
    }
    ...
```

### �t�@�C���Z�[�u�̎d�g��
�t�@�C���Z�[�u�́A*FIFile*���V�[���O���t�����ǂ�Ȃ���A�I�u�W�F�N�g���Z�[�u���Ă����܂��B�e�I�u�W�F�N�g��*GetDescAddress()*���A��������Ă��Ȃ����*GetDesc()*���Ăяo���ăf�B�X�N���v�^��ǂݏo���܂��B�V�[���O���t�ɂ́A����m�[�h�������̃m�[�h�̎q�m�[�h�ɂȂ��Ă���ꍇ�����邽�߁A2�d�ɃZ�[�u���Ȃ��悤��2�x�ڈȍ~�͎Q�ƂƂ��ăZ�[�u���܂��B�f�B�X�N���v�^�����o������A�f�B�X�N���v�^�̌^���𗘗p���āA�f�B�X�N���v�^�̃����o�����ԂɃZ�[�u���Ă����܂��B���ۂɃf�[�^���t�@�C���ɕۑ�����R�[�h�́A*FiFileSpr*�Ȃ�*FiFile*�̔h���N���X�ɂ���܂��B
### �t�@�C���Z�[�u�̎���
Framework���g���̂ƊȒP�ł��B
```
virtual void FWMyApp::Save(const char* filename){
    UTRef<ImportIf> import = GetSdk()->GetFISdk()->CreateImport();
    GetSdk()->SaveScene(filename, import);	// filename�ɃV�[�����Z�[�u
```
FISdk�P�̂Ŏg���ꍇ�͎��̂悤�ɂȂ�܂��B
```
void save(const char* filename, ImportIf* ex, ObjectIf* rootNode){
    //  �t�@�C���̃Z�[�u
    UTRef<FISdkIf> fiSdk = FISdkIf::CreateSdk();
    FIFileIf* file = fiSdk->CreateFileFromExt(".spr");
    ObjectIfs objs; //  ���[�h�p�I�u�W�F�N�g�X�^�b�N
    objs.push_back(rootNode);
    file->SetImport(ex);
    file->Save(*objs, filename);
}
```

## �C���|�[�g���̊Ǘ�
T.B.W.�iImport���g���ƕʂ̃t�@�C���ɏ������m�[�h���Ăяo�����Ƃ��ł���BImport���g���ă��[�h�����V�[�����Z�[�u�ꍇ�A�t�@�C���ۑ����ɂǂ��܂ł��t�@�C���ɕۑ�����̂������ɂȂ�B������Ǘ�����̂�Import�̖������Ǝv���Bby ���J��)
