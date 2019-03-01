/*
*  Copyright (c) 2003-2010, Shoichi Hasegawa and Springhead development team
*  All rights reserved.
*  This software is free software. You can freely use, distribute and modify this
*  software. Please deal with this software under one of the following licenses:
*  This license itself, Boost Software License, The MIT License, The BSD License.
*/
#ifndef CRMINIMUMTORQUECHANGE_H
#define CRMINIMUMTORQUECHANGE_H

#include <Foundation/SprObject.h>
#include <Creature/SprCRMinimumTorqueChangePlanner.h>
#include <Creature/SprCRTimeSeries.h>
#include <Creature/SprCRCreature.h>
#include <Foundation/Object.h>
#include <Creature/CreatureDecl.hpp>

namespace Spr {;

/**  CRMinimumTorqueChangePlanner
     �g���N�ω��ŏ��O����p���Ċ֐ߌn���R���g���[�����邽�߂̌v�Z�N���X
	 ���t�ɘa�@�ɂ�锽���v�Z�ɂ��ߎ��ŋ��߂�
	 �Q�l�_��
	  Title : Trajectory Formation of Arm Movement by a Neural Network with Forward and Inverse Dynamics Models
	  Authors : Yasuhiro WADA and Mitsuo KAWATO
	  Outline : They got approximate solution of Minimum Torque Change Model by using iterative method named FIRM(Forward Inverse Relaxation Model).

	 ���݂̖��F
	  �������߂ɓ�̒��˂�������
	  - �Ǐ]����PD�Q�C����傫�����Ă��邹�����Ƃ��v�������A1�{�ɂ��Ă���������
	  - �����O���̊J�n�p���Ɍ��݂̈ʒu���w�肵�Ă����̂������APD����Ȃ̂ō��̎p����ڕW�ɐݒ肵�Ă��܂��Ƃ��ꂪ������
	  �J��Ԃ��񐔂������K�v�Ȃ��ߌv�Z�Ɏ��Ԃ�������
	  - 1�X�e�b�v���̎����Ԍo�߂Ō���̂��̂��Ƃ肠�����o�́H
	  - �V�[�������G������Ƃ��ꂾ���V�~�����[�V�����Ɏ��Ԃ�������̂���_(�V�[���𕪂���H)
	  �������肵�Ă������A�g�p���Ȃ��֐߂̍��̂�stationary�ɂ��邾������IK�̌v�Z������
	  - �܂��IKActuator���̂��̂𖳌�������K�v��������
	  TimeSeries�\���̂��x�[�X�ɂ��������ɕύX��
*/
class CRTrajectoryPlanner : public Object {
public:
	//Joint�n�̊Ǘ��N���X(PHJoint�Ƃ͕�)
	class Joint {
	public:
		virtual void Initialize(int iterate, double movetime, int nVia, double rate = 1.0, bool vCorr = true) = 0;
		virtual void MakeJointMinjerk(int cnt) = 0;
		virtual void CloseFile() = 0;
		virtual void SaveTorque(int n) = 0;
		virtual void SaveTarget() = 0;
		virtual void SetTarget(int k, int n) = 0;
		virtual void SetTargetVelocity(int k, int n) = 0;
		virtual void SetTargetInitial() = 0;
		virtual void SetOffsetFromLPF(int n) = 0;
		virtual void ResetOffset(double o) = 0;
		virtual void SavePosition(int k, int n) = 0;
		virtual void SaveVelocity(int k, int n) = 0;
		virtual void SaveViaPoint(int v, int t) = 0;
		virtual void SavePositionFromLPF(int k, int n) = 0;
		virtual void SaveVelocityFromLPF(int k, int n) = 0;
		virtual void TrajectoryCorrection(int k, bool s) = 0;
		virtual void ApplyLPF(int count) = 0;
		virtual void Soften() = 0;
		virtual void Harden() = 0;
		virtual void ResetPD() = 0;
		virtual double CalcTotalTorqueChange() = 0;
		virtual double CalcTotalTorqueChangeLPF() = 0;
		virtual double CalcTorqueChangeInSection(int n) = 0;
		virtual double GetBestTorqueChangeInSection(int n) = 0;
		virtual void SetBestTorqueChange() = 0;
		virtual void ShowInfo() = 0;
		virtual void SetTargetCurrent() = 0;
		virtual void SetTargetFromLPF(int k, int n) = 0;
		virtual void OutputTorque() = 0;
		virtual void SetPD(double s, double d, bool mul) = 0;
		virtual void UpdateIKParam(double b, double p) = 0;
		virtual double GetMaxForce() = 0;
		virtual void SetWeight(double w = 1.0) = 0;
	};

	struct LPF {
		// N-Simple Moving Average LPF
		template<class T>
		static PTM::VMatrixRow<T> NSMA(PTM::VMatrixRow<T> input, int n, double mag, PTM::VVector<T> s);

		template<class T>
		static PTM::VVector<T> centerNSMAv(PTM::VVector<T> input, int n, double mag, T initial);

		template<class T>
		static PTM::VMatrixRow<T> weighted(PTM::VMatrixRow<T> input, PTM::VVector<T> s, PTM::VVector<double> w);

		template <class T>
		static PTM::VVector<T> weightedv(PTM::VVector<T> input, T initial, double w, double r = 1.0);
	};

private:
	// ���U�����Ƃ��Ɏ~�߂�
	bool isDiverged;

	// ----- �֐߂̏�Ԃ�ێ�����JointsTimeSeries -----
	std::vector<CRJointsTimeSeries> trajectorySatisfyingCondition;
	std::vector<CRJointsTimeSeries> trajectorySmoothed;

	// ----- �g���N���琶�������O���f�[�^�Q -----
	std::vector<CRSolidsTimeSeries> solidsTrajectorySatisfyingCondition;
	std::vector<CRSolidsTimeSeries> solidsTrajectorySmoothed;

	// ----- Scene�ƕۑ��p��States -----
	PHSceneIf* scene;
	UTRef<ObjectStatesIf> states;
	UTRef<ObjectStatesIf> initialStates;
	UTRefArray<ObjectStatesIf> tmpStates;
	UTRefArray<ObjectStatesIf> corStates;
	UTRefArray<ObjectStatesIf> beforeCorStates;


	// �v�Z�t�F�C�Y
	enum Phase {
		INIT,
		FORWARD,
		INVERSE,
		POST_PROCESS,
	};
	Phase phase;
	int currentIterate;
	bool bFinished;

	// �t�F�C�Y�V�t�g
	void PhaseShift() {
		switch (phase) {
		case Phase::FORWARD:
		case Phase::INIT:
			phase = Phase::INVERSE;
			break;
		case Phase::INVERSE:
			phase = Phase::FORWARD;
			break;
		}
	}

public:
	SPR_OBJECTDEF(CRTrajectoryPlanner);
	SPR_DECLMEMBEROF_CRTrajectoryPlannerDesc;
	//�R���X�g���N�^
	CRTrajectoryPlanner(const CRTrajectoryPlannerDesc& desc = CRTrajectoryPlannerDesc()) {
		SetDesc(&desc);
	}

	// -----�C���^�t�F�[�X�̎���-----

	// ----- �f�B�X�N���v�^�R���̊e��p�����[�^��Setter/Getter -----
	void SetDepth(int d) { depth = d; }
	int GetDepth() { return depth; }
	void SetMaxIterate(int i) { maxIterate = i; }
	int GetMaxIterate() { return maxIterate; }
	void SetMaxLPF(int l) { maxLPF = l; }
	int GetMaxLPF() { return maxLPF; }
	void SetLPFRate(double r) { LPFRate = r; }
	double GetLPFRate() { return LPFRate; }
	void EnableCorrection(bool e) { bCorrection = e; }
	bool IsEnabledCorrection() { return bCorrection; }
	void EnableStaticTarget(bool e) { bStaticTarget = e; }
	bool IsEnabledStaticTarget() { return bStaticTarget; }
	void EnableSpringCorrection(bool e) { bUseSpringCorrection = e; }
	bool IsEbabledSpringCorrection() { return bUseSpringCorrection; }
	void EnableJointMJTInitial(bool e) { bUseJointMJTInitial = e; }
	bool IsEbabledJointMJTInitial() { return bUseJointMJTInitial; }

	void EnableViaCorrection(bool e) { bViaCorrection = e; }
	bool IsEnabledViaCorrection() { return bViaCorrection; }
	void SetMaxIterateViaAdjust(int m) { maxIterateViaAdjust = m; }
	int GetMaxIterateViaAdjust() { return maxIterateViaAdjust; }
	void SetViaAdjustRate(double r) { viaAdjustRate = r; }
	double GetViaAdjustRate() { return viaAdjustRate; }

	void SetSpringRate(double s) { springRate = s; }
	double GetSpringRate() { return springRate; }
	void SetDamperRate(double d) { damperRate = d; }
	double GetDamperRate() { return damperRate; }
	void EnableMultiplePD(bool e) { bMultiplePD = e; }
	bool IsEnabledMultiplePD() { return bMultiplePD; }

	void EnableChangeBias(bool e) { bChangeBias = e; }
	bool IsEnabledChangeBias() { return bChangeBias; }
	void EnableChangePullback(bool e) { bChangePullback = e; }
	bool IsEnabledChangePullback() { return bChangePullback; }

	// ----- ����ȊO��Setter -----

	// ����������
	void Init();

	// �v�Z���s
	void CalcTrajectory() {};
	// 
	void CalcOneStep() {};

	// N��ڂ̌J��Ԃ�����Čv�Z
	void RecalcFromIterationN(int n) {};

	// �������ꂽ�O�������ۓK�p
	void JointTrajStep(bool step) {};

	// spring, damper set
	void SetSpringDamper(double s = 1e10, double d = 1e10, bool mul = true) {
		this->springRate = s;
		this->damperRate = d;
		this->bMultiplePD = mul;
	}
	// replay
	void Replay(int ite, bool noncorrected = false) {};

	void ReloadCorrected(int k, bool nc = false) {};

	// getters for trajectory
	Posed GetTrajctoryData(int k, int n) { return Posed(); }
	Posed GetNotCorrectedTrajctoryData(int k, int n) { return Posed(); }
	SpatialVector GetVeclocityData(int k, int n) { return SpatialVector(); }
	SpatialVector GetNotCorrectedVelocityData(int k, int n) { return SpatialVector(); }
};

}

#endif