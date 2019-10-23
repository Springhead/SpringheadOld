
## �T�v
Physics���W���[���͕����V�~�����[�V�����@�\��񋟂��܂��D��ɃT�|�[�g����Ă���̂́C�}���`�{�f�B�_�C�i�~�N�X�ƌĂ΂�鍄�̂Ɗ֐߂Ȃǂ̍S������Ȃ铮�͊w�V�~�����[�V�����ł��D���̂Ƃ���\�t�g�{�f�B�◬�́C�p�[�e�B�N���Ȃǂ̋@�\�̓T�|�[�g����Ă��܂���D
## Physics SDK
Physics���W���[���̂��ׂẴI�u�W�F�N�g��SDK�N���X*PHSdk*�ɂ���ĊǗ�����܂��D*PHSdk*�N���X�́C�v���O�����̎��s��ʂ��Ă����P�̃I�u�W�F�N�g�����݂���V���O���g���N���X�ł��D*PHSdk*�I�u�W�F�N�g���쐬����ɂ͈ȉ��̂悤�ɂ��܂��D
```
PHSdkIf* phSdk = PHSdkIf::CreateSdk();
```
�ʏ킱�̑���̓v���O�����̏��������Ɉ�x�������s���܂��D�܂��CFramework���W���[�����g�p����ꍇ�̓��[�U������*PHSdk*���쐬����K�v�͂���܂���D*PHSdk*�̋@�\�̓V�[���ƌ`��̊Ǘ��ł��D�V�[���Ɋւ���@�\�͎��߂Ő������܂��D�܂��C�`��Ɋւ���@�\�͈ȉ��̒ʂ�ł��D

\begin{tabular}{p{.15\hsize}p{.55\hsize}p{.2\hsize}}
*PHSdkIf* & &															\\ \midrule
*CDShapeIf** & *CreateShape(const CDShapeDesc\&)*	& �`����쐬	\\
*CDShapeIf**	& *GetShape(int)*					& �`����擾	\\
*int*		& *NShape()*							& �`��̐�		\\
\end{tabular}

�قȂ�V�[���ԂŌ`������L�ł���悤�ɁC�`��Ǘ��̓V�[���ł͂Ȃ�*PHSdk*�̋@�\�ɂȂ��Ă��܂��D�ڂ�����\ref{chap_collision}�͂��Q�Ƃ��Ă��������D
## �V�[��
�V�[���͕����V�~�����[�V�������s������\���܂��D�����̃V�[�����쐬�ł��܂����C�V�[�����m�݂͌��ɓƗ����Ă���C���[�U�����ڋ��n�����������Ȃ�����͉e�����y�ڂ��������Ƃ͂���܂���D�V�[���N���X��*PHScene*�ŁC*PHScene*�I�u�W�F�N�g��*PHSdk*�ɂ��Ǘ�����܂��D

\begin{tabular}{p{.15\hsize}p{.55\hsize}p{.2\hsize}}
\multicolumn{3}{l}{*PHSdkIf*}															\\ \midrule
*PHSceneIf**	& *CreateScene(const PHSceneDesc\& desc)*			& �V�[�����쐬		\\
*int*		& *NScene()*											& �V�[���̐�		\\
*PHSceneIf**	& *GetScene(int i)*									& �V�[�����擾		\\
*void*		& *MergeScene(PHSceneIf* scene0, PHSceneIf* scene1)*	& �V�[���𓝍�		\\
\end{tabular}

�V�[�����쐬����ɂ͈ȉ��̂悤�ɂ��܂��D
```
PHSceneIf* phScene = phSdk->CreateScene();
```
�����Ƀf�B�X�N���v�^���w�肷�邱�Ƃ��ł��܂��D*MergeScene*�́C*scene1*���ۗL����I�u�W�F�N�g�����ׂ�*scene0*�Ɉړ��������*scene1*���폜���܂��D�V�[���͍��̂�֐߂Ȃǂ̗l�X�ȍ\���v�f�̊Ǘ����s���ق��C�����V�~�����[�V�����Ɋւ���ݒ���s���@�\��񋟂��܂��D�e�\���v�f�̍쐬�ɂ��Ă͂��ꂼ��̐߂Ő������܂��̂ŁC�ȉ��ł̓V�~�����[�V�����ݒ�@�\�ɂ��ďq�ׂ܂��D

\begin{tabular}{p{.15\hsize}p{.35\hsize}p{.4\hsize}}
\multicolumn{3}{l}{*PHSceneDesc*}										\\ \midrule
*double*		&	*timeStep*	& ���ԃX�e�b�v��					\\
*unsigned*	&	*count*		& �V�~�����[�V���������X�e�b�v��	\\
*Vec3d*		&	*gravity*	& �d�͉����x						\\
*double*		&	*airResistanceRate*	& ��C��R�W��				\\
*int*		&	*numIteration*		& LCP�̔�����				\\
\end{tabular}



\begin{tabular}{p{.15\hsize}p{.55\hsize}p{.2\hsize}}
\multicolumn{3}{l}{*PHSceneIf*}							  \\ \midrule
*double*		& *GetTimeStep()*					& \\
*void*		& *SetTimeStep(double)*				& \\
*unsigned*	& *GetCount()*						& \\
*void*		& *SetCount(unsigned)*				& \\
*void*		& *SetGravity(const Vec3d\&)*		& \\
*Vec3d*		& *GetGravity()*						& \\
*void*		& *SetAirResistanceRate(double)*		& \\
*double*		& *GetAirResistanceRate()*			& \\
*int*		& *GetNumIteration()*				& \\
*void*		& *SetNumIteration()*				& \\
\end{tabular}

*timeStep*�͈�x�̃V�~�����[�V�����X�e�b�v�Ői�߂鎞�ԕ��ł��D�������قǃV�~�����[�V�����̐��x�͏オ��܂����C�������ԃV�~�����[�V������i�߂�̂ɂ�����v�Z�R�X�g�͑��債�܂��D*count*�̓V�[���쐬��ɃV�~�����[�V���������ݐσX�e�b�v���ł��D*count*��*timeStep*�̐ς��o�ߎ��Ԃ�\���܂��D*gravity*�͏d�͉����x�x�N�g���ł��D*airResistanceRate*�́C�V�~�����[�V�����̈��萫�����シ�邽�߂ɖ��X�e�b�v�Ɋe���̂̑��x�Ɋ|������W���ł��D�Ⴆ��*airRegistanceRate*��$0.95$�ł���΃X�e�b�v���Ƃɑ��x��$95$\%�ɂȂ�܂��D���̂悤�ɋ����I�Ɍ����������邱�ƂŁC���x���]���Ɉ��萫�𓾂邱�Ƃ��ł��܂��D*numIteration*�́C�S���͂��v�Z���邽�߂ɓ����Ŏ��s�����A���S���Y���̔����񐔂ł��D��ʂɁC�����񐔂Ɋւ��Ďw���֐��I�ɍS���͂̐��x�����サ�C�v�Z�R�X�g�͔��I�ɑ��債�܂��D
### �V�~�����[�V�����̎��s
�V�~�����[�V������$1$�X�e�b�v�i�߂�ɂ�*Step*�֐����Ăт܂��D

\begin{tabular}{p{.15\hsize}p{.3\hsize}p{.45\hsize}}
\multicolumn{3}{l}{*PHSceneIf*}		\\ \midrule
*void*	& *Step()*	& �V�~�����[�V������$1$�X�e�b�v�i�߂� \\
\end{tabular}

*Step*�����s����ƁC�����܂��ɏq�ׂē����Ŏ��̏������s���܂��D

-  �Փ˔���ƐڐG�S���̐���
-  �S���͂̌v�Z
-  ���̂̑��x����шʒu�̍X�V


## ����
���͕̂����V�~�����[�V�����̊�{�v�f�ł��D���̂̃N���X��*PHSolid*�ł��D�܂����̂��쐬�E�Ǘ����邽�߂�*PHScene*�̊֐��������܂��D

\begin{tabular}{p{.15\hsize}p{.45\hsize}p{.30\hsize}}
\multicolumn{3}{l}{*PHSceneIf*}									\\ \midrule
*PHSolidIf**		& *CreateSolid(const PHSolidDesc\&)*	& ���̂��쐬���� \\
*int*			& *NSolids()*						& ���̂̐� \\
*PHSolidIf*** 	& *GetSolids()*						& ���̔z��̐擪�A�h���X \\
\end{tabular}

���̂��쐬����ɂ�
```
PHSolidIf* solid = phScene->CreateSolid();
```
�Ƃ��܂��D�f�B�X�N���v�^���w�肵�č쐬���邱�Ƃ��ł��܂��D�܂��C*GetSolids*�͍쐬�������̂��i�[���������z��̐擪�A�h���X��Ԃ��܂��D���������āC�Ⴆ��$0$�Ԗڂ̍��̂��擾����ɂ�
```
PHSolidIf* solid = phScene->GetSolids()[0];      // get 0-th solid
```
�Ƃ��܂��D���ɍ��̎��g�̋@�\��������܂��D
### ����


\begin{tabular}{p{.15\hsize}p{.45\hsize}p{.30\hsize}}
\multicolumn{3}{l}{*PHSolidDesc*}							\\ \midrule
*double*		&	*mass*		& ����					\\
*Matrix3d*	&	*inertia*	& �����s��				\\
*Vec3d*		&	*center*		& ���ʒ��S				\\
*bool*		&	*dynamical*	& �����@���ɂ���������	\\
\end{tabular}



\begin{tabular}{p{.15\hsize}p{.45\hsize}p{.30\hsize}}
\multicolumn{3}{l}{*PHSolidIf*}								\\ \midrule
*double*		& *GetMass()*						& \\
*double* 	& *GetMassInv()*						& \\
*void* 		& *SetMass(double)*					& \\
*Vec3d* 		& *GetCenterOfMass()*				& \\
*void* 		& *SetCenterOfMass(const Vec3d\&)*	& \\
*Matrix3d* 	& *GetInertia()*						& \\
*Matrix3d* 	& *GetInertiaInv()*					& \\
*void* 		& *SetInertia(const Matrix3d\&)*		& \\
*void* 		& *CompInertia()*					& \\
*void* 		& *SetDynamical(bool)*				& \\
*bool* 		& *IsDynamical()*					& \\
\end{tabular}

*GetMassInv*��*GetInertiaInv*�͂��ꂼ�ꎿ�ʂ̋t���Ɗ����s��̋t�s���Ԃ��܂��D*CompInertia*�́C���̍��̂����`��Ƃ����̖��x�����Ƃɍ��̂̎��ʁC���ʒ��S�Ɗ����s����v�Z���C�ݒ肵�܂��D*dynamical*�́C���̍��̂������@���ɏ]�����ǂ������w�肷��t���O�ł��D����*dynamical*��*true*�̏ꍇ�C���̍��̂ɉ����͂��v�Z����C�j���[�g���̉^���@���ɂ��������č��̂̑��x���ω����܂��D����C*dynamical*��*false*�̏ꍇ�͊O�͂ɂ��e�����󂯂��C�ݒ肳�ꂽ���x�œ����^�����܂��D����͂��傤�ǁ��̎��ʂ����ꍇ�Ɠ����ł��D
### ���


\begin{tabular}{p{.15\hsize}p{.45\hsize}p{.30\hsize}}
\multicolumn{3}{l}{*PHSolidDesc*}							\\ \midrule
*Vec3d*	&	*velocity*		& ���x					\\
*Vec3d*	&	*angVelocity*	& �p���x				\\
*Posed*	&	*pose*			& �ʒu�ƌ���			\\
\end{tabular}



\begin{tabular}{p{.2\hsize}p{.5\hsize}p{.20\hsize}}
\multicolumn{3}{l}{*PHSolidIf*}									\\ \midrule
*Vec3d*			& *GetVelocity()*						& \\
*void* 			& *SetVelocity(const Vec3d\&)*			& \\
*Vec3d* 			& *GetAngularVelocity()*					& \\
*void* 			& *SetAngularVelocity(const Vec3d\&)*	& \\
*Posed* 			& *GetPose()*							& \\
*void* 			& *SetPose(const Posed\&)*				& \\
*Vec3d* 			& *GetFramePosition()*					& \\
*void* 			& *SetFramePosition(const Vec3d\&)*		& \\
*Vec3d* 			& *GetCenterPosition()*					& \\
*void* 			& *SetCenterPosition(const Vec3d\&)*		& \\
*Quaterniond* 	& *GetOrientation()*						& \\
*void* 			& *SetOrientation(const Quaterniond\&)*	& \\
\end{tabular}

*velocity*, *angVelocity*, *pose*�͂��ꂼ��O���[�o�����W�n�Ɋւ��鍄�̂̑��x�C�p���x�C�ʒu����ь�����\���܂��D*[Get|Set]FramePosition*�̓O���[�o�����W�n�Ɋւ��鍄�̂̈ʒu���擾/�ݒ肵�܂��D����ɑ΂���*[Get|Set]CenterPosition*�͍��̂̎��ʒ��S�̈ʒu���擾/�ݒ肵�܂��D�ΐS���Ă��鍄�̂̓��[�J�����W���_�Ǝ��ʒ��S����v���Ȃ����Ƃɒ��ӂ��Ă��������D*[Get|Set]Orientation*�̓O���[�o�����W�n�Ɋւ��鍄�̂̌������擾/�ݒ肵�܂��D
### �͂̈���Ǝ擾
���̂ɉ����͂ɂ�

-  ���[�U���ݒ肷��O��
-  �d��
-  �֐߂�ڐG��������S����

��$3$��ނ�����C���ꂼ��ɂ��ĕ��i�͂ƃg���N������܂��D�����ŁC�d�͂͏d�͉����x�ƍ��̂̎��ʂ�茈�܂�C�S���͍͂S�������𖞂����悤�ɓ����Ŏ����I�Ɍv�Z����܂��D�ȉ��ł̓��[�U�����̂ɉ�����O�͂�ݒ�E�擾������@�������܂��D

\begin{tabular}{p{.2\hsize}p{.5\hsize}p{.20\hsize}}
\multicolumn{3}{l}{*PHSolidIf*}								\\ \midrule
*void* 	& *AddForce(Vec3d)*					& \\
*void* 	& *AddTorque(Vec3d)*					& \\
*void* 	& *AddForce(Vec3d, Vec3d)*			& \\
*Vec3d* 	& *GetForce()*						& \\
*Vec3d* 	& *GetTorque()*						& \\
\end{tabular}

���i�͂�������ɂ�*AddForce*���g���܂��D
```
solid->AddForce(Vec3d(0.0, -1.0, 0.0));
```
�Ƃ���ƍ��̂̎��ʒ��S�ɕ��i��$(0, -1, 0)$�������܂��D�������͂̓O���[�o�����W�n�ŕ\������܂��D���
```
solid->AddTorque(Vec3d(1.0, 0.0, 0.0));
```
�Ƃ���ƍ��̂̎��ʒ��S�Ɋւ��ă��[�����g$(1, 0, 0)$�������܂��D��p�_��C�ӂɎw�肷��ɂ�
```
solid->AddForce(Vec3d(0.0, -1.0, 0.0), Vec3d(0.0, 0.0, 1.0));
```
�Ƃ��܂��D���̏ꍇ�͕��i��$(0, -1, 0)$����p�_$(0, 0, 1)$�ɉ����܂��D�����ō�p�_�̈ʒu�͍��̂̃��[�J�����W�ł͂Ȃ��O���[�o�����W�ŕ\������邱�Ƃɒ��ӂ��Ă��������D*AddForce*��*AddTorque*�͕�����ĂԂƁC���ꂼ��Ŏw�肵���O�͂̍��͂��ŏI�I�ɍ��̂ɉ����O�͂ƂȂ�܂��D�O�͂��擾����ɂ�*GetForce*�C*GetTorque*���g���܂��D�������C�����̊֐��Ŏ擾�ł���̂͒��O�̃V�~�����[�V�����X�e�b�v�ō��̂ɍ�p�����O�͂ł��D���������Ē��O�̃V�~�����[�V�����X�e�b�v���*AddForce*�����͎͂擾�ł��܂���D
## �֐�





\includegraphics[width=.5\hsize]{fig/phconstraint.eps}

\caption{Constraint class hierarchy}


�S���Ƃ͍��̂ƍ��̂̊Ԃɍ�p���Ă��̑��ΓI�^���ɐ����������v�f�ł��D�S���̃N���X�K�w��Fig.\,\ref{fig_phconstraint}�Ɏ����܂��D�܂��S���͊֐߂ƐڐG�ɕ�����܂��D�֐߂̓��[�U���쐬���܂����C�ڐG�͏Փ˔��茋�ʂɂ��ƂÂ��Ď����I�ɐ����E�폜����܂��D�֐߂͂���ɂ������̎�ނɕ������܂��D�ׂ��Ȑ����͌�񂵂ɂ��āC�܂��͊֐߂̍쐬���@���猩�Ă����܂��D
### �֐߂̍쐬
�ȉ��ł͂����Ƃ��g�p�p�x�̍����q���W�̍쐬���ɂƂ��Ċ֐߂̍쐬���@��������܂��D�q���W���쐬����ɂ͎��̂悤�ɂ��܂��D
```
PHSolidIf* solid0 = phScene->GetSolids()[0];
PHSolidIf* solid1 = phScene->GetSolids()[1];

PHHingeJointDesc desc;
desc.poseSocket.Pos() = Vec3d( 1.0, 0.0, 0.0);
desc.posePlug.Pos()   = Vec3d(-1.0, 0.0, 0.0);
PHHingeJointIf* joint
    = phScene->CreateJoint(solid0, solid1, desc)->Cast();
```
�쐬�������֐߂̎�ނɉ������f�B�X�N���v�^���쐬���C�����*PHScene*��*CreateJoint*�֐��ɓn���Ċ֐߂��쐬���܂��D���̂Ƃ��C�f�B�X�N���v�^�ƂƂ��ɘA�����������̂̃C���^�t�F�[�X���n���܂��D*CreateJoint*��*PHJointIf**��Ԃ��܂��̂ŁC�쐬�����֐߂̃C���^�t�F�[�X�𓾂�ɂ�*Cast*�œ��I�L���X�g���܂��D�֐߂Ɋւ���*PHScene*�̊֐����ȉ��Ɏ����܂��D

\begin{tabular}{p{.15\hsize}p{.75\hsize}p{.0\hsize}}
\multicolumn{3}{l}{*PHSceneIf*}													\\ \midrule
*PHJointIf**	& *CreateJoint(PHSolidIf*, PHSolidIf*, const PHJointDesc\&)*	& \\
*int*		& *NJoint()*													& \\
*PHJointIf**	& *GetJoint(int i)*											& \\
\end{tabular}

*NJoint*�̓V�[�����̊֐߂̌���Ԃ��܂��D*GetJoint*��*i*�Ԗڂ̊֐߂��擾���܂��D
### �\�P�b�g�ƃv���O





\begin{tabular}{c}
\includegraphics[clip, width=.5\hsize]{fig/socket_plug1.eps} \\
(a) before connection \\
\\
\includegraphics[clip, width=.5\hsize]{fig/socket_plug2.eps} \\
(b) after connection \\
\end{tabular}

\caption{Socket and plug}


���āC��̗�Ńf�B�X�N���v�^�ɒl��ݒ肵�Ă���ӏ��ɒ��ڂ��Ă��������D���̕����Ŋ֐߂̎��t���ʒu���w�肵�Ă��܂��DSpringhead�ł́C�\�P�b�g�ƃv���O�ƌĂ΂�郍�[�J�����W�n��p���Ċ֐߂̎��t���ʒu��\�����܂��D�\�P�b�g�ƃv���O�Ƃ́C���̖��O����A�z����悤�ɁC�A�����鍄�̂Ɏ��t�������̂悤�Ȃ��̂ł��D*CreateJoint*�̑�$1$�����̍��̂Ƀ\�P�b�g�����C��$2$�����̍��̂Ƀv���O�����܂��D�\�P�b�g�ƃv���O�����ꂼ��̍��̂̂ǂ̈ʒu�Ɏ��t�����邩���w�肷��̂��f�B�X�N���v�^��*poseSocket*��*posePlug*�ł��D��̗�ł̓\�P�b�g�̈ʒu��$(1,0,0)$�C�v���O�̈ʒu��$(-1,0,0)$�ł���(Fig.\,\ref{fig_socket_plug}(a))�D���̏ꍇ��Fig.\,\ref{fig_socket_plug}(b)�̂悤�ɍ��̂��A������܂��D��q����悤�ɁC�q���W�̓\�P�b�g�ƃv���O��z������v������S���ł��D���������ĘA�����ꂽ���̓��m�̓\�P�b�g�ƃv���O��z������]���Ƃ��đ��ΓI�ɉ�]���邱�Ƃ��ł��܂��D�\�P�b�g�ƃv���O�Ɋւ���f�B�X�N���v�^�ƃC���^�t�F�[�X���Љ�܂��D

\begin{tabular}{p{.15\hsize}p{.35\hsize}p{.40\hsize}}
\multicolumn{3}{l}{*PHConstraintDesc*}					\\ \midrule
*Posed*	&	*poseSocket*	& �\�P�b�g�̈ʒu�ƌ���	\\
*Posed*	&	*posePlug*	& �v���O�̈ʒu�ƌ���	\\
\end{tabular}



\begin{tabular}{p{.15\hsize}p{.50\hsize}p{.25\hsize}}
\multicolumn{3}{l}{*PHConstraintIf*}								\\ \midrule
*PHSolidIf**	& *GetSocketSolid()*							& �\�P�b�g���̍��� \\
*PHSolidIf** & *GetPlugSolid()*							& �v���O���̍��� \\
*void* 		& *GetSocketPose(Posed\&)*					& \\
*void* 		& *SetSocketPose(const Posed\&)*				& \\
*void* 		& *GetPlugPose(Posed\&)*						& \\
*void* 		& *SetPlugPose(const Posed\&)*				& \\
*void* 		& *GetRelativePose(Posed\&)*					& ���ΓI�Ȉʒu�ƌ��� \\
*void* 		& *GetRelativeVelocity(Vec3d\&, Vec3d\&)*	& ���Α��x \\
*void* 		& *GetConstraintForce(Vec3d\&, Vec3d\&)*		& �S���� \\
\end{tabular}

*GetRelativePose*�̓\�P�b�g���W�n���猩���v���O���W�n�̑��ΓI�Ȉʒu�ƌ������擾���܂��D���l�ɁC*GetRelativeVelocity*�̓\�P�b�g����݂��v���O�̑��Α��x���\�P�b�g���W�n�Ŏ擾���܂��D�����ő�$1$���������i���x�C��$2$�������p���x�ł��D*GetConstraintForce*�͂��̍S�������̂ɉ������S���͂��擾���܂�(��$1$���������i�́C��$2$���������[�����g)�D��̓I�ɂ́C�\�P�b�g�����̂ɍ�p�����S���͂��\�P�b�g���W�n�ŕ\���������̂������܂��D�v���O�����̂ɂ͍�p����p�̖@���ɂ���ċt�����̗͂���p���܂����C����𒼐ڎ擾����֐��͗p�ӂ���Ă��܂���D
### �֐߂̎��
Springhead�Ŏg�p�\�Ȋ֐߂̎�ނ�

-  �q���W (*PHHingeIf*)
-  �X���C�_ (*PHSliderIf*)
-  �p�X�W���C���g (*PHPathJointIf*)
-  �{�[���W���C���g (*PHBallJointIf*)
-  �o�l (*PHSpringIf*)

��5��ނł��D��ނ��ƂɁC���R�x�E�S���̎d���E�ψʂ̋��ߕ����قȂ�܂��D
#### �q���W
\begin{fig}\epscapopt{phhingejoint}{Hinge joint}{width=0.5\hsize}\end{fig}�q���W��$1$����]�֐߂ł��D�q���W�́C\Fig{phhingejoint}�Ɏ����悤�Ƀ\�P�b�g�ƃv���O��z������v����悤�ɍS�����܂��D���̂Ƃ��\�P�b�g��y���ƃv���O��y���̐����p(x�����m�ł��������Ƃł���)���֐ߕψʂƂȂ�܂��D�֐ߕψʂ��擾����API��$1$���R�x�֐�(*PH1DJointIf*)�ŋ��ʂł��D���̂��߃q���W�Ɍ��炸�X���C�_�E�p�X�W���C���g�ł��g�p�ł��܂��D\begin{reference}{PH1DJointIf}\classmember{double GetPosition()}�֐߂̕ψʂ��擾���܂��D�ψʂ̂͂�����͊֐߂̎�ނɈˑ����܂��D\end{reference}
#### �X���C�_
\begin{fig}\epscapopt{phsliderjoint}{Slider joint}{width=0.5\hsize}\end{fig}�X���C�_��$1$���R�x�̒����֐߂ł��D�X���C�_�́C\Fig{phsliderjoint}�Ɏ����悤�Ƀ\�P�b�g�ƃv���O��z�������꒼����ɏ��C�����҂�x���Cy�������������������悤�ɍS�����܂��D���̂Ƃ��\�P�b�g�̌��_����v���O�̌��_�܂ł��֐ߕψʂƂȂ�܂��D
#### �p�X�W���C���g
�p�X�W���C���g�̓\�P�b�g�ƃv���O�̑��Έʒu�֌W��$1$�p�����[�^�̎��R�Ȑ��ŕ\������֐߂ł��D�ڂ����͌�q���܂��DT.B.D.
#### �{�[���W���C���g
\begin{fig}  \begin{tabular}{cc}    \epsopt{phballjoint}{width=0.45\hsize} & \epsopt{swingtwist}{width=0.35\hsize} \\    (a) & (b)  \end{tabular}  \labelcap{phballjoint}{Ball Joint}\end{fig}�{�[���W���C���g��$3$���R�x�̉�]�֐߂ł��D�{�[���W���C���g��\Fig{phballjoint}(a)�Ɏ����悤�Ƀ\�P�b�g�ƃv���O�̌��_����v����悤�ɍS�����܂��D�\�P�b�g���W�n���v���O���W�n�ɕϊ�����悤�ȃN�H�[�^�j�I�����ψʂƂȂ�܂��D����ŁC�{�[���W���C���g�̕ψʂ̓I�C���[�p�̈��ł���Swing-Twist���W�n(\Fig{phballjoint}(b))�Ŏ擾���邱�Ƃ��ł��܂��D�\�P�b�g�ƃv���O��z�����m���Ȃ��p���X�C���O�p(Swing)�C�v���O��z�����\�P�b�g��x-y���ʂւ̎ˉe���\�P�b�g��x���ƂȂ��p���X�C���O���ʊp(Swing-Dir)�C�v���O��z������̉�]�p�x���c�C�X�g�p(Twist)�ƌĂт܂��DSwing-Twist���W�n�́C��q����{�[���W���C���g�̊֐߉��͈͂̎w��ɗp���܂��D����2��ނ̕ψʂ́C���ꂼ��ɑΉ������֐��Ŏ擾���邱�Ƃ��ł��܂��D\begin{reference}{PHBallJoint}\classmember{Quaterniond GetPosition()}�\�P�b�g���W�n���v���O���W�n�ɕϊ�����悤�ȃN�H�[�^�j�I����Ԃ��܂��D\classmember{Vec3d GetAngle()}Swing-Twist���W�n�ŕ\�����ꂽ�֐ߕψʂ�Ԃ��܂��D\end{reference}
#### �o�l
\begin{fig}\epscapopt{phspring}{Spring}{width=0.5\hsize}\end{fig}���̊Ԃ�A������_���p�t���o�l�ł��D�\�P�b�g���W�n�ƃv���O���W�n����v����Ƃ������R��ԂŁC�ʒu�̕ψʁE�p���̕ψʂɔ�Ⴕ�Ď��R��Ԃɖ߂��悤�ȗ́E���[�����g�𔭐����܂��D���i�^���ɍ�p����o�l�E�_���p�W���ƁC��]�^���ɍ�p����o�l�E�_���p�W���̓f�B�X�N���v�^�ɂ���Ă��ꂼ��ݒ�ł��܂��D\begin{lightreference}{PHSpringDesc}\multicolumn{2}{l}{*Vec3d spring*} & ���i�^���ɑ΂���o�l�W�� \\\multicolumn{2}{l}{*Vec3d damper*} & ���i�^���ɑ΂���_���p�W�� \\\multicolumn{2}{l}{*double springOri*} & ��]�^���ɑ΂���o�l�W�� \\\multicolumn{2}{l}{*double damperOri*} & ��]�^���ɑ΂���_���p�W�� \\\end{lightreference}
### �L�����Ɩ�����


\begin{tabular}{p{.15\hsize}p{.45\hsize}p{.30\hsize}}
\multicolumn{3}{l}{*PHConstraintDesc*}					\\ \midrule
*bool*	&	*bEnabled*	& �L��/�����t���O		\\
\end{tabular}



\begin{tabular}{p{.15\hsize}p{.50\hsize}p{.25\hsize}}
\multicolumn{3}{l}{*PHConstraintIf*}						\\ \midrule
*void*	& *Enable(bool)*					& \\
*bool* 	& *IsEnabled()*					& \\
\end{tabular}

�L���ȍS���͍S���͂𐶂��܂��D���������ꂽ�S���͑��݂��Ȃ��̂Ɠ�����ԂɂȂ�܂����C�폜����̂ƈقȂ肢�ł��ēx�L�������邱�Ƃ��ł��܂��D�쐬����̍S���͗L��������Ă��܂��D
### �֐ߐ���

#### $1$���R�x�֐߂̏ꍇ


\begin{tabular}{p{.15\hsize}p{.45\hsize}p{.30\hsize}}
\multicolumn{3}{l}{*PHJoint1DDesc*}								\\ \midrule
*double*	&	*spring*			& ���͈͉���				\\
*double*	&	*damper*			& ���͈͏��				\\
*double*	&	*targetPosition*	& ���͈͐����p�o�l�W��	\\
*double*	&	*targetVelocity*	& ���͈͐����p�_���p�W��	\\
*double*	&	*offsetForce*	& \\
*double*	&	*fMax*			& \\
\end{tabular}



\begin{longtable}{p{.15\hsize}p{.45\hsize}p{.30\hsize}}
\multicolumn{3}{l}{*PHJoint1DIf*}						\\ \midrule
*double*	& *GetPosition()*				& �֐ߕψʂ��擾 \\
*double* & *GetVelocity()*				& �֐ߑ��x���擾 \\
*void* 	& *SetSpring(double)*			& \\
*double* & *GetSpring()*					& \\
*void* 	& *SetDamper(double)*			& \\
*double* & *GetDamper()*					& \\
*void* 	& *SetTargetPosition(double)*	& \\
*double* & *GetTargetPosition()*			& \\
*void* 	& *SetTargetVelocity(double)*	& \\
*double* & *GetTargetVelocity()*			& \\
*void* 	& *SetOffsetForce(double)*		& \\
*double* & *GetOffsetForce()*				& \\
*void* 	& *SetTorqueMax(double)*			& �ő�֐߃g���N��ݒ� \\
*double* & *GetTorqueMax()*				& �ő�֐߃g���N���擾 \\
\end{longtable}

�֐߂��쓮�����$f$�͎����ŗ^�����܂��D

f = K(p_0 - p) + D(v_0 - v) + f_0

������$p$�C$v$�͂��ꂼ��֐ߕψʂƊ֐ߑ��x��*GetPosition*�C*GetVelocity*�Ŏ擾�ł��܂��D���̑��̋L���ƃf�B�X�N���v�^�ϐ��Ƃ̑Ή��͈ȉ��̒ʂ�ł��D

\begin{tabular}{ll}
$K$		&	*spring*				\\
$D$		&	*damper*				\\
$p_0$	&	*targetPosition*		\\
$v_0$	&	*targetVelocity*		\\
$f_0$	&	*offsetForce*
\end{tabular}

��̎��̓o�l�E�_���p���f����PD���䑥�̓�ʂ�̉��߂��ł��܂��D�O�҂Ƃ��ĂƂ炦��Ȃ�$K$�̓o�l�W���C$D$�̓_���p�W���C$p_0$�̓o�l�̎��R���C$v_0$�͊���x�ƂȂ�܂��D��҂Ƃ��ĂƂ炦��ꍇ��$K$��P�Q�C���C$D$��D�Q�C���C$p_0$�͖ڕW�ψʁC$v_0$�͖ڕW���x�ƂȂ�܂��D�܂��C$f_0$�͊֐߃g���N�̃I�t�Z�b�g���ł��D��̎��œ���ꂽ�֐߃g���N�͍Ō��$\pm$*fMax*�͈̔͂Ɏ��܂�悤�ɃN�����v����܂��D
#### �{�[���W���C���g�̏ꍇ
�q���W�Ɠ��l�ɁC�o�l�_���p���f���EPD������������܂��D�{�[���W���C���g�̕ψʂ̓N�H�[�^�j�I���ŕ\����邽�߁C�ڕW�ψ�*targetPosition*�̓N�H�[�^�j�I���ŁC�ڕW���x*targetVelocity*�͉�]�x�N�g���ŗ^���܂��D\begin{lightreference}{PHBallJointDesc}\multicolumn{2}{l}{*double spring*} & �o�l�W�� \\\multicolumn{2}{l}{*double damper*} & �_���p�W�� \\\multicolumn{2}{l}{*Quaterniond targetPosition*} & �ڕW�ψ� \\\multicolumn{2}{l}{*Vec3d targetVelocity*} & �ڕW���x \\\multicolumn{2}{l}{*Vec3d offsetForce*} & ���[�^�[�g���N \\\multicolumn{2}{l}{*double fMax*} & �֐߃g���N�̌��x \\\end{lightreference}	%\multicolumn{2}{l}{*void SetMotorTorque(double)*}		& \\	%\multicolumn{2}{l}{*double GetMotorTorque()*}	& \\	%double	secondDamper;	///< ��ڂ̃_���p�W��	%double  yieldStress;	///< �~������	%double  hardnessRate;	///< �~�����͈ȉ��̏ꍇ�ɓ�ڂ̃_���p�W���Ɋ|����䗦	%void SetTrajectoryVelocity(double v);	%double GetTrajectoryVelocity();	%double  GetSecondDamper();	%void	SetSecondDamper(double input);	%double GetYieldStress();    %void SetYieldStress(const double yS);	%double GetHardnessRate();	%void SetHardnessRate(const double hR);	%PHJointDesc::PHDeformationType 	GetDeformationMode();
### ���搧��
*CreateLimit*�͉��͈͐���I�u�W�F�N�g�̃f�B�X�N���v�^�������ɂƂ�܂��D$1$���R�x�֐߂̉��͈͐���̏ꍇ�C*Vec2d range*�������\���܂��D*range[0]*������̉����C*range[1]*������ł��D*range[0] < range[1]*����������Ă���Ƃ��Ɍ�����͈͐��񂪗L���ƂȂ�܂��D�f�t�H���g�ł�*range[0] > range[1]*�ƂȂ�l���ݒ肳��Ă��āC���͈͐���͖����ƂȂ��Ă��܂��D�֐߂̕ψʂ����͈͌��E�ɓ��B�����Ƃ��C�͈͂𒴉߂��Ȃ��悤�ɉ��͈͐���̍S���͂���p���܂��D���̂Ƃ��C�֐ߕψʂ�͈͓��ɉ����߂��͂̓o�l�E�_���p���f���Ōv�Z����܂��D���̃o�l�W���ƃ_���p�W���͂��ꂼ��f�B�X�N���v�^��*spring*�C*damper*�Ŏw�肵�܂��D\begin{tips}���͈͗p��*spring*�C*damper*�͏����l�ł��\���傫�Ȓl���ݒ肳��Ă��܂����C�֐ߐ���ɂ����Ĕ��ɑ傫�ȃo�l�E�_���p�W����p����Ɖ��͈͐���̃o�l�E�_���p�������Ă��܂����Ƃ�����܂��D���̏ꍇ�ɂ͊֐ߐ�����傫�ȌW����K�؂ɍĐݒ肷��ƁC���͈͓��Ŋ֐߂𐧌䂷�鎖���ł���悤�ɂȂ�܂��D\end{tips}
#### $1$���R�x�֐߂̏ꍇ
\begin{reference}{PH1DJointLimitDesc}\classmember{Vec2d range}���͈͂�\���܂��D*range[0]*�������C*range[1]*������ł��D\classmember{double spring} \Plus\classmember{double damper}���͈͂𐧌����邽�߂̃o�l�E�_���p���f���̌W���ł��D\end{reference}\begin{reference}{PH1DJointLimitIf}\classmember{IsOnLimit()}���݂̊֐ߎp�������͈͊O�ɂ��鎞��*true*��Ԃ��܂��D���̊֐���*true*��Ԃ��悤�Ȏ��C�֐߂ɂ͉��搧����������邽�߂̍S���͂��������Ă��܂��D\end{reference}
#### �{�[���W���C���g�̏ꍇ
�{�[���W���C���g�̉��͈͂�\Fig{phballjoint}(b)�Ɏ���Swing-Twist���W�n�ɂ���Ďw�肵�܂��D�{�[���W���C���g�ɑ΂��Ă�2��ނ̉��͈͐�����g�p���邱�Ƃ��ł��܂��D

-  *ConeLimit*�͉~���`�̉��͈͐���ŁC��Ɋ֐߂̃X�C���O�p�����͈͓��ɐ��񂵂܂��D
-  *SplineLimit*�͎��R�Ȑ��`�̉��͈͐���ŁC�v���O���W�nz���̉��͈͂�Ȑ��Ŏw�肷�邱�Ƃ��ł��܂��D

�����ł�*ConeLimit*�ɂ��Đ������܂�(*SplineLimit*�ɂ��Ă͌�q���܂�)�D\begin{reference}{PHBallJointConeLimitDesc}\classmember{Vec2d limitSwing}�X�C���O�p�̉��͈͂ł��D�T�O�I�ɂ́C�֐߂����ȏ�ɐ܂�Ȃ���Ȃ��悤�ɂ��鐧��ł�(�X�C���O�p�̉�����ݒ肷�鎖���ł���̂ŁC���ۂɂ͈��ȏ�ɂ܂������ɂȂ�Ȃ��悤�ɂ���@�\���L���Ă��܂�)�D*limitSwing[0]*�������C*limitSwing[1]*������ł��D*limitSwing*���擾�E�ݒ肷�邽�߂�API��\begin{quote}*PHBallJointConeLimitIf::[Set|Get]SwingRange(range)*\end{quote}�ł��D*limitSwing[0] > limitSwing[1]*�ƂȂ鎞�͖���������܂��D�f�t�H���g�ł�*limitSwing[0] > limitSwing[1]*�ƂȂ�l���Z�b�g����Ă��܂��D\classmember{Vec2d limitTwist}�c�C�X�g�p�̉��͈͂ł��D�T�O�I�ɂ́C�֐߂����ȏ�ɂ˂���Ȃ��悤�ɂ��邽�߂̐���ł��D*limitTwist[0]*�������C*limitTwist[1]*������ł��D*limitTwist*���擾�E�ݒ肷�邽�߂�API��\begin{quote}*PHBallJointConeLimitIf::[Set|Get]TwistRange(range)*\end{quote}�ł��D*limitTwist[0] > limitTwist[1]*�ƂȂ鎞�͖���������܂��D�f�t�H���g�ł�*limitTwist[0] > limitTwist[1]*�ƂȂ�l���Z�b�g����Ă��܂��D\classmember{double spring} \Plus\classmember{double damper}���͈͂𐧌����邽�߂̃o�l�E�_���p���f���̌W���ł��D$1$���R�x�֐߂̏ꍇ�Ɠ����ł��D\end{reference}\begin{reference}{PHBallJointConeLimitIf}\classmember{IsOnLimit()}���݂̊֐ߎp�������͈͊O�ɂ��鎞��*true*��Ԃ��܂��D$1$���R�x�֐߂̏ꍇ�Ɠ����ł��D\end{reference}
### �{�[���W���C���g�̎��R�Ȑ����� 

### �p�X�W���C���g 

### �e�Y���ό`�o�l�_���p

## �֐ߌn�̋t�^���w
�t�^���w(IK)�́C���̊֐ߌn�ɂ����č��̂��ڕW�ʒu�ɓ��B����悤�֐߂𐧌䂷��@�\�ł��DSpringhead�ł́C�֐ߌn�̃��R�r�A����p����IK�@�\���g�p�\�ł��D�����V�~�����[�V������1�X�e�b�v���ƂɊ֐ߌn�̃��R�r�A�����v�Z���C����Ɋ�Â��č��̂�ڕW�ʒu�E�p���ɋ߂Â���悤�Ȋe�֐߂̊p���x���v�Z���܂��D�V�~�����[�V�����𑱂��邱�ƂŁC�ŏI�I�ɍ��̂��ڕW�ʒu�E�p���ƂȂ�����Ԃ������܂��DSpringhead��̍��̊֐ߌn�ɑ΂���IK���g�p����ɂ́C���X���������K�v�ł��D���̂悤��3�̍��̂�������ɂȂ������֐ߌn���ɂƂ��ĉ�����܂��D

\epsopt{ikexample3link}{width=0.5\hsize}

IK���g�p����ɂ́C�܂�IK�ɗp���邽�߂̊֐߂��u�A�N�`���G�[�^�v�Ƃ��ēo�^����K�v������܂��D
```
// given PHSceneIf* phScene
// given PHSolidIf* solid1, solid2, solid3
// given PHHingeJointIf* joint1 (solid1 <-> solid2)
// given PHHingeJointIf* joint2 (solid2 <-> solid3)

PHIKHingeActuatorDesc descIKActuator;

PHIKHingeActuatorIf* ikActuator1
  = phScene->CreateIKActuator(descIKActuator);
ikActuator1.AddChildObject(joint1);

PHIKHingeActuatorIf* ikActuator2
  = phScene->CreateIKActuator(descIKActuator);
ikActuator1.AddChildObject(joint2);
```
*PHIKHingeActuatorIf*��*PHHingeJointIf*�ɑΉ�����A�N�`���G�[�^�N���X�ł��D���ɁC�֐ߌn�̐e�q�֌W��o�^���܂��D�e�A�N�`���G�[�^�ɁC�q�A�N�`���G�[�^��o�^���܂��D
```
ikActuator1.AddChildObject(ikActuator2);
```
�܂��CIK��p���ē��B�������[�̍��̂��u�G���h�G�t�F�N�^�v�Ƃ��ēo�^����K�v������܂��D
```
PHIKEndEffectorDesc descEndEffector;

PHIKEndEffectorIf* ikEndEffector1
  = phScene->CreateIKEndEffector(descEndEffector);
ikEndEffector1.AddChildObject(solid3);
```
�Ō�ɁC���̊֐ߌn�̐e�q�֌W�ɂ����āC�G���h�G�t�F�N�^�̒��ڂ̐e�ɂ�����A�N�`���G�[�^�ɑ΂��C�G���h�G�t�F�N�^��o�^���܂��D
```
ikActuator2.AddChildObject(ikEndEffector1);
```
���̗�ł� *solid1 -(joint1)-> solid2 -(joint2)-> solid3* �̂悤�Ɋ֐߂��ڑ�����Ă��܂�����C�֐ߌn�̖��[�ł��� *solid3* ���G���h�G�t�F�N�^�ɂ����ꍇ�C���ڂ̐e�ɂ�����A�N�`���G�[�^�� *joint2* �ɑΉ�����A�N�`���G�[�^�C���Ȃ킿 *ikActuator2* �Ƃ������ƂɂȂ�܂��D�����܂ł̍�ƂŁC�������ꂽ�I�u�W�F�N�g�̊֌W�͈ȉ��̂悤�ɂȂ��Ă���͂��ł��D

\epsopt{ikexample3linkobjects}{width=0.9\hsize}

����ŉ������͏I���ł��D�ڕW�ʒu���Z�b�g���CIK�G���W����L���ɂ����IK�������n�߂܂��D
```
// solid3 goes to (2, 5, 0)
ikEndEffector1->SetTargetPosition(Vec3d(2, 5, 0)); 

phScene->GetIKEngine()->Enable(true);

...
phScene->Step(); // IK is calculated in physics step
...
```

### IK�G���W��
IK�̌v�Z�́C*PHScene*������IK�G���W��(*PHIKEngine*)�ɂ���Ď�������Ă��܂��DIK�G���W���̓f�t�H���g�ł͖����ƂȂ��Ă��܂��D
```
phScene->GetIKEngine()->Enable(true);
```
�����s���邱�ƂŗL���ƂȂ�܂��D*GetIKEngine()*�́C*PHScene*������IK�G���W�����擾����API�ł��DSpringhead�ɂ�����IK�̌v�Z�����́C�֐ߌn�̃��R�r�s��i���R�r�A���j�Ɋ�Â��܂��D�S�A�N�`���G�[�^�̊֐ߊp�x�ɔ����ω��� $\varDelta\bm{\theta}$ ��^�������́C�S�G���h�G�t�F�N�^�̈ʒu�̔����ω��� $\varDelta\bm{r}$ �́C�֐ߌn�̃��R�r�A�� $J$ ��p����\[\varDelta\bm{r} = J \varDelta\bm{\theta}\]�ƕ\����܂��D���X�e�b�v���ƂɊ֐ߌn���R�r�A��$J$����іڕW�ʒu�Ɍ����������ψ�$\varDelta\bm{r}$���v�Z���C��L�̐��`�A�����������������ƂŊe�֐߂ɗ^����p���x�����߂܂��D���`�A���������̋����ɂ̓K�E�X=�U�C�f���@�ɂ��J��Ԃ���@��p���Ă��܂��D���̂���1�X�e�b�v������̌J��Ԃ��v�Z�̉񐔂ɂ���Čv�Z���x�ƌv�Z���x�̃g���[�h�I�t������܂��D�J��Ԃ��̉񐔂́C
```
// 20 iteration per 1 physics step
phScene->GetIKEngine()->SetNumIter(20);
```
�̂悤�ɂ��Đݒ肷�邱�Ƃ��ł��܂��D\referencetitle\begin{reference}{PHSceneIf}\classmember{PHIKEngineIf* GetIKEngine()}IK�G���W�����擾���܂��D\end{reference}\begin{reference}{PHIKEngineIf}\classmember{Enable(bool b)}IK�G���W���̗L���E������؂�ւ��܂��D������*true*�Ȃ�ΗL�������C*false*�Ȃ�Ζ��������܂��D\classmember{SetNumIter(int n)}IK�̌J��Ԃ��v�Z�񐔂�1�X�e�b�v������*n*��ɃZ�b�g���܂��D\end{reference}
### �A�N�`���G�[�^
Springhead�ł́CIK�Ɏg�p����e�֐߂��A�N�`���G�[�^�ƌĂт܂��DIK�́C�A�N�`���G�[�^���쓮�����č��̂�ڕW�ʒu�ɓ��B�����܂��D���I�u�W�F�N�g�֌W�}��IK�G���W���̓A�N�`���G�[�^�𕡐��ێ����C�e�A�N�`���G�[�^���e�֐߂�ێ����܂��D�A�N�`���G�[�^�I�u�W�F�N�g��ɂ��C�֐߂���Ή����܂��D�A�N�`���G�[�^�I�u�W�F�N�g�̋�̓I�Ȗ����́C�֐߂̏�Ԃ�IK�G���W���ɓ`���CIK�̌v�Z�̂����֐߃��R�r�A���̌v�Z�ȂǊ֐߂��Ƃɍs�����������s���CIK�̌v�Z���ʂɏ]���Ċ֐߂𓮂������ł��D
#### �A�N�`���G�[�^�N���X�̎�ނƍ쐬
�{�e���M���_�ł́CIK�p�A�N�`���G�[�^�Ƃ��Ďg�p�ł���̂̓q���W�ƃ{�[���W���C���g�݂̂ł��D���ꂼ��ɑΉ������A�N�`���G�[�^�N���X������܂��D

-  *PHIKHingeActuator*��*PHHingeJoint*�ɑ΂���A�N�`���G�[�^�ł��D�q���W�W���C���g��1���R�x���쓮�ɗp���܂��D

-  *PHIKBallActuator*��*PHBallJoint*�ɑ΂���A�N�`���G�[�^�ł��D�{�[���W���C���g��3���R�x�̊֐߂ł����C��q����G���h�G�t�F�N�^�̎p��������s��Ȃ�(�G���h�G�t�F�N�^�̈ʒu�݂̂𐧌䂷��)�ꍇ�́C�G���h�G�t�F�N�^�̈ʒu��ω������邱�Ƃ̂ł���2���R�x�݂̂��쓮�ɗp���܂�(�g�p����2���R�x�̎���1�X�e�b�v���ƂɍX�V����܂�)�D


```
// given PHSceneIf* phScene

PHIKHingeActuatorDesc descIKActuator;
PHIKHingeActuatorIf* ikActuator
    = phScene->CreateIKActuator(descActuator);
```
�A�N�`���G�[�^���쐬����ɂ́C*PHSceneIf*��*CreateIKActuator*�֐���p���܂��D�����̓A�N�`���G�[�^�̃f�B�X�N���v�^�ł��D*PHIKHingeActuatorDesc*�^�̃f�B�X�N���v�^��n���ƃq���W�p�̃A�N�`���G�[�^���쐬����C*PHIKBallActuatorDesc*�^�̃f�B�X�N���v�^��n���ƃ{�[���W���C���g�p�̃A�N�`���G�[�^���쐬����܂��D�쐬���ꂽ���_�ł́C�A�N�`���G�[�^�͊֐߂ƑΉ��t��������Ă��܂���D�A�N�`���G�[�^�̎q�v�f�Ɋ֐߂�o�^���邱�ƂőΉ��t�����s���܂��D
```
// given PHHingeJointIf* joint
ikActuator->AddChildObject(joint);
```

#### �A�N�`���G�[�^�̐e�q�֌W�̓o�^
���̂悤�ɓ�҂ɕ��򂵂������N���ɂƂ�܂��F

\epsopt{ikexample5link}{width=0.8\hsize}

�v�Z��CIK�ŋ쓮����֐ߌn�͖؍\���łȂ���΂Ȃ�܂���DSpringhead�ł́C�A�N�`���G�[�^�̐e�q�֌W����邱�ƂŊ֐߂̖؍\����ݒ肵�܂��D
```
// given PHIKActuator ikActuator1, ikActuator2
ikActuator1->AddChildObject(ikActuator2);
```
*AddChildObject*���Ăяo���ƁC�A�N�`���G�[�^�ɑ΂��u�q�v�f�v�ƂȂ�A�N�`���G�[�^��o�^���邱�Ƃ��ł��܂��D�����S�ẴA�N�`���G�[�^�ɑ΂��čs�����ƂŃA�N�`���G�[�^�̖؍\�����ݒ肳��܂��D���̂Ƃ��A�N�`���G�[�^�̐e�q�֌W�́C�O�o�̐}�̉E���̂悤�ɂȂ�܂��D
#### �֐߂̃_���p�W����IK
�֐߂̉^���́CIK�@�\�ɂ���Čv�Z���ꂽ�ڕW�֐ߊp���x���֐߂�*SetTargetVelocity*���邱�ƂŎ������܂��D�ڕW���x�Ɋւ���֐߂̐U�镑���́C�֐߂�*damper*�p�����[�^�ɂ���ĕω����܂��D��ʂ�*damper*���傫���قǊ֐߂͌ł��Ȃ�C�O���̉e�����󂯂Â炭�Ȃ�܂��D���̐����͂��̂܂�IK�̐U�镑���ɂ��󂯌p����܂��D
#### �d�ݕt��IK
�ʏ�CIK�͑S�Ă̊֐߂��\�Ȍ���ϓ��Ɏg�p���ĖڕW��B������悤�v�Z����܂��D����C�L�����N�^�̓���ɗp����ꍇ�ȂǂŁC����D��I�ɓ��������̂͂��܂蓮�����Ȃ��C�Ƃ������d�ݕt�����v��������ʂ�����܂��DSpringhead��IK�ɂ́C���̂悤�ȏd�ݕt����ݒ肷�邱�Ƃ��ł��܂��D
```
// given PHIKActuator ikActuator1, ikActuator2
ikActuator1->SetBias(2.0);
ikActuator2->SetBias(1.0);
```
*SetBias*�́C�w�肵���֐߂����܂蓮�����Ȃ��悤�ɐݒ肷��֐��ł��DBias�ɂ�$1.0$�ȏ�̒l��ݒ肵�܂��D�傫�Ȓl��ݒ肵���֐߂قǁCIK�ɂ�铮��͏������Ȃ�܂��D�f�t�H���g�ł͂ǂ̃A�N�`���G�[�^��$1.0$�ƂȂ��Ă���C�S�֐߂��ϓ��Ɏg�p����܂��D
### �G���h�G�t�F�N�^
���́E�֐ߌn���\�����鍄�̂̈ꕔ���C�u�G���h�G�t�F�N�^�v�Ɏw�肷�邱�Ƃ��ł��܂��D�G���h�G�t�F�N�^�ɂ͖ڕW�ʒu�E�p�����w�����邱�Ƃ��ł��܂��DIK�G���W���́C�G���h�G�t�F�N�^���̂��w�肳�ꂽ�ڕW�ʒu�E�p����B������悤�A�N�`���G�[�^�𐧌䂵�܂��D
#### �G���h�G�t�F�N�^�̍쐬
�G���h�G�t�F�N�^��*PHSceneIf*��*CreateIKEndEffector*��p���č쐬���܂��D�����ɂ�*PHIKEndEffectorDesc*��n���܂��D
```
// given PHSceneIf* phScene

PHIKEndEffectorDesc descEndEffector;

PHIKEndEffectorIf* ikEndEffector
  = phScene->CreateIKEndEffector(descEndEffector);
```
�A�N�`���G�[�^���l�C�G���h�G�t�F�N�^���쐬���_�ł͍��̂Ƃ̑Ή��������܂���D*AddChildObject*�ɂ�荄�̂��q�v�f�Ƃ��ēo�^����K�v������܂��D
```
// given PHSolidIf* solid

ikEndEffector.AddChildObject(solid);
```
���ɁC�G���h�G�t�F�N�^���̂�e���̂ɘA�����Ă���A�N�`���G�[�^�ɑ΂��C�G���h�G�t�F�N�^���q�v�f�Ƃ��ēo�^���܂��D
```
// given PHIKActuatorIf* ikActuatorParent

ikActuatorParent.AddChildObject(ikEndEffector);
```
�������邱�ƂŃG���h�G�t�F�N�^�̓A�N�`���G�[�^�؍\���̗t�m�[�h�ƂȂ�CIK�̌v�Z�Ɏg�p�ł���悤�ɂȂ�܂��D�Ȃ��C�G���h�G�t�F�N�^�͈�̊֐ߌn�ɑ΂��ĕ����쐬���邱�Ƃ��ł��܂��D���̏ꍇ�CIK�͕����̃G���h�G�t�F�N�^���\�Ȍ��蓯���ɖڕW�ʒu�E�p����B���ł���悤�A�N�`���G�[�^�𐧌䂵�܂��D�܂��C�G���h�G�t�F�N�^�͊֐ߌn�̐�[���̂Ɍ���܂���D
#### �ڕW�ʒu�̐ݒ�
�G���h�G�t�F�N�^�̖ڕW�ʒu��*SetTargetPosition*�ɂ���Ďw�肵�܂��D
```
// solid3 goes to (2, 5, 0)
ikEndEffector->SetTargetPosition(Vec3d(2, 5, 0)); 
```
�G���h�G�t�F�N�^�ɖڕW�p�����w�����C�G���h�G�t�F�N�^������̎p�����Ƃ�悤�Ɋ֐ߌn�𓮍삳���邱�Ƃ��ł��܂��D
```
ikEndEffector->SetTargetOrientation( Quaterniond::Rot('x', rad(30)) ); 
ikEndEffector->EnableOrientationControl(true);
```
�ڕW�p����*Quaterniond*�Őݒ肵�܂��D�p������̓f�t�H���g�ł͖����ɂȂ��Ă���C�g�p����ɂ�*EnableOrientationControl*���Ă�ŗL��������K�v������܂��D*EnablePositionControl*�����*EnableOrientationControl*��p����ƁC�ʒu����E�p������̗������ʂɗL���E���������邱�Ƃ��ł��܂��D
```
// �ʒu���䂠��C�p������Ȃ��i�f�t�H���g�j
ikEndEffector->EnablePositionControl(true);
ikEndEffector->EnableOrientationControl(false);
```

```
// �ʒu����Ȃ��C�p�����䂠��
ikEndEffector->EnablePositionControl(false);
ikEndEffector->EnableOrientationControl(true);
```

```
// �ʒu���䂠��C�p�����䂠��
ikEndEffector->EnablePositionControl(true);
ikEndEffector->EnableOrientationControl(true);
```

## �ڐG

### �ڐG���f��





\begin{tabular}{c}
\includegraphics[clip, width=.7\hsize]{fig/phcontact.eps} \\
\end{tabular}

\caption{Contact configuration}


Springhead�ō̗p���Ă���ڐG���f���ɂ��Đ������܂��D��\ref{sec_physics_scene}�߂ŏq�ׂ��悤�ɁC*PHSceneIf::Step*�ɂ���ăV�~�����[�V������1�X�e�b�v�i�߂�ƁC���߂Ɍ`��̌�������ƐڐG�S���̐������s���܂��D���������̌`��̌����f�ʂƁC�ڐG�S���̊֌W�ɂ���Fig.\,\ref{fig_physics_contact}�Ɏ����܂��D�}�ł͊ȒP�̂��߂ɓ񎟌��ŕ`���Ă��܂����C���ۂɂ͐ڐG�f�ʂ�\�����p�`�̊e���_�ɐڐG�S��������܂��D�ڐG�S�������̍S���Ɠ��l�Ƀ\�P�b�g�ƃv���O�ō\������܂��D����ŁC���̍S���Ƃ͈Ⴂ�ڐG�S���͌�������A���S���Y���ɂ���ē��I�ɐ����E�j������܂��D���̂��߁C�ڐG���������̂̂ǂ���Ƀ\�P�b�g���邢�̓v���O�����t�����邩�͏󋵈ˑ��ł���C�O������I�����邱�Ƃ͂ł��܂���D�v���O����у\�P�b�g�̌����͎��̂悤�ɂ��Č��܂�܂��D�܂��Cx���͐ڐG�@���ƕ��s�Ɍ����܂��D�������ǂ��炪���̌������͏󋵈ˑ��ł��D���ɁCy���͐ڐG�_�ɂ������̍��̂̑��Α��x�x�N�g����ڐG�f�ʂ֓��e���������Ɍ����܂��D�Ō��z����x�Cy���ɒ�������悤�Ɍ��܂�܂��D�ȉ��ł͊e�ڐG�S�����ۂ������ɂ��ċ�̓I�ɏq�ׂ܂��D�܂��C�@�������̐i�����x�̑召�ɉ����ďՓ˃��f���ƐÓI�ڐG���f���̂����ꂩ���I������܂��D

v^\mathrm{x} < -V^\mathrm{th}   \;\; &\Rightarrow \;\; �Փ˃��f�� \\
v^\mathrm{x} \ge -V^\mathrm{th} \;\; &\Rightarrow \;\; �ÓI�ڐG���f��

������$v^\mathrm{x}$�̓\�P�b�g���猩���v���O�̑��Α��x��x���i�ڐG�@���j�����ŁC�߂Â����������𕉂Ƃ��܂��D�܂��C$V^\mathrm{th}$�͏Փ˃��f���֐؂�ւ��ՊE���x�ł��D�Փ˃��f���ł́C1�X�e�b�v��̑��Α��x${v^\mathrm{x}}'$�����˕Ԃ�W��$e$�ɂ��ƂÂ��Č��܂�C����𖞂����悤�ȐڐG�͂��v�Z����܂��D

{v^\mathrm{x}}' = - e \, v^\mathrm{x}

�����ŁC���˕Ԃ�W���͏Փ˂���`��̕����l�ɒ�`���ꂽ���˕Ԃ�W���̕��ϒl�ł��D�ÓI�ڐG���f���ł́C�`�󓯎m�̐i���[�x$d$��1�X�e�b�v�ŏ���̊����Ō�������悤�ȐڐG�͂����߂܂��D�܂�C1�X�e�b�v��̐i���[�x��$d'$�Ƃ����

d' = d - \gamma \mathrm{max}(d - d^\mathrm{tol}, 0)

�ƂȂ�܂��D������$\gamma$�͐ڐG�S���̌덷�C�����ł��D�܂��C$d^\mathrm{tol}$�͋��e�i���[�x�ł��D�Ō�ɁC�ڐG�͂��������ׂ������ɂ��ďq�ׂ܂��D�܂��C�@�������ɂ͔����͂̂ݍ�p���邱�Ƃ���C�ڐG�͂�x������$f^\mathrm{x}$�ɂ�

f^\mathrm{x} \ge 0

���ۂ����܂��D����ŐڐG�͂�y������$f^\mathrm{y}$�Cz������$f^\mathrm{z}$�͖��C�͂�\���܂��D���C�͂Ɋւ��ẮC���̌����̑��Α��x�ɂ��ƂÂ��Î~���C�������C�������肳��C����ɉ����čő喀�C�͂̐��񂪉ۂ���܂��D

-\mu_0 f^\mathrm{x} \le &f^\mathrm{y} \le \mu_0 f^\mathrm{x} & & if \; -V^\mathrm{f} \le v^\mathrm{y} \le V^\mathrm{f},\\
 \mu   f^\mathrm{x} \le &f^\mathrm{y} \le \mu   f^\mathrm{x} & & otherwise

�����ŁC�Î~���C�W��$\mu_0$����ѓ����C�W��$\mu$�͒��˕Ԃ�W���Ɠ��l�Ɋe�`��̕����l�̕��ϒl���p�����܂��D�܂��C$V^\mathrm{f}$�͐Î~���C�Ɠ����C���؂�ւ��ՊE���x�ł��Dz�������ɂ��Ă����l�̐��񂪉ۂ���܂��D�ڐG���f���̊֌W����C���^�t�F�[�X�ɂ͈ȉ�������܂��D

\begin{longtable}{p{.1\hsize}p{.5\hsize}p{.4\hsize}}
\multicolumn{3}{l}{*CDShapeIf*}						\\ \midrule
*void*	& *SetElasticity(float e)*       & ���˕Ԃ�W����ݒ� \\
*float*  & *GetElasticity()*              & ���˕Ԃ�W�����擾 \\
*void*   & *SetStaticFriction(float mu0)* & �Ö��C�W����ݒ� \\
*float*  & *GetStaticFriction()*          & �Ö��C�W�����擾 \\
*void*   & *SetDynamicFriction(float mu)* & �����C�W����ݒ� \\
*float*  & *GetDynamicFriction()*         & �����C�W�����擾
\end{longtable}



\begin{longtable}{p{.1\hsize}p{.5\hsize}p{.4\hsize}}
\multicolumn{3}{l}{*PHSceneIf*}						\\ \midrule
*void*	& *SetContactTolerance(double tol)* & ���e�����[�x��ݒ� \\
*double* & *GetContactTolerance()*           & ���e�����[�x���擾 \\
*void*   & *SetImpactThreshold(double vth)*  & �ŏ��Փˑ��x��ݒ� \\
*double* & *GetImpactThreshold()*            & �ŏ��Փˑ��x���擾 \\
*void*   & *SetFrictionThreshold(double vf)* & �ŏ������C���x��ݒ� \\
*double* & *GetFrictionThreshold()*          & �ŏ������C���x���擾
\end{longtable}

\noindent**���l**

-  �ڐG�f�ʂ̌����ɂ��ẮC�`�󓯎m�̐i�����x�����ƂɌ��肵�܂����C�����ł͏ڂ����q�ׂ܂���D
-  ���C�͂Ɋւ��Ă�y���Cz�����ʂɈ����܂����C���ۂ̖��C�͂�y������z�����̍��͂Ƃ��ė^�����܂��̂ŁC
���͂��ő喀�C�͂𒴉߂���\��������܂��D���̂悤��Springhead�̖��C���f���͂����܂ŋߎ��I�Ȃ��̂ł��̂�
���ӂ��ĉ������D


### �ڐG�͂̎擾
����̍��̂ɍ�p����ڐG�͂𒼐ڎ擾���邽�߂̃C���^�t�F�[�X�͗p�ӂ���Ă��܂���D���̂��߁C���[�U�T�C�h�ł�����x�̌v�Z���s���K�v������܂��D�ȉ��ɁC���鍄�̂ɍ�p����ڐG�͂̍��͂����߂��������܂��D
```
// given PHSceneIf* scene
// given PHSolidIf* solid

Vec3d fsum;    //< sum of contact forces applied to "solid"
Vec3d tsum;    //< sum of contact torques applied to "solid"

int N = scene->NContacts();
Vec3d f, t;
Posed pose;

for(int i = 0; i < N; i++){
    PHContactPointIf* con = scene->GetContact(i);
    con->GetConstraintForce(f, t);

    if(con->GetSocketSolid() == solid){
        con->GetSocketPose(pose);
        fsum -= pose.Ori() * f;
        tsum -= pose.Pos() % pose.Ori() * f;
    }
    if(con->GetPlugSolid() == solid){
        con->GetPlugPose(pose);
        fsum += pose.Ori() * f;
        tsum += pose.Pos() % pose.Ori() * f;
    }
}
```
�܂��C�V�[�����̐ڐG�S���̐���*PHSceneIf::NConstacts*�Ŏ擾���C*for*���[�v����$i$�Ԗڂ̐ڐG�S����*PHSceneIf::GetContact*�Ŏ擾���܂��D����*PHConstraintIf::GetConstraintForce*�ŐڐG�͂̕��i��*f*�ƃ��[�����g*t*���擾���܂����C�ڐG�S���̏ꍇ���[�����g��$0$�ł��̂ŗp���܂���D�܂��C������S���͂̓\�P�b�g/�v���O���W�n�ŕ\�������̂ŁC��p�_�̓\�P�b�g/�v���O���W�n�̌��_�ł��D������l�����č��̂ɍ�p����͂ƃ��[�����g�֕ϊ����C���͂ɑ������킹�Ă����܂��D���̂��\�P�b�g���ł���ꍇ�͍�p�E����p���l�����ĕ����𔽓]���邱�Ƃɒ��ӂ��ĉ������D
### �ڐG�͌v�Z�̗L��/�����̐؂�ւ�
�����̃A�v���P�[�V�����ł́C���ׂĂ̍��̂̑g�ݍ��킹�Ɋւ��ĐڐG����舵���K�v�͂���܂���D���̂悤�ȏꍇ�͕K�v�ȍ��̂̑΂Ɋւ��Ă̂ݐڐG��L�������邱�ƂŌv�Z�R�X�g���팸�ł��܂��DSpringhead�ł́C���̂̑g�ݍ��킹���Ɍ������肨��ѐڐG�͌v�Z���s������؂�ւ��邱�Ƃ��ł��܂��D����ɂ�*PHSceneIf::SetContactMode*��p���܂��D

\begin{longtable}{p{.1\hsize}p{.9\hsize}}
\multicolumn{2}{l}{*PHSceneIf*}						\\ \midrule
*void*	& *SetContactMode(PHSolidIf* lhs, PHSolidIf* rhs, int mode)* \\
*void*   & *SetContactMode(PHSolidIf** group, size\_t length, int mode)* \\
*void*   & *SetContactMode(PHSolidIf* solid, int mode)* \\
*void*   & *SetContactMode(int mode)*
\end{longtable}

��Ԗڂ͍���*lhs*��*rhs*�̑΂Ɋւ��ă��[�h��ݒ肵�܂��D��Ԗڂ͔z��*[group, group + length)*�Ɋi�[���ꂽ���̂̑S�g�ݍ��킹�Ɋւ��Đݒ肵�܂��D�O�Ԗڂ͍���*solid*�Ƒ��̑S���̂Ƃ̑g�ݍ��킹�Ɋւ��Đݒ肵�܂��D�l�Ԗڂ̓V�[�����̂��ׂĂ̍��̂̑g�ݍ��킹�Ɋւ��Đݒ肵�܂��D�ݒ�\�ȃ��[�h�͈ȉ��̓��̈�ł��D

\begin{longtable}{p{.3\hsize}p{.7\hsize}}
\multicolumn{2}{l}{*PHSceneDesc::ContactMode*} \\ \midrule
*MODE\_NONE*	   & �������肨��ѐڐG�͌v�Z���s��Ȃ� \\
*MODE\_LCP*     & ����������s���C�S���͌v�Z�@��p���� \\
*MODE\_PENALTY* & ����������s���C�y�i���e�B���͖@��p���� \\
\end{longtable}

�f�t�H���g�ł͂��ׂĂ̍��̑΂Ɋւ���*MODE\_LCP*���I������Ă��܂��D��Ƃ��āC���ʂƂ̐ڐG�ȊO�����ׂăI�t�ɂ���ɂ�
```
// given PHSolidIf* floor

scene->SetContactMode(PHSceneDesc::MODE_NONE);
scene->SetContactMode(floor, PHSceneDesc::MODE_LCP);
```
�Ƃ��܂��D
## �֐ߍ��W�n�V�~�����[�V����
T.B.D.
## �M�A
T.B.D.
## �����A���S���Y���̐ݒ�
�ȉ��ł͕����V�~�����[�V�����̓����ŗp�����Ă���A���S���Y���̏ڍׂȐݒ荀�ڂɂ��Đ������܂��D
### �S���͌v�Z�G���W��
�S���͌v�Z�G���W���́C�֐߂�ڐG�Ȃǂ̍S���𖞑����邽�߂̍S���͂̌v�Z���s���܂��D�S���͌v�Z�G���W���̃N���X��*PHConstraintEngineIf*�ŁC������擾����ɂ͈ȉ��̊֐���p���܂��D*PHConstraintEngineIf*�̃C���^�t�F�[�X���ȉ��Ɏ����܂��D

\begin{longtable}{p{.12\hsize}p{.45\hsize}p{.33\hsize}}
\multicolumn{3}{l}{*PHConstraintEngineIf*}			\\ \midrule
*void*	& *SetVelCorrectionRate(double)*		& �֐ߍS���̌덷�C������ݒ� \\
*double* & *GetVelCorrectionRate()*			& �֐ߍS���̌덷�C�������擾 \\
*void*	& *SetContactCorrectionRate(double)*	& �ڐG�S���̌덷�C������ݒ� \\
*double* & *GetContactCorrectionRate()*		& �ڐG�S���̌덷�C�������擾 \\
\end{longtable}

�덷�C�����Ƃ́C1�X�e�b�v�ōS���덷�ǂ̒��x�C�����邩�������䗦�ŁC�ʏ�$[0, 1]$�̒l��ݒ肵�܂��D�덷�C������$1$�ɂ���ƁC1�X�e�b�v�ōS���덷��$0$�ɂ���悤�ȍS���͂��v�Z����܂����C���U���ۂȂǂ̃V�~�����[�V�����̕s���艻�������X��������܂��D�t�ɏC�����������ڂɐݒ肷��΃V�~�����[�V�����͈��艻���܂����C���덷�����債�܂��D�S���͌v�Z�G���W���́C�����Ŕ����^�̃A���S���Y���ōS���͂��v�Z���܂��D�A���S���Y���̔����񐔂�*PHSceneIf::SetNumIteration*�Őݒ肵�܂��i��\ref{sec_physics_scene}�ߎQ�Ɓj�D*PHSceneIf::SetContactTolerance*�Őݒ�\�ł��D*PHConstraintEngineIf::SetContactCorrectionRate*�Őݒ�\�ł��i��\ref{sec_physics_engine}�ߎQ�Ɓj�D
