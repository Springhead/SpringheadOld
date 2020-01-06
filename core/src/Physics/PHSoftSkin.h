#ifndef PHSOFTSKIN_H
#define PHSOFTSKIN_H

#include <Physics/SprPHOpObj.h>
#include "PHSolid.h"
#include "PHOPParticle.h"

using namespace std;

namespace Spr
{
	/**
	@function 
	1.Store Particle-Bone connection

	*/
	class PHSoftSkin : public SceneObject, public PHSoftSkinDesc
	{


	private:
		vector<PHSolid*> skBones;
		vector<PHOpParticle*> skSkinParticles;
		/** @brief store skining weight of skin particles, where particle i's weights of bone j is store
		*/
		vector<vector<float> > skiningWeight;
		vector<vector<unsigned> > skPtclLinkedBoneList;
		vector<vector<unsigned> > skBoneParticleList;
		vector<Vec3f> skBoneRestPoss;

	public:
		SPR_OBJECTDEF(PHSoftSkin);
		ACCESS_DESC(PHSoftSkin);

		PHSoftSkin()
		{
			solidNum = 0;
			particleNum = 0;
			dt = 0.01f;
		}

		PHSolidIf* GetSkinBone(int boneId);
		bool AddSkinBone(ObjectIf* solid);
		PHOpParticleIf* GetSkinPtcl(int pId);
		bool AddSkinPtcl(ObjectIf* ptcl);
		/**
		* @brief boneid is the bone index in skBones, pId is the particle id in skSkinParticles
		*/
		bool AddBoneToParticle(int boneid, ObjectIf* ptcl);
		bool AddParticleToBone(int boneid, ObjectIf* ptcl);
		void ParticleSkinBlending();
		void CalBoneWeights();
		void UpdateBoneForces();
		int GetParticleNum() {			return particleNum;		}
		int GetSolidNum() { return solidNum; }
		void SetDeltaT(float dttmp) { dt = dttmp; }
		float GetDeltaT(float dt) { return dt; }


	};


}//namespace
#endif
