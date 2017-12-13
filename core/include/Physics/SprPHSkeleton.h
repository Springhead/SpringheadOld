/*
 *  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */

/** \addtogroup gpPhysics 	*/
//@{

/**
 *	@file SprPHSkeleton.h
 *	@brief �X�P���g��
*/
#ifndef SPR_PHSKELETONIF_H
#define SPR_PHSKELETONIF_H

namespace Spr{;

struct PHBoneDesc {
	PHBoneDesc() {
	}
};

struct PHBoneIf : public SceneObjectIf{
public:
	SPR_IFDEF(PHBone);

	/** @brief Solid��ݒ肷��
	 */
	void SetSolid(PHSolidIf* solid);

	/** @brief Solid���擾����
	 */
	PHSolidIf* GetSolid();

	/** @brief Proxy Solid��ݒ肷��
	 */
	void SetProxySolid(PHSolidIf* solid);

	/** @brief Proxy Solid���擾����
	 */
	PHSolidIf* GetProxySolid();

	/** @brief Joint��ݒ肷��
	 */
	void SetJoint(PHJointIf* joint);

	/** @brief Joint���擾����
	 */
	PHJointIf* GetJoint();

	/** @brief �eBone��ݒ肷��
	 */
	void SetParent(PHBoneIf* parent);

	/** @brief �eBone���擾����
	 */
	PHBoneIf* GetParent();

	// ----- ----- ----- ----- -----

	/** @brief �{�[���̒������Z�b�g����
	 */
	void SetLength(double length);

	/** @brief �{�[���̌������Z�b�g����i�q�{�[����Position�������ɃZ�b�g����j
	 */
	void SetDirection(Vec3d dir);

	/** @brief �{�[���̈ʒu���Z�b�g����i�e�{�[����Direction�������ɃZ�b�g����j
	 */
	void SetPosition(Vec3d pos);

};

// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

struct PHSkeletonDesc {
	PHSkeletonDesc() {
	}
};

struct PHSkeletonIf : public SceneObjectIf{
public:
	SPR_IFDEF(PHSkeleton);

	/** @brief Bone�̐����擾����
	 */
	int NBones();

	/** @brief Bone���擾����
	 */
	PHBoneIf* GetBone(int i);

	/** @brief Bone���쐬����
	 */
	PHBoneIf* CreateBone(PHBoneIf* parent, const PHBoneDesc& desc = PHBoneDesc());

	/** @brief �͂�ł�x���擾����
	 */
	float GetGrabStrength();
};


}	//	namespace Spr

//@}

#endif
