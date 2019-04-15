#ifndef SPR_FWOPTIMIZER_H
#define SPR_FWOPTIMIZER_H

#include <Springhead.h>
#include <Framework/SprFWObject.h>
#include <Foundation/SprObject.h>
#ifdef USE_CLOSED_SRC
#include "../../closed/include/cmaes/cmaes.h"
#endif

#include<chrono> //trajectoryPlanner��
#include<queue>

namespace Spr{;

/*
  �����V�~�����[�V�������g�����œK���v�Z�̊�{�N���X
  FWApp�̂悤�ɂ��̃N���X���p�����ēƎ��̍œK���A�v���P�[�V�������쐬���邱�Ƃ�z�肷��  


*/

// -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  ----- 
// FWStaticTorqueOptimizer�Ɏg���S���N���X

class FWGroundConstraint{
public:
	Vec3d cNormal;
	PHSolidIf* cSolid;
	Posed initialPose;
	double cWeight;
	Vec3d contactForce;
	Vec3d contactPoint;
public:
	FWGroundConstraint();
	FWGroundConstraint(double w, Vec3d n);
	double CalcEvalFunc();
	void Init();
};

class FWUngroundedConstraint{
public:
	Vec3i cAxis;
	Vec3d normal;
	PHSolidIf* cSolid;
	Posed initialPose;
	double cWeight;
public:
	FWUngroundedConstraint();
	FWUngroundedConstraint(double w, Vec3i a, Vec3d n = Vec3d());
	double CalcEvalFunc();
	void Init();
};

struct JointPos {
	Quaterniond ori;
	double angle;
	JointPos();
	JointPos(Quaterniond q);
	JointPos(double a);
};

// -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  ----- 
//Unity�ŕ]���l�̓����\�����邽�߂̓]���p�\����
struct FWObjectiveValues{
	double errorvalue = 0;
	double torquevalue = 0;
	double stabilityvalue = 0;
	double groundvalue = 0;
	double ungroundedvalue = 0;
	double centervalue = 0;
	double initialorivalue = 0;
};

// -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  ----- 
// Framework�̍œK���v�Z�̊��N���X
// �C���^�t�F�[�X
struct FWOptimizerIf : public ObjectIf {
	SPR_IFDEF(FWOptimizer);

	/// Copy PHScene from passed scene
	void CopyScene(PHSceneIf* phSceneInput);

	/// Get FWScene
	PHSceneIf* GetScene();

	/// Initialize Optimizer
	void Init(int dimension);

	/// Start Optimization
	void Start();

	/// Abort Optimization
	void Abort();

	/// Check if Running
	bool IsRunning();

	/// Optimization Thread
	void Optimize();

	/// Optimization Iteration Step
	void Iterate();

	/// Apply Poplulation to Scene
	double ApplyPop(PHSceneIf* phScene, double const *x, int n);

	/// Objective Function to Minimize
	double Objective(double const *x, int n);

	/// Return Dimension of Result
	int NResults();

	/// Return Result
	double GetResult(int i);

	/// Return Results
	double* GetResults();

	/// Return Provisional Results
	double* GetProvisionalResults();

	void SetESParameters(double xs, double st, double tf, double la, double mi);
};

// �f�X�N���v�^
struct FWOptimizerDesc{
	SPR_DESCDEF(FWOptimizer);

	/// Initial search space vector
	double ixstart;
	/// Inital standard deviation of the samples
	double istddev;
	/// Minimal value difference
	double iTolFun;
	/// Population size
	double ilambda;
	/// Max iteration
	double iMaxIter;

	FWOptimizerDesc() {
		ixstart = 0.3;
		istddev = 0.3;
		iTolFun = 0.1;
		ilambda = 30;
		iMaxIter = 500;
	}
};


// -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  ----- 
// �p���œK���v�Z�̃C���^�t�F�[�X
struct FWStaticTorqueOptimizerIf : public FWOptimizerIf {
	SPR_IFDEF(FWStaticTorqueOptimizer);
	
	/// Init
	void Init();

	/// 
	void Iterate();

	/// 
	void ApplyResult(PHSceneIf* phScene);

	/// 
	double ApplyPop(PHSceneIf* phScene, double const *x, int n);

	/// 
	double Objective(double const *x, int n);

	/// 
	void SetScene(PHSceneIf* phSceneInput);

	/// 
	void Optimize();

	/// 
	bool TestForTermination();

	/// 
	void TakeFinalValue();
	
	// Set/Get errorWeight
	void SetErrorWeight(double v);
	double GetErrorWeight();

	// Set/Get stabilityWeight
	void SetStabilityWeight(double v);
	double GetStabilityWeight();

	// Set/Get torqueWeight
	void SetTorqueWeight(double v);
	double GetTorqueWeight();

	// Set/Get  constWeight
	void SetConstWeight(double v);
	double GetConstWeight();

	// Set/Get gravcenterWeight
	void SetGravcenterWeight(double v);
	double GetGravcenterWeight();

	// Set/Get  differentialWeight
	void SetDifferentialWeight(double v);
	double GetDifferentialWeight();

	// GroundConstraint�̒ǉ��A�擾�A�S����
	void AddPositionConst(FWGroundConstraint* f);
	FWGroundConstraint GetGroundConst(int n);
	void ClearGroundConst();

	// UngroundedConstraint�̒ǉ��A�擾�A�S����
	void AddPositionConst(FWUngroundedConstraint* f);
	FWUngroundedConstraint GetUngroundConst(int n);
	void ClearUngroundedConst();

	// �g���N�]�����̊֐߃E�F�C�g�̐ݒ�
	void SetJointWeight(PHJointIf* jo, double w);

	/// CMAES�̃p�����[�^�̐ݒ�
	void SetESParameters(double xs, double st, double tf, double la, double mi);

	/// �]���l���擾
	FWObjectiveValues GetObjectiveValues();
	
	/// �d�S�ʒu�擾
	Vec3f GetCenterOfGravity();

	/// �x�����p�`�Ɏg���Ă���_�̐�
	int NSupportPolygonVertices();

	/// �x�����p�`�Ɏg���Ă���_�̎擾
	Vec3f GetSupportPolygonVerticesN(int n);
};

// �p���œK���v�Z�̃f�X�N���v�^
struct FWStaticTorqueOptimizerDesc : public FWOptimizerDesc{
	SPR_DESCDEF(FWStaticTorqueOptimizer);

	FWStaticTorqueOptimizerDesc() {

	}
};

}

#endif //SPR_FWOPTIMIZER_H

