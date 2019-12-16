#include "PHSoftSkin.h"

using namespace Spr;

PHSolidIf* PHSoftSkin::GetSkinBone(int boneId)
{
	if (this->skBones.size() < boneId) {
		DSTR << "Error! lack bone num" << std::endl;
		return NULL;
	}
	return (PHSolidIf*)this->skBones[boneId]->GetObjectIf();
}
void PHSoftSkin::AddSkinBone(PHSolidIf* solid)
{
	this->skBones.emplace_back((PHSolid*)solid);
}
PHOpParticleIf* PHSoftSkin::GetSkinPtcl(int pId)
{
	return (PHOpParticleIf*)this->skSkinParticles[pId]->GetObjectIf();
}
void PHSoftSkin::AddSkinPtcl(PHOpParticleIf* ptcl)
{
	this->skSkinParticles.emplace_back((PHOpParticle*)ptcl);
}