﻿/*
 *  Copyright (c) 2003-2012, Shoichi Hasegawa and Springhead development team 
 *  All rights reserved.
 *  This software is free software. You can freely use, distribute and modify this 
 *  software. Please deal with this software under one of the following licenses: 
 *  This license itself, Boost Software License, The MIT License, The BSD License.   
 */
#ifndef PH_JOINT_MOTOR_H
#define PH_JOINT_MOTOR_H

#include <Physics/SprPHJoint.h>
#include <Physics/SprPHJointMotor.h>
#include <Physics/PhysicsDecl.hpp>
#include <Physics/PHConstraint.h>
#include <memory>

namespace Spr{;

struct JointFunctions {
	static double resistCalc(double d, double k_1, double k_2, double k_3, double k_4);
	static Vec2d ResistanceTorque(PH1DJointIf* jo, void* param);
	static Vec2d PD(PH1DJointIf* jo, void* param);

	static Vec2d ResistanceTorque(int a, PHBallJointIf* jo, void* param);
	static Vec2d PD(int a, PHBallJointIf* jo, void* param);
};

template<int NDOF> class PHNDJoint;

class PHJoint;
class PH1DJoint;
class PHBallJoint;
class PHSpring;

///	パラメータ一覧（1D/3D/6Dを共通で扱えるようにするためのデスクリプタもどき）
template<int NDOF>
class PHNDJointMotorParam {
public:
	typedef PTM::TVector<NDOF,double> VecNd;

	// State
	VecNd			fAvg;
	SpatialVector   xs;
	bool            bYielded;
	// Desc
	VecNd           spring;
	VecNd           damper;
	VecNd           secondDamper;
	VecNd           targetVelocity;
	VecNd           offsetForce;
	double          yieldStress;
	double          hardnessRate;
};

///	N自由度関節の関節コントローラ
template<int NDOF>
class PHNDJointMotor : public PHConstraintBase{
public:
	typedef PTM::TVector<NDOF,double> VecNd;

	/// コントロールの対象となる関節
	PHJoint* joint;

	VecNd	fMinDt;
	VecNd	fMaxDt;

	///< 現在のばね部の距離（三要素モデル用）
	SpatialVector newXs;

	/// コンストラクタ
	PHNDJointMotor() {}

	// ----- PHConstraintBaseの仮想関数
	virtual void SetupAxisIndex();
	virtual void Setup         ();
	virtual bool Iterate       ();
	virtual void CompResponse      (double df, int i);
	virtual void CompResponseDirect(double df, int i);

	/// 拘束軸を決定する
	//virtual void SetupAxisIndex();

	/// dA, dbを計算する
	//virtual void CompBias();

	// ----- このクラスの機能

	/// 弾性変形用のCompBias
	void CompBiasElastic();

	/// 塑性変形用のCompBias
	void CompBiasPlastic();

	/// 降伏したかどうか
	void CheckYielded();

	// ----- 派生クラスで実装する機能
	/// propVを計算する
	virtual VecNd GetPropV() { return VecNd(); }

	/// パラメータを取得する
	virtual void GetParams(PHNDJointMotorParam<NDOF>& p) {}

	/// パラメータを反映する
	virtual void SetParams(PHNDJointMotorParam<NDOF>& p) {}
};

///	1自由度関節の関節コントローラ
class PH1DJointMotor : public SceneObject, public PHNDJointMotor<1> {
public:
	SPR_OBJECTDEF(PH1DJointMotor);
	SPR_DECLMEMBEROF_PH1DJointMotorDesc;

	/// コンストラクタ
	PH1DJointMotor(const PH1DJointMotorDesc& desc = PH1DJointMotorDesc()) { SetDesc(&desc); }

	// ----- PHNDJointMotorの派生クラスで実装する機能
	/// propVを計算する(位置差分)
	virtual PTM::TVector<1,double> GetPropV();

	/// パラメータを取得する
	virtual void GetParams(PHNDJointMotorParam<1>& p);

	/// パラメータを反映する
	virtual void SetParams(PHNDJointMotorParam<1>& p);
};

//非線形の親クラス作ろうか？
class PH1DJointNonLinearMotor : public PH1DJointMotor {
public:
	SPR_OBJECTDEF(PH1DJointNonLinearMotor);
	SPR_DECLMEMBEROF_PH1DJointNonLinearMotorDesc;

	PH1DJointNonLinearMotor(const PH1DJointNonLinearMotorDesc& desc = PH1DJointNonLinearMotorDesc()) { 
		SetDesc(&desc); 
		springFunc = 0;
		damperFunc = 0;
		offset = 0;
	}

	Vec2d (*fpFunc)(PH1DJointIf* , void* );
	int springFunc;
	int damperFunc;

	void SetFuncFromDatabase(int i, void* param);
	void SetFuncFromDatabase(int i, int j, void* sparam, void* dparam);

	double targetPos;
	void* springParam;
	void* damperParam;

	double offset;

	// ----- PHNDJointMotorの派生クラスで実装する機能(この二つはオーバーライドしないとダメそう)
	/// propVを計算する(位置差分)
	virtual PTM::TVector<1, double> GetPropV();
	/// パラメータを取得する
	virtual void GetParams(PHNDJointMotorParam<1>& p);
};

/// 1自由度人体関節特性抵抗モータ
class PHHuman1DJointResistance : public PH1DJointNonLinearMotor {
public:
	SPR_OBJECTDEF(PHHuman1DJointResistance);
	SPR_DECLMEMBEROF_PHHuman1DJointResistanceDesc;

	PHHuman1DJointResistance(const PHHuman1DJointResistanceDesc& desc = PHHuman1DJointResistanceDesc()) {
		SetDesc(&desc);
		springFunc = 1;
		damperFunc = 1;
		springParam = new Vec4d(desc.coefficient);
		damperParam = new Vec4d(desc.coefficient);
		offset = 0;
	}

	double GetCurrentResistance();
};

///	球関節の関節コントローラ
class PHBallJointMotor : public SceneObject, public PHNDJointMotor<3> {
public:
	SPR_OBJECTDEF(PHBallJointMotor);
	SPR_DECLMEMBEROF_PHBallJointMotorDesc;

	/// コンストラクタ
	PHBallJointMotor(const PHBallJointMotorDesc& desc = PHBallJointMotorDesc()) { SetDesc(&desc); }

	// ----- PHNDJointMotorの派生クラスで実装する機能
	/// propVを計算する
	virtual PTM::TVector<3,double> GetPropV();

	/// パラメータを取得する
	virtual void GetParams(PHNDJointMotorParam<3>& p);

	/// パラメータを反映する
	virtual void SetParams(PHNDJointMotorParam<3>& p);
};

class PHBallJointNonLinearMotor : public PHBallJointMotor {
public:
	SPR_OBJECTDEF(PHBallJointNonLinearMotor);
	SPR_DECLMEMBEROF_PHBallJointNonLinearMotorDesc;

	PHBallJointNonLinearMotor(const PHBallJointNonLinearMotorDesc& desc = PHBallJointNonLinearMotorDesc()) { 
		SetDesc(&desc);
		springFunc = Vec3i();
		damperFunc = Vec3i();
		offset = Vec3d();
	}

	Vec3i springFunc;
	Vec3i damperFunc;

	void SetFuncFromDatabase(Vec3i i, Vec3i j, void* sparam[], void* dparam[]);
	void SetFuncFromDatabaseN(int n, int i, int j, void* sparam, void* dparam);

	Vec3d targetPos;
	void* springParam[3];
	void* damperParam[3];

	Vec3d offset;

	// ----- PHNDJointMotorの派生クラスで実装する機能(この二つはオーバーライドしないとダメそう)
	/// propVを計算する(位置差分)
	virtual PTM::TVector<3, double> GetPropV();
	/// パラメータを取得する
	virtual void GetParams(PHNDJointMotorParam<3>& p);

};

/// 3自由度人体関節特性抵抗モータ
class PHHumanBallJointResistance : public PHBallJointNonLinearMotor {
public:
	SPR_OBJECTDEF(PHHumanBallJointResistance);
	SPR_DECLMEMBEROF_PHHumanBallJointResistanceDesc;

	PHHumanBallJointResistance(const PHHumanBallJointResistanceDesc& desc = PHHumanBallJointResistanceDesc()) {
		SetDesc(&desc);
		springFunc = Vec3i(1, 1, 1);
		damperFunc = Vec3i(1, 1, 1);
		springParam[0] = new Vec4d(desc.xCoefficient);
		springParam[1] = new Vec4d(desc.yCoefficient);
		springParam[2] = new Vec4d(desc.zCoefficient);
		damperParam[0] = new Vec4d(desc.xCoefficient);
		damperParam[1] = new Vec4d(desc.yCoefficient);
		damperParam[2] = new Vec4d(desc.zCoefficient);
		offset = Vec3d();
	}

	Vec3d GetCurrentResistance();
};

///	バネダンパのコントローラ
class PHSpringMotor : public SceneObject, public PHNDJointMotor<6> {
public:
	SPR_OBJECTDEF(PHSpringMotor);
	SPR_DECLMEMBEROF_PHSpringMotorDesc;

	/// コンストラクタ
	PHSpringMotor() {}

	// ----- PHNDJointMotorの派生クラスで実装する機能
	/// propVを計算する
	virtual PTM::TVector<6,double> GetPropV();

	/// パラメータを取得する
	virtual void GetParams(PHNDJointMotorParam<6>& p);

	/// パラメータを反映する
	virtual void SetParams(PHNDJointMotorParam<6>& p);
};

}

#endif//PH_JOINT_MOTOR_H
