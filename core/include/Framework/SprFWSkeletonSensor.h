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

#ifndef FW_SKELETONSENSORIF_H
#define FW_SKELETONSENSORIF_H

#include <Foundation/SprObject.h>
#include <HumanInterface/SprHISkeletonSensor.h>

namespace Spr{;
/**	\addtogroup	gpHumanInterface	*/
//@{

/**	@brief SkeletonSensor�̃f�X�N���v�^ */
struct FWSkeletonSensorDesc {
	// ���炩���ߓo�^���ꂽPHSkeleton�������i����Ȃ��j�ꍇ�Ɏ�����PHSkeleton�����
	bool bCreatePHSkeleton;
	// PHSkeleton�����̂������Ă��Ȃ�������i����Ȃ�������j������PHSolid�����
	bool bCreatePHSolid;
	// ������PHSolid�����ۂɎ�����CDShape���쐬����
	bool bCreateCDShape;
	// ������PHSolid�����ۂɐe�q�֌W�Ɋ��PHJoint���쐬����
	bool bCreatePHJoint;
	// ������PHSolid�����ۂɎ����łQ��PHSolid�����Ԃ�PHSpring�łȂ�
	bool bCreatePHSpring;
	// �����ō��RoundCone�̒��a�i���w�̑����j
	Vec2d radius;

	FWSkeletonSensorDesc() {
		bCreatePHSkeleton = true;
		bCreatePHSolid    = true;
		bCreateCDShape    = true;
		bCreatePHJoint    = false;
		bCreatePHSpring   = false;
		radius            = Vec2d(0.7, 0.7);
	}
};

struct PHSkeletonIf;
/**	@brief SkeletonSensor�̃C���^�t�F�[�X */
struct FWSkeletonSensorIf: public SceneObjectIf {
	SPR_IFDEF(FWSkeletonSensor);

	/// �Z���T����̓ǂݍ��݂�PHScene�ւ̔��f���s��
	void Update();

	/// ���a���Z�b�g
	void SetRadius(Vec2d r);

	/// �֘A�t����ꂽHISkeletonSensor��Ԃ�
	HISkeletonSensorIf* GetSensor();

	/// �X�P���g������Ԃ�
	int NSkeleton();
	PHSkeletonIf* GetSkeleton(int i);

};

//@}
}
#endif
