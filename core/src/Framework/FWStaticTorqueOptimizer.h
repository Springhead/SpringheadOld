#ifndef FWSTATICTORQUEOPTIMIZER_H
#define FWSTATICTORQUEOPTIMIZER_H

#include <Framework/SprFWOptimizer.h>
#include <Framework/FWOptimizer.h>
#include <Framework/FrameworkDecl.hpp>

#include<../src/Foundation/UTClapack.h>

namespace Spr {
	;

	class GrahamConvexHull : public UTRefCount {
		struct Sort {
			static void quicksort(std::vector<Vec3f>& ver, int i, int j, Vec3d normal);
			static void simplesort(std::vector<Vec3f>& ver, Vec3d normal);
		};
	public:
		//�ʏW���`���̓_�W��
		std::vector<Vec3f> hull;
		//���p�`�̉����S
		Vec3f center;
		//���p�`�@��
		Vec3d normal;
		//�ʂ̌��_����̋���
		double dist;
	public:
		GrahamConvexHull();
		~GrahamConvexHull();
		//�^����ꂽ�_�W������O���n���ʑ��p�`���Čv�Z
		void Recalc(std::vector<Vec3f> vertices);
		//�O���n���ʑ��p�`���ɗ^�����_�����邩
		bool InsideGrahamConvexHull(Vec3f v);
		//���p�`���S����̋����ɉ������]���l�i��->��j
		double Eval(Vec3f v);
		//���p�`���Ȃ��_�W����Ԃ�
		Vec3f* GetVertices();
	};

	template<class TVtx>
	class FWQuickHull2D {
	public:
		std::vector<TVtx> points;
		Vec3d** begin;
		Vec3d** end;
	};

	class FWSupportPolygon {
	public:
		Vec3d normal;
		Vec3d dist;
	};

	// �֐߂��Ƃ̃E�F�C�g�ۑ��p�̍\����
	struct JointWeight {
	public:
		PHJointIf* joint;
		double weight;
		JointWeight() : joint(NULL), weight(1.0) {}
		JointWeight(PHJointIf*jo, double w) {
			joint = jo;
			weight = w;
		}
	};
	
	class FWStaticTorqueOptimizer : public FWOptimizer {
		std::vector<JointPos> initialPos;
		Vec3d initialRootPos;

		double errorWeight, stabilityWeight, torqueWeight, constWeight, gravcenterWeight, differentialWeight;    // �e�]���lWeight

		std::vector<FWGroundConstraint*> groundConst;               // �ڒn�S���W���A�Ƃ肠���������₷�������̂�vector
		std::vector<FWUngroundedConstraint*> ungroundedConst;       // ��ڒn�S��

		std::vector<int> bodyIndex;            // �g�̍\�����̂�index

		std::vector<JointWeight> jointWeights;

		// �f�[�^���M�p
		FWObjectiveValues val;                 // �]���l����ۑ��\����
		Vec3d cog;                             // �d�S���W
		double mass;
		std::vector<Vec3f> supportPolygon;     // �x�����p�`�`�����_�W��

	public:
		SPR_OBJECTDEF(FWStaticTorqueOptimizer);
		SPR_DECLMEMBEROF_FWStaticTorqueOptimizerDesc;

		FWStaticTorqueOptimizer(const FWStaticTorqueOptimizerDesc& desc = FWStaticTorqueOptimizerDesc()) {
			SetDesc(&desc);
		}

		void Init();

		void Iterate();

		void ApplyResult(PHSceneIf* phScene);

		double ApplyPop(PHSceneIf* phScene, double const *x, int n);

		double Objective(double const *x, int n);

		void SetScene(PHSceneIf* phSceneInput);

		void Optimize();

		bool TestForTermination();

		void TakeFinalValue();

		void SetESParameters(double xs, double st, double tf, double la, double mi) { FWOptimizer::SetESParameters(xs, st, tf, la, mi); }


		double CalcErrorCriterion();
		double CalcGroundedCriterion();
		double CalcPositionCriterion();
		double CalcCOGCriterion();
		double CalcDifferenceCriterion();
		double CalcTorqueCriterion();
		double CalcStabilityCriterion();

		double CenterOfGravity(PHIKActuatorIf* root, Vec3d& point);
		double CalcTorqueInChildren(PHIKActuatorIf* root, Vec3d& point, Vec3d& forceInChildren);

		void SetErrorWeight(double v) { errorWeight = v; }
		double GetErrorWeight() { return errorWeight; }

		void SetStabilityWeight(double v) { stabilityWeight = v; }
		double GetStabilityWeight() { return stabilityWeight; }

		void SetTorqueWeight(double v) { torqueWeight = v; }
		double GetTorqueWeight() { return torqueWeight; }

		void SetConstWeight(double v) { constWeight = v; }
		double GetConstWeight() { return constWeight; }

		void SetGravcenterWeight(double v) { gravcenterWeight = v; }
		double GetGravcenterWeight() { return gravcenterWeight; }

		void SetDifferentialWeight(double v) { differentialWeight = v; }
		double GetDifferentialWeight() { return differentialWeight; }

		// GroundConstraint�̑���
		void AddPositionConst(FWGroundConstraint* f);
		FWGroundConstraint GetGroundConst(int n);
		void ClearGroundConst();

		// UngroundedConstraint�̑���
		void AddPositionConst(FWUngroundedConstraint* f);
		FWUngroundedConstraint GetUngroundConst(int n);
		void ClearUngroundedConst();

		void SetJointWeight(PHJointIf* jo, double w) {
			int n = (int)jointWeights.size();
			for (int i = 0; i < n; i++) {
				if (jointWeights[i].joint == jo) {
					jointWeights[i].weight = w;
					return;
				}
			}
			jointWeights.push_back(JointWeight(jo, w));
		}

		FWObjectiveValues GetObjectiveValues() { return this->val; }

		Vec3f GetCenterOfGravity() { return this->cog; }

		int NSupportPolygonVertices() { return (int)(this->supportPolygon.size()); }

		Vec3f GetSupportPolygonVerticesN(int n) { return this->supportPolygon[n]; }
	};
	
}

#endif
