/*
*  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team
*  All rights reserved.
*  This software is free software. You can freely use, distribute and modify this
*  software. Please deal with this software under one of the following licenses:
*  This license itself, Boost Software License, The MIT License, The BSD License.
*/
#ifndef PHOPHAPTICRENDERER_H
#define PHOPHAPTICRENDERER_H

#include <Foundation/Object.h>
#include <Physics/PHOpHapticController.h>
#include <Collision/CDCollisionFunctions.h>
#include <map>

namespace Spr
{;

class PHOpHapticRenderer :public SceneObject, public PHOpHapticRendererDesc
	{
	SPR_OBJECTDEF(PHOpHapticRenderer);
	public :
		ACCESS_DESC(PHOpHapticRenderer);
		
		PHOpHapticController* myHc;
		std::vector<Vec3f> ctcPPosList;
		std::vector<Vec3f> ctcPNorList;

		std::vector<PHOpObj*>* opObjs;
		
		std::vector<std::map<int, std::vector<int> > > objEdgeInfos;
		std::vector<std::map<int, std::vector<int> > > objVtoFInfos;

		int animeTimeLine;
		bool useProxyPopOut;
		int popOutNum;
		

		struct proxySolveItror
		{
			std::vector<PHOpHapticController::ConstrainPlaneInfo*> constrainIs;
		
		}slvItr;

		struct DisCmpPtoPbyV
		{

			int pIndex;
			int vIndex;
			float distance;
			bool cmpdis(const DisCmpPtoPbyV &a, const DisCmpPtoPbyV &b)
			{
				return a.distance<b.distance;
			}
			bool operator < (const DisCmpPtoPbyV &a)const
			{
				return (distance < a.distance);
			}
		};

		PHOpHapticRenderer(const PHOpHapticRendererDesc& desc = PHOpHapticRendererDesc()) : PHOpHapticRendererDesc(desc)
		
		{
			hitWall = false;
			rigid = false;
			toUserVCSpring = 1.0f;
			toObjVCSpring = 1.0f;
			constraintSpring = 1.0f;
			useIncreaseMeshMove = false;
			useConstrainForce = false;
			useProxyfixSubitr = false;
			useDualTranFix = false;
			timeStep = 0.01f;
			currDtType = -1;
			noCtcItrNum = 0;
			proxyItrtNum = 0;
			proxyItrtMaxNum = 3;
			subStepProSolve = true;
			useProxyPopOut = true;
		}
		void SetRigid(bool set)
		{
			rigid = set;
			if (rigid)
			{
				if (myHc != NULL)
					myHc->hcObj->isRigid = rigid;
			}
		}
		bool IsRigid()
		{
			return rigid;
		}

		void initial3DOFRenderer(PHOpHapticController* hc, std::vector<PHOpObj*>* objs)
		{
			myHc = hc;
			opObjs = objs;
			forceOnRadius = 0.3f;
			objNum = (int)(*opObjs).size();
			//BuildVToFaceRelation();
			//BuildEdgeInfo();
		}
		void initial6DOFRenderer(PHOpHapticController* hc, std::vector<PHOpObj*>* objs)
		{
			myHc = hc;
			opObjs = objs;
			forceOnRadius = 0.3f;
			objNum = (int)(*opObjs).size();
			
		}

		void HapticProxyProcedure();
		void PruneNonPositiveTriangles();
		int HpProxyPopOut();
		void HapticProxySolveOpt(Vec3f currSubStart);
		bool new_intersectOnRouteUseShrink(Vec3f currSubStart, Vec3f currSubGoal, Vec3f &newSubStart, Vec3f &newSubGoal, PHOpHapticController::ConstrainPlaneInfo &cpinfo, bool inverseF, bool sameCheck);
		void HpForceMoment();
		void HpProxyNoCtcRecord2();
		void SeriousNoCtcProxyCCD3();

		void setForceOnRadius(float r)
		{
			forceOnRadius = r;
		}
		void SetForceSpring(float k)
		{
			toObjVCSpring = k;
		}
		float GetForceSpring()
		{
			return toObjVCSpring;
		}
		void SetConstraintSpring(float k)
		{
			constraintSpring = k;
		}
		float GetConstraintSrping()
		{
			return constraintSpring;
		}
		
	};
}

#endif
