#ifndef FWTRAJECTORYPLANNER_H
#define FWTRAJECTORYPLANNER_H

#include <Framework/SprFWOptimizer.h>
#include <Foundation/Object.h>
#include <Framework/FrameworkDecl.hpp>
#include <Framework/FWOptimizer.h>

namespace Spr {
	; 

	/**  FWTrajectoryPlanner
	     �g���N�ω��ŏ��O����p���Ċ֐ߌn���R���g���[�����邽�߂̌v�Z�N���X
		 �Q�l�_��
		  Title : Trajectory Formation of Arm Movement by a Neural Network with Forward and Inverse Dynamics Models
		  Authors : Yasuhiro WADA and Mitsuo KAWATO
		  Outline : They got approximate solution of Minimum Torque Change Model by using iterative method named FIRM(Forward Inverse Relaxation Model).

	*/

	class MinJerkTrajectory {
	private:
		ControlPoint sPoint;
		ControlPoint fPoint;
		int stime;
		int ftime;
		// �o�R�_���
		ControlPoint vPoint;
		int vtime;
		// �W���s��
		PTM::TMatrixRow<6, 3, double> coeffToV;
		PTM::TMatrixRow<6, 3, double> coeffToF;
	public:
		//�R���X�g���N�^(�������̌W�������߂�)
		//default
		MinJerkTrajectory();
		//�J�n�ʒu�ƏI�[�ʒu�̂�
		MinJerkTrajectory(Posed spose, Posed fpose, int time);
		//�o�R�_����(�o�R�_�ł̑��x�Ɖ����x�͓����Ōv�Z)
		MinJerkTrajectory(Posed spose, Posed fpose, Posed vpose, int time, int vtime);
		//�J�n�ƏI�[�̈ʒu�A���x�A�����x�w��
		MinJerkTrajectory(Posed spose, Posed fpose, Vec3d sVel, Vec3d fVel, Vec3d sAcc, Vec3d fAcc, int time, double per);
		MinJerkTrajectory(ControlPoint spoint, ControlPoint fpoint, double per);
		//�J�n�ƏI�_�̈ʒu�A���x�ƒʉߓ_�̈ʒu�A�ʉߎ��Ԏw��
		MinJerkTrajectory(Posed spose, Posed fpose, Vec3d sVel, Vec3d fVel, Posed vPose, int vtime, int time, double per);
		MinJerkTrajectory(ControlPoint spoint, ControlPoint fpoint, ControlPoint vpoint, double per);
		Posed GetCurrentPose(int t);
		Posed GetDeltaPose(int t);
		Vec6d GetCurrentVelocity(int t);
		double GetCurrentActiveness(int t);
	};

	class AngleMinJerkTrajectory {
	private:
		double sAngle;
		double fAngle;
		int stime;
		int ftime;
		double vAngle;
		int vtime;
		PTM::TVector<6, double> coeffToV;
		PTM::TVector<6, double> coeffToF;
	public:
		//�R���X�g���N�^(�������̌W�������߂�)
		//default
		AngleMinJerkTrajectory();
		//�J�n�ʒu�ƏI�[�ʒu�̂�
		AngleMinJerkTrajectory(double sangle, double fangle, int time);
		AngleMinJerkTrajectory(double sangle, double fangle, double sVel, double fVel, double sAcc, double fAcc, int time, double per);
        AngleMinJerkTrajectory(double sangle, double fangle, double sVel, double fVel, double vangle, double vVel, int time, int vtime, double per);
		AngleMinJerkTrajectory(double vAngle, int time, int vtime, double per);
		double GetCurrentAngle(int t);
		double GetDeltaAngle(int t);
		double GetCurrentVelocity(int t);
	};

	class QuaMinJerkTrajectory {
	private:
		Quaterniond sQua;
		Quaterniond fQua;
		int stime;
		int ftime;
		Quaterniond vQua;
		int vtime;
		Vec3d axis;
		double angle;
		AngleMinJerkTrajectory* amjt;
		PTM::VVector<Quaterniond> velToQua;
		PTM::TMatrixRow<6, 1, double> coeffToV;
		PTM::TMatrixRow<6, 1, double> coeffToF;
	public:
		//�R���X�g���N�^(�������̌W�������߂�)
		//default
		QuaMinJerkTrajectory();
		//�J�n�ʒu�ƏI�[�ʒu�̂�
		QuaMinJerkTrajectory(Quaterniond squa, Quaterniond fqua, Vec3d sVel, Vec3d fVel, int time, double per);
		QuaMinJerkTrajectory(Quaterniond squa, Quaterniond fqua, Vec3d sVel, Vec3d fVel, Vec3d sAcc, Vec3d fAcc, int time, double per);
		QuaMinJerkTrajectory(Quaterniond vqua, int time, int vtime, double per);
		~QuaMinJerkTrajectory();
		Quaterniond GetCurrentQuaternion(int t);
		Quaterniond GetDeltaQuaternion(int t);
		Vec3d GetCurrentVelocity(int t);
	};

	class FWTrajectoryPlanner : public Object{
	public:
		//Joint�n�̊Ǘ��N���X(PHJoint�Ƃ͕�)
		class Joint {
		public:
			virtual void Initialize(int iterate, int movetime, int nVia, double rate = 1.0, bool vCorr = true) = 0;
			virtual void MakeJointMinjerk(int cnt) = 0;
			virtual void CloseFile() = 0;
			virtual void SaveTorque(int n) = 0;
			virtual void SaveTarget() = 0;
			virtual void SetTarget(int k, int n) = 0;
			virtual void SetTargetVelocity(int k, int n) = 0;
			virtual void SetTargetInitial() = 0;
			virtual void SetOffsetFromLPF(int n) = 0;
			virtual void ResetOffset() = 0;
			virtual void SavePosition(int k, int n) = 0;
			virtual void SaveVelocity(int k, int n) = 0;
			virtual void SaveViaPoint(int v, int t) = 0;
			virtual void SavePositionFromLPF(int k, int n) = 0;
			virtual void SaveVelocityFromLPF(int k, int n) = 0;
			virtual void SaveVelocityForwardEnd() = 0;
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
		class HingeJoint : public Joint {
		public:
			PHIKHingeActuatorIf* hinge;          //�A�N�`���G�[�^

			PTM::VVector<double> torque;         //Inverse���ɋL�^�����g���N
			PTM::VVector<double> torqueLPF;      //LPF��g���N
			PTM::VMatrixRow<double> angle;       //Inverse�œ������p�p�x(�C������)
			PTM::VMatrixRow<double> angleLPF;    //Forward���ɋL�^����p�x
			PTM::VMatrixRow<double> angleVels;
			PTM::VMatrixRow<double> angleVelsLPF;

			double targetAngle;                  //�^�[�Q�b�g�ƂȂ�֐ߊp
			double targetVel;                    //�^�[�Q�b�g�ƂȂ�p���x(�ʏ��0)
			PTM::VVector<double> viaAngles;      //�o�R�_�ɂ�����p�x
			PTM::VVector<double> viaVels;        //�o�R�_�ɂ�����p���x
			PTM::VVector<int> viatimes;          //�o�R�_�̒ʉߎ���

			double initialTorque;                //�J�n���̔����g���N
			double initialAngle;                 //�J�n���̊֐ߊp�x
			double initialVel;                   //�J�n���̊p���x

			int iterate;                         //�J��Ԃ���
			int movetime;                        //���v�X�e�b�v
			double weight = 1.0;                 //�]���E�F�C�g
			double rateLPF = 1.0;                //LPF�̃��[�g
			double originalSpring;               //���̂΂˒萔
			double originalDamper;               //���̃_���p�萔
			double hardenSpring = 1e30;
			double hardenDamper = 1e8;
			bool mul = true;
			PTM::VVector<double> tChanges;
			bool viaCorrect;
			PTM::VMatrixRow<double> CorrTraj;
			double velBeforeEnd;
			
		private:
			std::ofstream* torGraph;
			std::ofstream* torChangeGraph;
			bool outputEnable = false;
			
		public:
			HingeJoint(PHIKHingeActuatorIf* hinge, std::string path, bool oe);
			~HingeJoint();
			void Initialize(int iterate, int mtime, int nVia, double rate = 1.0, bool vCorr = true);
			void MakeJointMinjerk(int cnt);
			void CloseFile();
			void SaveTorque(int n);
			void SaveTarget();
			void SetTarget(int k, int n);
			void SetTargetVelocity(int k, int n);
			void SetTargetInitial();
			void SetOffsetFromLPF(int n);
			void ResetOffset();
			void SavePosition(int k, int n);
			void SaveVelocity(int k, int n);
			void SavePositionFromLPF(int k, int n);
			void SaveVelocityFromLPF(int k, int n);
			void SaveVelocityForwardEnd();
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
		};
		class BallJoint : public Joint {
		public:
			PHIKBallActuatorIf* ball;            // �A�N�`���G�[�^

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
			PTM::VVector<int> viatimes;          // �o�R�_�̒ʉߎ���

			Vec3d initialTorque;                 // �J�n���̔����g���N
			Quaterniond initialOri;              // �J�n���̊֐ߊp�x
			Vec3d initialVel;                    // �J�n���̊p���x

			int iterate;                         // �J��Ԃ���
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
			Vec3d velBeforeEnd;

		private:
			std::ofstream* torGraph;
			std::ofstream* torChangeGraph;
			bool outputEnable = false;

		public:
			BallJoint(PHIKBallActuatorIf* ball, std::string path, bool oe);
			~BallJoint();
			void Initialize(int iterate, int mtime, int nVia, double rate = 1.0, bool vCorr = true);
			void MakeJointMinjerk(int cnt);
			void CloseFile();
			void SaveTorque(int n);
			void SaveTarget();
			void SetTarget(int k, int n);
			void SetTargetVelocity(int k, int n);
			void SetTargetInitial();
			void SetOffsetFromLPF(int n);
			void ResetOffset();
			void SavePosition(int k, int n);
			void SaveVelocity(int k, int n);
			void SaveViaPoint(int v, int t);
			void SavePositionFromLPF(int k, int n);
			void SaveVelocityFromLPF(int k, int n);
			void SaveVelocityForwardEnd();
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
		};
		class Joints {
			friend class Joint;
		public:
			std::vector<Joint*> joints;
			//std::vector<BallJoint> balls;
			//std::vector<HingeJoint> hinges;
		public:
			Joints();
			~Joints();
			void RemoveAll();
			void Add(PHIKActuatorIf* j, std::string path, bool oe = true);
			void Initialize(int iterate, int movetime, int nVia, double rate = 1.0, bool vCorr = true);
			void MakeJointMinjerk(int cnt);
			void CloseFile();
			void SetTarget(int k, int n);
			void SetTargetVelocity(int k, int n);
			void SetTargetInitial();
			void SaveTorque(int n);
			void SaveTarget();
			void SetOffsetFromLPF(int n);
			void ResetOffset();
			void SavePosition(int k, int n);
			void SaveVelocity(int k, int n);
			void SaveViaPoint(int v, int t);
			void SavePositionFromLPF(int k, int n);
			void SaveVelocityFromLPF(int k, int n);
			void SaveVelocityForwardEnd();
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
		};

		struct LPF {
			//N-Simple Moving Average LPF
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
		//----- �v�Z�ɂ��������� -----
		// ����ΏۂƂȂ�G���h�G�t�F�N�^
		PHIKEndEffectorIf* eef;
		// �J�n�p��
		ControlPoint startPoint = ControlPoint();
		// �ڕW�p��
		ControlPoint targetPoint = ControlPoint();
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
		// �l������֐߂̐[��
		//int depth;
		// �l������Actuator
		Joints joints;
		// �J��Ԃ���
		//int iterate;
		// �o�R���ԕ␳�ő��
		//int iterateViaAdjust;
		// �o�R���ԕ␳��
		//double viaAdjustRate;
		// ���U�����Ƃ��Ɏ~�߂�
		bool stop;

		//----- Scene�ƕۑ��p��States -----
		PHSceneIf* scene;
		UTRef<ObjectStatesIf> states;
		UTRef<ObjectStatesIf> initialstates;
		UTRefArray<ObjectStatesIf> tmpstates;
		UTRefArray<ObjectStatesIf> corstates;
		UTRefArray<ObjectStatesIf> beforecorstates;

		//----- �g���N���琶�������O���f�[�^�Q -----
		PTM::VMatrixRow<Posed> trajData;
		PTM::VMatrixRow<Posed> trajDataNotCorrected;
		PTM::VMatrixRow<Vec4d> trajVel;
		PTM::VMatrixRow<Vec4d> trajVelNotCorrected;

		//----- �o�͐�p�X -----
		std::string path;

		// �Đ����ɂ܂��ړ������ǂ���
		bool moving;
		// (replay����)�Đ��O��index�A�ʏ�͍Ō�̂���
		int ite;
		// �v�Z�ς݂��̃t���O
		bool calced;
		// ���v���C���̓K�p�X�e�b�v
		int repCount;
		// �ɏ��l���Ƃ����O���̔ԍ�
		int best;

		//----- ���[�p�X�֌W -----
		// ���[�p�X�̊|���
		//double rate = 1.0;

		//----- �v�Z����PD�l�Ɋւ���ϐ� -----
		// �g���N->�O����������spring&damper
		//double spring = 1e10;
		//double damper = 1e10;
		//bool mul = true;

		//----- Unity����ǂ��܂œK�p���邩�̃t���O -----
		// correction��K�p���邩�̃t���O
		//bool correction;
		// ���B�ڕW�̎p�����Œ肷�邩�̃t���O
		//bool staticTarget;
		// �֐ߎ������x�ŏ��O���������O���Ƃ��邩�̃t���O
		//bool jointMJT;
		// �C���O�O�����Đ����邩�̃t���O
		bool noncorrectedReplay;
		// �o�R�_�̏C�����s����
		//bool viaCorrection;
		// �������B�ɂ����ăo�l���g�p���邩
		//bool springCorrection;

		// �g���N�ω�
		PTM::VVector<double> torquechange;
		double totalchange;
		double besttorque;

		// �v�Z�t�F�C�Y
		enum Phase {
			MINJERK,
			FORWARD,
			INVERSE,
		};
		Phase phase;

		// �t�F�C�Y�V�t�g
		void PhaseShift() {
			switch (phase) {
			case Phase::FORWARD:
			case Phase::MINJERK:
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
		FWTrajectoryPlanner(int d, int i, int iv, bool c, double r = 1.0, double vRate = 0.65, bool sc = false);

		//----- �v�Z�p�֐� -----
		//joint�̐[���̃`�F�b�N�Ɠ�������
		void CheckAndSetJoints();
		//�f�o�b�O�p���\��
		void Debug();
		//�O���f�[�^�̏o��
		void OutputTrajectory(std::string filename);
		void OutputNotCorrectedTrajectory(std::string filename);
		void OutputVelocity(std::string filename);

		//Forward Inverse Relaxation Model
		void FIRM(ControlPoint tpoint, std::string output);
		//MakeMinJerk�����_��
		void MakeMinJerkAll();
		//Forward model(torque -> pos)
		void Forward(int k);
		//Inverse model(pos -> torque)
		void Inverse(int k);
		//
		void Correction(int k);
		//viatime adjustment
		bool ViatimeAdjustment();
		//viatime initialize
		void ViatimeInitialize();
		//Prepare solids and springs for correction
		void PrepareSprings();
		//
		int TimeToStep(double t) {
			t *= scene->GetTimeStepInv();
			return std::round(t);
		}

		//-----�C���^�t�F�[�X�̎���-----

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

		// �p�����[�^�̃��Z�b�g
		void ResetParameters(int d, int i, int iv, bool c, double r = 1.0, double vRate = 0.65, bool vCorr = true, bool sc = false) {
			this->depth = d;
			this->maxIterate = i;
			this->maxIterateViaAdjust = iv;
			this->bCorrection = c;
			this->LPFRate = r;
			this->viaAdjustRate = vRate;
			this->bViaCorrection = vCorr;
			this->bUseSpringCorrection = sc;
		}

		// ����������
		void Init();
		void Init(int d, int i, int iv, bool c, double r = 1.0, double vRate = 0.65, bool vCorr = true, bool sc = false);
		
		//�G���h�G�t�F�N�^�ݒ�
		void SetControlTarget(PHIKEndEffectorIf* e) { this->eef = e; }

		//�V�[���ݒ�
		void SetScene(PHSceneIf* s) { this->scene = s; }
		void AddControlPoint(ControlPoint c) { viaPoints.push_back(c); }

		//�v�Z���s
		void CalcTrajectory(ControlPoint tpoint, std::string output);

		void PhaseExecution() {};

		//N��ڂ̌J��Ԃ�����Čv�Z
		void RecalcFromIterationN(int n);

		//�������ꂽ�O�������ۓK�p
		void JointTrajStep(bool step);

		//moving?
		bool Moving() { return moving; }
		//spring, damper set
		void SetPD(double s = 1e10, double d = 1e10, bool mul = true) {
			this->springRate = s;
			this->damperRate = d;
			this->bMultiplePD = mul;
		}
		//replay
		void Replay(int ite, bool noncorrected = false);
		//return totalChange
		double GetTotalChange() { return totalchange; }
		//return best
		int GetBest() { return best; }
		void ReloadCorrected(int k, bool nc = false);
	};
}

#endif
