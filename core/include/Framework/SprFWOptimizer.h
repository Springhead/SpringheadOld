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
	PHSolidIf* cSolid;
	Posed initialPose;
	double cWeight;
public:
	FWUngroundedConstraint();
	FWUngroundedConstraint(double w, Vec3i a);
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

struct FWOptimizerDesc{
	SPR_DESCDEF(FWOptimizer);

	FWOptimizerDesc() {

	}
};

struct FWStaticTorqueOptimizerIf : public FWOptimizerIf {
	SPR_IFDEF(FWStaticTorqueOptimizer);
	
	void Init();

	void Iterate();

	void ApplyResult(PHSceneIf* phScene);

	double ApplyPop(PHSceneIf* phScene, double const *x, int n);

	double Objective(double const *x, int n);

	void SetScene(PHSceneIf* phSceneInput);

	void Optimize();

	bool TestForTermination();

	void TakeFinalValue();
	
	double CalcErrorCriterion();
	double CalcGroundedCriterion();
	double CalcPositionCriterion();
	double CalcCOGCriterion();
	double CalcDifferenceCriterion();
	double CalcTorqueCriterion();
	double CalcStabilityCriterion();

	double CenterOfGravity(PHIKActuatorIf* root, Vec3d& point);
	double CalcTorqueInChildren(PHIKActuatorIf* root, Vec3d& point, Vec3d& forceInChildren);
	
	void SetErrorWeight(double v);
	double GetErrorWeight();

	void SetStabilityWeight(double v);
	double GetStabilityWeight();

	void SetTorqueWeight(double v);
	double GetTorqueWeight();

	void SetResistWeight(double v);
	double GetResistWeight();

	void SetConstWeight(double v);
	double GetConstWeight();

	void SetGravcenterWeight(double v);
	double GetGravcenterWeight();

	void SetDifferentialWeight(double v);
	double GetDifferentialWeight();

	//�\���̂̔z����O��������Ȃ��̂łP�v�f����push
	void AddPositionConst(FWGroundConstraint* f);
	FWGroundConstraint GetGroundConst(int n);
	void ClearGroundConst();
	void AddPositionConst(FWUngroundedConstraint* f);
	FWUngroundedConstraint GetUngroundConst(int n);
	void ClearUngroundedConst();

	void SetESParameters(double xs, double st, double tf, double la, double mi);

	FWObjectiveValues GetObjectiveValues();
	
	Vec3f GetCenterOfGravity();

	int NSupportPolygonVertices();

	Vec3f GetSupportPolygonVerticesN(int n);
};

struct FWStaticTorqueOptimizerDesc {
	SPR_DESCDEF(FWStaticTorqueOptimizer);

	FWStaticTorqueOptimizerDesc() {

	}
};

//�����_�w��p�ɕK�v�����ȃf�[�^
struct ControlPoint{
	Posed pose;
	Vec6d vel;
	Vec6d acc;
	int step;
	double time;
	bool velControl;
	bool accControl;
	bool timeControl;
	ControlPoint();
	ControlPoint(Posed p, int s, double t);
	ControlPoint(Posed p, Vec6d v, int s, double t);
	//ControlPoint(ControlPoint& c);
};

struct FWTrajectoryPlannerIf : public ObjectIf{
	SPR_IFDEF(FWTrajectoryPlanner);

	//�������n
	void Reset(int d, int i, int iv, int n, double mg, int c, bool wf, bool snc = false, double r = 1.0, double vRate = 0.65);
	void Init();
	void Init(int d, int i, int iv, int n, double mg, int c, bool wf, bool snc, double r = 1.0, double vRate = 0.65);
	//joint�̐[���̃`�F�b�N�Ɠ�������
	//void CheckAndSetJoints();
	//�G���h�G�t�F�N�^�ݒ�
	void SetControlTarget(PHIKEndEffectorIf* e);
	//�V�[���ݒ�
	void SetScene(PHSceneIf* s);
	//�w��_�ʉߋO���v�Z
	void CalcTrajectoryWithViaPoint(ControlPoint tpoint, ControlPoint vpoint, int LPFmode, int smoothCount, std::string output, bool bChange, bool pChange, bool staticTarget, bool jmjt);
	//�A���O���v�Z
	void CalcContinuousTrajectory(int LPFmode, int smoothCount, std::string filename, bool bChange, bool pChange, bool staticTarget, bool jmjt);
	void AddControlPoint(ControlPoint c); //�����ړ�
										  //�֐ߊp�x�����O���v�Z
	void JointCalcTrajectory(Posed tPose, double mt, int LPFmode, int smoothCount, std::string output, bool bChange = false, bool pChange = false, bool staticTarget = false, bool jmjt = false);
	void CalcTrajectory(ControlPoint tpoint, int LPFmode, int smoothCount, std::string output, bool bChange, bool pChange, bool staticTarget, bool jmjt);
	//N��ڂ̌J��Ԃ�����Čv�Z
	void RecalcFromIterationN(int n);
	//�������ꂽ�O�������ۓK�p
	void JointTrajStep(bool step);
	//�␳
	//void JointTrajCorrection(int k);
	//
	bool Moving();
	//spring, damper set
	void SetPD(double s = 1e10, double d = 1e10, bool mul = true);
	//replay
	void Replay(int ite, bool noncorrected = false);
	//return totalChange
	double GetTotalChange();
	//return best
	int GetBest();
};

struct FWTrajectoryPlannerDesc {
	SPR_DESCDEF(FWTrajectoryPlanner);

	FWTrajectoryPlannerDesc() {

	}
};

}

#endif //SPR_FWOPTIMIZER_H

