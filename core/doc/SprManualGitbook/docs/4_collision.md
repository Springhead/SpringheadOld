
## �T�v
Collision���W���[���͕����v�Z�̊�b�ƂȂ�Փ˔���@�\��񋟂��܂��D������Collision���W���[����Physics���W���[���̃T�u���W���[���ƂȂ��Ă���C���҂͖��ڂɈˑ����Ă��܂��D���[�U�͎�Ƃ��č��̂ɏՓ˔���p�`������蓖�Ă�ۂ�Collision���W���[���̋@�\�𗘗p���邱�ƂɂȂ�܂��D




\includegraphics[width=.4\hsize]{fig/cdclass.eps}

\caption{Class hierarchy of Collision module}


Collision���W���[���̃N���X�K�w��Fig.\,\ref{fig_cdclass}�Ɏ����܂��D�Փ˔���`��͂��ׂ�`CDShape`����h�����܂��D�A���S���Y���̐�����C�`��͂��ׂēʌ`��łȂ���΂Ȃ�܂���D
## �`��̍쐬
�Փ˔���`��͎��̎菇�ō쐬�E�o�^���܂��D

1.  �`����쐬����
1.  ���̂֌`���ǉ�����
1.  �`��̈ʒu��ݒ肷��

�ȉ��ɏ���ǂ��Đ������܂��D�܂��`����쐬����ɂ͎��̂悤�ɂ��܂��D
```
// given PHSdkIf* phSdk

CDBoxDesc desc;
desc.boxsize = Vec3d(1.0, 1.0, 1.0);

CDBoxIf* box = phSdk->CreateShape(desc)->Cast();
```
�Փ˔���`��̃I�u�W�F�N�g��Physics���W���[�����Ǘ����܂��D���̂��߁C�`����쐬����ɂ�`PHSdk`�N���X��`CreateShape`�֐����g���܂��D`PHSdk`�ɂ��Ă�\ref{chap_physics}�͂��Q�Ƃ��Ă��������D�`����쐬����ɂ́C�܂���ނɉ������f�B�X�N���v�^���쐬���C���@�Ȃǂ̃p�����[�^��ݒ肵�܂��D���̗�ł͒����̃N���X`CDBox`�̃f�B�X�N���v�^���쐬���Ĉ�ӂ�$1.0$�̗����̂��쐬���܂��D�f�B�X�N���v�^���w�肵��`CreateShape`���Ăяo���ƁC�Ή������ނ̌`�󂪍쐬����C���̃C���^�t�F�[�X���Ԃ���܂��D�������߂�l�͌`��̊��N���X�ł���`CDShape`�̃C���^�t�F�[�X�ł��̂ŁC�h���N���X�i�����ł�`CDBox`�j�̃C���^�t�F�[�X�𓾂�ɂ͏�̂悤��`Cast`�֐��œ��I�L���X�g����K�v������܂��D�`����쐬������C���ɂ��̌`���^���������̂ɓo�^���܂��D
```
// given PHSolidIf* solid

solid->AddShape(box);         // first box
```
���̃N���X`PHSolid`�ɂ��Ă�\ref{chap_physics}�͂��Q�Ƃ��Ă��������D�����ŏd�v�Ȃ��Ƃ́C��x�쐬�����`���1�̍��̂ɂ����ł��o�^�ł��C�܂��قȂ镡���̍��̂ɂ��o�^�ł���Ƃ������Ƃł��D�܂�C�����`��𕡐��̍��̊Ԃŋ��L���邱�ƂŁC�`��̍쐬�R�X�g�⃁���������}���邱�Ƃ��ł��܂��D`AddShape`�֐��œo�^��������̌`��́C���̂̃��[�J�����W�n�̌��_�Ɉʒu���Ă��܂��D�����ύX�������ꍇ��`SetShapePose`�֐����g���܂��D
```
solid->AddShape(box);         // second box
solid->AddShape(box);         // third box 

// move first shape 1.0 in x-direction
solid->SetShapePose(0, Posed(Vec3d(1.0, 0.0, 0.0), Quaterniond());

// rotate second shape 30 degrees along y-axis
solid->SetShapePose(1, Posed(Vec3d(),
                    Quaterniond::Rot(Rad(30.0), 'y')));
```
`SetShapePose`�̑�1�����͑��삷��`��̔ԍ��ł��D�ŏ���`AddShape`�����`��̔ԍ���$0$�ŁC`AddShape`���邽�т�$1$�������܂��D�`��̈ʒu������͍��̂̃��[�J�����W�n�Ŏw�肵�܂��D�܂��C�`��̈ʒu�E�������擾����ɂ�`GetShapePose`�֐����g���܂��D�ȉ��ł�Springhead�ŃT�|�[�g����Ă���`�����ޕʂɉ�����܂��D
### ������





\includegraphics[width=.4\hsize]{fig/cdbox.eps}

\caption{Box geometry}


������(Fig.\,\ref{fig_cdbox})�̃N���X��*CDBox*�ł��D

\begin{tabular}{lll}
\multicolumn{3}{l}{*CDBoxDesc*}					\\ \midrule
*Vec3f*	&	*boxsize*	& �e�ӂ̒��� 	\\
\\
\multicolumn{3}{l}{*CDBoxIf*}					\\ \midrule
\multicolumn{2}{l}{*Vec3f GetBoxSize()*}			\\
\multicolumn{2}{l}{*void SetBoxSize(Vec3f)*}		\\
\end{tabular}


### ��





\includegraphics[width=.4\hsize]{fig/cdsphere.eps}

\caption{Sphere geometry}


��(Fig.\,\ref{fig_cdsphere})�̃N���X��`CDSphere`�ł��D

\begin{tabular}{lll}
\multicolumn{3}{l}{*CDSphereDesc*}				\\ \midrule
*float*	&	*radius*	& ���a 				\\
\\
\multicolumn{3}{l}{*CDSphereIf*}					\\ \midrule
\multicolumn{2}{l}{*float GetRadius()*}			\\
\multicolumn{2}{l}{*void SetRadius(float)*}		\\
\end{tabular}


### �J�v�Z��





\includegraphics[width=.4\hsize]{fig/cdcapsule.eps}

\caption{Capsule geometry}


�J�v�Z��(Fig.\,\ref{fig_cdcapsule})�̃N���X��`CDCapsule`�ł��D�J�v�Z���͉~���̗��[�ɔ����������`�����Ă��܂��D

\begin{tabular}{lll}
\multicolumn{3}{l}{*CDCapsuleDesc*}				\\ \midrule
*float*	&	*radius*	& �����̔��a 		\\
*float*	&	*length* & �~���̒���		\\
\\
\multicolumn{3}{l}{*CDCapsuleIf*}				\\ \midrule
\multicolumn{2}{l}{*float GetRadius()*}			\\
\multicolumn{2}{l}{*void SetRadius(float)*}		\\
\multicolumn{2}{l}{*float GetLength()*}			\\
\multicolumn{2}{l}{*void SetLength(float)*}		\\
\end{tabular}


### �ۃR�[��





\includegraphics[width=.4\hsize]{fig/cdroundcone.eps}

\caption{Round cone geometry}


�ۃR�[��(Fig.\,\ref{fig_cdroundcone})�̃N���X��`CDRoundCone`�ł��D�ۃR�[���̓J�v�Z���̗��[�̔��a����Ώ̂ɂȂ������̂ł��D

\begin{tabular}{lll}
\multicolumn{3}{l}{*CDRoundConeDesc*}			\\ \midrule
*Vec2f*	&	*radius*	& �e�����̔��a		\\
*float*	&	*length* & �����Ԃ̋���		\\
\\
\multicolumn{3}{l}{*CDRoundConeIf*}				\\ \midrule
\multicolumn{2}{l}{*Vec2f GetRadius()*}			\\
\multicolumn{2}{l}{*void SetRadius(Vec2f)*}		\\
\multicolumn{2}{l}{*float GetLength()*}			\\
\multicolumn{2}{l}{*void SetLength(float)*}		\\
\multicolumn{2}{l}{*void SetWidth(Vec2f)*}		\\
\end{tabular}

*SetWidth*�֐��́C�ۃR�[���̑S����ۑ������܂ܔ��a��ύX���܂��D
### �ʃ��b�V��





\includegraphics[width=.4\hsize]{fig/cdconvexmesh.eps}

\caption{Convex mesh geometry}


�ʃ��b�V��(Fig.\,\ref{fig_cdconvexmesh})�̃N���X��`CDConvexMesh`�ł��D�ʃ��b�V���Ƃ͉��݂⌊�������Ȃ����ʑ̂ł��D���_���W���w�肷�邱�ƂŎ��R�Ȍ`���쐬���邱�Ƃ��ł��܂��D

\begin{tabular}{lll}
\multicolumn{3}{l}{*CDConvexMeshDesc*}						\\ \midrule
*vector<Vec3f>*	&	*vertices*	& ���_���W�̔z��	\\
\\
\multicolumn{3}{l}{*CDConvexMeshIf*}					\\ \midrule
\multicolumn{2}{l}{*Vec3f* GetVertices()*}			& ���_�z��̐擪�A�h���X	\\
\multicolumn{2}{l}{*int NVertex()*}					& ���_��					\\
\multicolumn{2}{l}{*CDFaceIf* GetFace(int i)*}		& $i$�Ԗڂ̖�				\\
\multicolumn{2}{l}{*int NFace()*}					& �ʐ�						\\
\end{tabular}

�ʃ��b�V�����쐬�����ہC*CDConvexMeshDesc::vertices*�Ɋi�[���ꂽ���_������ŏ��̓ʑ��ʑ́i�ʕ�j���쐬����܂��D���ʑ̖̂ʂ�\��*CDFace*�̃C���^�t�F�[�X���ȉ��Ɏ����܂��D

\begin{tabular}{lll}
\multicolumn{3}{l}{*CDFaceIf*}						\\ \midrule
\multicolumn{2}{l}{*int* GetIndices()*}				& ���_�C���f�b�N�X�z��̐擪�A�h���X	\\
\multicolumn{2}{l}{*int NIndex()*}					& �ʂ̒��_��							\\
\end{tabular}

*NIndex*�͖ʂ��\�����钸�_�̐���Ԃ��܂��i�ʏ�$3$��$4$�ł��j�D�ʂ͒��_�z��𒼐ڕۗL�����C�C���f�b�N�X�z��Ƃ��ĊԐړI�ɒ��_���Q�Ƃ��܂��D���������āC�ʂ̒��_���W�𓾂�ɂ�
```
// given CDConvexMeshIf* mesh
CDFaceIf* face = mesh->GetFace(0);        // get 0-th face
int* idx = face->GetIndices();
Vec3f v = mesh->GetVertices()[idx[0]];    // get 0-th vertex
```
�Ƃ��܂��D
## �����̎w��
�`��ɂ͖��C�W���⒵�˕Ԃ�W���Ȃǂ̕������w�肷�邱�Ƃ��ł��܂��D�`��̊�{�N���X�ł���*CDShape*�̃f�B�X�N���v�^*CDShapeDesc*��*PHMaterial*�^�̕ϐ�*material*�������Ă��܂��D

\begin{tabular}{lll}
\multicolumn{3}{l}{*PHMaterial*}							\\ \midrule
*float*	&	*density*		& ���x				\\
*float*	&	*mu0*			& �Î~���C�W��		\\
*float*	&	*mu*				& �����C�W��		\\
*float*	&	*e*				& ���˕Ԃ�W��		\\
*float*	&	*reflexSpring*	& ���˕Ԃ�o�l�W���i�y�i���e�B�@�j	\\
*float*	&	*reflexDamper*	& ���˕Ԃ�_���p�W���i�y�i���e�B�@�j\\
*float*	&	*frictionSpring*	& ���C�o�l�W���i�y�i���e�B�@�j	\\
*float*	&	*frictionDamper*	& ���C�_���p�W���i�y�i���e�B�@�j\\
\end{tabular}

�`��쐬��ɕ������w�肷��ɂ�*CDShapeIf*�̊֐����g���܂��D

\begin{tabular}{lll}
\multicolumn{3}{l}{*CDShapeIf*}						\\ \midrule
\multicolumn{2}{l}{*void SetDensity(float)*}				& \\
\multicolumn{2}{l}{*float GetDensity()*}					& \\
\multicolumn{2}{l}{*void SetStaticFriction(float)*}		& \\
\multicolumn{2}{l}{*float GetStaticFriction()*}			& \\
\multicolumn{2}{l}{*void SetDynamicFriction(float)*}		& \\
\multicolumn{2}{l}{*float GetDynamicFriction()*}			& \\
\multicolumn{2}{l}{*void SetElasticity(float)*}			& \\
\multicolumn{2}{l}{*float GetElasticity()*}				& \\
\multicolumn{2}{l}{*void SetReflexSpring(float)*}		& \\
\multicolumn{2}{l}{*float GetReflexSpring()*}			& \\
\multicolumn{2}{l}{*void SetReflexDamper(float)*}		& \\
\multicolumn{2}{l}{*float GetReflexDamper()*}			& \\
\multicolumn{2}{l}{*void SetFrictionSpring(float)*}		& \\
\multicolumn{2}{l}{*float GetFrictionSpring()*}			& \\
\multicolumn{2}{l}{*void SetFrictionDamper(float)*}		& \\
\multicolumn{2}{l}{*float GetFrictionDamper()*}			& \\
\end{tabular}

�����Ɋ�Â����ڐG�͂̋�̓I�Ȍv�Z�@�ɂ��Ă͑�\ref{sec_physics_contact}�߂��Q�Ƃ��ĉ������D
## �􉽏��̌v�Z
�`��Ɋւ���􉽏����v�Z����֐����Љ�܂��D

\begin{tabular}{lll}
\multicolumn{3}{l}{*CDShapeIf*}							\\ \midrule
\multicolumn{2}{l}{*float CalcVolume()*}					& �̐ς��v�Z		\\
\multicolumn{2}{l}{*Vec3f CalcCenterOfMass()*}			& ���ʒ��S���v�Z	\\
\multicolumn{2}{l}{*Matrix3f CalcMomentOfInertia()*}		& �����s����v�Z	\\
\end{tabular}

*CalcVolume*�͌`��̑̐ς��v�Z���܂��D�̐ςɖ��x�i*GetDensity*�Ŏ擾�j���|����Ύ��ʂ������܂��D*CalcCenterOfMass*�֐��́C�`��̃��[�J�����W�n�ŕ\���ꂽ���ʒ��S�̍��W���v�Z���܂��D*CalcMomentOfInertia*�֐��́C�`��̃��[�J�����W�n�ŕ\���ꂽ���ʒ��S�Ɋւ��銵���s����v�Z���܂��D�������C���x��$1$�Ƃ����ꍇ�̒l���Ԃ���܂��̂ŁC���ۂ̊����s��𓾂�ɂ͖��x���|����K�v������܂��D
