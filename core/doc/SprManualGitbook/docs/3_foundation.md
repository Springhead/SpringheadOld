Foundation���W���[���͂��ׂĂ�Springhead�N���X�̊�{�N���X���`���܂��D���ʂɎg���Ă������C���[�U��Foundation�̋@�\�𒼐ڗ��p���邱�Ƃ͏��Ȃ��ł��傤�D
## ���s���^���
�i�قƂ�ǁj���ׂĂ�Springhead�I�u�W�F�N�g�͎��s���^���iRTTI�j�������Ă��܂��DC++�ɂ�*dynamic\_cast*�Ȃǂ�RTTI�@�\������܂����C��������啝�Ƀ��b�`�Ȍ^��񂪒񋟂���܂��D���s���^���̃N���X��*IfInfo*�ł��D*IfInfo*�͎��߂ŏЉ��*Object*�N���X����擾�ł��܂��D
## �I�u�W�F�N�g





\includegraphics[width=.5\hsize]{fig/utclass.eps}

\caption{Object class hierarchy}


�قƂ�ǂ��ׂĂ�Springhead�I�u�W�F�N�g��*Object*�N���X����h�����܂��D�I�u�W�F�N�g�͕����̎q�I�u�W�F�N�g�������Ƃ��ł��܂��DSpringhead�̃f�[�^�\���̓I�u�W�F�N�g�������c���[�\���ɂ���ďo���オ���Ă��܂��DFoundation���W���[���ɂ�����*Object*����̃N���X�K�w��Fig.\,\ref{fig_utclass}�Ɏ����܂��D�܂�*Object*�N���X�̎q�I�u�W�F�N�g�̍쐬�E�Ǘ��Ɋ֌W����֐����Љ�܂��D\noindent\begin{tabular}{p{1.0\hsize}}\\*ObjectIf*										\\ \midrule*size\_t NChildObject()*							\\�q�I�u�W�F�N�g�̐����擾����D							\\														\\*ObjectIf* GetChildObject(size\_t pos)*			\\*pos*�Ԗڂ̎q�I�u�W�F�N�g���擾����D			\\														\\*bool AddChildObject(ObjectIf* o)*				\\�I�u�W�F�N�g*o*���q�I�u�W�F�N�g�Ƃ��Ēǉ�����D�������ǉ����ꂽ��*true*�C����ȊO��*false*��Ԃ��D\\														\\*bool DelChildObject(ObjectIf* o)*				\\�I�u�W�F�N�g*o*���q�I�u�W�F�N�g����폜����D�������폜���ꂽ��*true*�C����ȊO��*false*��Ԃ��D\\														\\*void Clear();*									\\�N���A����D												\\\\\end{tabular}�����̊֐��͔h���N���X�ɂ���Ď�������܂��̂ŁC�ǉ��ł���q�I�u�W�F�N�g�̎�ނ␔�Ȃǂ̓N���X���ƂɈقȂ�܂��D�܂��CSpringhead�𕁒ʂɎg�p����͈͓��ł̓��[�U�������̊֐��𒼐ڌĂяo����ʂ͂Ȃ��ł��傤�D�X�g���[���o�͂̂��߂Ɉȉ��̋@�\������܂��D\noindent\begin{tabular}{p{1.0\hsize}}\\*ObjectIf*										\\ \midrule*void Print(std::ostream\& os) const*			\\�I�u�W�F�N�g�̓��e���X�g���[��*os*�ɏo�͂���D	\\\\\end{tabular}*Print*�́C��{�I�ɂ͂��̃I�u�W�F�N�g�̖��O���o�͂��C�q�I�u�W�F�N�g��*Print*���ċA�I�ɌĂяo���܂��D�������h���N���X�ɂ����*Print*�ŏo�͂������e���J�X�^�}�C�Y����Ă���ꍇ�͂��̌���ł͂���܂���D*NamedObject*�͖��O�t���I�u�W�F�N�g�ł��D*NamedObject*�̔h���N���X�ɂ͖��O�𕶎���ŗ^���邱�Ƃ��ł��C���O����I�u�W�F�N�g���������邱�Ƃ��ł��܂��D���O�t���I�u�W�F�N�g�ɂ́C���ڂ̐e�I�u�W�F�N�g�ȊO�ɁC���O���Ǘ����邽�߂̃l�[���}�l�W�����Ή����܂��D\noindent\begin{tabular}{p{1.0\hsize}}\\*NamedObjectIf*									\\ \midrule*const char* GetName()*			\\���O���擾����D						\\\\*void SetName(const char* n)*	\\���O��ݒ肷��D						\\\\*NameManagerIf* GetNameManager()*	\\�l�[���}�l�W�����擾����D					\\\\\end{tabular}���O�t���I�u�W�F�N�g����͂���ɃV�[���I�u�W�F�N�g���h�����܂��D�V�[���I�u�W�F�N�g����͎��Ӄ��W���[���̃I�u�W�F�N�g(*PHSolid*, *GRVisual*�Ȃ�)���h�����܂��D\noindent\begin{tabular}{p{1.0\hsize}}\\*SceneObjectIf*					\\ \midrule*SceneIf* GetScene()*			\\���g����������V�[�����擾����D		\\\\\end{tabular}
## �l�[���}�l�W���ƃV�[��
�l�[���}�l�W���͖��O�t���I�u�W�F�N�g�̃R���e�i�Ƃ��ē����C�����̖��O���Ǘ����܂��D�܂��C�l�[���}�l�W���͂��ꎩ�g���O�t���I�u�W�F�N�g�ł��D\noindent\begin{tabular}{p{1.0\hsize}}\\*NameManagerIf*									\\ \midrule*NamedObjectIf* FindObject(UTString name)*		\\���O��*name*�̃I�u�W�F�N�g���������C������΂��̃I�u�W�F�N�g��Ԃ��D������Ȃ����*NULL*��Ԃ��D					\\\\\end{tabular}�V�[���̓V�[���I�u�W�F�N�g�̃R���e�i�ł��D�V�[���̊�{�N���X��*Scene*�ŁC��������e���W���[���̃V�[��(*PHScene*, *GRScene*, *FWScene*�Ȃ�)���h�����܂��D*Scene*�N���X�͓��ɋ@�\��񋟂��܂���D
## �^�C�}
�^�C�}�@�\��Foundation�Œ񋟂���܂��D�^�C�}�N���X��*UTTimer*�ł��D�^�C�}���쐬����ɂ�
```
UTTimerIf* timer = UTTimerIf::Create();
```
�Ƃ��܂��D*UTTimer*�ɂ͈ȉ���API������܂��D

\begin{tabular}{ll}
*[Get|Set]Resolution*		& ����\�̎擾�Ɛݒ�	\\
*[Get|Set]Interval*			& �����̎擾�Ɛݒ�		\\
*[Get|Set]Mode*				& ���[�h�̎擾�Ɛݒ�	\\
*[Get|Set]Callback*			& �R�[���o�b�N�֐��̎擾�Ɛݒ� \\
*IsStarted*					& �����Ă��邩�ǂ���	\\
*IsRunning*					& �R�[���o�b�N�Ăяo���� \\
*Start*						& �n��	\\
*Stop*						& ��~	\\
*Call*						& �R�[���o�b�N�Ăяo��
\end{tabular}

*SetMode*�Ŏw��ł��郂�[�h�ɂ͈ȉ�������܂��D

\begin{tabular}{ll}
*MULTIEDIA*		& �}���`���f�B�A�^�C�}			\\
*THREAD*		& �Ɨ��X���b�h					\\
*FRAMEWORK*		& Framework���񋟂���^�C�}		\\
*IDLE*			& Framework���񋟂���A�C�h���R�[���o�b�N
\end{tabular}

�}���`���f�B�A�^�C�}��Windows���񋟂��鍂�@�\�^�C�}�ł��D�Ɨ��X���b�h���[�h�ł́C�^�C�}�p�̃X���b�h�����s����*Sleep*�֐��ɂ����������䂳��܂��D*FRAMEWORK*��*IDLE*���[�h�𗘗p����ɂ�*FWApp*��*CreateTimer*�֐���p����K�v������܂��D��{�I��*FRAMEWORK*���[�h�ł�GLUT�̃^�C�}�R�[���o�b�N���g���C*IDLE*���[�h�ł�GLUT�̃A�C�h���R�[���o�b�N���g���܂��DFramework���W���[����*FWApp*�𗘗p����ꍇ�́C*FWApp*��*CreateTimer*�֐��𗘗p��������֗��ł��傤�D
## ��Ԃ̕ۑ��E�Č�
�V�~�����[�V�������s���ƁA�V�[�����\������I�u�W�F�N�g�̏�Ԃ��ω�����B���鎞���ł̏�Ԃ�ۑ����Ă����A�Č����邱�Ƃ��ł���ƁA���X�e�b�v�O�ɖ߂�����A����X�e�b�v�̃V�~�����[�V�������A�͂��������ꍇ�Ɖ����Ȃ��ꍇ�Ŕ�ׂ���Ƃ�������Ƃ��ł���BSpringhead�ł́A*ObjectStatesIf*��p���邱�ƂŁA�ȉ��̂悤�ɃV�[���S�̂̏�Ԃ��܂Ƃ߂ă�������ɕۑ��A�Č����邱�Ƃ��ł���B
```
	PHSceneIf* phScene;
	�ȗ��FphScene�i�����V�~�����[�V�����̃V�[���j�̍\�z
	UTRef<ObjectStatesIf> states;
	states = ObjectStatesIf::Create();	// ObjectStates�I�u�W�F�N�g�̍쐬
	states->AllocateState(phScene);		// �ۑ��p�̃������m��
	states->SaveState(phScene);			// ��Ԃ̕ۑ�
	phScene->Step();					// ���̃V�~�����[�V������i�߂�
	�ȗ��F�����x�̎擾�Ȃ�
	states->LoadState(phScene);			// ��Ԃ̍Č�
	states->ReleaseState();				// �������̊J��
	�ȗ��F�͂�������Ȃǂ̏���
	phScene->Step();					// �{�Ԃ̃V�~�����[�V������i�߂�
```

### �ۑ��E�Č��̃^�C�~���O
Springhead�̃V�[��(PHScene��CRScene)�́A�����̃G���W��(PHEngine��CREngine�̔h���N���X)���Ăяo�����ƂŁA�V�~�����[�V������i�߂�B�V�[���́A�G���W���̌Ăяo�����ȊO�̃^�C�~���O�ł���΂��ł���Ԃ�ۑ��E�Č����邱�Ƃ��ł���B
### �V�[���\���ύX�̐���
��ԕۑ��p�̃������́A�V�[���̍\���Ɉˑ����Ă���B*AllocateState(), SaveState(), LoadState()*�����łȂ��A*ObjectStatesIf::ReleaseState()*���ˑ�����̂ŁA*ObjectIf::AddChildObject()*�Ȃǂ�API�ɂ���ăV�[���̍\����ω������Ă��܂��ƁA�ۑ��E�Č������łȂ��������̊J�����ł��Ȃ��Ȃ�B�ύX�O�ɊJ�����邩�A�V�[���\����߂��Ă���J������K�v������B
