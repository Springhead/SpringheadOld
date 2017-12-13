﻿/*
 *  Copyright (c) 2003-2012, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
#include "PHFemVibration.h"
#include "PHFemMeshNew.h"
#include "PHFemBase.h"
#include <Foundation/UTQPTimer.h>
//#include <Foundation/UTOpenMP.h>
#include <Foundation/UTClapack.h>


#ifdef _OPENMP
	#include <omp.h>
#endif

#ifdef _MSC_VER
	#define SPR_OMP(x) __pragma(omp x)
#else
#endif

#if 1
#undef SPR_OMP
#ifdef	_MSC_VER
#  define SPR_OMP(x) __pragma()
#else
#  define SPR_OMP(x)
#endif	//_MSC_VER
#endif

namespace Spr{;

PHFemVibrationDesc::PHFemVibrationDesc(){
	// ポアソン比:0.35,ヤング率 70GPa, 密度2.70g/cm3
	// 減衰比は適当に設定
	poisson = 0.25;
	young = (2.5e9)/27;
	density =610/3;
	alpha = 120;
	beta =7.05e-5;
	
}



UTQPTimerFileOut qtimer;	// 計算時間計測用
#define EDGE_EPS 1e-7		// 内積をとったときの閾値（*面のエッジにporthoがきたときに誤差で-になることがあるため）

//* 初期化と行列の作成
/////////////////////////////////////////////////////////////////////////////////////////
PHFemVibration::PHFemVibration(const PHFemVibrationDesc& desc){
	SetDesc(&desc);
	//analysis_mode = PHFemVibrationDesc::ANALYSIS_DIRECT;
	analysis_mode = PHFemVibrationDesc::ANALYSIS_MODAL;
	//integration_mode = PHFemVibrationDesc::INT_EXPLICIT_EULER;
	//integration_mode = PHFemVibrationDesc::INT_IMPLICIT_EULER;
	//integration_mode = PHFemVibrationDesc::INT_SIMPLECTIC;
	integration_mode = PHFemVibrationDesc::INT_NEWMARK_BETA;
	//SetAlpha(55.5071);//αとβをセット
	//SetBeta(3.12387e-006);

	//++//
	//dampingRatio[0] = 0.15;//(compRaileighDampingRatio)
	//dampingRatio[1] = 0.03;
	nMode = 55;
	bRecomp = true;
}

void PHFemVibration::Init(){
	DSTR << "Initializing PHFemVibration" << std::endl;
	/// 刻み時間の設定
	PHSceneIf* scene = GetPHFemMesh()->GetScene()->Cast();
	if(scene) vdt = scene->GetTimeStep();
	else vdt = 0.001;

	/// 全体剛性行列、全体質量行列、全体減衰行列の計算
	/// これらはすべてローカル系
	SPR_OMP(parallel sections)
	{
		SPR_OMP(section)
		CompStiffnessMatrix();
		SPR_OMP(section)
		CompMassMatrix();
	}	
	CompRayleighDampingMatrix();

	/// 各種変数の初期化
	int NDof = NVertices() * 3;
	xdl.resize(NDof, 0.0);//FEMメッシュの座標系での変位
	vl.resize(NDof, 0.0);
	al.resize(NDof, 0.0);
	fl.resize(NDof, 0.0);
	boundary.resize(NDof, 0.0);
	boundary.clear();
	GetVerticesDisplacement(xdl);		// FemVertexから変位を取ってくる
	//CompInitialCondition(matMIni, matKIni, matCIni, fl, xdl, vl, al);

	// テスト（境界条件の付加）
	std::vector< int > veIds, veIds1, veIds2;


	
	// phpipe用
	//veIds1 = FindVertices(521, Vec3d(1.0, 0.0, 0.0));
	//veIds2 = FindVertices(1, Vec3d(-1.0, 0.0, 0.0));
	//std::set_union(veIds1.begin(), veIds1.end(), veIds2.begin(), veIds2.end(), back_inserter(veIds));
	//for(int i = 0; i < (int)veIds.size(); i++){
	//	DSTR << veIds[i] << std::endl;
	//}

	//phPipemini用
	//veIds.push_back(10);
	//veIds.push_back(11);
	//veIds.push_back(12);
	//veIds.push_back(13);

	//phPipeminibox用
	//veIds.push_back(1);
	//veIds.push_back(2);
	//veIds.push_back(4);
	//veIds.push_back(5);

	//// phboard用
	//
	//fixedVertices.push_back(35);
	//fixedVertices.push_back(34);
	
	//fixedVertices.push_back(37);
	//fixedVertices.push_back(36);
	
  //四点接地
	//veIds.push_back(40);
	//veIds.push_back(41);

	//veIds.push_back(38);
	//veIds.push_back(39);


	//// phSphere用
	//for(int i = 49; i < 58; i++){
	//	veIds.push_back(i);
	//}

	////phBunny用
	//veIds = FindVertices(123, Vec3d(0.0, -1.0, 0.0));
	//for(int i = 0; i < (int)veIds.size(); i++){
	//	DSTR << veIds[i] << std::endl;
	//}

	//// phRing用
	//veIds.push_back(24);
	//veIds.push_back(25);
	//veIds.push_back(44);
	//for(int i = 0; i < (int)veIds.size(); i++){
	//	DSTR << veIds[i] << std::endl;
	//}
	
	//// phStick用
	//veIds.push_back(54);
	//veIds.push_back(55);
	//veIds.push_back(46);
	//veIds.push_back(47);
	
	//phStick 片持ち
	//veIds.push_back(0);
	//veIds.push_back(7);
	//veIds.push_back(5);
	//veIds.push_back(6);
	const char *stmp = GetPHFemMesh()->GetName();

	if (strcmp(stmp, "femMesh") == 0) {
		//int arr[8] = {0,7,1,2,3,4,5,6};
		//fixedVertices.insert(fixedVertices.end(), arr, arr+8);
		
		//int arr[8] = {0,1,2,3,4,5,6,7}; 
		//fixedVertices.insert(fixedVertices.end(), arr, arr+8);

		//int arr[6] = {25,13,18,7,17,16};   //TWO LEG EXPERIMENT
		//fixedVertices.insert(fixedVertices.end(), arr, arr+6);   //TWO LEG EXPERIMENT

		//int arr[7] = {13,14,28,4,83,38,34};   //MEASUREMENT EXPERIMENT
		//fixedVertices.insert(fixedVertices.end(), arr, arr+7);   //MEASUREMENT EXPERIMENT

		//int arr[4] = {74,76,75,77};   //MEASUREMENT EXPERIMENT
		//fixedVertices.insert(fixedVertices.end(), arr, arr+4);   //MEASUREMENT EXPERIMENT

		//int arr[4] = {91,94,175,174};   //MEASUREMENT EXPERIMENT
		//fixedVertices.insert(fixedVertices.end(), arr, arr+4);   //MEASUREMENT EXPERIMENT

		//int arr[4] = {91,94,175,174};   //MEASUREMENT EXPERIMENT
		//fixedVertices.insert(fixedVertices.end(), arr, arr+4);   //MEASUREMENT EXPERIMENT

		int arr[4] = {587,586,137,544};   //GOMU BEAM DETAILED
		fixedVertices.insert(fixedVertices.end(), arr, arr+4);   //GOMU BEAM DETAILED
	}

	//if ( (strcmp(stmp, "femMeshi") == 0) || (strcmp(stmp, "femMeshii") == 0) ) {
		//int arr[19] = {19,29,18,30,20,53,3,50,81,2,76,32,65,1,27,22,52,21,49};
		//fixedVertices.insert(fixedVertices.end(), arr, arr+19);
		/*int arr[33] = {19,29,18,30,20,
					 53,55,43,39,49,
					 3,37,59,0,21,
					 50,41,45,63,35,52,
					 81,82,71,57,
					 2,76,32,65,1,62,27,22};
		fixedVertices.insert(fixedVertices.end(), arr, arr+33);*/
		//int arr[5] = {13,14,33,27,32};
		//fixedVertices.insert(fixedVertices.end(), arr, arr+5);
		//int arr[4] = {19,54,38,31};
		//fixedVertices.insert(fixedVertices.end(), arr, arr+4);
		//int arr[6] = {30,32,18,11,33,23};   //TWO LEG EXPERIMENT JUST CORNERS
		//fixedVertices.insert(fixedVertices.end(), arr, arr+6);   //TWO LEG EXPERIMENT JUST CORNERS
		//int arr[22] = {11,42,10,34,12,38,18,37,17,51,23,50,29,53,31,39,33,40,3,41,30,32};   //TWO LEG EXPERIMENT ALL BOTTOM
		//fixedVertices.insert(fixedVertices.end(), arr, arr+22);   //TWO LEG EXPERIMENT ALL BOTTOM

		//int arr[8] = {30,32,18,11,33,23,34,53 };   //TWO LEG EXPERIMENT JUST CORNERS
		//fixedVertices.insert(fixedVertices.end(), arr, arr+8);   //TWO LEG EXPERIMENT JUST CORNERS

		//int arr[8] = {48,50,52,53,40,42,43,45};   //MEASURMENT EXPERIMENT POINTER LEGS
		//fixedVertices.insert(fixedVertices.end(), arr, arr+8);   //MEASUREMENT EXPERIMENT POINTER LEGS

		//int arr[8] = {59,26,8,45,60,46,9,24};   //GOMU BEAM 
		//fixedVertices.insert(fixedVertices.end(), arr, arr+8);   //GOMU BEAM

		//int arr[8] = {46,60,24,9,47,6,21,10};   //GOMU BEAM DETEAILEDD 20
		//fixedVertices.insert(fixedVertices.end(), arr, arr+8);   //GOMU BEAM DETAILED 20

		//int arr[6] = {142,138,269,206,273,210};   //GOMU BEAM DETEAILEDD 30
		//fixedVertices.insert(fixedVertices.end(), arr, arr+6);   //GOMU BEAM DETAILED 30

		//int arr[5] = {142,138,269,71,54};   //GOMU BEAM DETEAILEDD 30
		//fixedVertices.insert(fixedVertices.end(), arr, arr+5);   //GOMU BEAM DETAILED 30

		//int arr[9] = {2, 4, 5, 7,23,25,29,27,56};
		//fixedVertices.insert(fixedVertices.end(), arr, arr+9);   //CUBE 
	//}

	Vec3i con = Vec3i(1,1,1);
	for(int i = 0; i < (int)fixedVertices.size(); i++){
		AddBoundaryCondition(fixedVertices[i], con);
	//	std::cout << fixedVertices[i] << std::endl;
	}

	ReduceMatrixSize(matMp, boundary);
	ReduceMatrixSize(matCp, boundary);
	ReduceMatrixSize(matKp, boundary);
	DSTR << "All matrices has reduced." << std::endl;
	//++//
	//CompRayleighDampingMatrixByDampingRatio();

	if(analysis_mode == PHFemVibrationDesc::ANALYSIS_MODAL){
			InitModalAnalysis(matMp, matKp, matCp, flp, vdt, bRecomp, xdlp, vlp, alp, nMode);
	}

	DSTR << "Initializing Completed." << std::endl;
} 

void PHFemVibration::CompStiffnessMatrix(){
	PHFemMeshNew* mesh = phFemMesh;
	const int NTets = (int)mesh->tets.size();
	const int NDof = NVertices() * 3;
	matKIni.resize(NDof, NDof, 0.0);	// 初期化

	//SPR_OMP(parallel for)
	for(int i = 0; i < NTets; i++){
		// 要素行列の計算
		/// tetが持つ頂点順
		/// 要素剛性行列 u = (u0, v0, w0,  ..., un-1, vn-2, wn-1)として計算

		/// 形状関数の計算（頂点座標に応じて変わる）
		PTM::TMatrixRow< 4, 4, element_type > matCoeff;
		matCoeff.assign(mesh->CompTetShapeFunctionCoeff(i, true));
		TVector<4, element_type > b, c, d;	// 形状関数の係数
		b.assign(matCoeff.col(1));
		c.assign(matCoeff.col(2));
		d.assign(matCoeff.col(3));

		/// 行列B（ひずみ-変位）
		PTM::TMatrixRow< 6, 12, element_type > matB;
		matB.clear(0.0);
		matB[0][0] = b[0];	matB[0][3] = b[1];	matB[0][6] = b[2];	matB[0][9] = b[3];
		matB[1][1] = c[0];	matB[1][4] = c[1];	matB[1][7] = c[2];	matB[1][10] = c[3];
		matB[2][2] = d[0];	matB[2][5] = d[1];	matB[2][8] = d[2];	matB[2][11] = d[3];
		matB[3][0] = c[0];	matB[3][1] = b[0];	matB[3][3] = c[1];	matB[3][4] = b[1];	matB[3][6] = c[2];	matB[3][7] = b[2];	matB[3][9] = c[3];	matB[3][10] = b[3];
		matB[4][1] = d[0];	matB[4][2] = c[0];	matB[4][4] = d[1];	matB[4][5] = c[1];	matB[4][7] = d[2];	matB[4][8] = c[2];	matB[4][10] = d[3];	matB[4][11] = c[3];
		matB[5][0] = d[0];	matB[5][2] = b[0];	matB[5][3] = d[1];	matB[5][5] = b[1];	matB[5][6] = d[2];	matB[5][8] = b[2];	matB[5][9] = d[3];	matB[5][11] = b[3];
		const double volume = mesh->CompTetVolume(i, true);
		element_type div = 1.0 / (6.0 * volume);
		matB *= div;

		/// 弾性係数行列Dの計算（応力-ひずみ）
		/// （ヤング率、ポアソン比に応じてかわる）
		double E = GetYoungModulus();
		double v = GetPoissonsRatio();
		double av = 1.0 - v;
		double bv = 1.0 - 2.0 * v;
		double cv = 0.5 - v;
		double Em;
		if(bv == 0.0) Em = DBL_MAX; /// 変形しない。ほんとうは+∞になる。
		else Em = E / ((1.0 + v) * bv);
		PTM::TMatrixRow< 6, 6, element_type > matD;
		PTM::TMatrixRow< 6, 6, element_type > matDs;
		matD.clear(0.0);
		matD[0][0] = av;	matD[0][1] = v;		matD[0][2] = v;
		matD[1][0] = v;		matD[1][1] = av;	matD[1][2] = v;
		matD[2][0] = v;		matD[2][1] = v;		matD[2][2] = av;
		matD[3][3] = cv;
		matD[4][4] = cv;
		matD[5][5] = cv;
		matDs.assign(matD);
		matD *= Em;

		/// 要素剛性行列の計算(エネルギー原理）
		TMatrixRow< 12, 12, element_type > matKe;
		matKe.clear(0.0);
		matKe = matB.trans() * matD * matB * volume;
		
		// 全体剛性行列の計算
		// 頂点番号順 u = (u0, v0, w0,  ..., un-1, vn-2, wn-1)として計算
		// j:ブロック番号, k:ブロック番号
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				int id = mesh->tets[i].vertexIDs[j];
				int id2 = mesh->tets[i].vertexIDs[k];
				int t = id * 3;	int l = id2 * 3;
				int h = 3;		int w = 3;
				int te = j * 3;	int le = k * 3;
				matKIni.vsub_matrix(t, l, h, w) += matKe.vsub_matrix(te, le, h, w);
			}
		}
	}
	matKp.assign(matKIni);
}

void PHFemVibration::CompMassMatrix(){
	/// 質量行列の計算
	double totalMass = 0.0;
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	const int NTets = (int)mesh->NTets();
	const int NDof = NVertices() * 3;
	matMIni.resize(NDof, NDof, 0.0);	// 初期化

	for(int i = 0; i < NTets; i++){
		/// 要素剛性行列 u = (u0, v0, w0,  ..., un-1, vn-2, wn-1)として計算
		TMatrixRow< 12, 12, element_type > matMe;
		matMe.clear(0.0);
		TMatrixRow< 3, 3, element_type > I;
		I.clear(0.0);
		I[0][0] = 1.0; I[1][1] = 1.0; I[2][2] = 1.0;
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				int t = j * 3;
				int l = k * 3;
				int h = 3;
				int w = 3;
				if(j == k){
					matMe.vsub_matrix(t, l, h, w) = 2.0 * I;
				}else{
					matMe.vsub_matrix(t, l, h, w) = I;
				}
			}
		}
		const double volume = mesh->CompTetVolume(i, true);
		matMe *= GetDensity() * volume / 20.0;
		//totalMass += (density * 3 * volume);    //TAKEAHANA'S DENSITY TRICK
		totalMass += (density * volume);
		
		// 全体質量行列の計算
		// 頂点番号順 u = (u0, v0, w0,  ..., un-1, vn-2, wn-1)として計算
		// j:ブロック番号, k:ブロック番号
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				int id = mesh->GetTetVertexIds(i)[j];
				int id2 = mesh->GetTetVertexIds(i)[k];
				int t = id * 3;	int l = id2 * 3;
				int h = 3;		int w = 3;
				int te = j * 3;	int le = k * 3;
				matMIni.vsub_matrix(t, l, h, w) += matMe.vsub_matrix(te, le, h, w);
			}
		}
	}
	matMp.assign(matMIni);
	mesh->GetPHSolid()->SetMass(totalMass);
}

void PHFemVibration::CompRayleighDampingMatrix(){
	/// 減衰行列の計算（比例減衰）境界条件導入済み
	matCIni.assign(GetAlpha() * matMIni + GetBeta() * matKIni);
	matCp.assign(matCIni);
}

void PHFemVibration::CompRayleighDampingMatrixByDampingRatio(){
	// 減衰行列の計算
	// 固有値・固有ベクトルを求める
	VVectord evalue;
	VMatrixRd evector;
	CompEigenValue(matMp, matKp, 0, nMode, evalue, evector);
	// 固有振動数
	VVectord ew;
	CompEigenVibrationFrequency(evalue, ew);
	// 固有角振動数
	VVectord ewrad;
	CompEigenAngularVibrationFrequency(evalue, ewrad);

	// レイリー減衰係数
	double tw[2];
	tw[0] = ewrad[0];
	tw[1] = ewrad[ewrad.size() - 1];
	double a, b;
	CompRayleighDampingCoeffcient(tw, dampingRatio, a, b);
	DSTR << "Reiley coefficient" << std::endl;
	DSTR << a << " " << b << std::endl;
	std::cout << "Reiley coefficient" << std::endl;
	std::cout << a << " "<< b << std::endl;
	SetAlpha(a);
	SetBeta(b);
	CompRayleighDampingMatrix();
	// 全ての減衰比
	VVectord dratio;
	dratio.resize(ewrad.size(), 0.0);
	for(int i = 0; i < (int)dratio.size(); i++){
		dratio[i] = CompModalDampingRatio(ewrad[i]);
	}
	DSTR << "modal damping ratio" << std::endl;
	DSTR << dratio << std::endl;
}

void PHFemVibration::Step(){
	// FemVertexから変位をとってくる
	qtimer.StartPoint("step");
	qtimer.StartPoint("reduce");
	GetVerticesDisplacement(xdl);
	VVectord xdlp;
	xdlp.assign(xdl);
	VVectord vlp;
	vlp.assign(vl);
	VVectord alp;
	alp.assign(al);
	VVectord flp;
	flp.assign(fl);
	//ReduceVectorSize(flp, boundary);
	ReduceVectorSize(xdlp, vlp, alp, flp, boundary);
	qtimer.EndPoint("reduce");


	// 全頂点の更新フラグ初期化
	GetPHFemMesh()->SetVertexUpdateFlags(false);

	qtimer.StartPoint("integration");
	switch(analysis_mode){
		case PHFemVibrationDesc::ANALYSIS_DIRECT:
			{
				static VMatrixRe matSInv;
				if(bRecomp){
					bRecomp = false;
					matSInv.resize(matMp.height(), matMp.width(), 0.0);
					InitNumericalIntegration(matMp, matKp, matCp, vdt, matSInv);
				}
				NumericalIntegration(matSInv, matKp, matCp, flp, vdt, xdlp, vlp, alp);
			}
			break;
		case PHFemVibrationDesc::ANALYSIS_MODAL:
			ModalAnalysis(matMp, matKp, matCp, flp, vdt, bRecomp, xdlp, vlp, alp, nMode);
			break;
		default:
			break;
	}
	qtimer.EndPoint("integration");

	fl.clear(0.0);
	// 計算結果をFemVertexに反映
	qtimer.StartPoint("gain");
	AssignVector(xdlp, xdl, boundary);
	AssignVector(vlp, vl, boundary);
	AssignVector(alp, al, boundary);
	qtimer.EndPoint("gain");
	UpdateVerticesPosition(xdl);
	UpdateVerticesVelocity(vl);
		qtimer.EndPoint("step");

	static int count = 0;
	count++;
	if(count == 5000) qtimer.FileOut("time.xls");
}

void PHFemVibration::InitNumericalIntegration(const VMatrixRe& _M, const VMatrixRe& _K, const VMatrixRe& _C, const double& _dt, VMatrixRe& _SInv){
	switch(integration_mode){
		case PHFemVibrationDesc::INT_EXPLICIT_EULER:
			InitExplicitEuler(_M, _SInv);
			break;
		case PHFemVibrationDesc::INT_IMPLICIT_EULER:
			//ImplicitEuler(_M.inv(), _K, _C, _f, _dt, _xd, _v);
			break;
		case PHFemVibrationDesc::INT_SIMPLECTIC:
			InitSimplectic(_M, _SInv);
			break;
		case PHFemVibrationDesc::INT_NEWMARK_BETA:
			InitNewmarkBeta(_M, _K, _C, _dt, _SInv, 1.0/4.0);
			break;
		default:
			break;
	}
}

void PHFemVibration::NumericalIntegration(const VMatrixRe& _SInv, const VMatrixRe& _K, const VMatrixRe& _C, 
		const VVectord& _f, const double& _dt, VVectord& _xd, VVectord& _v, VVectord& _a){
	/// 数値積分
	switch(integration_mode){
		case PHFemVibrationDesc::INT_EXPLICIT_EULER:
			ExplicitEuler(_SInv, _K, _C, _f, _dt, _xd, _v);
			break;
		case PHFemVibrationDesc::INT_IMPLICIT_EULER:
			//ImplicitEuler(_M.inv(), _K, _C, _f, _dt, _xd, _v);
			break;
		case PHFemVibrationDesc::INT_SIMPLECTIC:
			Simplectic(_SInv, _K, _C, _f, _dt, _xd, _v);
			break;
		case PHFemVibrationDesc::INT_NEWMARK_BETA:
			NewmarkBeta(_SInv, _K, _C, _f, _dt, _xd, _v, _a, 1.0/4.0);
			break;
		default:
			break;
	}
}

void PHFemVibration::InitNumericalIntegration(const double& _m, const double& _k, const double& _c, const double& _dt, double& _sInv){
	/// 数値積分
	switch(integration_mode){
		case PHFemVibrationDesc::INT_EXPLICIT_EULER:
			InitExplicitEuler(_m, _sInv);
			break;
		case PHFemVibrationDesc::INT_IMPLICIT_EULER:
			break;
		case PHFemVibrationDesc::INT_SIMPLECTIC:
			InitSimplectic(_m, _sInv);
			break;
		case PHFemVibrationDesc::INT_NEWMARK_BETA:
			InitNewmarkBeta(_m, _k , _c, _dt, _sInv, 1.0/4.0);
			break;
		default:
			break;
	}
}

void PHFemVibration::NumericalIntegration(const double& _sInv, const double& _k, const double& _c, 
	const double& _f, const double& _dt, double& _x, double& _v, double& _a){
	/// 数値積分
	switch(integration_mode){
		case PHFemVibrationDesc::INT_EXPLICIT_EULER:
			ExplicitEuler(_sInv, _k, _c, _f, _dt, _x, _v);
			break;
		case PHFemVibrationDesc::INT_IMPLICIT_EULER:
			break;
		case PHFemVibrationDesc::INT_SIMPLECTIC:
			Simplectic(_sInv, _k, _c, _f, _dt, _x, _v);
			break;
		case PHFemVibrationDesc::INT_NEWMARK_BETA:
			NewmarkBeta(_sInv, _k, _c, _f, _dt, _x, _v, _a, 1.0/4.0);
			break;
		default:
			break;
	}
}

// モード解析初期化（レイリー減衰系）
//#define USE_MATRIX 1
//#define USE_SUBSPACE 1
void PHFemVibration::InitModalAnalysis(const VMatrixRe& _M, const VMatrixRe& _K, const VMatrixRe& _C, 
		const VVectord& _f, const double& _dt, bool& bFirst, VVectord& _xd, VVectord& _v, VVectord& _a, const int nmode){

	// 固有値・固有ベクトルを求める
		size_t size = _M.height();
		evalue.resize(nmode, 0.0);
		evector.resize(size, nmode, 0.0);
		qtimer.StartPoint("CompEigen");
		if (this->fixedVertices.size() == 0) {
			CompEigenValue(_M, _K, 6, nmode, evalue, evector);
		} else {
			CompEigenValue(_M, _K, 0, nmode, evalue, evector); }
		qtimer.EndPoint("CompEigen");

		q.resize(nmode,0);
		qv.resize(nmode,0);
		qa.resize(nmode,0);
		qf.resize(nmode,0);


		// MK系の固有振動数
		VVectord ew;
		CompEigenVibrationFrequency(evalue, ew);
		// MK系の固有角振動数
		VVectord ewrad;
		CompEigenAngularVibrationFrequency(evalue, ewrad);
		// レイリー減衰係数
		double tw[2];
		tw[0] = ewrad[0];
		tw[1] = ewrad[ewrad.size() - 1];

		double dampingratio[2];
		dampingratio[0] = 0.5 * (GetAlpha() / tw[0] + tw[0] * GetBeta());
		dampingratio[1] = 0.5 * (GetAlpha() / tw[1] + tw[1] * GetBeta());
		DSTR << "damiping ratio" << std::endl;
		DSTR << dampingratio[0] << " " << dampingratio[1] << std::endl;

		// モード質量、剛性, 減衰行列の計算
        #ifdef USE_OPENMP_PHYSICS
		# pragma omp parallel sections
        #endif
		{
            #ifdef USE_OPENMP_PHYSICS
            # pragma omp section
            #endif
			Mm.assign(evector.trans() * _M * evector);

            #ifdef USE_OPENMP_PHYSICS
            # pragma omp section
            #endif
			Km.assign(evector.trans() * _K * evector);

            #ifdef USE_OPENMP_PHYSICS
            # pragma omp section
            #endif
			Cm.assign(evector.trans() * _C * evector);

            #ifdef USE_OPENMP_PHYSICS
            # pragma omp section
            #endif
			SmInv.resize(nmode, nmode, 0.0);
		}

#ifdef USE_MATRIX
		InitNumericalIntegration(Mm, Km, Cm, _dt, SmInv);
#else
		for(int i = 0; i < nmode; i++){
			InitNumericalIntegration(Mm[i][i], Km[i][i], Cm[i][i], _dt, SmInv[i][i]);
		}
#endif
		DSTR << "Initializing modal analysis complete." << std::endl;
		std::cout << "Initializing modal analysis complete."<< std::endl;
		
}

// モード解析法（レイリー減衰系）
//#define USE_MATRIX 1
//#define USE_SUBSPACE 1
void PHFemVibration::ModalAnalysis(const VMatrixRe& _M, const VMatrixRe& _K, const VMatrixRe& _C, 
		const VVectord& _f, const double& _dt, bool& bFirst, VVectord& _xd, VVectord& _v, VVectord& _a, const int nmode){
	//DSTR << "//////////////////////////////////" << std::endl;

	qtimer.StartPoint("integration core");
	/*
	//_xdなどは拘束を入れた頂点変位ベクトル(xdlp)→変化のあった頂点だけ取る
	PHFemMeshNew* mesh = GetPHFemMesh();
	const int NVer = NVertices() ;
	VVectord  _xdp , _vp , _ap , _Mp;	

	_xdp.resize(NVer * 3 , 0.0 );//初期化
	_vp.resize(NVer * 3 , 0.0 );
	_ap.resize(NVer * 3 , 0.0 );
	_Mp.resize(NVer * 3 , 0.0 );

	int counter = 0;
	for(int i = 0; i < NVer; i++){
		int id = i * 3;
		if(mesh->vertices[i].bUpdated == true){//取り出し
				_xdp[counter] = _xd[id];
			_xdp[counter + 1] = _xd[id +1];
			_xdp[counter + 2] = _xd[id +2];

			_vp[counter] = _v[id];
			_vp[counter + 1] = _v[id +1];
			_vp[counter + 2] = _v[id +2];

			_ap[counter] = _a[id];
			_ap[counter + 1] = _a[id +1];
			_ap[counter + 2] = _a[id +2];

			counter += 3;
			_Mp = _M.col(id);
		}
	}
	if(counter!=0){
		_xdp.resize(counter * 3);
		_vp.resize(counter * 3);
		_ap.resize(counter * 3);
	}
	else{ 
		_xdp.resize(NVer * 3,0.0);
		_vp.resize(NVer * 3,0.0);
		_ap.resize(NVer * 3,0.0);
		_Mp.resize(NVer * 3,0.0);
	}
	*/

	// デカルト座標からモード座標系に変換
	//q.assign(evector.trans() * (_M * _xd));
	//qv.assign(evector.trans() * (_M * _v));
	//qa.assign(evector.trans() * (_M * _a));
	qf.assign(evector.trans() * _f);

	// 積分
#ifdef USE_MATRIX
	// 行列で計算
	NumericalIntegration(SmInv, Km, Cm, qf, _dt, q, qv, qa); 
#else
	// 1次独立の連立方程式なので、各方程式毎に計算
	//#pragma omp parallel for
	VVectord  q_temp = q;
	VVectord qv_temp = qv;
	VVectord qa_temp = qa;

	for(int i = 0; i < nmode; i++){
		NumericalIntegration(SmInv[i][i], Km[i][i], Cm[i][i], qf[i], _dt, q[i], qv[i], qa[i]);
	}
#endif
	// モード座標系からデカルト座標系に変換
	
	
	_xd = evector * q;
	_v = evector * qv;
	_a = evector * qa;

	//std::cout << "evector=" << evector << std::endl;
	//std::cout << "" << std::endl;

/*
	const int NVer = NVertices() ;
	int counter = 0;
	for(int i = 0; i < NVer; i++){//160頂点
		for(int j=0 ;j < nmode; j++){//55モード
			int id = i * 3;//480　(160 * x,y,z)
			if(qv_temp[j]!=qv[j]){//そのモードの振動ベクトルが変化していたら
				_v[counter] = evector[id] * qv;
				_v[counter+1] = evector[id+1] * qv;
				_v[counter+2] = evector[id+2] * qv;
				counter += 3;
			}
		}
	}
	*/
	/*for(int i = 0; i < nmode; i++){	
		if(q_temp[i]==q[i]){
			_xd = evector[i] * q;
		}
		
		if(qv_temp[i]==qv[i]){
			_v[i] = evector[i] * qv;
		}
		if(qa_temp[i]==qa[i]){
			_a[i] = evector[i] * qa;
		}
	}
	*/
	qtimer.EndPoint("integration core");
}

void PHFemVibration::CompEigenValue(const VMatrixRd& _M, const VMatrixRd& _K, const int start, const int interval, VVectord& e, VMatrixRd& v){
#if 1
		// 境界条件導入済みのmatMp, matKpをつかう
		// 固有値・固有ベクトルを求める
		size_t size = _M.height();
		if (!size) return;
		e.resize(interval, 0.0);
		v.resize(size, interval, 0.0);
#if USE_SUBSPACE
		SubSpace(_K, _M, interval, 1e-5, e, v);
#else
		int info = sprsygvx(_K, _M, e, v, start, interval);
		assert(info == 0);
#endif
		DSTR << "eigenvalue" << std::endl;
		DSTR << e << std::endl;
		//DSTR << "eigenvector" << std::endl;
		//DSTR << v << std::endl;

#endif
}

void PHFemVibration::CompEigenVibrationFrequency(const VVectord& e, VVectord& w){
	// 固有振動数
	w.resize(e.size(), 0.0);
	for(int i = 0; i < (int)w.size(); i++){
		w[i] = sqrt(e[i]) / (2.0 * M_PI);
	}
	DSTR << "eigen Vibration Value" << std::endl;
	DSTR << w << std::endl;
}

void PHFemVibration::CompEigenAngularVibrationFrequency(const VVectord& e, VVectord& wrad){
	wrad.resize(e.size(), 0.0);
	for(int i = 0; i < (int)wrad.size(); i++){
		wrad[i] = sqrt(e[i]);
	}
	DSTR << "eigen Angular Vibration Value" << std::endl;
	DSTR << wrad << std::endl;
}

double PHFemVibration::CompModalDampingRatio(double wrad){
	return 0.5 * (GetAlpha() / wrad + GetBeta() * wrad);
}

void PHFemVibration::CompRayleighDampingCoeffcient(double wrad[2], double ratio[2], double& a, double& b){
	double tmp = (2.0 * wrad[0] * wrad[1]) / (pow(wrad[1], 2) - pow(wrad[0], 2));
	a = tmp * (wrad[1] * ratio[0] - wrad[0] * ratio[1]);
	b = tmp * ((ratio[1] / wrad[0]) - (ratio[0] / wrad[1]));
}

void PHFemVibration::SubSpace(const VMatrixRe& _K, const VMatrixRe& _M, 
	const int nmode, const double epsilon, VVectord& evalue, VMatrixRe& evector){
	DSTR << "Start Computing eigenvalues and eigenvectors by SubSpace method" << std::endl;
	const int size = (int)_K.height();
	if(_K.det() <= 0){
		DSTR << "_K Matrix is not regular matrix." << std::endl;
		return;
	}
	if(nmode > size) assert(0);
	/// 初期化
	evalue.resize(nmode, 0.0);			// 固有値
	evector.resize(size, nmode, 0.0);	// 固有ベクトル
	// 初期値ベクトル
	VMatrixRe y;
	y.resize(size, nmode, 0.0);
	VMatrixRe ylast;
	ylast.resize(size, nmode, 0.0);
	VVectord yini;
	yini.resize(size, 1.0);		// 初期値は1.0
	yini.unitize();
	for(int i = 0; i < nmode; i++){
		y.col(i) = yini;
		ylast.col(i) = yini;
	}	

	/// _M, _Kをコレスキー分解
	// _AInvの計算はコレスキー分解値を使ってfor文で計算したほうが速いはず。
	// 今は速さを気にせず逆行列を計算してる。
	VMatrixRe _Mc;
	_Mc.resize(size, size, 0.0);
	cholesky(_M, _Mc);	
	VMatrixRe _Kc;
	_Kc.resize(size, size, 0.0);
	cholesky(_K, _Kc);
	//DSTR << "cholesky" << std::endl;
	//DSTR << _Mc << std::endl;
	//DSTR << _Kc  << std::endl;

	VMatrixRe _AInv;			
	_AInv.resize(size, size, 0.0);
	_AInv = _Mc.trans() * (_Kc.inv()).trans() * _Kc.inv() * _Mc;

	qtimer.StartPoint("iteration");
	/// 反復計算
	for(int k = 0; k < nmode; k++){
		VVectord z;
		z.resize(size, 0.0);
		int cnt = 0;
		while(1){
			// zの計算
			z = _AInv * y.col(k);
			// 修正グラム・シュミット法でベクトルを直交化
			for(int i = 0; i < k; i++){
				double a = y.col(i) * z;
				z -= a * y.col(i);
			}
			y.col(k) = z;
			y.col(k).unitize();

			double error = 0.0;
			error = sqrt((ylast.col(k) - y.col(k)) * (ylast.col(k) - y.col(k)));
			ylast.col(k) = y.col(k);
			if(abs(error) < epsilon){
				//DSTR << cnt << std::endl;
				//DSTR << abs(error) << std::endl;
				break;
			}
			cnt++;
			if(cnt > 1e5){
				DSTR << "Can not converge in subspace" << std::endl;
				break;
			}
		}
		evector.col(k) = _Mc.trans().inv() * y.col(k);		// 固有ベクトル
		evalue[k] = 1.0 / (y.col(k) * _AInv * y.col(k));	// 固有値
	}
	qtimer.EndPoint("iteration");
}

//* 各種設定関数
/////////////////////////////////////////////////////////////////////////////////////////
void PHFemVibration::SetAnalysisMode(PHFemVibrationDesc::ANALYSIS_MODE mode){
	analysis_mode = mode;
}

void PHFemVibration::SetIntegrationMode(PHFemVibrationDesc::INTEGRATION_MODE mode){
	integration_mode = mode;
}

void PHFemVibration::GetVerticesDisplacement(VVectord& _xd){
	/// FemVertexから変位を取ってくる
	// u = (u0, v0, w0, ...., un-1, vn-1, wn-1)の順
	int NVer = NVertices();
	_xd.resize(NVer * 3);
	for(int i = 0; i < NVer; i++){
		int id = i * 3;
		Vec3d disp = GetPHFemMesh()->GetVertexDisplacementL(i);
		_xd[id] = disp.x;
		_xd[id + 1] = disp.y;		
		_xd[id + 2] = disp.z;
	}
}

void PHFemVibration::UpdateVerticesPosition(VVectord& _xd){
	/// 計算結果をFemVertexに戻す
	// u = (u0, v0, w0, ...., un-1, vn-1, wn-1)の順
	int NVer = NVertices();
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	for(int i = 0; i < NVer; i++){
		int id = i * 3;
		Vec3d initialPos = mesh->GetVertexInitalPositionL(i);
		Vec3d vpos(_xd[id] + initialPos.x, _xd[id + 1] + initialPos.y, _xd[id + 2] + initialPos.z);
		GetPHFemMesh()->SetVertexPositionL(i, vpos);
	}
}

void PHFemVibration::UpdateVerticesVelocity(VVectord& _v){
	/// 計算結果をFemVertexに戻す
	// u = (u0, v0, w0, ...., un-1, vn-1, wn-1)の順
	int NVer = NVertices();
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	for(int i = 0; i < NVer; i++){
		int id = i * 3;
		//Vec3d initialPos = mesh->GetVertexInitalPositionL(i);
		Vec3d vvel(_v[id], _v[id+1], _v[id+2]);
		GetPHFemMesh()->SetVertexVelocityL(i, vvel);
	}
}


std::vector< int > PHFemVibration::FindVertices(const int vtxId, const Vec3d _vecl){
	std::vector< int > ve;
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	Vec3d base = mesh->GetVertexPositionL(vtxId);
	for(int i = 0; i < mesh->NSurfaceVertices(); i++){
		Vec3d rel = mesh->GetVertexPositionL(mesh->GetSurfaceVertex(i)) - base;
		double dot = rel * _vecl;
		if(abs(dot) < 1e-1) ve.push_back(mesh->GetSurfaceVertex(i));
	}
	return ve;
}

bool PHFemVibration::AddBoundaryCondition(VMatrixRe& mat, const int id){
	int n = (int)mat.height();
	if(id > n - 1) return false;
	mat.col(id).clear(0.0);
	mat.row(id).clear(0.0);
	mat.item(id, id) = 1.0;
	return true;
}

bool PHFemVibration::AddBoundaryCondition(const int vtxId, const Vec3i dof = Vec3i(1, 1, 1)){
	int NVer = NVertices();

	//for(int j=0;j<= (NVer-1)*3 ;j++){
//		boundary[j]=0;
//	}

	if(0 <= vtxId && vtxId <= NVer -1){
		for(int i = 0; i < 3; i++){
			if(dof[i] == 1){
				const int id = vtxId * 3 + i;
				boundary[id] = 1;
			}

		}
		return true;
	}
	return false;
}

bool PHFemVibration::AddBoundaryCondition(const std::vector< Vec3i >& bcs){ 
	int NVer = NVertices();
	if(NVer != (int)bcs.size()) return false;
	for(int i = 0; i < (int)bcs.size(); i++){
		for(int j = 0; j < 3; j++){
			if(bcs[i][j] == 1){
				const int id = i + j;
				boundary[id] = 1;
			}
		}
	}
	return true;
}

void PHFemVibration::ReduceMatrixSize(VMatrixRe& mat, const VVector< int >& bc){
	int diff = 0;					// 削除した数
	for(int i = 0; i < (int)bc.size(); i++){
		if(bc[i] == 0) continue;
		int id = i - diff;			// 削除したい行列番号
		VMatrixRe tmp;
		tmp.resize(mat.height() - 1, mat.width() - 1, 0.0);
		for(int j = 0; j < (int)tmp.height(); j++){
			int row = j;
			if(j >= id) row++;
			for(int k = 0; k < (int)tmp.width(); k++){
				int col = k;
				if(k >= id) col++;
				tmp[j][k] = mat[row][col];
			}
		}
		mat.assign(tmp);
		diff++;
	}
}

void PHFemVibration::ReduceMatrixSize(VMatrixRe& _M, VMatrixRe& _K, VMatrixRe& _C, const VVector< int >& bc){
	SPR_OMP(parallel sections)
	{
		SPR_OMP(section)
		ReduceMatrixSize(_M, bc);
		SPR_OMP(section)
		ReduceMatrixSize(_K, bc);
		SPR_OMP(section)
		ReduceMatrixSize(_C, bc);
	}
}

void PHFemVibration::ReduceVectorSize(VVectord& r, const VVector< int >& bc){
	int diff = 0;					// 削除した数
	for(int i = 0; i < (int)bc.size(); i++){
		if(bc[i] == 0) continue;
		int id = i - diff;			// 削除したい位置
		VVectord tmp;
		tmp.resize(r.size() - 1, 0.0);
		for(int j = 0; j < (int)tmp.size(); j++){
			int index = j;
			if(j >= id) index++;
			tmp[j] = r[index];
		}
		r.assign(tmp);
		diff++;
	}
}

void PHFemVibration::ReduceVectorSize(VVectord& _xd, VVectord& _v, VVectord& _a, VVectord& _f,const VVector< int >& bc){
	SPR_OMP(parallel sections)
	{
		SPR_OMP(section)
		ReduceVectorSize(_xd, boundary);
		SPR_OMP(section)
		ReduceVectorSize(_v, boundary);
		SPR_OMP(section)
		ReduceVectorSize(_a, boundary);
		SPR_OMP(section)
		ReduceVectorSize(_f, boundary);	
	}
}

void PHFemVibration::AssignVector(const VVectord& from, VVectord& to, const VVector< int >& bc){
	int diff = 0;
	for(int i = 0; i < (int)bc.size(); i++){
		if(bc[i] > 0){
			diff++;
			continue;
		}
		to[i] = from[i-diff];
	}
}

bool PHFemVibration::AddVertexForceL(int vtxId, Vec3d fL){
	if(0 <= vtxId && vtxId <= NVertices() -1){
		int id = vtxId * 3;
		fl[id] += fL.x;
		fl[id + 1] += fL.y;
		fl[id + 2] += fL.z;
		return true;
	}
	return false;
}

bool PHFemVibration::AddVertexForceW(int vtxId, Vec3d fW){
	if(0 <= vtxId && vtxId <= NVertices() -1){
		Vec3d fL = GetPHFemMesh()->GetPHSolid()->GetOrientation().Inv() * fW;
		AddVertexForceL(vtxId, fL);
		return true;
	}
	return false;
}

bool PHFemVibration::AddVertexForceW(std::vector< Vec3d > fWs){
	if(NVertices() != (int)fWs.size()) return false;
	for(int i = 0; i < (int)fWs.size(); i++){
		Vec3d fL = GetPHFemMesh()->GetPHSolid()->GetOrientation().Inv() * fWs[i];
		AddVertexForceL(i, fL);
	}
	return true;
}

bool PHFemVibration::AddForce(int tetId, Vec3d posW, Vec3d fW){
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	Posed inv = mesh->GetPHSolid()->GetPose().Inv();
	Vec3d posL = inv * posW;
	Vec3d fL = inv * fW;
	Vec4d v;

	//if(!mesh->CompTetShapeFunctionValue(tetId, posL, v, false)) return false;
	mesh->CompTetShapeFunctionValue(tetId, posL, v, true);
	for(int i = 0; i < 4; i++){
		int vtxId = mesh->GetTetVertexIds(tetId)[i];
		mesh->SetVertexUpateFlag(vtxId, true);	//更新フラグ
		Vec3d fdiv = v[i] * fL;
		AddVertexForceL(vtxId, fdiv);
	}
	return true;
}

bool PHFemVibration::AddForceL(int tetId, Vec3d posW, Vec3d fL){
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	Posed inv = mesh->GetPHSolid()->GetPose().Inv();
	Vec3d posL = inv * posW;
	//Vec3d fL = inv * fW;
	Vec4d v;

	//if(!mesh->CompTetShapeFunctionValue(tetId, posL, v, true)) { DSTR << "ERRORL" << std::endl; return false; }
	mesh->CompTetShapeFunctionValue(tetId, posL, v, true);
	//DSTR << this->GetName()  << " : " << tetId << std::endl;
	for(int i = 0; i < 4; i++){
		int vtxId = mesh->GetTetVertexIds(tetId)[i];
		mesh->SetVertexUpateFlag(vtxId, true);	//更新フラグ  Update Flag

		Vec3d fdiv = v[i] * fL;
		AddVertexForceL(vtxId, fdiv);
	}
	return true;
}

bool PHFemVibration::SetDamping(int tetId, Vec3d posW, double damp_ratio){
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	Posed inv = mesh->GetPHSolid()->GetPose().Inv();
	Vec3d posL = inv * posW;
	Vec4d v;
	if(!mesh->CompTetShapeFunctionValue(tetId, posL, v, false)) return false;
	for(int i = 0; i < 4; i++){
		int vtxId = mesh->GetTetVertexIds(tetId)[i];
		mesh->SetVertexUpateFlag(vtxId, true);	//更新フラグ 
		double r = pow(damp_ratio, v[i]);
		if(0 <= vtxId && vtxId <= NVertices() -1){
			int id = vtxId * 3;
			vl[id] *= r;
			vl[id + 1] *= r;
			vl[id + 2] *= r;

			return true;
		}
	}
	return true;
}


bool PHFemVibration::SetDampingRatio(){
	dampingRatio[0] = 0.08;
	dampingRatio[1] = 0.1;
	SetAlpha(55.5414);
	SetBeta(8.78132e-008);
	std::cout << ""<< std::endl;
	std::cout << "Rayleigh" << std::endl;
	std::cout << GetAlpha() << " "<< GetBeta() << std::endl;
	Init();
	bRecomp = true;

	return true;
}



bool PHFemVibration::GetDisplacement(int tetId, Vec3d posW, Vec3d& disp, bool bDeform){
	disp = Vec3d();
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	Posed inv = mesh->GetPHSolid()->GetPose().Inv();
	Vec3d posL = inv * posW;
	Vec4d v;
	if(!mesh->CompTetShapeFunctionValue(tetId, posL, v, bDeform)) return false;
	for(int i = 0; i < 4; i++){
		int vtxId = mesh->GetTetVertexIds(tetId)[i];
		disp += mesh->GetVertexDisplacementL(vtxId) * v[i];
	}
	mesh->GetPHSolid()->GetPose() * disp;
	return true;
}

bool PHFemVibration::GetVelocity(int tetId, Vec3d posW, Vec3d& vel, bool bDeform){
	vel = Vec3d();
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	Posed inv = mesh->GetPHSolid()->GetPose().Inv();
	Vec3d posL = inv * posW;
	Vec4d v;
	//if(!mesh->CompTetShapeFunctionValue(tetId, posL, v, bDeform)) return false;
	mesh->CompTetShapeFunctionValue(tetId, posL, v, bDeform);
	for(int i = 0; i < 4; i++){
		int vtxId = mesh->GetTetVertexIds(tetId)[i];
		vel += mesh->GetVertexVelocityL(vtxId) * v[i];
	}
	mesh->GetPHSolid()->GetPose() * vel;
	return true;
}

bool PHFemVibration::GetPosition(int tetId, Vec3d posW, Vec3d& pos, bool bDeform){
	pos = Vec3d();
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	Posed inv = mesh->GetPHSolid()->GetPose().Inv();
	Vec3d posL = inv * posW;
	Vec4d v;
	//if(!mesh->CompTetShapeFunctionValue(tetId, posL, v, bDeform)) return false;
	mesh->CompTetShapeFunctionValue(tetId, posL, v, bDeform);
	for(int i = 0; i < 4; i++){
		int vtxId = mesh->GetTetVertexIds(tetId)[i];
		pos += mesh->GetVertexPositionL(vtxId) * v[i];
	}
	mesh->GetPHSolid()->GetPose() * pos;
	return true;
}

inline Vec3d CompFaceNormal(const Vec3d* pos) {
	Vec3d vec[2];
	vec[0] = pos[1] - pos[0];
	vec[1] = pos[2] - pos[0];
	// FemMeshの頂点は表面から見て時計周りに並ぶ
	// 表面方向の法線は外積は反時計まわりにかける
	return (vec[1] % vec[0]).unit();
}

bool PHFemVibration::FindClosestPointOnMesh(const Vec3d& p, const Vec3d fp[3], Vec3d& cp, double& dist, bool bDeform){
	//PHFemMeshNewIf* mesh = GetPHFemMesh();
	const Vec3d normal = CompFaceNormal(fp);
	const Vec3d p0 = fp[0] - p;			// pからfp[0]までのベクトル
	dist = p0 * normal;					// pから面への距離
	const Vec3d ortho = dist * normal;	// pから面へのベクトル
	cp = p + ortho;						// pをface上に射影した位置(近傍点）

	// cpが面内にあるかどうか判定
	// 外積を取って、normalと同じ方向(内積が=>0)なら中、normalと逆方向(内積が< 0)なら外
	// 面の頂点は表面からみて時計まわり
	for(int j = 0; j < 3; j++){
		int index = j + 1;
		if(j == 2)	index = 0;
		Vec3d vec[2];
		vec[0] = (cp - fp[j]).unit();
		vec[1] = (fp[index] - fp[j]).unit();
		//DSTR << vec[0] << " " << vec[1] << std::endl;
		//DSTR << (vec[0] % vec[1]) * normal << std::endl;
		if((vec[0] % vec[1]) * normal < -EDGE_EPS) return false;
	}
	return true;	
}

bool PHFemVibration::FindNeighborFaces(Vec3d posW, std::vector< int >& faceIds, std::vector< Vec3d >& cpWs, bool bDeform){
	// ワールド座標系で計算
	faceIds.clear();
	cpWs.clear();
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	Posed pose = mesh->GetPHSolid()->GetPose();
//	std::vector< FemFace > faces = mesh->faces;
	int nsf = GetPHFemMesh()->NSurfaceFace();
	double dist = DBL_MAX;
	for(int i = 0; i < nsf; i++){
		Vec3d fp[3];
		for(int j = 0; j < 3; j++){
			int vid = mesh->GetFaceVertexIds(i)[j];
			if(bDeform)		fp[j] = pose * mesh->GetVertexPositionL(vid);
			else			fp[j] = pose * mesh->GetVertexInitalPositionL(vid);
		}
		Vec3d cpW;
		double d;
		if(!FindClosestPointOnMesh(posW, fp, cpW, d, bDeform)) continue;
		if(d < dist){
			// 前回よりも点-面間の距離が近い場合は近い方を選ぶ
			dist = d;
			faceIds.clear();
			cpWs.clear();
			faceIds.push_back(i);
			cpWs.push_back(cpW);
		}else if(d == dist){
			// 前回と距離が同じ場合は加える
			faceIds.push_back(i);
			cpWs.push_back(cpW);
		}
	}
	if(faceIds.size()) return true;
	else	return false;
}

bool PHFemVibration::FindNeighborTetrahedron(Vec3d posW, int& tetId, Vec3d& cpW, bool bDeform){
	std::vector< int > faceIds;
	std::vector< Vec3d > closestPoints;
	if(!FindNeighborFaces(posW, faceIds, closestPoints, bDeform)) return false;
	// 1点で力を加えたり、変位を取得したりする操作について
	// faceが1つ:点-面
	// faceが2つ:辺で接している、どちらか1つの面を選べば良い
	// faceが3つ:点で接している。これもどれか1つの面を選べば良い
	// 以上からひとつの四面体がわかれば良い
	tetId = GetPHFemMesh()->FindTetFromFace(faceIds[0]);
	cpW = closestPoints[0];

	//for(int i = 0; i < faceIds.size(); i++){
	//	DSTR << "faceId:" << faceIds[i] << std::endl;
	//	for(int j = 0; j < 3; j++){
	//		DSTR << "vertexId" << mesh->faces[faceIds[i]].vertexIDs[j] << std::endl;
	//	}
	//}
	return true;
}

void PHFemVibration::MatrixFileOut(VMatrixRe mat, std::string filename){
	std::ofstream ofs(filename.c_str());
	if (!ofs){
		DSTR << "Can not open the file : " << filename << std::endl;
		return;
	}

#if (_MSC_VER > 1500)
	ofs.precision(element_limit);
#endif
	for (int i = 0; i < (int)mat.height(); i++){
		for(int j = 0; j < (int)mat.width(); j ++){
			ofs << mat.item(i, j) << ",";
		}
		ofs << std::endl;
    }
    ofs.close();
}

//This function uses almost the same method as Susa to match to find
//the pointer on the FEM surface. But this method considers the
//contact normal and the tetra face normal to make it faster
bool PHFemVibration::searchSurfaceTetra(Vec3d commonPointW, Vec3d contactNormalU, int &faceId, Vec3d &surfacePoint, bool bDeform) {
	PHFemMeshNewIf* mesh = GetPHFemMesh();
	Posed pose = mesh->GetPHSolid()->GetPose();
	int nsf = mesh->NSurfaceFace();
	faceId = 0;

	double dist = DBL_MAX;
	for(int i = 0; i < nsf; i++){

		double cosine = (pose * mesh->GetFaceNormal(i)).unit() * contactNormalU;
		if (!(cosine > 0.9) ) {   // 0 degrees
			//DSTR << "DEBUG mesh " << mesh->femIndex << " : " << cosine  << " : " << i << std::endl; 
			continue; }  //Addition to the method

		Vec3d fp[3];
		for(int j = 0; j < 3; j++){
			int vid = mesh->GetFaceVertexIds(i)[j];
			if (bDeform)	fp[j] = pose * mesh->GetVertexPositionL(vid);
			else			fp[j] = pose * mesh->GetVertexInitalPositionL(vid);
		}
		Vec3d cpW; 
		double d;

		if(!FindClosestPointOnMesh(commonPointW, fp, cpW, d, bDeform)) continue;
		if(d < dist){
			// 前回よりも点-面間の距離が近い場合は近い方を選ぶ
			dist = d;
			faceId = i;
			surfacePoint = cpW;
		}else if(d == dist){
			faceId = i;
			surfacePoint = cpW;
		}
	}

	if(faceId) return true;
	else return false;
}

//gets the reduced index, to get values from the reduced matrix
int PHFemVibration::getReducedIndex(int vertexId) {
	//considering the reduced matrix to calculate the right index
	//the fixedVertices should be sort for this block to work

	int nfix = (int) fixedVertices.size();
	int jumps = 0;
	for (int i=0; i< nfix ;i++){
		 if (fixedVertices[i] < vertexId)
			 jumps++;
		 else
			 break; 
	}

	return (vertexId - jumps) * 3;
}

//Return the instant vertex position
bool PHFemVibration::GetInstantPosition(int vertexId, Vec3d& returnPosL) {
	
	Vec3d initialPos = GetPHFemMesh()->GetVertexInitalPositionL(vertexId);

	int id = getReducedIndex(vertexId);
	
	returnPosL[0] = (evector.row(id) * q) + initialPos.x;
	returnPosL[1] = (evector.row(id+1) * q) + initialPos.y;
	returnPosL[2] = (evector.row(id+2) * q) + initialPos.z;

	return true;
}

//Return the instant vertex velocity
bool PHFemVibration::GetInstantVelocity(int vertexId, Vec3d& returnVelL) {
	
	int id = getReducedIndex(vertexId);

	returnVelL[0] = (evector.row(id) * qv);
	returnVelL[1] = (evector.row(id+1) * qv);
	returnVelL[2] = (evector.row(id+2) * qv);
	return true;
}

//Return the instant vertex acceleration
bool PHFemVibration::GetInstantAcceleration(int vertexId, Vec3d& returnAccelL) {
	
	int id = getReducedIndex(vertexId);

	returnAccelL[0] = (evector.row(id) * qa);
	returnAccelL[1] = (evector.row(id+1) * qa);
	returnAccelL[2] = (evector.row(id+2) * qa);
	return true;
}

//Returns the mass of a simple tetra element
bool PHFemVibration::GetVertexMass(int vertexId, double& returnMass, bool bDeform){
	
	/*Vec3d returnMass;

	int id = vtxId * 3;
	returnMass[0] = matMp[id][id];
	returnMass[1] = matMp[id+1][id+1];
	returnMass[2] = matMp[id+2][id+2];
	return returnMass;*/

	PHFemMeshNew *mesh = this->GetPHFemMesh()->Cast();
	const double volume = mesh->CompTetVolume(vertexId, true);
	
	if (volume == 0.0) {return false;}

	returnMass = density * volume;  //Taken from Susa's code

	return true;
}

inline double PHFemVibration::TriArea2D(double x1, double y1, double x2, double y2, double x3, double y3)
{
	return (x1-x2)*(y2-y3) - (x2-x3)*(y1-y2);
}

void PHFemVibration::Barycentric(Vec3d fp[3], Vec3d& p, double &u, double &v, double &w)
{
	// Unnormalized triangle normal
	Vec3d a = fp[0];
	Vec3d b = fp[1];
	Vec3d c = fp[2];

	Vec3d m = (b - a)%(c - a);
	// Nominators and one-over-denominator for u and v ratios
	double nu, nv, ood;
	// Absolute components for determining projection plane
	double  x = abs(m.x), y = abs(m.y), z = abs(m.z);
	// Compute areas in plane of largest projection
	if(x>=y&&x>=z){
		// x is largest, project to the yz plane
		nu = TriArea2D(p.y, p.z, b.y, b.z, c.y, c.z); // Area of PBC in yz plane
		nv = TriArea2D(p.y, p.z, c.y, c.z, a.y, a.z); // Area of PCA in yz plane
		ood = 1.0f / m.x; // 1/(2*area of ABC in yz plane)
	} else if (y >= x && y >= z) {
		// y is largest, project to the xz plane
		nu = TriArea2D(p.x, p.z, b.x, b.z, c.x, c.z);
		nv = TriArea2D(p.x, p.z, c.x, c.z, a.x, a.z);
		ood = 1.0f / -m.y;
	} else {
		// z is largest, project to the xy plane
		nu = TriArea2D(p.x, p.y, b.x, b.y, c.x, c.y);
		nv = TriArea2D(p.x, p.y, c.x, c.y, a.x, a.y);
		ood = 1.0f / m.z;
	}
		u = nu * ood;
		v = nv * ood;
		w=1.0f-u-v;
}

bool PHFemVibration::TestPointTriangle(Vec3d fp[3], Vec3d c)
{
	double u, v, w;
	Barycentric(fp, c, u, v, w);
	return v >= 0.0f && w >= 0.0f && (v + w) <= 1.0f;
}

}
