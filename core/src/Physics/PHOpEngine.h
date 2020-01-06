/*
*  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team
*  All rights reserved.
*  This software is free software. You can freely use, distribute and modify this
*  software. Please deal with this software under one of the following licenses:
*  This license itself, Boost Software License, The MIT License, The BSD License.
*/
#ifndef PHOPENGINE_H
#define PHOPENGINE_H


#include <SprDefs.h>
  #undef CreateDialog
  #undef CreateFile
  #undef GetObject
  #undef min
  #undef max
// end

#include <Physics/PHOpDecompositionMethods.h>
#include "Physics/PHOpHapticController.h"
#include "Physics/PHEngine.h"
#include "Physics/PHOpObj.h"
#include "Physics/PHOpHapticRenderer.h"
#include "Physics/PHOpAnimation.h"
#include "Physics/PHSoftSkin.h"

namespace Spr{
	;

	class PHOpEngine : public PHEngine
	{
	public:
		SPR_OBJECTDEF(PHOpEngine);
		//時間微分
		double fdt;
		//opオブジェクト配列
		std::vector<PHOpObj*> opObjs;
		//ObjIdの計数
		int objidIndex;
		//描画する粒子の半径係数
		float radiusCoe;

		UTRef<PHOpAnimation> opAnimator;	//	To avoid memory leak

		int opIterationTime;

		TQuaternion<float> winPose;

		bool subStepProFix;
		bool subStepProSolve;
		bool logForce;
		bool useAnime;

		UTRef<PHSoftSkin> softSkin;

		//proxy
		int noCtcItrNum;
		PHOpHapticRenderer* opHpRender;
		PHOpHapticController *myHc;
		bool useHaptic;
		bool useSoftSkin;

		PHOpEngine();
		int  GetPriority() const {
			return SGBP_NONE;
		}
		void SetIterationCount(int count);
		int GetIterationCount();
		void Step();

		void SetGravity(bool gflag);
		virtual bool AddChildObject(ObjectIf* o);
		virtual bool DelChildObject(ObjectIf* o);
		void SetTimeStep(double dt);
		double GetTimeStep();
		int GetOpObjNum(){ return(int)opObjs.size(); }
		PHOpObjDesc* GetOpObj(int i);
		void StepWithBlend();
		int  AddOpObj();
		PHOpObjIf* GetOpObjIf(int obji);
		void HapticProcedure_3DOF();
		void HapticProcedure_6DOF();
		void Initial6DOFHapticRenderer(int objId);
		void SetUseHaptic(bool hapticUsage);
		bool GetUseHaptic();
		
		void SetHapticSolveEnable(bool enable);
		bool IsHapticSolve();
		void SetProxyCorrectionEnable(bool enable);
		bool IsProxyCorrection();
		void Initial3DOFHapticRenderer();

		ObjectIf* GetOpHapticController();
		ObjectIf* GetOpHapticRenderer();
		ObjectIf* GetOpAnimator();
		void SetUpdateNormal(bool flag);
		bool IsUpdateNormal(int obji);
		void SetAnimationFlag(bool flag);
		bool GetAnimationFlag();
		void SetDrawPtclR(float r);
		float GetDrawPtclR();
		void SetUseSoftSkin(bool flag);
		bool GetUseSoftSkin();
		ObjectIf* GetSoftSkin();

		void SetCurrentCameraOritation(TQuaternion<float> orit);
		TQuaternion<float> GetCurrentCameraOrientation();
	};

}
#endif
