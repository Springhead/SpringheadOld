/*
 *  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
/**
 *	@file SprHISkeletonSensor.h
 *	@brief �X�P���g���i�{�[���\���j��F������Z���T�BKinect, Leapmotion�ȂǁB
*/

#ifndef HI_SKELETONSENSORIF_H
#define HI_SKELETONSENSORIF_H

#include <HumanInterface/SprHIBase.h>

namespace Spr{;
/**	\addtogroup	gpHumanInterface	*/
//@{

/**	@brief SkeletonSensor���Ԃ��X�P���g���Ɋ܂܂��{�[��*/
struct HIBoneIf: public ObjectIf{
	SPR_IFDEF(HIBone);

	/// �e��Ԃ�
	HIBoneIf* GetParent();

	/// �ʒu��Ԃ�
	Vec3d GetPosition();
	/// �����x�N�g���i����1�j��Ԃ�
	Vec3d GetDirection();
	/// ������Ԃ�
	double GetLength();
};

/**	@brief SkeletonSensor���Ԃ��X�P���g��*/
struct HISkeletonIf: public ObjectIf{
	SPR_IFDEF(HISkeleton);

	/// �S�̂̎p����Ԃ�
	Posed GetPose();
	/// �{�[���̐���Ԃ�
	int NBones();
	/// �{�[����Ԃ�
	HIBoneIf* GetBone(int i);
	/// ���[�g�{�[����Ԃ�
	HIBoneIf* GetRoot();
	/// �͂�ł�x��Ԃ�
	float GetGrabStrength();

	/// �g���b�L���O��
	bool IsTracked();

	/// �g���b�L���OID
	int GetTrackID();
};

/**	@brief SkeletonSensor�̃C���^�t�F�[�X */
struct HISkeletonSensorIf: public HIBaseIf{
	SPR_IFDEF(HISkeletonSensor);

	/// �X�P���g���̐���Ԃ�
	int NSkeletons();
	/// �X�P���g����Ԃ�
	HISkeletonIf* GetSkeleton(int i);

	// �X�P�[���W�����Z�b�g����
	void SetScale(double s);
	// ���S�ʒu���Z�b�g����
	void SetCenter(Vec3d c);
	// ���W���̌��������߂��]���Z�b�g����
	void SetRotation(Quaterniond q);

};

//@}
}
#endif
