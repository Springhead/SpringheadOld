#ifndef SPR_PHSKELETON_H
#define SPR_PHSKELETON_H

#include <SprFoundation.h>
#include <SprPhysics.h>
#include <Foundation/Object.h>
#include <vector>

namespace Spr{;

class PHBone : public SceneObject{

	PHSolidIf* solid;
	PHSolidIf* proxySolid;
	PHJointIf* joint;
	PHBoneIf*  parent;

	Posed      lastPose;

	std::vector<PHBoneIf*> children;

public:
	Quaterniond lastJointPose;

	SPR_OBJECTDEF(PHBone);

	/** @brief �f�t�H���g�R���X�g���N�^
	*/
	PHBone(){ solid = NULL; proxySolid = NULL; joint = NULL; parent = NULL; lastPose = Posed(); lastJointPose = Quaterniond(); }

	/** @brief Solid��ݒ肷��
	 */
	void SetSolid(PHSolidIf* solid) { this->solid = solid; }

	/** @brief Solid���擾����
	 */
	PHSolidIf* GetSolid() { return solid; }

	/** @brief Proxy Solid��ݒ肷��
	 */
	void SetProxySolid(PHSolidIf* solid) { this->proxySolid = solid; }

	/** @brief Proxy Solid���擾����
	 */
	PHSolidIf* GetProxySolid() { return proxySolid; }

	/** @brief Joint��ݒ肷��
	 */
	void SetJoint(PHJointIf* joint) { this->joint = joint; }

	/** @brief Joint���擾����
	 */
	PHJointIf* GetJoint() { return joint; }

	/** @brief �eBone��ݒ肷��
	 */
	void SetParent(PHBoneIf* parent) { this->parent = parent; }

	/** @brief �eBone���擾����
	 */
	PHBoneIf* GetParent() { return parent; }

	/** @brief �{�[���̒������Z�b�g����
	 */
	void SetLength(double length);

	/** @brief �{�[���̌������Z�b�g����i�q�{�[����Position�������ɃZ�b�g����j
	 */
	void SetDirection(Vec3d dir);

	/** @brief �{�[���̈ʒu���Z�b�g����
	 */
	void SetPosition(Vec3d pos);

	// ----- ----- ----- ----- -----

	virtual bool        AddChildObject(ObjectIf* o) {
		if (DCAST(PHBoneIf,o)) { children.push_back(o->Cast()); return true; }
		return false;
	}
	virtual ObjectIf*   GetChildObject(size_t pos)  { return children[pos];   }
	virtual size_t      NChildObject() const        { return children.size(); }
	
};

class PHSkeleton : public SceneObject{
public:

	std::vector< UTRef<PHBone> > bones;

	float grabStrength;

	SPR_OBJECTDEF(PHSkeleton);

	/** @brief �f�t�H���g�R���X�g���N�^
	*/
	PHSkeleton(){ }

	/** @brief Bone�̐����擾����
	 */
	int NBones() { return (int)(bones.size()); }

	/** @brief Bone���擾����
	 */
	PHBoneIf* GetBone(int i) { return bones[i]->Cast(); }

	/** @brief Bone���쐬����
	 */
	PHBoneIf* CreateBone(PHBoneIf* parent, const PHBoneDesc& desc = PHBoneDesc()) {
		PHBone* bone = DBG_NEW PHBone();
		bone->SetDesc(&desc);
		bones.push_back(bone);
		bone->SetScene(GetScene());
		return bone->Cast();
	}

	/** @brief �͂�ł�x���擾����
	 */
	float GetGrabStrength() { return grabStrength; }
};

}

#endif
