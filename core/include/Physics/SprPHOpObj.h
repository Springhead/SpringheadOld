/*
 *  Copyright (c) 2003-2008, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
#ifndef SPR_PHOPOBJ_H
#define SPR_PHOPOBJ_H

#include <Foundation/SprObject.h>

namespace Spr{;
class PHOpHapticController;

///	���̂̃X�e�[�g
struct PHOpObjState{
	Vec3d		velocity;		///<	���ʒ��S�̑��x		(World�n)
	Vec3d		angVelocity;	///<	�p���x				(World�n)
//	Vec3d		lastVelocity;	///<	�O��̑��x			(World�n)
//	Vec3d		lastAngVelocity;///<	�O��̊p���x			(World�n)
	Posed		pose;			///<	���W���_�̈ʒu�ƌ���	(World�n)
//	Posed		lastPose;		///<	�O��̈ʒu�ƌ���		(World�n)
};

struct PHOpHapticRendererDesc{
	float extForceSpring;
	float outForceSpring;
	float constraintSpring;
	float timeStep;
	float forceOnRadius;

	bool useConstrainForce;
	bool useProxyfixSubitr;
	bool useIncreaseMeshMove;
	bool sqrtAlphaForce;
	bool hitWall;
	bool useDualTranFix;
	bool rigid;

	int proxyItrtNum;
	int proxyItrtMaxNum;
	int currDtType;
	int objNum;
	int noCtcItrNum;

	Vec3f proxyFixPos;
};

struct PHOpObjDesc : public PHOpObjState{
	double		mass;			///<	����
	Matrix3d	inertia;		///<	�����e���\��	(Local�n)
	Vec3d		center;			///<	���ʒ��S�̈ʒu	(Local�n)
	bool		dynamical;		///<	�����@���ɏ]����(���x�͐ϕ������)

	////model���_�Q
	Vec3f *objTargetVts;
	
	//model���_�f�[�^
	float objTargetVtsArr[10000];

	//model���_�Q��
	int objTargetVtsNum;
	//���q�̐�
	int assPsNum;
	//���qgroup�̐�
	int assGrpNum;
	
	//���qgroup��link���萔
	int objGrouplinkCount;
	//ObjectID
	int objId;
	//�����S����switch
	bool objUseDistCstr;
	//Mesh�������Ă��Ȃ�Object
	bool objNoMeshObj;
	//���̂�
	bool isRigid;
	//�͊oObject�Ƌ�ʂ̂��ߎg��
	int objType;
	//���a�̕���
	float objAverRadius;
	//���a�̕���
	float objMaxRadius;

	//�J��Ԃ������v��
	int objitrTime;

	//FaceNormal��Blend�̂Ƃ��ɍX�V���邩
	bool updateNormals;


	PHOpObjDesc(){ Init(); }
	void Init(){
		mass = 1.0f;
		inertia = Matrix3d::Unit();
		dynamical = true;
	}
};

struct CDShapeIf; 
struct PHTreeNodeIf;

///	���̂̃C���^�t�F�[�X
struct PHOpObjIf : public SceneObjectIf {
	SPR_IFDEF(PHOpObj);
	
	
	bool initialPHOpObj(Vec3f *vts, int vtsNum, float pSize);
	void		SetGravity(bool bOn);
	void SimpleSimulationStep();

	void AddVertextoLocalBuffer(Vec3f v);
	bool InitialObjUsingLocalBuffer(float pSize);

	void positionPredict();
	void positionPredictFriction(PHOpHapticController* myHc);
	void groupStep();
	void integrationStep();
	void ReducedPositionProject();
	void positionProject();
	void SetDefaultLinkNum(int linkNum);

	void BuildBlendWeight();
	void buildGroupCenter();
	int GetVertexNum();
	Vec3f GetVertex(int vi);
	ObjectIf* GetOpParticle(int pi);
	ObjectIf* GetOpGroup(int gi);
	int GetobjVtoPmap(int vi);
	float GetVtxBlendWeight(int Vtxi, int Grpi);
	
	void SetVelocityDamping(float vd);
	float GetVelocityDamping();
	float GetBoundLength();
	void SetBound(float b);
	void SetTimeStep(float t);
	float GetTimeStep();
	float GetObjBeta();
	void SetObjBeta(float beta);
	void SetObjAlpha(float alpha);
	float GetObjAlpha();
	bool GetObjDstConstraint();
	void SetObjDstConstraint(bool d);
	void SetObjItrTime(int itrT);
	int GetObjItrTime();
	void StoreOrigPose();


};
struct PHOpParticleDesc {

	//���_��
	int pNvertex;
	//�����̃O���[�vid
	int pMyGroupInd;
	//���q��id
	int pPId;
	//����obj��id
	int pObjId;
	//���q�d���W��alpha(�J����)
	float pParaAlpha;
	//�}�E�X�ɐG��ꂽ���t���O
	bool hitedByMouse;
	//���_�����ʁi���j
	float pSingleVMass;
	//���q�̑������ʁi�J�����j
	float pTotalMass;
	
	//���q�����a�i���Ƃ��Ĉ������Ɏg���j
	float pRadii;
	//���I���q���a
	float pDynamicRadius;
	//�唼�avector
	Vec3f pMainRadiusVec;
	//�����avector
	Vec3f pSecRadiusVec;
	//�]���avector
	Vec3f pThrRadiusVec;
	//�唼�a
	float pMainRadius;
	//�����a
	float pSecRadius;
	//�]���a
	float pThrRadius;
	//���q�̌��݈ʒu
	Vec3f pCurrCtr;
	//���q�̏����ʒu
	Vec3f pOrigCtr;
	//���q�̗\���ʒu
	Vec3f pNewCtr;
	//���q�̑��x
	Vec3f pVelocity;
	//SPhash �Ɍ��o���ꂽ��
	bool isColliedbySphash;
	//ColliCube�Ɍ��o���ꂽ��
	bool isColliedbyColliCube;
	//�}�E�X�ɂ��܂ꂽ��
	bool isFixedbyMouse;
	//�Œ肵�Ă邩
	bool isFixed;
	//SPhash �ɉ������ׂ���
	bool isColliedSphashSolved;
	//SPhash �ɂ܂��Ȃ��������ׂ���
	bool isColliedSphashSolvedReady;
	
	//�O��
	Vec3f pExternalForce;
	//not yet been used
	Vec3f pExternalTorque;//not yet been used
	//not yet been used
	Vec3f pExternalDisplacement;
	//�܂ރ��b�V����index
	std::vector<int> pFaceInd;
	
	//���q���[�����g�s��
	Matrix3f pMomentR;
	//���q�������]�s��
	Matrix3f pSmR;
	
	//���_�������[�����g 
	Matrix3f pMomentInertia;
	//���_�������[�����g�̋t 
	Matrix3f pInverseOfMomentInertia;
	//���_�̎听������PCA�ɂ��ȉ~�̌����s��
	Matrix3f ellipRotMatrix;
	//���q�ŗL�����AellipRotMatrix����
	Quaternionf ellipOrigOrint;
	//���q�p���x
	Vec3f pWvel;//�p���x�A�����͑��x�̑傫���A�����͑��x�̕���
	//used to precalculation in Collision Detection;
	Matrix3f pPreEllipA;

	//���݌���
	Quaternionf pCurrOrint;
	//��������
	Quaternionf pOrigOrint;
	//�\������
	Quaternionf pNewOrint;
	

};
struct PHOpGroupDesc {
	//���q�O���[�v��id
	int gMyIndex;
	//�O���[�v�̃��[�����g�s��
	Matrix3f gAgroup;
	//�O���[�v�̌ŗL�x�N�g���Q
	Matrix3f gEigen;
	//�O���[�v�̎���
	float gtotalMass;
	//�������S
	Vec3f gOrigCenter;
	//���ݒ��S
	Vec3f gCurrCenter;
	//���̃O���[�v�Ɋ܂ޗ��q�̐�
	int gNptcl;
};
struct PHOpParticleIf : public ObjectIf{
	SPR_IFDEF(PHOpParticle);
	int GetOpPtclVtxId(int vi);
	int GetinGrpListNum();
	int GetinGrpList(int gi);
	float GetVtxDisWeight(int vi);
	PHOpParticleDesc* GetParticleDesc();
};
struct PHOpGroupIf : public ObjectIf{
	SPR_IFDEF(PHOpGroup);

	int GetGrpInPtclNum();
	int GetGrpInPtcl(int gi);
	PHOpGroupDesc* GetGroupDesc();
};
struct PHOpHapticControllerDesc
{
	float posScale;
	float rotScale;
	float forceScale;
	Vec3f userPos;
	Posef userPose;
	Vec3f hcCurrPPos;
	Vec3f hcCurrUPos;
	Vec3f hcLastUPos;
	Vec3f hcFixsubGoal;
	float c_obstRadius;

	int hpObjIndex;
	enum HapticDOFType
	{
		_3DOF,
		_6DOF,
	};

	HapticDOFType hcType;
	bool logForce;
	bool hcReady;
	bool IsSetForceReady;

	int fileindex;
	Vec3f lastHpRateF;
	bool hcCollied;
	//proxy
	int constrainCount;//used in dynamic constrain feel, indicate the constrainNum now
	int constrainCountHc;//used in Haptic rate
	Vec3f couterPlaneN;
	float hcElmDtcRadius;
	int collectCount;
	int collectItrtor;
	bool hcProxyOn;
	int suspObjid;

	float proxyRadius;
	int surrCnstrs;// detected constrains Num before fix

	enum cstrainType{
		cstPoint = 1,
		cstEdge,
		cstFace

	};

	struct PvsHcCtcPInfo
	{
		int ptclIndex;
		int objIndex;
		Vec3f ctcPos;
	};

};
struct PHOpHapticControllerIf : public SceneObjectIf{
	SPR_IFDEF(PHOpHapticController);

	void SetHCForceReady(bool flag);
	bool GetHCForceReady();
	bool CheckProxyState();
	void AddColliedPtcl(int pIndex, int objindex, Vec3f ctcPos);
	bool BeginLogForce();
	void EndLogForce();
	void setC_ObstacleRadius(float r);
	Vec3f GetUserPos();
	Vec3f GetHCPosition();
	void SetHCReady(bool flag);
	bool GetHCReady();
	void SetHCPosition(Vec3f pos);
	void SetHCPose(Posef pose);
	Posef GetHCPose();
	float GetC_ObstacleRadius();
	Vec3f GetCurrentOutputForce();
};
struct PHOpHapticRendererIf : public SceneObjectIf{
	SPR_IFDEF(PHOpHapticRenderer);
#ifdef USEGRMESH
	void ProxySlvPlane();
	void ProxyMove();
	void ProxyTrace();
	bool ProxyCorrection();
	void ForceCalculation();
	void setForceOnRadius(float r);
	void SetForceSpring(float k);
	float GetForceSpring();
	void SetConstraintSpring(float k);
	float GetConstraintSrping();

	void HpNoCtcProxyCorrection();
	void HpConstrainSolve(Vec3f &currSubStart);
	void BuildVToFaceRelation();
	void BuildEdgeInfo();
#endif
	void SetRigid(bool set);
	bool IsRigid();
};

struct PHOpAnimationDesc  {

	struct OpAnimationStruct
	{
		int animatedPindex;
		int animatedObjindex;
		int animatedType;
		int animatedHoldtimes;

		Vec3f animatedForces;
		Vec3f animatedPStarts;
		Vec3f animatedPEnds;

	};
	float timestep;
};
struct PHOpAnimationIf :public  SceneObjectIf, public PHOpAnimationDesc{
	SPR_IFDEF(PHOpAnimation);

	void AddAnimationP(int objIndex, int pIndex, Vec3f start, Vec3f end, float totalTime);
	void AddAnimationP(int objIndex, int pIndex, Vec3f force, float totalTime);
	void AnimationStep(void* opEngine);
	void AnimationIntergration(void* opEngine);
	
};



}	//	namespace Spr
#endif
