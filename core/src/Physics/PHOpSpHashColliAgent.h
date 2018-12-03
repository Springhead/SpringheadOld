﻿#ifndef PHOPSPHASHCOLLIAGENT_H
#define PHOPSPHASHCOLLIAGENT_H


#include <Foundation/Object.h>
#include <Physics/SprPHOpSpHashAgent.h>
#include <Collision/SprCDSpHash.h>
#include <Collision/CDSpatialHashTable.h>
#include "Physics/PHOpEngine.h"

namespace Spr{;

struct solvedColliPair{
	int cOInd1, cOInd2;
	int cPInd1, cPInd2;
};

class PHOpSpHashColliAgent: public SceneObject, public PHOpSpHashColliAgentDesc{
public :
	SPR_OBJECTDEF(PHOpSpHashColliAgent);


	UTRef<CDSpatialHashTable> spTable;
	PHSceneIf* scene;
	PHOpEngineIf* opengIf;
	PHOpEngine* opEngine;
	int objNum;
	int timeStamp;

	
	bool enableCollision;
	
	std::vector<Vec3f> pPCtcPs;
	std::vector<Vec3f> pPCtcPs2;
	std::vector<Vec3f> pPCtcPs3;
	std::vector<Vec3f> pPCtcPs4;
	std::vector<Vec3f> PlanePosList;
	std::vector<Vec3f> PlaneNorList;

	//flags
	bool colliCheckedBySphash;
	bool useHapticDevice;
	int solveCount;
	bool useDebugInfo;

	PHOpSpHashColliAgent(const PHOpSpHashColliAgentDesc& desc = PHOpSpHashColliAgentDesc(), SceneIf* s = NULL) :PHOpSpHashColliAgentDesc(desc)
	{
		colliCheckedBySphash = false;
		objNum = 0;
		timeStamp = 0;
		useDebugInfo = true;
		useHapticDevice = false;
		enableCollision = false;
		collisionCstrStiffness = 1.0f;
		SetScene(s);
	}

	Vec3f GetFirContactPosition(int firId);
	Vec3f GetSecContactPosition(int secId);

	void SetCollisionCstrStiffness(float alpha);
	float GetCollisionCstrStiffness();
	void EnableCollisionDetection(bool able = true);
	void Initial(float cellSize, CDBounds  bounds);
	void SetDebugMode(bool flag);
	bool GetDebugMode();
	bool IsCollisionEnabled();
	void OpDirCollision();
	void SetIsDirCollision(bool flag);
	bool GetIsDirCollision();
	void AddContactPlane(Vec3f planeP, Vec3f planeN);
	void ClearDebugData();
	void UpdateSceneInfo();
	void OpCollisionProcedure();
	void OpCollisionProcedure(int myTimeStamp);
	void ReducedSpHashColliCheck();
	void spHashColliPlane();
	void spHashColliContact(int objIndex1, int ptclindex1, int objIndex2, int ptclindex2, Vec3f &linkVec);
	void EllipColliInit();
	void pctlColliSolve(int objIndex1, int ptclindex1, int objIndex2, int ptclindex2, Vec3f &ctc1, Vec3f &ctc2);
	Vec3f getCtcP_PvP(Vec3f &vectorN, Matrix3f &ellipA1tmp, Matrix3f &ellipA2tmp, float &d, float& lamdaP);
	//Vec3f getConterCtcP_PvP(Vec3f &vectorN, Matrix3f &ellipA1tmp, Matrix3f &ellipA2tmp);

};

}
#endif
