/*
 *  Copyright (c) 2003-2012, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
/**
OpenMp���g���������s��̏�Z�̌v�Z���Ԃ̌v���v���O�����B
�s��̃T�C�Y�ƃ��[�v�񐔂��w�肷��B
OpenMp��for���𕪊����āA����v�Z���s���B
�V���O���X���b�h�ƃ}���`�X���b�h�łǂ��炪���������ʂ�Ԃ��B
 */

#include <iostream>
#include <conio.h>
#include <Springhead.h>

using namespace std;
using namespace Spr;
using namespace PTM;

#ifdef _OPENMP
	#include <omp.h>
#endif

class OmpTimer{
private:
	double start, end;
public:
	void Start(){
#ifdef _OPENMP
		start = 0.0;
		end = 0.0;
		start = omp_get_wtime();
#endif
	}

	double Stop(){
#ifdef _OPENMP
		end = omp_get_wtime();
		double diff = end - start;
		std::cout << diff << std::endl;
		return  diff;
#endif	
	}
};

void CompMatrix(size_t size){
	VMatrixRow<double> matA;
	matA.resize(size, size, 1.0);
	VMatrixRow<double> matB;
	matB.resize(size, size, 2.0);
	VMatrixRow<double> matC;
	matC.resize(size, size, 0.0);
	matC = matA * matB;
}

void TestSingle(size_t size, int nIter){
	for(int i = 0; i < nIter; i++)
		CompMatrix(size);
}

void TestOMP(size_t size, int nIter){
	#pragma omp parallel for
	for(int i = 0; i < nIter; i++)
		CompMatrix(size);
}

void Test(size_t size, int nIter){
	cout << "----------------------------------------------" << std::endl;
	cout << "Matrix " << size << " : " << "Times " << nIter << std::endl;

	OmpTimer timer;
	double single, multi;

	cout << "	Single thread [sec]: ";
	timer.Start();
	TestSingle(size, nIter);
	single = timer.Stop();

	cout << "	 Multi thread [sec]: ";
	timer.Start();
	TestOMP(size, nIter);
	multi = timer.Stop();

	if(single < multi)
		cout << "			Single is " << (1.0 - single / multi) * 100 << "% faster!" << std::endl;
	else
		cout << "			Multi is " << (1.0 - multi / single) * 100 << "% faster!" << std::endl;
	CSVOUT << nIter << "," << single << "," << multi << std::endl;
}

int _cdecl main()
{
	int matSize;
	std::cout << "Put the size of square matrix in int." << std::endl;
	std::cin >> matSize;

	int loopNum;
	std::cout << "Put the number of times of for loop in int" << std::endl;
	std::cin >> loopNum;

	for(int i = 1; i <= loopNum; i++){
		Test(matSize, i);
	}
	std::cout << "Computation Complete!" << std::endl;
	std::cout << "Press any key to end." << std::endl;
	if(_getch()) return 0;
}