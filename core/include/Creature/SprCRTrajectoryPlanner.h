#ifndef SPR_CRTRAJECTORYPLANNER_H
#define SPR_CRTRAJECTORYPLANNER_H

#include <Springhead.h>
#include <Foundation/SprObject.h>
#ifdef USE_CLOSED_SRC
#include "../../closed/include/cmaes/cmaes.h"
#endif

namespace Spr { ;

// -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  -----  ----- 
// �g���N�ω��ŏ����v�Z

// ��ԓ��̌o�R�_�w��p�f�[�^
struct ControlPoint { // ���� ViaPoint
	Posed pose;
	SpatialVector vel;
	SpatialVector acc;
	double time;
	bool velControl;
	bool accControl;
	bool timeControl;
	ControlPoint();
	ControlPoint(Posed p, double t);
	ControlPoint(Posed p, SpatialVector v, SpatialVector a, double t);
	//ControlPoint(ControlPoint& c);
};


// �g���N�ω��ŏ����v�Z�̃C���^�t�F�[�X
struct CRTrajectoryPlannerIf : public ObjectIf {
	SPR_IFDEF(CRTrajectoryPlanner);

	void SetDepth(int d);
	int GetDepth();
	void SetMaxIterate(int i);
	int GetMaxIterate();
	void SetMaxLPF(int l);
	int GetMaxLPF();
	void SetLPFRate(double r);
	double GetLPFRate();
	void EnableCorrection(bool e);
	bool IsEnabledCorrection();
	void EnableStaticTarget(bool e);
	bool IsEnabledStaticTarget();
	void EnableSpringCorrection(bool e);
	bool IsEbabledSpringCorrection();
	void EnableJointMJTInitial(bool e);
	bool IsEbabledJointMJTInitial();

	void EnableViaCorrection(bool e);
	bool IsEnabledViaCorrection();
	void SetMaxIterateViaAdjust(int m);
	int GetMaxIterateViaAdjust();
	void SetViaAdjustRate(double r);
	double GetViaAdjustRate();

	void SetSpringRate(double s);
	double GetSpringRate();
	void SetDamperRate(double d);
	double GetDamperRate();
	void EnableMultiplePD(bool e);
	bool IsEnabledMultiplePD();

	void EnableChangeBias(bool e);
	bool IsEnabledChangeBias();
	void EnableChangePullback(bool e);
	bool IsEnabledChangePullback();

	//������
	void Init();
	//�G���h�G�t�F�N�^�ݒ�
	void SetControlTarget(PHIKEndEffectorIf* e);
	//�V�[���ݒ�
	void SetScene(PHSceneIf* s);
	void AddViaPoint(ControlPoint c);
	//�֐ߊp�x�����O���v�Z
	void CalcTrajectory();
	void CalcOneStep();
	//N��ڂ̌J��Ԃ�����Čv�Z
	void RecalcFromIterationN(int n);
	//�������ꂽ�O�������ۓK�p
	void JointTrajStep(bool step);
	//
	bool Moving();
	//spring, damper set
	void SetSpringDamper(double s = 1e5, double d = 1e5, bool mul = true);
	//replay
	void Replay(int ite, bool noncorrected = false);
	//return best
	int GetBest();
	//
	void ReloadCorrected(int k, bool nc = false);

	Posed GetTrajctoryData(int k, int n);
	Posed GetNotCorrectedTrajctoryData(int k, int n);
	SpatialVector GetVeclocityData(int k, int n);
	SpatialVector GetNotCorrectedVelocityData(int k, int n);
};

// �g���N�ω��ŏ����v�Z�̃f�X�N���v�^
struct CRTrajectoryPlannerDesc {
	SPR_DESCDEF(CRTrajectoryPlanner);
	// Desc�ɂ��낢��ڂ�����

	double depth;
	int maxIterate;
	int maxLPF;
	double LPFRate;
	bool bCorrection;
	bool bStaticTarget;
	bool bUseSpringCorrection;
	bool bUseJointMJTInitial;

	bool bViaCorrection;
	int maxIterateViaAdjust;
	double viaAdjustRate;

	double springRate;
	double damperRate;
	bool bMultiplePD;

	bool bChangeBias;
	bool bChangePullback;

	std::string outputPath;

	CRTrajectoryPlannerDesc() {
		depth = 3;
		maxIterate = 100;
		maxLPF = 10;
		LPFRate = 1.0;
		bCorrection = true;
		bStaticTarget = false;
		bUseSpringCorrection = false;
		bUseJointMJTInitial = false;

		bViaCorrection = false;
		maxIterateViaAdjust = 0;
		viaAdjustRate = 0.0;

		springRate = 1e5;
		damperRate = 1e5;
		bMultiplePD = true;

		bChangeBias = true;
		bChangePullback = false;

		outputPath = "";
	}
};

}

#endif