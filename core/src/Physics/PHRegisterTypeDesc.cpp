﻿/*
 *  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
#include <Foundation/UTTypeDesc.h>
#include <Physics/PHSdk.h>

namespace Spr{ 
extern void RegisterTypeDescCollision(UTTypeDescDbIf* db);
extern void RegisterTypeDescPhysics(UTTypeDescDbIf* db);

void SPR_CDECL PHRegisterTypeDescs(){
	static bool bFirst=true;
	if (!bFirst) return;
	bFirst = false;
	UTRegisterTypeDescs();
	UTTypeDescDbIf* db = UTTypeDescDbPool::Get("Physics");
	assert(db);
	RegisterTypeDescCollision(db);
	RegisterTypeDescPhysics(db);
	db->RegisterAlias("PHConstraintDesc", "PHJointDesc");
	db->Link();
	UTTypeDescDbIf* fdb = UTTypeDescDbPool::Get("Foundation");
	db->Link(fdb);
	db->LinkCheck();
}
}
