#include "tetgen.h"
#include "sprTetgen.h"

bool sprTetgenCpp(int& nVtxsOut, Spr::Vec3d*& vtxsOut, int& nTetsOut, int*& tetsOut, int nVtxIn, Spr::Vec3d* vtxIn, int nFacesIn, Spr::GRMeshFace* facesIn, char* option){
	//TetGen�Ŏl�ʑ̃��b�V����
	tetgenio in, out;	//	tetgen�̃f�B�X�N���v�^

	//	���_�̊��0��
	in.firstnumber = 0;
	in.numberofpoints = nVtxIn;						//	grMesh�̒��_�̐���ݒ�
	in.pointlist = DBG_NEW REAL[in.numberofpoints * 3];
	for(int j=0; j < nVtxIn; j++){	//	���_�̍��W��ݒ�
		for(int k=0; k<3; ++k){
			in.pointlist[j*3+k] = vtxIn[j][k];
		}
	}

	in.numberoffacets = nFacesIn;	//�ʂ̐�
	//	�ʏ��p�̃������̊m��
	in.facetlist = DBG_NEW tetgenio::facet[in.numberoffacets];
	in.facetmarkerlist = DBG_NEW int[in.numberoffacets];
	//	�ʏ��̑��
	for(int j =0; j < in.numberoffacets ; j++){
		tetgenio::facet* f = &in.facetlist[(int)j];
		f->numberofpolygons = 1;
		f->polygonlist = DBG_NEW tetgenio::polygon[f->numberofpolygons];
		f->numberofholes = 0;
		f->holelist = NULL;
		tetgenio::polygon* p = &f->polygonlist[0];
		p->numberofvertices = facesIn[j].nVertices;
		p->vertexlist = DBG_NEW int[p->numberofvertices];
		for(int k =0; k < p->numberofvertices; k++){
			p->vertexlist[k] = facesIn[j].indices[k];
		}
		in.facetmarkerlist[j] = 0;
	}
	/*	���͏��̊m�F�p
	in.save_nodes("tetgenIn");
	in.save_poly("tetgenIn");
	in.save_elements("tetgenIn");
	*/
	tetrahedralize(option, &in, &out);	
	//	�o�͏��̊m�F�p
	out.save_nodes("tetgenOut");			
	out.save_elements("tetgenOut");
	out.save_faces("tetgenOut");
	
	nVtxsOut = out.numberofpoints;
	vtxsOut = DBG_NEW Spr::Vec3d[nVtxsOut];
	for(int i=0; i<nVtxsOut; ++i) vtxsOut[i] = out.pointlist + 3*i;
	nTetsOut = out.numberoftetrahedra;
	tetsOut = DBG_NEW int [4*nTetsOut];
	for(int i=0; i<4*nTetsOut; ++i) tetsOut[i] = out.tetrahedronlist[i];
	if (nVtxsOut && nTetsOut) return true;
	return false;
}
void sprTetgenFreeCpp(Spr::Vec3d* vtxsOut, int* tetsOut){
	delete vtxsOut;
	delete tetsOut;
}
extern "C"{
	bool sprTetgen(int& nVtxsOut, Spr::Vec3d*& vtxsOut, int& nTetsOut, int*& tetsOut, int nVtxIn, Spr::Vec3d* vtxIn, int nFacesIn, Spr::GRMeshFace* facesIn, char* option){
		return sprTetgenCpp(nVtxsOut, vtxsOut, nTetsOut, tetsOut, nVtxIn, vtxIn, nFacesIn, facesIn, option);
	}
	void sprTetgenFree(Spr::Vec3d* vtxsOut, int* tetsOut){
		sprTetgenFreeCpp(vtxsOut, tetsOut);
	}
}
