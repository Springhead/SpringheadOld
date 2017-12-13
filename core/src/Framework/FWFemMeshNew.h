/*
 *  Copyright (c) 2003-2012, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
#ifndef FW_FEMMESH_NEW_H
#define FW_FEMMESH_NEW_H

#include "FWObject.h"
#include <Framework/SprFWFemMeshNew.h>
#include "../Physics/PHFemMeshNew.h"
#include "FrameworkDecl.hpp"

namespace Spr{;

class GRMesh;

/**	Framework��ł�FEM���b�V���B
	���X�e�b�v�APHFemMeshNew��FEM�V�~�����[�V�������ʂ�GRMesh�ɔ��f������B
	���������ɂ́AGRMesh����PHFemMeshNew�𐶐����A�����PHFemMeshNew����GRMesh�𐶐����AgrMesh��grFrame�̉���GRMesh�ƒu��������B*/
class FWFemMeshNew: public FWObject{
	SPR_OBJECTDEF(FWFemMeshNew);		
	SPR_DECLMEMBEROF_FWFemMeshNewDesc;
public:
	//UTRef< PHFemMeshNew > phFemMesh;	///< �����v�Z�p�̃��b�V��
	PHFemMeshNew*  phFemMesh;
	UTRef< GRMesh > grFemMesh;			///< �`��p�̃��b�V��
	std::vector<int> vertexIdMap;		///< grFemMesh����phFemMesh��
	//char* meshRoughness;			///< tetgen�Ő������郁�b�V���̑e��
	bool drawflag;
	std::vector<float> texmode1Map;

	FWFemMeshNew(const FWFemMeshNewDesc& d=FWFemMeshNewDesc());		//�R���X�g���N�^
	///	�q�I�u�W�F�N�g�̐�
	virtual size_t NChildObject() const;
	///	�q�I�u�W�F�N�g�̎擾
	virtual ObjectIf* GetChildObject(size_t pos);
	///	�q�I�u�W�F�N�g�̒ǉ�
	virtual bool AddChildObject(ObjectIf* o);
	/// phMesh���擾
	PHFemMeshNewIf* GetPHFemMesh(){ return phFemMesh->Cast();	};

	///	���[�h��ɌĂ΂��BgrMesh����phMesh�𐶐����AgrMesh��phMesh�ɍ��킹�����̂ɒu��������
	void Loaded(UTLoadContext* );
	///	grFemMesh����l�ʑ̃��b�V���𐶐�����BTetgen���g��phFemMesh�Ɋi�[����B
	virtual bool CreatePHFemMeshFromGRMesh();
	///	phFemMesh�����GRMesh�𐶐�����B�}�e���A���Ȃǂ�grMesh����E���B
	void CreateGRFromPH();

	///	�O���t�B�N�X�\���O�̓�������
	void Sync();
	/// PHVibration�̏��𓯊�
	void SyncVibrationInfo();
	/// PHThermo�̏��𓯊�
	void SyncThermoInfo();

	void DrawEdgeCW(Vec3d vtx0, Vec3d vtx1,float Red,float Green,float Blue);		// 2�ʒu���W���Ȃ���������,Color,World coordinate

	Vec4f CompThermoColor(float value);

	void CreateTranslucentMesh(GRMeshIf* wetMesh,std::map<int,int> corFemWet,std::vector<int> femVtx,std::vector<bool> vWetFlag,GRRenderIf* render);

	void EnableDrawEdgeCW(bool flag){drawflag = flag;};

	void Settexmode1Map(float temp);
public:
	enum TEXTURE_MODE{
		BROWNED,
		MOISTURE,
		THERMAL,
	} texturemode;
	void SetTexmode(unsigned mode){texture_mode = mode;};
};
}

#endif
