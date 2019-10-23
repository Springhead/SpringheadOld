
## �T�v
HumanInterface���W���[���́C�n�[�h�E�F�A����̓f�o�C�X�𗘗p���邽�߂̏����n�Ɉˑ����Ȃ��C���^�t�F�[�X��񋟂��܂��D�قƂ�ǂ̏ꍇ�CHumanInterface�̋@�\��Framework���W���[������ăA�N�Z�X���邱�ƂɂȂ�܂��D���̏ꍇ�́C��q����q���[�}���C���^�t�F�[�X�I�u�W�F�N�g��f�o�C�X�̍쐬�����[�U���g�ōs���K�v�͂���܂���D
## HumanInterface SDK
HumanInterface���W���[���̂��ׂẴI�u�W�F�N�g��SDK�N���X*HISdk*�ɂ���ĊǗ�����܂��D*HISdk*�N���X�́C�v���O�����̎��s��ʂ��Ă����P�̃I�u�W�F�N�g�����݂���V���O���g���N���X�ł��D*HISdk*�I�u�W�F�N�g���쐬����ɂ͈ȉ��̂悤�ɂ��܂��D
```
HISdkIf* hiSdk = HISdkIf::CreateSdk();
```
�ʏ킱�̑���̓v���O�����̏��������Ɉ�x�������s���܂��D�܂��CFramework���W���[�����g�p����ꍇ�̓��[�U������*HISdk*���쐬����K�v�͂���܂���D
## �N���X�K�w�ƃf�[�^�\��





\includegraphics[width=.5\hsize]{fig/hiclass.eps}

\caption{HumanInterface class hierarchy}


HumanInterface���W���[���̃N���X�K�w��Fig.\,\ref{fig_hiclass}�Ɏ����܂��D�f�o�C�X�ɂ͎��f�o�C�X�Ɖ��z�f�o�C�X������܂��D���f�o�C�X�͌����̃n�[�h�E�F�A�ɑΉ����C�Ⴆ��Win32�}�E�X�₠�郁�[�J��A/D�ϊ��{�[�h��\�����f�o�C�X������܂��D����C���z�f�o�C�X�͎��f�o�C�X���񋟂���@�\�P�ʂ�\���C�����n�Ɉˑ����܂���D�Ⴆ�΁C1��A/D�ϊ��|�[�g�⒊�ۉ����ꂽ�}�E�X�C���^�t�F�[�X������ɂ�����܂��D��{�I�ɁC���������������Ă̓��[�U�͎��f�o�C�X�ɐG��邱�Ƃ͂Ȃ��C���z�f�o�C�X��ʂ��Ă����̋@�\�𗘗p���邱�ƂɂȂ�܂��D�q���[�}���C���^�t�F�[�X�̓f�o�C�X�������x�Œ��ۉ����ꂽ����C���^�t�F�[�X��񋟂��܂��D




\includegraphics[width=.5\hsize]{fig/humaninterface.eps}

\caption{HumanInterface module data structure}


����HumanInterface���W���[���̃f�[�^�\����Fig.\,\ref{fig_humaninterface}�Ɏ����܂��D*HISdk*�I�u�W�F�N�g�̓q���[�}���C���^�t�F�[�X�v�[���ƃf�o�C�X�v�[���������Ă��܂��D�f�o�C�X�v�[���Ƃ͎��f�o�C�X�̏W�܂�ŁC���ꂼ��̎��f�o�C�X�͂��̋@�\���������̉��z�f�o�C�X�Ƃ��ĊO���ɒ񋟂��܂��D�f�o�C�X�̋@�\���g���ɂ́C

1.  ���f�o�C�X���쐬����
1.  ���f�o�C�X���񋟂��鉼�z�f�o�C�X�ɃA�N�Z�X����

�Ƃ���2�i�K�̎菇�𓥂݂܂��D�ȉ��ɂ���Ɋ֌W����*HISdk*�̊֐����Љ�܂��D

\begin{tabular}{p{.25\hsize}p{.65\hsize}}
*HISdkIf*																		\\ \midrule
*HIRealDeviceIf**	& *AddRealDevice(const IfInfo* ii, const void* desc = NULL)* \\
*HIRealDeviceIf**	& *FindRealDevice(const char* name)* \\
*HIRealDeviceIf**	& *FindRealDevice(const IfInfo* ii)*
\end{tabular}

*AddRealDevice*�͌^���*ii*�ƃf�B�X�N���v�^*desc*���w�肵�Ď��f�o�C�X���쐬���܂��D*FindRealDevice*�͖��O���^�����w�肵�āC�����̎��f�o�C�X���������܂��D���Ƃ��΁C������GLUT��p����L�[�{�[�h�E�}�E�X���f�o�C�X���擾����ɂ�
```
hiSdk->FindRealDevice(DRKeyMouseGLUTIf::GetIfInfoStatic());
```
�Ƃ��܂��D���z�f�o�C�X���擾����ѕԋp������@�ɂ�*HISdk*�������@��*HIRealDevice*�𒼐ڌĂяo�����@��2�ʂ肪����܂��D

\begin{tabular}{p{.25\hsize}p{.65\hsize}}
*HISdkIf*																							\\ \midrule
*HIVirtualDeviceIf** & *RentVirtualDevice(const IfInfo* ii, const char* name, int portNo)*	\\
*bool*				& *ReturnVirtualDevice(HIVirtualDeviceIf* dev)*	\\
\end{tabular}

*RentVirtualDevice*�̓f�o�C�X�v�[�����X�L�������Č^���ɍ��v�����ŏ��̉��z�f�o�C�X��Ԃ��܂��D���f�o�C�X�����肵�����ꍇ��*name*�Ŏ��f�o�C�X�����w�肵�܂��D�܂��C�����̉��z�f�o�C�X��񋟂�����f�o�C�X������܂��D���̏ꍇ�̓|�[�g�ԍ�*portNo*�Ŏ擾���������z�f�o�C�X���w��ł��܂��D�f�o�C�X�̋�����h�����߂ɁC��x�擾���ꂽ���z�f�o�C�X�͗��p����ԂɂȂ�܂��D���p���̃f�o�C�X�͐V���Ɏ擾���邱�Ƃ͂ł��܂���D�g���I������f�o�C�X��*ReturnVirtualDevice*�ŕԋp���邱�Ƃɂ���čĂю擾�\�ɂȂ�܂��D

\begin{tabular}{p{.25\hsize}p{.65\hsize}}
*HIRealDeviceIf*																				\\ \midrule
*HIVirtualDeviceIf**	& *Rent(const IfInfo* ii, const char* name, int portNo)*	\\
*bool*				& *Return(HIVirtualDeviceIf* dev)*
\end{tabular}

������͎��f�o�C�X���璼�ڎ擾�C�ԋp���邽�߂̊֐��ł��D�@�\�͓��l�ł��D
## ���f�o�C�X
Springhead�ł͂������̃��[�J���̃n�[�h�E�F�A�����f�o�C�X�Ƃ��ăT�|�[�g����Ă��܂����C�����n�ɋ����ˑ����镔���ł��邽�ߖ{�h�L�������g�̑ΏۊO�Ƃ��܂��D�����̂�����̓\�[�X�R�[�h�����Ă��������D
## �L�[�{�[�h�E�}�E�X
�L�[�{�[�h����у}�E�X�̋@�\�͕����1�̃N���X�Ƃ��Ē񋟂���Ă��܂��D�L�[�{�[�h�E�}�E�X�̉��z�f�o�C�X��*DVKeyMouse*�ł��D���f�o�C�X�Ƃ��Ă�Win32 API��p����*DRKeyMouseWin32*��GLUT��p����*DRKeyMouseGLUT*������܂��D�񋟂����@�\�ɑ����̍��ق�����̂Œ��ӂ��ĉ������D
### ���z�L�[�R�[�h
Ascii�O�̓���L�[�ɂ͏����n�ˑ��̃L�[�R�[�h�����蓖�Ă��Ă��܂��D���̍����z�����邽�߂Ɉȉ��̃V���{����*DVKeyCode*�񋓌^�Œ�`����Ă��܂��D

\begin{tabular}{p{.3\hsize}p{.6\hsize}}
*DVKeyCode*									\\ \midrule
*ESC*				& �G�X�P�[�v			\\
*F1* - *F12*	& �t�@���N�V�����L�[	\\
*LEFT*				& ��					\\
*UP*					& ��					\\
*RIGHT*				& ��					\\
*DOWN*				& ��					\\
*PAGE\_UP*			& Page Up				\\
*PAGE\_DOWN*			& Page Down				\\
*HOME*				& Home					\\
*END*				& End					\\
*INSERT*				& Insert				\\
\end{tabular}

�K�v�ɉ����ăV���{�����ǉ������\��������܂��̂ŁC���S�ȃ��X�g�̓w�b�_�t�@�C���Ŋm�F���Ă��������D
### �R�[���o�b�N
*DVKeyMouse*����̃C�x���g����������ɂ�*DVKeyMouseCallback*�N���X���p�����C�C�x���g�n���h�����I�[�o���C�h���܂��D*DVKeyMouseCallback*�͂������̃q���[�}���C���^�t�F�[�X�N���X���p�����Ă���ق��C��q����A�v���P�[�V�����N���X*FWApp*���p�����Ă��܂��D

\begin{tabular}{p{.2\hsize}p{.7\hsize}}
*DVKeyMouseCallback*								\\ \midrule
*virtual bool* & *OnMouse(int button, int state, int x, int y)*		\\
\multicolumn{2}{l}{�}�E�X�{�^���v�b�V��/�����[�X}	\\
\\
*virtual bool* & *OnDoubleClick(int button, int x, int y)*			\\
\multicolumn{2}{l}{�_�u���N���b�N}	\\
\\
*virtual bool* & *OnMouseMove(int button, int x, int y, int zdelta)*	\\
\multicolumn{2}{l}{�}�E�X�J�[�\���ړ�/�}�E�X�z�C�[����]}	\\
\\
*virtual bool* & *OnKey(int state, int key, int x, int y)*			\\
\multicolumn{2}{l}{�L�[�v�b�V��/�����[�X}	\\
\end{tabular}

*OnMouse*�̓}�E�X�{�^���̃v�b�V�����邢�̓����[�X���������Ƃ��ɌĂяo����܂��D*button*�̓C�x���g�Ɋ֌W����}�E�X�{�^������т������̓���L�[�̎��ʎq��ێ����C���̒l��*DVButtonMask*�񋓎q�̒l��OR�����ŕ\������܂��D*state*�̓}�E�X�{�^����ԕω��������C*DVButtonSt*�񋓎q�̂����ꂩ�̒l�������܂��D*x*�C*y*�̓C�x���g�������̃J�[�\�����W��\���܂��D��Ƃ��āC���{�^���̃v�b�V���C�x���g����������ɂ͎��̂悤�ɂ��܂��D
```
// inside your class definition ...
virtual bool OnMouse(int button, int state, int x, int y){
    if(button & DVButtonMask::LBUTTON && state == DVButtonSt::DOWN){
        // do something here
    }
}
```
*OnDoubleClick*�̓}�E�X�{�^���̃_�u���N���b�N���������Ƃ��ɌĂ΂�܂��D�����̒�`��*OnMouse*�Ɠ��l�ł��D*OnMouseMove*�̓}�E�X�J�[�\�����ړ����邩�C�}�E�X�z�C�[������]�����ۂɌĂ΂�܂��D*button*�͒��O�̃}�E�X�v�b�V���C�x���g�ɂ�����*OnMouse*�ɓn���ꂽ�̂Ɠ����l�������܂��D*x*, *y*�͈ړ���̃J�[�\�����W�C*zdelta*�̓}�E�X�J�[�\���̉�]�ʂł��D*OnKey*�̓L�[�{�[�h�̃L�[���v�b�V������邩�����[�X���ꂽ�ۂɌĂ΂�܂��D*state*��*DVKeySt*�񋓎q�̒l�������܂��D*key*�̓v�b�V�����邢�̓����[�X���ꂽ�L�[�̉��z�L�[�R�[�h��ێ����܂��D�ȉ��Ɋ֘A����񋓎q�̒�`�������܂��D

\begin{tabular}{p{.3\hsize}p{.6\hsize}}
*DVButtonMask*									\\ \midrule
*LBUTTON*				& ���{�^��				\\
*RBUTTON*				& �E�{�^��				\\
*MBUTTON*				& ���{�^��				\\
*SHIFT*					& Shift�L�[��������		\\
*CONTROL*				& Ctrl�L�[��������		\\
*ALT*					& Alt�L�[��������		\\
\end{tabular}



\begin{tabular}{p{.3\hsize}p{.6\hsize}}
*DVButtonSt*								\\ \midrule
*DOWN*			& �{�^���v�b�V��		\\
*UP*				& �{�^�������[�X		\\
\end{tabular}



\begin{tabular}{p{.3\hsize}p{.6\hsize}}
*DVKeySt*								\\ \midrule
*PRESSED*		& ������Ă���			\\
*TOGGLE\_ON*		& �g�O������Ă���		\\
\end{tabular}


### API�Ƃ��Ē񋟂����@�\
�ȉ���*DVKeyMouse*�̊֐��������܂��D

\begin{tabular}{p{.1\hsize}p{.8\hsize}}
*DVKeyMouseIf*																		\\ \midrule
*void*	& *AddCallback(DVKeyMouseCallback*)* 	\\
*void*	& *RemoveCallback(DVKeyMouseCallback*)* 	\\
*int*	& *GetKeyState(int key)*					\\
*void*	& *GetMousePosition(int\& x, int\& y, int\& time, int count=0)*
\end{tabular}

*AddCallback*�̓R�[���o�b�N�N���X��o�^���܂��D��̉��z�f�o�C�X�ɑ΂��ĕ����̃R�[���o�b�N��o�^�ł��܂��D*RemoveCallback*�͓o�^�ς̃R�[���o�b�N�N���X���������܂��D*GetKeyState*��*DVKeyCode*�Ŏw�肵���L�[�̏�Ԃ�*DVKeySt*�̒l�ŕԂ��܂��D*GetMousePosition*��*count*�X�e�b�v�O�̃}�E�X�J�[�\���̈ʒu���擾����̂ɗp���܂��D������*count*��$0$�ȏ�$63$�ȉ��łȂ���΂Ȃ�܂���D*x*, *y*�ɃJ�[�\�����W���C*time*�Ƀ^�C���X�^���v���i�[����܂��D
### �T�|�[�g�󋵂Ɋւ��钍��
�g�p������f�o�C�X�ɂ���Ă͈ꕔ�̋@�\���񋟂���Ȃ��̂Œ��ӂ��ĉ������D*OnMouseMove*�ɂ����ă}�E�X�z�C�[���̉�]�ʂ��擾����ɂ́C���f�o�C�X�Ƃ���*DRKeyMouseWin32*���g�p���邩�Cfreeglut�ƃ����N���ăr���h����Springhead���*DRKeyMouseGLUT*���g�p����K�v������܂��D*OnKey*�ɂ����ăL�[�̃g�O����Ԃ��擾����ɂ͎��f�o�C�X�Ƃ���*DRKeyMouseWin32*���g�p����K�v������܂��D*GetKeyState*��*DRKeyMouseWin32*�ł̂݃T�|�[�g����܂��D*GetMousePosition*�ɂ����āC�^�C���X�^���v���擾����ɂ�*DRKeyMouseWin32*��p����K�v������܂��D
## �W���C�X�e�B�b�N
�W���C�X�e�B�b�N�̉��z�f�o�C�X��*DVJoyStick*�ł��D���f�o�C�X�Ƃ��Ă�GLUT��p����*DRJoyStickGLUT*�݂̂�����܂��DT.B.D.
## �g���b�N�{�[��





\includegraphics[width=.5\hsize]{fig/hitrackball.eps}

\caption{Trackball}


�g���b�N�{�[���̓L�[�{�[�h�E�}�E�X�ɂ����i�E��]��6���R�x����͂���q���[�}���C���^�t�F�[�X�ł��D�g���b�N�{�[�����g�����Ƃɂ��C�J�����𒍎��_�܂��Ɏ��_�ύX���邱�Ƃ��ł���悤�ɂȂ�܂��D�g���b�N�{�[���𑀍삷����@�ɂ́CAPI�𒼐ڌĂяo�����@�ƁC���z�}�E�X�ɃR�[���o�b�N�o�^������@�̓�ʂ肪����܂��D���l�ɁC�g���b�N�{�[���̏�Ԃ��擾������@�ɂ�API�Ăяo���ƃR�[���o�b�N�o�^�̓�ʂ肪����܂��D���z�}�E�X�ƃg���b�N�{�[������у��[�U�v���O�����̊֌W��\figurename\ref{fig_trackball}�Ɏ����܂��D
### ��]���S�Ɖ�]�p�x
�J�����̈ʒu�ƌ����́C�����_�C�o�x�p�C�ܓx�p����ђ����_����̋����ɂ���Č��܂�܂��D

\begin{tabular}{p{.15\hsize}p{.5\hsize}p{.25\hsize}}
\multicolumn{3}{l}{*HITrackballDesc*}				\\ \midrule
*Vec3f*	&	*target*			& ��]���S		\\
*float*	&	*longitude*		& �o�x[rad]		\\
*float*	&	*latitude*		& �ܓx[rad]		\\
*float*	&	*distance*		& ����			\\
\end{tabular}



\begin{tabular}{p{.15\hsize}p{.75\hsize}}
\multicolumn{2}{l}{*HITrackballIf*}									\\ \midrule
*Vec3f*	& *GetTarget()*							\\
*void* 	& *SetTarget(Vec3f)*						\\
*void* 	& *GetAngle(float\& lon, float\& lat)*	\\
*void* 	& *SetAngle(float lon, float lat)*		\\
*float* 	& *GetDistance()*						\\
*void* 	& *SetDistance(float dist)*				\\
\end{tabular}


### �͈͎w��
�ȉ��̋@�\�Ŋp�x����ы����ɔ͈͐������������܂��D

\begin{tabular}{p{.15\hsize}p{.5\hsize}p{.25\hsize}}
\multicolumn{3}{l}{*HITrackballDesc*}					\\ \midrule
*Vec2f*	&	*lonRange*		& �o�x�͈�			\\
*Vec2f*	&	*latRange*		& �ܓx�͈�			\\
*Vec2f*	&	*distRange*		& �����͈�			\\
\end{tabular}



\begin{tabular}{p{.15\hsize}p{.75\hsize}}
\multicolumn{2}{l}{*HITrackballIf*}									\\ \midrule
*void* 	& *GetLongitudeRange(float\& rmin, float\& rmax)*	\\
*void* 	& *SetLongitudeRange(float rmin, float rmax)*		\\
*void* 	& *GetLatitudeRange(float\& rmin, float\& rmax)*		\\
*void* 	& *SetLatitudeRange(float rmin, float rmax)*			\\
*void* 	& *GetDistanceRange(float\& rmin, float\& rmax)*		\\
*void* 	& *SetDistanceRange(float rmin, float rmax)*			\\
\end{tabular}


### �R�[���o�b�N�o�^


\begin{tabular}{p{.2\hsize}p{.7\hsize}}
\multicolumn{2}{l}{*HITrackballIf*}								\\ \midrule
*DVKeyMouseIf** 	& *GetKeyMouse()*						\\
*void* 			& *SetKeyMouse(DVKeyMouseIf*)*			\\
*void* 			& *SetCallback(HITrackballCallback*)*	\\
\end{tabular}

�g���b�N�{�[�����}�E�X���삷��ɂ�*DVKeyMouse*�N���X�ɃR�[���o�b�N�o�^����K�v������܂��D�R�[���o�b�N�o�^����ɂ�*SetKeyMouse*�C�o�^��̉��z�}�E�X���擾����ɂ�*GetKeyMouse*���Ăт܂��D�܂��C���[�U�v���O�������g���b�N�{�[���ɃR�[���o�b�N�o�^���ď�ԕω��ɔ����ł���悤�ɂ���ɂ́C*HITrackballCallback*�N���X���p�����C*SetCallback*�֐��ɓn���܂��D*HITrackballCallback*�͈ȉ��̒P��̉��z�֐��������܂��D

\begin{tabular}{p{.2\hsize}p{.7\hsize}}
\multicolumn{2}{l}{*HITrackballCallback*}					\\ \midrule
*virtual void* 	& *OnUpdatePose(HITrackballIf* tb)*	\\
\end{tabular}

*OnUpdatePose*�̓g���b�N�{�[���̈ʒu�E�����ɕω���������x�ɌĂ΂�܂��D������*tb*�͌Ăяo�����̃g���b�N�{�[���������܂��D
### �}�E�X�{�^��������
*HITrackball*�͓�����*DVKeyMouseCallback*���p�����܂��D*SetKeyMouse*�ɂ��*DVKeyMouse*�ɃR�[���o�b�N�o�^����ƁC�}�E�X�J�[�\�����ړ����邽�т�*OnMouseMove*�C�x���g�n���h�����Ăяo����C�g���b�N�{�[���̓�����Ԃ��X�V����܂��D�}�E�X�ړ����̃{�^����Ԃɉ����ăg���b�N�{�[���̂ǂ̏�Ԃ��ω����邩�͂�����x�J�X�^�}�C�Y���\�ł��D�ȉ��Ɋ֘A����@�\�������܂��D

\begin{tabular}{p{.15\hsize}p{.35\hsize}p{.4\hsize}}
\multicolumn{3}{l}{*HITrackballDesc*}		\\ \midrule
*int*	& *rotMask*		& ��]����̃{�^��������		\\
*int*	& *zoomMask*		& �Y�[������̃{�^��������		\\
*int*	& *trnMask*		& ���s�ړ�����̃{�^��������	\\
\end{tabular}



\begin{tabular}{p{.15\hsize}p{.75\hsize}}
\multicolumn{2}{l}{*HITrackballIf*}			\\ \midrule
*void* 	& *SetRotMask(int mask)*		\\
*void* 	& *SetZoomMask(int mask)*	\\
*void* 	& *SetTrnMask(int mask)*		\\
\end{tabular}

*rotMask*, *zoomMask*, *trnMask*�͂��ꂼ���]����C�Y�[������C���s�ړ�����Ɋ��蓖�Ă����}�E�X�{�^���ɑΉ�����*OnMouseMove*��*button*�����̒l��\���܂��D�ȉ��ɑΉ��֌W���܂Ƃ߂܂��D

\begin{tabular}{p{.3\hsize}p{.3\hsize}p{.3\hsize}}
\toprule
�}�E�X�ړ�����		& *button*�l		& �ω���		\\ \midrule
���E				& *rotMask*		& �o�x			\\
�㉺				& *rotMask*		& �ܓx			\\
�㉺				& *zoomMask*		& ����			\\
���E				& *trnMask*		& �����_x���W	\\
�㉺				& *trnMask*		& �����_y���W	\\
\bottomrule
\end{tabular}

�f�t�H���g�̃{�^�������Ă͈ȉ��̒ʂ�ł��D

\begin{tabular}{p{.3\hsize}p{.6\hsize}}
*rotMask*	& *LBUTTON*					\\
*zoomMask*	& *RBUTTON*					\\
*trnMask*	& *LBUTTON* + *ALT*	\\
\end{tabular}

���������āC���{�^���h���b�O�ŉ�]����C�E�{�^���h���b�O�ŃY�[������C[ALT]�L�[+���h���b�O�ŕ��s�ړ��ƂȂ�܂��D�Ȃ��C����ł̓}�E�X�̈ړ������Ƃ̑Ή����J�X�^�}�C�Y���邱�Ƃ͂ł��܂���D�܂��C�}�E�X�z�C�[���̉�]�ƃg���b�N�{�[����A��������@�\���������ł��D
### �}�E�X����ɑ΂���ɐ��Ɗ��x
�}�E�X�ړ��ʂƊp�x�ω��ʁC�����ω��ʂƂ̔��W�������L�̋@�\�Őݒ�ł��܂��D

\begin{tabular}{p{.15\hsize}p{.35\hsize}p{.4\hsize}}
\multicolumn{3}{l}{*HITrackballDesc*}							\\ \midrule
*float*	&	*rotGain*		& ��]�Q�C��[rad/pixel]		\\
*float*	&	*zoomGain*		& �Y�[���Q�C��[rad/pixel]	\\
*float*	&	*trnGain*		& ���s�ړ��Q�C��			\\
\end{tabular}



\begin{tabular}{p{.15\hsize}p{.75\hsize}}
\multicolumn{2}{l}{*HITrackballIf*}									\\ \midrule
*float* 	& *GetRotGain()*			\\
*void* 	& *SetRotGain(float g)*	\\
*float* 	& *GetZoomGain()*		\\
*void* 	& *SetZoomGain(float g)*	\\
*float* 	& *GetTrnGain()*			\\
*void* 	& *SetTrnGain(float g)*	\\
\end{tabular}


### �g���b�N�{�[���Ŏ��_�𓮂���
�g���b�N�{�[���̈ʒu�ƌ������J�����ɔ��f����ɂ́C�`�揈���̖`���ňȉ��̂悤�ɂ��܂��D
```
// given GRRenderIf* render
render->SetViewMatrix(trackball->GetAffine().inv());
```

## Spidar
Spidar�̓��C���쓮�^��3���E6���͊o�񎦃q���[�}���C���^�t�F�[�X�ł��DT.B.D.
