#ifndef PHSOFTSKIN_H
#define PHSOFTSKIN_H

#include "PHSolid.h"
#include "PHOPParticle.h"

namespace Spr
{

	class PHSoftSkin : public SceneObject
	{
	private:
		std::vector<PHSolid*> skBones;
		std::vector<PHOpParticle*> skSkinParticles;


	public:
		PHSolidIf* GetSkinBone(int boneId);
		void AddSkinBone(PHSolidIf* solid);
		PHOpParticleIf* GetSkinPtcl(int pId);
		void AddSkinPtcl(PHOpParticleIf* ptcl);
	};


}//namespace
#endif
