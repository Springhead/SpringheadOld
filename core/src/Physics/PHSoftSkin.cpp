#include "PHSoftSkin.h"

using namespace Spr;

PHSolidIf* PHSoftSkin::GetSkinBone(int boneId)
{
	if (this->skBones.size() < (unsigned)boneId) {
		DSTR << "Error! lack bone num" << std::endl;
		return NULL;
	}
	return (PHSolidIf*)this->skBones[boneId]->GetObjectIf();
}
void PHSoftSkin::AddSkinBone(ObjectIf* solid)
{
	skBones.emplace_back((PHSolid*)solid);
	vector<unsigned> tmp;
	skBoneParticleList.emplace_back(tmp);
	//skBoneParticleList.emplace_back(pinSolidList);
	solidNum++;
}
void PHSoftSkin::AddParticleToBone(int boneid, int pId)
{
	for (unsigned int i = 0; i<skBoneParticleList[boneid].size(); i++)
	{
		if (skBoneParticleList[boneid][i] == pId)
			return;
	}
	skBoneParticleList[boneid].emplace_back(pId);
}
PHOpParticleIf* PHSoftSkin::GetSkinPtcl(int pId)
{
	return (PHOpParticleIf*)this->skSkinParticles[pId]->GetObjectIf();
}
void PHSoftSkin::AddSkinPtcl(ObjectIf* ptcl)
{
	this->skSkinParticles.emplace_back((PHOpParticle*)((PHOpParticleIf*)ptcl)->Cast());
	vector<unsigned> tmp;
	skPtclLinkedBoneList.emplace_back(tmp);
	particleNum++;
}

/**
* @brief boneid is the bone index in skBones, pId is the particle id in skSkinParticles
*/
void PHSoftSkin::AddBoneToParticle(int boneid, int pId)
{
	for (unsigned int i = 0; i<skPtclLinkedBoneList[pId].size(); i++)
	{
		if (skPtclLinkedBoneList[pId][i] == (unsigned)boneid)
			return;
	}
	skPtclLinkedBoneList[pId].emplace_back(boneid);
}

void PHSoftSkin::CalBoneWeights()
{
	skiningWeight.resize(skPtclLinkedBoneList.size());
	for (unsigned pi = 0; pi < skPtclLinkedBoneList.size(); pi++)
	{
		assert(skPtclLinkedBoneList.size() == skSkinParticles.size());
		std::vector<float> distancelist;
		float distanceSum = 0.0;
		Vec3f pPos = skSkinParticles[pi]->pOrigCtr;
		skiningWeight[pi].resize(skPtclLinkedBoneList[pi].size());
		
		for (unsigned bi = 0; bi < skPtclLinkedBoneList[pi].size(); bi++)
		{
			PHSolid *so = skBones[skPtclLinkedBoneList[pi][bi]];
			Posef bPos = so->GetPose();
			float tmpdis = (bPos.Pos() - pPos).norm();
			distanceSum += tmpdis;//vertex‚©‚ç‚·‚×‚ÄƒŠƒ“ƒN‚µ‚ÄParticle‚Ì‹——£‚ðŒvŽZ‚·‚é
			distancelist.emplace_back(tmpdis);
			
		}

		float weightsum = 0.0;

		for (unsigned bi = 0; bi < skPtclLinkedBoneList[pi].size(); bi++)
		{
			weightsum += distanceSum / distancelist[bi];
		}
		for (unsigned bi = 0; bi < skPtclLinkedBoneList[pi].size(); bi++)
		{
			skiningWeight[pi][bi] = (distanceSum / distancelist[bi]) / weightsum;
		}
	}
}

void PHSoftSkin::ParticleSkinBlending()
{

	for (unsigned pi = 0; pi < skSkinParticles.size(); pi++)
	{
		assert(skPtclLinkedBoneList.size() == skSkinParticles.size());
		Vec3f pOrig = skSkinParticles[pi]->pOrigCtr;
		Vec3f pNew; pNew.clear();

		for (unsigned bi = 0; bi < skPtclLinkedBoneList[pi].size(); bi++)
		{
			assert(skiningWeight[pi].size() == skPtclLinkedBoneList[pi].size());
			PHSolid *so = skBones[skPtclLinkedBoneList[pi][bi]];
			Posef bPos = so->GetPose();

			pNew += skiningWeight[pi][bi] * (bPos.Ori() * (pOrig - bPos.Pos()));
		}
		skSkinParticles[pi]->pNewCtr = pNew;
	}
}

void PHSoftSkin::UpdateBoneForces()
{
	for (unsigned bi = 0; bi < skBones.size(); bi++)
	{
		for (unsigned pi = 0; pi < skBoneParticleList.size(); pi++)
		{
			PHOpParticle *dp = skSkinParticles[pi];
			skBones[bi]->AddForce(dp->pExternalForce);
		}
	}
}