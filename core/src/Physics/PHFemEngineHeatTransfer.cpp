#include "PHFemEngine.h"
namespace Spr {;

struct CondVtx;					//	Conduction�@Vertex�̈Ӗ��H�`����Ⓒ�_�H	Companioned Vertex�H�̗��H �̂ǂ��炩�B
struct CondVtxs :public std::vector<CondVtx> {
	//PHFemMesh* pmesh;
	//
	PHFemMeshNew* pmesh;
	std::vector<int> vtx2Cond;
};
struct CondVtx {
	int vid;
	Vec3d pos;	//	x,y�͐ڐG�ʏ�ł̈ʒu�Az�͐ڐG�ʂ���̋���
	double area;
	double assign;
	CondVtx() :vid(-1), area(0), assign(0) {}
	struct Companion {
		int id;
		double area;
		Companion(int i, double a) :id(i), area(a) {}
	};
	std::vector<Companion> companions;
	struct Less {
		int axis;
		Less(int a) :axis(a) {}
		bool operator() (const CondVtx& a, const CondVtx& b) const { return a.pos[axis] < b.pos[axis]; }
	};
};
inline static double dist2D2(const Vec3d& a, const Vec3d& b) {
	return Square(a.x - b.x) + Square(a.y - b.y);
}

inline static double dist2Dxz(const Vec3d& a, const Vec3d& b) {
	return sqrt(Square(a.x - b.x) + Square(a.z - b.z));
}
//	condVtxs�̂Ȃ�����Afroms�ׂ̗̊��蓖�Ăɋ󂫂����钸�_��񋓂��Apos�ɋ߂����Ƀ\�[�g���ĕԂ��B
struct Dist2Less {
	Vec3d pos;
	CondVtxs& condVtxs;
	Dist2Less(Vec3d p, CondVtxs& c) :pos(p), condVtxs(c) {}
	bool operator () (int a, int b)const {
		return dist2D2(condVtxs[a].pos, pos) < dist2D2(condVtxs[b].pos, pos);
	}
};
double FindNearest(const Vec3d& pos, CondVtxs& condVtxs, int& found) {
	if (condVtxs.size() == 0) {
		found = -1;
		return DBL_MAX;
	}
	int minId = found;
	double minDist2;
	int cid;
	do {
		cid = minId;
		minDist2 = dist2D2(condVtxs[cid].pos, pos);		//������2�� 
		int vid = condVtxs[cid].vid;
		for (unsigned e = 0; e < condVtxs.pmesh->vertices[vid].edgeIDs.size(); ++e) {
			FemEdge& edge = condVtxs.pmesh->edges[condVtxs.pmesh->vertices[vid].edgeIDs[e]];
			int next = edge.vertexIDs[0] == vid ? edge.vertexIDs[1] : edge.vertexIDs[0];
			int cnext = condVtxs.vtx2Cond[next];			//edge pair
			if (cnext >= 0) {
				double d2 = dist2D2(condVtxs[cnext].pos, pos);
				if (d2 < minDist2) {
					minDist2 = d2;
					minId = cnext;
				}
			}
		}
	} while (cid != minId);
	found = cid;
	return sqrt(minDist2);
}
void DeleteNeighbor(int id, std::vector<int> &neighbor) {

	//id�ƈ�v����v�f���폜
	int delNUM = -1;	//�폜����v�f�͉��Ԗڂ�
	for (unsigned n = 0; n<neighbor.size(); ++n) {
		if (neighbor[n] == id) {
			delNUM = n;
			break;
		}
	}
	neighbor.erase(neighbor.begin() + delNUM);
}
void AddCompanion(CondVtxs& v1, int id1, CondVtxs& v2, int id2, double a) {
	assert(a > 0);
	v1[id1].assign += a;
	v2[id2].assign += a;
	assert(v1[id1].area - v1[id1].assign > -1e8);
	assert(v2[id2].area - v2[id2].assign > -1e8);
	unsigned i;
	for (i = 0; i<v1[id1].companions.size(); ++i) {
		if (v1[id1].companions[i].id == id2) {		// ���ł�companion�ɓo�^����Ă��钸�_����Add�̎��A?
			v1[id1].companions[i].area += a;
			break;
		}
	}
	if (i == v1[id1].companions.size()) {
		v1[id1].companions.push_back(CondVtx::Companion(id2, a));
	}
	for (i = 0; i<v2[id2].companions.size(); ++i) {
		if (v2[id2].companions[i].id == id1) {
			v2[id2].companions[i].area += a;
			break;
		}
	}
	if (i == v2[id2].companions.size()) {
		v2[id2].companions.push_back(CondVtx::Companion(id1, a));
	}
}

void RenewNeighbor(CondVtxs& condvtx, int id, std::vector<int> &neighbor) {
	//id�ƈ�v����v�f���폜
	DeleteNeighbor(id, neighbor);

	//id�Ɨאڂ���v�f�i�_�j��neighbor�ɒǉ�
	for (unsigned e = 0; e<condvtx.pmesh->vertices[condvtx[id].vid].edgeIDs.size(); ++e) {
		//�\�ʃG�b�W�łȂ���Έȉ������X�L�b�v
		if (condvtx.pmesh->edges[condvtx.pmesh->vertices[condvtx[id].vid].edgeIDs[e]] < (int)condvtx.pmesh->nSurfaceEdge)
			continue;
		FemEdge& edge = condvtx.pmesh->edges[condvtx.pmesh->vertices[condvtx[id].vid].edgeIDs[e]];	//id����_��edge������
		int next = edge.vertexIDs[0] == condvtx[id].vid ? edge.vertexIDs[1] : edge.vertexIDs[0];				//��������̓_�����߂�
		if (condvtx.pmesh->GetPHFemThermo()->GetVertexToofar(next) == false) { //�����ėאړ_�ɂ͉����Ȃ��_�ł͂Ȃ����
			int cnext = condvtx.vtx2Cond[next];		//condvtx�ɕϊ�
			if (cnext >= 0 && cnext<(int)condvtx.size())
			{	//���̓_���ڐG���ł���Ƃ�()(condvtx�̃T�C�Y���ł���Ƃ��F�T�C�Y���傫���ꍇ��condvtxs)
				if (condvtx[cnext].assign == 0) {		//�܂����蓖�Ă��Ă��Ȃ����
					int exist = 0;
					for (unsigned n = 0; n<neighbor.size(); ++n) {
						if (neighbor[n] == cnext) {
							exist = 1;	//���ł�neighbor�ɒl������Ƃ��͑�����Ȃ�
							break;
						}
					}
					if (exist == 0)
						neighbor.push_back(cnext);	//neighbor�ɒǉ�
				}
			}
		}
	}
}

void MakeVtxPair(CondVtxs(&condVtxs)[2], std::vector<int>(&neighbor)[2], int baseMesh, int current_id) {
	int companion_id;//������
	double dist = DBL_MAX;

	while (1) { //neighbor���m�̋����i�Ή���������_���m)�̋����������傫���Ȃ�����I��

		double overlapArea; //�d�Ȃ��Ă��镔���̖ʐ�
		companion_id = -1;//������

						  //neighbor�̒������_�Ɉ�ԋ߂��_��T���Acompanion_id�ɂ���
		double mini_length = DBL_MAX;	//edge�̒���
		for (unsigned n = 0; n<neighbor[1 - baseMesh].size(); ++n) {
			//neighbor[���葤�̃��b�V��][n]��condVtxs[����b�V��][current_id]�̋��������߂�
			double length = dist2D2(condVtxs[1 - baseMesh][neighbor[1 - baseMesh][n]].pos, condVtxs[baseMesh][current_id].pos);
			if (length < mini_length) {
				mini_length = length;
				companion_id = neighbor[1 - baseMesh][n];
			}
		}

		if (companion_id == -1) {//neighbor����̂Ƃ��̓��[�v�I���Bneighbor�ɗv�f�������Ă���Ƃ��Acompanion_id��-1�ɂȂ�Ȃ��B
			return;
		}

		//��������i����2�_�̋����������傫�������烋�[�v�I���j
		dist = dist2Dxz(condVtxs[baseMesh][current_id].pos, condVtxs[1 - baseMesh][companion_id].pos); //���݁A���ׂĂ���2���_�̋���
		if (dist > 0.1/*1.14499*/) {
			condVtxs[baseMesh].pmesh->GetPHFemThermo()->SetVertexToofar(condVtxs[baseMesh][current_id].vid, true);//�����������_���}�[�N
			DeleteNeighbor(current_id, neighbor[baseMesh]);//neighbor����v�f�폜
														   //condVtxs[1-baseMesh].pmesh->vertices[condVtxs[1-baseMesh][companion_id].vid].toofar = true;//�����������_���}�[�N
														   //DeleteNeighbor(companion_id,neighbor[1-baseMesh]);//neighbor����v�f�폜

														   //�܂�neighbor�ɗv�f�������Ă���̂ł���΁A�ċN�I�ɌĂяo���B
			if (neighbor[0].size() != 0 && neighbor[1].size() != 0) {
				//	DSTR << "0�T�C�Y�F" << neighbor[0].size() << endl;
				//	for(unsigned n=0; n<neighbor[0].size(); n++){
				//		DSTR << "0�c��F" << condVtxs[0][neighbor[0][n]].vid << endl;
				//	}
				//	DSTR << "1�T�C�Y�F" << neighbor[1].size() << endl;
				//	for(unsigned n=0; n<neighbor[1].size(); n++){
				//		DSTR << "1�c��F" << condVtxs[1][neighbor[1][n]].vid << endl;
				//	}
				MakeVtxPair(condVtxs, neighbor, 1 - baseMesh, neighbor[1 - baseMesh][0]);
			}
			return;
		}

		if (condVtxs[baseMesh][current_id].area - condVtxs[baseMesh][current_id].assign > condVtxs[1 - baseMesh][companion_id].area - condVtxs[1 - baseMesh][companion_id].assign) {
			//��_�̖ʐρ�����̖ʐ�
			overlapArea = condVtxs[1 - baseMesh][companion_id].area - condVtxs[1 - baseMesh][companion_id].assign; //���葤�i���������j�̖ʐς�overlapArea
			AddCompanion(condVtxs[baseMesh], current_id, condVtxs[1 - baseMesh], companion_id, overlapArea);
			condVtxs[1 - baseMesh].pmesh->GetPHFemThermo()->SetVertexBeCondVtxs(condVtxs[1 - baseMesh][companion_id].vid, true);	//�Ή��t���I������_��true

																																	//���葤�̖ʐς�S�Ċ��蓖�Ă��̂ŁA�Ή��_���폜���A���̗אړ_��neighbor�ɒǉ�
			RenewNeighbor(condVtxs[1 - baseMesh], companion_id, neighbor[1 - baseMesh]);

			//��_�̕������蓖�Ă���ʐς������̂ŁA��_�̎c��̖ʐς����蓖�Ă邽�߁A�����neighbor���炳�����ɍs���B
		}
		else {	//��_�̖ʐρ�=����̖ʐ�
				//��_�i���������j�̖ʐς�overlapArea
			overlapArea = condVtxs[baseMesh][current_id].area - condVtxs[baseMesh][current_id].assign;
			AddCompanion(condVtxs[baseMesh], current_id, condVtxs[1 - baseMesh], companion_id, overlapArea);
			condVtxs[baseMesh].pmesh->GetPHFemThermo()->SetVertexBeCondVtxs(condVtxs[baseMesh][current_id].vid, true);	//�Ή��t���I������_��true

																														//��_�̖ʐς�S�Ċ��蓖�Ă��̂ŁA�Ή��_���폜���A���̗אړ_��neighbor�ɒǉ�
			RenewNeighbor(condVtxs[baseMesh], current_id, neighbor[baseMesh]);

			//��_�𑊎葤�Ɉڂ�
			baseMesh = 1 - baseMesh;
			current_id = companion_id;	//��_�𑊎葤�Ɉڂ�
		}
	}
}


void PHFemEngine::ThermalTransfer() {
	for (int i = 0; i < (int) meshPairs.size(); ++i) {
		HeatTrans(meshPairs[i]);
	}
}
void PHFemEngine::HeatTrans(PHFemMeshPair* mp) {
	PHSolid* phs0 = mp->mesh[0]->GetPHSolid()->Cast();
	PHSolid* phs1 = mp->mesh[1]->GetPHSolid()->Cast();
	PHFemMeshNew* fmesh0 = mp->mesh[0];
	PHFemMeshNew* fmesh1 = mp->mesh[1];

	/*heattrans�֐����p------------------------------------------------------------------------��������*/
	PHSolid* solids[2];
	solids[0] = phs0;
	solids[1] = phs1;

	PHFemMeshNew* fmesh[2];
	fmesh[0] = fmesh0;
	fmesh[1] = fmesh1;
	PHScene* scene = solids[0]->GetScene()->Cast();
	//	�ڐG�y�A�������āA������Ȃ画�肷��B
	bool bSwap;
	PHSolidPairForLCP* pair = scene->GetSolidPair(solids[0]->Cast(), solids[1]->Cast(), bSwap)->Cast();
	PHShapePairForLCP* sp = pair->GetShapePair(0, 0)->Cast();			/// 1st shape of wvery object is used as shape pair (= heatrans pair) 

	if (sp->lastContactCount != (scene->GetCount() - 1)) {		//���ڐG���Ă��Ȃ���΁B�ڐG	�͑����Ōv�Z�BCDDetectorImp::ContactDetect()��State�̎d�l�F�Ō�ڐG���̃J�E���g��ێ��̂��� 
																//	���ڐG�Ȃ̂ŁAGJK���Ă�
		sp->shapePoseW[0] = solids[0]->GetPose() * solids[0]->GetShapePose(0);
		sp->shapePoseW[1] = solids[1]->GetPose() * solids[1]->GetShapePose(0);
		if (bSwap) std::swap(sp->shapePoseW[0], sp->shapePoseW[1]);
		Vec3d sep;
		double dist = FindClosestPoints(sp->shape[0], sp->shape[1], sp->shapePoseW[0], sp->shapePoseW[1], sep, sp->closestPoint[0], sp->closestPoint[1]);
		if (dist < 1e-10) {
			//	���Ȃ�߂��̂ŁA�@�����������̂ŁA�x���������Ă����B
			DSTR << "�Q���̂����ɋ߂����A�ڐG���͂��Ă��Ȃ������ȏ��";
			DSTR << " dist : " << dist << std::endl;
			if (dist < 1e-14) {
				DSTR << "����" << std::endl;
			}
		}
		sp->depth = -dist;
		sp->normal = (sp->shapePoseW[1] * sp->closestPoint[1] - sp->shapePoseW[0] * sp->closestPoint[0]);	//��̓`�M�̌v�Z�K�v�B�ʁ��ʂ̌����F�@������`�M�v�Z
		sp->normal.unitize();
	}

	//	����:dist
	//	�������߂���Γ`�M�̏���
	/*	�M�`�B�� �� [W/(m^2 K)] ��p����ƁA���E��� q = ��(T-Tc) (T:�ړ_���x Tc:���̗͂��̓��̉��x)
	�Q���̂̐ڐG���ƁAT1-��1->Tc-��2->T2 �ƂȂ�ƍl������B
	q = ��1(T1-Tc) = ��2(Tc-T2) ��� (��1+��2)Tc = ��1T1 + ��2T2
\	Tc = (��1T1 + ��2T2)/(��1+��2)
	q = ��1(T1-(��1T1 + ��2T2)/(��1+��2)) = ��1T1 - ��1(��1T1 + ��2T2)/(��1+��2)
	= (��1��2T1 - ��1��2T2)/(��1+��2) = ��'(T1-T2)  ��' = ��1��2/(��1+��2)	*/
	/*	q��Q�ɂ��Ă̍l�@
	q�͒P�ʖʐς�����Ȃ̂ŁA���_�Ԃ̔M�̈ړ���Q�ɒ����ɂ́A���_����\����ʐς��|����K�v������B
	�{���́A�O�p�`�̏d�Ȃ�ƌ`��֐����狁�߂�ׂ����́B[

	�������A�d�Ȃ��͖��X�e�b�v�ς��̂ŁA���̌v�Z�͑�ρB�ȗ������l����B
	���_�͒��_���܂ގO�p�`�ɐ��͂����B�O�p�`�̏d�Ȃ���A���_�̋����̈Ӗ����傫���B
	�������߂����̂����蓖�ĂĂ������A��Ŕ�ђn���o�Ă͂����Ȃ��B
	�����ŁA�P�_���珉�߂ď��X�Ɋ��蓖�ė̈��傫�����čs���B����ł���͋N���Ă���ђn�͂łȂ��B

	���_�̖ʐς́A���_���܂ގO�p�`�B�̖ʐς̘a��1/3�B
	*/
	const double isoLen = 0.005;	//	0.1�ɂ���ƁA���]����A�����ʂ����M�����B0.01�ɂ���ƁA���Ζʂ͉��M����Ȃ����A���Ζʂɋ߂��G�b�W�����M�����
	const double isoLen2 = 0.07;	//	condVtxs�y�A������ȏ㗣�ꂽ��A�Ή����Ă��Ȃ����Ƃɂ���W��
	if (sp->depth > -isoLen) {		//	�Փ˂̐[����
		CondVtxs condVtxs[2];
		condVtxs[0].pmesh = fmesh[bSwap ? 1 : 0]->Cast();
		condVtxs[1].pmesh = fmesh[bSwap ? 0 : 1]->Cast();
		//	�������߂����_��񋓁B���łɖ@���ɐ����ȕ��ʏ�ł̍��W�����߂Ă����B
		Matrix3d coords;
		if (std::abs(sp->normal.x) < std::abs(sp->normal.y)) coords = Matrix3d::Rot(sp->normal, Vec3d(1, 0, 0), 'z');		//	���̊Ԃ̋��L�ʏ�ł�x-y���ʂɕ��̂̏㉺���̂̒��_��u�������邽�߂̍��W�ϊ������邽�߂ɁAz���𐂒����ʂ�   //�ˉe�����H�H
		else coords = Matrix3d::Rot(sp->normal, Vec3d(0, 1, 0), 'z');
		Matrix3d coords_inv = coords.inv();
		Vec3d normalL[2];

		for (int i = 0; i<2; ++i) {
			normalL[i] = sp->shapePoseW[i].Ori().Inv() * sp->normal * (i == 0 ? 1 : -1);		//����̈Ӗ�:? 1,-1�̏����K�v�Ȃ̂��H			//world���W����̖@������A���[�J���̖@���̌������v�Z: W���W�ϊ� *  normalL(ocal) =  normalW(orld)
																								//DSTR << std::endl << "NL:" << normalL[i]<< std::endl;
			for (unsigned v = 0; v < condVtxs[i].pmesh->surfaceVertices.size(); ++v) {
				double vd = (sp->closestPoint[i] - condVtxs[i].pmesh->vertices[condVtxs[i].pmesh->surfaceVertices[v]].pos) * normalL[i];
				vd -= sp->depth;
				if (vd < isoLen) {
					CondVtx c;
					c.vid = condVtxs[i].pmesh->surfaceVertices[v];
					c.pos = coords_inv * (sp->shapePoseW[i] * condVtxs[i].pmesh->vertices[c.vid].pos);
					c.pos.z = vd + (sp->depth / 2);	//	���ʂ���̋����ɂ��Ă����B
													// sp->normal�͂ǂ��炩�̕��̂���̖@���Ȃ̂ŁA����̌�����condvtxs��bswap�ɂ���āH�������肤��B
													// if(bSwap == true)	condVtxs[0] == fmesh[1]		// sp->normal�@���Ɣ��Ό����̂�
													// else(bSwap == false)	condVtxs[0] == fmesh[0]		// sp->normal�@���Ɠ�������

					double judgeN = normalL[i] *
						condVtxs[i].pmesh->GetPHFemThermo()->GetVertexNormal(condVtxs[i].pmesh->surfaceVertices[v]);

					if (judgeN > 0.0) {		// <= �ȑO�̕�������
						condVtxs[i].push_back(c);		//.�@l.828�ł���Ă���condVtxs�͓����H�BcondVtxs�̃����o�ϐ���ݒ肵��condVtx�����B
					}
				}
			}
		}
		for (unsigned i = 0; i<2; i++) {
			if (condVtxs[i].size() == 0) {
				DSTR << "00 Can not find companion vertex on object " << i << std::endl;
			}
		}
		/*heattrans�֐����p--------------------------------------------------------------�����܂�*/

		const double isoLen3 = 0.003;		//:BoundingBox�̎��͉�[m]�܂Ńy�A�T���͈͂Ƃ��邩
											//	Less�����(�ڐG�ʏ��x,z����)�\�[�g
		Vec2d bboxMin, bboxMax;
		for (int axis = 0; axis<2; ++axis) {
			for (int i = 0; i<2; ++i) {
				std::sort(condVtxs[i].begin(), condVtxs[i].end(), CondVtx::Less(axis)); //x(y)���ɂ��ė����̂̒��_���\�[�g
			}
			//	�����ƂɁA2����AABB�̂��߂̍ŏ��l/�ő�l�����߂�
			//	boundingbox�`�F�b�N �d�Ȃ�Ȃ������͎̂Ă�
			//	�����ƂɁA���ʔ͈͂̍��W������B�ŏ�����B
			bboxMin[axis] = condVtxs[0].size() ? condVtxs[0].front().pos[axis] : DBL_MIN;                           //condVtxs[0]�̃T�C�Y������΁Afront().pos����
			bboxMin[axis] = std::max(bboxMin[axis], (condVtxs[1].size() ? condVtxs[1].front().pos[axis] : DBL_MIN));  //condVtxs[1]�̃T�C�Y������΁Afront().pos���� ���Ɣ�r���đ傫���ق������i�d�Ȃ��Ă��镔���̍ŏ��l�j
			bboxMin[axis] -= isoLen3; //<-isoLen,	
			for (int i = 0; i<2; ++i) {		//	condVtxs�̂ǂ�����AisoLen3���O���̓_�͌�₩�珜�O����
				CondVtx tmp;
				tmp.pos[axis] = bboxMin[axis];
				CondVtxs::iterator it = std::lower_bound(condVtxs[i].begin(), condVtxs[i].end(), tmp, CondVtx::Less(axis));
				condVtxs[i].erase(condVtxs[i].begin(), it);
			}
			bboxMax[axis] = condVtxs[0].size() ? condVtxs[0].back().pos[axis] : DBL_MAX;
			bboxMax[axis] = std::min(bboxMax[axis], (condVtxs[1].size() ? condVtxs[1].back().pos[axis] : DBL_MAX));
			bboxMax[axis] += isoLen3;
			for (int i = 0; i<2; ++i) {
				CondVtx tmp;
				tmp.pos[axis] = bboxMax[axis];
				CondVtxs::iterator it = std::upper_bound(condVtxs[i].begin(), condVtxs[i].end(), tmp, CondVtx::Less(axis));		//	Less�ŗǂ��̂�
				condVtxs[i].erase(it, condVtxs[i].end());
			}
		}

		//�Ή����钸�_�̂Ȃ����_�̍폜
		for (int i = 0; i<2; ++i) {
			condVtxs[i].vtx2Cond.resize(condVtxs[i].pmesh->vertices.size(), -1);
			for (unsigned j = 0; j<condVtxs[i].size(); ++j) {
				condVtxs[i].vtx2Cond[condVtxs[i][j].vid] = j;
			}
		}
		//	�Ή����钸�_��������Ȃ����_���A�폜�̂��߂Ƀ}�[�N�B
		std::vector<int> eraseVtxs[2];
		for (int i = 0; i<2; ++i) {
			int from = 0;
			for (unsigned j = 0; j<condVtxs[i].size(); ++j) {
				int found = from;
				double dist = FindNearest(condVtxs[i][j].pos, condVtxs[1 - i], found);	// condVtxs[i][j].pos��condVtxs[1-i](sp�̃y�A)�̓��A��ԒZ�����isoLen��蒷��������A�M�`�����Ȃ��B���ǁA�ŏ��ɁAisoLen�Ŕ��肵�Ă���y�A����Ă���񂾂���A���̂��ƂɁAdist���v�Z����K�v�͂���̂��낤���HcondVtxs�����X�e�b�v�X�V����Ȃ��̂Ȃ�A�K�v����
				if (dist > isoLen2) {	//	���ʋ�����isoLen�ȏ�̒��_�͍폜�̂��߃��X�gout
					eraseVtxs[i].push_back(j);
				}
				else {
					from = found;
				}
			}
		}
		//	�}�[�N�������_���폜
		for (int i = 0; i<2; ++i) {
			std::sort(eraseVtxs[i].begin(), eraseVtxs[i].end());
			for (int j = (int)eraseVtxs[i].size() - 1; j>0; --j) {
				condVtxs[i].erase(condVtxs[i].begin() + eraseVtxs[i][j]);
			}
			if (condVtxs[i].size() == 0) {
				return;
			}
		}

		//���_�̒S������ʐς̌v�Z(���ۂɂ͌v�Z���Ă���̂ł͂Ȃ��Ăяo���đ�����Ă邾��)��Ɠ�����
		for (int i = 0; i<2; ++i) {
			for (unsigned j = 0; j<condVtxs[i].size(); ++j) {
				condVtxs[i][j].area = condVtxs[i].pmesh->GetPHFemThermo()->GetVertexArea(condVtxs[i][j].vid);
			}
		}
		//2���̂��d�Ȃ��Ă��镔���̒��S��T��
		double xCenter = 0.5*(bboxMin.x + bboxMax.x); //�d�Ȃ��Ă��镔���̒��S
		int centerVtx[2] = { -1, -1 };	//������(-1,-1)�����Ƃ� //condVtxs�őO���牽�Ԗڂ�
		for (int i = 0; i<2; ++i) {
			CondVtx tmp;
			tmp.pos[1] = 0.5*(bboxMin.y + bboxMax.y);
			CondVtxs::iterator it = std::lower_bound(condVtxs[i].begin(), condVtxs[i].end(), tmp, CondVtx::Less(1)); //condVtxs[i]�ibegin~end�Łj�w�肵���l�itmp)�ȏ�̒l���ŏ��Ɍ����ʒu��Ԃ��B
			int cit = (int)(it - condVtxs[i].begin()); //tmp���傫���l(�v�f��������)���o���ꏊ-�ŏ��̗v�f�̏ꏊ
			double minDistX = DBL_MAX;	//�������idouble�̏���l�j
			for (int y = 0; y<5; ++y) {
				if (cit - y >= 0 && cit - y < (int)condVtxs[i].size()) {
					double dist = std::abs(condVtxs[i][cit - y].pos.x - xCenter);
					if (dist < minDistX) {
						centerVtx[i] = cit - y;
						minDistX = dist;
					}
				}
				if (cit + y < (int)condVtxs[i].size()) {
					double dist = std::abs(condVtxs[i][cit + y].pos.x - xCenter);
					if (dist < minDistX) {
						centerVtx[i] = cit + y;
						minDistX = dist;
					}
				}
			}
			assert(centerVtx[i] >= 0); //�_���`�F�b�N centerVtx��0���傫���i0��菬�����Ɛf�f���b�Z�[�W�j
		}

		//	centerVtx[i]�ƈ�ԋ߂����_��T��
		int baseMesh = 0; //0or1�A���b�V���̑Ή���T�����A���b�V���O�ƂP�̂ǂ������ɒT���Ă��邩
		int current_id = centerVtx[0]; //��̓_ID�B�����̑Ή��_��T���Ă���B
		int companion_id = centerVtx[1];

		// baseMesh(=centerVtx[0])�����centerVtx[1]��faces[0]�����������B�Ή�������companion_id��Ԃ��B

		/*//9.14 while���őΉ��Â���悤�ɑS�_�Ή��Â���悤�Ƀ��[�v������
		���蓖�Ă����_�̐� = condVtxs�̐��ɂȂ�����A�S�_�Ή������Ƃ������Ƃ�loop����o��B
		2013.9.20
		�אړ_��T���ɍs�������˗אړ_�̖ʐς��S�Ă����ς��������Ƃ��̏����������Ă��Ȃ��B
		*/
		/*2013.9.20
		TriInOutJudge�̑�O������face��n���̂����A�\��face�����m�F�����ɓn���Ă����̂Ńo�O���o���B
		TriInoutJudge�ŕԂ��Ă����ϐ��͒��_ID���������A�Ԃ��ׂ��͂����Vtx2cond�ŕϊ������������B
		���݂͏C���ς�
		*/
		/*
		2013.10.8
		�I���i���[�v�j������coundVtxs(�ڐG���Ă���_)�̐��ƑΉ��t�����I������i�ʐς��O�ɂȂ����j�_�̐����r���A���ꂪ�������������ꍇ�ɑS�_�Ή��ɂ���B
		�Ή��t�����I������Ƃ��ɁAcountMesh[0or1]���J�E���g�A�b�v����B

		2013.10.22
		�I�������̕ύX�B�ːڐG�ʐς̂���������Ή��t������ڐG�I���B
		���̂���counMesh�̃J�E���g�A�b�v�͍폜�B
		neighbor�ϐ���ǉ����A�������玟�̑Ή���I�Ԃ悤�ɂ���BAddneighbor�֐��ǉ��B

		2014
		�I�������͒��_�y�A�̐��������ɂ���		*/

		//	��������Ή����L���Ă���
		std::vector<int> neighbor[2];		//���_�̒T�����
		neighbor[0].push_back(current_id);
		neighbor[1].push_back(companion_id);

		//�Ή��_�����
		MakeVtxPair(condVtxs, neighbor, baseMesh, current_id);
		double areaSUM[2] = { 0.0, 0.0 };


		/// 2���̂̊ԂŔM�`�B���E�������p�ɂ��M�`�B�v�Z���s��
		for (unsigned i = 0; i < condVtxs[0].size(); i++) {
			//	�Ή�����ߓ_(companions[j])�̉��x���g���ĔM�`�B�̌v�Z���s��
			double areasum = 0.0;
			for (unsigned j = 0; j < condVtxs[0][i].companions.size(); j++) {
				// �M�`�B�̃y�A�ɂȂ��Ă���ғ��m���A�����F�ŕ`��A�ǂ̐F�ŕ`�悷�邩�A�����_���Ō���H
				//i=0����A�P���`�F�b�N���Ă����B�d�����Ă���ꍇ�ɂ́A�F���㏑������Ă��܂��̂ŁB
				condVtxs[0].pmesh->GetPHFemThermo()->SetVertexHeatTransRatio(condVtxs[0][i].vid, mp->heatTransferRatio);	// �t���C�p��-��C�Ԃœ`�M���Ȃ��F���̊ԓ`�B���̂ݓK�p�����ׂ������A�Ƃ肠�����B
																													//>		isoLen3==0�̎��AjudgeN����Ɠ����Ă���_�̐��͓����Ȃ̂ɁA�M�`�B����Ă��Ȃ��_������悤�Ɍ�����B
				double dqdt = mp->heatTransferRatio * (condVtxs[0].pmesh->GetPHFemThermo()->GetVertexTemp(condVtxs[0][i].vid)			//	0,1�ǂ��炪�ǂ��炩�ς��\�����肾���A����ł����̂��B
					- condVtxs[1].pmesh->GetPHFemThermo()->GetVertexTemp(condVtxs[1][condVtxs[0][i].companions[j].id].vid)) * condVtxs[0][i].companions[j].area;
				//	�M�`�B�Ώے��_�ł́A�M���˂��v�Z���Ȃ�
				//DSTR << condVtxs[0].pmesh->vertices[condVtxs[0][i].vid].beRadiantHeat << "," <<
				//	condVtxs[1].pmesh->vertices[condVtxs[1][condVtxs[0][i].companions[j].id].vid].beRadiantHeat <<std::endl;
				condVtxs[0].pmesh->GetPHFemThermo()->SetVertexBeRadiantHeat(condVtxs[0][i].vid, false);
				condVtxs[1].pmesh->GetPHFemThermo()->SetVertexBeRadiantHeat(condVtxs[1][condVtxs[0][i].companions[j].id].vid, false);

				// condvtx[0]��Vecf ��dqdt �𑫂�
				// condVtx[1]��companion.id�Ԗڂ�Vecf�������
				condVtxs[0].pmesh->GetPHFemThermo()->AddvecFAll(condVtxs[0][i].vid, -dqdt);//-
				condVtxs[1].pmesh->GetPHFemThermo()->AddvecFAll(condVtxs[1][condVtxs[0][i].companions[j].id].vid, dqdt);//+
			}
		}
	}
}

}
