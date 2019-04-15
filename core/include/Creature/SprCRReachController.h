/*
 *  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
#ifndef SPR_CRREACHCONTROLLERIF_H
#define SPR_CRREACHCONTROLLERIF_H

#include <Foundation/SprObject.h>
#include <Creature/SprCRController.h>
#include <Physics/SprPHSolid.h>
#include <Physics/SprPHJoint.h>
#include <Physics/SprPHIK.h>

namespace Spr{;

///	�O���^���R���g���[��
struct CRReachControllerIf : public CRControllerIf{
	SPR_IFDEF(CRReachController);

	/** @brief ���B�Ɏg���G���h�G�t�F�N�^��ݒ�E�擾����
	*/
	void SetIKEndEffector(PHIKEndEffectorIf* ikEff, int n=0);
	PHIKEndEffectorIf* GetIKEndEffector(int n=0);

	/** @brief �ŏI���B�ڕW�ʒu���Z�b�g����
	*/
	void SetFinalPos(Vec3d pos);

	/** @brief �ŏI���B�ڕW���x���Z�b�g����i�f�t�H���g�� (0,0,0)�j
	*/
	void SetFinalVel(Vec3d vel);
	
	/** @brief �o�R�n�_�ʉߎ������Z�b�g����i���̏ꍇ�A�o�R�n�_��p���Ȃ��j
	*/
	void SetViaTime(float time);

	/** @brief �o�R�n�_���Z�b�g����
	*/
	void SetViaPos(Vec3d pos);

	/** @brief �������[�h��L���ɂ���
	*/
	void EnableLookatMode(bool bEnable);
	bool IsLookatMode();

	/** @brief ��̎g�p����ݒ�E�擾����
	*/
	void SetNumUseHands(int n);
	int GetNumUseHands();

	/** @brief i�Ԗڂ̘r�̕t�����֐߂��Z�b�g����i�����Ɋ�Â��g�p����Ɏg���j
	*/
	void SetBaseJoint(int n, PHJointIf* jo);

	// ----- ----- -----

	/** @brief ���ϓ��B���x���Z�b�g����i��������ڕW���B���Ԃ��v�Z�����j
	*/
	void SetAverageSpeed(double speed);
	double GetAverageSpeed();

	/** @brief �}�[�W���iFinalPos���炱�̔��a���ɓ��B����΂悢�j���Z�b�g����
	*/
	void SetMargin(double margin);

	/** @brief �����}�[�W���iFinalPos���炱�̔��a�̒��ɂ͓���Ȃ��悤�ɂ���j���Z�b�g����
	*/
	void SetInnerMargin(double margin);

	/** @brief �ڕW�����̑��x�ȏ�ɂȂ����瓞�B�ڕW�̍X�V����U��~
	*/
	void SetWaitVel(double vel);

	/** @brief Wait��ɖڕW�����̑��x�ȉ��ɂȂ����瓞�B�^�������X�^�[�g
	*/
	void SetRestartVel(double vel);

	// ----- ----- -----

	/** @brief �O���ʉߓ_�̈ʒu�E���x��Ԃ� s=0.0�`1.0
	*/
	Vec6d GetTrajectory(float s);

	/** @brief �ڕW���B���Ԃ�Ԃ�
	*/
	float GetReachTime();

	/** @brief ���ݎ�����Ԃ�
	*/
	float GetTime();

	/** @brief �f�o�b�O����`�悷��
	*/
	void Draw();

	// ----- ----- -----

	/** @brief �p�����䊮�����̎��Ԃ̊������Z�b�g����
	*/
	void SetOriControlCompleteTimeRatio(float oriTime);
};

//@{
///	�O���^���R���g���[����State
struct CRReachControllerState{
	/// �O���^���J�n����̌o�ߎ���
	float time;
	
	/// �ڕW���B�����i�^���J�n����0�Ƃ���j
	float reachTime;

	/// �ڕW�o�R�_�ʉߎ����i�o�R�_���g��Ȃ��ꍇ�͕��̒l�Ƃ���j
	float viaTime;

	/// �p�����䊮�����̎��Ԃ̊���
	float oricontTimeRatio;

	/// �^���J�n���̈ʒu�E���x�E�p���E�p���x
	Vec3d initPos, initVel, initAVel;
	Quaterniond initOri;

	/// �o�R�_�̖ڕW�ʒu�E�p��
	Vec3d viaPos;
	Quaterniond viaOri;

	/// ���ݓ��B�ڕW�Ƃ��Ă���ʒu�E���x�E�p���E�p���x
	Vec3d targPos, targVel, targAVel;
	Quaterniond targOri;

	/// ���݂̈ʒu�E���x�E�p���E�p���x
	Vec3d currPos, currVel, currAVel;
	Quaterniond currOri;

	/// �ŏI�I�Ȃ̖ڕW�ʒu�E���x�E�p���E�p���x
	Vec3d finalPos, finalVel, finalAVel;
	Quaterniond finalOri;

	CRReachControllerState(){
		time = 0; reachTime = -1; viaTime  = -1; oricontTimeRatio = 0;
		initPos  = Vec3d(); initVel  = Vec3d(); initOri  = Quaterniond(); initAVel  = Vec3d();
		targPos  = Vec3d(); targVel  = Vec3d(); targOri  = Quaterniond(); targAVel  = Vec3d();
		currPos  = Vec3d(); currVel  = Vec3d(); currOri  = Quaterniond(); currAVel  = Vec3d();
		finalPos = Vec3d(); finalVel = Vec3d(); finalOri = Quaterniond(); finalAVel = Vec3d();
		viaPos   = Vec3d(); viaOri   = Quaterniond();
	}
};

/// �O���^���R���g���[���̃f�X�N���v�^
struct CRReachControllerDesc : public CRControllerDesc, public CRReachControllerState {
	SPR_DESCDEF(CRReachController);

	// �}�[�W��
	double margin;

	// �����}�[�W��
	double innerMargin;

	// ���ϓ��B���x
	double averageSpeed;

	// �ڕW�X�V�҂����x
	double waitVel;

	// �X�V�҂��㓞�B�^���ĊJ���x
	double restartVel;

	CRReachControllerDesc() {
		margin             = 0.0;
		innerMargin        = 0.0;
		averageSpeed       = 5.0;
		waitVel            = 5.0;
		restartVel         = 2.5;
	}
};

//@}

}

#endif//SPR_CRREACHCONTROLLERIF_H
