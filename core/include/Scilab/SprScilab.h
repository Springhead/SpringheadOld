#ifndef SCILAB_H
#define SCILAB_H

//	ScilabCall For Springhead2

#include <Base/TMatrix.h>
#include <complex>

namespace Scilab{

#define __INTERNAL_API_SCILAB__
//#define API_SCILAB_EXPORTS
#include "Scilab/api_scilab/includes/api_common.h"
// api_common.h����#define�����Ɗ�����̂�undef����
#undef Rhs
#undef Lhs
//#undef API_SCILAB_EXPORTS
#include "Scilab/core/includes/doublecomplex.h"
#include "Scilab/core/includes/BOOL.h"
#undef __INTERNAL_API_SCILAB__
bool StartScilab(char* SCIpath, char *ScilabStartup,int *Stacksize);
#include "ScilabStub.hpp"
extern StrCtx** ppvApiCtx;
}
namespace Spr{
	///	SciLab�̏������B�g�p�O�Ɉ�x�����ĂԁB
	/// ��O�����������ƈ�x�~�܂�B
	inline int ScilabStart(char* SCIpath=NULL, char *ScilabStartup=NULL,int *Stacksize=NULL){
		return (int)Scilab::StartScilab(SCIpath, ScilabStartup, Stacksize);
	}
	///	SciLab�̏I���B
	inline bool ScilabEnd(char *ScilabQuit=NULL){ return Scilab::TerminateScilab(ScilabQuit) != 0; }
	///	SciLab�Ɏd���𑗂�B job�ɂ�SciLab�̕��𕶎���œn���B
	inline int ScilabJob(const char* job){ return Scilab::SendScilabJob((char*)job); }
	///	SciLab�s����Q�Ƃ��邽�߂̌^
	typedef PTM::EMatrixCol<double> SCMatrix;
	///	SciLab�s��ւ̎Q�Ƃ̎擾�B name ��Scilab�̕��ł̕ϐ�����n���B 
	inline SCMatrix ScilabMatrix(const char* name){
		// �s�񐔂̎擾
		int n, m;
		Scilab::SciErr sciErr;
		sciErr = Scilab::readNamedMatrixOfDouble(*Scilab::ppvApiCtx, name, &m, &n, NULL);
		if(sciErr.iErr){
			//Scilab::printError(&sciErr, 0);
			std::cout << "Can not read the matrix " << name << name << std::endl;
			assert(0);
		}
		// �f�[�^�̎Q�Ƃ̎擾
		void* data = NULL;
		sciErr = Scilab::readNamedPointer(*Scilab::ppvApiCtx, name, &data);
		if(sciErr.iErr){
			//Scilab::printError(&sciErr, 0);
			std::cout << "Can not find the pointer of " << name << std::endl;
			assert(0);
		}
		std::cout << (double*)data << std::endl;
		SCMatrix rv(m, n, m, (double*)data);
		return rv;
	}
	///	SciLab�s��̐ݒ�B name ��Scilab�̕��ł̕ϐ�����n���B 
	template <class AD> bool ScilabSetMatrix(const char* name, PTM::MatrixImp<AD>& a){
		int m = (int)a.height();
		int n = (int)a.width();
		double* v = new double [m*n];
		for(int j=0; j<n; ++j){
			for(int i=0; i<m; ++i){
				v[j*m + i] = a.item(i, j);
			}
		}
		Scilab::SciErr sciErr;
		sciErr = Scilab::createNamedMatrixOfDouble(*Scilab::ppvApiCtx, name, m, n, v);
		delete[] v;
		return sciErr.iErr ? false : true;
	}
	///	SciLab�s��̃R�s�[�̎擾�B name ��Scilab�̕��ł̕ϐ�����n���B 
	template <class AD> bool ScilabGetMatrix(PTM::MatrixImp<AD>& a, const char* name){
		// �s�񐔂̎擾
		int n, m;
		Scilab::SciErr sciErr;
		sciErr = Scilab::readNamedMatrixOfDouble(*Scilab::ppvApiCtx, name, &m, &n, NULL);
		if(sciErr.iErr){
			//Scilab::printError(&sciErr, 0);
			std::cout << "Scilab has not the matrix : " << name << std::endl;
			return false;
		}
		// �f�[�^�̃R�s�[���擾
		double* data = new double [m * n];
		sciErr = Scilab::readNamedMatrixOfDouble(*Scilab::ppvApiCtx, name, &m, &n, data);
		if(sciErr.iErr){
			//Scilab::printError(&sciErr, 0);
			std::cout << "Scilab has not the matrix : " << name << std::endl;
			return false;
		}
		SCMatrix rv(m, n, m, (double*)data);
		// �s��̃R�s�[
		a.assign(rv);
		delete[] data;
		return sciErr.iErr ? false : true;
	}
}
#endif
