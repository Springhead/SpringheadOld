/*
 *  Copyright (c) 2003-2012, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
/**
 *	@file SprPHFemMeshNew.h
 *	@brief ����
*/
#ifndef SPR_PH_FEMMESH_NEW_IF_H
#define SPR_PH_FEMMESH_NEW_IF_H

#include <Foundation/SprObject.h>

/**	\addtogroup gpPhysics	*/
//@{
namespace Spr{;

struct PHSolidIf;
struct PHFemVibrationIf;
struct PHFemThermoIf;
struct PHFemPorousWOMoveIf;

///	FemMesh�̃X�e�[�g
struct PHFemMeshNewState{};
///	FemMesh�̃f�B�X�N���v�^
struct PHFemMeshNewDesc: public PHFemMeshNewState{
	std::vector<Vec3d> vertices;
	std::vector<int> tets;
	std::vector<int> faces;
	bool spheric;   //For multiple FEM implementation
};
/// PHFemMeshNew�ւ̃C���^�t�F�[�X
struct PHFemMeshNewIf : public SceneObjectIf{
	SPR_IFDEF(PHFemMeshNew);
	void SetPHSolid(PHSolidIf* s);
	PHSolidIf* GetPHSolid();
	PHFemVibrationIf* GetPHFemVibration();
	PHFemThermoIf* GetPHFemThermo();
	PHFemPorousWOMoveIf* GetPHFemPorousWOMove();
	int NVertices();
	int NFaces();
	int NTets();
	void SetVertexUpdateFlags(bool flg);
	void SetVertexUpateFlag(int vid, bool flg);
	double CompTetVolume(int tetID, bool bDeform);
	bool AddVertexDisplacementW(int vtxId, Vec3d disW);
	bool AddVertexDisplacementL(int vtxId, Vec3d disL);
	bool SetVertexPositionW(int vtxId, Vec3d posW);
	bool SetVertexPositionL(int vtxId, Vec3d posL);
	bool SetVertexVelocityL(int vtxId, Vec3d posL);
	Vec3d GetVertexVelocityL(int vtxId);
	Vec3d GetVertexPositionL(int vtxId);
	Vec3d GetVertexDisplacementL(int vtxId);
	Vec3d GetVertexInitalPositionL(int vtxId);
	void SetVelocity(Vec3d v);
	int* GetTetVertexIds(int t);
	int* GetFaceVertexIds(int f);
	Vec3d GetFaceNormal(int f);
	int GetSurfaceVertex(int i);
	int NSurfaceVertices();
	int NSurfaceFace();
	bool CompTetShapeFunctionValue(const int& tetId, const Vec3d& posL, Vec4d& value, const bool& bDeform);
	/// �ʂ���l�ʑ̂�T��
	int FindTetFromFace(int faceId);
};

/// Fem�̃f�X�N���v�^
struct PHFemBaseDesc{};
/// Fem�̋��ʌv�Z����
struct PHFemBaseIf : public SceneObjectIf{
	SPR_IFDEF(PHFemBase);
	PHFemMeshNewIf* GetPHFemMesh();
};

/// �U���v�Z�̃f�X�N���v�^
struct PHFemVibrationDesc : public PHFemBaseDesc{
	enum ANALYSIS_MODE{
		ANALYSIS_DIRECT,
		ANALYSIS_MODAL
	};
	enum INTEGRATION_MODE{
		INT_EXPLICIT_EULER,
		INT_IMPLICIT_EULER,
		INT_SIMPLECTIC,
		INT_NEWMARK_BETA,
	};
	double young;		///< �����O��(Pa, N/m2)
	double poisson;		///< �|�A�\����(*��l�ȗ����̂̏ꍇ�A-1 <= v <= 0.5)
	double density;		///< ���x(kg/m3)
	double alpha;		///< �S��������
	double beta;		///< �\��������
	std::vector<int> fixedVertices;	///< �Œ蒸�_��IDs
	PHFemVibrationDesc();
};

/// �U���v�Z
struct PHFemVibrationIf : public PHFemBaseIf{
	SPR_IFDEF(PHFemVibration);
	void SetTimeStep(double dt);
	double GetTimeStep();
	void SetYoungModulus(double value);
	double GetYoungModulus();
	void SetPoissonsRatio(double value);
	double GetPoissonsRatio();
	void SetDensity(double value);
	double GetDensity();
	void SetAlpha(double value);
	double GetAlpha();
	void SetBeta(double value);
	double GetBeta();
	void SetBoundary(int vtxIds);
	void ClearBoundary();
	std::vector<int>  GetBoundary();
	void SetAnalysisMode(PHFemVibrationDesc::ANALYSIS_MODE mode);
	void SetIntegrationMode(PHFemVibrationDesc::INTEGRATION_MODE mode);
	bool AddBoundaryCondition(int vtxId, Vec3i dof);
	void DeleteBoundaryCondition();
	bool FindNeighborTetrahedron(Vec3d posW, int& tetId, Vec3d& cpW, bool bDeform);
	bool SetDamping(int tetId, Vec3d posW, double damp_ratio);
	// �͂�������
	bool AddForce(int tetId, Vec3d posW, Vec3d fW);
	// �`��֐����g���ĔC�ӂ̓_�̕ψʂ��擾����
	bool GetDisplacement(int tetId, Vec3d posW, Vec3d& disp, bool bDeform);
	// �`��֐����g���ĔC�ӂ̓_�̑��x���擾����
	bool GetVelocity(int tetId, Vec3d posW, Vec3d& vel, bool bDeform);
	// �`��֐����g���ĔC�ӂ̓_�̈ʒu(�ω���)���擾����
	bool GetPosition(int tetId, Vec3d posW, Vec3d& pos, bool bDeform);
#ifndef SWIG
	// ���E������������(���_���jAdd the voudnary conditions (vertex order)
	bool AddBoundaryCondition(std::vector< Vec3i >& bcs); 
	// ���_�ɗ͂�������i���[���h���W�n�j  Applying force to the vertex (world coordinate system)
	bool AddVertexForceW(int vtxId, Vec3d fW);
	// ���_�Q�ɗ͂�������i���[���h���W�n�j Applying force to a group of vertices (world coordinate system)
	bool AddVertexForceW(std::vector< Vec3d >& fWs);
#endif
	void SetbRecomp();	
	void Init();
};

///FemThermo�̃f�X�N���v�^
struct PHFemThermoDesc: public PHFemBaseDesc{
	double rho;						//	���x
	double thConduct;				//�M�`����
	double thConduct_x;				//	x����	�M�`����
	double thConduct_y;				//	y����	�M�`����
	double thConduct_z;				//	z����	�M�`����
	double heatTrans;				//�M�`�B��			//class �ߓ_�ɂ́AheatTransRatio�����݂���
	double specificHeat;			//��M
	double radiantHeat;				//�M�t�˗��i��C�ւ̔M�`�B���j
	//float	distance[10];			//	���S����̋���	��ڂ�0.0
	//float	ondo[10];				//	��L�����̉��x
	double initial_temp;			//	�ώ��ȏ������x�A
	PHFemThermoDesc();
	void Init();
	double weekPow_full;
};

///	���x��FEM�p�̃��b�V��
struct PHFemThermoIf : public PHFemBaseIf{
	SPR_IFDEF(PHFemThermo);
	int GetSurfaceVertex(int id);
	int NSurfaceVertices();
	void SetVertexTc(int id,double temp);
	void SetVertexTc(int id,double temp,double heatTrans);
	Vec3d GetPose(int id);
	Vec3d GetSufVtxPose(unsigned id);
	unsigned long GetStepCount();					///	�J�E���g�P
	unsigned long GetStepCountCyc();				///	�J�E���g�P�����T�ڂ�	�v�Z��:TotalCount = GetStepCount() + GetStepCountCyc() * (1000 * 1000 * 1000) 
	double GetVertexTemp(unsigned id);				// ���b�V���ߓ_�̉��x���擾
	double GetSufVertexTemp(unsigned id);			// ���b�V���\�ʂ̐ߓ_���x���擾
	void SetVertexTemp(unsigned id,double temp);
	void SetVerticesTempAll(double temp);
	void AddvecFAll(unsigned id,double dqdt);		//�Z�b�g���ƁA�l����������ւ��������Ȗ��O�Ŋ댯�B���ۂɂ́Aadd���́AIH���M�x�N�g���݂̂�Set����B�x�N�g����Set����֐�������āA���[�h���Ă������Ǝv���B
	void SetvecFAll(unsigned id,double dqdt);		//FAll�̐����ɉ��Z�����A�댯
	void SetRhoSpheat(double rho,double Cp);		//�f�ތŗL�̕���
	Vec2d GetIHbandDrawVtx();
	void CalcIHdqdt_atleast(double r,double R,double dqdtAll,unsigned num);
	void UpdateIHheatband(double xS,double xE,unsigned heatingMODE);//���쌴�ǉ�
	void UpdateIHheat(unsigned heating);	//	IH���M��Ԃ̍X�V
	void UpdateVecF();						//	����M���̂̔M�������Z�b�g
	void UpdateVecF_frypan();				//	����M���̂̔M�������Z�b�g
	void DecrMoist();						//	
	void DecrMoist_velo(double vel);						//
	void DecrMoist_vel(double dt);						//
	void InitAllVertexTemp();
	void SetInitThermoConductionParam(
		double thConduct,		// thConduct:�M�`����
		double rho,				// roh:���x
		double specificHeat,	// specificHeat:��M J/ (K�Ekg):1960
		double heatTrans		// heatTrans:�M�`�B�� W/(m^2�EK)
		);
	void SetParamAndReCreateMatrix(double thConduct0,double roh0,double specificHeat0);
	double GetArbitraryPointTemp(Vec3d temppos);			//	�����A���g�p
	double GetVtxTempInTets(Vec3d temppos);					//	�g�p���Ă���֐�	
	void InitVecFAlls();
	double Get_thConduct();
	bool SetConcentricHeatMap(std::vector<double> r, std::vector<double> temp, Vec2d origin);
	void SetThermalEmissivityToVerticesAll(double thermalEmissivity,double thermalEmissivity_const);
	// �M���˓���֌W
	void SetOuterTemp(double temp);
	void SetThermalRadiation(double ems,double ems_const);
	void SetGaussCalcParam(unsigned cyc,double epsilon);
	void InitTcAll(double temp);
	void InitToutAll(double temp);
	void SetWeekPow(double weekPow_);
	void SetIHParamWEEK(double inr_, double outR_, double weekPow_);
	void SetHeatTransRatioToAllVertex(double heatTransR_);
	void AfterSetDesc();												//�S�s��Ȃǂ���蒼��
	//void ReProduceMat_Vec_ThermalRadiation();
	void SetStopTimespan(double timespan);
	void UpdateMatk_RadiantHeatToAir();
	void ActivateVtxbeRadiantHeat();			//
	PTM::TMatrixRow<4,4,double> GetKMatInTet(unsigned id);
	void OutputMatKall();
	void IfRadiantHeatTrans();
	float calcGvtx(std::string fwfood, int pv, unsigned texture_mode);
	void SetTimeStep(double dt);
	Vec3d GetVertexNormal(unsigned vtxid);
	void SetVertexHeatTransRatio(unsigned vtxid, double heattransRatio);
	void SetVertexBeRadiantHeat(unsigned vtxid, bool flag);
	double GetVertexArea(unsigned vtxid);
	void SetVertexToofar(unsigned vtxid, bool tooFar);
	bool GetVertexToofar(unsigned vtxid);
	void SetVertexBeCondVtxs(unsigned vtxid, bool becondVtxs);
	void CreateVecFAll();
	void CalcFaceNormalAll();
	void CalcVertexNormalAll();
	void InitFaceNormalAll();
	void InitVertexNormalAll();
	void RevVertexNormalAll();
	void SetWeekPowFULL(double weekPow_full);
	void SetweekPow_FULL(double setweekPow_FULL);
	void Setems(double setems);
	double GetWeekPowFULL();
	Vec3d GetVertexPose(unsigned vtxid);
	void OutTetVolumeAll();
	int GetTetsV(unsigned tetid, unsigned vtxid);
	void VecFNegativeCheck();
	double GetVecFElem(unsigned vtxid);
	int GetTetVNums(unsigned id,unsigned num);
	double GetInitialTemp();
	void UpdateVertexTempAll();
	void SetThermoCameraScale(double minTemp,double maxTemp);
};


struct PHFemPorousWOMoveDesc: public PHFemBaseDesc{
	double wDiffAir;
	double K;		//�Z���W��
	double kc;		//�ъǃ|�e���V�����̌W��
	double kp;		//�ъǈ��͂̒萔
	double alpha;	//�ъǃ|�e���V�����̌W��
	double gamma;	//�ъǈ��͂̌W��
	double rhoWater;	//���̖��x(g/m^3)
	double rhoOil;	//���̖��x(g/m^3)
	double rhowInit;	//�ܐ����̏����l
	double rhooInit;	//�ܖ����̏����l
	double evapoRate;	//�������x�萔
	double denatTemp;	//�ϐ����x	���_�����̉��x�ɒB����ƁA���������ܐ����x�N�g���ɉ�����
	double boundWaterRatio;	//�������̊��� 0.15�`0.25
	double equilWaterCont;	//������1�i�������̕��t�ܐ���
	double limitWaterCont;	//���E������ �P���������ƌ�����1�i��������臒l
	double boundaryThick;	//�����̌���
	double initMassAll;		//�H�ނ̏�������
	double initWaterRatio;	//�H�ނ̎��ʂɑ΂��鐅�����ʂ̏����l
	double initOilRatio;	//�H�ނ̎��ʂɑ΂�������ʂ̏����l
	double shrinkageRatio;	//�^���p�N���ϐ����̎��k��
	Vec3d top;
	Vec3d center;
	Vec3d bottom;
	PHFemPorousWOMoveDesc();
	void Init();
};

struct PHFemPorousWOMoveIf: public PHFemBaseIf{
	SPR_IFDEF(PHFemPorousWOMove);
	void SetTimeStep(double dt);
	double GetTimeStep();
	void UpdateVertexRhoWAll();
	void UpdateVertexRhoOAll();
	void SetVertexMw(unsigned vtxid, double mw);
	void SetVertexMo(unsigned vtxid, double mo);
	double GetVertexMw(unsigned vtxid);
	double GetVertexMo(unsigned vtxid);
	double GetVtxWaterInTets(Vec3d temppos);
	double GetVtxOilInTets(Vec3d temppos);
	double GetVertexRhoW(unsigned vtxid);
	double GetVertexRhoO(unsigned vtxid);
	float calcGvtx(std::string fwfood, int pv, unsigned texture_mode);
	void setGravity(Vec3d g);
	double decideWetValue(unsigned faceid);
	double GetVtxSaturation(unsigned vtxid);
};


//@}

}	//	namespace Spr
#endif