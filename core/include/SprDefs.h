/** ��glut�̑����freeglut���g��
	�E���ɗ��R�������ꍇ��freeglut����������
	�E�W���C�X�e�B�b�N�Ȃǂ�freeglut�ɂ����Ȃ��@�\���g�������ꍇ�͕K�v
	�EOpenGL1.0���V�����o�[�W�������g�p�������ꍇ�͕K�v
 */
#define USE_FREEGLUT

/* GLUI�g�p�R�[�h��L��������
 */
#define USE_GLUI

/** �g�p����OpenGL�̃o�[�W����
	������USE_FREEGLUT���`���邱�Ƃ��K�v
 */
#define OPENGL_MAJOR_VERSION 3
#define OPENGL_MINOR_VERSION 0

/** GLEW���g�p
 */
#define USE_GLEW

/** Physics��OpenMP���g�p
 */
//#define USE_OPENMP_PHYSICS

/** Springhead2/closed �̃\�[�X���g�p���邩�ǂ���
	�J���҈ȊO�͖���`�Ƃ��Ă�������
 */
#include "SprUseClosedSrcOrNot.h"

/** use this definition to use functions that use boost::numeric::bindings::lapack.
    see Foundation/UTClapack.h
 */
#define USE_LAPACK
