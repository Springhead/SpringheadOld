/*
 *  Copyright (c) 2003-2006, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
#ifndef PTMATRIX_TMATRIX_H
#define PTMATRIX_TMATRIX_H

/**	\addtogroup gpLinearAlgebra	*/
//@{
/** 
	@page PTM �|�[�^�u�� �e���v���[�g �s��N���X���C�u����
	
	@author ���J�� ����

	@date 2001�N6��10��,2003�N10��20���X�V

	@section introM �͂��߂�
		���̃h�L�������g�̓|�[�^�u�� �e���v���[�g �s��N���X���C�u����
		�̃h�L�������g�ł��D
		�|�[�^�u�� �e���v���[�g �s��N���X���C�u�����́C
		�e���v���[�g�ɂ��M�~N�s��̃N���X���C�u�����ł��D
		�s��̃T�C�Y���e���v���[�g�Ŏ��o�[�W�����ƕϐ��Ŏ��o�[�W����������܂��D
		
	@section specM ���̃��C�u�����̓���
	@subsection tmpM �e���v���[�g�ŉ���
		�e���v���[�g�ł́C�S�Ă��e���v���[�g�ŐÓI�ɉ������Ă��܂��D
		�s��̃T�C�Y��|�C���^�Ȃǂ�ێ����邽�߂̊Ǘ��̈�������܂���D
		���̂��߁C
		<ul>
			<li> �s��̈ꕔ(�����s��C�x�N�g���C�s�x�N�g���C��x�N�g��)�Ȃǂ�
				���ڎQ�Ƃ��邱�Ƃ��ł���(������\)�D
			<li> �z����L���X�g���čs��Ƃ��Ďg�p���邱�Ƃ��\�D
			<li> �s��̊|���Z�ȂǂŁC�s��̃T�C�Y������Ȃ��ꍇ�C�R���p�C������
				�R���p�C�����G���[���o�͂���D
			<li> �s��̃T�C�Y�𓮓I�ɕύX���邱�Ƃ��ł��Ȃ��D
		</ul>
		�Ƃ����������������܂��D
	@subsection portM �ڐA��
		�����n�ˑ������̑����e���v���[�g�@�\�����p���Ă��Ȃ���C�S�@�\���C
		3�̃R���p�C���Ŏg�p�ł��܂��D�T�|�[�g���Ă���R���p�C���́C
		<ul>
			<li> CL (MS Visual C++ 6.0)
			<li> bcc32(Borland C++ 5.5.1)	���߂�Ȃ����܂����m�F�ł��D�������삵�܂���D
			<li> gcc(GNU c compiler 2.95.3-5)
		</ul>
		�ł��D
	@subsection why �V���ɃN���X���C�u�������쐬�������R
		���łɑ����̍s�񃉃C�u����������Ȃ���C�V���ɍ쐬�������R�́C
		- TNT�CMTL �̍s��͊Ǘ��̈���������Ɏ����߁C�z����L���X�g����
			�s��Ƃ��Ďg�p���邱�Ƃ��ł��Ȃ��D
		- Blitz �� TinyMatrix, TinyVector �������CVisual C++ ��
			�g�p�ł��Ȃ��D
		- ���̒m�����C�����s��C�����x�N�g���ւ̎Q�Ƃ�Ԃ��s�񃉃C�u����
			�͑��݂��Ȃ��D

	����ł��D
	
	@section ptm_usage �g����
	�|�[�^�u�� �e���v���[�g �s��N���X���C�u�����́C�w�b�_�t�@�C����������Ȃ�
	�N���X���C�u�����Ȃ̂�, TMatrix.h, TMatrixUtility.h, TVector.h
	�𓯂��t�H���_�ɓ���Ă����C.cpp�t�@�C������w�b�_���C���N���[�h���邾����
	�g�p�ł��܂��D
	@subsection sampleM �T���v��
		�ȒP�ȃT���v���ł��D�K���ȃt�@�C����(���Ƃ��� sample.cpp) �ŕۑ�����
		�R���p�C�����Ă��������D�R���p�C�����邽�߂ɂ́C
		<DL>
		<DT> visual C++ �̏ꍇ
		<DD> cl -GX sample.cpp
		<DT> gcc�̏ꍇ
		<DD> g++ sample.cpp
		<DT> bcc �̏ꍇ
		<DD> bcc32 sample.cpp
		</DL>
	�Ƃ��Ă��������D
	@verbatim
#include "TMatrix.h"    //  �s�񃉃C�u�����̃C���N���[�h����D
#include <iostream>
using namespace PTM;    //  �s��N���X��PTM���O��Ԃ̒��Ő錾����Ă���D
void main(){
    TMatrixRow<2,2,float> mat;     //  2�s2��̍s���錾
    mat[0][0] = 1;  mat[0][1] = 2;
    mat[1][0] = 3;  mat[1][1] = 4;
    TVector<2,float> vec;       //  2�����̃x�N�g����錾
    vec[0] = 1; vec[1] = 0;
    std::cout << mat;
    std::cout << vec << std::endl;
    std::cout << mat * vec << std::endl;	//	�|���Z
    std::cout << mat + mat << std::endl;	//	�����Z
    std::cout << mat - mat << std::endl;	//	�����Z
    std::cout << mat.trans() << std::endl;	//	�]�u
    std::cout << mat.inv() << std::endl;	//	�t�s��
}
@endverbatim
	@subsection vecfunc �x�N�g���̋@�\
	���̉��Z���ł��܂��D
	<ul>
	<li> +:�a, -:��, *:����/�萔�{, /:�萔����1
	<li> ==:��r, =:���
	<li> <<:�o��, >>:����
	<li> %:�O��(2�E3�����̂�)
	</ul>
	���̃����o�֐��������܂��D
	<ul>
	<li> unit(): �������������P�ʃx�N�g����Ԃ��D
	<li> norm(): �x�N�g���̑傫��(�m����)��Ԃ��D
	<li> sub_vector(): �����x�N�g���ւ̎Q�Ƃ�Ԃ��D
	</ul>
	�ϐ��ł̓T�C�Y�̕ύX���ł��܂��D
	<ul>
	<li> resize(int h, int w):	�T�C�Y�̕ύX
	<li> height():	�������s��̍s��
	<li> width():	�����s��̗�
	</ul>
	@subsection matfunc �s��̋@�\
	���̉��Z���ł��܂��D
	<ul>
		<li> +:�a, -:��, *:��/�萔�{, /:�萔����1
		<li> ==:��r, =:���
		<li> <<:�o��, >>:����
	</ul>
	���̃����o�֐��������܂��D
	<ul>
		<li> det(): �s�񎮂�Ԃ��D
		<li> inv(): �t�s���Ԃ��D
		<li> gauss(): �K�E�X�̏����@�ŕ������������D
		<li> sub_matrix(): �����s��ւ̎Q�Ƃ�Ԃ��D
		<li> row(): �s�x�N�g���ւ̎Q�Ƃ�Ԃ��D
		<li> col(): ��x�N�g���ւ̎Q�Ƃ�Ԃ��D
	</ul>
		sub_matrix()��row()�ɂ͒l�������邱�Ƃ��ł��܂��D
		@verbatim
	TMatrixRow<3,3,float> mat; TVector<3, float> vec;
	mat.row() = vec;@endverbatim
	@section pub �Ĕz�z�̏���
	�Ĕz�z����ꍇ�́C������҂̏����E�A��������ρE�폜���Ȃ��ł��������D
	���I�ȉ�ЂŃ\�t�g�E�G�A�������l�ɂ����R�Ɏg�p�ł���悤�ɂ�����
	�̂ŁCGPL�ELGPL�ɂ��܂���ł����D
	�������GPL�ELGPL�ɉ��ς��čĔz�z���Ă��������Ă����\�ł��D
	@section support �T�|�[�g
	�o�O�C�s��C�Ӗ��s���ȃR���p�C���G���[�Ȃǂ��������ꍇ�́C
	���J�� ���� (hase@hi.pi.titech.ac.jp) �܂ł��A�����������D
	�ł������T�|�[�g���C���ǂ����C�u�����ɂ��Ă�������ł��D<br>
	���ɂ��̃��C�u�����̓e���v���[�g�N���X���C�u�����Ȃ̂ŁC�g�p���ɁC
	�����̓��삪����Ȃ��ƈӖ��̂킩��Ȃ��R���p�C���G���[�ɏo����Ƃ�
	����Ǝv���܂��D���̂悤�Ȗ��ɂ͑Ή��������ł��̂ŁC�܂��͂��A�����������D
	@section thanksM �ӎ�
	LU�����C�t�s��C�K�E�X�����@�Ȃǂ̍s��v�Z�A���S���Y���́C<br>
    �u�w�b����ɂ��ŐV�A���S���Y�����T�x�S�\�[�X�R�[�h�v<br>
    ftp://ftp.matsusaka-u.ac.jp/pub/algorithms<br>
	���� ���F Haruhiko Okumura<br>
	�����ς��ė��p�����Ă��������܂����D
	���R�ɃR�[�h���g�킹�Ă��������āC���肪�Ƃ��������܂��D	*/
//-----------------------------------------------------------------------------
/**	@file TMatrix.h
	�e���v���[�g�ɂ��N�~M�s��^�̒�`.
	�v�f�̌^�ƃT�C�Y���e���v���[�g�̈����ɂ��邱�ƂŁC
	�Ǘ������������Ɏ������ɁC��ʂ̍s��������D
	�z����L���X�g���čs��ɂ��邱�Ƃ��ł���D
	�����s���s�����s���x�N�g���Ƃ��Ď��o�����Ƃ��ł���D
	sparse matrix �ɂ͑Ή����Ă��Ȃ��D										*/
//------------------------------------------------------------------------------

#include "TVector.h"

///	Portable Template Matrix���C�u�����̖��O���
namespace PTM{;

#ifdef _WIN32
 #pragma pack(push, 4)
 #ifdef _DEBUG
  #pragma optimize ("awgity", on)
  #pragma auto_inline(on)
  #pragma inline_recursion(on)
 #endif
#endif

/**	�����s��^�쐬�̂��߂̃��[�e�B���e�B�[�N���X.
	TSubMatrixDim<top, left, height, width> �Ǝ������w��ł���B*/
template <size_t T, size_t L, size_t H, size_t W>
class TSubMatrixDim{
public:
	DIMDEF(DIMENC(T),		TOP);
	DIMDEF(DIMENC(L),		LEFT);
	DIMDEF(DIMENC(H),		HEIGHT);
	DIMDEF(DIMENC(W),		WIDTH);
};
/**	�����s��^�쐬�̂��߂̃��[�e�B���e�B�[�N���X.
	TMatDim<height, width> �Ǝ������w��ł���B	*/
template <size_t H, size_t W>
class TMatDim{
public:
	DIMDEF(DIMENC(H),		HEIGHT);
	DIMDEF(DIMENC(W),		WIDTH);
};

template <size_t H, size_t W, class OD> class TSubMatrixRow;
template <class T, class Z=T, class U=Z> class ESubMatrixRow;
template <size_t H, size_t W, class OD> class TSubMatrixCol;
template <class T, class Z=T, class U=Z> class ESubMatrixCol;
///	�s�x�N�g���̊�{�^	�T�C�Y�F�e���v���[�g
template <class desc>
class TMakeSubMatrixRow{
public:
	typedef TYPENAME desc::element_type element_type;
	typedef TYPENAME desc::exp_type exp_type;
	exp_type& exp(){ return *(exp_type*)this;}
	const exp_type& exp() const { return *(exp_type*)this;}
	///	@name �����s��
	//@{
	///	�����s��i�e���v���[�g�Łj
	template <class SUB>
		TSubMatrixRow<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>& sub_matrix(SUB){
		return (TSubMatrixRow<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>&)exp().item(DIMDEC(SUB::TOP), DIMDEC(SUB::LEFT));
	}
	template <class SUB>
		const TSubMatrixRow<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>& sub_matrix(SUB) const {
		return (TSubMatrixRow<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>&)exp().item(DIMDEC(SUB::TOP), DIMDEC(SUB::LEFT));
	}
	///	�����s��i�T�C�Y�����e���v���[�g�Łj
	template <class SUB>
		TSubMatrixRow<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>& sub_matrix(size_t t, size_t l, SUB){
		return (TSubMatrixRow<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>&)exp().item(t,l);
	}
	template <class SUB>
		const TSubMatrixRow<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>& sub_matrix(size_t t, size_t l, SUB) const {
		return (TSubMatrixRow<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>&)exp().item(t,l);
	}
	///	�����s��i�ϐ��Łj
	ESubMatrixRow<element_type> vsub_matrix(int t, int l, int h, int w){
		return ESubMatrixRow<element_type>(h, w, exp().stride(), &exp().item(t,l));
	}
	//@}
};
///	��x�N�g���̊�{�^	�T�C�Y�F�e���v���[�g
template <class desc>
class TMakeSubMatrixCol{
public:
	typedef TYPENAME desc::element_type element_type;
	typedef TYPENAME desc::exp_type exp_type;
	exp_type& exp(){ return *(exp_type*)this;}
	const exp_type& exp() const { return *(exp_type*)this;}
	///	@name �����s��
	//@{
	///	�����s��i�e���v���[�g�Łj
	template <class SUB>
		TSubMatrixCol<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>& sub_matrix(SUB){
		return (TSubMatrixCol<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>&)exp().item(DIMDEC(SUB::TOP), DIMDEC(SUB::LEFT));
	}
	template <class SUB>
		const TSubMatrixCol<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>& sub_matrix(SUB) const {
		return (TSubMatrixCol<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>&)exp().item(DIMDEC(SUB::TOP), DIMDEC(SUB::LEFT));
	}
	///	�����s��i�T�C�Y�����e���v���[�g�Łj
	template <class SUB>
		TSubMatrixCol<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>& sub_matrix(size_t t, size_t l, SUB){
		return (TSubMatrixCol<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>&)exp().item(t,l);
	}
	template <class SUB>
		const TSubMatrixCol<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>& sub_matrix(size_t t, size_t l, SUB) const {
		return (TSubMatrixCol<DIMDEC(SUB::HEIGHT), DIMDEC(SUB::WIDTH), desc>&)exp().item(t,l);
	}
	///	�����s��i�ϐ��Łj
	ESubMatrixCol<element_type> vsub_matrix(int t, int l, int h, int w){
		return ESubMatrixCol<element_type>(h, w, exp().stride(), &exp().item(t,l));
	}
	//@}
};
///	�s�x�N�g���̊�{�^	�T�C�Y�F�ϐ�
template <class desc>
class EMakeSubMatrixRow{
public:
	typedef TYPENAME desc::element_type element_type;
	typedef TYPENAME desc::exp_type exp_type;
	exp_type& exp(){ return *(exp_type*)this;}
	const exp_type& exp() const { return *(exp_type*)this;}
	///	@name �����s��
	//@{
	///	�����s��i�ϐ��Łj
	ESubMatrixRow<element_type> vsub_matrix(int t, int l, int h, int w){
		return ESubMatrixRow<element_type>(h, w, exp().stride(), &exp().item(t,l));
	}
	//@}
};
///	��x�N�g���̊�{�^	�T�C�Y�F�ϐ�
template <class desc>
class EMakeSubMatrixCol{
public:
	typedef TYPENAME desc::element_type element_type;
	typedef TYPENAME desc::exp_type exp_type;
	exp_type& exp(){ return *(exp_type*)this;}
	const exp_type& exp() const { return *(exp_type*)this;}
	///	@name �����s��
	//@{
	///	�����s��i�ϐ��Łj
	ESubMatrixCol<element_type> vsub_matrix(int t, int l, int h, int w){
		return ESubMatrixCol<element_type>(h, w, exp().stride(), &exp().item(t,l));
	}
	//@}
};


//----------------------------------------------------------------------------
///	@name �s�񉉎Z�̎���
//@{
template <class DESC> class MatrixImp;
template <DIMTYPE H, DIMTYPE W, class D> class TMatrixBaseBase;
template <DIMTYPE H, DIMTYPE W, class D> class TMatrixBase;
template <class DESC> class EMatrixBase;

/**	���(*this = b).
	@param b �����T�C�Y�̍s��.	*/
template <class AD, class BD>
void assign(MatrixImp<AD>& a, const MatrixImp<BD>& b) {
	a.resize(b.height(), b.width());
	a.size_assert(b);
	for(size_t i=0; i<a.height(); ++i)
		for(size_t j=0; j<a.width(); ++j)
			a.item(i,j) = (TYPENAME AD::element_type)b.item(i,j);
}
/**	���(*this = b).
	@param b �����T�C�Y�̃x�N�g��.	*/
template <class AD>
void assign(MatrixImp<AD>& a, const TYPENAME AD::element_type* b) {
	for(size_t i=0; i<a.height(); ++i)
		for(size_t j=0; j<a.width(); ++j)
			a.item(i,j) = b[i*a.width()+j];
}
///	��r
template <class AD, class BD>
bool equal(const MatrixImp<AD>& a, const MatrixImp<BD>& b){
	if (!a.size_check(b)) return false;
	for(size_t i=0; i<a.height(); ++i)
		for(size_t j=0; j<a.width(); ++j)
			if (a.item(i,j) != b.item(i,j)) return false;
	return true;
}
///	���Z
template <class AD, class BD>
void add(MatrixImp<AD>& a, const MatrixImp<BD>& b){
	a.size_assert(b);
	for(size_t i=0; i<a.height(); ++i)
		for(size_t j=0; j<a.width(); ++j)
			a.item(i,j) += b.item(i,j);
}
///	���Z
template <class AD, class BD>
void sub(MatrixImp<AD>& a, const MatrixImp<BD>& b){
	a.size_assert(b);
	for(size_t i=0; i<a.height(); ++i)
		for(size_t j=0; j<a.width(); ++j)
			a.item(i,j) -= b.item(i,j);
}
///	�s��ƃX�J���[�̊|���Z
template <class AD>
void multi(MatrixImp<AD>& a, TYPENAME AD::element_type b){
	for(size_t i=0; i<a.height(); ++i)
		for(size_t j=0; j<a.width(); ++j)
			a.item(i,j) *= b;
}
///	�s��ƃx�N�g���̊|���Z
template <class RD, class AD, class BD>
void multi(VectorImp<RD>& r, const MatrixImp<AD>& a, const VectorImp<BD>& b){
	r.resize(a.height());
	for(size_t n=0; n<r.size(); ++n){
		r.item(n) = a.row(n) * b;
	}
}
///	�s��ƃx�N�g���̊|���Z	:	3x3
template <class RD, class AD, class BD>
void multi(TVectorBase<DIMENC(3), RD>& r, const TMatrixBase<DIMENC(3),DIMENC(3),AD>& a, const TVectorBase<DIMENC(3), BD>& b){
	r(0) = a.row(0) * b;
	r(1) = a.row(1) * b;
	r(2) = a.row(2) * b;
}
///	�s��̊|���Z
template <class RD, class AD, class BD>
void multi(MatrixImp<RD>& r, const MatrixImp<AD>& a, const MatrixImp<BD>& b){
	typedef TYPENAME RD::zero zero;
	assert(a.width()==b.height());
	r.resize(a.height(), b.width());
	for(size_t i=0; i<a.height(); ++i){
		for(size_t j=0; j<b.width(); ++j){
			r.item(i,j) = zero(0);
			for(size_t k=0; k<a.width(); ++k){
				r.item(i,j) += a.item(i,k) * b.item(k,j);
			}
		}
	}
}
///	�s��̊|���Z	�T�C�Y�F3x3
#ifndef __BORLANDC__
template <class RD, class AD, class BD>
void multi(TMatrixBase<DIMENC(3), DIMENC(3), RD>& r, const TMatrixBase<DIMENC(3), DIMENC(3), AD>& a, const TMatrixBase<DIMENC(3), DIMENC(3), BD>& b){
        typedef TYPENAME RD::element_type ET;
#define CALC(i,j) r.item(i,j) = ET( a.item(i,0)*b.item(0,j) + a.item(i,1)*b.item(1,j) + a.item(i,2)*b.item(2,j) )
	CALC(0,0);	CALC(0,1);	CALC(0,2);
	CALC(1,0);	CALC(1,1);	CALC(1,2);
	CALC(2,0);	CALC(2,1);	CALC(2,2);
#undef CALC
}
#endif
///	�s��̊|���Z	�T�C�Y�F4x4
template <class RD, class AD, class BD>
void multi(TMatrixBase<DIMENC(4), DIMENC(4), RD>& r, const TMatrixBase<DIMENC(4), DIMENC(4), AD>& a, const TMatrixBase<DIMENC(4), DIMENC(4), BD>& b){
        typedef TYPENAME RD::element_type ET;
#define CALC(i,j) r.item(i,j) = ET( a.item(i,0)*b.item(0,j) + a.item(i,1)*b.item(1,j) + a.item(i,2)*b.item(2,j) + a.item(i,3)*b.item(3,j) )
	CALC(0,0);	CALC(0,1);	CALC(0,2);	CALC(0,3);
	CALC(1,0);	CALC(1,1);	CALC(1,2);	CALC(1,3);
	CALC(2,0);	CALC(2,1);	CALC(2,2);	CALC(2,3);
	CALC(3,0);	CALC(3,1);	CALC(3,2);	CALC(3,3);
#undef CALC
}

///	�s��	�T�C�Y�F�ϐ�
template <class AD>
TYPENAME AD::element_type det(const MatrixImp<AD>& a){
	TYPENAME AD::ret_type tmp(a);
	VVector<int> ip;
	VVector<TYPENAME AD::element_type> w;
	ip.resize(a.height());
	w.resize(a.height());
	return lu(tmp, ip, w);
}
///	�s��	�T�C�Y�F�e���v���[�g
template <DIMTYPE H, DIMTYPE W, class AD>
TYPENAME AD::element_type det(const TMatrixBaseBase<H,W,AD>& a){
	TYPENAME AD::ret_type tmp(a);
	TVector<DIMDEC(H), int> ip;
	TVector<DIMDEC(H), TYPENAME AD::element_type> w;
	return lu(tmp, ip, w);
}
#ifndef __BORLANDC__
///	�s��	�T�C�Y�F2x2
template <class AD>
TYPENAME AD::element_type det(const TMatrixBase<DIMENC(2),DIMENC(2),AD>& a){
	return a.item(0,0) * a.item(1,1) - a.item(0,1) * a.item(1,0);
}
#endif
///	�s��	�T�C�Y�F3x3
template <class AD>
TYPENAME AD::element_type det(const TMatrixBase<DIMENC(3),DIMENC(3),AD>& a){
	return 
		( a.item(0,0) * a.item(1,1) * a.item(2,2)  +  a.item(1,0) * a.item(2,1) * a.item(0,2)  +  a.item(2,0) * a.item(0,1) * a.item(1,2) ) -
		( a.item(2,0) * a.item(1,1) * a.item(0,2)  +  a.item(0,0) * a.item(2,1) * a.item(1,2)  +  a.item(1,0) * a.item(0,1) * a.item(2,2) );
}
///	LU�������s���Ba ������������B�s�񎮂�Ԃ��B
template <class AD>
TYPENAME AD::element_type lu(MatrixImp<AD>& a, int* ip, TYPENAME AD::element_type* weight){
#define ABS_LU_MATRIX(a)	((a)>0 ? (a) : -(a))
	assert(a.width() == a.height());
	int i, j, k, ii, ik;
	int n = (int)a.height();
	TYPENAME AD::element_type t, u, det_;
	
	det_ = 0;                   // �s��
	for (k = 0; k < n; k++) {  // �e�s�ɂ���
		ip[k] = k;             // �s�������̏����l
		u = 0;                 // ���̍s�̐�Βl�ő�̗v�f�����߂�
		for (j = 0; j < n; j++) {
			t = ABS_LU_MATRIX(a.item(k,j));
            if (t > u) u = t;
		}
		if (u == 0) goto PTM_EXIT; // 0 �Ȃ�s���LU�����ł��Ȃ�
		weight[k] = 1 / u;     // �ő��Βl�̋t��
	}
	det_ = 1;                   // �s�񎮂̏����l
	for (k = 0; k < n; k++) {  // �e�s�ɂ���
		u = -1;
		for (i = k; i < n; i++) {  // ��艺�̊e�s�ɂ���
			ii = ip[i];            // �d�݁~��Βl ���ő�̍s��������
			t = ABS_LU_MATRIX(a.item(ii, k)) * weight[ii];
			if (t > u) {  u = t;  j = i;  }
		}
		ik = ip[j];
		if (j != k) {
			ip[j] = ip[k];  ip[k] = ik;  // �s�ԍ�������
			det_ = -det_;  // �s����������΍s�񎮂̕������ς��
		}
		u = a.item(ik, k);  det_ *= u;  // �Ίp����
		if (u == 0) goto PTM_EXIT;    // 0 �Ȃ�s���LU�����ł��Ȃ�
		for (i = k + 1; i < n; i++) {  // Gauss�����@
			ii = ip[i];
			t = (a.item(ii, k) /= u);
			for (j = k + 1; j < n; j++)
				a.item(ii, j) -= t * a.item(ik, j);
		}
	}
	PTM_EXIT:
	return det_;           // �߂�l�͍s��
}
//	a x + b = 0 ��1���������������DLU�����ς݂̕K�v����D
template <class AD, class XD, class BD>
void solve(MatrixImp<AD>& a, VectorImp<XD>& x, const VectorImp<BD>& b, int* ip){
	int i, j, ii;
	TYPENAME XD::element_type t;
	const int n = a.height();
	for (i = 0; i < n; i++) {       // Gauss�����@�̎c��
		ii = ip[i];  t = b[ii];
		for (j = 0; j < i; j++) t -= a.item(ii, j) * x[j];
		x[i] = t;
	}
	for (i = n - 1; i >= 0; i--) {  // ��ޑ��
		t = x[i];  ii = ip[i];
		for (j = i + 1; j < n; j++) t -= a.item(ii, j) * x[j];
		x[i] = t / a.item(ii, i);
	}
}
///	�R���X�L�[�@�Da,s������������D
template <class AD, class BD>
void cholesky(MatrixImp<AD>& a, VectorImp<BD>& s){
	int i,j,k;
	int num = a.height();
	
	//reduction  foreward
	a.item(0,0) = sqrt(a.item(0,0));
	s.item(0) /= a.item(0, 0);
	for(i=1;i<num;i++) {
		a.item(0,i) /= a.item(0,0);
	}

	for(i=1;i<num;i++){
		for(k=0;k<i;k++){
			a.item(i,i) -= a.item(k,i)*a.item(k,i);
			s.item(i) -= a.item(k,i)*s.item(k);
		}
		a.item(i,i) = sqrt(a.item(i,i));
		for(j=i+1; j<num; j++){
			for (k=0; k<i; k++){
				a.item(i,j) -= a.item(k,i) * a.item(k,j);
			}
			a.item(i,j) /= a.item(i,i);
		}
		s.item(i) /= a.item(i,i);
	}

	// backwark substitution 
	for(i=num-1; i>=0; i--){
		for(j=i+1; j<num; j++){			
			s.item(i) -= a.item(i,j) * s.item(j);
		}
		s.item(i) /= a.item(i,i);
	}
}
///	�K�E�X�̏����@�C��Ɨ̈�(�s�����̋L�^)�Ƃ��āC int ip[height()];  ���K�v�D
template <class AD, class XD, class BD>
TYPENAME AD::element_type gauss(MatrixImp<AD>& a, VectorImp<XD>& x, const VectorImp<BD>& b, int* ip){
	TYPENAME AD::element_type det_;		// �s��
	TYPENAME AD::col_vector_type::ret_type w;
	det_ = lu(a, ip, w);				// LU����
	if (det_ != 0) solve(a, x, b, ip);	// LU�����̌��ʂ��g���ĘA��������������
	return det_;						// �߂�l�͍s��
}

/**	�t�s������߂�D
	@param a		���̍s��(LU���������)
	@param b		�t�s��
	@param ip		��Ɨ̈�(�s�����̋L�^)
	@param weight	��Ɨ̈�(�s�̏d�ݕt��)
*/
template <class RD, class AD>
TYPENAME AD::element_type inv(MatrixImp<RD>& r, MatrixImp<AD>& a, int* ip, TYPENAME AD::element_type* weight) {
	assert(a.height() == a.width());
	r.resize(a.height(), a.width());
	int i, j, k, ii;
	int n = (int)a.height();
	TYPENAME AD::element_type t, det;

	det = a.lu(ip, weight);
	if (det != 0){
		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				ii = ip[i];  t = (ii == k);
				for (j = 0; j < i; j++)
					t -= a.item(ii, j) * r.item(j, k);
				r.item(i, k) = t;
			}
			for (i = n - 1; i >= 0; i--) {
				t = r.item(i, k);  ii = ip[i];
				for (j = i + 1; j < n; j++)
					t -= a.item(ii, j) * r.item(j, k);
				r.item(i, k) = t / a.item(ii, i);
			}
		}
	}
	return det;
}

///	 �t�s���Ԃ��D
template <class AD>
TYPENAME AD::ret_type inv(const MatrixImp<AD>& a){
	typedef TYPENAME AD::ret_type ret_type;
	ret_type r, tmp(a);
	VVector<int> ip;
	ip.resize(a.height());
	VVector<TYPENAME AD::element_type> w;
	w.resize(a.height());
	inv(r, tmp, (int*)ip, (TYPENAME AD::element_type*)w);
	return r;
}
///	 �t�s���Ԃ��D	�T�C�Y�F�e���v���[�g
template <class AD, DIMTYPE H, DIMTYPE W>
TYPENAME AD::ret_type inv(const TMatrixBaseBase<H,W,AD>& a){
	TYPENAME AD::ret_type r, tmp(a);
	TVector<DIMDEC(H), int> ip;
	TVector<DIMDEC(H), TYPENAME AD::element_type> w;
	inv(r, tmp, (int*)ip, (TYPENAME AD::element_type*)w);
	return r;
}
#ifndef __BORLANDC__
///	�t�s���Ԃ�
template <class AD>
TYPENAME AD::ret_type inv(const TMatrixBase<DIMENC(2), DIMENC(2), AD>& a){
	TYPENAME AD::element_type d = a.det();
	TYPENAME AD::ret_type rv;
	rv.item(0,0) =  a.item(1,1) / d;
	rv.item(0,1) = -a.item(0,1) / d;
	rv.item(1,0) = -a.item(1,0) / d;
	rv.item(1,1) =  a.item(0,0) / d;
	return rv;
}
#endif
///	�t�s��
template <class AD>
TYPENAME AD::ret_type inv(const TMatrixBase<DIMENC(3), DIMENC(3), AD>& a){
#define DET2_INV_TMATRIXBASE(a,b,c,d)	(a*d - b*c)
	TYPENAME AD::ret_type rtv;
	TYPENAME AD::element_type det_ = 1 / a.det();
	rtv.item(0,0) = DET2_INV_TMATRIXBASE(a.item(1,1), a.item(1,2), a.item(2,1), a.item(2,2)) * det_;
	rtv.item(1,0) = DET2_INV_TMATRIXBASE(a.item(1,2), a.item(1,0), a.item(2,2), a.item(2,0)) * det_;
	rtv.item(2,0) = DET2_INV_TMATRIXBASE(a.item(1,0), a.item(1,1), a.item(2,0), a.item(2,1)) * det_;
		
	rtv.item(0,1) = DET2_INV_TMATRIXBASE(a.item(2,1), a.item(2,2), a.item(0,1), a.item(0,2)) * det_;
	rtv.item(1,1) = DET2_INV_TMATRIXBASE(a.item(2,2), a.item(2,0), a.item(0,2), a.item(0,0)) * det_;
	rtv.item(2,1) = DET2_INV_TMATRIXBASE(a.item(2,0), a.item(2,1), a.item(0,0), a.item(0,1)) * det_;
	
	rtv.item(0,2) = DET2_INV_TMATRIXBASE(a.item(0,1), a.item(0,2), a.item(1,1), a.item(1,2)) * det_;
	rtv.item(1,2) = DET2_INV_TMATRIXBASE(a.item(0,2), a.item(0,0), a.item(1,2), a.item(1,0)) * det_;
	rtv.item(2,2) = DET2_INV_TMATRIXBASE(a.item(0,0), a.item(0,1), a.item(1,0), a.item(1,1)) * det_;
	return rtv;
#undef DET2_INV_TMATRIXBASE
}
//----------------------------------------------------------------------------
/**	�s��̃C���^�t�F�[�X �D�s��N���X�̊�{�N���X�ƂȂ�C�s��ւ̃A�N�Z�X��񋟂���D
	�s��̎��̂́CTMatrix / VMatrix / EMatrix ������C
	�e���v���[�g�ŁC�ϐ��ŁC�ϐ��ŊO���o�b�t�@�ƂȂ��Ă���D
	�s��̓Y�����ƃT�C�Y�̈Ӗ��͈ȉ��̒ʂ�D
	@verbatim
    (0,0) (0,1)....................(0,m)...  ^
    (1,0) (1,1)                        :...  | 
      :                                :... height()
      :                                :...  |
    (n,0) (n,1)....................(n,m)...  V
    <---------  width()  -------------->
    <---------  stride()  ---------------->@endverbatim
	�������̃C���[�W�Ƃ��ẮC�����̍s�ō\�������s��(???Row)��
	�����̗�ō\�������s��(???Col)������D
*/
///	�s��v�Z�̎���
template <class DESC>
class MatrixImp: public DESC::make_sub_matrix{
public:
	typedef DESC desc;
	typedef TYPENAME desc::exp_type				exp_type;
	typedef TYPENAME desc::ret_type				ret_type;
	typedef TYPENAME desc::element_type			element_type;
	typedef TYPENAME desc::row_vector_ref		row_vector_ref;
	typedef TYPENAME desc::const_row_vector_ref	const_row_vector_ref;
	typedef TYPENAME desc::col_vector_ref		col_vector_ref;
	typedef TYPENAME desc::const_col_vector_ref	const_col_vector_ref;
	typedef TYPENAME desc::trans_ref				trans_ref;
	typedef TYPENAME desc::const_trans_ref		const_trans_ref;
	typedef TYPENAME desc::zero					zero;
	typedef TYPENAME desc::unit					unit;
	///	�R���X�g���N�^
	MatrixImp(){}

	///@name �s��̎Q��
	//@{
	///	���̂̎擾
	exp_type& exp(){ return *(exp_type*)this; }
	const exp_type& exp() const { return *(const exp_type*)this; }
	///	n�Ԗڂ̗v�f��Ԃ�(���0).
	element_type& item(size_t n, size_t m){ return exp().item_impl(n,m); }
	const element_type& item(size_t n, size_t m) const { return exp().item_impl(n,m); }
	///	�s�x�N�g��
	row_vector_ref row(size_t n){ return exp().row_impl(n) ;}
	const_row_vector_ref row(size_t n) const { return exp().row_impl(n) ;}
	template <class I>
	row_vector_ref operator [] (I n){ return exp().row_impl(n) ;}
	template <class I>
	const_row_vector_ref operator [] (I n) const { return exp().row_impl(n) ;}
	///	��x�N�g��
	col_vector_ref col(size_t m){ return exp().col_impl(m) ;}
	const_col_vector_ref col(size_t m) const { return exp().col_impl(m) ;}
	///	�]�u�s��
	trans_ref trans() { return exp().trans_impl(); }
	const_trans_ref trans() const { return exp().trans_impl(); }
	///	element_type* �֕ϊ�
	operator element_type*(){ return &item(0,0); }
	operator const element_type*() const { return &item(0,0); }
	
	///	�s���̎擾
	size_t height() const { return exp().height_impl(); }
	///	�񐔂̎擾
	size_t width() const { return exp().width_impl(); }
	///	�T�C�Y�̐ݒ�
	void resize(size_t h, size_t w){ exp().resize_impl(h,w); }
	///	stride �̎擾
	size_t stride() const { return exp().stride_impl(); }
	/**	�x�N�g���̗v�f��S��v�ɂ���.
		@param v �v�f�^�̒l.	*/
	void clear(const element_type v=zero(0)){
		for(size_t i=0; i<height(); ++i)
			for(size_t j=0; j<width(); ++j)
				item(i,j) = v;
	}
	//@}

	///	@name �`�F�b�N
	//@{
	template <class B> void size_assert(const MatrixImp<B>& b) const {
		assert(height() == b.height() && width() == b.width());
	}
	template <class B> bool size_check(const MatrixImp<B>& b) const {
		return height() == b.height() && width() == b.width();
	}
	//@}

	///	@name ���Z
	//@{
	/**	���(*this = b)	@param b �����T�C�Y�̍s��.	*/
	template <class BD> void assign(const MatrixImp<BD>& b) { PTM::assign(exp(), b); }
	/**	���(*this = b).@param b �����T�C�Y�̃x�N�g��.	*/
	void assign(const element_type* b) { PTM::assign(exp(), b); }
	///	��r
	template <class BD> bool equal(const MatrixImp<BD>& b) const { return PTM::equal(exp(), b); }
	///	���Z
	template <class BD> void add(const MatrixImp<BD>& b){ PTM::add(exp(), b); }
	///	���Z
	template <class BD> void sub(const MatrixImp<BD>& b){ PTM::sub(exp(), b); }
	///	�X�J���[�̊|���Z
	void multi(element_type b){ PTM::multi(exp(), b); }
	///	LU�������s���Bthis������������B�s�񎮂�Ԃ��B
	element_type lu(int* ip, element_type* weight){ return PTM::lu(exp(), ip, weight); }
	//	(*this) x + b = 0 ��1���������������DLU�����ς݂̍s��łȂ��Ƃ��߁D
	template <class XD, class BD> void solve(VectorImp<XD>& x, const VectorImp<BD>& b, int* ip){ PTM::solve(exp(), x, b, ip); }
	///	�R���X�L�[�@
	template <class VBASE> void cholesky(VectorImp<VBASE>& s){ PTM::cholesky(exp(), s); }
	///	�K�E�X�̏����@�C��Ɨ̈�(�s�����̋L�^)�Ƃ��āC int ip[height()];  ���K�v�D
	template <class XD, class BD> element_type gauss(VectorImp<XD>& x, const VectorImp<BD>& b, int* ip){ return PTM::gauss(exp(), x, b, ip); }
	///	�t�s������߂�B
	template <class B> element_type inv(MatrixImp<B>& a_inv, int* ip, element_type* weight) { return PTM::inv(a_inv, exp(), ip, weight); }
	///	�t�s������߂�B
	ret_type inv() const { return PTM::inv(exp()); }
	///	�s��
	element_type det() const { return PTM::det(exp()); }
	//@}
	///@name	�X�g���[�����o��
	//@{
	///	�o��
	void print(std::ostream& os, char* sep="( )") const {
//		os << "sz:" << height() << "," << width() << std::endl;
		int w = os.width();
		os.width(0);
		for(size_t i=0; i<height(); ++i){
			for(int j=0; j<w; ++j){
				if (sep[1]) os << sep[1];
			}
			if (i == 0){
				if(sep[0]) os << sep[0];
			}else{
				if(sep[1]) os << sep[1];
			}
			row(i).print(os);
			if (i==height()-1){
				if(sep[2]) os << sep[2];
			}
			os << std::endl;
		}
		os.width(w);
	}
	///	����
	void input(std::istream& is){
		char ch;
		is >> ch;
		for(int i=0; i<height(); ++i) is >> row(i);
		is >> ch;
	}
	//@}
protected:
	///	�o�b�t�@�̏������D
	void init_buffer(){}
	///	�f�t�H���g�R���X�g���N�^���ĂԁD
	void set_default(){}
};

/**	MatrixImp�^�h���N���X�ɕK�v�ȃ����o�̒�`.
	�h���N���X����邽�тɁC���̃}�N�����g���ă����o�����.
	@param	THIS	�V���ɐ錾����h���N���X�̌^��.
	@see	MatrixImp	*/

#define DEF_MATRIXD_BASIC_MEMBER(THIS)										\
	typedef THIS						this_type;							\
	typedef TYPENAME desc::exp_type				exp_type;					\
	typedef TYPENAME desc::ret_type				ret_type;					\
	typedef TYPENAME desc::row_vector_ref		row_vector_ref;				\
	typedef TYPENAME desc::const_row_vector_ref	const_row_vector_ref;		\
	typedef TYPENAME desc::col_vector_ref		col_vector_ref;				\
	typedef TYPENAME desc::const_col_vector_ref	const_col_vector_ref;		\
	typedef TYPENAME desc::element_type			element_type;				\
	typedef TYPENAME desc::zero					zero;						\
	typedef TYPENAME desc::unit					unit;						\
	typedef TYPENAME desc::trans_ref			trans_ref;					\
	typedef TYPENAME desc::const_trans_ref		const_trans_ref;			\
	/*  �s�� b ����	*/													\
	template <class B>														\
	THIS& operator =(const PTM::MatrixImp<B>& b){							\
		assign(b); return *this;											\
	}																		\
	THIS& operator =(const THIS& b){										\
		assign(b); return *this;											\
	}																		\
	/**	+=���Z�q(*this = *this + b).										\
		@param	b	�������������s��	*/									\
	template <class B>														\
	this_type& operator +=(const PTM::MatrixImp<B>& b){						\
		add(b); return *this;												\
	}																		\
	/**	-=���Z�q(*this = *this - b). @param	b	�������������s��	*/		\
	template <class B>														\
	this_type& operator -=(const PTM::MatrixImp<B>& b){						\
		sub(b); return *this;												\
	}																		\
	/**	- ���Z�q (return -*this).	*/										\
	ret_type operator- () { ret_type r(*this); r*=-1; return r; }			\
	/**	*=���Z�q(*this = b * *this). @param	b	�v�f�^	*/					\
	this_type operator*= (element_type b){									\
		multi(b);															\
		return *this;														\
	}																		\
	/**	/=���Z�q(*this = *this / b). @param	b	�v�f�^	*/					\
	this_type operator/= (element_type b){									\
		div(b);																\
		return *this;														\
	}																		\

#define DEF_MATRIX_BASIC_MEMBER(THIS)										\
	DEF_MATRIXD_BASIC_MEMBER(THIS)											\
	/*	�f�t�H���g�R���X�g���N�^	*/										\
	THIS(){ this->init_buffer(); this->set_default();} 			\
	/*  �s�� b �ɂ�鏉����		*/											\
	template <class B>														\
	THIS(const PTM::MatrixImp<B>& b){ this->init_buffer(); this->assign(b);}	\

//----------------------------------------------------------------------------
//	�������e���v���[�g�Ŏ��x�N�g��	T???Matrix
//
///	�������e���v���[�g�Ŏ��x�N�g���̊�{�^
template<DIMTYPE H, DIMTYPE W, class D>
class TMatrixBaseBase: public MatrixImp<D> {
protected:
	///	�o�b�t�@�̏������͕s�p
	void init_buffer(){};
	///	�p����p
	TMatrixBaseBase(){} 
public:
	DIMDEF(H, HEIGHT);			///<	�s��
	DIMDEF(W, WIDTH);			///<	��
	DIMDEF(D::STRIDE, STRIDE);	///<	��(�s)�̊Ԋu
	typedef D desc;
	typedef MatrixImp<desc> base_type;
	DEF_MATRIXD_BASIC_MEMBER(TMatrixBaseBase);

	///	�s��
	size_t height_impl() const { return DIMDEC(H); }
	///	��
	size_t width_impl() const { return DIMDEC(W); }
	size_t stride_impl() const { return DIMDEC(D::STRIDE); }
	void resize_impl(size_t h, size_t w) { assert(h==this->height() && w==this->width()); }
	///	�s�x�N�g��
	row_vector_ref row_impl(size_t n){ return (row_vector_ref)this->item(n,0); }
	const_row_vector_ref row_impl(size_t n) const { return (row_vector_ref)this->item(n,0); }
	///	��x�N�g��
	col_vector_ref col_impl(size_t m){ return (col_vector_ref)this->item(0,m); }
	const_col_vector_ref col_impl(size_t m) const { return (col_vector_ref)this->item(0,m); }
	///	�]�u
	trans_ref trans_impl() { return (trans_ref)this->item(0,0); }
	const_trans_ref trans_impl() const { return (const_trans_ref)this->item(0,0); }
};
template<DIMTYPE H, DIMTYPE W, class D>
class TMatrixBase: public TMatrixBaseBase<H,W,D> {
public:
	DIMDEF(H, HEIGHT);			///<	�s��
	DIMDEF(W, WIDTH);			///<	��
	DIMDEF(D::STRIDE, STRIDE);	///<	��(�s)�̊Ԋu
	typedef D desc;
	typedef TMatrixBaseBase<H,W,D> base_type;
	DEF_MATRIXD_BASIC_MEMBER(TMatrixBase);
};

template <class EXP, class TRANS, size_t H, size_t W, size_t STR, class T, class Z=T, class U=Z>
class TMatrixDescBase{
public:
	DIMDEF(DIMENC(STR),				STRIDE);				///<	�s��o�b�t�@�̕�
	typedef EXP						exp_type;				///<	����
	typedef exp_type				ret_type;				///<	�Ԃ�l�^
	typedef T						element_type;			///<	�v�f�̌^
	typedef Z						zero;					///<	zero(0)�� 0 ��Ԃ��^
	typedef U						unit;					///<	unit(1)�� 1 ��Ԃ��^
	typedef TRANS					trans_type;				///<	�]�n�s��̌^
	typedef trans_type&				trans_ref;				///<	�]�n�s��̎Q�ƌ^
	typedef const trans_type&		const_trans_ref;		///<	�]�n�s��̎Q�ƌ^
};
template <class EXP, class TRANS, size_t H, size_t W, size_t STR, class T, class Z=T, class U=Z>
class TMatrixDescRow: public TMatrixDescBase<EXP,TRANS,H,W,STR,T,Z,U>{
public:
	typedef TMakeSubMatrixRow< TMatrixDescRow<EXP,TRANS,H,W,STR,T,Z,U> > make_sub_matrix;
	typedef TVector<W,T>			row_vector_type;		///<	�s�x�N�g���^
	typedef row_vector_type&		row_vector_ref;			///<	�s�x�N�g���̎Q��
	typedef const row_vector_type&	const_row_vector_ref;	///<	�s�x�N�g���̎Q��
	typedef TVectorSlice<H,STR,TVector<H*STR,T> >
									col_vector_type;		///<	��x�N�g���^
	typedef col_vector_type&		col_vector_ref;			///<	��x�N�g���̎Q��
	typedef const col_vector_type&	const_col_vector_ref;	///<	��x�N�g���̎Q��
};
template <class EXP, class TRANS, size_t H, size_t W, size_t STR, class T, class Z=T, class U=Z>
class TMatrixDescCol: public TMatrixDescBase<EXP,TRANS,H,W,STR,T,Z,U>{
public:
	typedef TMakeSubMatrixCol< TMatrixDescCol<EXP,TRANS,H,W,STR,T,Z,U> > make_sub_matrix;
	typedef TVectorSlice<W,STR,TVector<W*STR,T> >
									row_vector_type;		///<	�s�x�N�g���^
	typedef row_vector_type&		row_vector_ref;			///<	�s�x�N�g���̎Q��
	typedef const row_vector_type&	const_row_vector_ref;	///<	�s�x�N�g���̎Q��
	typedef TVector<H,T>			col_vector_type;		///<	��x�N�g���^
	typedef col_vector_type&		col_vector_ref;			///<	��x�N�g���̎Q��
	typedef const col_vector_type&	const_col_vector_ref;	///<	��x�N�g���̎Q��
};
template <class EXP, class TRANS, size_t H, size_t W, class OD>
class TSubMatrixDescRow: public TMatrixDescRow<EXP, TRANS, H, W, DIMDEC(OD::STRIDE), TYPENAME OD::element_type, TYPENAME OD::zero, TYPENAME OD::unit>{
public:
	typedef TMakeSubMatrixRow< TSubMatrixDescRow<EXP,TRANS,H,W,OD> > make_sub_matrix;
};
template <class EXP, class TRANS, size_t H, size_t W, class OD>
class TSubMatrixDescCol: public TMatrixDescCol<EXP, TRANS, H, W, DIMDEC(OD::STRIDE), TYPENAME OD::element_type, TYPENAME OD::zero, TYPENAME OD::unit>{
public:
	typedef TMakeSubMatrixCol< TSubMatrixDescCol<EXP,TRANS,H,W,OD> > make_sub_matrix;
};

template <size_t H, size_t W, class T, class Z=T, class U=Z> class TMatrixCol;
/**	�s��^. TMatrixRow<3,3, float> m; �̂悤�Ɏg��
	@param	H	�s���D
	@param	W	�񐔁D
	@param	T	�v�f�̌^.	*/
template <size_t H, size_t W, class T, class Z=T, class U=Z>
class TMatrixRow:public TMatrixBase<DIMENC(H), DIMENC(W), TMatrixDescRow<TMatrixRow<H,W,T,Z,U>, TMatrixCol<W,H,T,Z,U>, H, W, W, T, Z, U> >{
public:
	///	�^���
	typedef TMatrixDescRow<TMatrixRow<H,W,T,Z,U>, TMatrixCol<W,H,T,Z,U>, H, W, W, T, Z, U> desc;
	typedef TMatrixBase<DIMENC(H),DIMENC(W),desc> base_type;		///<	��{�N���X�^
	///	�p������Ȃ���{�I�ȃ����o�̒�`. @see ::DEF_MATRIX_BASIC_MEMBER
	DEF_MATRIX_BASIC_MEMBER(TMatrixRow);

public:
	///	�v�f�̃A�N�Z�X
	element_type& item_impl(size_t i, size_t j){ return data[i][j]; }
	const element_type& item_impl(size_t i, size_t j) const { return data[i][j]; }
private:
	element_type data[H][W];										///<	�f�[�^
};

/**	��s��^. TMatrixCol<3,3, float> m; �̂悤�Ɏg��
	@param	H	�s���D
	@param	W	�񐔁D
	@param	T	�v�f�̌^.	*/
template <size_t H, size_t W, class T, class Z, class U>
class TMatrixCol:public TMatrixBase<DIMENC(H), DIMENC(W), TMatrixDescCol<TMatrixCol<H,W,T,Z,U>, TMatrixRow<W,H,T,Z,U>, H,W,H,T,Z,U> >{
public:
	///	�^���
	typedef TMatrixDescCol<TMatrixCol<H,W,T,Z,U>, TMatrixRow<H,W,T,Z,U>, H, W, H, T, Z, U> desc;
	typedef TMatrixBase<DIMENC(H),DIMENC(W),desc> base_type;		///<	��{�N���X�^
	///	�p������Ȃ���{�I�ȃ����o�̒�`. @see ::DEF_MATRIX_BASIC_MEMBER
	DEF_MATRIX_BASIC_MEMBER(TMatrixCol);

public:
	///	�v�f�̃A�N�Z�X
	element_type& item_impl(size_t i, size_t j){ return data[j][i]; }
	const element_type& item_impl(size_t i, size_t j) const { return data[j][i]; }
private:
	element_type data[W][H];				///<	�f�[�^
};

template <size_t H, size_t W, class OD> class TSubMatrixCol;

///	�����s��(�e���v���[�g��)
template <size_t H, size_t W, class OD>
class TSubMatrixRow:public TMatrixBase<DIMENC(H),DIMENC(W),TSubMatrixDescRow<TSubMatrixRow<H,W,OD>,TSubMatrixCol<W,H,OD>, H,W,OD> >{
public:
	typedef TSubMatrixDescRow<TSubMatrixRow<H,W,OD>,TSubMatrixCol<W,H,OD>, H,W,OD> desc;
	typedef TMatrixBase<DIMENC(H),DIMENC(W),desc> base_type;
	///	�p������Ȃ���{�I�ȃ����o�̒�`. @see ::DEF_MATRIX_BASIC_MEMBER
	DEF_MATRIX_BASIC_MEMBER(TSubMatrixRow);
    DIMDEF(base_type::HEIGHT, HEIGHT);
    DIMDEF(base_type::WIDTH, WIDTH);

	///	�v�f�̃A�N�Z�X
	element_type& item_impl(size_t i, size_t j){ return data[i][j]; }
	const element_type& item_impl(size_t i, size_t j) const { return data[i][j]; }
protected:
	element_type data[DIMDEC(HEIGHT)][DIMDEC(base_type::STRIDE)];
};

///	�����s��(�e���v���[�g��)
template <size_t H, size_t W, class OD>
class TSubMatrixCol:public TMatrixBase<DIMENC(H),DIMENC(W),TSubMatrixDescCol<TSubMatrixCol<H,W,OD>,TSubMatrixRow<W,H,OD>, H,W,OD> >{
public:
	typedef TSubMatrixDescCol<TSubMatrixCol<H,W,OD>,TSubMatrixRow<W,H,OD>, H,W,OD> desc;
	typedef TMatrixBase<DIMENC(H),DIMENC(W),desc> base_type;
	///	�p������Ȃ���{�I�ȃ����o�̒�`. @see ::DEF_MATRIX_BASIC_MEMBER
	DEF_MATRIX_BASIC_MEMBER(TSubMatrixCol);
    DIMDEF(base_type::HEIGHT, HEIGHT);
    DIMDEF(base_type::WIDTH, WIDTH);

	///	�v�f�̃A�N�Z�X
	element_type& item_impl(size_t i, size_t j){ return data[j][i]; }
	const element_type& item_impl(size_t i, size_t j) const { return data[j][i]; }
protected:
	element_type data[DIMDEC(WIDTH)][DIMDEC(base_type::STRIDE)];
};

//-----------------------------------------------------------------------------
//	�T�C�Y��ϐ��Ŏ��x�N�g��
//

template <class T> class EMatrixRow;
template <class T> class VMatrixRow;
template <class T> class EMatrixCol;
template <class T> class VMatrixCol;
template <class EXP, class TRANS, class T, class Z=T, class U=Z> class EMatrixDescBase{
public:
	typedef EXP							exp_type;				///<	����
	typedef T							element_type;			///<	�v�f�̌^
	typedef Z							zero;					///<	zero(0)�� 0 ��Ԃ��^
	typedef U							unit;					///<	unit(1)�� 1 ��Ԃ��^
	typedef	TRANS						trans_type;				///<	�]�n�s��
	typedef trans_type					trans_ref;				///<	�]�n�s��̎Q�ƌ^
	typedef trans_type					const_trans_ref;		///<	�]�n�s��̎Q�ƌ^
};
template <class EXP, class TRANS, class T, class Z=T, class U=Z>
class EMatrixDescRow: public EMatrixDescBase<EXP, TRANS, T, Z, U>{
public:
	typedef VMatrixRow<T>							ret_type;				///<	�Ԃ�l�^
	typedef EVector<T>								row_vector_type;		///<	�s�x�N�g���^
	typedef row_vector_type							row_vector_ref;			///<	��x�N�g���̎Q��
	typedef TYPENAME row_vector_type::const_type	const_row_vector_ref;	///<	�s�x�N�g���̎Q��
	typedef EVectorSlice<T>							col_vector_type;		///<	��x�N�g���^
	typedef col_vector_type							col_vector_ref;			///<	�s�x�N�g���̎Q��
	typedef TYPENAME col_vector_type::const_type	const_col_vector_ref;	///<	��x�N�g���̎Q��
	typedef EMakeSubMatrixRow< EMatrixDescRow<EXP, TRANS, T, Z, U> > make_sub_matrix;
};
template <class EXP, class TRANS, class T, class Z=T, class U=Z>
class EMatrixDescCol: public EMatrixDescBase<EXP, TRANS, T, Z, U>{
public:
	typedef VMatrixCol<T>							ret_type;				///<	�Ԃ�l�^
	typedef EVectorSlice<T>							row_vector_type;		///<	�s�x�N�g���^
	typedef row_vector_type							row_vector_ref;			///<	��x�N�g���̎Q��
	typedef TYPENAME row_vector_type::const_type	const_row_vector_ref;	///<	�s�x�N�g���̎Q��
	typedef EVector<T>								col_vector_type;		///<	��x�N�g���^
	typedef col_vector_type							col_vector_ref;			///<	�s�x�N�g���̎Q��
	typedef TYPENAME col_vector_type::const_type	const_col_vector_ref;	///<	��x�N�g���̎Q��
	typedef EMakeSubMatrixCol< EMatrixDescCol<EXP, TRANS, T, Z, U> > make_sub_matrix;
};

///	�T�C�Y��ϐ��ł��s��̊�{�^
template <class D>
class EMatrixBase:public MatrixImp<D>{
public:
	///	�^���
	typedef D desc;
	typedef MatrixImp<desc> base_type;		///<	��{�N���X�^
	DEF_MATRIXD_BASIC_MEMBER(EMatrixBase);

	size_t height_impl() const { return height_; }
	size_t width_impl() const { return width_; }
		
	///	�s�x�N�g��
	row_vector_ref row_impl(size_t n){
		return row_vector_ref(this->width(), 1, &this->item(n,0)); 
	}
	const_row_vector_ref row_impl(size_t n) const {
		return const_row_vector_ref(this->width(), 1, &this->item(n,0));
	}
	///	��x�N�g��
	col_vector_ref col_impl(size_t m){
		return col_vector_ref(this->height(), this->stride(), &this->item(0,m));
	}
	const_col_vector_ref col_impl(size_t m) const {
		return const_col_vector_ref(this->height(), this->stride(), &this->item(0,m));
	}
	///	�]�u
	trans_ref trans_impl(){
		return trans_ref(this->width(), this->height(), this->stride(), &this->item(0,0));
	}
	const_trans_ref trans_impl() const {
		return const_trans_ref(this->width(), this->height(), this->stride(), &this->item(0,0));
	}
	///
	void resize_impl(size_t h, size_t w) { assert(h==height_ && w==width_);}

protected:
	size_t height_;
	size_t width_;
	element_type* data;						///<	�f�[�^
	void init_buffer(){height_=0; width_=0; data=0; }
	EMatrixBase(size_t h, size_t w, const element_type* d):height_(h), width_(w), data((element_type*)d){}
	EMatrixBase():height_(0), width_(0), data(0){}
};

///	�T�C�Y��ϐ��ł��s��̊�{�^
template <class D>
class EMatrixBaseRow:public EMatrixBase<D>{
protected:
	EMatrixBaseRow(){}
	EMatrixBaseRow(const EMatrixBaseRow& m): EMatrixBase<D>(m){}
public:
	typedef D desc;
	typedef EMatrixBase<D> base_type;
	DEF_MATRIXD_BASIC_MEMBER(EMatrixBaseRow)
	EMatrixBaseRow(size_t h, size_t w, const element_type* d):EMatrixBase<D>(h,w,d){}
	///	�v�f�̃A�N�Z�X
	element_type& item_impl(size_t i, size_t j){ return this->data[i*this->stride()+j]; }
	const element_type& item_impl(size_t i, size_t j) const { return this->data[i*this->stride()+j]; }
	///	�X�g���C�h
	size_t stride_impl() const { return this->width_; }
	///	�s�x�N�g��
	row_vector_ref row_impl(size_t n){
		return row_vector_ref(this->width(), 1, &this->item(n,0));
	}
	const_row_vector_ref row_impl(size_t n) const {
		return const_row_vector_ref(this->width(), 1, &this->item(n,0));
	}
	///	��x�N�g��
	col_vector_ref col_impl(size_t m){
		return col_vector_ref(this->height(), this->stride(), &this->item(0,m));
	}
	const_col_vector_ref col_impl(size_t m) const {
		return const_col_vector_ref(this->height(), this->stride(), &this->item(0,m));
	}
};

///	�T�C�Y��ϐ��ł��s��̊�{�^
template <class D>
class EMatrixBaseCol:public EMatrixBase<D>{
protected:
	EMatrixBaseCol(){}
	EMatrixBaseCol(const EMatrixBaseCol& m): EMatrixBase<D>(m){}
public:
	typedef D desc;
	typedef EMatrixBase<D> base_type;
	DEF_MATRIXD_BASIC_MEMBER(EMatrixBaseCol)
	EMatrixBaseCol(size_t h, size_t w, const element_type* d):EMatrixBase<D>(h,w,d){}
	///	�v�f�̃A�N�Z�X
	element_type& item_impl(size_t i, size_t j){ return this->data[j*this->stride()+i]; }
	const element_type& item_impl(size_t i, size_t j) const { return this->data[j*this->stride()+i]; }
	///	�X�g���C�h
	size_t stride_impl() const { return this->height_; }
	///	�s�x�N�g��
	row_vector_ref row_impl(size_t n){
		return row_vector_ref(this->width(), this->stride(), &this->item(n,0));
	}
	const_row_vector_ref row_impl(size_t n) const {
		return const_row_vector_ref(this->width(), this->stride(), &this->item(n,0));
	}
	///	��x�N�g��
	col_vector_ref col_impl(size_t m){
		return col_vector_ref(this->height(), 1, &this->item(0,m));
	}
	const_col_vector_ref col_impl(size_t m) const {
		return const_col_vector_ref(this->height(), 1, &this->item(0,m));
	}
};

/**	�s��^. EMatrixRow<float> m(3,3,buf); �̂悤�Ɏg��
	@param	T	�v�f�̌^.	*/
template <class T>
class EMatrixRow:public EMatrixBaseRow< EMatrixDescRow<EMatrixRow<T>, EMatrixCol<T>, T> >{
public:
	///	�^���
	typedef EMatrixDescRow<EMatrixRow<T>, EMatrixCol<T>, T> desc;
	typedef EMatrixBaseRow<desc> base_type;		///<	��{�N���X�^
	///	�p������Ȃ���{�I�ȃ����o�̒�`. @see ::DEF_MATRIX_BASIC_MEMBER
	DEF_MATRIX_BASIC_MEMBER(EMatrixRow);
	EMatrixRow(const EMatrixRow& m):base_type(m.height_, m.width_,m.data){}
	EMatrixRow(size_t h, size_t w, size_t str, const element_type* d):base_type(h,w,d){ assert(str == w); }
};

/**	�s��^. VMatrixRow<float> m(3,3); �̂悤�Ɏg��
	@param	T	�v�f�̌^.	*/
template <class T>
class VMatrixRow:public EMatrixBaseRow< EMatrixDescRow<VMatrixRow<T>, EMatrixCol<T>, T> >{
public:
	///	�^���
	typedef EMatrixDescRow<VMatrixRow<T>, EMatrixCol<T>, T> desc;
	typedef EMatrixBaseRow<desc> base_type;		///<	��{�N���X�^
	///	�p������Ȃ���{�I�ȃ����o�̒�`. @see ::DEF_MATRIX_BASIC_MEMBER
	DEF_MATRIX_BASIC_MEMBER(VMatrixRow);
	VMatrixRow(const VMatrixRow& m){ this->init_buffer(); this->assign(m); }
	~VMatrixRow(){ delete [] this->data; }
	///
	void resize_impl(size_t h, size_t w) {
		if (this->height()*this->width()<h*w){
			delete [] this->data;
			this->data = new T[h*w];
			this->height_ = h;
			this->width_ = w;
		}
	}
};

/**	�s��^. EMatrixCol<float> m(3,3,buf); �̂悤�Ɏg��
	@param	T	�v�f�̌^.	*/
template <class T>
class EMatrixCol:public EMatrixBaseCol< EMatrixDescCol<EMatrixCol<T>, EMatrixRow<T>, T> >{
public:
	///	�^���
	typedef EMatrixDescCol<EMatrixCol<T>, EMatrixRow<T>, T> desc;
	typedef EMatrixBaseCol<desc> base_type;		///<	��{�N���X�^
	///	�p������Ȃ���{�I�ȃ����o�̒�`. @see ::DEF_MATRIX_BASIC_MEMBER
	DEF_MATRIX_BASIC_MEMBER(EMatrixCol);
	EMatrixCol(const EMatrixCol& m):base_type(m.height_, m.width_, m.data){}
	EMatrixCol(size_t h, size_t w, size_t str, const element_type* d):base_type(h,w,d){ assert(str == h); }
};

/**	�s��^. VMatrixCol<float> m(3,3); �̂悤�Ɏg��
	@param	T	�v�f�̌^.	*/
template <class T>
class VMatrixCol:public EMatrixBaseCol< EMatrixDescCol<VMatrixCol<T>, EMatrixRow<T>, T> >{
public:
	///	�^���
	typedef EMatrixDescCol<VMatrixCol<T>, EMatrixRow<T>, T> desc;
	typedef EMatrixBaseCol<desc> base_type;		///<	��{�N���X�^
	///	�p������Ȃ���{�I�ȃ����o�̒�`. @see ::DEF_MATRIX_BASIC_MEMBER
	DEF_MATRIX_BASIC_MEMBER(VMatrixCol);
	VMatrixCol(const VMatrixCol& m){ this->init_buffer(); this->assign(m); }
	~VMatrixCol(){ delete [] this->data; }
	///
	void resize_impl(size_t h, size_t w) {
		if (this->height()*this->width()<h*w){
			delete [] this->data;
			this->data = new T[h*w];
		}
		this->height_ = h;
		this->width_ = w;
	}
};

template <class T, class Z, class U> class ESubMatrixCol;
///	�����s��(�ϐ���)
template <class T, class Z, class U>
class ESubMatrixRow:public EMatrixBaseRow< EMatrixDescRow<ESubMatrixRow<T>, ESubMatrixCol<T>, T,Z,U> >{
public:
	typedef EMatrixDescRow<ESubMatrixRow<T>, ESubMatrixCol<T>, T,Z,U> desc;
	typedef EMatrixBaseRow<desc> base_type;
	///	�p������Ȃ���{�I�ȃ����o�̒�`. @see ::DEF_MATRIX_BASIC_MEMBER
	DEF_MATRIX_BASIC_MEMBER(ESubMatrixRow);
	///
	ESubMatrixRow(size_t h, size_t w, size_t str, const element_type* d):base_type(h, w, d), stride_(str){}
	///
	ESubMatrixRow(const ESubMatrixRow& m):base_type(m.height_, m.width_, m.data), stride_(m.stride_){}
	///
	size_t stride_impl() const { return stride_; }
protected:
	size_t stride_;
	void init_buffer() { this->height_=0; this->width_=0; this->stride_=0; this->data=0; }
};

///	�����s��(�ϐ���)
template <class T, class Z, class U>
class ESubMatrixCol:public EMatrixBaseCol< EMatrixDescCol<ESubMatrixCol<T>, ESubMatrixRow<T>, T,Z,U> >{
public:
	typedef EMatrixDescCol<ESubMatrixCol<T>, ESubMatrixRow<T>, T,Z,U> desc;
	typedef EMatrixBaseCol<desc> base_type;
	///	�p������Ȃ���{�I�ȃ����o�̒�`. @see ::DEF_MATRIX_BASIC_MEMBER
	DEF_MATRIX_BASIC_MEMBER(ESubMatrixCol);
	///
	ESubMatrixCol(size_t h, size_t w, size_t str, const element_type* d):base_type(h,w,d), stride_(str){}
	///
	ESubMatrixCol(const ESubMatrixCol& m):base_type(m.height_, m.width_, m.data), stride_(m.stride_){}
	///
	size_t stride_impl() const { return stride_; }
protected:
	size_t stride_;
	void init_buffer() { this->height_=0; this->width_=0; this->stride_=0; this->data=0; }
};


//----------------------------------------------------------------------------
///	@name �s��̉��Z�q
//@{
///	�s��̔�r
template <class AD, class BD>
bool operator == (const MatrixImp<AD>& a, const MatrixImp<BD>& b){
	return a.equal(b);
}
///	�s��̔�r
template <class AD, class BD>
bool operator != (const MatrixImp<AD>& a, const MatrixImp<BD>& b){
	return !a.equal(b);
}
///	�s��̘a
template <class AD, class BD>
TYPENAME AD::ret_type operator + (const MatrixImp<AD>& a, const MatrixImp<BD>& b){
	TYPENAME AD::ret_type r(a);
	r.add(b);
	return r;
}
///	�s��̍�
template <class AD, class BD>
TYPENAME AD::ret_type operator - (const MatrixImp<AD>& a, const MatrixImp<BD>& b){
	TYPENAME AD::ret_type r(a);
	r.sub(b);
	return r;
}
///	�s��̊|���Z	�T�C�Y�F�e���v���[�g
template <DIMTYPE AH, DIMTYPE AW, class AD, DIMTYPE BW, class BD>
TMatrixCol<DIMDEC(AH), DIMDEC(BW), TYPENAME AD::element_type> operator * (
	const TMatrixBase<AH, AW, AD>& a,
	const TMatrixBase<AW, BW, BD>& b){
	TMatrixCol<DIMDEC(AH), DIMDEC(BW), TYPENAME AD::element_type> r;
	multi(r, a, b);
	return r;
}
///	�s��̊|���Z	�T�C�Y�F�ϐ�
template <class AD, class BD>
VMatrixCol<TYPENAME AD::element_type> operator * (const MatrixImp<AD>& a, const MatrixImp<BD>& b){
	VMatrixCol<TYPENAME AD::element_type> r;
	multi(r, a, b);
	return r;
}

//	�x�N�g���ƍs��̊|���Z
///	�x�N�g���ƍs��̊|���Z	�T�C�Y�F�e���v���[�g
template <DIMTYPE AH, DIMTYPE AW, class AD, class BD>
TVector<DIMDEC(AH), TYPENAME AD::element_type> operator * (const TMatrixBase<AH, AW, AD>& a, const VectorImp<BD>& b){
	TVector<DIMDEC(AH), TYPENAME AD::element_type> r;
	multi(r, a, b);
	return r;
}
///	�x�N�g���ƍs��̊|���Z	�T�C�Y�F�ϐ�
template <class AD, class BD>
VVector<TYPENAME BD::element_type> operator * (const MatrixImp<AD>& a, const VectorImp<BD>& b){
	VVector<TYPENAME BD::element_type> r;
	multi(r, a, b);
	return r;
}
///	�x�N�g���ƍs��̊|���Z	�T�C�Y�F�e���v���[�g
template <class AD, DIMTYPE BH, DIMTYPE BW, class BD>
TVector<DIMDEC(BW), TYPENAME AD::element_type> operator * (const VectorImp<AD>& a, const TMatrixBase<BH, BW, BD>& b){
	TVector<DIMDEC(BW), TYPENAME AD::element_type> r;
	multi(r, b.trans(), a);
	return r;
}
///	�x�N�g���ƍs��̊|���Z	�T�C�Y�F�ϐ�
template <class AD, class BD>
VVector<TYPENAME AD::element_type> operator * (const VectorImp<AD>& a, const MatrixImp<BD>& b){
	VVector<TYPENAME AD::element_type> r;
	multi(r, b.trans(), a);
	return r;
}
///	�s��̒萔�{
template <class D>
TYPENAME D::ret_type operator * (const MatrixImp<D>& a, TYPENAME D::element_type b){
	TYPENAME D::ret_type r(a);
	r.multi(b);
	return r;
}
///	�s��̒萔�{
template <class D>
TYPENAME D::ret_type operator * (TYPENAME D::element_type a, const MatrixImp<D>& b){
	TYPENAME D::ret_type r(b);
	r.multi(a);
	return r;
}

///	�\��
template <class D>
std::ostream& operator << (std::ostream& os, const MatrixImp<D>& m){
	m.print(os);
	return os;
}
///	����
template <class D>
std::istream& operator >> (std::istream& is, MatrixImp<D>& m){
	m.input(is);
	return is;
}
//@}

#ifdef _WIN32
 #ifdef _DEBUG
  #pragma optimize ("", on)
  #pragma auto_inline(off)
  #pragma inline_recursion(off)
 #endif
 #pragma pack(pop)
#endif

}	//	namespace PTM
#endif
