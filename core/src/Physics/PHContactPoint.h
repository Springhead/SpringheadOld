﻿/*
 *  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
#ifndef PHCONTACTPOINT_H
#define PHCONTACTPOINT_H

#include <Physics/PHConstraint.h>

namespace Spr{;

class PHShapePairForLCP;

struct PHContactPointState:public PHConstraintState{
	int shapePair;
	Vec3d pos;
};

class PHContactPoint : public PHConstraint{
public:
	SPR_OBJECTDEF(PHContactPoint);

	PHShapePairForLCP* shapePair;
	Posed  pose;
	double mu0, mu, e;
	double spring, damper;

	double fx, flim0, flim;
	bool   isStatic;

	Vec3d  velField;  ///< contact motor velocity (in local coord)

public:
	/// コンストラクタ
	PHContactPoint(){}
	PHContactPoint(const Matrix3d& local, PHShapePairForLCP* sp, Vec3d p, PHSolid* s0, PHSolid* s1);

	// ----- PHConstraintの派生クラスで実装する機能
	virtual void CompBias();
	virtual void CompError();
	virtual bool Projection(double& f_, int i);
	virtual bool ProjectionCorrection(double& F, int k);
};

}

#endif
