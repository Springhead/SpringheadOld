#ifndef SPRFWOPOBJ_H
#define SPRFWOPOBJ_H

#include <Framework/SprFWObject.h>

namespace Spr{;


struct FWOpObjDesc :public FWObjectDesc{

	float fwPSize;
};

struct FWOpObjIf : FWObjectIf{
	SPR_IFDEF(FWOpObj);
	void Blend();

	///	�q�I�u�W�F�N�g�̐�
	 size_t NChildObject() const;
	///	�q�I�u�W�F�N�g�̎擾
	 ObjectIf* GetChildObject(size_t pos);
	///	�q�I�u�W�F�N�g�̒ǉ�
	 bool AddChildObject(ObjectIf* o);
	 void CreateOpObjWithRadius(float r);
	 void CreateOpObj();
	 ObjectIf* GetOpObj();
	 ObjectIf* GetGRMesh();
};

}
#endif