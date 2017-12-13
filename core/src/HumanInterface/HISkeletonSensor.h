/*
 *  Copyright (c) 2003-2012, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   

 */
#ifndef HI_SKELETONSENSOR_H
#define HI_SKELETONSENSOR_H

#include <HumanInterface/HIBase.h>
#include <HumanInterface/SprHISkeletonSensor.h>
#include <Foundation/SprObject.h>

#include <vector>

namespace Spr{;

// SkeletonSensor���Ԃ��X�P���g���Ɋ܂܂��{�[��
class HIBone: public Object {
public:
	SPR_OBJECTDEF(HIBone);

	HIBoneIf* parent;

	Vec3d     position;
	Vec3d     direction;
	double    length;

	// ----- ----- ----- ----- -----
	// API�֐�

	/// �e��Ԃ�
	HIBoneIf* GetParent() { return parent; }

	/// �ʒu��Ԃ�
	Vec3d GetPosition() { return position; }
	/// �����x�N�g���i����1�j��Ԃ�
	Vec3d GetDirection() { return direction; }
	/// ������Ԃ�
	double GetLength() { return length; }
};

// SkeletonSensor���Ԃ��X�P���g��
class HISkeleton: public Object {
public:
	SPR_OBJECTDEF(HISkeleton);

	std::vector< UTRef<HIBoneIf> > bones;

	Posed pose;

	float grabStrength;

	int trackID;

	bool bTracked;

	// ----- ----- ----- ----- -----
	// API�֐�

	/// �S�̂̎p����Ԃ�
	Posed GetPose() { return pose; }
	/// �{�[���̐���Ԃ�
	int NBones() { return (int)(bones.size()); }
	/// �{�[����Ԃ�
	HIBoneIf* GetBone(int i) { return bones[i]; }
	/// ���[�g�{�[����Ԃ�
	HIBoneIf* GetRoot() {
		for (int i=0; i<(int)bones.size(); ++i) {
			if (bones[i]->GetParent()==NULL) { return bones[i]; }
		}
		return NULL;
	}
	/// �͂�ł�x��Ԃ�
	virtual float GetGrabStrength() { return grabStrength; }
	/// �g���b�L���O��
	bool IsTracked() { return bTracked; }
	/// �g���b�L���OID
	int GetTrackID() { return trackID; }

	// ----- ----- ----- ----- -----
	// ��API�֐�

	/// ���ɑ���Ȃ����̃{�[��������
	void PrepareBone(int n) {
		for (int i=(int)bones.size(); i<n; ++i) {
			bones.push_back( (DBG_NEW HIBone())->Cast() );
		}
	}
};

// �X�P���g�����擾����Z���T�[�iKinect, Leapmotion�Ȃǁj
class HISkeletonSensor: public HIBase {
public:
	SPR_OBJECTDEF(HISkeletonSensor);

	std::vector< UTRef<HISkeletonIf> > skeletons;

	double      scale;
	Vec3d       center;
	Quaterniond rotation;

	HISkeletonSensor() {
		scale    = 1.0;
		center   = Vec3d();
		rotation = Quaterniond();
	}

	// ----- ----- ----- ----- -----
	// API�֐�

	/// �X�P���g���̐���Ԃ�
	int NSkeletons() { return (int)(skeletons.size()); }
	/// �X�P���g����Ԃ�
	HISkeletonIf* GetSkeleton(int i) { return skeletons[i]; }

	// �X�P�[���W�����Z�b�g����
	void SetScale(double s) { scale = s; }
	// ���S�ʒu���Z�b�g����
	void SetCenter(Vec3d c) { center = c; }
	// ���W���̌��������߂��]���Z�b�g����
	void SetRotation(Quaterniond q) { rotation = q; }

	// ----- ----- ----- ----- -----
	// ��API�֐�

	/// ���ɑ���Ȃ����̃X�P���g��������
	void PrepareSkeleton(int n) {
		for (int i=(int)skeletons.size(); i<n; ++i) {
			skeletons.push_back( (DBG_NEW HISkeleton())->Cast() );
		}
	}
};

}

#endif//HI_LEAP_H
