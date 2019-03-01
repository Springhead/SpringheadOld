#ifndef FWTRAJECTORYPLANNER_H
#define FWTRAJECTORYPLANNER_H

#include <Framework/SprFWOptimizer.h>
#include <Foundation/Object.h>
#include <Framework/FrameworkDecl.hpp>
#include <Framework/FWOptimizer.h>
#include <Creature/CRMinimumJerkTrajectory.h>

namespace Spr {
	; 

	/**  FWTrajectoryPlanner
	     �g���N�ω��ŏ��O����p���Ċ֐ߌn���R���g���[�����邽�߂̌v�Z�N���X
		 �Q�l�_��
		  Title : Trajectory Formation of Arm Movement by a Neural Network with Forward and Inverse Dynamics Models
		  Authors : Yasuhiro WADA and Mitsuo KAWATO
		  Outline : They got approximate solution of Minimum Torque Change Model by using iterative method named FIRM(Forward Inverse Relaxation Model).

		  �o�O�ɂ���
		  �����ς̃o�O
		  �E���������߂ɃW�����v����������
		   -> �������̎��O���������̊J�n���ʒu�Ɍ��݂̎��^�[�Q�b�g���w�肷�邱�Ƃŉ���
		  �c���Ă���o�O
		�@�E���[�p�X��������񐔂�0�ɂ��āA�C�����؂��Ă���̂ɋO�����ς���Ă���
		   -> IK��؂�Y��Ă�����APD�Q�C�����K�؂���Ȃ�������A�Ƃ����������Ɛ���
		      ����PD�Q�C���ɂ��Ă͉����ƃV�r�A
		  
		  ���
		  �E�t�H���[�h�͒������Ǝv�����A�C���o�[�X�̏C�������܂������Ȃ�
		  �E

	*/
	
	class FWTrajectoryPlanner : public Object{
	public:
		//Joint�n�̊Ǘ��N���X(PHJoint�Ƃ͕�)
		class Joint {
		public:
			//
			virtual void Initialize(int iterate, double movetime, int nVia, double rate = 1.0, bool vCorr = true) = 0;
			//
			virtual void MakeJointMinjerk(int cnt) = 0;
			//
			virtual void CloseFile() = 0;
			//
			virtual void SaveTorque(int n) = 0;
			//
			virtual void SaveTarget() = 0;
			virtual void SetTarget(int k, int n) = 0;
			//
			virtual void SetTargetVelocity(int k, int n) = 0;
			//
			virtual void SetTargetInitial() = 0;
			//
			virtual void SetOffsetFromLPF(int n) = 0;
			//
			virtual void ResetOffset(double o) = 0;
			//
			virtual void SavePosition(int k, int n) = 0;
			virtual void SaveVelocity(int k, int n) = 0;
			//
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
			virtual void SetPullbackTarget(int k, int n) = 0;
			virtual void SetPullbackTargetFromInitial() = 0;
		};
		class HingeJoint : public Joint {
		public:
			PHIKHingeActuatorIf* hinge;          //�A�N�`���G�[�^
			PHSceneIf* scene;

			PTM::VVector<double> torque;         //Inverse���ɋL�^�����g���N
			PTM::VVector<double> torqueLPF;      //LPF��g���N
			PTM::VMatrixRow<double> angle;       //Inverse�œ������p�p�x(�C������)
			PTM::VMatrixRow<double> angleLPF;    //Forward���ɋL�^����p�x
			PTM::VMatrixRow<double> angleVels;
			PTM::VMatrixRow<double> angleVelsLPF;

			double targetAngle;                  //�^�[�Q�b�g�ƂȂ�֐ߊp  finalAngle
			double targetVel;                    //�^�[�Q�b�g�ƂȂ�p���x(�ʏ��0)  finalAngularVelocity
			PTM::VVector<double> viaAngles;      //�o�R�_�ɂ�����p�x
			PTM::VVector<double> viaVels;        //�o�R�_�ɂ�����p���x
			PTM::VVector<double> viatimes;       //�o�R�_�̒ʉߎ���

			double initialTorque;                //�J�n���̔����g���N  torque[0]
			double initialAngle;                 //�J�n���̊֐ߊp�x  angle[i][0]
			double initialVel;                   //�J�n���̊p���x   angleVel[i][0]
			double initialPullbackTarget;   // �J�n����IK�v���o�b�N�^�[�Q�b�g
			
			double weight = 1.0;                 //�]���E�F�C�g
			double rateLPF = 1.0;                //LPF�̃��[�g
			double originalSpring;               //���̂΂˒萔
			double originalDamper;               //���̃_���p�萔
			double hardenSpring = 1e30;  //
			double hardenDamper = 1e8;
			bool mul = true;

			int iterate;                         //�J��Ԃ���  *
			double mtime;                        //���v����(s)   *
			int movetime;                        //���v�X�e�b�v  *
			bool viaCorrect;                     // *
			PTM::VMatrixRow<double> CorrTraj;    // �g���ĂȂ�����

			PTM::VVector<double> torqueChange;
			PTM::VVector<double> torqueChangeLPF;
			PTM::VVector<double> tChanges;
			
		private:
			std::ofstream* torGraph;
			std::ofstream* torChangeGraph;
			bool outputEnable = false;
			
		public:
			HingeJoint(PHIKHingeActuatorIf* hinge, std::string path, bool oe);
			~HingeJoint();
			void Initialize(int iterate, double mtime, int nVia, double rate = 1.0, bool vCorr = true);
			void MakeJointMinjerk(int cnt);
			void CloseFile();
			void SaveTorque(int n);
			void SaveTarget();
			void SetTarget(int k, int n);
			void SetTargetVelocity(int k, int n);
			void SetTargetInitial();
			void SetOffsetFromLPF(int n);
			void ResetOffset(double o);
			void SavePosition(int k, int n);
			void SaveVelocity(int k, int n);
			void SavePositionFromLPF(int k, int n);
			void SaveVelocityFromLPF(int k, int n);
			void SaveViaPoint(int v, int t);
			void TrajectoryCorrection(int k, bool s);
			void ApplyLPF(int count);
			void Soften();
			void Harden();
			void ResetPD();
			double CalcTotalTorqueChange();
			double CalcTotalTorqueChangeLPF();
			double CalcTorqueChangeInSection(int n);
			double GetBestTorqueChangeInSection(int n);
			void SetBestTorqueChange();
			void ShowInfo();
			void SetTargetCurrent();
			void SetPD(double s, double d, bool mul);
			void SetTargetFromLPF(int k, int n);
			void UpdateIKParam(double b, double p);
			void OutputTorque();
			double GetMaxForce() { return hinge->GetJoint()->GetMaxForce(); }
			void SetWeight(double w) { weight = w; }
			void SetPullbackTarget(int k, int n);
			void SetPullbackTargetFromInitial();
		};
		class BallJoint : public Joint {
		public:
			PHIKBallActuatorIf* ball;            // �A�N�`���G�[�^
			PHSceneIf* scene;

			/// 
			PTM::VVector<Vec3d> torque;          // Inverse���ɋL�^�����g���N
			PTM::VVector<Vec3d> torqueLPF;       // LPF��g���N
			PTM::VMatrixRow<Quaterniond> ori;    // Inverse�œ������p�p�x(�C������)
			PTM::VMatrixRow<Quaterniond> oriLPF; // Forward���ɋL�^����p�x
			PTM::VMatrixRow<Vec3d> oriVels;
			PTM::VMatrixRow<Vec3d> oriVelsLPF;

			Quaterniond targetOri;               // �^�[�Q�b�g�ƂȂ�֐ߊp
			Vec3d targetVel;                     // �^�[�Q�b�g�ƂȂ�p���x(�ʏ��0)
			PTM::VVector<Quaterniond> viaOris;   // �o�R�_�ɂ�����p�x
			PTM::VVector<Vec3d> viaVels;         // �o�R�_�ɂ�����p���x
			PTM::VVector<double> viatimes;          // �o�R�_�̒ʉߎ���

			Vec3d initialTorque;                 // �J�n���̔����g���N
			Quaterniond initialOri;              // �J�n���̊֐ߊp�x
			Vec3d initialVel;                    // �J�n���̊p���x
			Quaterniond initialPullbackTarget;   // �J�n����IK�v���o�b�N�^�[�Q�b�g

			int iterate;                         // �J��Ԃ���
			double mtime;                        // ���v����(s)
			int movetime;                        // ���v�X�e�b�v
			double weight = 1.0;                 // �]���E�F�C�g
			double rateLPF = 1.0;                // LPF�̃��[�g
			double originalSpring;               // ���̂΂˒萔
			double originalDamper;               // ���̃_���p�萔
			double hardenSpring = 1e30;
			double hardenDamper = 1e8;
			bool mul = true;
			PTM::VVector<double> tChanges;
			bool viaCorrect;
			PTM::VMatrixRow<Quaterniond> CorrTraj; // �o�R�_�C���Ɏg������(���̓R�����g�A�E�g����Ă���)

			PTM::VVector<double> torqueChange;
			PTM::VVector<double> torqueChangeLPF;

		private:
			std::ofstream* torGraph;
			std::ofstream* torChangeGraph;
			bool outputEnable = false;

		public:
			BallJoint(PHIKBallActuatorIf* ball, std::string path, bool oe);
			~BallJoint();
			void Initialize(int iterate, double mtime, int nVia, double rate = 1.0, bool vCorr = true);
			void MakeJointMinjerk(int cnt);
			void CloseFile();
			void SaveTorque(int n);
			void SaveTarget();
			void SetTarget(int k, int n);
			void SetTargetVelocity(int k, int n);
			void SetTargetInitial();
			void SetOffsetFromLPF(int n);
			void ResetOffset(double o);
			void SavePosition(int k, int n);
			void SaveVelocity(int k, int n);
			void SaveViaPoint(int v, int t);
			void SavePositionFromLPF(int k, int n);
			void SaveVelocityFromLPF(int k, int n);
			void TrajectoryCorrection(int k, bool s);
			void SetBestTorqueChange();
			void ApplyLPF(int count);
			void Soften();
			void Harden();
			void ResetPD();
			double CalcTotalTorqueChange();
			double CalcTotalTorqueChangeLPF();
			double CalcTorqueChangeInSection(int n);
			double GetBestTorqueChangeInSection(int n);
			void ShowInfo();
			void SetTargetCurrent();
			void SetPD(double s, double d, bool mul);
			void SetTargetFromLPF(int k, int n);
			void UpdateIKParam(double b, double p);
			void OutputTorque();
			double GetMaxForce() { return ball->GetJoint()->GetMaxForce(); }
			void SetWeight(double w) { weight = w; }
			void SetPullbackTarget(int k, int n);
			void SetPullbackTargetFromInitial();
		};
		class Joints {
			friend class Joint;
		public:
			std::vector<Joint*> joints;
			FWTrajectoryPlannerIf* fwPlanner;
		public:
			Joints();
			~Joints();
			void RemoveAll();
			void Add(PHIKActuatorIf* j, std::string path, bool oe = true);
			void Initialize(int iterate, double movetime, int nVia, double rate = 1.0, bool vCorr = true);
			void MakeJointMinjerk(int cnt);
			void CloseFile();
			void SetTarget(int k, int n);
			void SetTargetVelocity(int k, int n);
			void SetTargetInitial();
			void SaveTorque(int n);
			void SaveTarget();
			void SetOffsetFromLPF(int n);
			void ResetOffset(double o);
			void SavePosition(int k, int n);
			void SaveVelocity(int k, int n);
			void SaveViaPoint(int v, int t);
			void SavePositionFromLPF(int k, int n);
			void SaveVelocityFromLPF(int k, int n);
			void TrajectoryCorrection(int k, bool s);
			void SetBestTorqueChange();
			double GetBestTorqueChangeInSection(int n);
			void ApplyLPF(int count);
			void Soften();
			void Harden();
			void ResetPD();
			double CalcTotalTorqueChange();
			double CalcTotalTorqueChange(std::ofstream& o);
			double CalcTotalTorqueChangeLPF();
			double CalcTorqueChangeInSection(int n);
			void ShowInfo();
			void SetTargetCurrent();
			void SetWeight();
			void SetPD(double s, double d, bool mul);
			void SetTargetFromLPF(int k, int n);
			void UpdateIKParam(double b, double p);
			void OutputTorque();
			void SetPullbackTarget(int k, int n);
			void SetPullbackTargetFromInitial();
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
		// ----- �v�Z�ɂ��������� -----
		// ����ΏۂƂȂ�G���h�G�t�F�N�^
		PHIKEndEffectorIf* ikEndEffector;
		// �J�n�p��
		//ControlPoint startPoint = ControlPoint();
		Posed initialTargetPose;
		SpatialVector initialTargetVel;
		SpatialVector initialTargetAcc;
		// �ڕW�p��
		PHSolidIf* targetSolid;
		PHSpringIf* targetSpring;
		// �r���ʉߓ_
		std::vector<ControlPoint> viaPoints;
		std::vector<PHSolidIf*> viaSolids;
		std::vector<PHSpringIf*> viaSprings;
		// �ړ����Ԃ�b�ŕ\��������
		double mtime;
		// �ړ����Ԃ�Step���ɂ�������(mtime�v��Ȃ��H)
		int movtime;
		// �l������Actuator
		Joints joints;
		// ���U�����Ƃ��Ɏ~�߂�
		bool isDiverged;

		// ----- Scene�ƕۑ��p��States -----
		PHSceneIf* scene;
		UTRef<ObjectStatesIf> states;
		UTRef<ObjectStatesIf> initialStates;
		UTRefArray<ObjectStatesIf> tmpStates;
		UTRefArray<ObjectStatesIf> corStates;
		UTRefArray<ObjectStatesIf> beforeCorStates;

		// ----- �g���N���琶�������O���f�[�^�Q -----
		PTM::VMatrixRow<Posed> trajData;
		PTM::VMatrixRow<Posed> trajDataNotCorrected;
		PTM::VMatrixRow<SpatialVector> trajVel;
		PTM::VMatrixRow<SpatialVector> trajVelNotCorrected;

		// ----- �t���O�n -----
		// �Đ����ɂ܂��ړ������ǂ���
		bool isMoving;
		// �v�Z�ς݂��̃t���O
		bool isCalculated;

		// ----- ���v���C�֌W -----
		// (replay����)�Đ��O��index�A�ʏ�͍Ō�̂���
		int ite;
		// ���v���C���̓K�p�X�e�b�v
		int repCount;
		// �ɏ��l���Ƃ����O���̔ԍ�
		int best;

		// ----- Unity����ǂ��܂œK�p���邩�̃t���O -----
		// �C���O�O�����Đ����邩�̃t���O
		bool noncorrectedReplay;

		// �g���N�ω�
		double bestTorque;
		std::vector<double> torqueChangeRecord;

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
		SPR_OBJECTDEF(FWTrajectoryPlanner);
		SPR_DECLMEMBEROF_FWTrajectoryPlannerDesc;
		//�R���X�g���N�^
		FWTrajectoryPlanner(const FWTrajectoryPlannerDesc& desc = FWTrajectoryPlannerDesc()) {
			SetDesc(&desc);
		}

		// ----- �v�Z�p�֐� -----

		// �K�p�֐߂��m�F���A�v�Z�p�\���̃x�N�g���ɕۑ�
		void CheckAndSetJoints();
		// �f�o�b�O�p���\��
		void DisplayDebugInfo();
		// �O���f�[�^�̏o��
		void OutputTrajectory(std::string filename);
		void OutputNotCorrectedTrajectory(std::string filename);
		void OutputVelocity(std::string filename);

		// Forward Inverse Relaxation Model
		void ForwardInverseRelaxation();
		// �X�^�b�N�����o�R�_����MJT���쐬
		void MakeMinJerk();
		
		// Forward model(torque -> pos)
		void CompForwardDynamics(int k);
		// Inverse model(pos -> torque)
		void CompInverseDynamics(int k);
		//
		void TrajectoryCorrection(int k);
		//
		void PostProcessing();
		// viatime adjustment
		bool AdjustViatime();
		// viatime initialize
		void InitializeViatime();
		// Prepare solids and springs for correction
		void PrepareSprings();

		// 
		//
		int TimeToStep(double t) {
			t *= scene->GetTimeStepInv();
			return std::round(t);
		}
		void LoadInitialState() {
			states->LoadState(scene);
			//scene->GetIKEngine()->ApplyExactState();
		}
		SpatialVector GetEndEffectorVelocity() {
			Vec3d vel = ikEndEffector->GetSolid()->GetVelocity();
			Vec3d angularVel = ikEndEffector->GetSolid()->GetAngularVelocity();
			Vec3d localVel = vel + PTM::cross(angularVel, ikEndEffector->GetSolid()->GetPose().Ori() * ikEndEffector->GetTargetLocalPosition());
			Vec3d localAngularVel = angularVel;
			return SpatialVector(localVel, localAngularVel);
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
		
		// �G���h�G�t�F�N�^�ݒ�
		void SetControlTarget(PHIKEndEffectorIf* e) { this->ikEndEffector = e; }
		// �V�[���ݒ�
		void SetScene(PHSceneIf* s) { this->scene = s; }

		// ����������
		void Init();

		// �o�R�_�̒ǉ�
		void AddViaPoint(ControlPoint c) { viaPoints.push_back(c); }

		// �v�Z���s
		void CalcTrajectory();
		// 
		void CalcOneStep();

		// N��ڂ̌J��Ԃ�����Čv�Z
		void RecalcFromIterationN(int n);

		// �������ꂽ�O�������ۓK�p
		void JointTrajStep(bool step);

		// moving?
		bool Moving() { return isMoving; }
		// spring, damper set
		void SetSpringDamper(double s = 1e10, double d = 1e10, bool mul = true) {
			this->springRate = s;
			this->damperRate = d;
			this->bMultiplePD = mul;
		}
		// replay
		void Replay(int ite, bool noncorrected = false);
		// return best
		int GetBest() { return best; }
		void ReloadCorrected(int k, bool nc = false);

		// getters for trajectory
		Posed GetTrajctoryData(int k, int n) { return Posed(); }
		Posed GetNotCorrectedTrajctoryData(int k, int n) { return Posed(); }
		SpatialVector GetVeclocityData(int k, int n) { return SpatialVector(); }
		SpatialVector GetNotCorrectedVelocityData(int k, int n) { return SpatialVector(); }
	};
}

#endif
