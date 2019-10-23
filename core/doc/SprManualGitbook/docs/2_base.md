Base���W���[���͊�{�@�\�̏W���̂ł��D�ȉ��ł͍��ڕʂɂ����ɂ��ĉ�����܂��D
## �s��E�x�N�g�����Z
\begin{table}[t]\caption{Matrix and vector classes}

\begin{tabular}{ll}
\toprule
�N���X��							& �@�\					\\ \midrule
*Vec[2|3|4][f|d]*			& �x�N�g��				\\
*Matrix[2|3|4][f|d]*			& �s��					\\
*Quaternion[f|d]*			& �P�ʃN�H�[�^�j�I��	\\
*Affine[f|d]*				& �A�t�B���ϊ�			\\
*Pose[f|d]*					& 3�����x�N�g���ƃN�H�[�^�j�I���̕����^ \\
\bottomrule
\end{tabular}

\end{table}Table\,\ref{table_matrix}�ɂ悭�g����s��E�x�N�g���N���X�������܂��D�����̐����̓x�N�g����s��̃T�C�Y��\���C*f*�C*d*�͂��ꂼ��*float*�^�C*double*�^�ɑΉ����܂��D
### �x�N�g��
�x�N�g���^�͕��̂̈ʒu�⑬�x�C�͂Ȃǂ̕����ʂ�\�����邽�߂ɕp�ɂɎg���܂��D�Ⴆ��*double*�^�̗v�f����Ȃ�3�����x�N�g��*x*���`����ɂ�
```
Vec3d x;
```
�Ƃ��܂��D�v�f�A�N�Z�X��*[]*���Z�q��p���܂��D
```
x[0];    // 0-th element
```
���̑��C*Vec[2|3][f|d]*�ɂ��Ă�*.x*, *.y*, *.z*�ł��v�f�A�N�Z�X�ł��܂��D�C�ӂ̌Œ�T�C�Y�̃x�N�g�����g���܂��D*float*�^��10�����x�N�g����
```
TVector<10, float> x;    // 10-dimensional float vector
```
�Ƃ��܂��D�ϒ��x�N�g����
```
VVector<float> x;
x.resize(10);            // can be resized at any time
```
�Ŏg���܂�.**������*VVector::resize**�ɂ��T�C�Y�ύX���s���Ɗ����̓��e�͔j������܂��̂Œ��ӂ��ĉ������D*��{�I�ȉ��Z�͈�ʂ�T�|�[�g����Ă��܂��D
```
Vec3d a, b, c;
double k;

c = a + b;               // addition
a += b;

c = a - b;               // subtraction
a -= b;

b = k * a;               // multiply vector by scalar
a *= k;

k = x * y;               // scalar product

x % y;                   // vector product (3D vector only)
```
���ׂẴx�N�g���^�ɂ��Ĉȉ��̃����o�֐����g���܂��D
```
a.size();                // number of elements
a.norm();                // norm
a.square();              // square of norm
a.unitize();             // normalize
b = a.unit();            // normalized vector
```

### �s��
�s��͕��s�ړ����]�Ȃǂ̕ϊ���C���̂̊������[�����g��\�����邽�߂Ɏg���܂��D�Ⴆ�΁C*double*�^�̗v�f����Ȃ�$3 \times 3$�s��$A$�͎��̂悤�ɒ�`���܂��D
```
Matrix3d A;
```
�v�f�A�N�Z�X��*[]*���Z�q��p���܂��D
```
x[0][1];    // element at 0-th row, 1-th column
```
�C�ӂ̌Œ�T�C�Y�̍s����g���܂��D��������ɗ�����ɗv�f�����񂵂��s���
```
TMatrixCol<2, 3, float> M;    // column-oriented 2x3 matrix
```
�v�f���s�����ɐ��񂵂��s���
```
TMatrixRow<2, 3, float> M;    // row-oriented 2x3 matrix
```
�ƂȂ�܂��D���Ȃ݂ɂ����قǂ�*Matrix3d*��*TMatrixCol<3,3,double>*�Ɠ����ł��D�σT�C�Y�s���
```
VMatrixCol<float> M;
M.resize(10, 13);             // column-oriented variable matrix
```
�Ŏg���܂��D*VMatrixCol*�ł͗v�f�̓�������ŗ�����ɕ��т܂��D���*VMatrixRow*�ł͍s�����ɗv�f�����т܂��D�s��^�ɂ��Ă��C�x�N�g���^�Ɠ��l�̎l�����Z���T�|�[�g����Ă��܂��D�s��ƃx�N�g���Ԃ̉��Z�͎��̂悤�ɂȂ�܂��D
```
Matrix3d M;
Vec3d a, b;

b = M * a;               // multiplication
```
���ׂĂ̍s��^�ɂ��Ĉȉ��̃����o�֐��ōs������ї񐔂��擾�ł��܂��D
```
M.height();              // number of rows
M.width();               // number of columns
```
2x2, 3x3�s��ɂ��Ă͈ȉ��̐ÓI�����o�֐����p�ӂ���Ă��܂��D
```
Matrix2d N;
Matrix3d M;
double theta;
Vec3d axis;

// methods common to Matrix2[f|d] and Matrix3[f|d]
M = Matrix3d::Zero();        // zero matrix; same as M.clear()
M = Matrix3d::Unit();        // identity matrix
M = Matrix3d::Diag(x,y,z);   // diagonal matrix

N = Matrix2d::Rot(theta);    // rotation in 2D

M = Matrix3d::Rot(theta, 'x');    // rotation w.r.t. x-axis
                                  // one can specify 'y' and 'z' too
M = Matrix3d::Rot(theta, axis);   // rotation along arbitrary vector
```

### �A�t�B���ϊ�
�A�t�B���ϊ��͎�ɃO���t�B�N�X�ɂ�����ϊ����w�肷�邽�߂Ɏg�p���܂��D�A�t�B���ϊ��^*Affine[f|d]*��4x4�s��Ƃ��Ă̋@�\������Ă��܂��D�����Ĉȉ��̃����o�֐����g���܂��D
```
Affinef A;
Matrix3f R;
Vec3f p;

R = A.Rot();           // rotation part
p = A.Trn();           // translation part
```
�܂��C�悭�g�p����A�t�B���ϊ��𐶐�����ÓI�����o���p�ӂ���Ă��܂��D
```
A = Affinef::Unit();            // identity transformation
A = Affinef::Trn(x, y, z);      // translation
A = Affinef::Rot(theta, 'x');   // rotation w.r.t. x-axis
                                // one can specify 'y' and 'z' too
A = Affinef::Rot(theta, axis);  // rotation w.r.t. arbitrary axis
A = Affinef::Scale(x, y, z);    // scaling
```

### �N�H�[�^�j�I��
�N�H�[�^�j�I���͎�ɕ����v�Z�ɂ����鍄�̂̌������]��\�����邽�߂Ɏg���܂��D�N�H�[�^�j�I����4�����x�N�g���̊�{�@�\������Ă��܂��D�v�f�A�N�Z�X��*[]*���Z�q�ɉ����Ĉȉ��̕��@���g���܂��D
```
Quaterniond q;
q.w;                   // same as q[0]
q.x;                   // same as q[1]
q.y;                   // same as q[2]
q.z;                   // same as q[3]
q.V();                 // vector composed of x,y,z elements
```
���Z�͈ȉ��̂悤�ɍs���܂��D�܂��C�N�H�[�^�j�I�����m�̐ς͉�]�̍�����\���܂��D
```
Quaterniond q, q0, q1;
q0 = Quaterniond::Rot(Rad(30.0), 'x');   // 30deg rotation along x-axis
q1 = Quaterniond::Rot(Rad(-90.0), 'y');  // -90deg rotationt along y-axis

q = q1 * q0;
```
���ɁC�N�H�[�^�j�I����3�����x�N�g���Ƃ̐ς́C�x�N�g���̉�]��\���܂��D
```
Vec3d a(1, 0, 0);
Vec3d b = q0 * a;
```
���̂悤�ɁC�N�H�[�^�j�I���͊�{�I�ɉ�]�s��𓯂��悤�Ȋ��o�Ŏg���܂��D*Quaterniond[f|d]*�ɂ͈ȉ��̃����o�֐�������܂��D�܂���]���Ɖ�]�p�x���擾����ɂ�
```
Vec3d axis = q.Axis();        // rotation axis
double angle = q.Theta();     // rotation angle
```
�Ƃ��܂��D�܂��C�t��]��\�������N�H�[�^�j�I���𓾂�ɂ�
```
q.Conjugate();         // conjugate (reverse rotation)

Quaterniond y;
y = q.Conjugated();    // return conjugated quaternion
y = q.Inv();           // return inverse (normalized conjugate)
```
�Ƃ��܂��D*Conjugate*�͂��̃N�H�[�^�j�I�����̂������N�H�[�^�j�I���ɕϊ�����̂ɑ΂��C*Conjugated*�͒P�ʋ����N�H�[�^�j�I����Ԃ��܂��D*Inv*��*Conjugated*�Ƃقړ����ł����C�߂�l�̃m������$1$�ƂȂ�悤�ɐ��K�����s���܂��D��]��\���N�H�[�^�j�I���͗��_��͕K���m������$1$�Ȃ̂Ő��K���͕s�v�ł����C���ۂ͐��l�v�Z�ɂ�����덷�Ŏ���Ƀm����������Ă��邱�Ƃ�����܂��D���̂悤�Ȍ덷��␳���邽�߂ɓK�X���K�����s���K�v������܂��D��]�s��Ƒ��ݕϊ�����ɂ͈ȉ��̂悤�ɂ��܂��D
```
Matrix3d R = Matrix3d::Rot(Rad(60.0), 'z');
q.FromMatrix(R);       // conversion from rotation matrix
q.ToMatrix(R);         // conversion to rotation matrix
```
*FromMatrix*�͓n���ꂽ��]�s��*R*�Ɠ����ȃN�H�[�^�j�I���Ƃ���*q*��ݒ肵�܂��D���*ToMatrix*�́C�Q�Ɠn�����ꂽ*R*��*q*�Ɠ����ȉ�]�s��Ƃ��Đݒ肵�܂��D���l�ɁC�ȉ��̓I�C���[�p�Ƃ̑��ݕϊ����s���܂��D
```
Vec3d angle;
q.ToEuler(angle);      // to Euler angle
q.FromEuler(angle);    // from Euler angle
```
�Ō�ɁC�ȉ��̊֐���2�̃x�N�g���ɑ΂��C�Е��������Е��Ɉ�v�����悤�ȉ�]��\���N�H�[�^�j�I�������߂܂��D��ʂ�2�̃x�N�g������v�������]�͈�ӂł͂���܂��񂪁C*RotationArc*�͗����̃x�N�g���ɒ������鎲�Ɋւ����]�C����΍ŒZ�����̉�]�����߂܂��D
```
Vec3d r0(1, 0, 0), r1(0, 1, 0);
q.RotationArc(r0, r1);    // rotation that maps r0 to r1 
```

### �|�[�Y
�|�[�Y�͈ʒu�ƌ����̕����^�ł��D�����Ƃ��Ă̓A�t�B���ϊ��Ɏ��Ă��܂����C�S����7�̐����ŕ\���ł��邽�߃A�t�B���ϊ������R���p�N�g�ł��D�|�[�Y�͕����v�Z�ł̍��̂̈ʒu�ƌ�����\�����邽�߂Ȃǂɗp���܂��D*Pose[f|d]*�^�̃����o�ϐ���*Pos*��*Ori*��2�݂̂ŁC���ꂼ��|�[�Y�̕��i����(*Vec3[f|d]*)�Ɖ�]����(*Quaternion[f|d]*)�ւ̎Q�Ƃ�Ԃ��܂��D
```
Posed P;
P.Pos() = Vec3d(1, 2, 3);
P.Ori() = Quaterniond::Rot(Rad(45.0), 'x');
Vec3d p = P.Pos();
Quaterniond q = P.Ori();
```

### �����l�ɂ���
*Vec\[2|3|4]\[f|d]*�^�̓[���x�N�g���ɏ���������܂��D*Matrix\[2|3]\[f|d]*�^�����*Affine\[f|d]*�^�͒P�ʍs��ɏ���������܂��D�܂��C*Quaternion\[f|d]*�͍P���ʑ���\���N�H�[�^�j�I���ɏ���������܂��D

## �X�}�[�g�|�C���^
�Q�ƃJ�E���g�ɂ��ƂÂ��X�}�[�g�|�C���^�ł��D�Q�ƃJ�E���g��$0$�ɂȂ����I�u�W�F�N�g�̃������������I�ɉ�����邽�߂Ƀ��[�U���蓮��*delete*�����s�����Ԃ��Ȃ��C���������[�N�̊댯���ጸ�ł��܂��D�Q�ƃJ�E���g�N���X��*UTRefCount*�ł��DSpringhead�̂قƂ�ǂ̃N���X��*UTRefCount*���p�����Ă��܂��D�X�}�[�g�|�C���^�̓e���v���[�g�N���X*UTRef*�ł��D�ȉ��ɗ�������܂��D
```
class A : public UTRefCount{};
UTRef<A> a = new A();
// no need to delete a
```

## ���̑��̋@�\

### UTString
������^�ł��D����ł�std::string�Ɠ����ł��D
### UTTypeDesc
Springhead�̃N���X�������s���^���ł��D
### UTTreeNode
�c���[�\���̊�{�N���X�ł��D
