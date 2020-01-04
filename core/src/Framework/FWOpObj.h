﻿/*
*  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team
*  All rights reserved.
*  This software is free software. You can freely use, distribute and modify this
*  software. Please deal with this software under one of the following licenses:
*  This license itself, Boost Software License, The MIT License, The BSD License.
*/
#ifndef FWOPOBJ_H
#define FWOPOBJ_H


#include <Framework/SprFWOpObj.h>
#include <Framework/FWObject.h>
#include "FrameworkDecl.hpp"
#include <Graphics/GRMesh.h>
#include <Physics/PHOpObj.h>
namespace Spr{ ;

class FWOpObj: public FWObject{
	SPR_OBJECTDEF(FWOpObj);
public :
	UTRef<GRMesh> grMesh;
	UTRef<PHOpObj> opObj;
	float fwPSize;
	int fwPLinkNum;

	FWOpObj(const FWOpObjDesc& d = FWOpObjDesc());

	//GRMeshから、Opオブジェクトを作る
	void CreateOpObj();
	//頂点をGraphicsに反映する
	void Blend();
	void Sync();
	void CreateOpObjWithRadius(float r, int pLinkNum = -1);
	///	子オブジェクトの数
	virtual size_t NChildObject() const;
	///	子オブジェクトの取得
	virtual ObjectIf* GetChildObject(size_t pos);
	///	子オブジェクトの追加
	virtual bool AddChildObject(ObjectIf* o);
	ObjectIf* GetOpObj();
	ObjectIf* GetGRMesh();
};

}
#endif
