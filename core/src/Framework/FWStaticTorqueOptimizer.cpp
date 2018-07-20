﻿#include <Framework/FWStaticTorqueOptimizer.h>

namespace Spr { ;

//----- ----- ----- -----
FWGroundConstraint::FWGroundConstraint() { this->cWeight = 1.0; this->cNormal = Vec3d(0, 0, 0); }
FWGroundConstraint::FWGroundConstraint(double w, Vec3d n) { this->cWeight = w;  this->cNormal = n.unit(); this->contactForce = Vec3d(); this->contactPoint = Vec3d(); }
double FWGroundConstraint::CalcEvalFunc() {
	Vec3d normal1 = cNormal.unit();
	Vec3d normal2 = initialPose.Ori().Inv() * cNormal.unit();
	// 現在姿勢との差分を取得
	Vec3d dPosition = cSolid->GetPose().Pos() - initialPose.Pos();
	Quaterniond dQuaternion = initialPose.Ori().Inv() * cSolid->GetPose().Ori();
	Vec3d n1 = dQuaternion * normal2;
	double gq = 1.0 - n1 * normal2;
	double gp = abs(dPosition * normal1);
#ifdef _DEBUG
	DSTR << normal << initialPose << cSolid->GetPose() << dPosition << "rotationValue:" << gq << " positionValue:" << gp << std::endl;
#endif
	return cWeight * (gq + gp);
}
void FWGroundConstraint::Init() {
	if (cSolid != NULL) {
		this->initialPose = cSolid->GetPose();
		//this->cNormal = initialPose.Ori().Inv() * cNormal;
	}
}

//----- ----- ----- -----
FWUngroundedConstraint::FWUngroundedConstraint() { this->cWeight = 1.0; this->cAxis = Vec3i(0, 0, 0); }
FWUngroundedConstraint::FWUngroundedConstraint(double w, Vec3i a, Vec3d n) { this->cWeight = w; this->cAxis = a; this->normal = n.unit(); }
double FWUngroundedConstraint::CalcEvalFunc() {
	Vec3d dPosition = cSolid->GetPose().Pos() - initialPose.Pos();
	Quaterniond dQuaternion = initialPose.Ori().Inv() * cSolid->GetPose().Ori();
	Vec3d n1 = dQuaternion * normal;
	double gq = 1.0 - n1 * normal;
	return cWeight * (abs(dPosition * cAxis) + gq);
}
void FWUngroundedConstraint::Init() {
	if (cSolid != NULL) {
		this->initialPose = cSolid->GetPose();
		this->normal = initialPose.Ori().Inv() * normal;
	}
}

JointPos::JointPos() { ori = Quaterniond(); angle = 0; }
JointPos::JointPos(Quaterniond q) { ori = q; }
JointPos::JointPos(double a) { angle = a; }


void GrahamConvexHull::Sort::quicksort(std::vector<Vec3f>& ver, int i, int j, Vec3d normal) {
	if (i >= j) return;
	int p = (i + j) / 2;
	//int k = part(ver, i, j, p);
	Vec3d criteria = Vec3d(ver[p]);
	int l = i, r = j;
	while (l <= r) {
		while (l < j && cross(criteria - ver[0], ver[l] - ver[0]).y < 0) l++;
		while (i < r && cross(criteria - ver[0], ver[r] - ver[0]).y > 0) r--;
		if (l >= r) break;
		Vec3f v = ver[l];
		ver[l] = ver[r];
		ver[r] = v;
		//DSTR << "swap(" << l << "," << r << ")" << std::endl;
		l++;
		r--;
	}
	DSTR << std::endl;
	for (int k = i; k < j + 1; k++) {
		DSTR << cross(criteria - ver[0], ver[k] - ver[0]).y << std::endl;
	}
	DSTR << std::endl;
	quicksort(ver, i, l - 1, normal);
	quicksort(ver, r + 1, j, normal);
	DSTR << "checkforall" << std::endl;
	DSTR << std::endl;
	for (int a = i; a < j + 1; a++) {
		criteria = ver[a];
		for (int k = i; k < j + 1; k++) {
			DSTR << cross(criteria - ver[0], ver[k] - ver[0]).y << std::endl;
		}
		DSTR << std::endl;
	}
}

void GrahamConvexHull::Sort::simplesort(std::vector<Vec3f>& ver, Vec3d normal) {
	int size = (int)ver.size();
	double checker;
	for (int i = 1; i < size; i++) {
		for (int j = i; j < size; j++) {
			checker = cross(ver[i] - ver[0], ver[j] - ver[0]).y;
			if (checker < 0) {
				Vec3d tmp;
				tmp = ver[j];
				ver[j] = ver[i];
				ver[i] = tmp;
			}
		}
	}
}
GrahamConvexHull::GrahamConvexHull() {
	center = Vec3f(0.0, 0.0, 0.0);
	normal = Vec3d(0.0, 1.0, 0.0);
	dist = 0;
}

GrahamConvexHull::~GrahamConvexHull() {
	std::vector<Vec3f>().swap(hull);
}

bool GrahamConvexHull::InsideGrahamConvexHull(Vec3f v) {
	bool inside = false;
	int l = (int)hull.size() - 1;
	if (l < 3) return false;
	for (int i = 1; i < l - 1; i++) {
		Vec3d cross1 = cross(v - hull[0], hull[i] - hull[0]);
		Vec3d cross2 = cross(v - hull[i], hull[i + 1] - hull[i]);
		Vec3d cross3 = cross(v - hull[i + 1], hull[0] - hull[i + 1]);
		DSTR << cross1 << cross2 << cross3 << std::endl;
		if (cross1.y * cross2.y > 0 && cross1.y * cross3.y > 0) {
			inside = true;
			DSTR << "inside!" << std::endl;
			break;
		}
	}
	return inside;
}

void GrahamConvexHull::Recalc(std::vector<Vec3f> vertices) {
	int n = (int)vertices.size();
	if (n > 2) {
		int xmax = 0;
		for (int i = 0; i < n; i++) {
			if (vertices[xmax].x < vertices[i].x) {
				xmax = i;
			}
			else if (vertices[xmax].x == vertices[i].x && vertices[xmax].z < vertices[i].z) {
				xmax = i;
			}
			vertices[i].y = 0;
		}
		Vec3f tmp = vertices[0];
		vertices[0] = vertices[xmax];
		vertices[xmax] = tmp;
		DSTR << "before sort" << std::endl;
		for (int i = 0; i < (int)vertices.size(); i++) {
			DSTR << vertices[i] << std::endl;
		}
		Sort::simplesort(vertices, normal);
		//Sort::quicksort(vertices, 1, n - 1, normal);
		DSTR << "after sort" << std::endl;
		for (int i = 0; i < (int)vertices.size(); i++) {
			DSTR << vertices[i] << std::endl;
		}
		vertices.push_back(vertices[0]);
		int m = 1;
		hull.clear();

		hull.push_back(vertices[0]); hull.push_back(vertices[1]);
		for (int i = 2; i < n + 1; i++) {
			while (cross(vertices[i] - hull[m - 1], hull[m] - hull[m - 1]).y > 0) {
				Vec3f removed = hull[m];
				hull.pop_back();
				m--;
				if (m == 0) {
					break;
				}
			}
			hull.push_back(vertices[i]);
			m++;
		}
		/*/
		for (int i = 0; i < vertices.size(); i++) {
		hull.push_back(vertices[i]);
		}
		*/
		int l = (int)hull.size() - 1;
		center = Vec3f(0.0, 0.0, 0.0);
		for (int i = 0; i < l; i++) {
			center = center + (vertices[i]) / l;
		}

	}
}

double GrahamConvexHull::Eval(Vec3f v) {
	int nHull = (int)hull.size();
	Vec3d c;
	double min = INFINITY;;
	for (int i = 0; i < nHull; i++)
		DSTR << "vertices[" << i << "]:" << hull[i] << std::endl;
	DSTR << "center of hull:" << center << std::endl;

	for (int i = 0; i < nHull; i++) {
		Vec3f edge = hull[i + 1] - hull[i];
		if (edge.norm() != 0) {
			c = cross(edge, v - hull[i]) / edge.norm();
			if (min > abs(c.y)) {
				min = abs(c.y);
			}
		}
	}
	//if (min >= 0) DSTR << "inside" << std::endl;
	return exp(10 * ((InsideGrahamConvexHull(v) ? -1 : 1) * min + 0.0));
}

Vec3f* GrahamConvexHull::GetVertices() {
	return &*hull.begin();
}


// --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- ---

void FWStaticTorqueOptimizer::Init() {
	// Save Initial Root Pos
	PHIKActuatorIf* root = phScene->GetIKActuator(0);
	while (root->GetParent()) { root = root->GetParent(); }
	if (DCAST(PHIKBallActuatorIf, root)) {
		initialRootPos = DCAST(PHIKBallActuatorIf, root)->GetJoint()->GetSocketSolid()->GetPose().Pos();
	}
	if (DCAST(PHIKHingeActuatorIf, root)) {
		initialRootPos = DCAST(PHIKHingeActuatorIf, root)->GetJoint()->GetSocketSolid()->GetPose().Pos();
	}

	// Save Initial Pos and Determine DOF
	int nJoints = phScene->NIKActuators();
	int dof = 3;
	initialPos.resize(nJoints);
	for (int i = 0; i < nJoints; ++i) {
		if (DCAST(PHIKBallActuatorIf, phScene->GetIKActuator(i))) {
			PHBallJointIf* jo = DCAST(PHIKBallActuatorIf, phScene->GetIKActuator(i))->GetJoint();
			if (jo->GetSpring() == 0) {
				jo->SetSpring(1e+30);
			}
			if (jo->GetDamper() == 0) {
				jo->SetDamper(1e+30);
			}
			initialPos[i].ori = jo->GetPosition();
			dof += 3;
		}
		if (DCAST(PHIKHingeActuatorIf, phScene->GetIKActuator(i))) {
			PHHingeJointIf* jo = DCAST(PHIKHingeActuatorIf, phScene->GetIKActuator(i))->GetJoint();
			if (jo->GetSpring() == 0) {
				jo->SetSpring(1e+30);
			}
			if (jo->GetDamper() == 0) {
				jo->SetDamper(1e+30);
			}
			initialPos[i].angle = jo->GetPosition();;
			dof += 1;
		}
	}
	for (size_t i = 0; i < groundConst.size(); i++) {
		groundConst[i]->Init();
	}
	for (size_t i = 0; i < ungroundedConst.size(); i++) {
		ungroundedConst[i]->Init();
	}

	int nSolids = phScene->NSolids();
	for (int i = 0; i < nSolids; i++) {
		PHSolidIf* so = phScene->GetSolids()[i];
		if (so->NShape() > 0) {
			for (int j = 0; j < so->NShape(); j++) {
				DSTR << "CD(" << so->GetName() << "):" << so->GetShape(j)->GetName() << std::endl;
			}
		}
	}
	DSTR << errorWeight << stabilityWeight << torqueWeight << std::endl;
	supportPolygon.clear();
	FWOptimizer::Init(dof);
	double* initObj = new double[dof]; //たまにinitObjの値が変
									   //Objective(initObj, dof);
}

void FWStaticTorqueOptimizer::Iterate() { 
#ifdef USE_CLOSED_SRC
	// Generate lambda new search points, sample population
	pop = evo->samplePopulation();

	// evaluate the new search points using objective function
	for (int i = 0; i < evo->get(CMAES<double>::Lambda); ++i) {
		states->LoadState(phScene);
		DSTR << "Loadedd scene" << std::endl;

		arFunvals[i] = Objective(pop[i], (int)evo->get(CMAES<double>::Dimension));
	}

	// update the search distribution used for sampleDistribution()
	evo->updateDistribution(arFunvals);
#endif
}

void FWStaticTorqueOptimizer::ApplyResult(PHSceneIf* phScene) { FWOptimizer::ApplyPop(phScene, GetResults(), NResults()); }

double FWStaticTorqueOptimizer::ApplyPop(PHSceneIf* phScene, double const *x, int n) {
	int nJoints = phScene->NIKActuators();
	int cnt = 0;
	double obj = 0;

	double scale = 0.1;

	// Root Solid
	PHIKActuatorIf* root = phScene->GetIKActuator(0);
	while (root->GetParent()) { root = root->GetParent(); }
	Vec3d pos = Vec3d(x[cnt + 0], x[cnt + 1], x[cnt + 2]) * scale;
	if (DCAST(PHIKBallActuatorIf, root)) {
		DCAST(PHIKBallActuatorIf, root)->GetJoint()->GetSocketSolid()->SetFramePosition(pos + initialRootPos);
	}
	if (DCAST(PHIKHingeActuatorIf, root)) {
		DCAST(PHIKHingeActuatorIf, root)->GetJoint()->GetSocketSolid()->SetFramePosition(pos + initialRootPos);
	}
	DSTR << pos << initialRootPos << std::endl;
	obj += pos.norm();
	cnt += 3;

	// Jointの初期角度をセット
	for (int i = 0; i < nJoints; ++i) {
		if (DCAST(PHIKBallActuatorIf, phScene->GetIKActuator(i))) {
			Vec3d rot = Vec3d(x[cnt + 0], x[cnt + 1], x[cnt + 2]) * scale;
			Quaterniond ori = Quaterniond::Rot(rot) * initialPos[i].ori;
			DSTR << DCAST(PHIKBallActuatorIf, phScene->GetIKActuator(i))->GetJoint()->GetPosition() << ori << std::endl;
			DCAST(PHIKBallActuatorIf, phScene->GetIKActuator(i))->SetJointTempOri(ori);
			DCAST(PHIKBallActuatorIf, phScene->GetIKActuator(i))->GetJoint()->SetTargetPosition(ori);
			obj += pow(rot.norm(), 4);
			cnt += 3;
		}
		if (DCAST(PHIKHingeActuatorIf, phScene->GetIKActuator(i))) {
			double relAngle = x[cnt] * scale;
			double angle = relAngle + initialPos[i].angle;
			DCAST(PHIKHingeActuatorIf, phScene->GetIKActuator(i))->SetJointTempAngle(angle);
			DCAST(PHIKHingeActuatorIf, phScene->GetIKActuator(i))->GetJoint()->SetTargetPosition(angle);
			obj += pow(relAngle, 4);
			cnt += 1;
		}
	}

	phScene->GetIKEngine()->FK();
	phScene->GetIKEngine()->ApplyExactState(true);

	// Find Lowest Solid

	return obj;
}

double FWStaticTorqueOptimizer::Objective(double const *x, int n) {
	double obj = 0;

	// 1. Apply x to Scene
	obj += ApplyPop(phScene, x, n);


	// 2. Do Simulation Step And Calc Criterion

	for (int i = 0; i < 1; ++i) {
		phScene->Step();
	}

	// a. Calc Error Criterion
	val.errorvalue = CalcErrorCriterion();
	obj += val.errorvalue;

	// b. gronded solids evaluation
	val.groundvalue = CalcGroundedCriterion();
	obj += val.groundvalue;

	// c. position constraint evaluation
	val.ungroundedvalue = CalcPositionCriterion();
	obj += val.ungroundedvalue;

	// d. center of gravity evaluation
	val.centervalue = CalcCOGCriterion();
	obj += val.centervalue;

	// e. evaluate difference from initial joint ori
	val.initialorivalue = CalcDifferenceCriterion();
	obj += val.initialorivalue;

	// f. Calc Torque Criterion
	val.torquevalue = CalcTorqueCriterion();
	obj += val.torquevalue;

	// g. Calc Stability Criterion
	// Evaluate from body solids velocity and angular velocity
	val.stabilityvalue = CalcStabilityCriterion();
	obj += val.stabilityvalue;

	return obj;
}

void FWStaticTorqueOptimizer::SetScene(PHSceneIf* phSceneInput) { phScene = phSceneInput; }

void FWStaticTorqueOptimizer::Optimize() { FWOptimizer::Optimize(); }

bool FWStaticTorqueOptimizer::TestForTermination() {
#ifdef USE_CLOSED_SRC
	return evo->testForTermination();
#else
	return true;
#endif
}

void FWStaticTorqueOptimizer::TakeFinalValue() {
#ifdef USE_CLOSED_SRC
	xfinal = evo->getNew(CMAES<double>::XMean);
	Objective(xfinal, (int)evo->get(CMAES<double>::Dimension));
#endif
}

double FWStaticTorqueOptimizer::CalcErrorCriterion() {
	// EndEffectorによるエラー評価
	double e = 0;
	for (int i = 0; i < phScene->NIKEndEffectors(); ++i) {
		PHIKEndEffectorIf* eef = phScene->GetIKEndEffector(i);
		if (eef->IsPositionControlEnabled()) {
			Vec3d diff = ((eef->GetSolid()->GetPose() * eef->GetTargetLocalPosition()) - eef->GetTargetPosition());
			e += pow(diff.norm(), 2);
		}
		if (eef->IsOrientationControlEnabled()) {
			e += ((eef->GetSolid()->GetOrientation() * Vec3d(1, 0, 0)) - (eef->GetTargetOrientation() * Vec3d(1, 0, 0))).norm();
			e += ((eef->GetSolid()->GetOrientation() * Vec3d(0, 1, 0)) - (eef->GetTargetOrientation() * Vec3d(0, 1, 0))).norm();
		}
	}
	return errorWeight * e;
}

double FWStaticTorqueOptimizer::CalcGroundedCriterion() {
	// 接地拘束を評価
	double g = 0;
	for (size_t i = 0; i < groundConst.size(); i++) {
		g += groundConst[i]->CalcEvalFunc();
	}
	return constWeight * g;
}

double FWStaticTorqueOptimizer::CalcPositionCriterion() {
	// 非接地位置拘束を評価
	double p = 0;
	for (size_t i = 0; i < ungroundedConst.size(); i++) {
		p += ungroundedConst[i]->CalcEvalFunc();
	}
	return constWeight * p;
}

double FWStaticTorqueOptimizer::CalcCOGCriterion() {
	// 重心位置を評価
	double g = 0;
	std::vector<Vec3f> supports;
	for (size_t i = 0; i < groundConst.size(); i++) {
		// make supporting polygon from all vertices of body grounded collider
		Vec3f* vertices;
		Vec3f v;
		int ns = groundConst[i]->cSolid->NShape();
		for (int j = 0; j < ns; j++) {
			CDShapeIf* shape = groundConst[i]->cSolid->GetShape(0);
			// Boxにしか対応していません
			if (DCAST(CDBoxIf, shape)) {
				vertices = DCAST(CDBoxIf, shape)->GetVertices();
				for (int k = 0; k < 8; k++) {
					v = groundConst[i]->cSolid->GetPose() * groundConst[i]->cSolid->GetShapePose(0) * vertices[k];
					//DSTR << "CDBoxVer[" << k << "]:" << v << std::endl;
					supports.push_back(v);
				}
			}
		}
	}

	if (!bodyIndex.empty()) {
		int bSize = (int)bodyIndex.size();
		Vec3d totalBodyGravPos = Vec3d();
		double totalBodyMass = 0;
		// Calculate position of cog
		for (int i = 0; i < bSize; i++) {
			Vec3d bodyGravPos = phScene->GetSolids()[bodyIndex[i]]->GetCenterPosition();
			double bodyMass = phScene->GetSolids()[bodyIndex[i]]->GetMass();
			totalBodyGravPos = (bodyMass / (totalBodyMass + bodyMass)) * bodyGravPos + (totalBodyMass / (totalBodyMass + bodyMass)) * totalBodyGravPos;
			totalBodyMass += bodyMass;
		}
		cog = totalBodyGravPos;
		// Create convex hull and calculate cog evaluation
		GrahamConvexHull gh = GrahamConvexHull();
		gh.Recalc(supports);
		supportPolygon.resize(gh.hull.size());
		std::copy(gh.hull.begin(), gh.hull.end(), supportPolygon.begin());
		double e = gh.Eval(totalBodyGravPos);
		g = totalBodyMass * e;
	}
	else {
		PHIKActuatorIf* root = phScene->GetIKActuator(0);
		while (root->GetParent()) { root = root->GetParent(); }
		Vec3d totalBodyGravPos = Vec3d();
		double totalBodyMass = 0;
		totalBodyMass = CenterOfGravity(root, totalBodyGravPos);
		cog = totalBodyGravPos;
		// Create convex hull and calculate cog evaluation
		GrahamConvexHull gh = GrahamConvexHull();
		gh.Recalc(supports);
		supportPolygon.resize(gh.hull.size());
		std::copy(gh.hull.begin(), gh.hull.end(), supportPolygon.begin());
		double e = gh.Eval(totalBodyGravPos);
		g = totalBodyMass * e;
	}
	return gravcenterWeight * g;
}

double FWStaticTorqueOptimizer::CalcDifferenceCriterion() {
	// 初期関節角との差分を評価
	double d = 0;
	int nJoints = phScene->NIKActuators();
	for (int i = 0; i < nJoints; i++) {
		if (DCAST(PHIKBallActuatorIf, phScene->GetIKActuator(i))) {
			Quaterniond jQuaternion = DCAST(PHIKBallActuatorIf, phScene->GetIKActuator(i))->GetJoint()->GetPosition();
			Vec3d euler;
			/// 本来はToEulerから取得したVec3dはyzxの順であることを考慮する必要があるが今回は変える必要なし
			jQuaternion.ToEuler(euler);
			Vec3d euler0;
			Quaterniond jQuaternion0 = initialPos[i].ori;
			jQuaternion0.ToEuler(euler0);
			euler0 -= euler;
			d += pow(euler0.norm(), 2);
		}
		else if (DCAST(PHIKHingeActuatorIf, phScene->GetIKActuator(i))) {
			double angle = DCAST(PHIKHingeActuatorIf, phScene->GetIKActuator(i))->GetJoint()->GetPosition() - initialPos[i].angle;
			d += pow(angle, 2);
		}
	}
	return differentialWeight * d;
}

double FWStaticTorqueOptimizer::CalcTorqueCriterion() {
	typedef double element_type;

	typedef ublas::vector< element_type >                               vector_type;
	typedef ublas::matrix< element_type, ublas::column_major >          matrix_type;
	typedef ublas::diagonal_matrix< element_type, ublas::column_major > diag_matrix_type;

	// トルクを評価
	double t = 0;
	int nContacts = (int)groundConst.size();
	PHIKActuatorIf* root = phScene->GetIKActuator(0);
	while (root->GetParent()) { root = root->GetParent(); }
	Vec3d totalBodyGravPos = Vec3d();
	double totalBodyMass = 0;
	totalBodyMass = CenterOfGravity(root, totalBodyGravPos);

	Vec3d gravity = phScene->GetGravity();

	// 接触力計算
	// utclapackを使ってみる
	matrix_type A_;
	A_.resize(6, 3 * nContacts);
	A_.clear();
	vector_type M_, F_;
	M_.resize(6);
	M_.clear();
	F_.resize(3 * nContacts);
	F_.clear();

	//接触力計算時の事前予想
	Vec3d massgrav = totalBodyMass * gravity;
	PTM::VVector<Vec3d> assumptionForce;
	assumptionForce.resize(nContacts, Vec3d());

	for (int i = 0; i < nContacts; i++) {
		Vec3d contactPos = groundConst[i]->cSolid->GetPose() * groundConst[i]->contactPoint - totalBodyGravPos; //逆？
		//A.col(3 * i) = Vec6d(0, contactPos.z, -contactPos.y, 1, 0, 0);
		A_.at_element(1, 3 * i) = -contactPos.z;
		A_.at_element(2, 3 * i) = contactPos.y;
		A_.at_element(3, 3 * i) = 1;
		//A.col(3 * i + 1) = Vec6d(-contactPos.z, 0, contactPos.x, 0, 1, 0);
		A_.at_element(0, 3 * i + 1) = contactPos.z;
		A_.at_element(2, 3 * i + 1) = -contactPos.x;
		A_.at_element(4, 3 * i + 1) = 1;
		//A.col(3 * i + 2) = Vec6d(contactPos.y, -contactPos.x, 0, 0, 0, 1);
		A_.at_element(0, 3 * i + 2) = -contactPos.y;
		A_.at_element(1, 3 * i + 2) = contactPos.x;
		A_.at_element(5, 3 * i + 2) = 1;
		
		// 各接地点から重心方向への力の予測ベクトルを用意し、事前に差し引く
		assumptionForce[i] = Vec3d();// (massgrav.norm() / nContacts) * -contactPos.unit();
		massgrav += assumptionForce[i];
	}

	M_[3] = -massgrav.x;
	M_[4] = -massgrav.y;
	M_[5] = -massgrav.z;

	//A_ = U * D * Vt
	ublas::matrix<double> U, Vt;
	ublas::diagonal_matrix<double> D, Di, Di_;
	svd(A_, U, D, Vt);

	for (size_t i = 0; i < A_.size1(); i++) {
		for (size_t j = 0; j < A_.size2(); j++) {
			DSTR << A_.at_element(i, j) << " ";
		}
		DSTR << std::endl;
	}

	Di.resize(D.size2(), D.size1());
	for (size_t i = 0; i<(std::min(A_.size1(), A_.size2())); ++i) {
		// Tikhonov Regularization
		if (D(i, i) > 1e-10) {
			Di.at_element(i, i) = D(i, i) / (D(i, i)*D(i, i));
		}
		else {
			break; // 特異値が小さいときはランク落ちと判定
		}
		DSTR << Di.at_element(i, i) << " " << D(i, i) << std::endl;
	}

	for (size_t i = 0; i < U.size1(); i++) {
		for (size_t j = 0; j < U.size2(); j++) {
			DSTR << U.at_element(i, j) << " ";
		}
		DSTR << std::endl;
	}
	DSTR << std::endl;
	for (size_t i = 0; i < Vt.size1(); i++) {
		for (size_t j = 0; j < Vt.size2(); j++) {
			DSTR << Vt.at_element(i, j) << " ";
		}
		DSTR << std::endl;
	}

	// A_.pseudoinv = Vtt * D+ * Ut
	// --- 特異値->擬似逆行列&力
	vector_type      UtM = ublas::prod(ublas::trans(U), M_);
	vector_type    DiUtM = ublas::prod(Di, UtM);
	F_ = ublas::prod(ublas::trans(Vt), DiUtM);

	DSTR << "F_:(";
	for (int i = 0; i < (int)F_.size(); i++) {
		DSTR << F_[i] << " ";
	}
	DSTR << ")" << std::endl;

	for (int i = 0; i < nContacts; i++) {
		groundConst[i]->contactForce = Vec3d(F_[3 * i], F_[3 * i + 1], F_[3 * i + 2]) + assumptionForce[i];
	}

	Vec3d force = Vec3d();
	Vec3d point = Vec3d();
	t = CalcTorqueInChildren(root, point, force);
	for (int i = 0; i < nContacts; i++) {
		double penalty = dot(groundConst[i]->contactForce, groundConst[i]->cNormal);
		if (penalty < 0) {
			t += abs(penalty) * 1e5;
		}
	}
	return torqueWeight * t;
}

double FWStaticTorqueOptimizer::CalcStabilityCriterion() {
	//剛体の速度、角速度からバランスを評価
	double s = 0;
	for (int j = 0; j < phScene->NSolids(); ++j) {
		s += phScene->GetSolids()[j]->GetVelocity().norm();
		s += phScene->GetSolids()[j]->GetAngularVelocity().norm();
	}
	return stabilityWeight * s;
}

double FWStaticTorqueOptimizer::CenterOfGravity(PHIKActuatorIf* root, Vec3d& point) {
	double mass = 0;

	PHSolidIf* rootSolid;
	if (DCAST(PHIKBallActuatorIf, root)) {
		rootSolid = DCAST(PHIKBallActuatorIf, root)->GetJoint()->GetPlugSolid();
	}
	else {
		rootSolid = DCAST(PHIKHingeActuatorIf, root)->GetJoint()->GetPlugSolid();
	}
	DSTR << rootSolid->GetName() << rootSolid->GetPose() << std::endl;
	mass = rootSolid->GetMass();
	Vec3d thisCOG = rootSolid->GetPose() * rootSolid->GetCenterOfMass();
	int Nchilds = root->NChildActuators();
	Vec3d childCOG = Vec3d();
	double childMass;
	for (int i = 0; i < Nchilds; i++) {
		childMass = CenterOfGravity(root->GetChildActuator(i), childCOG);
		thisCOG = (childMass / (mass + childMass)) * childCOG + (mass / (mass + childMass)) * thisCOG;
		mass += childMass;
	}
	point = thisCOG;

	return mass;
}

double FWStaticTorqueOptimizer::CalcTorqueInChildren(PHIKActuatorIf* root, Vec3d& point, Vec3d& f) {
	// 対象関節のプラグ剛体にかかる力と力点(ワールド座標系)
	Vec3d force;
	Vec3d thisCOF;

	// 現在の剛体とその全子剛体におけるトルク評価値(返り値用)
	double torque = 0;

	// プラグとソケットの情報取得
	PHJointIf* joint;
	PHSolidIf* plugSolid;
	PHSolidIf* socketSolid;
	Posed plugPose;
	Posed socketPose;
	if (DCAST(PHIKBallActuatorIf, root)) {
		joint = DCAST(PHIKBallActuatorIf, root)->GetJoint();
		plugSolid = joint->GetPlugSolid();
		socketSolid = joint->GetSocketSolid();
		DCAST(PHIKBallActuatorIf, root)->GetJoint()->GetPlugPose(plugPose);
		DCAST(PHIKBallActuatorIf, root)->GetJoint()->GetSocketPose(socketPose);
	}
	else {
		joint = DCAST(PHIKHingeActuatorIf, root)->GetJoint();
		plugSolid = joint->GetPlugSolid();
		socketSolid = joint->GetSocketSolid();
		DCAST(PHIKHingeActuatorIf, root)->GetJoint()->GetPlugPose(plugPose);
		DCAST(PHIKHingeActuatorIf, root)->GetJoint()->GetSocketPose(socketPose);
	}
	DSTR << plugSolid->GetName() << plugSolid->GetPose() << std::endl;

	// プラグ剛体にはたらく重力と重心を取得(ワールド)
	force = plugSolid->GetMass() * phScene->GetGravity();
	thisCOF = plugSolid->GetPose() * plugSolid->GetCenterOfMass();

	// 再帰による子剛体内のトルク値取得及び力合成
	int Nchilds = root->NChildActuators();
	Vec3d childCOF = Vec3d();
	Vec3d forceInChildren;
	for (int i = 0; i < Nchilds; i++) {
		torque += CalcTorqueInChildren(root->GetChildActuator(i), childCOF, forceInChildren);
		double t = forceInChildren.norm() / (force.norm() + forceInChildren.norm());
		thisCOF = t * childCOF + (1 - t) * thisCOF;
		force += forceInChildren;
	}

	// 接地剛体の抗力の合成
	for (int i = 0; i < (int)groundConst.size(); i++) {
		if (plugSolid == groundConst[i]->cSolid) {
			DSTR << "match : " << plugSolid->GetName() << "&groundConst[" << i << "]" << std::endl;
			double t = groundConst[i]->contactForce.norm() / (force.norm() + groundConst[i]->contactForce.norm());
			thisCOF = t * (groundConst[i]->cSolid->GetPose() * groundConst[i]->contactPoint) + (1 - t) * thisCOF;
			force += groundConst[i]->contactForce;
		}
	}

	// 現アクチュエータのトルクを計算
	Vec3d jointPos = socketSolid->GetPose() * socketPose.Pos();
	Vec3d dir = jointPos - thisCOF;
	// ローカル化(上の段階ではまだワールド)
	Vec3d forceLocal = (socketSolid->GetPose() * socketPose).Ori().Inv() * force;
	dir = (socketSolid->GetPose() * socketPose).Ori().Inv() * dir;
	Vec3d moment = cross(dir, -forceLocal);

	// 関節特性抵抗の加算
	Vec3d resistanceTorque = Vec3d();
	Vec3d actualForce = Vec3d();
	if (DCAST(PHIKBallActuatorIf, root)) {
		actualForce = DCAST(PHIKBallActuatorIf, root)->GetJoint()->GetMotorForceN(0);
		if (DCAST(PHIKBallActuatorIf, root)->GetJoint()->NMotors() > 1) {
			PHHumanBallJointResistanceIf* resist = DCAST(PHHumanBallJointResistanceIf, DCAST(PHIKBallActuatorIf, root)->GetJoint()->GetMotors()[1]);
			if (resist) {
				resistanceTorque = resist->GetCurrentResistance();
			}
		}
	}
	else {
		moment = Vec3d(0, 0, moment.z);
		actualForce = Vec3d(0, 0, DCAST(PHIKHingeActuatorIf, root)->GetJoint()->GetMotorForceN(0));
		if (DCAST(PHIKHingeActuatorIf, root)->GetJoint()->NMotors() > 1) {
			PHHuman1DJointResistanceIf* resist = DCAST(PHHuman1DJointResistanceIf, DCAST(PHIKHingeActuatorIf, root)->GetJoint()->GetMotors()[1]);
			if (resist) {
				resistanceTorque = Vec3d(0, 0, resist->GetCurrentResistance());
			}
		}
	}
	DSTR << "dir:" << dir << " force:" << force << " (local):" << forceLocal << std::endl;
	DSTR << root->GetName() << " moment:" << moment << "(" << moment.norm() << ") actual:" << actualForce << "(" << actualForce.norm() << ") resistance:" << resistanceTorque << std::endl;
	moment -= resistanceTorque;

	// 関節ウェイトの取得
	double weight = 1.0;
	int NJointWeights = (int)jointWeights.size();
	for (int i = 0; i < NJointWeights; i++) {
		if (joint == jointWeights[i].joint) {
			weight = jointWeights[i].weight;
			break;
		}
	}

	// 評価値の加算
	torque += weight * (moment * moment);
	DSTR << "weight:" << weight << " value:" << weight * (moment * moment) << std::endl;

	// ワールド座標系でのCOFと力を参照渡しで返す(親のほうで使いまわすため)
	// もう少しいい方法があるなら変更したい
	point = thisCOF;
	f = force;

	// 現剛体以下のツリー内でのトルク評価値を返す
	return torque;
}

void FWStaticTorqueOptimizer::AddPositionConst(FWGroundConstraint* f) {
	groundConst.push_back(f);
}

FWGroundConstraint FWStaticTorqueOptimizer::GetGroundConst(int n) {
	if (n >= 0 && n < (int)groundConst.size()) {
		return *groundConst[n];
	}
	return FWGroundConstraint();
}

void FWStaticTorqueOptimizer::ClearGroundConst() {
	groundConst.clear();
}
void FWStaticTorqueOptimizer::AddPositionConst(FWUngroundedConstraint* f) {
	ungroundedConst.push_back(f);
}
FWUngroundedConstraint FWStaticTorqueOptimizer::GetUngroundConst(int n) {
	if (n >= 0 && n < (int)ungroundedConst.size()) {
		return *ungroundedConst[n];
	}
	return FWUngroundedConstraint();
}
void FWStaticTorqueOptimizer::ClearUngroundedConst() {
	ungroundedConst.clear();
}

}
