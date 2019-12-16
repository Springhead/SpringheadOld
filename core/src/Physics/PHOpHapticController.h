/*
*  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team
*  All rights reserved.
*  This software is free software. You can freely use, distribute and modify this
*  software. Please deal with this software under one of the following licenses:
*  This license itself, Boost Software License, The MIT License, The BSD License.
*/
#ifndef PHOPHAPTICCONTROLLER_H
#define PHOPHAPTICCONTROLLER_H

#include <Foundation/Object.h>
#include <Physics/PHOpObj.h>
#include <sstream>

namespace Spr {
	;

#define TriAId 2
#define TriBId 1
#define TriCId 0
#define ParallelBigForceProblemScalarThreshold 3
#define ParallelBigForceProblemThreshold 400.0f
#define ProxyPopOutPopLittleOverCoeff 1.001f
#define ProxyPopOutRangeScalarCoeff 2.01f
#define ProxyPopOutPopMinimumCoeff 0.02f

	class PHOpHapticController: public SceneObject, public PHOpHapticControllerDesc
	{
	public:
		PHOpObj* hcObj;
		PHOpHapticController(const PHOpHapticControllerDesc& desc = PHOpHapticControllerDesc()): PHOpHapticControllerDesc(desc)
		{
			max_output_force = 6.0f;
			IsSetForceReady = false;
			ProxySolveDetectionSize = 2;
			SolveShrinkRadio = 0.999f;
			sameCstrInside = false;
			OutputForceLimit = 10.0f;
		}
		~PHOpHapticController()
		{
			if (logForceFile) fclose(logForceFile);
			if (logPosFile) fclose(logPosFile);
			if (logPPosFile) fclose(logPPosFile);
		}

		SPR_OBJECTDEF(PHOpHapticController);
		ACCESS_DESC(PHOpHapticController);

		
		std::vector<PvsHcCtcPInfo> hcColliedPs;
		std::vector<int> suspFaceIndex;
		SpatialVector outForce;
		
		FILE *logForceFile;//Force
		FILE *logPPosFile;//proxy pos
		FILE *logPosFile;//particle pos
		FILE *logUPosFile;//user pos
		float max_output_force;
		float ProxySolveDetectionSize;
		float SolveShrinkRadio;
		std::vector<int> surrCnstrList;
		Vec3f hcFixProxystart;
		bool sameCstrInside;
		float hcNoCtcDtcRadius;
		

		struct ConstrainPlaneInfo{
			ConstrainPlaneInfo()
			{

			}
			bool isSameCstr(ConstrainPlaneInfo& a)
			{
				if (this->cstType != a.cstType) return false;

				if (this->objid != a.objid) return false;

				if (this->cstType == cstrainType::cstFace)
				{
					if (this->planeid == a.planeid)
					{
						return true;
					}
					else return false;
				}
				else if (this->cstType == cstrainType::cstEdge)
				{
					if (((this->edgeidA == a.edgeidA) && (this->edgeidB == a.edgeidB)) || ((this->edgeidA == a.edgeidB) && (this->edgeidB == a.edgeidA)))
					{
						return true;
					}
					else return false;
				}
				else if (this->cstType == cstrainType::cstPoint)
				{
					if (this->vid == a.vid)
					{
						return true;
					}
					else return false;
				}

				return false;
			}

			ConstrainPlaneInfo& operator = (const ConstrainPlaneInfo &a)
			{
				this->cstType = a.cstType;
				this->edgeidA = a.edgeidA;
				this->edgeidB = a.edgeidB;
				this->objid = a.objid;
				this->planeid = a.planeid;
				this->planeN = a.planeN;
				this->planeP = a.planeP;
				this->vid = a.vid;
				this->fu = a.fu;
				this->fv = a.fv;
				this->fw = a.fw;
				this->segmentt = a.segmentt;
				this->routet = a.routet;
				return *this;


			}

			ConstrainPlaneInfo(const ConstrainPlaneInfo  & a)
			{
				this->cstType = a.cstType;
				this->edgeidA = a.edgeidA;
				this->edgeidB = a.edgeidB;
				this->objid = a.objid;
				this->planeid = a.planeid;
				this->planeN = a.planeN;
				this->planeP = a.planeP;
				this->vid = a.vid;
				this->fu = a.fu;
				this->fv = a.fv;
				this->fw = a.fw;
				this->segmentt = a.segmentt;
				this->routet = a.routet;
			}
			
			int vid;
			int edgeidA;
			int edgeidB;
			int planeid;
			int objid;
			cstrainType cstType;
			Vec3f planeN;
			Vec3f planeP;
			Vec3f goalP;
			float fv, fu, fw, segmentt, routet;
		};
		
		ConstrainPlaneInfo hcBindCpi;
		
		std::vector<ConstrainPlaneInfo> cpiVec;
		std::vector<ConstrainPlaneInfo> cpiHpVec;
		std::vector<ConstrainPlaneInfo> cpiLastHpVec;
		std::vector<int> sameIdArr;
		std::vector<int> sameLIdArr;
		

		//for new HC
		
		SpatialVector GetHCOutput();


	
		
		bool InitialHapticController(PHOpObj* opObjectif);
		bool InitialHapticController();
		
		void LogForce(TQuaternion<float> winPose);
		bool CheckProxyState();
		void SetHCColliedFlag(bool flag);
		
		void AddColliedPtcl(int pIndex, int objindex, Vec3f ctcPos);
		PHOpParticle* GetMyHpProxyParticle();
		bool BeginLogForce();
		void EndLogForce();
		void ClearColliedPs();
		void setC_ObstacleRadius(float r);
		int GetHpObjIndex();
		ObjectIf* GetHpOpObj();
		bool SetForce(Vec3f f, Vec3f t);
		
		void SetHCForceReady(bool flag);
		bool GetHCForceReady();
		void SetHCReady(bool flag);
		bool GetHCReady();
		Vec3f GetHCPosition();
		void SetHCPosition(Vec3f pos);
		void SetHCPose(Posef pose);
		Posef GetHCPose();
		Vec3f Get3DoFProxyPosition()
		{
			return hcObj->objPArr[0].pCurrCtr;
		}
		
		Vec3f GetUserPosition()
		{
			return userPos;
		}
		
		void SetUserPose(Vec3f &pos, Vec3f &rot)
		{
			userPos = pos;
			//userPose = ;
		}
		float GetC_ObstacleRadius()
		{
			return c_obstRadius;
		}
		Vec3f GetCurrentOutputForce();
		void SetManualMode(bool flag)
		{
			isManual = flag;
		}
		bool GetManualMode()
		{
			return isManual;
		}
		
	};
	static bool  HasIinArr(int checki, int* arr, int Num)
	{
		for (int i = 0; i < Num; i++)
			if (checki == arr[i]) return true;

		return false;
	}
}//namespace
#endif
