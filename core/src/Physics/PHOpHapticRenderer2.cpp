///*
//*  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team
//*  All rights reserved.
//*  This software is free software. You can freely use, distribute and modify this
//*  software. Please deal with this software under one of the following licenses:
//*  This license itself, Boost Software License, The MIT License, The BSD License.
//*/
//#include "Physics/PHOpHapticRenderer.h"
//#include "Collision\CDCollisionFunctions.h"
//
//#define USE_a_little_over_InSolve
//#define USE_a_little_over_InUctcFix
//#define ProxyFixInCORadius
//#define USE_GLOBLE_COLLI
//#define Old_Functions
//#define new_ProxyFunctions
//#define CHECK_INF_ERR
//#define USE_ShrinkReturn
//#define PROPOSE_PROXYCORRECTION
////#define USE_PruneNegtiveFacesPop
//#define ProxyCCDLittleOverCoeff 1.0001f
//#define SMALL_AS_ZERO 1e-7
//
//namespace Spr
//{
//	;
//
//
//	using namespace std;
//
//
//	void solveNt(Vec3f a0, Vec3f a1, Vec3f b0, Vec3f b1, Vec3f c0, Vec3f c1, Vec3f &tsqrCoeff, Vec3f &tlinCoeff, Vec3f &cstCoeff)
//	{
//		Vec3f va = a1 - a0;
//		Vec3f vb = b1 - b0;
//		Vec3f vc = c1 - c0;
//
//		float vBAxd = (vb.x - va.x);
//		float vBAyd = (vb.y - va.y);
//		float vBAzd = (vb.z - va.z);
//		float vCAxd = (vc.x - va.x);
//		float vCAyd = (vc.y - va.y);
//		float vCAzd = (vc.z - va.z);
//
//		float _0BAxd = b0.x - a0.x;
//		float _0BAyd = b0.y - a0.y;
//		float _0BAzd = b0.z - a0.z;
//		float _0CAxd = c0.x - a0.x;
//		float _0CAyd = c0.y - a0.y;
//		float _0CAzd = c0.z - a0.z;
//
//		float _1BAxd = b1.x - a1.x;
//		float _1BAyd = b1.y - a1.y;
//		float _1BAzd = b1.z - a1.z;
//		float _1CAxd = c1.x - a1.x;
//		float _1CAyd = c1.y - a1.y;
//		float _1CAzd = c1.z - a1.z;
//
//		tsqrCoeff.x = (vBAyd*vCAzd - vBAzd*vCAyd);
//		tsqrCoeff.y = (vBAzd*vCAxd - vBAxd*vCAzd);
//		tsqrCoeff.z = (vBAxd*vCAyd - vBAyd*vCAxd);
//
//		tlinCoeff.x = (_0BAyd*vCAzd + _0CAzd*vBAyd - _0BAzd*vCAyd - _0CAyd*vBAzd);
//		tlinCoeff.y = (_0BAzd*vCAxd + _0CAxd*vBAzd - _0BAxd*vCAzd - _0CAzd*vBAxd);
//		tlinCoeff.z = (_0BAxd*vCAyd + _0CAyd*vBAxd - _0BAyd*vCAxd - _0CAxd*vBAyd);
//
//		cstCoeff.x = (_0BAyd*_0CAzd - _0BAzd*_0CAyd);
//		cstCoeff.y = (_0BAzd*_0CAxd - _0BAxd*_0CAzd);
//		cstCoeff.z = (_0BAxd*_0CAyd - _0BAyd*_0CAxd);
//	}
//
//	bool SolveProxyCCDt(Vec3f fa0, Vec3f fb0, Vec3f fc0, Vec3f fa1, Vec3f fb1, Vec3f fc1, Vec3f &p, double &t, double c_obstacle)
//	{
//		bool hasRoot = false;
//
//		//how many distinct roots defines rootType, rootType 4 for one real two complex roots
//		int rootType = -1;
//
//		Vec3f tcubCoeff, tsqrCoeff, tlinCoeff, tCstCoeff;
//		solveNt(fa0, fa1, fb0, fb1, fc0, fc1, tsqrCoeff, tlinCoeff, tCstCoeff);
//
//
//		//solve AP*N = 0
//		Vec3f va = fa1 - fa0;
//		Vec3f vb = fb1 - fb0;
//		Vec3f vc = fc1 - fc0;
//		tcubCoeff.x = -(va.x)*tsqrCoeff.x;
//		tcubCoeff.y = -(va.y)*tsqrCoeff.y;
//		tcubCoeff.z = -(va.z)*tsqrCoeff.z;
//
//		float pax = p.x - fa0.x;
//		float pay = p.y - fa0.y;
//		float paz = p.z - fa0.z;
//		tsqrCoeff.x = tsqrCoeff.x * pax + tlinCoeff.x * (-va.x);
//		tsqrCoeff.y = tsqrCoeff.y * pay + tlinCoeff.y * (-va.y);
//		tsqrCoeff.z = tsqrCoeff.z * paz + tlinCoeff.z * (-va.z);
//
//		tlinCoeff.x = tlinCoeff.x * pax + tCstCoeff.x * (-va.x);
//		tlinCoeff.y = tlinCoeff.y * pay + tCstCoeff.y * (-va.y);
//		tlinCoeff.z = tlinCoeff.z * paz + tCstCoeff.z * (-va.z);
//
//		tCstCoeff.x = tCstCoeff.x * pax;
//		tCstCoeff.y = tCstCoeff.y * pay;
//		tCstCoeff.z = tCstCoeff.z * paz;
//
//		//see discriminant
//		double a = tcubCoeff.x + tcubCoeff.y + tcubCoeff.z;
//		double b = tsqrCoeff.x + tsqrCoeff.y + tsqrCoeff.z;
//		double c = tlinCoeff.x + tlinCoeff.y + tlinCoeff.z;
//		double d = tCstCoeff.x + tCstCoeff.y + tCstCoeff.z;
//
//		//add c_objstacle
//		//d -= c_obstacle;
//
//		if (fabs(a) < SMALL_AS_ZERO)
//		{//degrade to quadratic equation
//			if (fabs(b) < SMALL_AS_ZERO)
//			{//degrade to linear equation
//				if (fabs(c) < SMALL_AS_ZERO)
//				{//not moved..
//					return false;
//				}
//
//				rootType = 1;
//				t = -d / c;
//#ifdef DEBUG_PROXYCCD
//				DSTR << "linear equation root" << endl;
//#endif
//
//				if ((t <= 1.) && (t>0))
//				{
//					return true;
//				}
//				else  return false;
//			}
//			else
//			{//b^2 -4ac
//			 //-b +- sqrt(dlt)/2a
//
//				double dlt = c*c - 4 * b *d;
//				if (dlt < 0) {
//#ifdef DEBUG_PROXYCCD
//					DSTR << "No solution for quad!" << endl;
//#endif
//					return false;
//				}
//				if (dlt >0)rootType == 2;
//				if (dlt == 0)rootType == 1;
//
//				double C1 = (-c + sqrt(dlt)) / (2 * b);
//				double C2 = (-c - sqrt(dlt)) / (2 * b);
//#ifdef DEBUG_PROXYCCD
//				DSTR << "Quadratic equation root" << endl;
//#endif
//				if ((C1 > 0) && (C1 <= 1.))
//				{
//					t = C1;
//					if ((C2 > 0) && (C2 <= 1.) && (C1 > C2))
//					{
//						t = C2;
//						return true;
//					}
//					return true;
//				}
//				else if ((C2 > 0) && (C2 <= 1.))
//				{
//					t = C2;
//					return true;
//				}
//				int u = 0;
//				return false;
//
//			}
//		}
//
//
//		//dlt = 18abcd - 4b^3d + b^2c^2 - 4ac^3 - 27a^2d^2
//		//if dlt >0 there are three distinct real roots
//		//if dlt =0 there is a multiple root and all of its roots are real
//		//if dlt <0 there is one real root and two complex conjugate roots
//		double dlt = 18. * a*b*c*d - 4. * b*b*b*d + b*b*c*c - 4. * a*c*c*c - 27. * a*a*d*d;
//
//		//by cubic equation formula
//		//d0 = b^2 - 3ac
//		//d1 = 2b^3 - 9abc + 27a^2d
//		//C = (d1 -+sqrt(-27a^2*dlt) * 0.5)^(1/3)
//		//also we can use dlt by 
//		double d0 = b * b - 3. * a *c;
//		double d1 = 2. * b*b*b - 9. * a*b*c + 27. * a*a*d;
//		double C1, C2, C3;
//
//		if ((0 == d0) && (0 == d1))
//		{//If both Δ and Δ0 are equal to 0, then the equation has a single root (which is a triple root):
//		 // -b / 3a
//			rootType = 1;
//			C1 = (-b) / (3. * a);
//		}
//
//		if ((0 == d0) && (0 != d1))
//		{//If Δ = 0 and Δ0 ≠ 0, then there are both a double root,and a simple root,
//			rootType = 2;
//			C1 = (9. * a * d - b*c) / (2. * d0);
//			C2 = (4. * a*b*c - 9. * a*a*d - b*b*b) / (a*d0);
//		}
//
//		if (dlt > 0)
//		{//Trigonometric solution for three real roots
//		 //substituting x = t - (b)/3a
//		 // p = (3ac - b^2 )/ 3a^2
//		 // q = (2b^3 - 9abc + 27a^2d)/ 27a^3
//		 //t_k = 2 * sqrt((-p)/3)cos(1/3arccos((3q)/2p * sqrt((-3)/p))-(2PI*k)/3), for k =0,1,2
//			rootType = 3;
//			double p = (3. * a*c - b*b) / (3. * a*a);
//			double q = (2. * b*b*b - 9. * a*b*c + 27. * a*a*d) / (27. * a*a*a);
//			double t_0 = 2. * sqrt((-p) / 3.)
//				* cos(1. / 3. * acos((3.*q) / (2.*p) * sqrt(-3. / p)));
//			//double t_0 = 2. * sqrt((-p) / 3.)
//			//	* cos(1. / 3. * acos((3.*q) / 2.*p * sqrt(-3. / p)) - (2.*PI) / 3.);
//			//	double t_0 = 2. * sqrt((-p) / 3.)
//			//		* cos(1. / 3. * acos((3.*q) / 2.*p * sqrt(-3. / p)) - (2.*PI*2.) / 3.);
//			q = -q;
//			double t_1 = -2. * sqrt((-p) / 3.)
//				* cos(1. / 3. * acos((3.*q) / (2.*p) * sqrt(-3. / p)));
//			double t_2 = -t_0 - t_1;
//
//			C1 = t_0 - b / (3.*a);
//			C2 = t_1 - b / (3.*a);
//			C3 = t_2 - b / (3.*a);
//		}
//		else if (dlt < 0)
//		{// When there is only one real root(and p ≠ 0), it may be similarly represented using hyperbolic functions,
//			rootType = 4;
//			/*double p = (3. * a*c - b*b) / 3. * a*a;
//			double q = (2. * b*b*b - 9. * a*b*c + 27. * a*a*d) / 27. * a*a*a;
//			double t_0;
//			assert(p != 0);
//			if ((p < 0) && ((4 * p*p*p + 27 * q *q)>0))
//			{
//			t_0 = -2 * fabs(q) / q * sqrt((-p) / 3.)*cosh(1. / 3.*acosh((-3.*fabs(q)) / 2 * p * sqrt((-3.) / p)));
//			}
//			else if (p > 0)
//			{
//			t_0 = -2 * sqrt(p / 3.)*sinh(1. / 3.*asinh(3.*q / 2.*p * sqrt(3. / p)));
//			}
//			else{
//			DSTR << "What?!" << endl;
//			return false;
//			}
//			C1 = t_0 - b / 3.*a;*/
//
//			//other ways to solve rootType4
//			//x_0 = -1/(3a)(b + C + d0/C)
//			double C = cbrt((d1 + sqrt(d1*d1 - 4. * pow(d0, 3))) / 2.);
//			C1 = -1. / (3.*a)*(b + C + d0 / C);
//		}
//
//
//		if (rootType == 1)
//		{
//			if ((C1 > 0) && (C1 < 1.))
//			{
//#ifdef DEBUG_PROXYCCD
//				DSTR << "One triple root" << endl;
//#endif
//				t = C1;
//				return true;
//			}
//		}
//		else if (rootType == 2)
//		{
//			if ((C1 > 0) && (C1 < 1.))
//			{
//				if ((C2 > 0) && (C2 < 1.))
//				{
//#ifdef DEBUG_PROXYCCD
//					DSTR << "rootType =2, Two avaliable root!" << endl;
//#endif
//					if (C1 >C2) t = C2;
//					else t = C1;
//					return true;
//				}
//
//				t = C1;
//				return true;
//			}
//			else if ((C2 > 0) && (C2 < 1.))
//			{
//#ifdef DEBUG_PROXYCCD
//				DSTR << "rootType =2, One avaliable root!" << endl;
//#endif
//				t = C2;
//				return true;
//			}
//			else {
//#ifdef DEBUG_PROXYCCD
//				DSTR << "rootType = 2, No solution " << endl;
//#endif
//			}
//		}
//		else if (rootType == 3)
//		{
//			int avaRootNum = 0;
//			if ((C1 > 0) && (C1 < 1.))
//			{
//				t = C1;
//				avaRootNum++;
//			}
//			if ((C2 > 0) && (C2 < 1.))
//			{
//
//				t = C2;
//				avaRootNum++;
//			}
//			if ((C3 > 0) && (C3 < 1.))
//			{
//
//				t = C3;
//				avaRootNum++;
//			}
//
//			switch (avaRootNum) {
//			case 0:
//#ifdef DEBUG_PROXYCCD
//				DSTR << "rootType =3, No solution " << endl;
//#endif
//				return false;
//				break;
//#ifdef DEBUG_PROXYCCD
//			case 1: DSTR << "rootType =3, One avaliable root!" << endl;
//				break;
//			case 2: DSTR << "rootType =3, Two avaliable root!" << endl;
//				break;
//			case 3: DSTR << "rootType =3, Three avaliable root!" << endl;
//				break;
//#endif
//			}
//
//			return true;
//
//		}
//		else if (rootType == 4)
//		{
//			if ((C1 > 0) && (C1 < 1.))
//			{
//#ifdef DEBUG_PROXYCCD
//				DSTR << "One real root" << endl;
//#endif
//				t = C1;
//				return true;
//			}
//		}
//
//
//		return false;
//	}
//
//
//	void PHOpHapticRenderer::HapticProxyProcedure()
//	{
//		/*if (!useMultirate)
//			if (playRecordedHI)
//			{
//				DSTR << "playRecordorderid " << playRecordorderid << endl;
//				HapticInteractionsPlayBackStep();
//				playRecordorderid++;
//			}*/
//
//		PHOpParticle *hdp = myHc->GetMyHpProxyParticle();
//
//
//		if (!manualModel)
//		{
//
//
//			animeTimeLine = 0;
//			//#ifndef HAPTICRATE
//			//if (!useMultirate)
//				//myHc->userPos = GetCurrentWin()->GetTrackball()->GetPose().Ori() *  spgpos * myHc->posScale;
//			//#else
//			if (useMultirate)
//				myHc->userPos = myHc->hcCurrUPos;
//			//#endif
//
//
//		}
//		//	mtHapticFix.startMyTimer();
//		//	mtHapticFix.pauseMyTimer();
//
//		//if (!myHc->CheckProxyState())
//		{
//			
//
//			if (useProxyPopOut) {
//				//触っていない時のproxyfix
//				noCtcItrNum = 0;
//
//				PruneNonPositiveTriangles();
//
//
//				//mtHpProxyCCD.startMyTimer();
//				SeriousNoCtcProxyCCD3();
//				//mtHpProxyCCD.pauseMyTimer();
//
//				//mtHpNoCtcCCD.pauseMyTimer();
//				myHc->hcFixProxystart = hdp->pCurrCtr;
//				//mtHpProxyPopOut.startMyTimer();
//#ifdef USE_PruneNegtiveFacesPop
//				//if (!useAdaptiveProxy)
//				//{
//				//	popOutNum = HpProxyOnlyPush(); //popOutNum = HpProxyPopOutUsePruneList();
//				//}
//				//else {
//				//	popOutNum = AdaptiveProxyPopOut();
//				//}
//				/*if (popOutNum == 0)
//				{
//					HpProxyOnlyPush();
//				}*/
//#else
//				popOutNum = HpProxyPopOut();
//#endif
//				//mtHpProxyPopOut.endMyTimer();
//				
//
//			}
//
//		}
//		
//
//
//#ifdef COLLI_TIME
//		mtHaptic.startMyTimer();
//#endif
//
//
//		//HpCtcSolveOnProxy();
//		if (subStepProSolve)
//		{
//			//haptic解決
//			//HpProxyCtcSolve(myHc->GetMyHpProxyParticle()->pCurrCtr);
//			//mtHapticSolve.startMyTimer();
//#ifdef PrintInfoColliSolve
//			DSTR << "StartHapticSolve" << endl;
//#endif
//			HapticProxySolveOpt(myHc->GetMyHpProxyParticle()->pCurrCtr);
//			//HapticProxySolveOptWithForceShading(myHc->GetMyHpProxyParticle()->pCurrCtr);
//			//HapticProxySolveOptWithFS_Friction(myHc->GetMyHpProxyParticle()->pCurrCtr);
//			//mtHapticSolve.endMyTimer();
//			//HpProxyCtcSolve();
//
//		}
//		//	mtHapticFix.endMyTimer();//end after the recoding local coordinates
//
//		if (!myHc->CheckProxyState())
//		{
//
//			hdp->pNewCtr = myHc->userPos;
//
//			//hdp->pNewOrint = myHc->currSpg->GetPose().Ori().Inv();
//
//		}
//
//
//#ifdef COLLI_TIME
//		mtHaptic.endMyTimer();
//		cout << "constrainSolve time" << endl;
//		mtHaptic.printElastedTime();
//#endif
//
//		//haptic移動速度計算する
//
//		//hdp->pVelocity = (myHc->userPos - hdp->pNewCtr) / myHc->params.timeStep;//not good define, use penetration instead
//		myHc->_3dofProxyPenetration = myHc->userPos - hdp->pNewCtr;
//
//		//if (useHpMoment)
//		{
//			//haptic force and torque calculation
//
//			HpForceMoment();
//			//HpApplyHpForceOnProxyCstrPs();
//			//HpHapticForceOnCstrDir();
//			//HpHapticForceOnCstrDirWithInDirect();
//		}
//
//
//		//for No contact Proxy pop out
//		//myHc->ClearProxyPOData();
//
//		if (useProxyPopOut)
//		{
//			//mtHpProxyCCD.restartMyTimer();
//			//if (!myHc->CheckProxyState())
//
//			//HpProxyNoCtcRecord();
//			HpProxyNoCtcRecord2();
//			//mtHpProxyCCD.endMyTimer();
//		}
//	}
//
//	void PHOpHapticRenderer::PruneNonPositiveTriangles()
//	{
//		Vec3f& proxyPos = myHc->GetMyHpProxyParticle()->pCurrCtr;
//		for (int obji = 0; obji < objNum; obji++)
//		{
//			PHOpObj &obj = *(*opObjs)[obji];
//			obj.triListForProxyCCD.clear();
//			int faceNum = obj.objMeshFaces.size();
//
//			for (int fi = 0; fi < faceNum; fi++)
//			{
//				Vec3f lasta = obj.lastTargetVts[obj.objMeshFaces[fi].indices[2]];
//				Vec3f lastb = obj.lastTargetVts[obj.objMeshFaces[fi].indices[1]];
//				Vec3f lastc = obj.lastTargetVts[obj.objMeshFaces[fi].indices[0]];
//
//				if ((proxyPos - lasta).dot(cross(lastb - lasta, lastc - lasta)) > 0)
//				{
//					obj.triListForProxyCCD.push_back(fi);
//				}
//			}
//		}
//
//
//	}
//
//	void PHOpHapticRenderer::HpProxyNoCtcRecord2()
//	{
//		float detectRadius = myHc->hcNoCtcDtcRadius;
//		for(int obji = 0; obji < objNum; obji++)
//		{
//			if (obji == myHc->GetHpObjIndex())continue;
//
//			PHOpObj &obj = *(*opObjs)[obji];
//
//			if (!::memcpy_s(obj.lastTargetVts, obj.objMeshVtsNum * sizeof(Vec3f), obj.objMeshVts, obj.objMeshVtsNum * sizeof(Vec3f)))
//			{
//
//			}
//			else
//			{
//				cout << "error in Record vertex memcpy!" << endl;
//			}
//
//		}
//	}
//
//	void PHOpHapticRenderer::HpForceMoment()
//	{
//
//		MatrixExtension ma;
//		//Force calculation
//		PHOpParticle	*hdp = myHc->GetMyHpProxyParticle();
//		int insideCount;
//		//PHOpObj *myobj = &dfmObj[0];
//		PHOpObj *myobj;
//		if (myHc->hcProxyOn)
//		{
//			myobj = (*opObjs)[myHc->cpiVec[0].objid];
//		}
//		else myobj = (*opObjs)[0];
//		std::vector<DisCmpPtoPbyV> disCmpQue;
//		//std::vector<int> corrPtcl;
//		DisCmpPtoPbyV tmpdcp;
//		vector<float> vWeights;
//
//		int applyForcePNum = 25;
//
//		int appliedNum = 0;
//		if (myHc->CheckProxyState())
//		{
//
//			//old approach: calculate closest particles
//			for (int pi = 0; pi < myobj->assPsNum; pi++)
//			{
//				PHOpParticle* gdp = &myobj->objPArr[pi];
//
//				/*for (int suspi = 0; suspi<myHc->hcColliedPs.size(); suspi++)
//				{*/
//				//for (int vi = 0; vi<myobj->objPArr[myHc->hcColliedPs[suspi].ptclIndex].pNvertex; vi++)
//				for (int vi = 0; vi < myobj->objPArr[pi].pNvertex; vi++)
//				{
//					//Vec3f &v = tgtMesh->vertices[myobj->objPArr[myHc->hcColliedPs[suspi].ptclIndex].pVertArr[vi]];
//					Vec3f &v = myobj->objMeshVts[myobj->objPArr[pi].pVertArr[vi]];
//
//					float dist = fabs((myHc->GetMyHpProxyParticle()->pNewCtr - v).norm());
//					//if (dist<(myHc->c_obstRadius * 5))
//					if (dist < (forceOnRadius))
//					{
//
//
//						tmpdcp.distance = dist;
//						tmpdcp.pIndex = pi;
//						tmpdcp.vIndex = vi;//ここは頂点のidです
//						disCmpQue.push_back(tmpdcp);
//
//						//corrPtcl.push_back(myHc->hcColliedPs[suspi].ptclIndex);
//						//corrPtcl.push_back(pi);
//
//					}
//				}
//			}
//
//			//when alpha = 1 solve
//			//if (dfmObj[0].params.alpha == 1.0f)
//			//{
//			//	//std::sort(disCmpQue.begin(),disCmpQue.end());
//			//	if (disCmpQue.size() < 1)
//			//		return;
//			//	Vec3f pMove = hdp->pVelocity *disCmpQue[0].distance;
//			//	float deltT = dfmObj[0].params.timeStep;
//			//	for (int j = 0; j < dfmObj[0].assPsNum; j++)
//			//	{
//			//		PHOpParticle *cdp = &dfmObj[0].objPArr[j];
//			//		cdp->pExternalForce += pMove;// / (deltT * deltT) * cdp-> pTempSingleVMass;
//			//	}
//			//	return;
//			//}
//
//
//			std::sort(disCmpQue.begin(), disCmpQue.end());
//			//erase particles not connected to the nearest
//			auto itr = disCmpQue.begin();
//			int itrI = 0;
//
//			for (int di = 0; di < disCmpQue.size(); di++)
//			{
//				int checkid = disCmpQue[di].pIndex;
//				bool isLinked = false;
//				PHOpGroup &pg = myobj->objGArr[disCmpQue[0].pIndex];
//				for (int pli = 0; pli < pg.gNptcl; pli++)
//				{
//					if (pg.gPInd[pli] == checkid)
//					{
//						isLinked = true;
//					}
//				}
//
//				if (!isLinked)
//				{
//					itr = disCmpQue.erase(itr);
//					di--;
//				}
//				else itr++;
//
//			}
//			//erase particles more than we want "applyForcePNum"
//			insideCount = disCmpQue.size();
//
//			if (applyForcePNum > insideCount)
//			{
//				applyForcePNum = insideCount;
//			}
//			itr = disCmpQue.begin();
//			itrI = 0;
//
//			for (int it = 0; it < applyForcePNum; it++)
//			{
//				itr++;
//			}
//			for (int it = applyForcePNum; it < insideCount; it++)
//			{
//				itr = disCmpQue.erase(itr);
//			}
//
//
//
//			//match face
//			vector<Vec3f> moves;
//			//float totalMovement = (closestP - hdp->pNewCtr).norm();///////////////////debug
//			float totalMovement = myHc->_3dofProxyPenetration.norm();
//			Vec3f moveNormal = myHc->_3dofProxyPenetration.unit();
//			if (totalMovement == 0.0f)
//				return;
//
//			//weight calculation
//			float totalDis = 0.0f;
//			//for (int vsi = 0; vsi < insideCount; vsi++)
//			for (int vsi = 0; vsi < applyForcePNum; vsi++)
//			{
//				totalDis += disCmpQue[vsi].distance;
//			}
//
//			int testFloat0 = 0;
//			float tsttotalMove = 0.0f;
//			float weightTotal = 0.0f;
//			totalDis = 1.0f / totalDis;
//
//			for (int vsi = 0; vsi < applyForcePNum; vsi++)
//			{
//				float weight = (disCmpQue[vsi].distance * totalDis);
//				vWeights.push_back(weight);
//
//				////template consider: use projection direction for moving verts
//				//moves.push_back(moveNormal * (totalMovement * weight));
//				//tsttotalMove += moves[vsi].norm();
//				weightTotal += 1.0f / weight;
//			}
//			//original
//			for (int vsi = 0; vsi < applyForcePNum; vsi++)
//			{
//				moves.push_back(moveNormal * (totalMovement * (1.0f / vWeights[vsi]) / weightTotal));
//				tsttotalMove += moves[vsi].norm();
//			}
//			////proposal: push same force
//			//for (int vsi = 0; vsi < insideCount; vsi++)
//			//{
//			//	moves.push_back(moveNormal * totalMovement / insideCount);
//			//}
//
//			//Here we don't need move the vertex -> to move the Particle
//			//Calculate force by these moves
//			Vec3f pMove, pRotate;
//
//
//			//movedVerticesNum = applyForcePNum;
//
//
//			for (int vsi = 0; vsi < applyForcePNum; vsi++)
//			{
//				PHOpParticle *cdp = &myobj->objPArr[disCmpQue[vsi].pIndex];
//				//cdp->isForcedByHaptic = true;
//				//int plocalind = cdp->getVertexLclIndex(disCmpQue[vsi].pIndex);
//				int plocalVid = disCmpQue[vsi].vIndex;
//				if (plocalVid != -1)
//				{
//
//					//Local plausible surface regeneration 
//					//displacement
//					if (sqrtAlphaForce)
//						pMove = moves[vsi];// *(1 - sqrt(dfmObj[cdp->pObjId].params.alpha));
//					else pMove = moves[vsi];//  *(1 - dfmObj[cdp->pObjId].params.alpha);
//											//		pMove = moves[vsi] * (1 - sqrt(cdp->pParaAlpha));
//											//	else pMove = moves[vsi] * (1 - cdp->pParaAlpha);
//
//											//angularVelocity
//											//Vec3f &vPosition = dfmObj[cdp->pObjId].targetMesh->vertices[disCmpQue[vsi].pIndex];
//											//pRotate += cdp->pInverseOfMomentInertia 
//											//	* me.VectorCross((vPosition - cdp->pCurrCtr),moves[vsi]) 
//											//	* dfmObj[cdp->pObjId].params.timeStep;
//
//				}
//				else DSTR << "GtoL index Error" << endl;
//				if (!(pMove.x == pMove.x) || !(pMove.y == pMove.y) || !(pMove.z == pMove.z))
//				{
//					int u = 0;
//					DSTR << "pMove not a number Error!" << endl;
//				}
//				if (_isnan(pMove.x) == 1 || _isnan(pMove.y) == 1 || _isnan(pMove.z) == 1)
//				{
//					int u = 0;
//					DSTR << "pMove not a number Error!" << endl;
//				}
//				//Delayed Force based
//				//float deltT = dfmObj[cdp->pObjId].params.timeStep;
//
//
//				if (!useConstrainForce)
//				{
//
//					cdp->pExternalForce += toObjVCSpring * pMove;// *(deltT * deltT) / cdp->pTempSingleVMass;
//															   //cdp->pExternalForce = forceSpring * pMove;// / myHc->posScale;// / (deltT * deltT) * cdp->pTempSingleVMass / (deltT * deltT) * cdp->pTempSingleVMass;
//															   //cdp->pExternalForce += forceSpring * pMove;//罠です、although f = kx, but k here is not a spring
//
//					int u = 0;
//				}
//				
//			}
//		}
//	}
//
//	void PHOpHapticRenderer::SeriousNoCtcProxyCCD3()
//	{
//		Vec3f &userPoint = myHc->userPos;
//
//		Vec3f newProxyPosByTriFace;
//		Vec3f newProxyPosByTriEorV;
//		Vec3f toProxyRoute;
//		Vec3f currFaceN, lastFaceN, closP, movN;
//		float movD;
//		bool contactWithFace = false;
//
//		float littleOverPopOut = 0.0001f;
//
//		float c_objstacle =  myHc->c_obstRadius;
//
//		float smallestCCDt = 10.0f;
//		float smallestCCDt2 = 10.0f;
//		float closestDist = 1000.0f;
//
//		for(int obji = 0; obji < objNum; obji++)
//		{
//			PHOpObj &obj = *(*opObjs)[obji];
//
//			//unsigned int faceNum = tgtMesh->NFace();
//			unsigned int faceNum = obj.triListForProxyCCD.size();
//
//			//for (unsigned int fii = 0; fii < faceNum; fii++)
//			for (unsigned int ofi = 0; ofi < faceNum; ofi++)
//			{
//				unsigned int faceq1 = 2; unsigned int faceq3 = 0;
//				double CCDt;
//
//				Vec3f& currfpa = obj.objMeshVts[obj.objMeshFaces[obj.triListForProxyCCD[ofi]].indices[faceq1]];
//				Vec3f& currfpb = obj.objMeshVts[obj.objMeshFaces[obj.triListForProxyCCD[ofi]].indices[1]];
//				Vec3f& currfpc = obj.objMeshVts[obj.objMeshFaces[obj.triListForProxyCCD[ofi]].indices[faceq3]];
//
//
//				Vec3f& lastfpa = obj.lastTargetVts[obj.objMeshFaces[obj.triListForProxyCCD[ofi]].indices[faceq1]];
//				Vec3f& lastfpb = obj.lastTargetVts[obj.objMeshFaces[obj.triListForProxyCCD[ofi]].indices[1]];
//				Vec3f& lastfpc = obj.lastTargetVts[obj.objMeshFaces[obj.triListForProxyCCD[ofi]].indices[faceq3]];
//
//				//use distance with current vertex
//				/*if (isClose(currfpa, ProxyPosition, detectRadius)
//				|| isClose(currfpb, ProxyPosition, detectRadius)
//				|| isClose(currfpc, ProxyPosition, detectRadius))
//				*/
//				//
//				//
//#ifdef INVERSE_TRIANGLE_NORMAL
//				currfaceN = cross(currfpc - currfpa, currfpb - currfpa);
//#else 
//				currFaceN = cross(currfpb - currfpa, currfpc - currfpa);
//#endif
//				currFaceN.unitize();
//
//				//cull by positive half-space
//				//if ((myHc->GetMyHpProxyParticle()->pCurrCtr - lastfpa).dot(lastFaceN) < 0)continue;// this is nolonger needed since we use triListForProxyCCD
//
//				////cull by non penetration filters (Tang.M 2010), only check two signs
//				if ((myHc->GetMyHpProxyParticle()->pCurrCtr - currfpa).dot(currFaceN) > 0)continue;
//
//
//
//				//use distance with vertex motion
//				//	Vec3f closPinA, closPinB, closPinC;
//				//	float st;
//				//	ClosestPtPointSegment(ProxyPosition, lastfpa, currfpa, st, closPinA);
//				//	ClosestPtPointSegment(ProxyPosition, lastfpb, currfpb, st, closPinB);
//				//	ClosestPtPointSegment(ProxyPosition, lastfpc, currfpc, st, closPinC);
//
//				//	if (isClose(closPinA, ProxyPosition, detectRadius)
//				//		|| isClose(closPinB, ProxyPosition, detectRadius)
//				//		|| isClose(closPinC, ProxyPosition, detectRadius))
//				{
//
//					// test by CCD and solve t
//#ifdef DEBUG_PROXYCCD
//					DSTR << endl;
//					DSTR << "for face " << ofi << " ";
//#endif
//					//testSolveCount++;
//					if (SolveProxyCCDt(lastfpa, lastfpb, lastfpc, currfpa, currfpb, currfpc, myHc->GetMyHpProxyParticle()->pCurrCtr, CCDt, c_objstacle))
//					{
//						Vec3f tfpa = lastfpa + (currfpa - lastfpa)* CCDt;
//						Vec3f tfpb = lastfpb + (currfpb - lastfpb)* CCDt;
//						Vec3f tfpc = lastfpc + (currfpc - lastfpc)* CCDt;
//
//#ifdef DEBUG_PROXYCCD
//						DSTR << "t =" << CCDt << endl;
//#endif
//
//						bool inside = false;
//						int region = -1;
//						float wb, wc;
//
//
//						//find in triangle faces
//						Vec3f closP = CollisionFunctions::ClosestPtoTriangle(myHc->GetMyHpProxyParticle()->pCurrCtr, tfpa, tfpb, tfpc, inside, region, wb, wc);
//
//
//						if (inside)
//						{//contact in triangle
//
//
//							if (CCDt > smallestCCDt)continue;
//							smallestCCDt = CCDt;
//							contactWithFace = true;
//
//
//
//
//							//myHc->GetMyHpProxyParticle()->pCurrCtr = currfpa + (currfpb - currfpa) * wb + (currfpc - currfpa)* wc + faceN * c_objstacle;
//							newProxyPosByTriFace = currfpa + (currfpb - currfpa) * wb + (currfpc - currfpa)* wc + currFaceN * c_objstacle *ProxyCCDLittleOverCoeff;
//#ifdef DEBUG_PROXYCCD_DRAW
//							DA.AddTempDrawLine(tfpb, tfpa);
//							DA.AddTempDrawLine(tfpa, tfpc);
//							DA.AddTempDrawLine(tfpc, tfpb);
//
//							DA.AddTempDrawLine(lastfpb, lastfpa);
//							DA.AddTempDrawLine(lastfpa, lastfpc);
//							DA.AddTempDrawLine(lastfpc, lastfpb);
//
//							DA.AddTempDrawLine(lastfpb, currfpb);
//							DA.AddTempDrawLine(lastfpa, currfpa);
//							DA.AddTempDrawLine(lastfpc, currfpc);
//
//							DA.AddTempDrawLine(currfpa, currfpb);
//							DA.AddTempDrawLine(currfpc, currfpa);
//							DA.AddTempDrawLine(currfpb, currfpc);
//							DA.AddTempDrawFont3D(currfpb, "Fc");
//							DA.AddTempDrawFont3D(tfpb, "Ft");
//							DA.AddTempDrawFont3D(lastfpb, "Fl");
//							string dfi = "F" + to_string(ofi);
//							DA.AddTempDrawFont3D((currfpb + currfpa + currfpc) / 3.0f, dfi);
//							DA.AddTempDrawBall(myHc->GetMyHpProxyParticle()->pCurrCtr, myHc->c_obstRadius*0.01f);
//							DA.AddTempDrawFont3D(myHc->GetMyHpProxyParticle()->pCurrCtr, dfi);
//#endif
//						}
//						else {
//							float dist = fabs((closP - myHc->GetMyHpProxyParticle()->pCurrCtr).norm());
//
//							if (dist < c_objstacle) {
//								// contact in edge or vertex move
//								if (dist < closestDist)
//								{
//									closestDist = dist;
//
//									if (CCDt > smallestCCDt2)continue;
//									smallestCCDt2 = CCDt;
//
//									movD = c_objstacle - dist;
//									movN = (myHc->GetMyHpProxyParticle()->pCurrCtr - closP).unit();
//
//									newProxyPosByTriEorV = myHc->GetMyHpProxyParticle()->pCurrCtr + movN * movD;
//								}
//
//								//myHc->objPArr[0].pCurrCtr = closP + (ProxyPosition - closP).unit() * c_objstacle;
//								//ProxyPosition = closP + (ProxyPosition - closP).unit() * c_objstacle;
//#ifdef DEBUG_PROXYCCD_DRAW
//								DA.AddTempDrawLine(tfpb, tfpa);
//								DA.AddTempDrawLine(tfpa, tfpc);
//								DA.AddTempDrawLine(tfpc, tfpb);
//
//								DA.AddTempDrawLine(lastfpb, lastfpa);
//								DA.AddTempDrawLine(lastfpa, lastfpc);
//								DA.AddTempDrawLine(lastfpc, lastfpb);
//
//								DA.AddTempDrawLine(lastfpb, currfpb);
//								DA.AddTempDrawLine(lastfpa, currfpa);
//								DA.AddTempDrawLine(lastfpc, currfpc);
//
//								DA.AddTempDrawLine(currfpa, currfpb);
//								DA.AddTempDrawLine(currfpc, currfpa);
//								DA.AddTempDrawLine(currfpb, currfpc);
//								//	DA.AddTempDrawFont3D(currfpb, "EorVcurrfpb");
//								//	DA.AddTempDrawFont3D(tfpb, "EorVtfpb");
//								//	DA.AddTempDrawFont3D(lastfpb, "EorVlastfpb");
//								string dfi = "EV" + to_string(ofi);
//								DA.AddTempDrawFont3D((currfpb + currfpa + currfpc) / 3.0f, dfi);
//								DA.AddTempDrawBall(newProxyPosByTriEorV, myHc->c_obstRadius*0.01f);
//
//								DA.AddTempDrawFont3D(newProxyPosByTriEorV, dfi);
//
//
//#endif				
//							}
//						}
//
//					}
//
//				}
//
//
//			}
//		}
//
//		if (contactWithFace) {
//			if (smallestCCDt < 10) {
//
//				myHc->GetMyHpProxyParticle()->pCurrCtr = newProxyPosByTriFace;
//			}
//
//		}
//		else
//		{
//			if (smallestCCDt2 < 10) {
//				myHc->GetMyHpProxyParticle()->pCurrCtr = newProxyPosByTriEorV;
//			}
//		}
//
//
//
//	}
//
//
//	int PHOpHapticRenderer::HpProxyPopOut()
//	{
//
//		MatrixExtension ma;
//		float c_objst = myHc->c_obstRadius;
//		float move_a_little_over = c_objst * ProxyPopOutPopLittleOverCoeff;
//		float move_minimum = c_objst * ProxyPopOutPopMinimumCoeff;
//
//		myHc->surrCnstrList.clear();
//		myHc->surrCnstrList.reserve(10000);
//		//myHc->surrCnstrRegionList.clear();
//		myHc->sameCstrInside = false;
//
//		int itrNum = 0;
//		int maxitrNum;// = 100;
//		if (useProxyfixSubitr)
//			maxitrNum = 2000;
//		else maxitrNum = 2;//use odd number
//		Vec3f fixProxyStart = myHc->hcFixProxystart;
//		Vec3f closestP, movN, dyFaceNormal;
//		bool closeOnlyinVorE = true;
//		bool proxyPopouted = false;
//		float st;
//
//		PHOpParticle	*hdp = myHc->GetMyHpProxyParticle();
//		for(int obji = 0; obji <opObjs->size(); obji++)
//		{
//			myHc->surrCnstrList.clear();
//			PHOpObj *myobj = (*opObjs)[obji];
//			unsigned int faceNum = myobj->objMeshFaces.size();// tgtMesh->NFace();
//			//float c_obsSqure = c_objst * c_objst;
//			float checkRadius = c_objst *ProxyPopOutRangeScalarCoeff;// *1.01f; //towards round-off error//large because fixed proxy may fall //with 1.0f will have fall
//																	 //float checkRadius = c_objst; 
//
//																	 //collect potential faces
//			int triRegion = -1;
//			bool insideFlag = false;
//			for (unsigned int ofi = 0; ofi < faceNum; ofi++)
//			{
//
//				Vec3f &fpa = myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[TriAId]];
//				Vec3f &fpb = myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[TriBId]];
//				Vec3f &fpc = myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[TriCId]];
//
//				//detect those face to us
//#ifdef INVERSE_TRIANGLE_NORMAL
//				Vec3f faceN = cross(fpc - fpa, fpb - fpa);
//#else
//				Vec3f faceN = cross(fpb - fpa, fpc - fpa);
//#endif
//
//				if (faceN.dot(fpa - fixProxyStart) > 0)
//				{
//					continue;
//				}
//
//
//				Vec3f closP = CollisionFunctions::ClosestPtoTriangle(fixProxyStart, fpa, fpb, fpc, insideFlag, triRegion);
//
//				if (CollisionFunctions::isClose(closP, fixProxyStart, checkRadius))
//				{
//					myHc->surrCnstrList.push_back(ofi);
//
//					if (triRegion == 0) closeOnlyinVorE = false;
//					//#ifdef DrawProxyPopOut
//					//				dyFaceNormal = cross(fpb - fpa, fpc - fpa);
//					//				dyFaceNormal.unitize();
//					//				dyFaceNormal = dyFaceNormal * c_objst;
//					//
//					//				DA.AddTempDrawLine(fpa, fpb);
//					//				DA.AddTempDrawLine(fpa, fpc);
//					//				DA.AddTempDrawLine(fpc, fpb);
//					//
//					//				DA.AddTempDrawLine(fpa + dyFaceNormal, fpb + dyFaceNormal);
//					//				DA.AddTempDrawLine(fpa + dyFaceNormal, fpc + dyFaceNormal);
//					//				DA.AddTempDrawLine(fpc + dyFaceNormal, fpb + dyFaceNormal);
//					//#endif
//
//
//				}
//
//			}
//
//			float movL;
//#ifdef DrawProxyPopOut
//			Vec3f drawStart = fixProxyStart;
//#endif
//
//			do {
//#ifdef PrintProxyPopUpInfo
//				DSTR << "InsidePopOutNum: " << myHc->surrCnstrList.size() << endl;
//
//#endif
//				bool fallin = false;
//				bool udatedInsideFlag = false;
//				int updatedRegion;
//
//				//we first check in triangle case, edge and vertex case is solved if no fall in triangle face
//				for (int isoi = 0; isoi < myHc->surrCnstrList.size(); isoi++)
//				{
//					int ofi = myHc->surrCnstrList[isoi];
//					Vec3f &fpa = myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[TriAId]];
//					Vec3f &fpb = myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[TriBId]];
//					Vec3f &fpc = myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[TriCId]];
//
//#ifdef PrintProxyPopUpInfo
//					DSTR << "for tri " << ofi << endl;
//#endif
//#ifdef DrawProxyPopOut
//					drawStart = fixProxyStart;
//#endif
//#ifdef INVERSE_TRIANGLE_NORMAL
//					dyFaceNormal = cross(fpc - fpa, fpb - fpa);
//#else
//					dyFaceNormal = cross(fpb - fpa, fpc - fpa);
//#endif
//					dyFaceNormal.unitize();
//
//					//float projC = ((fpa + dyFaceNormal* move_a_little_over) - fixProxyStart).dot(dyFaceNormal);
//					float projC = ((fpa + dyFaceNormal*c_objst) - fixProxyStart).dot(dyFaceNormal);
//					if (projC > 0)
//					{
//
//						closestP = CollisionFunctions::ClosestPtoTriangle(fixProxyStart, fpa, fpb, fpc, udatedInsideFlag, updatedRegion);
//
//
//
//						if (closeOnlyinVorE)
//						{
//							//closeOnlyinVorE = false;//for checking loop
//
//							fallin = true;
//
//							bool largeMove = false;
//							if ((fpa - fixProxyStart).dot(dyFaceNormal) > 0)
//							{//Large move need
//								largeMove = true;
//							}
//
//
//							if (checkRadius > c_objst)
//							{
//
//								if (!CollisionFunctions::isClose(closestP, fixProxyStart, c_objst))
//								{
//									fallin = false;
//									continue;
//								}
//							}
//
//							if (updatedRegion < 10)
//							{//in Vertex
//								if (updatedRegion == 1)
//								{
//									if (largeMove)
//									{
//										movN = (fpa - fixProxyStart).unit();
//										movL = move_a_little_over + fabs((fixProxyStart - fpa).norm());
//									}
//									else {
//										movN = (fixProxyStart - fpa).unit();
//										movL = move_a_little_over - fabs((fixProxyStart - fpa).norm());
//									}
//
//								}
//								else if (updatedRegion == 2)
//								{
//									if (largeMove)
//									{
//										movN = (fpb - fixProxyStart).unit();
//										movL = move_a_little_over + fabs((fixProxyStart - fpb).norm());
//									}
//									else {
//										movN = (fixProxyStart - fpb).unit();
//										movL = move_a_little_over - fabs((fixProxyStart - fpb).norm());
//									}
//								}
//								else if (updatedRegion == 3)
//								{
//									if (largeMove)
//									{
//										movN = (fpc - fixProxyStart).unit();
//										movL = move_a_little_over + fabs((fixProxyStart - fpc).norm());
//									}
//									else {
//										movN = (fixProxyStart - fpc).unit();
//										movL = move_a_little_over - fabs((fixProxyStart - fpc).norm());
//									}
//								}
//							}
//							else
//							{//in Edge
//								if (updatedRegion == 12)
//								{
//									CollisionFunctions::ClosestPtPointSegment(fixProxyStart, fpa, fpb, st, closestP);
//								}
//								else if (updatedRegion == 13)
//								{
//									CollisionFunctions::ClosestPtPointSegment(fixProxyStart, fpa, fpc, st, closestP);
//								}
//								else if (updatedRegion == 23)
//								{
//									CollisionFunctions::ClosestPtPointSegment(fixProxyStart, fpb, fpc, st, closestP);
//								}
//								if (largeMove)
//								{
//									movN = (closestP - fixProxyStart).unit();
//									movL = move_a_little_over + fabs((fixProxyStart - closestP).norm());
//								}
//								else {
//									movN = (fixProxyStart - closestP).unit();
//									movL = move_a_little_over - fabs((fixProxyStart - closestP).norm());
//								}
//							}
//
//
//							if (movL < move_minimum)
//							{
//								//	cout << "Too small Move " << endl;
//								movL = move_minimum;// *100;
//							}
//
//							fixProxyStart += movN * movL;
//							proxyPopouted = true;
//						}
//
//						else if (0 == updatedRegion)
//						{
//
//							fallin = true;
//							if ((fpa - fixProxyStart).dot(dyFaceNormal) > 0)
//							{//case fall in mesh -- large move
//							 //is it really should be solved?
//
//								movN = (closestP - fixProxyStart).unit();
//								movL = move_a_little_over + fabs((closestP - fixProxyStart).norm());
//
//								if (movL < move_minimum)
//								{
//									//		cout << "Too small Move " << endl;
//									movL = move_minimum;// *100;
//								}
//
//								fixProxyStart += movN * movL;
//								proxyPopouted = true;
//#ifdef PrintProxyPopUpInfo
//								DSTR << "Large Move " << endl;
//#endif
//
//							}
//							else {
//								movN = (fixProxyStart - closestP).unit();
//								movL = move_a_little_over - fabs((fixProxyStart - closestP).norm());
//
//								if (movL < move_minimum)
//								{
//									//	cout << "Too small Move " << endl;
//									movL = move_minimum;// *100;
//								}
//
//								fixProxyStart += movN * movL;
//								proxyPopouted = true;
//#ifdef PrintProxyPopUpInfo
//								if (movL < 0) DSTR << "minus move?" << endl;
//#endif
//							}
//						}
//
//#ifdef DrawProxyPopOut
//						DA.AddTempDrawLine(drawStart, fixProxyStart);
//						drawStart = fixProxyStart;
//#endif
//					}
//
//
//				}
//
//#ifdef PrintProxyPopUpInfo
//				if (!fallin)
//				{
//					float differDistace = fabs((fixProxyStart - myHc->hcFixProxystart).norm());
//					if (differDistace > checkRadius)
//					{
//						DSTR << "move too much!!" << differDistace << endl;
//					}
//				}
//#endif
//
//
//				if (itrNum > maxitrNum || !fallin)
//				{
//					//#ifdef PRINT_PC_ITR
//#ifdef PrintProxyPopUpInfo
//					DSTR << "PMitrNum " << itrNum << endl;
//#endif
//					//#endif
//					break;
//				}
//
//				itrNum++;
//
//			} while (1);
//		}
//		if (proxyPopouted)
//		{
//			if (itrNum > maxitrNum)
//			{
//				DSTR << "PMOverMaxitrNum " << itrNum << endl;
//
//			}
//
//
//			myHc->hcFixProxystart = fixProxyStart;
//			hdp->pCurrCtr = myHc->hcFixProxystart;// +counterPlane * overDist;
//			hdp->pNewCtr = hdp->pCurrCtr;
//			return itrNum;
//		}
//		else return 0;
//		//	DSTR << "PMitrNum " << popOutNum << endl;
//	}
//
//
//	void PHOpHapticRenderer::HapticProxySolveOpt(Vec3f currSubStart)
//	{
//		//mPrevPrecE is because using USE_a_little_over_InSolve
//		//The magnitute of mPrevPrecE can be calculated by trigonometric function
//		//
//		//			\theta
//		//		  /|
//		//		 / | mPrevPrecE
//		//		/__|
//		//     littleOverSolve = 0.00001f
//		//
//		//Here we use Theta = 10, then we get mPrevPrecE > 0.0000567f;
//
//		unsigned int intsCounts = 0;
//		myHc->constrainCount = 0;
//		//cpiVec.clear();
//		//bool nextStepOn = false;
//		bool firStepOn = false;
//		bool secStepOn = false;
//		bool thrStepOn = false;
//		PHOpParticle	*hdp = myHc->GetMyHpProxyParticle();
//		Vec3f& currGoal = myHc->userPos;
//
//		Vec3f newSubGoal;
//		Vec3f newSubStart;
//		Vec3f nextSubGoal;
//		Vec3f nextSubStart;
//		unsigned int proxyLoopNum = 1;
//
//		vector<PHOpHapticController::ConstrainPlaneInfo>& cpiVec = myHc->cpiVec;
//		Affinef app; Vec3f look;
//
//#ifdef USE_ProxyPopOut_In_ProxySolve
//		myHc->hcFixProxystart = currSubStart;
//
//#ifdef USE_PruneNegtiveFacesPop
//		if (useAdaptiveProxy)
//			AdaptiveProxyPopOut();
//		else
//			HpProxyPopOutUsePruneList();
//#else
//		HpProxyPopOut();
//#endif
//		currSubStart = myHc->hcFixProxystart;
//#endif
//
//#ifdef PrintProxySolveCheckInfo
//		//--------------add check in face start-------
//		for(int obji = 0; obji < objNum; obji++)
//		{
//			GRMesh* tgtMesh = dfmObj[obji].targetMesh;//only for debug, one obj
//			unsigned int faceNum = tgtMesh->NFace();//only for debug, one obj
//			for (unsigned int ofi = 0; ofi < faceNum; ofi++)
//			{
//
//				Vec3f fpa =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[2]];
//				Vec3f fpb =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[1]];
//				Vec3f fpc =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[0]];
//				Vec3f faceN = (cross(fpb - fpa, fpc - fpa)).unit();
//
//
//
//
//				bool insideTri = false;
//				int regionF = -1;
//
//				Vec3f closp = ClosestPtoTriangle(currSubStart, fpa, fpb, fpc, insideTri, regionF);
//
//				if (insideTri)
//				{
//					if (!isClose(closp, currSubStart, myHc->c_obstRadius))continue;
//
//
//					float checIn = (currSubStart - (fpa + faceN * myHc->c_obstRadius)).dot(faceN);
//
//					if (checIn < 0)
//					{
//
//						DSTR << "fall in tri in beginning in" << ofi << " of obj" << obji << endl;
//
//						myHc->hcFixProxystart = currSubStart;
//						if (useAdaptiveProxy)
//							AdaptiveProxyPopOut();
//						else
//							HpProxyPopOutUsePruneList();
//						currSubStart = myHc->hcFixProxystart;
//
//
//						if (!isClose(closp, currSubStart, myHc->c_obstRadius))continue;
//
//
//						checIn = (currSubStart - (fpa + faceN * myHc->c_obstRadius)).dot(faceN);
//
//						if (checIn < 0)
//						{
//							DSTR << "fall again tri in beginning in" << ofi << " of obj" << obji << endl;
//						}
//					}
//
//				}
//			}
//		}
//		//--------------add check in face end------
//#endif
//		//draw pos before proxy solve
//		////DA.AddTempDrawBall(currSubStart, myHc->c_obstRadius*0.3f);
//		//DA.AddTempDrawFont3D(currSubStart, "bg");
//
//		unsigned int cpiNum = 0;
//		PHOpHapticController::ConstrainPlaneInfo &tmpcpinfo = cpiVec[0];
//#ifdef USE_GLOBLE_COLLI
//#ifdef USE_ShrinkReturn
//		firStepOn = new_intersectOnRouteUseShrink(currSubStart, currGoal, newSubStart, newSubGoal, tmpcpinfo, false, true);
//#else
//		firStepOn = new_intersectOnRoute(currSubStart, currGoal, newSubStart, newSubGoal, tmpcpinfo, false, true);
//		//firStepOn = intersectOnRoute(currSubStart, currGoal, newSubStart, newSubGoal, tmpcpinfo, false);
//#endif
//
//
//#else
//		firStepOn = intersectOnRouteInColliPs(currSubStart, currGoal, newSubStart, newSubGoal, tmpcpinfo, false, true);
//#endif
//
//
//
//		//DSTR<<"FirstIntSolved "<<nextStepOn<<endl;
//		myHc->couterPlaneN = tmpcpinfo.planeN;
//
//		if (firStepOn)
//		{
//
//			myHc->constrainCount = 1;
//
//			myHc->hcProxyOn = true;
//
//
//#ifdef PrintInfoColliSolve
//			DA.AddTempDrawLine(newSubStart, newSubGoal);
//			DA.AddTempDrawFont3D(newSubStart, "1st s");
//			DA.AddTempDrawFont3D(newSubGoal, "1st g");
//
//			switch (tmpcpinfo.cstType)
//			{
//			case PHOpHapticController::cstEdge:
//				DSTR << "Fir cstEdge obj" << tmpcpinfo.objid << " Edge" << tmpcpinfo.edgeidA << " " << tmpcpinfo.edgeidB << endl;
//				////DA.AddTempDrawBall(tmpcpinfo.planeP, myHc->c_obstRadius*0.5);
//				////DA.AddTempDrawFont3D(tmpcpinfo.planeP, "ec1");
//				////DA.AddTempDrawLine(tmpcpinfo.planeP, tmpcpinfo.planeP + tmpcpinfo.planeN);
//				break;
//			case PHOpHapticController::cstPoint:
//				DSTR << "Fir cstPoint obj" << tmpcpinfo.objid << " Point" << tmpcpinfo.vid << endl;
//				break;
//			case PHOpHapticController::cstFace:
//				DSTR << "Fir cstFace obj" << tmpcpinfo.objid << " Face" << tmpcpinfo.planeid << endl;
//				break;
//			default:
//				break;
//			}
//#endif
//			bool sameinside = false;
//			bool parallelDetected = false;
//
//			do {
//
//#ifdef USE_ProxyPopOut_In_ProxySolve
//				myHc->hcFixProxystart = newSubStart;
//
//#ifdef USE_PruneNegtiveFacesPop
//				if (useAdaptiveProxy)
//					AdaptiveProxyPopOut();
//				else
//					HpProxyPopOutUsePruneList();
//#else
//				HpProxyPopOut();
//#endif
//				newSubStart = myHc->hcFixProxystart;
//#endif
//
//
//#ifdef PrintInfoColliSolveProcess			
//				DSTR << "NextSubStart" << newSubStart.x << " " << newSubStart.y << " " << newSubStart.z << endl;
//				DSTR << "NextSubGoal" << newSubGoal.x << " " << newSubGoal.y << " " << newSubGoal.z << endl;
//#endif
//				PHOpHapticController::ConstrainPlaneInfo &tmpcpinfo1 = cpiVec[1];
//#ifdef PrintProxySolveCheckInfo
//				//--------------add check in face start-------
//				for(int obji = 0; obji < objNum; obji++)
//				{
//					GRMesh* tgtMesh = dfmObj[obji].targetMesh;//only for debug, one obj
//					unsigned int faceNum = tgtMesh->NFace();//only for debug, one obj
//					for (unsigned int ofi = 0; ofi < faceNum; ofi++)
//					{
//
//						Vec3f fpa =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[2]];
//						Vec3f fpb =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[1]];
//						Vec3f fpc =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[0]];
//						Vec3f faceN = (cross(fpb - fpa, fpc - fpa)).unit();
//
//
//						bool insideTri = false;
//						int regionF = -1;
//
//						Vec3f closp = ClosestPtoTriangle(newSubStart, fpa, fpb, fpc, insideTri, regionF);
//
//						if (insideTri)
//						{
//							if (!isClose(closp, newSubStart, myHc->c_obstRadius))continue;
//							float checIn = (newSubStart - (fpa + faceN * myHc->c_obstRadius)).dot(faceN);
//
//							if (checIn < 0)
//							{
//
//								DSTR << "fall in tri in second start" << ofi << " of obj" << obji << endl;
//#ifdef USE_ProxyPopOut_In_ProxySolve
//								myHc->hcFixProxystart = newSubStart;
//
//#ifdef USE_PruneNegtiveFacesPop
//								if (useAdaptiveProxy)
//									AdaptiveProxyPopOut();
//								else
//									HpProxyPopOutUsePruneList();
//#else
//								HpProxyPopOut();
//#endif
//								newSubStart = myHc->hcFixProxystart;
//#endif
//								closp = ClosestPtoTriangle(newSubStart, fpa, fpb, fpc, insideTri, regionF);
//								if (!isClose(closp, newSubStart, myHc->c_obstRadius))continue;
//								checIn = (newSubStart - (fpa + faceN * myHc->c_obstRadius)).dot(faceN);
//
//								if (checIn < 0)
//								{
//									DSTR << "fallagain in tri in second start" << ofi << " of obj" << obji << endl;
//								}
//							}
//						}
//
//						Vec3f closp2 = ClosestPtoTriangle(newSubGoal, fpa, fpb, fpc, insideTri, regionF);
//
//						if (insideTri)
//						{
//							if (!isClose(closp2, newSubGoal, myHc->c_obstRadius))continue;
//
//							float checIn = (newSubGoal - (fpa + faceN * myHc->c_obstRadius)).dot(faceN);
//
//							if (checIn < 0)
//							{
//
//								DSTR << "fall in tri in second goal in" << ofi << " of obj" << obji << endl;
//							}
//						}
//					}
//				}
//				//--------------add check in face end------
//#endif
//#ifdef USE_GLOBLE_COLLI
//#ifdef USE_ShrinkReturn
//				secStepOn = new_intersectOnRouteUseShrink(newSubStart, newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo1, false, true);
//#else
//#ifdef USE_a_little_over_InSolve
//				secStepOn = new_intersectOnRoute(newSubStart - ((newSubGoal - tmpcpinfo.planeP).unit())*mPrevPrecE, newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo1, false, true);
//#else
//				secStepOn = new_intersectOnRoute(newSubStart, newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo1, false, true);
//#endif
//#endif 
//				//secStepOn = intersectOnRoute(newSubStart - ((newSubGoal - tmpcpinfo.planeP).unit())*mPrevPrecE, newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo1, false);
//				//secStepOn = intersectOnRoute(newSubStart, newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo1, false);
//#else
//				secStepOn = intersectOnRouteInColliPs(newSubStart - ((newSubGoal - tmpcpinfo.planeP).unit())*mPrevPrecE, newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo1, false);
//#endif
//
//				//DSTR<<"NextIntSolved "<<nextStepOn<<endl;
//				sameinside = false;
//
//				if (secStepOn)
//				{
//
//
//					myHc->constrainCount = 2;
//#ifdef PrintInfoColliSolve
//					DA.AddTempDrawLine(nextSubStart, nextSubGoal);
//					DA.AddTempDrawFont3D(nextSubStart, "2nd s");
//					DA.AddTempDrawFont3D(nextSubGoal, "2nd g");
//
//					switch (tmpcpinfo1.cstType)
//					{
//					case PHOpHapticController::cstEdge:
//						DSTR << "Sec cstEdge obj" << tmpcpinfo1.objid << " Edge" << tmpcpinfo1.edgeidA << " " << tmpcpinfo1.edgeidB << " " << endl;
//						//	//DA.AddTempDrawBall(tmpcpinfo1.planeP, myHc->c_obstRadius*0.5);
//						//	//DA.AddTempDrawFont3D(tmpcpinfo1.planeP, "ec2");
//						//	//DA.AddTempDrawLine(tmpcpinfo1.planeP, tmpcpinfo1.planeP + tmpcpinfo1.planeN);
//						break;
//					case PHOpHapticController::cstPoint:
//						DSTR << "Sec cstPoint obj" << tmpcpinfo1.objid << " Point" << tmpcpinfo1.vid << " " << endl;
//
//						break;
//					case PHOpHapticController::cstFace:
//						DSTR << "Sec cstFace obj" << tmpcpinfo1.objid << " Face" << tmpcpinfo1.planeid << " " << endl;
//
//						break;
//					default:
//						break;
//					}
//
//
//
//#endif
//					for (unsigned int samei = 0; samei<myHc->constrainCount - 1; samei++)
//					{
//						if (tmpcpinfo1.isSameCstr(cpiVec[samei]))
//						{
//							sameinside = true;
//						}
//					}
//					if (sameinside)
//					{
//#ifdef PrintInfoColliSolve
//						DSTR << "same inside" << endl;
//#endif
//						myHc->constrainCount--;
//						break;
//					}
//
//
//					/*	myHc->GetMyHpProxyParticle()->pNewCtr = nextSubStart;
//					DSTR<<"pNewCtr set to nextSubStart"<<endl;*/
//
//					//------------------ OLD two cstr solve -----------------
//
//					unsigned int Nirs = 3 + myHc->constrainCount;
//					VMatrixRow< double > clms;
//					clms.resize(Nirs, Nirs);
//					clms.clear(0.0);
//					VVector< double > d;
//					d.resize(Nirs);
//					d.clear(0.0);
//					vector<int> turns; turns.resize(Nirs);
//					VVector< double > f;
//					f.resize(Nirs);
//					f.clear(0.0);
//
//					//colums with number "1"
//					for (unsigned int mi = 0; mi<3; mi++)
//					{
//						clms[mi][mi] = 1;
//					}
//
//					//make counterPlane for Proxy
//					Vec3f counterPlane;
//					for (unsigned int pbpi = 0; pbpi<myHc->constrainCount; pbpi++)
//						//for(int pbpi = 0;pbpi<pssbPlanes.size();pbpi++)
//					{
//						unsigned int objid = cpiVec[pbpi].objid;
//
//						Vec3f planeN = cpiVec[pbpi].planeN;
//						Vec3f planeP = cpiVec[pbpi].planeP;
//
//						counterPlane += planeN;
//
//						float fA = planeN.x, fB = planeN.y, fC = planeN.z;
//						float fD = -(fA * planeP.x + fB * planeP.y + fC * planeP.z);
//
//						//render->SetMaterial(GRRenderIf::RED);
//						//render->DrawLine(planeP,planeP+(planeN * 1.5));
//
//						clms[0][3 + pbpi] = fA;
//						clms[1][3 + pbpi] = fB;
//						clms[2][3 + pbpi] = fC;
//
//						clms[3 + pbpi][0] = fA;
//						clms[3 + pbpi][1] = fB;
//						clms[3 + pbpi][2] = fC;
//
//						d[3 + pbpi] = -fD;
//
//					}
//					d[0] = currGoal.x;
//					d[1] = currGoal.y;
//					d[2] = currGoal.z;
//#ifdef PrintCalInfoColliSolve
//					DSTR << "constrainPlaneMatrix proxyslove1:" << endl;
//					for (unsigned int i = 0; i<Nirs; i++)
//					{
//						for (unsigned int j = 0; j<Nirs; j++)
//							DSTR << clms[i][j] << " ";
//
//						DSTR << "* f = " << d[i] << endl;
//					}
//#endif
//					//GaussElimi::SolveGaussElimi(clms, d, Nirs, f);
//					clms.gauss(f, d, turns.data());
//
//#ifdef PrintCalInfoColliSolve
//					DSTR << "Result1 proxy solve f:" << endl;
//					for (unsigned int i = 0; i<Nirs; i++)
//					{
//
//						DSTR << " f = " << f[i];
//					}
//
//					DSTR << endl;
//#endif
//					counterPlane /= 2;
//					counterPlane.unitize();
//
//					if (f[0] == 0.0f&&f[1] == 0.0f&&f[2] == 0.0f)
//					{
//						//parallel plane detected use only one 
//#ifdef PrintInfoBigForce
//						DSTR << "parallel detected! proxy solve 1" << endl;
//#endif
//						myHc->constrainCount = 1;
//						parallelDetected = true;
//
//
//						break;
//
//					}
//					else {
//						Vec3f couterPSubGoal;
//						couterPSubGoal.x = f[0];
//						couterPSubGoal.y = f[1];
//						couterPSubGoal.z = f[2];
//
//						//check near parallel planes problem
//						Vec3f f = (couterPSubGoal - myHc->userPos) * ParallelBigForceProblemScalarThreshold;
//						float magni = f.norm();
//						if (magni > ParallelBigForceProblemThreshold)
//						{//near parallel plane cause big force problem
//#ifdef PrintInfoBigForce
//							DSTR << "tst Big Force Output!" << endl;
//#endif
//							f.clear();
//
//							myHc->constrainCount--;
//
//							parallelDetected = true;
//							break;
//
//						}
//						else {
//
//							newSubGoal = couterPSubGoal;
//							newSubStart = tmpcpinfo1.planeP;
//							myHc->couterPlaneN = counterPlane;
//						}
//
//#ifdef STORE_LOCALCOORD
//						//find local coordinates for proxyfix
//						//find face or edge
//						for (unsigned int ci = 0; ci < myHc->constrainCount; ci++)
//						{
//							if (myHc->cpiVec[ci].cstType == PHOpHapticController::cstFace)
//							{
//								unsigned int obji = myHc->cpiVec[ci].objid;
//								GRMesh *tgtm = dfmObj[obji].targetMesh;
//								float t;
//								bool itflag = IntersectSegmentTriangle(newSubGoal, newSubGoal - myHc->cpiVec[ci].planeN,
//									tgtm->vertices[tgtm->faces[myHc->cpiVec[ci].planeid].indices[2]] + cpiVec[ci].planeN * myHc->c_obstRadius,
//									tgtm->vertices[tgtm->faces[myHc->cpiVec[ci].planeid].indices[1]] + cpiVec[ci].planeN * myHc->c_obstRadius,
//									tgtm->vertices[tgtm->faces[myHc->cpiVec[ci].planeid].indices[0]] + cpiVec[ci].planeN * myHc->c_obstRadius,
//									myHc->cpiVec[ci].fu, myHc->cpiVec[ci].fv, myHc->cpiVec[ci].fw, t);
//								unsigned int u = 0;
//								break;
//							}
//							/*else if (myHc->cpiVec[ci].cstType == PHOpHapticController::cstEdge)
//							{
//							unsigned int obji = myHc->cpiVec[ci].objid;
//							GRMesh *tgtm = dfmObj[obji].targetMesh;
//							float ct;
//							bool itflag = IntersectSegmentCylinder(newSubGoal, newSubGoal - myHc->cpiVec[ci].planeN,
//							tgtm->vertices[myHc->cpiVec[ci].edgeidA], tgtm->vertices[myHc->cpiVec[ci].edgeidB],
//							myHc->c_obstRadius, ct);
//							unsigned int u = 0;
//							break;
//							}*/
//						}
//
//						int u = 0;
//#endif
//					}
//					//------------------ OLD two cstr solve END-----------------
//
//
//					////new simple way //not good because do not consider the planeP of first
//					//Vec3f twoCstrPlaneN;
//					//twoCstrPlaneN = tmpcpinfo.planeN;
//					//twoCstrPlaneN += tmpcpinfo1.planeN;
//					//twoCstrPlaneN * 0.5f;
//
//					//Vec3f ctcP = tmpcpinfo1.planeP;
//					//Vec3f nextP = myHc->userPos - ctcP;
//					//twoCstrPlaneN.unitize();
//					//float proj = nextP.dot(twoCstrPlaneN);
//					////float magni = fabs(proj);
//					//Vec3f tstnewSubGoal = ctcP + (nextP - twoCstrPlaneN * proj);
//					//Vec3f tstnewSubStart = ctcP;
//
//					//
//					//Vec3f tstcouterPlaneN = twoCstrPlaneN;
//					//int u = 0;
//
//#ifdef Save_GoalPos
//					objnewSubstarts.push_back(newSubStart);
//					objnewSubgoals.push_back(newSubGoal);
//#endif
//					//save barycentric coordinate in first face constrain (ignore the case that no face constr inside)
//					//for (int ci = 0;ci<)
//				}
//				else {
//					break;
//					/*
//					myHc->GetMyHpProxyParticle()->pNewCtr = nextSubGoal;
//					DSTR<<"pNewCtr set to nextSubGoal"<<endl;*/
//				}
//
//				{//Third constrain 
//
//				 //do popUp before 
//#ifdef USE_ProxyPopOut_In_ProxySolve
//					myHc->hcFixProxystart = newSubStart;
//#ifdef USE_PruneNegtiveFacesPop
//					if (useAdaptiveProxy)
//						AdaptiveProxyPopOut();
//					else
//						HpProxyPopOutUsePruneList();
//#else
//					HpProxyPopOut();
//#endif
//					newSubStart = myHc->hcFixProxystart;
//#endif
//
//
//#ifdef PrintProxySolveCheckInfo
//					//--------------add check in face start-------
//					for(int obji = 0; obji < objNum; obji++)
//					{
//						GRMesh* tgtMesh = dfmObj[obji].targetMesh;//only for debug, one obj
//						unsigned int faceNum = tgtMesh->NFace();//only for debug, one obj
//						for (unsigned int ofi = 0; ofi < faceNum; ofi++)
//						{
//
//							Vec3f fpa =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[2]];
//							Vec3f fpb =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[1]];
//							Vec3f fpc =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[0]];
//							Vec3f faceN = (cross(fpb - fpa, fpc - fpa)).unit();
//
//
//							bool insideTri = false;
//							int regionF = -1;
//
//							Vec3f closp = ClosestPtoTriangle(newSubStart, fpa, fpb, fpc, insideTri, regionF);
//
//							if (insideTri)
//							{
//								if (!isClose(closp, newSubStart, myHc->c_obstRadius))continue;
//								float checIn = (newSubStart - (fpa + faceN * myHc->c_obstRadius)).dot(faceN);
//
//								if (checIn < 0)
//								{
//
//									DSTR << "fall in tri in third start" << ofi << " of obj" << obji << endl;
//#ifdef USE_ProxyPopOut_In_ProxySolve
//									myHc->hcFixProxystart = newSubStart;
//
//#ifdef USE_PruneNegtiveFacesPop
//									if (useAdaptiveProxy)
//										AdaptiveProxyPopOut();
//									else
//										HpProxyPopOutUsePruneList();
//#else
//									HpProxyPopOut();
//#endif
//									newSubStart = myHc->hcFixProxystart;
//#endif
//									closp = ClosestPtoTriangle(newSubStart, fpa, fpb, fpc, insideTri, regionF);
//									if (!isClose(closp, newSubStart, myHc->c_obstRadius))continue;
//									checIn = (newSubStart - (fpa + faceN * myHc->c_obstRadius)).dot(faceN);
//
//									if (checIn < 0)
//									{
//										DSTR << "fallagain in tri in third start" << ofi << " of obj" << obji << endl;
//									}
//								}
//							}
//
//							Vec3f closp2 = ClosestPtoTriangle(newSubGoal, fpa, fpb, fpc, insideTri, regionF);
//
//							if (insideTri)
//							{
//								if (!isClose(closp2, newSubGoal, myHc->c_obstRadius))continue;
//								float checIn = (newSubGoal - (fpa + faceN * myHc->c_obstRadius)).dot(faceN);
//
//								if (checIn < 0)
//								{
//
//									DSTR << "fall in tri in third goal" << ofi << " of obj" << obji << endl;
//								}
//							}
//						}
//					}
//					//--------------add check in face end------
//#endif
//					PHOpHapticController::ConstrainPlaneInfo &tmpcpinfo2 = cpiVec[2];
//
//
//#ifdef USE_GLOBLE_COLLI
//#ifdef USE_ShrinkReturn
//					thrStepOn = new_intersectOnRouteUseShrink(newSubStart, newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo2, false, true);
//#else
//#ifdef USE_a_little_over_InSolve
//					thrStepOn = new_intersectOnRoute(newSubStart - ((newSubGoal - tmpcpinfo1.planeP).unit())*mPrevPrecE, newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo2, false, true);
//#else
//					thrStepOn = new_intersectOnRoute(newSubStart, newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo2, false, true);
//#endif
//#endif
//					//thrStepOn = intersectOnRoute(newSubStart - ((newSubGoal - tmpcpinfo1.planeP).unit())*mPrevPrecE, newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo2, false);
//					//thrStepOn = intersectOnRoute(newSubStart , newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo2, false);
//#else
//					thrStepOn = intersectOnRouteInColliPs(newSubStart - ((nextSubGoal - tmpcpinfo1.planeP).unit())*mPrevPrecE, newSubGoal, nextSubStart, nextSubGoal, tmpcpinfo2, false);
//#endif
//
//					if (thrStepOn)
//					{
//
//						myHc->constrainCount = 3;
//
//#ifdef PrintInfoColliSolve
//						DA.AddTempDrawLine(nextSubStart, nextSubGoal);
//						DA.AddTempDrawFont3D(nextSubStart, "3rd s");
//						DA.AddTempDrawFont3D(nextSubGoal, "3rd g");
//
//						switch (tmpcpinfo2.cstType)
//						{
//						case PHOpHapticController::cstEdge:
//							DSTR << "Third cstEdge obj" << tmpcpinfo2.objid << " Edge" << tmpcpinfo2.edgeidA << " " << tmpcpinfo2.edgeidB << " " << endl;
//							////DA.AddTempDrawBall(tmpcpinfo2.planeP, myHc->c_obstRadius*0.5);
//							////DA.AddTempDrawFont3D(tmpcpinfo2.planeP, "ec3");
//							////DA.AddTempDrawLine(tmpcpinfo2.planeP, tmpcpinfo2.planeP + tmpcpinfo2.planeN);
//							break;
//						case PHOpHapticController::cstPoint:
//							DSTR << "Third cstPoint obj" << tmpcpinfo2.objid << " Point" << tmpcpinfo2.vid << " " << endl;
//
//							break;
//						case PHOpHapticController::cstFace:
//							DSTR << "Third cstFace obj" << tmpcpinfo2.objid << " Face" << tmpcpinfo2.planeid << " " << endl;
//
//							break;
//						default:
//							break;
//						}
//
//
//#endif	
//						for (unsigned int samei = 0; samei<myHc->constrainCount - 1; samei++)
//						{
//
//							if (tmpcpinfo2.isSameCstr(cpiVec[samei]))
//							{
//								sameinside = true;
//							}
//
//						}
//
//
//						if (sameinside)
//						{
//#ifdef PrintInfoColliSolve
//							DSTR << "same inside" << endl;
//#endif
//							myHc->constrainCount--;
//							break;
//						}
//						unsigned int Nirs = 3 + myHc->constrainCount;
//						vector<int> turns; turns.resize(Nirs);
//						VMatrixRow< double > clms;
//						clms.resize(Nirs, Nirs);
//						clms.clear(0.0);
//						VVector< double > d;
//						d.resize(Nirs);
//						d.clear(0.0);
//
//						VVector< double > f;
//						f.resize(Nirs);
//						f.clear(0.0);
//
//						//colums with number "1"
//						for (unsigned int mi = 0; mi<3; mi++)
//						{
//							clms[mi][mi] = 1;
//						}
//
//						//make counterPlane for Proxy
//						Vec3f counterPlane;
//						for (unsigned int pbpi = 0; pbpi<myHc->constrainCount; pbpi++)
//							//for(unsigned int pbpi = 0;pbpi<pssbPlanes.size();pbpi++)
//						{
//							unsigned int objid = cpiVec[pbpi].objid;
//							//unsigned int corrTurni;
//							//if (pbpi == 0)
//							//{
//							//	//if ((cpiVec[pbpi].planeid == 2) || (cpiVec[pbpi].planeid == 3))
//							//	{
//							//		corrTurni = 0;
//							//	}
//							//	//else corrTurni = pbpi;
//							//}
//							//else if (pbpi == 1)
//							//{
//							//	//if ((cpiVec[pbpi].planeid == 3) || (cpiVec[pbpi].planeid == 0))
//							//	{
//							//		corrTurni = 2;
//							//	}
//							//}
//							//else if (pbpi == 2)
//							//{
//							//	//if ((cpiVec[pbpi].planeid == 2) || (cpiVec[pbpi].planeid == 0))
//							//	{
//							//		corrTurni = 3;
//							//	}
//							//}
//
//							PHOpObj *myobj = (*opObjs)[objid];
//							
//							Vec3f planeN = cpiVec[pbpi].planeN;
//							Vec3f planeP = cpiVec[pbpi].planeP;
//
//							counterPlane += planeN;
//
//							float fA = planeN.x, fB = planeN.y, fC = planeN.z;
//							float fD = -(fA * planeP.x + fB * planeP.y + fC * planeP.z);
//
//							//render->SetMaterial(GRRenderIf::RED);
//							//render->DrawLine(planeP,planeP+(planeN * 1.5));
//
//							clms[0][3 + pbpi] = fA;
//							clms[1][3 + pbpi] = fB;
//							clms[2][3 + pbpi] = fC;
//
//							clms[3 + pbpi][0] = fA;
//							clms[3 + pbpi][1] = fB;
//							clms[3 + pbpi][2] = fC;
//
//							d[3 + pbpi] = -fD;
//
//						}
//						d[0] = currGoal.x;
//						d[1] = currGoal.y;
//						d[2] = currGoal.z;
//#ifdef PrintInfoColliSolveProcess
//						DSTR << "constrainPlaneMatrix in proxy solve 2:" << endl;
//						for (unsigned int i = 0; i<Nirs; i++)
//						{
//							for (unsigned int j = 0; j<Nirs; j++)
//								DSTR << clms[i][j] << " ";
//
//							DSTR << "* f = " << d[i] << endl;
//						}
//#endif
//						/*GaussElimi (clms, f, -d);
//						DSTR<<"Result1 f:"<<endl;
//						for(unsigned int i = 0;i<Nirs;i++)
//						{
//
//						DSTR<<" springhead GaussElimi f = "<<f[i];
//						}
//						DSTR<<endl;*/
//						//GaussElimi::SolveGaussElimi(clms, d, Nirs, f);
//						clms.gauss(f, d, turns.data());
//
//#ifdef PrintCalInfoColliSolve
//						DSTR << "Result2 f:" << endl;
//						for (unsigned int i = 0; i<Nirs; i++)
//						{
//
//							DSTR << " f = " << f[i];
//						}
//
//						DSTR << endl;
//#endif
//						counterPlane /= myHc->constrainCount;
//						counterPlane.unitize();
//
//						if (f[0] == 0.0f&&f[1] == 0.0f&&f[2] == 0.0f)
//						{
//							//parallel plane detected use only one 
//#ifdef PrintInfoBigForce
//							DSTR << "parallel detected!proxysolve 2" << endl;
//#endif	
//							myHc->constrainCount = 1;
//							parallelDetected = true;
//							//break;
//							break;
//						}
//						else {
//							Vec3f couterPSubGoal;
//							couterPSubGoal.x = f[0];
//							couterPSubGoal.y = f[1];
//							couterPSubGoal.z = f[2];
//
//							//check near parallel planes problem
//							Vec3f f = (couterPSubGoal - myHc->userPos) * ParallelBigForceProblemScalarThreshold;
//							float magni = f.norm();
//							if (magni > ParallelBigForceProblemThreshold)
//							{//near parallel plane cause big force problem
//#ifdef PrintInfoBigForce
//								DSTR << "tst Big Force Output!" << endl;
//#endif
//								f.clear();
//
//								myHc->constrainCount--;
//
//								parallelDetected = true;
//								break;
//							}
//							else {
//
//								newSubGoal = couterPSubGoal;
//								newSubStart = tmpcpinfo2.planeP;
//								myHc->couterPlaneN = counterPlane;
//							}
//
//
//#ifdef STORE_LOCALCOORD
//							//find local coordinates for proxyfix
//							//find face or edge
//							for (unsigned int ci = 0; ci < myHc->constrainCount; ci++)
//							{
//								if (myHc->cpiVec[ci].cstType == PHOpHapticController::cstFace)
//								{
//									unsigned int obji = myHc->cpiVec[ci].objid;
//									GRMesh *tgtm = dfmObj[obji].targetMesh;
//									float t;
//									bool itflag = IntersectSegmentTriangle(newSubStart, newSubGoal,
//										tgtm->vertices[tgtm->faces[myHc->cpiVec[ci].planeid].indices[2]] + cpiVec[ci].planeN * myHc->c_obstRadius,
//										tgtm->vertices[tgtm->faces[myHc->cpiVec[ci].planeid].indices[1]] + cpiVec[ci].planeN * myHc->c_obstRadius,
//										tgtm->vertices[tgtm->faces[myHc->cpiVec[ci].planeid].indices[0]] + cpiVec[ci].planeN * myHc->c_obstRadius,
//										myHc->cpiVec[ci].fu, myHc->cpiVec[ci].fv, myHc->cpiVec[ci].fw, t);
//									int u = 0;
//									//ClosestPtoTriangle(newSubStart)
//									break;
//								}
//								/*else if (myHc->cpiVec[ci].cstType == PHOpHapticController::cstEdge)
//								{
//								unsigned int obji = myHc->cpiVec[ci].objid;
//								GRMesh *tgtm = dfmObj[obji].targetMesh;
//								float ct;
//								bool itflag = IntersectSegmentCylinder(newSubStart, newSubGoal,
//								tgtm->vertices[myHc->cpiVec[ci].edgeidA], tgtm->vertices[myHc->cpiVec[ci].edgeidB],
//								myHc->c_obstRadius, ct);
//								int u = 0;
//								break;
//								}*/
//							}
//							int u = 0;
//#endif
//						}
//#ifdef Save_GoalPos
//						objnewSubstarts.push_back(newSubStart);
//						objnewSubgoals.push_back(newSubGoal);
//#endif
//					}
//				}
//				// newSubStart = newSubStart;// + myHc->couterPlaneN*0.002f;
//				//myHc->GetMyHpProxyParticle()->pNewCtr = newSubStart;
//#ifdef PrintInfoColliSolveProcess		
//				DSTR << "final" << endl;
//				DSTR << "ctcNum: " << myHc->constrainCount << endl;
//				DSTR << "newSubGoal: " << newSubGoal.x << " " << newSubGoal.y << " " << newSubGoal.z << endl;
//				DSTR << "couterPlaneN: " << myHc->couterPlaneN.x << " " << myHc->couterPlaneN.y << " " << myHc->couterPlaneN.z << endl;
//#endif		
//				{
//					//Over Third faces 
//					//for simple if speed is not enough,only use 
//
//
//				}
//
//			} while (0);
//
//
//			Vec3f closestP;
//			if (myHc->constrainCount == 1)
//			{
//				myHc->GetMyHpProxyParticle()->pNewCtr = newSubGoal;
//
//#ifdef PrintNewCtr
//				DSTR << "pNewCtr is setting (in currConstrNum = 1)" << hdp->pNewCtr.x << " " << hdp->pNewCtr.y << " " << hdp->pNewCtr.z << endl;
//#endif
//				//closestP = newSubGoal;
//			}
//			else if (myHc->constrainCount == 2)
//			{
//				myHc->GetMyHpProxyParticle()->pNewCtr = newSubGoal;
//#ifdef PrintNewCtr
//				DSTR << "pNewCtr is setting (in currConstrNum = 2)" << hdp->pNewCtr.x << " " << hdp->pNewCtr.y << " " << hdp->pNewCtr.z << endl;
//#endif
//				//closestP = newSubGoal;
//			}
//			else if (myHc->constrainCount == 3)
//			{
//				//myHc->GetMyHpProxyParticle()->pNewCtr = newSubStart;
//				myHc->GetMyHpProxyParticle()->pNewCtr = newSubGoal;
//#ifdef PrintNewCtr
//				DSTR << "pNewCtr is setting (in currConstrNum = 3)" << hdp->pNewCtr.x << " " << hdp->pNewCtr.y << " " << hdp->pNewCtr.z << endl;
//#endif
//				//closestP = newSubStart;
//			}
//
//			if (sameinside || parallelDetected)
//			{
//				myHc->GetMyHpProxyParticle()->pNewCtr = newSubStart;
//				//#ifdef PrintNewCtr
//				DSTR << "pNewCtr is setting parallel with constraintCount=" << myHc->constrainCount << endl;
//				//#endif
//				myHc->sameCstrInside = true;
//			}
//#ifdef PrintProxySolveCheckInfo
//			//--------------add check in face start-------
//			for(int obji = 0; obji < objNum; obji++)
//			{
//				GRMesh* tgtMesh = dfmObj[obji].targetMesh;//only for debug, one obj
//				unsigned int faceNum = tgtMesh->NFace();//only for debug, one obj
//				for (unsigned int ofi = 0; ofi < faceNum; ofi++)
//				{
//
//					Vec3f fpa =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[2]];
//					Vec3f fpb =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[1]];
//					Vec3f fpc =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[0]];
//					Vec3f faceN = (cross(fpb - fpa, fpc - fpa)).unit();
//
//
//					bool insideTri = false;
//					int regionF = -1;
//
//					Vec3f closp = ClosestPtoTriangle(newSubGoal, fpa, fpb, fpc, insideTri, regionF);
//
//					if (insideTri)
//					{
//						if (!isClose(closp, newSubGoal, myHc->c_obstRadius))continue;
//						float checIn = (newSubGoal - (fpa + faceN * myHc->c_obstRadius)).dot(faceN);
//
//						if (checIn < 0)
//						{
//
//							DSTR << "fall in tri in solved goal" << ofi << " of obj" << obji << endl;
//						}
//					}
//
//
//				}
//			}
//			//--------------add check in face end------
//#endif
//			//	mtHapticFix.restartMyTimer();
//			////save local coordinates for proxyfix
//			//Vec3f counterP;
//			//for (unsigned int csti = 0; csti < myHc->constrainCount; csti++)
//			//{
//			//	PHOpHapticController::ConstrainPlaneInfo &cpinfo1 = myHc->cpiVec[csti];
//			//	GRMesh *tgtm = dfmObj[cpinfo1.objid].targetMesh;
//			//	Vec3f *a, *b, *la, *lb, *lc, *v;
//			//	Vec3f d;
//			//	float t;
//			//	switch (cpinfo1.cstType)
//			//	{
//			//	case PHOpHapticController::cstEdge:
//			//		a = &tgtm->vertices[cpinfo1.edgeidA];
//			//		b = &tgtm->vertices[cpinfo1.edgeidB];
//			//		//update local coordinates
//			//		//SaveCylLocalCoordinates(*a, *b, myHc->GetMyHpProxyParticle()->pNewCtr, currGoal, myHc->c_obstRadius, cpinfo1.segmentt);
//			//		SaveCylLocalCoordinates(myHc->GetMyHpProxyParticle()->pNewCtr, *a, *b, cpinfo1.segmentt, d);
//			//		//update direction
//			//		cpinfo1.planeN = (myHc->GetMyHpProxyParticle()->pNewCtr - d).unit();
//
//			//		//test record savelocal 
//			//		//cpinfo1.planeP = myHc->GetMyHpProxyParticle()->pNewCtr;
//
//			//		//counterP += cpinfo1.planeN;
//			//		break;
//			//	case PHOpHapticController::cstPoint:
//			//		v = &tgtm->vertices[cpinfo1.vid];
//			//		//update direction
//			//		cpinfo1.planeN = (myHc->GetMyHpProxyParticle()->pNewCtr - *v).unit();
//			//		//counterP += cpinfo1.planeN;
//			//		break;
//			//	case PHOpHapticController::cstFace:
//			//		la = &tgtm->vertices[tgtm->faces[cpinfo1.planeid].indices[2]];
//			//		lb = &tgtm->vertices[tgtm->faces[cpinfo1.planeid].indices[1]];
//			//		lc = &tgtm->vertices[tgtm->faces[cpinfo1.planeid].indices[0]];
//			//		//update local coordinates
//			//		SaveTriLocalCoordinates(myHc->GetMyHpProxyParticle()->pNewCtr, currGoal, *la, *lb, *lc, cpinfo1.fu, cpinfo1.fv, cpinfo1.fw, t);
//			//		//counterP += cross(*lb - *la, *lc - *la);
//			//		break;
//			//	default:
//			//		break;
//			//	}
//			//}
//			//		mtHapticFix.pauseMyTimer();
//			//myHc->couterPlaneN = counterP / myHc->constrainCount;
//
//			////new approach one additional test
//			//PHOpHapticController::ConstrainPlaneInfo tmpcpinfotst;
//			//bool addtionalTestHit = false;
//			//addtionalTestHit = new_intersectOnRoute(myHc->GetMyHpProxyParticle()->pNewCtr, currGoal, newSubStart, newSubGoal, tmpcpinfotst, false);
//
//			//-----------------------------------------------------iterated Proxy solve start
//			//do popUp before 
//#ifdef USE_ProxyPopOut_In_ProxySolve
//			myHc->hcFixProxystart = newSubStart;
//#ifdef USE_PruneNegtiveFacesPop
//			if (useAdaptiveProxy)
//				AdaptiveProxyPopOut();
//			else
//				HpProxyPopOutUsePruneList();
//#else
//			HpProxyPopOut();
//#endif
//			newSubStart = myHc->hcFixProxystart;
//#endif
//
//
//			//outOf Constr test
//			bool outOfCstr = false;
//			PHOpHapticController::ConstrainPlaneInfo tmpcpinfotst;
//#ifdef USE_ShrinkReturn
//			outOfCstr = new_intersectOnRouteUseShrink(myHc->GetMyHpProxyParticle()->pNewCtr, currGoal, newSubStart, newSubGoal, tmpcpinfotst, false, false);
//#else
//#ifdef USE_a_little_over_InSolve
//			outOfCstr = new_intersectOnRoute(myHc->GetMyHpProxyParticle()->pNewCtr - (currGoal - myHc->GetMyHpProxyParticle()->pNewCtr) * mPrevPrecE, currGoal, newSubStart, newSubGoal, tmpcpinfotst, false, false);
//#else
//			outOfCstr = new_intersectOnRoute(myHc->GetMyHpProxyParticle()->pNewCtr, currGoal, newSubStart, newSubGoal, tmpcpinfotst, false, false);
//#endif
//#endif
//			if (outOfCstr)
//			{
//				bool SameCstrInThisLoop = false;
//
//				for (unsigned int csti = 0; csti < myHc->constrainCount; csti++)
//				{
//					PHOpHapticController::ConstrainPlaneInfo &cpinfo1 = myHc->cpiVec[csti];
//
//					if (tmpcpinfotst.isSameCstr(cpinfo1))
//					{
//						SameCstrInThisLoop = true;
//					}
//
//				}
//
//				if (!SameCstrInThisLoop)
//				{
//#ifdef PrintProxySolveCheckInfo
//					DSTR << "found other in Solve";
//					switch (tmpcpinfotst.cstType)
//					{
//					case PHOpHapticController::cstEdge:
//						DSTR << "cstEdge obj" << tmpcpinfotst.objid << " Edge" << tmpcpinfotst.edgeidA << " " << tmpcpinfotst.edgeidB << endl;
//						break;
//					case PHOpHapticController::cstPoint:
//						DSTR << "cstPoint obj" << tmpcpinfotst.objid << " Point" << tmpcpinfotst.vid << endl;
//						break;
//					case PHOpHapticController::cstFace:
//						DSTR << "cstFace obj" << tmpcpinfotst.objid << " Face" << tmpcpinfotst.planeid << endl;
//						break;
//					default:
//						break;
//					}
//
//#endif 
//
//					proxyItrtNum++;
//					if (proxyItrtNum < proxyItrtMaxNum)
//					{
//#ifdef PrintItrctingProxySolve
//						DSTR << "iterating" << proxyItrtNum << endl;
//#endif
//						//vector<PHOpHapticController::ConstrainPlaneInfo*>::iterator unii = unique(slvItr.constrainIs.begin(), slvItr.constrainIs.end());
//						//if (unii == slvItr.constrainIs.end())
//						bool SameCstrInAllLoop = false;
//						for (unsigned int ii = 0; ii < slvItr.constrainIs.size(); ii++)
//						{
//							PHOpHapticController::ConstrainPlaneInfo *cpinfo1 = slvItr.constrainIs[ii];
//
//							if (tmpcpinfotst.isSameCstr(cpinfo1[ii]))
//							{
//								SameCstrInAllLoop = true;
//#ifdef PrintItrctingProxySolve
//								DSTR << "No need more loop" << endl;
//#endif
//							}
//
//
//						}
//						if (!SameCstrInAllLoop)
//						{
//							myHc->hcFixProxystart = myHc->GetMyHpProxyParticle()->pNewCtr;
//#ifdef USE_PruneNegtiveFacesPop
//							if (useAdaptiveProxy)
//								AdaptiveProxyPopOut();
//							else
//								HpProxyPopOutUsePruneList();
//#else
//							HpProxyPopOut();
//#endif
//							myHc->GetMyHpProxyParticle()->pNewCtr = myHc->hcFixProxystart;
//
//							slvItr.constrainIs.push_back(&tmpcpinfotst);
//							myHc->constrainCount = 0;
//#ifdef PrintProxySolveCheckInfo
//							DSTR << "Solveloop " << proxyItrtNum << " Start" << endl;
//#endif
//							HapticProxySolveOpt(myHc->GetMyHpProxyParticle()->pNewCtr);
//						}
//					}
//					else {
//						int u = 0;
//					}
//				}
//
//			}
//			else
//			{
//				myHc->constrainCount = 0;
//#ifdef PrintInfoHapticColliSolution
//				if (myHc->hcProxyOn)
//				{
//					if (!firStepOn) {
//						DSTR << "noCTC" << endl;
//					}
//					else if (!secStepOn)
//					{
//						DSTR << "noCTC on secCTC" << endl;
//					}
//					else if (!thrStepOn)
//					{
//						DSTR << "noCTC on thrCTC" << endl;
//					}
//					else {
//						DSTR << "What's wrong???" << endl;
//					}
//					DSTR << "hcProxyOff" << endl;
//				}
//#endif
//				myHc->hcProxyOn = false;
//
//				myHc->couterPlaneN.clear();
//			}
//
//			//-----------------------------------------------------------------iterated Proxy solve end
//		}
//		else {
//			//myHc->GetMyHpProxyParticle()->pNewCtr = myHc->userPos;
//
//			myHc->constrainCount = 0;
//#ifdef PrintInfoHapticColliSolution
//			if (myHc->hcProxyOn)
//			{
//				if (!firStepOn) {
//					DSTR << "noCTC" << endl;
//				}
//				else if (!secStepOn)
//				{
//					DSTR << "noCTC on secCTC" << endl;
//				}
//				else if (!thrStepOn)
//				{
//					DSTR << "noCTC on thrCTC" << endl;
//				}
//				else DSTR << "What's wrong???" << endl;
//				DSTR << "hcProxyOff" << endl;
//			}
//#endif
//			myHc->hcProxyOn = false;
//
//			myHc->couterPlaneN.clear();
//		}
//	}
//
//	bool PHOpHapticRenderer::new_intersectOnRouteUseShrink(Vec3f currSubStart, Vec3f currSubGoal, Vec3f &newSubStart, Vec3f &newSubGoal, PHOpHapticController::ConstrainPlaneInfo &cpinfo, bool inverseF, bool sameCheck)
//	{
//
//		float nearestDist = 100.0f;
//
//		//for insidecheck
//		unsigned int cstrNum = myHc->constrainCount;
//		PHOpHapticController::ConstrainPlaneInfo tmpcpinfo;
//
//		//be carefull all the projection should be found related to userpoint not newsubgoal
//		Vec3f &userPoint = myHc->userPos;
//
//		Vec3f prcRoute = currSubGoal - currSubStart;
//		Vec3f &p = currSubStart;
//		Vec3f &u = currSubGoal;
//		Vec3f midP_forDetect = (currSubGoal + currSubStart)*0.5f;
//
//		bool intsectDtcted = false;
//		int IsIntsctedOverf;
//		int IsIntsctedEdgecyliner;
//		int IsIntsctedSphere;
//		int IsIntsctedOverf2;
//
//		float detectRadius = myHc->ProxySolveDetectionSize;
//		/*float detectRadius = (userPoint - currSubStart).norm();
//		if (detectRadius < myHc->min_hcElmDtcRadius)
//		detectRadius = myHc->min_hcElmDtcRadius;
//		else if (detectRadius > myHc->max_hcElmDtcRadius)
//		detectRadius = myHc->max_hcElmDtcRadius;*/
//
//		//start from midPoint 
//		//detectRadius *= 0.5f;
//
//		vector<Vec3f> fsInRangeNs; fsInRangeNs.reserve(400);
//		vector<unsigned int> vsInRange; vsInRange.reserve(400);
//		vector<unsigned int> fsInRange; fsInRange.reserve(400);
//
//		for (int obji = 0; obji <opObjs->size(); obji++)
//		{
//			fsInRangeNs.clear();
//			vsInRange.clear();
//			fsInRange.clear();
//
//			PHOpObj *myobj = (*opObjs)[obji];
//			
//			unsigned int vertNum = myobj->objMeshVtsNum;// tgtMesh->NVertex();
//			unsigned int faceNum = myobj->objMeshFaces.size();
//
//			//collect face inrange
//			for (unsigned int ofi = 0; ofi < faceNum; ofi++)
//			{
//				bool finr = false;
//				unsigned int faceq1 = 2; unsigned int faceq3 = 0;
//
//				if (inverseF)
//				{
//					faceq1 = 0; faceq3 = 2;
//				}
//				Vec3f &fpa = myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[faceq1]];
//				Vec3f &fpb =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[1]];
//				Vec3f &fpc =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[faceq3]];
//
//				//detect in range
//				//#ifdef DetectFromMiddlePoint
//				//			if (isClose(fpa, midP_forDetect, detectRadius)
//				//				|| isClose(fpb, midP_forDetect, detectRadius)
//				//				|| isClose(fpc, midP_forDetect, detectRadius))
//				//			
//				//#else 
//				//			if (isClose(fpa, currSubStart, detectRadius)
//				//				|| isClose(fpb, currSubStart, detectRadius)
//				//				|| isClose(fpc, currSubStart, detectRadius))
//				//			#endif
//				{
//
//
//					//detect those face to us
//#ifdef INVERSE_TRIANGLE_NORMAL
//					Vec3f faceN = cross(fpc - fpa, fpb - fpa);
//#else
//					Vec3f faceN = cross(fpb - fpa, fpc - fpa);
//#endif
//
//					if (faceN.dot(prcRoute) < 0)
//					{
//						finr = true;
//						fsInRangeNs.push_back(faceN);
//						fsInRange.push_back(ofi);
//					}
//				}
//
//
//
//			}
//			for (unsigned int ofi = 0; ofi < vertNum; ofi++)
//			{
//				bool finr = false;
//				Vec3f &fpa =  myobj->objMeshVts[ofi];
//#ifdef DetectFromMiddlePoint
//				if (isClose(fpa, midP_forDetect, detectRadius))
//#else
//				if (CollisionFunctions::isClose(fpa, currSubStart, detectRadius))
//#endif
//				{
//					vsInRange.push_back(ofi);
//				}
//
//			}
//
//			Vec3f abFpa;
//			Vec3f abFpb;
//			Vec3f abFpc;
//
//			//new for tstoverTriface
//			for (unsigned int fi = 0; fi < fsInRange.size(); fi++)
//			{
//				unsigned int ofi = fsInRange[fi];
//
//				//tstOnOverTRi a triangle on the upper position of the face  
//				unsigned int faceq1 = 2; unsigned int faceq3 = 0;
//
//				if (inverseF)
//				{
//					faceq1 = 0; faceq3 = 2;
//				}
//				Vec3f &fpa =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[faceq1]];
//				Vec3f &fpb =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[1]];
//				Vec3f &fpc =  myobj->objMeshVts[myobj->objMeshFaces[ofi].indices[faceq3]];
//				if (myobj->objMeshFaces[ofi].nVertices == 4)
//					DSTR << "rectangle detected" << endl;
//
//				Vec3f dyFaceNormal = fsInRangeNs[fi];// cross(fpb - fpa, fpc - fpa);
//
//													 //			Vec3f dyFaceNormal = cross(fpb - fpa, fpc - fpa);
//
//				dyFaceNormal.unitize();
//				dyFaceNormal = dyFaceNormal * myHc->c_obstRadius * myHc->SolveShrinkRadio;
//
//				Vec3f abFpa = fpa + dyFaceNormal;
//				Vec3f abFpb = fpb + dyFaceNormal;
//				Vec3f abFpc = fpc + dyFaceNormal;
//
//#ifdef DrawRouteInfo
//				render->SetMaterial(GRRenderIf::BLACK);
//				render->DrawLine(abFpa, abFpb);
//				render->DrawLine(abFpc, abFpb);
//				render->DrawLine(abFpa, abFpc);
//#endif	
//				float fu, fv, fw, ft;
//
//				IsIntsctedOverf = CollisionFunctions::IntersectSegmentTriangle(p, u, abFpa, abFpb, abFpc, fu, fv, fw, ft);
//				if (IsIntsctedOverf == 1)
//				{
//					Vec3f itsctPos = abFpa*fu + abFpb*fv + abFpc*fw;
//
//#ifdef DRAW_INTSINFO
//					Affinef affpos;
//					affpos.Pos() = itsctPos;
//					render->SetMaterial(GRRenderIf::ORANGE);
//					render->PushModelMatrix();
//					render->MultModelMatrix(affpos);
//					render->DrawBox(0.02f, 0.02f, 0.02f, true);
//					render->PopModelMatrix();
//#endif
//					float dist = fabs((currSubStart - itsctPos).norm());
//					if (dist<nearestDist)
//					{
//						tmpcpinfo.cstType = PHOpHapticController::cstFace;
//						tmpcpinfo.fu = fu;
//						tmpcpinfo.fw = fw;
//						tmpcpinfo.fv = fv;
//						tmpcpinfo.planeid = ofi;
//						tmpcpinfo.objid = obji;
//						//for insidecheck
//						bool sameinside = false;
//						if (cstrNum > 0 && sameCheck)
//						{
//							for (unsigned int samei = 0; samei<cstrNum; samei++)
//							{
//								if (tmpcpinfo.isSameCstr(myHc->cpiVec[samei]))
//								{
//									sameinside = true;
//#ifdef PrintProxySolveCheckInfo
//									DSTR << "same inside" << ofi << endl;
//#endif
//								}
//							}
//
//						}
//						if (!sameinside)
//						{
//
//							cpinfo.cstType = PHOpHapticController::cstFace;
//							cpinfo.fu = fu;
//							cpinfo.fw = fw;
//							cpinfo.fv = fv;
//							cpinfo.planeid = ofi;
//							cpinfo.objid = obji;
//							dyFaceNormal.unitize();
//							cpinfo.planeN = dyFaceNormal;
//#ifdef USE_ShrinkReturn
//							itsctPos = itsctPos + dyFaceNormal *(1.0f - myHc->SolveShrinkRadio);
//#endif
//							cpinfo.planeP = itsctPos;
//							nearestDist = dist;
//						}
//					}
//
//				}
//			}
//
//			//new for tstEdgeCylinder
//			for (unsigned int fi = 0; fi < fsInRange.size(); fi++)
//			{
//				unsigned int i = fsInRange[fi];
//				//no map is needed
//				unsigned int evid1, evid2;
//				//case A-B for Tri ABC
//				evid1 = myobj->objMeshFaces[i].indices[TriAId];
//				evid2 = myobj->objMeshFaces[i].indices[TriBId];
//
//				Vec3f &a =  myobj->objMeshVts[evid1];
//				Vec3f &b =  myobj->objMeshVts[evid2];
//				float ct;
//				IsIntsctedEdgecyliner = CollisionFunctions::IntersectSegmentCylinder(p, u, a, b, myHc->c_obstRadius * myHc->SolveShrinkRadio, ct);
//				if (IsIntsctedEdgecyliner == 1)
//				{
//					Vec3f itsctPos = p + ct *(u - p);
//#ifdef DRAW_INTSINFO
//					Affinef affpos;
//
//					affpos.Pos() = itsctPos;
//					render->SetMaterial(GRRenderIf::BROWN);
//					render->PushModelMatrix();
//					render->MultModelMatrix(affpos);
//					render->DrawBox(0.02f, 0.02f, 0.02f, true);
//					render->PopModelMatrix();
//#endif
//					float ct2;
//					Vec3f clsP;
//					CollisionFunctions::ClosestPtPointSegment(itsctPos, a, b, ct2, clsP);
//					Vec3f dyFaceNormal = (itsctPos - clsP).unit();
//
//					float norm = fabs((a - b).norm());
//					float segT = fabs((a - clsP).norm()) / norm;
//
//					////DA.AddTempDrawBall(itsctPos, myHc->c_obstRadius*0.5);
//					////DA.AddTempDrawFont3D(itsctPos, "ctc");
//
//					float dist = fabs((currSubStart - itsctPos).norm());
//					if (dist<nearestDist)
//					{
//						tmpcpinfo.cstType = PHOpHapticController::cstEdge;
//						tmpcpinfo.edgeidA = evid1;
//						tmpcpinfo.edgeidB = evid2;
//						tmpcpinfo.routet = ct;
//						tmpcpinfo.segmentt = segT;
//						tmpcpinfo.objid = obji;
//
//						//for insidecheck
//						bool sameinside = false;
//						if (cstrNum > 0 && sameCheck)
//						{
//							for (unsigned int samei = 0; samei<cstrNum; samei++)
//							{
//								if (tmpcpinfo.isSameCstr(myHc->cpiVec[samei]))
//								{
//									sameinside = true;
//#ifdef PrintProxySolveCheckInfo
//									DSTR << "same inside" << evid1 << "," << evid2 << endl;
//#endif
//								}
//							}
//
//						}
//						if (!sameinside)
//						{
//
//							cpinfo.cstType = PHOpHapticController::cstEdge;
//							cpinfo.edgeidA = evid1;
//							cpinfo.edgeidB = evid2;
//							cpinfo.routet = ct;
//							cpinfo.segmentt = segT;
//							cpinfo.objid = obji;
//							//dyFaceNormal.unitize();
//							//cpinfo.planeN = dyFaceNormal;
//							//cpinfo.planeN = (tgtMesh->normals[evid1] + tgtMesh->normals[evid2]) *0.5f;///not correct
//
//							//find connected face
//							bool otherFFind = false;
//							int j;
//							for (int fii = 0; fii < fsInRange.size(); fii++)
//							{
//								j = fsInRange[fii];
//								if (j == i) continue;
//								if (HasIinArr(evid1, myobj->objMeshFaces[j].indices, 3)
//									&& HasIinArr(evid2, myobj->objMeshFaces[j].indices, 3))
//								{
//									otherFFind = true;
//									break;
//								}
//							}
//							Vec3f &a1 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriCId]];
//							Vec3f e1N = ((b - a) % (a1 - a)).unit();
//							Vec3f &a2 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriAId]];
//							Vec3f &b2 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriBId]];
//							Vec3f &c2 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriCId]];
//							Vec3f e2N = ((b2 - a2) % (c2 - a2).unit());
//							if (otherFFind) cpinfo.planeN = ((e1N + e2N) * 0.5f).unit();
//							else cpinfo.planeN = dyFaceNormal;
//#ifdef USE_ShrinkReturn
//							itsctPos = itsctPos + dyFaceNormal *(1.0f - myHc->SolveShrinkRadio);
//#endif
//							cpinfo.planeP = itsctPos;
//							//DA.AddTempDrawLine(cpinfo.planeP, cpinfo.planeP + cpinfo.planeN);
//							//DA.AddTempDrawFont3D(cpinfo.planeP + cpinfo.planeN, "en");
//							nearestDist = dist;
//						}
//					}
//
//
//				}
//
//				//case B-C for Tri ABC
//				evid1 = myobj->objMeshFaces[i].indices[TriBId];
//				evid2 = myobj->objMeshFaces[i].indices[TriCId];
//
//				Vec3f &c =  myobj->objMeshVts[evid1];
//				Vec3f &d =  myobj->objMeshVts[evid2];
//
//				IsIntsctedEdgecyliner = CollisionFunctions::IntersectSegmentCylinder(p, u, c, d, myHc->c_obstRadius * myHc->SolveShrinkRadio, ct);
//				if (IsIntsctedEdgecyliner == 1)
//				{
//					Vec3f itsctPos = p + ct *(u - p);
//#ifdef DRAW_INTSINFO
//					Affinef affpos;
//
//					affpos.Pos() = itsctPos;
//					render->SetMaterial(GRRenderIf::BROWN);
//					render->PushModelMatrix();
//					render->MultModelMatrix(affpos);
//					render->DrawBox(0.02f, 0.02f, 0.02f, true);
//					render->PopModelMatrix();
//#endif
//
//
//					float ct2;
//					Vec3f clsP;
//					CollisionFunctions::ClosestPtPointSegment(itsctPos, c, d, ct2, clsP);
//					Vec3f dyFaceNormal = (itsctPos - clsP).unit();
//					float dist = fabs((currSubStart - itsctPos).norm());
//					float norm = fabs((c - d).norm());
//					float segT = fabs((c - clsP).norm()) / norm;
//
//					////DA.AddTempDrawBall(itsctPos, myHc->c_obstRadius);
//					////DA.AddTempDrawFont3D(itsctPos, "ctc");
//
//					if (dist<nearestDist)
//					{
//						tmpcpinfo.cstType = PHOpHapticController::cstEdge;
//						tmpcpinfo.edgeidA = evid1;
//						tmpcpinfo.edgeidB = evid2;
//						tmpcpinfo.routet = ct;
//						tmpcpinfo.segmentt = segT;
//						tmpcpinfo.objid = obji;
//
//
//						//for insidecheck
//						bool sameinside = false;
//						if (cstrNum > 0 && sameCheck)
//						{
//							for (unsigned int samei = 0; samei<cstrNum; samei++)
//							{
//								if (tmpcpinfo.isSameCstr(myHc->cpiVec[samei]))
//								{
//									sameinside = true;
//#ifdef PrintProxySolveCheckInfo
//									DSTR << "same inside" << evid1 << "," << evid2 << endl;
//#endif
//								}
//							}
//
//						}
//						if (!sameinside)
//						{
//
//							cpinfo.cstType = PHOpHapticController::cstEdge;
//							cpinfo.edgeidA = evid1;
//							cpinfo.edgeidB = evid2;
//							cpinfo.routet = ct;
//							cpinfo.segmentt = segT;
//							cpinfo.objid = obji;
//							/*dyFaceNormal.unitize();
//							cpinfo.planeN = dyFaceNormal;*/
//							//cpinfo.planeN = (tgtMesh->normals[evid1] + tgtMesh->normals[evid2]) *0.5f;
//
//							//find connected face
//							bool otherFFind = false;
//							int j;
//							for (int fii = 0; fii < fsInRange.size(); fii++)
//							{
//								j = fsInRange[fii];
//								if (j == i) continue;
//								if (HasIinArr(evid1, myobj->objMeshFaces[j].indices, 3)
//									&& HasIinArr(evid2, myobj->objMeshFaces[j].indices, 3))
//								{
//									otherFFind = true;
//									break;
//								}
//							}
//							Vec3f &e1 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriAId]];
//							Vec3f e1N = ((c - e1) % (d - e1)).unit();
//							Vec3f &a2 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriAId]];
//							Vec3f &b2 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriBId]];
//							Vec3f &c2 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriCId]];
//							Vec3f e2N = ((b2 - a2) % (c2 - a2).unit());
//							if (otherFFind) cpinfo.planeN = ((e1N + e2N) * 0.5f).unit();
//							else cpinfo.planeN = dyFaceNormal;
//
//#ifdef USE_ShrinkReturn
//							itsctPos = itsctPos + dyFaceNormal *(1.0f - myHc->SolveShrinkRadio);
//#endif
//							cpinfo.planeP = itsctPos;
//							//DA.AddTempDrawLine(cpinfo.planeP, cpinfo.planeP + cpinfo.planeN);
//							//DA.AddTempDrawFont3D(cpinfo.planeP + cpinfo.planeN, "en");
//							nearestDist = dist;
//						}
//					}
//
//
//				}
//
//				//case C-A for Tri ABC
//				evid1 = myobj->objMeshFaces[i].indices[TriAId];
//				evid2 = myobj->objMeshFaces[i].indices[TriCId];
//
//				Vec3f &e =  myobj->objMeshVts[evid1];
//				Vec3f &f =  myobj->objMeshVts[evid2];
//
//				IsIntsctedEdgecyliner = CollisionFunctions::IntersectSegmentCylinder(p, u, e, f, myHc->c_obstRadius * myHc->SolveShrinkRadio, ct);
//				if (IsIntsctedEdgecyliner == 1)
//				{
//					Vec3f itsctPos = p + ct *(u - p);
//#ifdef DRAW_INTSINFO
//					Affinef affpos;
//
//					affpos.Pos() = itsctPos;
//					render->SetMaterial(GRRenderIf::BROWN);
//					render->PushModelMatrix();
//					render->MultModelMatrix(affpos);
//					render->DrawBox(0.02f, 0.02f, 0.02f, true);
//					render->PopModelMatrix();
//#endif
//
//
//					float ct2;
//					Vec3f clsP;
//					CollisionFunctions::ClosestPtPointSegment(itsctPos, e, f, ct2, clsP);
//					Vec3f dyFaceNormal = (itsctPos - clsP).unit();
//					float dist = fabs((currSubStart - itsctPos).norm());
//					float norm = fabs((e - f).norm());
//					float segT = fabs((e - clsP).norm()) / norm;
//
//					////DA.AddTempDrawBall(itsctPos, myHc->c_obstRadius);
//					////DA.AddTempDrawFont3D(itsctPos, "ctc");
//
//					if (dist<nearestDist)
//					{
//
//						tmpcpinfo.cstType = PHOpHapticController::cstEdge;
//						tmpcpinfo.edgeidA = evid1;
//						tmpcpinfo.edgeidB = evid2;
//						tmpcpinfo.routet = ct;
//						tmpcpinfo.segmentt = segT;
//						tmpcpinfo.objid = obji;
//
//
//						//for insidecheck
//						bool sameinside = false;
//						if (cstrNum > 0 && sameCheck)
//						{
//							for (unsigned int samei = 0; samei<cstrNum; samei++)
//							{
//								if (tmpcpinfo.isSameCstr(myHc->cpiVec[samei]))
//								{
//									sameinside = true;
//#ifdef PrintProxySolveCheckInfo
//									DSTR << "same inside" << evid1 << "," << evid2 << endl;
//#endif
//								}
//							}
//
//						}
//						if (!sameinside)
//						{
//
//							cpinfo.cstType = PHOpHapticController::cstEdge;
//							cpinfo.edgeidA = evid1;
//							cpinfo.edgeidB = evid2;
//							cpinfo.routet = ct;
//							cpinfo.segmentt = segT;
//							cpinfo.objid = obji;
//							/*dyFaceNormal.unitize();
//							cpinfo.planeN = dyFaceNormal;*/
//							//cpinfo.planeN = (tgtMesh->normals[evid1] + tgtMesh->normals[evid2]) *0.5f;
//
//							//find connected face
//							bool otherFFind = false;
//							int j;
//							for (int fii = 0; fii < fsInRange.size(); fii++)
//							{
//								j = fsInRange[fii];
//								if (j == i) continue;
//								if (HasIinArr(evid1, myobj->objMeshFaces[j].indices, 3)
//									&& HasIinArr(evid2, myobj->objMeshFaces[j].indices, 3))
//								{
//									otherFFind = true;
//									break;
//								}
//							}
//							Vec3f &e1 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriBId]];
//							Vec3f e1N = ((e1 - e) % (f - e)).unit();
//							Vec3f &a2 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriAId]];
//							Vec3f &b2 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriBId]];
//							Vec3f &c2 =  myobj->objMeshVts[myobj->objMeshFaces[i].indices[TriCId]];
//							Vec3f e2N = ((b2 - a2) % (c2 - a2).unit());
//							if (otherFFind) cpinfo.planeN = ((e1N + e2N) * 0.5f).unit();
//							else cpinfo.planeN = dyFaceNormal;
//
//#ifdef USE_ShrinkReturn
//							itsctPos = itsctPos + dyFaceNormal *(1.0f - myHc->SolveShrinkRadio);
//#endif
//							cpinfo.planeP = itsctPos;
//							//	DA.AddTempDrawLine(cpinfo.planeP, cpinfo.planeP + cpinfo.planeN);
//							//	DA.AddTempDrawFont3D(cpinfo.planeP + cpinfo.planeN, "en");
//
//							nearestDist = dist;
//						}
//					}
//
//				}
//			}
//
//			//new for tstvertexBall
//			for (unsigned int vi = 0; vi<vsInRange.size(); vi++)
//			{
//				Vec3f &vP =  myobj->objMeshVts[vsInRange[vi]];
//
//
//				float vt;
//				Vec3f itsctPos;
//				IsIntsctedSphere = CollisionFunctions::IntersectSegmentSphere(p, (u - p).unit(), (u - p).norm(), vP, myHc->c_obstRadius * myHc->SolveShrinkRadio, vt, itsctPos);
//				if (IsIntsctedSphere == 1)
//				{
//#ifdef DRAW_INTSINFO
//					Affinef affpos;
//					render->SetMaterial(GRRenderIf::GREEN);
//					affpos.Pos() = itsctPos;
//					render->PushModelMatrix();
//					render->MultModelMatrix(affpos);
//					render->DrawBox(0.02f, 0.02f, 0.02f, true);
//					render->PopModelMatrix();
//
//
//					affpos.Pos() = vP;
//					render->SetMaterial(GRRenderIf::BROWN);
//					render->PushModelMatrix();
//					render->MultModelMatrix(affpos);
//					render->DrawSphere(myHc->c_obstRadius, 6, 6, false);
//					render->PopModelMatrix();
//#endif
//					Vec3f dyFaceNormal = (itsctPos - vP).unit();
//
//					float dist = fabs((currSubStart - itsctPos).norm());
//					if (dist<nearestDist)
//					{
//						tmpcpinfo.cstType = PHOpHapticController::cstPoint;
//						tmpcpinfo.objid = obji;
//						tmpcpinfo.vid = vsInRange[vi];
//
//						//for insidecheck
//						bool sameinside = false;
//						if (cstrNum > 0 && sameCheck)
//						{
//							for (unsigned int samei = 0; samei<cstrNum; samei++)
//							{
//								if (tmpcpinfo.isSameCstr(myHc->cpiVec[samei]))
//								{
//									sameinside = true;
//#ifdef PrintProxySolveCheckInfo
//									DSTR << "same inside v" << vsInRange[vi] << endl;
//#endif
//								}
//							}
//
//						}
//						if (!sameinside)
//						{
//
//							cpinfo.cstType = PHOpHapticController::cstPoint;
//							cpinfo.vid = vsInRange[vi];
//							cpinfo.objid = obji;
//							//cpinfo.planeN = dyFaceNormal;
//							cpinfo.planeN = myobj->objMeshNormals[vi];
//#ifdef USE_ShrinkReturn
//							itsctPos = itsctPos + dyFaceNormal *(1.0f - myHc->SolveShrinkRadio);
//#endif
//							cpinfo.planeP = itsctPos;
//
//							nearestDist = dist;
//						}
//					}
//
//
//				}
//			}
//
//		}
//
//		if (nearestDist<100.0f)
//		{
//			Vec3f nextP = userPoint - cpinfo.planeP;
//			float proj = nextP.dot(cpinfo.planeN);
//			float magni = fabs(proj);
//			newSubGoal = userPoint + cpinfo.planeN * magni;
//			newSubStart = cpinfo.planeP;
//
//			return true;
//
//		}
//		//}
//		return false;
//	}
//
//}
