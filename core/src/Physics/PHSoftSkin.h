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

	public:
		SPR_OBJECTDEF(PHSoftSkin);
		ACCESS_DESC(PHSoftSkin);

		PHSoftSkin()
		{
			solidNum = 0;
			particleNum = 0;
		}

		PHSolidIf* GetSkinBone(int boneId);
		void AddSkinBone(ObjectIf* solid);
		PHOpParticleIf* GetSkinPtcl(int pId);
		void AddSkinPtcl(ObjectIf* ptcl);
		/**
		* @brief boneid is the bone index in skBones, pId is the particle id in skSkinParticles
		*/
		void AddBoneToParticle(int boneid, int pId);
		void AddParticleToBone(int boneid, int pId);
		void ParticleSkinBlending();
		void CalBoneWeights();
		void UpdateBoneForces();
		int GetParticleNum() {			return particleNum;		}
		int GetSolidNum() { return solidNum; }

	};


}//namespace
#endif
