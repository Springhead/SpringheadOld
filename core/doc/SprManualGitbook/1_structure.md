
## �f�B���N�g���\��





\includegraphics[width=.6\hsize]{fig/filetree.eps}

\caption{Directory tree of Springhead}


Springhead�̃f�B���N�g���\����Fig.\,\ref{fig_filetree}�Ɏ����܂��D
## ���C�u�����\��
\begin{table}[t]\caption{Springhead modules}\begin{tabular}{lll}\toprule���W���[����			& �v���t�B�b�N�X	& �@�\	\\ \midrule{\bf Base}				& -					& �s��E�x�N�g�����Z�C�X�}�[�g�|�C���^�C\\						&					& ���̑���{�@�\	\\{\bf Foundation}		& UT				& Springhead�̊�{�N���X�C���s���^���	\\{\bf Collision}			& CD				& �Փ˔���	\\{\bf Physics}			& PH				& �����v�Z	\\{\bf Graphics}			& GR				& �V�[���O���t�C�`��	\\{\bf FileIO}			& FI				& �t�@�C�����o��	\\{\bf HumanInterface}	& HI				& �q���[�}���C���^�t�F�[�X�f�o�C�X�� \\						&					& �C���^���N�V���� \\{\bf Creature}			& CR				& �o�[�`�����N���[�`�� \\{\bf Framework}			& FW				& ���W���[���Ԃ̘A�g�� \\						&					& �A�v���P�[�V�����쐬�x�� \\ \bottomrule\end{tabular}\end{table}\begin{table}[t]\caption{Module dependencies}

\begin{tabular}{llllllllll}
\toprule
���W���[����			& 			&			&			&			&			&			&			&			&			\\ \midrule
{\bf Base}				& -			& -			& -			& -			& -			& -			& -			& -			& -			\\
{\bf Foundation}		& $\circ$	& -			& -			& -			& -			& -			& -			& -			& -			\\
{\bf Collision}			& $\circ$	& $\circ$	& -			& -			& -			& -			& -			& -			& -			\\
{\bf Physics}			& $\circ$	& $\circ$	& $\circ$	& -			& -			& -			& -			& -			& -			\\
{\bf Graphics}			& $\circ$	& $\circ$	& -			& -			& -			& -			& -			& -			& -			\\
{\bf FileIO}			& $\circ$	& $\circ$	& -			& -			& -			& -			& -			& -			& -			\\
{\bf HumanInterface}	& $\circ$	& $\circ$	& -			& -			& -			& -			& -			& -			& -			\\
{\bf Creature}			& $\circ$	& $\circ$	& -			& $\circ$	& -			& -			& -			& -			& -			\\
{\bf Framework}			& $\circ$	& $\circ$	& -			& $\circ$	& $\circ$	& $\circ$	& $\circ$	& -			& -			\\ \bottomrule
\end{tabular}

\end{table}Springhead�͕����̃��W���[������\������Ă��܂��DTable\,\ref{table_modules}�Ƀ��W���[���ꗗ�������܂��DTable\,\ref{table_dependency}�Ƀ��W���[���Ԃ̈ˑ��֌W�������܂��D�ʏ�C���[�U��Springhead���g�p����ɂ������Ă����̈ˑ��֌W��z�Ɉӎ�����K�v�͂���܂���D�܂��C���炩�̎����Springhead�̓���̋@�\�i���Ƃ��Ε����V�~�����[�V�����j�݂̂�p�������Ƃ����ꍇ�ɑΉ��ł���悤�ɁC���W���[���Ԃ̈ˑ��֌W�͂Ȃ�ׂ��a�ɂȂ�悤�ɐ݌v����Ă��܂��D���������Ă��̂悤�ȏꍇ�ɂ͗p�r�ɉ����ĕK�v�ȃ��W���[���݂̂��g����悤�ɂȂ��Ă��܂��D
## �N���X�EAPI�̖����K��
�e���W���[���Ɋ܂܂��N���X�̖��O�ɂ́CTable\,\ref{table_modules}�Ɏ������悤�ȃ��W���[���ŗL�̃v���t�B�b�N�X�����܂�(��: Physics���W���[����*PHSolid*�CCollision���W���[����*CDShape*)�D�ꕔ�ɂ͂��̃��[���ɂ�������Ȃ��N���X�����݂��܂�(��: Foundation���W���[����Object)�DAPI(�N���X�̃����o�֐�)�ɂ��ɂ������K��������܂��DAPI���͊�{�I��(���� + �ړI��)�Ƃ����`���ŏ������e��[�I�ɕ\�����܂��D�܂��C�P��̐擪�����̂ݑ啶���C���̑��͏������ŕ\�L���܂��D��Ƃ��Ă�*PHSolid::SetMass*�C*GRSdk::CreateScene*�Ȃǂł��D
## �C���^�t�F�[�X�ƃf�B�X�N���v�^
Springhead�ł͎d�l�Ǝ����𖾊m�ɕ������邽�߂ɁC�C���^�t�F�[�X�N���X�Ǝ����N���X���������Ă��܂��D���[�U�̓C���^�t�F�[�X�N���X�݂̂��g�p����Springhead�̋@�\�𗘗p���܂��D�������C`Base`��`Foundation`���W���[���ɂ��邲����{�I�ȃN���X�C�����`Framework`�̃A�v���P�[�V�����N���X�͗�O�ƂȂ��Ă��܂��D�܂��CSpringhead�̃N���X�ɂ͂��ꂼ��Ƀf�B�X�N���v�^���p�ӂ���Ă��܂��D�f�B�X�N���v�^�Ƃ́C���̃N���X�̓ǂݏ����\�ȑ����݂̂��W�߂��\���̂ł��D�f�B�X�N���v�^�𗘗p���邱�ƂŁC�����ݒ�̃C���X�^���X�𑽐��ݒ肷�邱�Ƃ��p�ӂɂȂ�܂��D�܂��C�f�B�X�N���v�^�̓t�@�C���ւ̃f�[�^�̕ۑ���ǂݍ��݂ɂ����Ă��𗧂��܂��D�ȉ���`Physics`���W���[���̍��̂�\��`PHSolid`�N���X���ɂƂ��Đ������܂��D
```
// given PHSolidIf* phScene, 

PHSolidDesc desc;
desc.mass = 1.0;

PHSolidIf* solid = phScene->CreateSolid(desc);
```
��̃R�[�h��`PHSolidDesc`��`PHSolid`�N���X�̃f�B�X�N���v�^�ł��D�܂����̃����o�ϐ�`mass`�ɒl���Z�b�g���邱�Ƃō��̂̎��ʂ�ݒ肵�Ă��܂��D���ɁC���̂��쐬���邽�߂�`CreateSolid`�֐����Ă΂�܂��D������`CreateSolid`�͕����V�[����\��`PHScene`�N���X�̃����o�֐��ł��D���ۂɂ�`PHScene`�N���X�̃C���^�t�F�[�X`PHSceneIf`���擾����K�v������܂����C�����ł͊��ɓ����Ă���Ƃ��Ă��܂��D���̂��쐬�����ƁC`CreateSolid`����C���^�t�F�[�X`PHSolidIf`�̃|�C���^���Ԃ���܂��D����ȍ~�̍��̂̑���͂��̃C���^�t�F�[�X����čs���܂��D
```
solid->SetMass(5.0);
```
��{�I�ɁC�f�B�X���v�^����Đݒ�\�ȑ����̓C���^�t�F�[�X��`Get/Set`�n�֐����g���Ď擾�C�ݒ肪�ł���悤�ɂȂ��Ă��܂��D�ꍇ�ɉ����ĕ֗��ȕ����g���Ă��������DSpringhead�I�u�W�F�N�g�͂��ׂē����Ń������Ǘ�����Ă��܂��̂ŁC���[�U�������I��`delete`����K�v�͂���܂���i�܂��C���Ă͂����܂���j�D`Create`���ꂽ�I�u�W�F�N�g�̓v���O�����̏I�����Ɏ����I�ɔj������܂��D
## ���ڂ����m�肽���l��
�ȍ~�̏͂ł͊e���W���[���ɂ��Ă��ڂ����������܂��DSpringhead�𗘗p�����ŁC���ׂẴ��W���[�����ڂ�����������K�v�͂���܂���D�K�v�ɉ����ĎQ�Ƃ��Ă��������D
