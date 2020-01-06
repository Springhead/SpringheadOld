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
bool PHSoftSkin::AddSkinBone(ObjectIf* solid)
{
	for (int bi = 0; bi < skBones.size(); bi++)
	{
		if (skBones[bi] == (PHSolid*)solid)
			return false;
	}
	skBones.emplace_back((PHSolid*)solid);
	vector<unsigned> tmp;
	skBoneParticleList.emplace_back(tmp);
	skBoneRestPoss.emplace_back(((PHSolid*)solid)->GetFramePosition());
	//skBoneParticleList.emplace_back(pinSolidList);
	solidNum++;
	return true;
}
bool PHSoftSkin::AddParticleToBone(int boneid, ObjectIf* ptcl)
{
	int pId = -1;
	PHOpParticleDesc* pd = (PHOpParticleDesc*)((PHOpParticleIf*)ptcl)->GetDescAddress();
	for (unsigned pi = 0; pi < skSkinParticles.size(); pi++)
	{
		if (skSkinParticles[pi]->GetParticleDesc()->pPId == pd->pPId
			&& skSkinParticles[pi]->GetParticleDesc()->pObjId == pd->pObjId)
			pId = pi;
	}

	if (pId < 0) return false;

	for (unsigned int i = 0; i<skBoneParticleList[boneid].size(); i++)
	{
		if (skBoneParticleList[boneid][i] == pId)
			return false;
	}
	skBoneParticleList[boneid].emplace_back(pId);
	return true;
}
PHOpParticleIf* PHSoftSkin::GetSkinPtcl(int pId)
{
	return (PHOpParticleIf*)this->skSkinParticles[pId]->GetObjectIf();
}
bool PHSoftSkin::AddSkinPtcl(ObjectIf* ptcl)
{
	//Check same particle
	PHOpParticleDesc* pd = (PHOpParticleDesc*)((PHOpParticleIf*)ptcl)->GetDescAddress();
	for (unsigned pi = 0; pi < skSkinParticles.size(); pi++)
	{
		if (skSkinParticles[pi]->GetParticleDesc()->pPId ==pd->pPId
			&& skSkinParticles[pi]->GetParticleDesc()->pObjId == pd->pObjId)
			return false;
	}


	skSkinParticles.emplace_back((PHOpParticle*)((PHOpParticleIf*)ptcl)->Cast());
	vector<unsigned> tmp;
	skPtclLinkedBoneList.emplace_back(tmp);
	particleNum++;
	return true;
}

/**
* @brief boneid is the bone index in skBones, pId is the particle id in skSkinParticles
*/
bool PHSoftSkin::AddBoneToParticle(int boneid, ObjectIf* ptcl)
{
	int pId = -1;
	PHOpParticleDesc* pd = (PHOpParticleDesc*)((PHOpParticleIf*)ptcl)->GetDescAddress();
	for (unsigned pi = 0; pi < skSkinParticles.size(); pi++)
	{
		if (skSkinParticles[pi]->GetParticleDesc()->pPId == pd->pPId
			&& skSkinParticles[pi]->GetParticleDesc()->pObjId == pd->pObjId)
			pId = pi;
	}

	if (pId < 0) return false;

	for (unsigned int i = 0; i<skPtclLinkedBoneList[pId].size(); i++)
	{
		if (skPtclLinkedBoneList[pId][i] == (unsigned)boneid)
			return false;
	} 
	skPtclLinkedBoneList[pId].emplace_back(boneid);
	return true;
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
	float dtSq = dt*dt;
	for (unsigned pi = 0; pi < skSkinParticles.size(); pi++)
	{
		assert(skPtclLinkedBoneList.size() == skSkinParticles.size());
		Vec3f pOrig = skSkinParticles[pi]->pLocalOrigCtr;
		Vec3f pNew; pNew.clear();
		//cout << "P" << endl;
		for (unsigned bi = 0; bi < skPtclLinkedBoneList[pi].size(); bi++)
		{
			assert(skiningWeight[pi].size() == skPtclLinkedBoneList[pi].size());
			PHSolid *so = skBones[skPtclLinkedBoneList[pi][bi]];
			//Vec3f pos = so->GetCenterPosition();
			Posef bPos = so->GetPose();
			//cout <<	bPos << endl;
			Vec3f solidRestpos = skBoneRestPoss[skPtclLinkedBoneList[pi][bi]];

			pNew += skiningWeight[pi][bi] * (bPos * (pOrig - solidRestpos));
		}
		skSkinParticles[pi]->pExternalForce = (pNew - skSkinParticles[pi]->pNewCtr) /(dtSq) * skSkinParticles[pi]->pTotalMass;
	}
}

void PHSoftSkin::UpdateBoneForces()
{
	for (unsigned bi = 0; bi < skBones.size(); bi++)
	{
		for (unsigned pi = 0; pi < skBoneParticleList.size(); pi++)
		{
			PHOpParticle *dp = skSkinParticles[pi];
			if(dp->pHapticForce.norm() > 0)
				skBones[bi]->AddForce(dp->pHapticForce);
		}
	}
}