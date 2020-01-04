﻿/*
*  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team
*  All rights reserved.
*  This software is free software. You can freely use, distribute and modify this
*  software. Please deal with this software under one of the following licenses:
*  This license itself, Boost Software License, The MIT License, The BSD License.
*/
#ifndef PHOPOBJ_H
#define PHOPOBJ_H

#include <Physics/SprPHOpObj.h>
#include <Collision/SprCDShape.h>
#include <Physics/PHEngine.h>
#include <Foundation/Object.h>

#include <Physics/PHOpParticle.h>
#include <Physics/PHOpGroup.h>
#include <Physics/PHOpDecompositionMethods.h>
#include <Physics/PHSoftSkin.h>

#define GROUP_DISTANCE

using namespace PTM;

namespace Spr{
	;

	
	struct TriFace {
	int	nVertices;	///< 3 or 4
	int	indices[4];
	};
	class PHOpObj : public SceneObject, public PHOpObjDesc {
	
	public:
		SPR_OBJECTDEF(PHOpObj);
		ACCESS_DESC(PHOpObj);
		PHOpObj(const PHOpObjDesc& desc = PHOpObjDesc(), SceneIf* s = NULL) :PHOpObjDesc(desc)
		{
		
			gravityOn = false;

			objGrouplinkCount = 5;
			objMeshVtsNum = 0;
			objNoMeshObj = false;
			objUseDistCstr = false;
			objUseReducedPP = true;

			initialVtoPmap = false;
			initialtgV = false;
			initialGArr = false;
			initialOrgP = false;
			initialPArr = false;
			updateNormals = false;
			isRigid = false;

			objType = 0;
			objitrTime = 1;
			j.init();

			objSkin = DBG_NEW PHSoftSkin();
		}

		~PHOpObj()
		{
			if (initialGArr)
				delete[] objGArr;
			if (initialPArr)
				delete[] objPArr;
			if (initialOrgP)
				delete[] objOrigPos;
			if (initialVtoPmap)
				delete[] objVtoPmap;
			if (initialBlWei)
			{
				for (int i = 0; i < objMeshVtsNum; i++)
				{
					delete[] objBlWeightArr[i];

				}
				delete[] objBlWeightArr;
			}
			delete objSkin;
		}

		//Step計算用関数
		//void newReducedPositionProjectByOne(int i);
		//void ReducedPositionProjectByOne(int i);
		//void positionProjectByOne(int i);

		//新しいsimulation方法(慣性Matrixを更新、GoalPositionは平均ではなくそのまま）
		void newReducedPositionProject();
		//simpleの一回simulation過程のまとめる
		void SimpleSimulationStep();

		//shapematching計算をJacobi計算用の
		Jacobi j;
		//model頂点群データ
		//float objMeshVtsArr[10000];
		//float *objMeshVtsArr;

		//Triangle faces for haptic rendering (no need of GRMesh)
		std::vector<TriFace> objMeshFaces;
		//Triangle normals for haptic (no need of GRMesh)
		std::vector<Vec3f> objMeshNormals;
		//頂点の初期位置（Blendに使う）
		Vec3f* objOrigPos;
		//頂点の初期位置初期化flag
		bool initialOrgP;
		//粒子の配列初期化されたか
		bool initialPArr;
		//質量中心（開発中、未検証）
		//Vec3f objMassCenter;
		//頂点が粒子groupmemberに対する重み（Blendに使う）
		float** objBlWeightArr;
		//重み初期化されたか
		bool initialBlWei;
		//粒子の初期姿勢
		Spr::TPose<float> * objOrinPsPoseList;
		//頂点から粒子のmap
		int *objVtoPmap;
		//頂点粒子map初期化されたか
		bool initialVtoPmap;

		//粒子BVH（開発中）
		//BVHgOp *bvhGOps;

		//model頂点群
		Vec3f *objMeshVts;

		//model頂点群初期化されたか
		bool initialtgV;
		//model頂点群数
		//int objMeshVtsNum;
		//一時粒子group保存場
		std::vector<PHOpGroup> tmpPGroups;
		//粒子groupの配列
		PHOpGroup* objGArr;
		//粒子group初期化されたか
		bool initialGArr;


		//一時粒子保存場
		std::vector<PHOpParticle> tmpPtclList;
		//粒子の配列
		PHOpParticle *objPArr;//Memoryの考えで、ここで最後に保存しました


		//独立alpha使用switch（開発中）
		bool objUseIndepParam;
		//重力switch
		bool gravityOn;
		//軽量化計算関数switch
		bool objUseReducedPP;
		////粒子と表面meshとの対応関係
		std::vector<int> objFaceBelongs;

		std::vector<Vec3f> tmpVts;

		//record triangles for proxy CCD 
		std::vector<int> triListForProxyCCD;
		//record last vertices for CCD
		Vec3f *lastTargetVts;

		//int bvhNum;

		//Skin of the object that follows the solid bone
		PHSoftSkin* objSkin;


	private:
		//配置完了のlist（local用）
		std::vector<int> mPtclAssList;
	public:

		ObjectIf* GetObjSkin() {
			return objSkin->Cast();
		}

		bool GetDesc(void *desc)  {
			
			for(int vi=0;vi<objMeshVtsNum * 3 ;vi++)
			{
				((float*)desc)[vi] = objMeshVtsArr[vi];
			}

			return true;
		}
		float GetVtxBlendWeight(int Vtxi, int Grpi)
		{
			return objBlWeightArr[Vtxi][Grpi];
		}
		int GetobjVtoPmap(int vi)
		{
			return objVtoPmap[vi];
		}

		void SetGravity(bool bOn)
		{
			gravityOn = bOn;
		}

		/*void GetFirVertexData(float vData[])
		{
		vData = objMeshVtsArr;
		}*/
		//float (&GetFirVData())[10000]
		/*float *GetFirVData()
		{
			return objMeshVtsArr;
		}*/


		void InitialFloatVertexDataArr()
		{
			//objMeshVtsArr = new float[objMeshVtsNum * 3];
			//objMeshVtsArr[0] = new float[10000];
			for (int vi = 0; vi <objMeshVtsNum; vi++)
			{
				objMeshVtsArr[vi * 3] = objMeshVts[vi].x;
				objMeshVtsArr[vi * 3 + 1] = objMeshVts[vi].y;
				objMeshVtsArr[vi * 3 + 2] = objMeshVts[vi].z;
			}
			//int u = 0;
		}

		void UpdateItrTime(int itrT, bool useIndepParamflag)
		{
			objitrTime = itrT;
			objUseIndepParam = useIndepParamflag;
		}

		void SetDefaultLinkNum(int linkNum)
		{
			objGrouplinkCount = linkNum;
		}

		ObjectIf* GetOpParticle(int pi)
		{
			return objPArr[pi].Cast();
		}
		ObjectIf* GetOpGroup(int gi)
		{
			return objGArr[gi].Cast();
		}


		void DynamicRadiusUpdate()
		{
			for (int pi = 0; pi < assPsNum; pi++)
			{
				PHOpParticle &dp = objPArr[pi];
				float maxD = 0;
				for (int vi = 0; vi < dp.pNvertex; vi++)
				{
					Vec3f &v = objMeshVts[dp.pVertArr[vi]];
					float dist = fabs((v - dp.pCurrCtr).norm());
					if (dist > maxD)
						maxD = dist;
				}
				dp.pDynamicRadius = maxD;
				if (dp.pNvertex == 1)
					dp.pDynamicRadius = objAverRadius;
			}

		}


		bool assignPtcl(int vIndex)
		{
			if (mPtclAssList.size() == 0)
			{
				mPtclAssList.push_back(vIndex);
				return true;
			}
			for (int i = 0; i < (int)mPtclAssList.size(); i++)
			{
				if (mPtclAssList[i] == vIndex)
				{
					//DSTR<<"Particle already assigned "<<i<<std::endl;
					return false;
				}

			}
			mPtclAssList.push_back(vIndex);
			return true;
		}


		void DistanceConstrain();

		//simulation
		void groupStep();


		void positionPredict();


		void positionProject();


		void ReducedPositionProject();

		//pNewCtrからpCurrCtrへ更新

		void integrationStep();


		void summationTogAgroup();


		void dampVelocities();


		void AddInternalParticle(Vec3f &Pos)//, int* linkPs, int linkNum)
		{
			int i = assPsNum;



			std::vector<DisCmpPoint> disCmpQue;
			DisCmpPoint tmpdcp;

			Vec3f p2;
			float distance;
			for (int j = 0; j < assGrpNum; j++)
			{
				if (j == i)continue;
				p2 = objPArr[j].pOrigCtr;

				p2 = Pos - p2;
				distance = fabs(p2.norm());
				tmpdcp.distance = distance;
				tmpdcp.pIndex = j;

				disCmpQue.push_back(tmpdcp);

			}
			std::sort(disCmpQue.begin(), disCmpQue.end());
			//int u = 0;

			PHOpGroup* pg = new PHOpGroup();
			pg->gMyIndex = i;
			pg->gPInd.push_back(i);
			pg->gNptcl++;

			int linkCount = objGrouplinkCount;
			for (int k = 0; k < linkCount; k++)
			{
				pg->addPInds(disCmpQue[k].pIndex);
				//build groupInfo for particle ,particle \ngs to...
				objPArr[disCmpQue[k].pIndex].pInGrpList.push_back(i);

			}

			assPsNum++;
			PHOpParticle* newpList = new PHOpParticle[assPsNum];
			for (int j = 0; j < assPsNum - 1; j++)
			{
				newpList[j] = objPArr[j];
			}

			objPArr = newpList;
			objPArr[assPsNum - 1].pPId = assPsNum - 1;
			objPArr[assPsNum - 1].pObjId = this->objId;
			for (int k = 0; k < linkCount; k++)
			{
				objPArr[assPsNum - 1].pInGrpList.push_back(disCmpQue[k].pIndex);
			}
			objPArr[assPsNum - 1].pRadii = 0.5f;//debug
			objPArr[assPsNum - 1].pMyGroupInd = i;
			objPArr[assPsNum - 1].pTotalMass = 1.0f;
			objPArr[assPsNum - 1].pOrigCtr = Pos;
			objPArr[assPsNum - 1].pCurrCtr = Pos;
			objPArr[assPsNum - 1].pNewCtr = Pos;
			//objPArr[assPsNum-1].pType = 1;

			assGrpNum++;
			PHOpGroup* gplist = new PHOpGroup[assGrpNum];
			for (int j = 0; j < assGrpNum - 1; j++)
			{
				gplist[j] = objGArr[j];
			}
			objGArr = gplist;
			objGArr[assGrpNum - 1] = *pg;

			buildGroupCenter();
			BuildBlendWeight();
			//int u2 = 0;

			delete pg;
			delete gplist;
			delete newpList;
		}


		void vertexBlending()
		{
			
			for (int j = 0; j < assPsNum; j++)
			{

				PHOpGroup &pg = objGArr[objPArr[j].pMyGroupInd];
				//頂点はグループのメンバーに対して重みをかけて位置を計算する
				for (int k = 0; k < objPArr[j].pNvertex; k++)
				{
					int vertind = objPArr[j].pVertArr[k];
					Vec3f &vert = objOrigPos[vertind];
					Vec3f u; u = u.Zero();
					
					int startFromLinkP = 0;
					for (int jm = startFromLinkP; jm < pg.gNptcl; jm++)
					{

						PHOpParticle &dp = objPArr[pg.getParticleGlbIndex(jm)];

						//Spr::TPose<float> &ctrpose = TPose<float>(dp.pOrigCtr,dp.pOrigOrint);//ctrP.pOrigCtr,ctrP.pOrigOrint
						//ctrpose= ctrpose.Inv();
						//boost!1
						Spr::TPose<float> &ctrpose = objOrinPsPoseList[pg.getParticleGlbIndex(jm)];

					
						Spr::TPose<float> pose = TPose<float>(dp.pCurrCtr, dp.pCurrOrint);
						
						pose.x = -pose.x;
						pose.y = -pose.y;
						pose.z = -pose.z;
					
						//ver.1 boost1
						//u += blWeightArr[vertind][jm] * (pose * (ctrpose * vert));// (taM *
						//ver.2 boost2
						u += objBlWeightArr[vertind][jm] * (pose * (ctrpose.Pos() + vert));// (taM *

						//u += taB * (vert * blWeightArr[vertind][jm]);// (taM *//debug 
						//int ks = 0;
					}
					//if (useTetgen)

					objMeshVts[vertind] = u;
					objMeshVtsArr[vertind * 3] = u.x;
					objMeshVtsArr[vertind * 3 + 1] = u.y;
					objMeshVtsArr[vertind * 3 + 2] = u.z;

				}
			}
#ifdef USEGRMESH
			//	 calc normal
			// 頂点を共有する面の数
			if (updateNormals)
			{
				std::vector<int> nFace(objMeshVtsNum, 0);

				for (unsigned i = 0; i < targetMesh->triFaces.size(); i += 3){
					Vec3f n = (targetMesh->vertices[targetMesh->triFaces[i + 1]] - targetMesh->vertices[targetMesh->triFaces[i]])
						% (targetMesh->vertices[targetMesh->triFaces[i + 2]] - targetMesh->vertices[targetMesh->triFaces[i]]);
					n.unitize();

					targetMesh->normals[targetMesh->triFaces[i]] += n;
					targetMesh->normals[targetMesh->triFaces[i + 1]] += n;
					targetMesh->normals[targetMesh->triFaces[i + 2]] += n;
					nFace[targetMesh->triFaces[i]] ++;
					nFace[targetMesh->triFaces[i + 1]] ++;
					nFace[targetMesh->triFaces[i + 2]] ++;
				}

				for (unsigned i = 0; i < targetMesh->normals.size(); ++i)
					targetMesh->normals[i] /= nFace[i];
			}
#else
			
#endif
		}

		Matrix3f SolveShpMchByJacobi(PHOpGroup &pg);


		bool InitialObjUsingLocalBuffer(float pSize, int objGrpLinkNum = -1)
		{
			int vtsNum = (int)tmpVts.size();
			Vec3f* vts = new Vec3f[vtsNum];

			for (int vi = 0; vi < vtsNum; vi++)
			{
				vts[vi] = tmpVts[vi];
			}
			ClearLocalVtsBuffer();

			objOrigPos = new Vec3f[vtsNum];
			initialOrgP = true;
			objMeshVts = vts;//Tetgenため使う
			objMeshVtsNum = vtsNum;
			lastTargetVts = DBG_NEW Vec3f[vtsNum];

			if (objGrpLinkNum < 0)
				objGrpLinkNum = objGrouplinkCount;

			InitialFloatVertexDataArr();

			initialDeformVertex(vts, vtsNum);
			if (!BuildParticles(vts, vtsNum, tmpPtclList, pSize, objGrpLinkNum))
				return false;

			return true;

			
		}

		void ClearLocalVtsBuffer()
		{
			std::vector<Vec3f> cl;
			cl.swap(tmpVts);
		}
		
		void AddVertextoLocalBuffer(Vec3f v)
		{
			tmpVts.push_back(v);
		}

		bool initialPHOpObj(Vec3f *vts, int vtsNum, float pSize, int objGrpLinkNum = -1)
		{
			objOrigPos = new Vec3f[vtsNum];
			initialOrgP = true;
			objMeshVts = vts;//Tetgenため使う
			objMeshVtsNum = vtsNum;
			lastTargetVts = DBG_NEW Vec3f[vtsNum];

			if (objGrpLinkNum < 0)
				objGrpLinkNum = objGrouplinkCount;

			InitialFloatVertexDataArr();

			initialDeformVertex(vts, vtsNum);
			if (!BuildParticles(vts, vtsNum, tmpPtclList, pSize, objGrpLinkNum))
				return false;

			return true;
		}



		bool BuildParticles(Vec3f *vts, int vtsNum, std::vector<PHOpParticle> &dParticleArr, float pSize, int objGrpLinkNum)
		{

			float distance;
			PHOpParticle *dp = new PHOpParticle();

#ifdef TIME_DISPLAY
			mt.startMyTimer();
#endif
			Vec3f beginP, diameterP;
			float objPtclRadius = pSize;

			//decide particle pos & add vertexes to particles
			//Particle自動生成手順
			//最初の頂点からparticle直径範囲内他の頂点を探す、
			//見つかった全ての頂点を一つのparticleにあげる
			//Simple Particle auto generation
			//From first vertex, find other vertex inside particle diameter
			//add all found vetices into one particle ->loop			
			for (int i = 0; i < vtsNum; i++)
			{

				if (!assignPtcl(i))
					continue;
				dp->addNewVertex(i);
				beginP = vts[i];

				for (int j = 0; j < vtsNum; j++)
				{
					diameterP = vts[j];
					diameterP = beginP - diameterP;
					distance = fabs(diameterP.norm());
					if (distance < objPtclRadius)
					{
						if (assignPtcl(j))
						{
							dp->addNewVertex(j);

						}

					}
				}
				dp->pObjId = objId;
				dp->pRadii = objPtclRadius;//debug origin radius

				dParticleArr.push_back(*dp);
				delete dp;
				dp = new PHOpParticle();

			}
			delete dp;

			//Particleに関する情報を生成する
			//Build Particle propoties
			objAverRadius = 0.0f;
			objMaxRadius = 0.0f;
			//objMassCenter = Vec3f(0, 0, 0);
			for (int i = 0; i < (int)dParticleArr.size(); i++)
			{
				PHOpParticle &dp = dParticleArr[i];
				int nsize = dp.pNvertex;
				Vec3f *varr; varr = new Vec3f[nsize];
				for (int j = 0; j < nsize; j++)
					varr[j] = vts[dParticleArr[i].pVertTempInd[j]];

				dp.ptclBuildStep(varr);
				dp.swapVectorToArr();

				objAverRadius += dp.pMainRadius;

				if (dp.pMainRadius > objMaxRadius)
					objMaxRadius = dp.pMainRadius;
				delete[] varr;
			}
			objAverRadius /= dParticleArr.size();

			for (int i = 0; i < (int)dParticleArr.size(); i++)
			{
				PHOpParticle &dp = dParticleArr[i];
				//initial dynamicRadius
				dp.pDynamicRadius = objAverRadius;
				//cal masscenter 
				//objMassCenter += dp.pCurrCtr;

			}
			//objMassCenter = objMassCenter / dParticleArr.size();

			DSTR << "Particle Assignment Finished " << std::endl;

#ifdef TIME_DISPLAY
			mt.endMyTimer();
			mt.printElastedTime();

			mt.startMyTimer();
#endif
			//Particle groupを作る
			//buildGroup
			Vec3f p1, p2;
			//int  nearest[4];
			//predistance = 1000;
			std::vector<DisCmpPoint> disCmpQue;
			DisCmpPoint tmpdcp;

			//particlegroup生成自動化手順
			//最初のparticleから,
			//link 数決める時 
			//ある限り隣のparticleをgroupに入れる  ->loop
			//link 数足りない時
			//あるだけ隣のparticleをgroupに入れる  ->loop
			for (int i = 0; i < (int)dParticleArr.size(); i++)
			{
				dParticleArr[i].pMyGroupInd = i;

				dParticleArr[i].pMainRadius *= objMaxRadius;
				dParticleArr[i].pSecRadius *= objMaxRadius;
				dParticleArr[i].pThrRadius *= objMaxRadius;


				p1 = dParticleArr[i].pOrigCtr;
				tmpdcp.distance = 0.0;
				tmpdcp.pIndex = i;
				disCmpQue.push_back(tmpdcp);
				for (int j = 0; j < (int)dParticleArr.size(); j++)
				{
					if (j == i)continue;
					p2 = dParticleArr[j].pOrigCtr;

					p2 = p1 - p2;
					distance = fabs(p2.norm());
					tmpdcp.distance = distance;
					tmpdcp.pIndex = j;

					disCmpQue.push_back(tmpdcp);

				}
				//隣particleへの距離のsort
				std::sort(disCmpQue.begin(), disCmpQue.end());


#ifdef GROUP_DISTANCE
				PHOpGroup  pg;

				distance = pSize;

				distance += 0.1f;

#endif 
				//build link  
				int linkCount = 0;
				//use limited linklength or constant linkCount
				for (int k = 0; k < (int)disCmpQue.size(); k++)
				{
					if (disCmpQue[k].distance <= distance)
						linkCount++;

				}
				if (linkCount < (int)disCmpQue.size())
					linkCount = objGrpLinkNum; //debug linkCount
				else linkCount = (int)disCmpQue.size();

				if ((int)dParticleArr.size() < linkCount)
					linkCount = (int)dParticleArr.size() - 1;

				pg.gMyIndex = i;
				pg.gPInd.push_back(i);
				pg.gNptcl++;
				for (int k = 0; k < linkCount; k++)
				{
					pg.addPInds(disCmpQue[k].pIndex);
					//build groupInfo for particle ,particle belongs 
					dParticleArr[disCmpQue[k].pIndex].pInGrpList.push_back(i);

				}


				tmpPGroups.push_back(pg);
				swapDisCmpQue(disCmpQue);
			}
			DSTR << "Particle Assignment Finished " << std::endl;
#ifdef TIME_DISPLAY
			mt.endMyTimer();
			mt.printElastedTime();

			mt.startMyTimer();
#endif
			//Arrayへmemoryを変える


			swapMemParticle(dParticleArr);

			swapMemGroup();

			//connect each other groups
			for (int i = 0; i < assPsNum; i++)
			{
				PHOpParticle &dp = objPArr[i];
				PHOpGroup  &pg = objGArr[i];


				int Ingrpsize = (int)dp.pInGrpList.size();
				for (int pin = 0; pin < Ingrpsize; pin++)
				{

					if (pg.addPInds(dp.pInGrpList[pin]))
						objPArr[dp.pInGrpList[pin]].pInGrpList.push_back(i);

					//int u = 0;
				}

			}

			//build weight relation between vertices to particle center
			//buildDisWeightForVsinP();

			//face情報の入力
			//buildFaceInfoInP();

			//VertexからOpまでの逆mapをつくる
			BuildMapFromVtoP();

			//buildGroupCenter
			buildGroupCenter();

#ifdef TIME_DISPLAY
			mt.endMyTimer();
			mt.printElastedTime();
#endif
			//particlegroupweightを作る
			//initial blend weight
			BuildBlendWeight();

			//Particle初期姿勢を記憶する(blendingに使う)
			StoreOrigPose();

			//Initial PHSoftSkin particles
			for (int pi = 0; pi < assPsNum; pi++)
			{
				objSkin->AddSkinPtcl(objPArr[pi].Cast());
			}

			return true;
		}



		void buildParticleMomentInertia()
		{
			for (int j = 0; j < assPsNum; j++)
			{
				PHOpParticle &dp = objPArr[j];
				Matrix3f &pMIMatrix = dp.pMomentInertia;
				for (int i = 0; i < dp.pNvertex; i++)
				{
					Vec3f p = objMeshVts[dp.pVertArr[i]] - dp.pCurrCtr;
					pMIMatrix.xx += p.y * p.y + p.z * p.z;
					pMIMatrix.xy += -p.x * p.y;
					pMIMatrix.xz += -p.x * p.z;
					pMIMatrix.yx += -p.y * p.x;
					pMIMatrix.yy += p.x * p.x + p.z * p.z;
					pMIMatrix.yz += -p.y * p.z;
					pMIMatrix.zx += -p.z * p.x;
					pMIMatrix.zy += -p.z * p.y;
					pMIMatrix.zz += p.x * p.x + p.y * p.y;

				}
				pMIMatrix = pMIMatrix * dp.pTotalMass;
				dp.pInverseOfMomentInertia = pMIMatrix.inv();
			}

		}



		void buildDisWeightForVsinP()
		{
			DSTR << "BuildDisWeightForVsinP" << std::endl;
			if (objNoMeshObj)
				return;
			for (int j = 0; j < assPsNum; j++)
			{
				float totalDis = 0.0f;
				objPArr[j].pVectDisWeightArr = new float[objPArr[j].pNvertex];
				objPArr[j].initialWArr = true;
				for (int k = 0; k < objPArr[j].pNvertex; k++)
				{
					Vec3f &vp = objMeshVts[objPArr[j].pVertArr[k]];
					totalDis += (vp - objPArr[j].pCurrCtr).norm();

				}

				for (int k = 0; k < objPArr[j].pNvertex; k++)
				{
					Vec3f &vp = objMeshVts[objPArr[j].pVertArr[k]];
					if (totalDis == 0.0f)
					{
						objPArr[j].pVectDisWeightArr[k] = 1;
						continue;
					}
					objPArr[j].pVectDisWeightArr[k] = (vp - objPArr[j].pCurrCtr).norm() / totalDis;

				}
				//int u = 0;
			}

		}

		void buildGroupCenter()
		{
			DSTR << "BuildGroupCenter" << std::endl;
			for (int i = 0; i < assGrpNum; i++)
			{
				objGArr[i].gOrigCenter = objGArr[i].gOrigCenter.Zero();
				objGArr[i].gtotalMass = 0.0f;
				//build group totalmass
				for (int j = 0; j < objGArr[i].gNptcl; j++)
				{
					PHOpParticle &dp = objPArr[objGArr[i].getParticleGlbIndex(j)];
					objGArr[i].gOrigCenter += dp.pOrigCtr * dp.pTotalMass;
					objGArr[i].gtotalMass += dp.pTotalMass;
				}
				objGArr[i].gOrigCenter /= objGArr[i].gtotalMass;
				objGArr[i].gCurrCenter = objGArr[i].gOrigCenter;
			}

		}

		void StoreOrigPose()
		{
			//Particle初期姿勢を記憶する(blendingに使う)
			//build Oringinal Pose of Ps
			objOrinPsPoseList = new TPose<float>[assPsNum];
			for (int j = 0; j < assPsNum; j++)
			{
				Spr::TPose<float> ctrpose = TPose<float>(objPArr[j].pOrigCtr, objPArr[j].pOrigOrint);
				ctrpose = ctrpose.Inv();
				objOrinPsPoseList[j] = ctrpose;
			}
		}
		void BuildBlendWeight()
		{
			DSTR << "BuildBlendWeight" << std::endl;
			//build linear blend skin weight

			int size = 0;
			if (objNoMeshObj)
			{
				objBlWeightArr = new float*[1];
				objBlWeightArr[0] = new float[1];
				objBlWeightArr[0][0] = 1;
				initialBlWei = true;
				return;
			}

			size = objMeshVtsNum;

			objBlWeightArr = new float*[size];
			initialBlWei = true;
			for (int j = 0; j < assPsNum; j++)
			{

				Vec3f CenterPs = objPArr[j].pOrigCtr;
				PHOpGroup pg = objGArr[objPArr[j].pMyGroupInd];
				int gpSize = pg.gNptcl;//
				for (int k = 0; k < objPArr[j].pNvertex; k++)
				{//Particle内すべてvertexに対して

					std::vector<float> distancelist;
					float distanceSum = 0.0;
					int vertind = objPArr[j].pVertArr[k];
					Vec3f vert;

					vert = objMeshVts[vertind];

					float tmpdis = (CenterPs - vert).norm();
					distanceSum += tmpdis;//vertexからすべてlinkしてParticleの距離を計算する
					distancelist.push_back(tmpdis);

					float* linkWeight = new float[gpSize];
					float weightsum = 0.0;
					objBlWeightArr[vertind] = new float[gpSize];

					if (distancelist[0] == 0.0f)
					{
						objBlWeightArr[vertind][0] = 1.0;
						for (int jm = 1; jm < gpSize; jm++)
						{
							objBlWeightArr[vertind][jm] = 0.0;
						}
						continue;
					}

					for (int jm = 1; jm < gpSize; jm++)
					{//すべてlinkされたParticleに対して

						//PHOpParticle linkPs = objPArr[pg.getParticleGlbIndex(jm)];
						Vec3f linkPsCenter = objPArr[pg.getParticleGlbIndex(jm)].pOrigCtr;
						float tmpdis = (linkPsCenter - vert).norm();
						distanceSum += tmpdis;
						distancelist.push_back(tmpdis);
					}
					for (int jm = 0; jm < gpSize; jm++)
					{
						linkWeight[jm] = distanceSum / distancelist[jm];
						weightsum += linkWeight[jm];

					}
					for (int jm = 0; jm < gpSize; jm++)
					{
						objBlWeightArr[vertind][jm] = linkWeight[jm] / weightsum;

					}

				}
			}


		}

		//Build inverse relation from vertex to particle


		void BuildMapFromVtoP()
		{
			DSTR << "BuildMapFromVtoP" << std::endl;
			if (this->objNoMeshObj)return;
			objVtoPmap = new int[objMeshVtsNum];
			initialtgV = true;
			for (int pi = 0; pi < assPsNum; pi++)
			{
				for (int vi = 0; vi < objPArr[pi].pNvertex; vi++)
					objVtoPmap[objPArr[pi].pVertArr[vi]] = pi;
			}
			//int u = 0;
		}


		//Build face infomation inside each Particle 
		//void buildFaceInfoInP()
		//{
		//	for (int i = 0; i<assPsNum; i++)
		//	{
		//		PHOpParticle &dp = objPArr[i];
		//		//if(targetMesh)return;
		//		if (objType>0)return;
		//		if (targetMesh->faces[0].nVertices == 4)
		//		{
		//			DSTR << "faces[0].nVertices==4 please check model or edit code" << std::endl;
		//		}
		//		int facesize = targetMesh->faces.size();
		//		for (int im = 0; im < facesize; im++)
		//		{
		//			std::vector<int> fidx;
		//			int faceVNum = targetMesh->faces[im].nVertices;
		//			for (int fic = 0; fic<faceVNum; fic++)
		//				fidx.push_back(targetMesh->faces[im].indices[fic]);
		//
		//			int count = faceVNum;
		//			bool found = false;
		//			for (int checkin = 0; checkin < faceVNum; checkin++)
		//			{
		//				for (int jm = 0; jm < dp.pNvertex; jm++)
		//				{
		//					int vidx1 = dp.pVertArr[jm];
		//					//if(count==0) 
		//					//	break;
		//					std::vector<int>::iterator iter = std::find(fidx.begin(), fidx.end(), vidx1);
		//					if (iter != fidx.end())
		//					{
		//						found = true;
		//						iter = std::find(dp.pFaceInd.begin(), dp.pFaceInd.end(), im);
		//						if (iter == dp.pFaceInd.end())
		//						{
		//							dp.pFaceInd.push_back(im);
		//							//dp.pVtoFs.insert(dp.pVtoFs.begin()+jm,im);
		//							DSTR << "Face " << im << " detected in " << i << std::endl;
		//						}
		//						break;
		//					}
		//
		//				}
		//				if (found) break;
		//			}
		//
		//			fidx.~vector();
		//		}
		//		int u = 0;
		//	}
		//}


		//clear the memory of the vector used
		void swapMemGroup()
		{
			assGrpNum = (int)tmpPGroups.size();
			objGArr = new PHOpGroup[assGrpNum];
			initialGArr = true;
			for (int i = 0; i < assGrpNum; i++)
			{
				objGArr[i] = tmpPGroups[i];
			}
			std::vector<PHOpGroup> s;

			s.swap(tmpPGroups);
		}

		//clear memory
		void swapDisCmpQue(std::vector<DisCmpPoint> &dcp)
		{
			std::vector<DisCmpPoint> s;
			s.swap(dcp);
		}

		//clear memory
		void swapMemParticle(std::vector<PHOpParticle> &dParticleArr)
		{
			assPsNum = (int)dParticleArr.size();
			objPArr = new PHOpParticle[assPsNum];
			initialPArr = true;
			for (int i = 0; i < assPsNum; i++)
			{
				objPArr[i] = dParticleArr[i];
				objPArr[i].pPId = i;
			}
			std::vector<PHOpParticle> s;

			s.swap(dParticleArr);
		}


		//DeformVertex初期化
		void initialDeformVertex(Vec3f *vts, int vtsNum)
		{
			for (int i = 0; i < vtsNum; i++)
			{
				objOrigPos[i] = vts[i];
			}
		}
		float GetblWeight(int vertexIndex, int linkPIndex)
		{
			return objBlWeightArr[vertexIndex][linkPIndex];
		}
		//PHOpObjIf* GetMyIf();

		int GetVertexNum()
		{
			return objMeshVtsNum;
		}
		Vec3f GetVertex(int vi)
		{
			return objMeshVts[vi];
		}
		struct ObjectParams
		{
		public:
			ObjectParams()
			{
				setDefaults();
			}

			Vec3f gravity;
			float timeStep;
			CDBounds bounds;//挙動範囲

			float alpha;
			float beta;
			float gama;

			bool quadraticMatch;
			bool volumeConservation;


			bool allowFlip;

			float veloDamping;


			inline void setDefaults()
			{
				timeStep = 0.01f;


				gravity = gravity.Zero();
				gravity.y = -9.81f;
				float boundcube = 3.0;
				bounds.min.x = -boundcube;
				bounds.min.y = -boundcube;
				bounds.min.z = -boundcube;
				bounds.max.x = boundcube;
				bounds.max.y = boundcube;
				bounds.max.z = boundcube;

				alpha = 1.0f;
				beta = 0.00f;
				gama = 1.0f;

				quadraticMatch = false;
				volumeConservation = false;

				allowFlip = false;

				veloDamping = 0.05f;

			}
			inline void SetBound(float boundLength)
			{
				float boundcube = boundLength;
				bounds.min.x = -boundcube;
				bounds.min.y = -boundcube;
				bounds.min.z = -boundcube;
				bounds.max.x = boundcube;
				bounds.max.y = boundcube;
				bounds.max.z = boundcube;
			}

		}params;
		float GetObjAlpha()
		{
			return params.alpha;
		}
		void SetObjAlpha(float alpha)
		{
			params.alpha = alpha;
		}
		float GetObjBeta()
		{
			return params.beta;
		}
		void SetObjBeta(float beta)
		{
			params.beta = beta;
		}
		float GetTimeStep()
		{
			return params.timeStep;
		}
		void SetTimeStep(float t)
		{
			params.timeStep = t;
		}
		void SetBound(float b)
		{
			params.SetBound(b);
		}
		float GetBoundLength()
		{
			return (params.bounds.max.x);
		}
		float GetVelocityDamping()
		{
			return params.veloDamping;
		}
		void SetVelocityDamping(float vd)
		{
			params.veloDamping = vd;
		}
		void SetObjItrTime(int itrT)
		{
			objitrTime = itrT;
		}
		int GetObjItrTime()
		{
			return objitrTime;
		}
		void SetObjDstConstraint(bool d)
		{
			objUseDistCstr = d;
		}
		bool GetObjDstConstraint()
		{
			return objUseDistCstr;
		}
		PHOpParticle& getObjParticle(int pIndex)
		{
			return objPArr[pIndex];
		}
		PHOpGroup& getObjPGroup(int groupIndex)
		{
			return objGArr[groupIndex];
		}
		void FindObjctBound()
		{
			float minX = 0.0, maxX = 0.0;
			float minY = 0.0, maxY = 0.0;
			float minZ = 0.0, maxZ = 0.0;
			//int axis = 0;
			if (assPsNum>0)
			{
				minX = objPArr[0].pCurrCtr.x;
				maxX = minX;
				minY = objPArr[0].pCurrCtr.y;
				maxY = minY;
				minZ = objPArr[0].pCurrCtr.z;
				maxZ = minZ;
			}

			for (int i = 0; i<assPsNum; i++)
			{
				if (minX>objPArr[i].pCurrCtr.x)
					minX = objPArr[i].pCurrCtr.x;
				if (maxX<objPArr[i].pCurrCtr.x)
					maxX = objPArr[i].pCurrCtr.x;

				if (minY>objPArr[i].pCurrCtr.y)
					minY = objPArr[i].pCurrCtr.y;
				if (maxY<objPArr[i].pCurrCtr.y)
					maxY = objPArr[i].pCurrCtr.y;

				if (minZ>objPArr[i].pCurrCtr.z)
					minZ = objPArr[i].pCurrCtr.z;
				if (maxZ<objPArr[i].pCurrCtr.z)
					maxZ = objPArr[i].pCurrCtr.z;

			}


		}


	};



}// namespace

#endif
