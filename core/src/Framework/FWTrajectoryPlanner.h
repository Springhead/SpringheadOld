#ifndef FWTRAJECTORYPLANNER_H
#define FWTRAJECTORYPLANNER_H

#include <Framework/SprFWOptimizer.h>
#include <Foundation/Object.h>
#include <Framework/FrameworkDecl.hpp>

namespace Spr {
	; 
	class MinJerkTrajectory {
	private:
		ControlPoint sPoint;
		ControlPoint fPoint;
		int stime;
		int ftime;
		ControlPoint vPoint;
		int vtime;
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
		Quaterniond GetCurrentQuaternion(int t);
		Quaterniond GetDeltaQuaternion(int t);
	};

	class FWTrajectoryPlanner : public Object{

		//Joint�n�̊Ǘ��N���X
		class Joint {
		public:
			virtual void Initialize(int iterate, int movetime) {};
			virtual void SaveTorque(int n) = 0;
			virtual void SaveTarget() = 0;
			virtual void SetTarget(int k, int n) = 0;
			virtual void SetOffsetFromLPF(int n) = 0;
			virtual void ResetOffset() = 0;
			virtual void SavePosition(int k, int n) = 0;
			virtual void SaveViaPoint(int v, int t) = 0;
			virtual void SavePositionFromLPF(int k, int n) = 0;
			virtual void TrajectoryCorrection(int k, bool s) = 0;
			virtual void TrajectoryCorrectionWithVia(int k, bool s) = 0;
			virtual void ApplyLPF(int lpf, int count) = 0;
			virtual void Soften() = 0;
			virtual void Harden() = 0;
			virtual void ResetPD() = 0;
			virtual double CalcTotalTorqueChange() = 0;
			virtual double CalcTorqueChangeInSection(int n) = 0;
			virtual void SetBestTorqueChange() = 0;
			virtual void ShowInfo() = 0;
			virtual void SetTargetCurrent() = 0;
			virtual void SetTargetFromLPF(int k, int n) = 0;
		};
		class HingeJoint : public Joint {
		public:
			PHIKHingeActuatorIf* hinge;
			PTM::VVector<double> torque;
			PTM::VVector<double> torqueLPF;
			PTM::VMatrixRow<double> angle;
			PTM::VMatrixRow<double> angleLPF;
			double targetAngle;
			double targetVel;
			PTM::VVector<double> viaAngles;
			PTM::VVector<double> viaVels;
			PTM::VVector<int> viatimes;
			double deltaViaAngle;
			double initialTorque;
			double initialAngle;
			double initialVel;
			int iterate;
			int movetime;
			double weight = 1.0;
			double rateLPF = 1.0;
			double originalSpring;
			double originalDamper;
			double hardenSpring = 1e10;
			double hardenDamper = 1e8;
			bool mul = true;
			double vel = 0;
			PTM::VVector<double> tChanges;
			bool viaCorrect;
			PTM::VMatrixRow<double> CorrTraj;
		public:
			HingeJoint(PHIKHingeActuatorIf* hinge);
			//~HingeJoint();
			void Initialize(int iterate, int mtime, int nVia, double rate = 1.0, bool vCorr = true);
			void SaveTorque(int n);
			void SaveTarget();
			void SetTarget(int k, int n);
			void SetOffsetFromLPF(int n);
			void ResetOffset();
			void SavePosition(int k, int n);
			void SavePositionFromLPF(int k, int n);
			void SaveViaPoint(int v, int t);
			void TrajectoryCorrection(int k, bool s);
			void TrajectoryCorrectionWithVia(int k, bool s);
			void ApplyLPF(int lpf, int count);
			void Soften();
			void Harden();
			void ResetPD();
			double CalcTotalTorqueChange();
			double CalcTorqueChangeInSection(int n);
			void SetBestTorqueChange();
			void ShowInfo();
			void SetTargetCurrent();
			void SetPD(double s, double d, bool mul);
			void SetTargetFromLPF(int k, int n);
			void UpdateIKParam(double b, double p);
		};
		class BallJoint : public Joint {
		public:
			PHIKBallActuatorIf* ball;
			PTM::VVector<Vec3d> torque;
			PTM::VVector<Vec3d> torqueLPF;
			PTM::VMatrixRow<Quaterniond> ori;
			PTM::VMatrixRow<Quaterniond> oriLPF;
			Quaterniond targetOri;
			Vec3d targetVel;
			Quaterniond deltaEndOri;
			PTM::VVector<Quaterniond> viaOris;
			PTM::VVector<Vec3d> viaVels;
			PTM::VVector<int> viatimes;
			Quaterniond deltaViaOri;
			int viatime;
			Vec3d initialTorque;
			Quaterniond initialOri;
			Vec3d initialVel;
			int iterate;
			int movetime;
			double weight = 1.0;
			double rateLPF = 1.0;
			double originalSpring;
			double originalDamper;
			double hardenSpring = 1e10;
			double hardenDamper = 1e8;
			bool mul = true;
			Vec3d vel = Vec3d();
			PTM::VVector<double> tChanges;
			bool viaCorrect;
		public:
			BallJoint(PHIKBallActuatorIf* ball);
			~BallJoint();
			void Initialize(int iterate, int mtime, int nVia, double rate = 1.0, bool vCorr = true);
			void SaveTorque(int n);
			void SaveTarget();
			void SetTarget(int k, int n);
			void SetOffsetFromLPF(int n);
			void ResetOffset();
			void SavePosition(int k, int n);
			void SaveViaPoint(int v, int t);
			void SavePositionFromLPF(int k, int n);
			void TrajectoryCorrection(int k, bool s);
			void TrajectoryCorrectionWithVia(int k, bool s);
			void SetBestTorqueChange();
			void ApplyLPF(int lpf, int count);
			void Soften();
			void Harden();
			void ResetPD();
			double CalcTotalTorqueChange();
			double CalcTorqueChangeInSection(int n);
			void ShowInfo();
			void SetTargetCurrent();
			void SetPD(double s, double d, bool mul);
			void SetTargetFromLPF(int k, int n);
			void UpdateIKParam(double b, double p);
		};
		class Joints {
			friend class Joint;
		public:
			std::vector<Joint*> joints;
			std::vector<BallJoint> balls;
			std::vector<HingeJoint> hinges;
		public:
			Joints();
			~Joints();
			void RemoveAll();
			void Add(PHIKActuatorIf* j);
			void initialize(int iterate, int movetime, int nVia, double rate = 1.0, bool vCorr = true);
			void SetTarget(int k, int n);
			void SaveTorque(int n);
			void SaveTarget();
			void SetOffsetFromLPF(int n);
			void ResetOffset();
			void SavePosition(int k, int n);
			void SaveViaPoint(int v, int t);
			void SavePositionFromLPF(int k, int n);
			void TrajectoryCorrection(int k, bool s);
			void TrajectoryCorrectionWithVia(int k, bool s);
			void SetBestTorqueChange();
			double GetBestTorqueChangeInSection(int n);
			void ApplyLPF(int lpf, int count);
			void Soften();
			void Harden();
			void ResetPD();
			double CalcTotalTorqueChange();
			double CalcTorqueChangeInSection(int n);
			void ShowInfo();
			void SetTargetCurrent();
			void SetWeight();
			void SetPD(double s, double d, bool mul);
			void SetTargetFromLPF(int k, int n);
			void UpdateIKParam(double b, double p);
		};

		struct LPF {
			//BiQuad LPF
			static PTM::VMatrixRow<double> BiQuad(PTM::VMatrixRow<double> input, double samplerate, double freq, double q);
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
		//����ΏۂƂȂ�G���h�G�t�F�N�^
		PHIKEndEffectorIf* eef;
		//�J�n�p��
		ControlPoint startPoint = ControlPoint();
		//�ڕW�p��
		ControlPoint targetPoint = ControlPoint();
		//�r���ʉߓ_
		ControlPoint viaPoint = ControlPoint();
		std::vector<ControlPoint> viaPoints;
		//�ړ����Ԃ�b�ŕ\��������
		double mtime;
		//�ړ����Ԃ�Step���ɂ�������(mtime�v��Ȃ��H)
		int movtime;
		//�l������֐߂̐[��
		int depth;
		//�l������Actuator
		Joints joints;
		//�J��Ԃ���
		int iterate;
		//�o�R���ԕ␳�ő��
		int iterateViaAdjust;
		//�o�R���ԕ␳��
		double viaAdjustRate;

		//----- Scene�ƕۑ��p��States -----
		PHSceneIf* scene;
		UTRef<ObjectStatesIf> states;
		UTRef<ObjectStatesIf> cstates;
		UTRef<ObjectStatesIf> initialstates;
		UTRefArray<ObjectStatesIf> tmpstates;

		//----- �g���N���琶�������O���f�[�^�Q -----
		PTM::VMatrixRow<Posed> trajData;
		PTM::VMatrixRow<Posed> trajDataNotCorrected;
		PTM::VMatrixRow<Vec4d> trajVel;
		PTM::VMatrixRow<Vec4d> trajVelNotCorrected;
		PTM::VMatrixRow<Posed> ContinuousTrajData;

		//�Đ����ɂ܂��ړ������ǂ���
		bool moving;
		//(replay����)�Đ��O��index�A�ʏ�͍Ō�̂���
		int ite;
		//�v�Z�ς݂��̃t���O
		bool calced;
		//���v���C���̓K�p�X�e�b�v
		int repCount;
		//�ɏ��l���Ƃ����O���̔ԍ�
		int best;

		//----- ���[�p�X�֌W -----
		//BiQuadLPS�p�̎Ւf���g����Q�l
		double freq;
		double qvalue;
		//N�_����
		int nsma;
		double mag;
		//�E�F�C�g
		PTM::VVector<double> weight;
		//���[�p�X�̊|���
		double rate = 1.0;

		//----- �v�Z����PD�l�Ɋւ���ϐ� -----
		//�g���N->�O����������spring&damper
		double spring = 1e10;
		double damper = 1e10;
		bool mul = true;

		//----- Unity����ǂ��܂œK�p���邩�̃t���O -----
		//correction��K�p���邩�̃t���O
		int correction;
		//�C���O�̋O����Save���邩
		bool saveNotCorrected;
		//���B�܂ő҂�
		bool waitFlag;
		//�C���O�O�����Đ����邩�̃t���O
		bool noncorrectedReplay;
		//���B�ڕW�̎p�����Œ肷�邩�̃t���O
		bool staticTarget;
		//�֐ߎ������x�ŏ��O���������O���Ƃ��邩�̃t���O
		bool jointMJT;
		//���[�p�X�E�F�C�g�𓮓I�ɕω������邩�̃t���O
		bool dynamicalWeight;
		//
		bool viaCorrect;

		//�g���N�ω�
		PTM::VVector<double> torquechange;
		double totalchange;
		double besttorque;

	public:
		SPR_OBJECTDEF(FWTrajectoryPlanner);
		SPR_DECLMEMBEROF_FWTrajectoryPlannerDesc;
		//�R���X�g���N�^
		FWTrajectoryPlanner(const FWTrajectoryPlannerDesc& desc = FWTrajectoryPlannerDesc()) {
			SetDesc(&desc);
		}
		FWTrajectoryPlanner(int d, int i, int iv, double f, double q, int n, double mg, int c, bool wf, bool snc = false, double r = 1.0, double vRate = 0.65);

		//----- �v�Z�p�֐� -----
		//joint�̐[���̃`�F�b�N�Ɠ�������
		void CheckAndSetJoints();
		//���x�ŏ��O������
		void MakeMinJerkAndSave();
		void MakeMinJerkAndSaveWithViaPoint();
		//Forward 
		void JointForward(int k, bool via = false);
		//Inverse
		void JointInverse(int k, bool via = false);
		//�␳
		void JointTrajCorrection(int k);
		void JointTrajCorrectionWithViaPoint(int k);
		//�f�o�b�O�p���\��
		void Debug();
		//�f�o�b�O�p�A�E�g�v�b�g�t�@�C���̑�{����
		void PrepareOutputFilename(std::string& filename);
		//�O���f�[�^�̏o��
		void OutputTrajectory(std::string filename);
		void OutputNotCorrectedTrajectory(std::string filename);
		void OutputVelocity(std::string filename);
		//���[�h
		void LoadScene();

		//������
		//Forward Inver Relaxation Model
		void FIRM(ControlPoint tpoint, int LPFmode, int smoothCount, std::string output, bool bChange, bool pChange, bool staticTarget, bool jmjt);
		//viatime adjustment
		bool ViatimeAdjustment();
		//viatime initialize
		void ViatimeInitialize();
		//MakeMinJerk�����_��
		void MakeMinJerkAll();
		//
		void Forward(int k);
		void Inverse(int k);
		void Correction(int k);
		void CalcTrajectory(ControlPoint tpoint, int LPFmode, int smoothCount, std::string output, bool bChange, bool pChange, bool staticTarget, bool jmjt);
		int TimeToStep(double t) {
			t *= scene->GetTimeStepInv();
			return ((t - (int)t) < 0.5) ? (int)t : (int)(t + 1);
		}

		//-----�C���^�t�F�[�X�̎���-----

		//�������n
		void Reset(int d, int i, int iv, int n, double mg, int c, bool wf, bool snc = false, double r = 1.0, double vRate = 0.65, bool vCorr = true) {
			this->depth = d;
			this->iterate = i;
			this->iterateViaAdjust = iv;
			this->nsma = n;
			this->mag = mg;
			this->correction = c;
			this->rate = r;
			this->viaAdjustRate = vRate;
			this->waitFlag = wf;
			this->saveNotCorrected = snc;
			this->viaCorrect = vCorr;
		}

		void Init();

		void Init(int d, int i, int iv, int n, double mg, int c, bool wf, bool snc, double r = 1.0, double vRate = 0.65, bool vCorr = true);
		
		//�G���h�G�t�F�N�^�ݒ�
		void SetControlTarget(PHIKEndEffectorIf* e);

		//�V�[���ݒ�
		void SetScene(PHSceneIf* s);

		//�w��_�ʉߋO���v�Z
		void CalcTrajectoryWithViaPoint(ControlPoint tpoint, ControlPoint vpoint, int LPFmode, int smoothCount, std::string output, bool bChange, bool pChange, bool staticTarget, bool jmjt);

		//�A���O���v�Z
		void CalcContinuousTrajectory(int LPFmode, int smoothCount, std::string filename, bool bChange, bool pChange, bool staticTarget, bool jmjt);
		void AddControlPoint(ControlPoint c);

		//�֐ߊp�x�����O���v�Z
		void JointCalcTrajectory(Posed tPose, double mt, int LPFmode, int smoothCount, std::string output, bool bChange = false, bool pChange = false, bool staticTarget = false, bool jmjt = false);
		void JointRecalcFromIterateN(Posed tPose, double mt, int LPFmode, int smoothCount, std::string output, bool bChange = false, bool pChange = false, bool staticTarget = false, bool jmjt = false);

		//N��ڂ̌J��Ԃ�����Čv�Z
		void RecalcFromIterationN(int n);

		//�������ꂽ�O�������ۓK�p
		void JointTrajStep(bool step);

		//moving?
		bool Moving() { return moving; }
		//spring, damper set
		void SetPD(double s = 1e10, double d = 1e10, bool mul = true);
		//replay
		void Replay(int ite, bool noncorrected = false);
		//return totalChange
		double GetTotalChange();
		//return best
		int GetBest();
	};

}

#endif
