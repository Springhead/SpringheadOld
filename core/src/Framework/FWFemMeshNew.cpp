/*
 *  Copyright (c) 2003-2012, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */

#if (_MSC_VER >= 1700)
#include <functional>
#endif

#include <Graphics/GRMesh.h>
#include <Foundation/UTLoadHandler.h>
#include "FWFemMeshNew.h"
#include "FWSprTetgen.h"

#ifdef USE_HDRSTOP
#pragma hdrstop
#endif

#ifdef _DEBUG
# define PDEBUG(x)	x
#else
# define PDEBUG(x)
#endif

namespace Spr{;

FWFemMeshNewDesc::FWFemMeshNewDesc(){
	Init();
}
void FWFemMeshNewDesc::Init(){
//	meshRoughness = "pq2.1a0.000005";//phStick (�l�ʑ�200��)
	kogetex = 5;
}

FWFemMeshNew::FWFemMeshNew(const FWFemMeshNewDesc& d){
	grFemMesh = NULL;
	// p: piecewise linear comlex, q:2.1�����l�ʑ̘̂c��(1�ȏ�`�H�ȉ��j�Aa:�e��
	//meshRoughness = "pq3.1a0.5";//phSphere 
	//meshRoughness = "pq2.1a0.1";//phRec 
	//meshRoughness = "pq2.1a1.15";//phCube phBoardmini phPipemini
	SetDesc(&d);
	texture_mode = 1;		//	�e�N�X�`���\���̏����l�F���x
	drawflag=true;
}

size_t FWFemMeshNew::NChildObject() const{
	return FWObject::NChildObject() + (grFemMesh ? 1 : 0) + (phFemMesh ? 1 : 0);
}

ObjectIf* FWFemMeshNew::GetChildObject(size_t pos){
	if(pos < FWObject::NChildObject()){
		return FWObject::GetChildObject(pos);
	}else{
		pos -= FWObject::NChildObject();
	}	
	if(grFemMesh){
		if (pos == 0) return grFemMesh->Cast();
		else pos --;
	}
	if(phFemMesh){
		if (pos == 0) return phFemMesh->Cast();
		else pos --;
	}
	return NULL;
}

bool FWFemMeshNew::AddChildObject(ObjectIf* o){
	PHFemMeshNew* pm = o->Cast();
	if (pm){
		phFemMesh = pm;
		phFemMesh->SetPHSolid(GetPHSolid());
		return true;
	}
	GRMesh* mesh = o->Cast();
	if (mesh){
		grFemMesh = mesh;
		return true;
	}
	return FWObject::AddChildObject(o);
}

void FWFemMeshNew::Loaded(UTLoadContext*){
	if(grFemMesh){
		if(!phFemMesh){
			// phFemMesh��NULL�̏ꍇ�A�V���ɐ�������B
			// �v�Z���W���[���͍���Ȃ��̂ŕʂɍ��K�v������i�������j�B
			phFemMesh = DBG_NEW PHFemMeshNew();
			// PHFemEngine�ɒǉ��o�^	
			if(GetPHSolid() && GetPHSolid()->GetScene()){
				GetPHSolid()->GetScene()->AddChildObject(phFemMesh->Cast());
				phFemMesh->SetPHSolid(GetPHSolid());
			}
			CreatePHFemMeshFromGRMesh();		
		}else if(phFemMesh->vertices.size() == 0){
			// phFemMesh�̒��_����̏ꍇ
			// tetgen�ɂ�郁�b�V���̐���
			CreatePHFemMeshFromGRMesh();
		}
	}

	if (grFrame && grFemMesh){
		grFrame->DelChildObject(grFemMesh->Cast());
		CreateGRFromPH();
		grFrame->AddChildObject(grFemMesh->Cast());
	}

	phFemMesh->Init();
}

bool FWFemMeshNew::CreatePHFemMeshFromGRMesh(){
	//	�Ăяo���ꂽ���_��grFemMesh �ɃO���t�B�N�X�̃��b�V���������Ă���B
	//	grFemMesh���l�ʑ̃��b�V���ɕϊ����āAphFemMesh������B
	
	//TetGen�Ŏl�ʑ̃��b�V����
	Vec3d* vtxsOut=NULL;
	int* tetsOut=NULL;
	int nVtxsOut=0, nTetsOut=0;
	std::vector<Vec3d> vtxsIn;
	for(unsigned i = 0; i < grFemMesh->vertices.size(); ++i) vtxsIn.push_back(grFemMesh->vertices[i]);
	// swithes q+(���a/�ŒZ��) (e.g. = q1.0~2.0) a �ő�̑̐� 
	sprTetgen(nVtxsOut, vtxsOut, nTetsOut, tetsOut, (int)grFemMesh->vertices.size(), &vtxsIn[0], (int)grFemMesh->faces.size(), &grFemMesh->faces[0], (char*)meshRoughness.c_str());
	
	//	phFemMesh�p�̃f�B�X�N���v�^pmd�ɒl�����Ă���
	PHFemMeshNewDesc pmd;
	for(int i=0; i < nVtxsOut; i++){
		pmd.vertices.push_back(vtxsOut[i]);
	} 
	pmd.tets.assign(tetsOut, tetsOut + nTetsOut*4);
	pmd.spheric = (bool)spheric;
	phFemMesh->SetDesc(&pmd);

	return true;
}

struct FaceMap{
	FaceMap(){
		vtxs[0] = vtxs[1] = vtxs[2] = -1;
		face = -1;
	}
	int vtxs[3];
	int& operator [](int i) {return vtxs[i]; }
	int face;
};

void FWFemMeshNew::CreateGRFromPH(){
	// 3D�e�N�X�`�����g����悤�ɂ��邽�߂ɁAgrFemMesh���č\�z����
	// 3D�e�N�X�`�����g��Ȃ��ꍇ�͕K�v�Ȃ�

	//	���_�̑Ή��\��p��
	std::vector<int> vtxMap;
	vtxMap.resize(phFemMesh->vertices.size(), -1);
	for(unsigned i=0; i<phFemMesh->surfaceVertices.size(); ++i){
		vtxMap[phFemMesh->surfaceVertices[i]] = i;
	}
	GRMeshDesc gmd;	//	�V����GRMesh�̃f�X�N���v�^
	//	�\�ʂ̒��_��ݒ�
	for(unsigned i=0; i< phFemMesh->surfaceVertices.size(); ++i) 
		gmd.vertices.push_back(phFemMesh->vertices[ phFemMesh->surfaceVertices[i] ].pos);
	//	�\�ʂ̎O�p�`��ݒ�
	for(unsigned i=0; i< phFemMesh->nSurfaceFace; ++i) {
		GRMeshFace f;
		f.nVertices = 3;
		for(int j=0; j<3; ++j){
			f.indices[j] = vtxMap[phFemMesh->faces[i].vertexIDs[j]];
		}
		gmd.faces.push_back(f);
	}
	//	phFemMesh�̎O�p�`��grFemMesh�̎O�p�`�̑Ή��\������	�d�Ȃ��Ă���ʐς��ő�̂��̂��Ή������
	//	�܂��A�@�����߂����̂�T���A��1�Ɩ�2��̒��_�̋������߂����̂Ɍ���A�d�Ȃ��Ă���ʐς����߂�B
	std::vector<Vec3f> pnormals(gmd.faces.size());
	for(unsigned pf=0; pf<gmd.faces.size(); ++pf){
		assert(gmd.faces[pf].nVertices == 3);
		pnormals[pf] = ((gmd.vertices[gmd.faces[pf].indices[2]] - gmd.vertices[gmd.faces[pf].indices[0]]) %
		(gmd.vertices[gmd.faces[pf].indices[1]] - gmd.vertices[gmd.faces[pf].indices[0]])).unit();
	}
	std::vector<Vec3f> gnormals(grFemMesh->faces.size());
	struct FaceWall{
		Vec3f wall[4];
	};
	std::vector<FaceWall> gWalls(gnormals.size());
	for(unsigned gf=0; gf<gnormals.size(); ++gf){
		gnormals[gf] = ((grFemMesh->vertices[grFemMesh->faces[gf].indices[2]] - grFemMesh->vertices[grFemMesh->faces[gf].indices[0]]) %
			(grFemMesh->vertices[grFemMesh->faces[gf].indices[1]] - grFemMesh->vertices[grFemMesh->faces[gf].indices[0]])).unit();
		int nv = grFemMesh->faces[gf].nVertices;
		for(int i=0; i<nv; ++i){
			gWalls[gf].wall[i] = ((grFemMesh->vertices[grFemMesh->faces[gf].indices[(i+1)%nv]] - grFemMesh->vertices[grFemMesh->faces[gf].indices[i]]) % gnormals[gf]).unit();
		}
	}
	std::vector< FaceMap > pFaceMap(pnormals.size());
	for(unsigned pf=0; pf<pnormals.size(); ++pf){
		//	�����̕���(pf)�Ɠ��ꕽ�ʂɍڂ��Ă���O���t�B�N�X�̕��ʂ��
		std::vector<int> gfCands;
		for(unsigned gf=0; gf<gnormals.size(); ++gf){
			if (pnormals[pf] * gnormals[gf] > 0.999){	//	�@���������̂͂���
				int pv;
				for(pv=0; pv<3; ++pv){
					double d = gnormals[gf] * (gmd.vertices[gmd.faces[pf].indices[pv]] - grFemMesh->vertices[grFemMesh->faces[gf].indices[0]]);
					if (d*d > 1e-8) break;	//	���������ꂷ���Ă���̂͂���
				}
				if (pv==3) gfCands.push_back(gf);
			}
		}
		//	pf�̊e���_�ɑΉ�����gf��������
		std::vector<int> gfForPv[3];
		for(unsigned pv=0; pv<3; ++pv){
			for(unsigned i=0; i<gfCands.size(); ++i){
				int gf = gfCands[i];
				int gv;
				for(gv=0; gv<grFemMesh->faces[gf].nVertices; ++gv){
					double d = gWalls[gf].wall[gv] * (gmd.vertices[gmd.faces[pf].indices[pv]] - grFemMesh->vertices[grFemMesh->faces[gf].indices[gv]]);
					if (d < -1e-6) break;
				}
				if (gv == grFemMesh->faces[gf].nVertices){
					gfForPv[pv].push_back(gf);
				}
			}
		}
		//	�R�������_���A�P�̃O���t�B�N�X�O�p�`�����L����ꍇ�A���L������̂�D��
		std::vector< std::pair<int, int> > votes;
		for(int i=0; i<3; ++i){
			for(unsigned j=0; j<gfForPv[i].size(); ++j){
				unsigned k;
				for(k=0; k<votes.size(); ++k){
					if (votes[k].second == gfForPv[i][j]){
						votes[k].first ++;
						break;
					}
				}
				if (k==votes.size()) votes.push_back(std::make_pair(1, gfForPv[i][j]));
			}
		}
		std::sort(votes.begin(), votes.end(), std::greater<std::pair<int, int> >());
		for(int i=0; i<3; ++i){
			for(unsigned j=0; j<votes.size(); ++j){
				for(unsigned k=0; k<gfForPv[i].size(); ++k){
					if (votes[j].second == gfForPv[i][k]){
						pFaceMap[pf][i] = gfForPv[i][k];
						goto nextPv;
					}
				}
			}
			nextPv:;
		}
		if (pFaceMap[pf][0] == pFaceMap[pf][1]) pFaceMap[pf].face = pFaceMap[pf][0];
		else if (pFaceMap[pf][1] == pFaceMap[pf][2]) pFaceMap[pf].face = pFaceMap[pf][1];
		else if (pFaceMap[pf][2] == pFaceMap[pf][0]) pFaceMap[pf].face = pFaceMap[pf][2];
		else pFaceMap[pf].face = pFaceMap[pf][0];
		if (pFaceMap[pf].face == -1){
			return;
		}
	}
#if 0
	DSTR << "FaceMap PHtoGR:\n";
	for(unsigned i=0; i<pFaceMap.size(); ++i)
		DSTR << pFaceMap[i].face << ":" << pFaceMap[i][0] << " " << pFaceMap[i][1] << " " << pFaceMap[i][2] << ", ";
	DSTR << std::endl;
#endif

	//	�Ή��\�ɉ����ă}�e���A�����X�g��ݒ�B
	gmd.materialList.resize(grFemMesh->materialList.size() ? pFaceMap.size() : 0);
	for(unsigned pf=0; pf<gmd.materialList.size(); ++pf){
		gmd.materialList[pf] = grFemMesh->materialList[pFaceMap[pf].face];
	}

	//	�V�������GRMesh�̒��_����phFemMesh�̒��_�ւ̑Ή�
	vertexIdMap.resize(gmd.vertices.size(), -1);
	//	�Ή��\�ɉ����āA���_�̃e�N�X�`�����W���쐬
	//		ph�̂P�_��gr�̒��_�����ɑΉ�����ꍇ������B
	//		���̏ꍇ�͒��_�̃R�s�[�����K�v������B
	assert(grFemMesh->faceNormals.size());	// ���[�h�����t�@�C���ɖ@����񂪊܂܂�Ă��Ȃ�
	std::vector<bool> vtxUsed(gmd.vertices.size(), false);
	for(unsigned pf=0; pf<pFaceMap.size(); ++pf){		
		for(unsigned i=0; i<3; ++i){
			int pv = gmd.faces[pf].indices[i];
			//	�e�N�X�`�����W���v�Z
			Vec2f texCoord;
			Vec3f normal;
			GRMeshFace& gFace = grFemMesh->faces[pFaceMap[pf][i]];
			GRMeshFace& gFaceNormal = grFemMesh->faceNormals[pFaceMap[pf].face];
			GRMeshFace* gNormal = NULL;
			if (grFemMesh->normals.size()){
				gNormal = &gFace;
				if (grFemMesh->faceNormals.size()) gNormal = &grFemMesh->faceNormals[pFaceMap[pf].face];
			}
			if (gFace.nVertices == 3){
				Vec3f weight;
				Matrix3f vtxs;
				for(unsigned j=0; j<3; ++j){
					vtxs.col(j) = grFemMesh->vertices[gFace.indices[j]];
				}
				int tmp[3];
				vtxs.gauss(weight, gmd.vertices[pv], tmp);
				for(unsigned j=0; j<3; ++j){
					if (weight[j] <= -0.001){
						DSTR << "�O���t�B�N�X��3���_�̊O���ɕ����̒��_������܂��B" << std::endl; 
						for(unsigned k=0; k<3; ++k){
							for(unsigned ax=0; ax<3; ++ax){
								DSTR << grFemMesh->vertices[gFace.indices[k]][ax];
								DSTR << (ax==2 ? "\n" : "\t");
							}
						}
						for(unsigned ax=0; ax<3; ++ax){
							DSTR << gmd.vertices[pv][ax];
							DSTR << (ax==2 ? "\n" : "\t");
						}
					}
					//assert(grFemMesh->texCoords.size() == 0);	// ���[�h�����t�@�C����UV�}�b�s���O�̏�񂪂Ȃ�
					texCoord += weight[j] * grFemMesh->texCoords[gFace.indices[j]];
					if(gNormal) normal += weight[j] * grFemMesh->normals[gNormal->indices[j]];
				}
			}else{	//	4���_
				//	�ǂ̂R���_�ŋߎ�����ƈ�ԗǂ����𒲂ׁA���̂R���_����
				Vec3f weight[4];
				Matrix3f vtxs[4];
				double wMin[4];
				double wMinMax = -DBL_MAX;
				int maxId=-1;
				for(int j=0; j<4; ++j){
					for(int k=0; k<3; ++k){
						vtxs[j].col(k) = grFemMesh->vertices[gFace.indices[k<j ? k : k+1]];
					}
					int tmp[3];
					vtxs[j].gauss(weight[j], gmd.vertices[pv], tmp);
					wMin[j] = DBL_MAX;
					for(int l=0; l<3; ++l) if (wMin[j] > weight[j][l]) wMin[j] = weight[j][l];
					if (wMin[j] > wMinMax){
						wMinMax = wMin[j];
						maxId = j;
					}
				}
				for(int j=0; j<3; ++j){
					if (weight[maxId][j] <= -0.001){
						DSTR << "�O���t�B�N�X��3���_\t"; 
						for(unsigned k=0; k<3; ++k){
							DSTR << grFemMesh->vertices[gFace.indices[k]] << "\t";
						}
						DSTR << "�̊O���ɕ����̒��_:\t" << gmd.vertices[pv] << "������܂�" << std::endl;
					}
					//assert(grFemMesh->texCoords.size() == 0);	// ���[�h�����t�@�C����UV�}�b�s���O�̏�񂪂Ȃ�
					texCoord += weight[maxId][j] * grFemMesh->texCoords[gFace.indices[j<maxId?j:j+1]];
					if(gNormal){
						normal += weight[maxId][j] * grFemMesh->normals[gFaceNormal.indices[j<maxId?j:j+1]];
					}
				}
			}
			gmd.texCoords.resize(gmd.vertices.size());
			if (grFemMesh->normals.size()) gmd.normals.resize(gmd.vertices.size());
			//	�d�����_�̏ꍇ�̓R�s�[�����Ȃ�����
			if (vtxUsed[pv]){
				if (gmd.texCoords[pv] != texCoord || 
					(grFemMesh->normals.size() && gmd.normals[pv] != normal)){	
					//	���_�̃R�s�[�̍쐬
					gmd.vertices.push_back(gmd.vertices[pv]);
					gmd.texCoords.push_back(texCoord);
					if (gmd.normals.size()) gmd.normals.push_back(normal);
					gmd.faces[pf].indices[i] = (int)gmd.vertices.size()-1;
					vertexIdMap.push_back(phFemMesh->surfaceVertices[pv]);
				}
			}else{	//	�����łȂ���΁A���ڑ��
				gmd.texCoords[pv] = texCoord;
				if (gmd.normals.size()) gmd.normals[pv] = normal; 
				vertexIdMap[pv] = phFemMesh->surfaceVertices[pv];
				vtxUsed[pv] = true;
			}
		}
	}
	// ���_�J���[�̐ݒ�
	//*�f�o�b�N���[�h����mesh�`��ɂ���ė�����B�ǂ����Ń�������j�󂵂Ă�\������
#if _DEBUG
#else
	gmd.colors.resize(grFemMesh->colors.size() ? vertexIdMap.size() : 0);
	for(unsigned pv=0; pv<gmd.colors.size(); ++pv){
		gmd.colors[pv] = grFemMesh->colors[vertexIdMap[pv]];
	}
#endif
	//	GRMesh���쐬
	GRMesh* rv = grFemMesh->GetNameManager()->CreateObject(GRMeshIf::GetIfInfoStatic(), &gmd)->Cast();
	//	�}�e���A���̒ǉ�
	for (unsigned i=0; i<grFemMesh->NChildObject(); ++i){
		rv->AddChildObject(grFemMesh->GetChildObject(i));
	}
	//	�e�N�X�`�����[�h���R�s�[
	rv->tex3d = grFemMesh->tex3d;
	grFemMesh = rv;

	for(int i = 0; i < (int)vertexIdMap.size(); i++){
		texmode1Map.push_back(0);
	}
}

void FWFemMeshNew::Sync(){		
	//	��������
	FWObject::Sync();
	if(syncSource == FWObjectDesc::PHYSICS){
		if(GetPHFemMesh()->GetPHFemVibration()){
			SyncVibrationInfo();
		}
		if(GetPHFemMesh()->GetPHFemThermo()){
				SyncThermoInfo();
		}
	}
}

void FWFemMeshNew::SyncVibrationInfo(){
	if(!grFemMesh) return;
	grFemMesh->EnableAlwaysCreateBuffer();
	// ���_�ʒu�̓���
	if (vertexIdMap.size()) {
		Vec3f* grVertices = grFemMesh->GetVertices();
		for (int i = 0; i < (int)vertexIdMap.size(); i++) {
			int pId = vertexIdMap[i];
			grVertices[i] = (Vec3f)phFemMesh->vertices[pId].pos;
		}
	}
	// �ψʂŐF�ω�
	if(grFemMesh->NColors() < 1) return;
	Vec4f* vc = grFemMesh->GetColors();
	double base = 1e-6;
	double offset = 1e-5;
	for(int i = 0; i < (int)vertexIdMap.size(); i++){
		int pId = vertexIdMap[i];
		//float value = phFemMesh->GetVertexDisplacementL(pId).norm();
		float value = phFemMesh->GetVertexVelocityL(pId).norm();
		//CSVOUT << value << "," << value/base+offset <<  std::endl;			
		//vc[i] = CompThermoColor(value/base + offset);
		vc[i] = CompThermoColor(value/0.001+0.01);
	}
}

void FWFemMeshNew::SyncThermoInfo(){
	if(!grFemMesh) return;
	grFemMesh->EnableAlwaysCreateBuffer();
	// ���_�ʒu�̓���
	Vec3f* grVertices = grFemMesh->GetVertices();
	for(int i = 0; i < (int)vertexIdMap.size(); i++){
		int pId = vertexIdMap[i];
		grVertices[i] = (Vec3f)phFemMesh->vertices[pId].pos;
	}
	//���_���x�̓���
	GetPHFemMesh()->GetPHFemThermo()->UpdateVertexTempAll();
	
	//	�e�X�g�p
	//static double value, delta;
	//if (value <= 0) delta = 0.01;
	//if (value >= 1) delta = -0.01;
	//value += delta;
#ifdef VTX_DBG
	////	�f�o�b�O�p
	//// face�ӂ�`��
	DrawFaceEdge();
	////	XZ���ʂ�`��	true:�`�悷��
	//DrawIHBorderXZPlane(0);
	////	IH���M�̈�̋��E��������
	//DrawIHBorder(0.095,0.1);
#endif

	std::string fwfood;
	fwfood = this->GetName();		//	fwmesh�̖��O�擾


	if(fwfood == "fwNegi"){
		 //vertex�̖@���H�\��
		for(unsigned i=0; i < phFemMesh->faces.size(); i++){
			//.	face�G�b�W��\��	
			DrawEdgeCW(phFemMesh->GetFaceEdgeVtx(i,0),phFemMesh->GetFaceEdgeVtx(i,1),1.0f,0.5f,0.1f);
			DrawEdgeCW(phFemMesh->GetFaceEdgeVtx(i,1),phFemMesh->GetFaceEdgeVtx(i,2),1.0f,0.5f,0.1f);
			DrawEdgeCW(phFemMesh->GetFaceEdgeVtx(i,2),phFemMesh->GetFaceEdgeVtx(i,0),1.0f,0.5f,0.1f);
		}
	}

	if(fwfood == "fwPan"){
		//for(unsigned i =0; i < phMesh->vertices.size();i++){
		//	DrawNormal(phMesh->vertices[i].pos, phMesh->vertices[i].normal);
		//}
		for(unsigned i=0; i < phFemMesh->faces.size(); i++){
			//.	face�G�b�W��\��	
			DrawEdgeCW(phFemMesh->GetFaceEdgeVtx(i,0),phFemMesh->GetFaceEdgeVtx(i,1),1.0f,0.5f,0.1f);
			DrawEdgeCW(phFemMesh->GetFaceEdgeVtx(i,1),phFemMesh->GetFaceEdgeVtx(i,2),1.0f,0.5f,0.1f);
			DrawEdgeCW(phFemMesh->GetFaceEdgeVtx(i,2),phFemMesh->GetFaceEdgeVtx(i,0),1.0f,0.5f,0.1f);
		}
	}
	
	if(fwfood == "fwNsteak"){
		//for(unsigned i =0; i < phMesh->vertices.size();i++){
		//	DrawNormal(phMesh->vertices[i].pos, phMesh->vertices[i].normal);
		//}
		for(unsigned i=0; i < phFemMesh->faces.size(); i++){
			//.	face�G�b�W��\��	
			DrawEdgeCW(phFemMesh->GetFaceEdgeVtx(i,0),phFemMesh->GetFaceEdgeVtx(i,1),1.0f,0.5f,0.1f);
			DrawEdgeCW(phFemMesh->GetFaceEdgeVtx(i,1),phFemMesh->GetFaceEdgeVtx(i,2),1.0f,0.5f,0.1f);
			DrawEdgeCW(phFemMesh->GetFaceEdgeVtx(i,2),phFemMesh->GetFaceEdgeVtx(i,0),1.0f,0.5f,0.1f);
		}
	}


	//	50�x����:�e�N�X�`���̐[���v�Z(0~50)	( vertices.temp - 50.0 ) * dtex / 50.0
	//	50�x����:�e�N�X�`���̐[���v�Z(50~100)	( vertices.temp - 100.0 ) * dtex / 50.0
	//	50�x����:�e�N�X�`���̐[���v�Z(100~150)	( vertices.temp - 150.0 ) * dtex / 50.0
	//	����𖞂����悤�ɁA50,100,150�x�Ȃǂ�ϐ��ɂ��Ă��悢�B���A���ɗ��p���Ȃ����A��ڂł킩��₷���̂ŁA���̂܂܂ł��������B
	//	50�x���݂��Ƃ�dtex�����Z�����ɁAgvtx[stride*gv + tex + 2] = (temp - 50.0 ) * dtex / 50.0 + thstart;�����ł��̂���

	
	//	��������
	FWObject::Sync();
	if (syncSource==FWObjectDesc::PHYSICS){
		if (grFemMesh && grFemMesh->IsTex3D()){
			float* gvtx = grFemMesh->GetVertexBuffer();
			if (gvtx){
				int tex = grFemMesh->GetTexOffset();
				int stride = grFemMesh->GetStride();
				for(unsigned gv = 0; gv < vertexIdMap.size(); ++gv){
					float gvtxTemp;
					int pv = vertexIdMap[gv];
					float texend = 0.0f;
					if(fwfood == "fwNsteak"){
						texend=0.25862f;
					}else if(fwfood == "fwNegi" || fwfood == "fwPan"){
						texend=0.25;
					}
					//	PH���牽�炩�̕����ʂ�����Ă���
							//ph����ߓ_�̉��x������Ă���
					//PHFemMeshThermo�̊e�ߓ_�̉��x������Ă���B
					//���x�̒l�ɉ����āA���̌W����p���āA�e�N�X�`�����W���v�Z����
					//	value = phMesh�̔h���N���X->thermo[pv];
					//	GR�̃e�N�X�`�����W�Ƃ��Đݒ肷��B	s t r q �� r��ݒ�
					//gvtx[stride*gv + tex + 2] = value + gvtx[stride*gv];	//	gvtx[stride*gv]�ŏꏊ�ɂ���ĈႤ�[�x���E���Ă��邱�Ƃ�
					//gvtx[stride*gv + tex + 2] = 0.1 + value;
					////gvtx[stride*gv + tex + 2] = thstart;
	//				gvtx[stride*gv + tex + 2] = thstart;

					//	�ǂ̃e�N�X�`���ɂ��邩�̏�����������
					//	���O�̃e�N�X�`�����W��ۑ����Ă����B�Ȃ���΁A�����l��ݒ�
					//	�e�N�X�`���̕\�����[�h��؂�ւ���SW���L�[�{�[�h����؂�ւ���SampleApp.h��AddHotkey�AAddAction�����������
				
					//	CADThermo�̊Y�������̃\�[�X
					//if(tvtxs[j].temp <= tvtxs[j].temp5){		//tvtxs[j].wmass > wmass * ratio1
					//	texz	= texbegin;
					//	double texznew =diff * grad + texz;//����,�e�N�X�`�����W�̏����l
					//	////�O�̃e�N�X�`�������W��������̌v�Z�l���[��������A���̌v�Z���ʂ𔽉f������
					//	if(tvtxs[j].tex1memo <= texznew){			//���߂͂��̏������Ȃ��Ă���������ǁA��x���x���オ���āA��߂Ă���͕K�v�ɂȂ�
					//		tvtxs[j].SetTexZ(tratio * dl + texz);	//�e�N�X�`����Z���W�����肷��B//�\���e�N�X�`���͂��̐��`�a��\��������̂ŁAZ���W�����`�a�ŕ\������̂ŁA���`�a�̌v�Z���g�p
					//		tvtxs[j].tex1memo = tratio * dl + texz;	//tex1memo���X�V����
					//	}
					//}
					//if(texturemode == BROWNED){
#if 0
					// �ψʂŐF�ω��O�ɏ����Ă���͂���������̖��߂��D��
					
					if(grFemMesh->NColors() < 1) return;
					Vec4f* vc = grFemMesh->GetColors();
					double base = 1e-8;
					double offset = 1e-8;
					for(int i = 0; i < (int)vertexIdMap.size(); i++){
						int pId = vertexIdMap[i];
						float value = phFemMesh->GetVertexDisplacementL(pId).norm();
						//value = phFemMesh->//�T�[���p�̊֐��Œ��_���x���擾
						//DSTR << value << std::endl;
						DSTR << value/base + offset << std::endl;
						//DSTR << value/base + offset +rand() << std::endl;
						vc[i] = CompThermoColor(value/base + offset);
						//vc[i] = CompThermoColor(1.0);
					}
#endif
					if(texture_mode == 1){
						//	�ł��e�N�X�`���؂�ւ�
						//	�Ă���ɉ������ω�
					//gvtx[stride*gv + tex + 2] = texstart;		// �ł��e�N�X�`���̏������W
#if 0
						//���b�V���̔���
						//DSTR << "this->GetName(): " << this->GetName() << std::endl; ;	//phMesh->GetName():fem4
						//���L�O��̂ǂ̂����ł�OK
						std::string strg;
						strg = this->GetName();
						if(strg == "fwNegi"){
							DSTR << "Negi STR" << std::endl;
						}
						FWFemMeshIf* fmeshif;
						GetScene()->FindObject(fmeshif,"fwNegi");
						if( fmeshif ){
							DSTR << fmeshif->GetName() << std::endl;
							DSTR << "NEGINEGI GET" << std::endl;

						}
						//
						FWFemMeshIf* fnsteakifif;
						GetScene()->FindObject(fnsteakifif,"fwNsteak");
						if( fnsteakifif ){
							DSTR << fnsteakifif->GetName() << std::endl;
							DSTR << "NIKUNIKU GET" << std::endl;
						}  
						
#endif	
						gvtxTemp = phFemMesh->GetPHFemThermo()->calcGvtx(fwfood, pv, texture_mode);
						if(gvtxTemp > texmode1Map[gv] && gvtxTemp < texend){
							texmode1Map[gv] = gvtxTemp;
						}
						if(gvtx){
							gvtx[stride * gv + tex + 2] = texmode1Map[gv];
						}
					}else if(texture_mode == 3 || texture_mode == 2 || texture_mode == 4){
						gvtxTemp = phFemMesh->GetPHFemThermo()->calcGvtx(fwfood, pv, texture_mode);
						if(gvtx){
							gvtx[stride * gv + tex + 2] = gvtxTemp;
							if(fwfood == "fwNsteak"){
								//DSTR<<"fwNsteak kogetex "<<kogetex<<"  gvtxTemp: "<<gvtxTemp<<std::endl;
							}
						}
					}
				}
			}	
		}else{
			DSTR << "Error: " << GetName() << ":FWFemMesh does not have 3D Mesh" << std::endl;
		}
	}
}

void FWFemMeshNew::Settexmode1Map(float temp){
	//�ł��e�N�X�`���̖���
	unsigned kogetex	= 5;
	//�����e�N�X�`���̖���
	unsigned watex		= 2;
	//�T�[���e�N�X�`���̖���
	unsigned thtex		= 6;
	unsigned thcamtex   = 9;		//�M�J�������ۂ��\���p
	//	���[�h�e�N�X�`���[���ł����������x�̏�	�i�܂��́j�������x���ł�	�ɂ��ύX�\�i�t�@�C�����̃��l�[�����K�v�j

	//�����e�N�X�`���̖���(���̋�Ԗ��x��p�����ꍇ)
	unsigned watex2 = 5;

	std::string fwfood;
	fwfood = this->GetName();		//	fwmesh�̖��O�擾

	if(fwfood == "fwNegi" ||fwfood == "fwPan"){		///	�e�N�X�`���Ɖ��x�A�����ʂƂ̑Ή��\�́ASamples/Physics/FEMThermo/�e�N�X�`���̐F�Ɖ��x�̑Ή�.xls	���Q�Ƃ̂���
		kogetex	= 5;
	}
	else if(fwfood == "fwNsteak"){
		kogetex	= 7;		//7�ɂ���
	}

	double dtex =(double) 1.0 / ( kogetex + thtex + watex + thcamtex);		//	�e�N�X�`�����s���W�̑w�Ԋu
	if(fwfood == "fwNsteak"){
		dtex =(double) 1.0 / ( kogetex + thtex + watex + thcamtex + watex2);
	}
	double texstart = dtex /2.0;										//	�e�N�X�`�����W�̏����l = �ł��e�N�X�`���̃X�^�[�g���W
	double wastart = texstart + kogetex * dtex;							//	�����ʕ\���e�N�X�`���̃X�^�[�g���W
	double thstart = texstart + kogetex * dtex + 1.0 * dtex;			//	�T�[���̃e�N�X�`���̃X�^�[�g���W �����e�N�X�`����2���ڂ���X�^�[�g
	double thcamstart = texstart + (thtex + kogetex + watex) * dtex;	//
	
	float gvtxTemp = 0.0f;

	if(fwfood == "fwPan"){
			gvtxTemp = texstart;// + dtex;		// �˂��ݐF�̒��
		}else if(fwfood == "fwNegi"){
			// ���x�ω��Ɠ����Ł@
			// -50.0~0.0:aqua to blue
			if(temp <= -50.0){
				gvtxTemp = texstart + dtex;
			}
			else if(-50.0 < temp && temp <= 0.0){	
				gvtxTemp = texstart + dtex;//(texstart ) + ((temp + 50.0) * dtex /50.0);
			}
			//	0~50.0:blue to green
			else if(0.0 < temp && temp <= 50.0 ){
				//double green = temp * dtex / 50.0 + thstart;
				gvtxTemp = (temp - 50.0)  * dtex / 50.0 + texstart + dtex; //+     dtex;
			}
			//	50.0~100.0:green to yellow
			else if(50.0 < temp && temp <= 100.0){
				gvtxTemp = (temp - 50.0 ) * dtex / 50.0 + texstart + dtex;// + 2 * dtex;
			}
			//	100.0~150:yellow to orange	
			else if(100.0 < temp && temp <= 150.0){
				gvtxTemp = (temp - 50.0 ) * dtex / 50.0 + texstart + dtex;// + 2 * dtex;
			}
			//	150~200:orange to red
			else if(150.0 < temp && temp <= 200.0){
				double pinkc = (temp - 50.0 ) * dtex / 50.0 + thstart ;
				gvtxTemp = dtex * 4.0 + texstart;//(temp - 50.0 ) * dtex / 50.0 + texstart + dtex;// + 2 * dtex;
			}
			//	200~250:red to purple
			else if(200.0 < temp && temp <= 250.0){
				gvtxTemp = dtex * 4.0 + texstart;//(temp - 50.0 ) * dtex / 50.0 + texstart + dtex;// + 2 * dtex;
			}
			///	250~:only purple
			else if(250.0 < temp){
				gvtxTemp = dtex * 4.0 + texstart;
				//gvtx[stride*gv + tex + 2] = wastart;			//whit
			}
	}else if(fwfood == "fwNsteak"){
			// -50.0~0.0:aqua to blue
			if(temp <= 50.0){
				gvtxTemp = texstart;
			}
			else if(50.0 < temp && temp <= 60.0){
				gvtxTemp = texstart + ((temp - 50) / 10 * dtex);//(texstart ) + ((temp + 50.0) * dtex /50.0);
			}
			else if(60.0 < temp && temp <= 63.0){
				gvtxTemp = texstart + ((temp - 60) / 3 * dtex) + (1.0 * dtex);//(texstart ) + ((temp + 50.0) * dtex /50.0);
			}
			//	0~50.0:blue to green
			else if(63.0 < temp && temp <= 68.0 ){
				//double green = temp * dtex / 50.0 + thstart;
				gvtxTemp = texstart + ((temp - 63) / 5 * dtex) + (2.0 * dtex); //+     dtex;
			}
			//	50.0~100.0:green to yellow
			else if(68.0 < temp && temp <= 72.0){
				gvtxTemp = texstart + ((temp - 68) / 5 * dtex) + (3.0 * dtex);// + 2 * dtex;
			}
			//	100.0~150:yellow to orange	
			else if(72.0 < temp && temp <= 77.0){
				gvtxTemp = texstart + ((temp - 72) / 5 * dtex) + (4.0 * dtex);// + 2 * dtex;
			}
			//	150~200:orange to red
			else if(77.0 < temp && temp <= 120.0){
				gvtxTemp = texstart + ((temp - 77) / 43 * dtex) + (5.0 * dtex);// + 2 * dtex;
			}
			//	200~250:red to purple
			else if(120.0 < temp ){
				gvtxTemp = texstart + (6.0 * dtex);// + 2 * dtex;
			}
		}
	for(unsigned i = 0; i < vertexIdMap.size(); ++i){
		texmode1Map[i]=gvtxTemp;
	}
}

void FWFemMeshNew::DrawEdgeCW(Vec3d vtx0, Vec3d vtx1,float R,float G,float B){
	// ���͂��ꂽ2���_���W�Ԃ�����
	if(drawflag==true){
	Vec3d wpos0 = this->GetGRFrame()->GetWorldTransform() * vtx0; //* ���[�J�����W�� ���E���W�ւ̕ϊ����đ��
	Vec3d wpos1 = this->GetGRFrame()->GetWorldTransform() * vtx1; //* ���[�J�����W�� ���E���W�ւ̕ϊ����đ��
	glBegin(GL_LINES);
		glColor3d(R,G,B);
		glVertex3d(wpos0[0],wpos0[1],wpos0[2]);
		glVertex3d(wpos1[0],wpos1[1],wpos1[2]);
	glEnd();
	}
	//glFlush();
}

Vec4f FWFemMeshNew::CompThermoColor(float value){
	float cos = -0.5 * std::cos( 4 * M_PI * value) + 0.5;
	Vec4f color;
	if(value > 1.0){
		// red
		color = Vec4f(1.0, 0.0, 0.0, 1.0);
	}else if(value > 3.0 / 4.0){
		// red + green
		color = Vec4f(1.0, cos, 0.0, 1.0);
	}else if(value > 2.0 / 4.0){
		// green
		color = Vec4f(cos, 1.0, 0.0, 1.0);
	}else if(value > 1.0 / 4.0){
		// green + blue
		color = Vec4f(0.0, 1.0, cos, 1.0);
	}else if(value > 0.0){
		// blue
		color = Vec4f(0.0, 0.0, 1.0, 1.0);
	}
	return color;
}


}
