/*
*  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team
*  All rights reserved.
*  This software is free software. You can freely use, distribute and modify this
*  software. Please deal with this software under one of the following licenses:
*  This license itself, Boost Software License, The MIT License, The BSD License.
*/
#ifndef SPR_CRTIMESERIESIF_H
#define SPR_CRTIMESERIESIF_H

#include <Foundation/SprObject.h>

namespace Spr {

	struct CRBoneIf;

	// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

	// CRJointTimeSlice�̂ǂ̕ϐ��Ƀf�[�^�������Ă��邩�������t���O�̎w��Ɏg��
	enum CRJointTimeSliceFlag {
		CRJT_SPRING, CRJT_DAMPER, CRJT_ANGLE, CRJT_VELOCITY, CRJT_ACCELERATION, CRJT_TORQUE
	};

	// ���鎞���ɂ�����֐߂̏�ԁi�܂��͖ڕW�l�j�������\����
	struct CRJointTimeSlice {
		// �Ή�����{�[���i�P�Ȃ�f�[�^�Ƃ��Ďg�������ꍇ��NULL�ł������j
		CRBoneIf* bone;

		// ����
		double time;

		// �ǂ̕ϐ��Ƀf�[�^�������Ă��邩�������t���O
		bool enable[6];

		// �o�l�W���̕W���l�ɑ΂���䗦
		double springRatio;

		// �_���p�W���̕W���l�ɑ΂���䗦
		double damperRatio;
	};

	// -- �q���W�W���C���g�̏ꍇ
	struct CRHingeJointTimeSlice : CRJointTimeSlice {
		// �p�x
		double angle;

		// �p���x
		double velocity;

		// �p�����x
		double acceleration;

		// �g���N
		double torque;
	};

	// -- �{�[���W���C���g�̏ꍇ
	struct CRBallJointTimeSlice : CRJointTimeSlice {
		// �p��
		Quaterniond orientation;

		// �p���x
		Vec3d velocity;

		// �p�����x
		Vec3d acceleration;

		// �g���N
		Vec3d torque;
	};

	// ----- ----- ----- ----- -----

	// �֐߂̏W���ɑ΂���JointTimeSlice
	// �i�֐߂̏W���F�@�S�g��A�̂̈ꕔ�Ȃǁj
	struct CRJointsTimeSlice {
		// �e�֐߂��Ƃ�TimeSlice�f�[�^
		std::vector<CRJointTimeSlice> jointTimeSlice;
	};

	// JointsTimeSlice�̎��n��f�[�^
	struct CRJointsTimeSeries {
		std::vector<CRJointsTimeSlice> jointsTimeSlice;
	};

	// ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- ----- -----

	// CRSolidTimeSlice�̂ǂ̕ϐ��Ƀf�[�^�������Ă��邩�������t���O�̎w��Ɏg��
	enum CRSolidTimeSliceFlag {
		CRST_POSE, CRST_VELOCITY, CRST_ACCELERATION, CRST_SPRING, CRST_DAMPER
	};

	// ���鎞���ɂ����鍄�̂̏�ԁi�܂��͖ڕW�l�j�������\����
	struct CRSolidTimeSlice {
		// �Ή�����{�[���i�P�Ȃ�f�[�^�Ƃ��Ďg�������ꍇ��NULL�ł������j
		CRBoneIf* bone;

		// ����
		double time;

		// �ǂ̕ϐ��Ƀf�[�^�������Ă��邩�������t���O
		bool enable[5];

		// �ʒu�E�p��
		Posed pose;

		// ���x�E�p���x
		Vec6d velocity;

		// �����x�E�p�����x
		Vec6d acceleration;

		// ���PD�����P�W���̕W���l�ɑ΂���䗦
		double springRatio;

		// ���PD�����D�W���̕W���l�ɑ΂���䗦
		double damperRatio;
	};

	// ----- ----- ----- ----- -----

	// ���̂̏W���ɑ΂���SolidTimeSlice
	// �i���̂̏W���F�@�S�g��A�̂̈ꕔ�Ȃǁj
	struct CRSolidsTimeSlice {
		// �e���̂��Ƃ�TimeSlice�f�[�^
		std::vector<CRSolidTimeSlice> solidTimeSlice;
	};

	// SolidsTimeSlice�̎��n��f�[�^
	struct CRSolidsTimeSeries {
		std::vector<CRSolidsTimeSlice> solidsTimeSlice;
	};

}

#endif//SPR_CRTIMESERIESIF_H