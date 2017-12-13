/*
 *  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
/**
 *	@file SprHILeap.h
 *	@brief Leapmotion
*/

#ifndef HI_LEAPIF_H
#define HI_LEAPIF_H

#include <HumanInterface/SprHISkeletonSensor.h>

namespace Spr{;
/**	\addtogroup	gpHumanInterface	*/
//@{

/**	@brief Leapmotion�̃C���^�t�F�[�X */
struct HILeapIf: public HISkeletonSensorIf{
	SPR_IFDEF(HILeap);
};

/**	@brief Leapmotion�̃f�X�N���v�^ */
struct HILeapDesc{
	SPR_DESCDEF(HILeap);

	HILeapDesc() {
	}
};

/** @brief LeapmotionUDP�̃C���^�[�t�F�[�X */
struct HILeapUDPIf: public HISkeletonSensorIf{
	SPR_IFDEF(HILeapUDP);
	bool calibrate(int formerLeapID);
};

/** @brief LeapmotionUDP�̃f�X�N���v�^ */
struct HILeapUDPDesc{
	SPR_DESCDEF(HILeapUDP);

	HILeapUDPDesc() {
	}
};

//@}
}
#endif
