#	Do not edit. RunSwig.bat will update this file.
#pragma SWIG nowarn=-401-325
%module Physics
//-- 
#define PyAPI_FUNC(r)	r			
#define LONG_MAX		0X7FFFFFFFL	
#define UCHAR_MAX		0xFF		
#define NULL			0			
#undef __PYDECL					
#define __PYDECL					
#undef SPR_CDECL					
#define SPR_CDECL					
#undef SPR_DLL						
#define SPR_DLL					
//---
%ignore Spr::PHSolidIf::AddShapes;
%ignore Spr::PHIKActuatorIf::GetRawSolution;
%ignore Spr::PHSceneIf::GetSolids;
%ignore Spr::PHJoint1DIf::GetRange;
%ignore Spr::PHSceneIf::SetContactMode(PHSolidIf **,size_t,PHSceneDesc::ContactMode);
%ignore Spr::PHSceneIf::SetContactMode(PHSolidIf **,size_t);
%ignore Spr::PHSceneIf::GetSolidPair(PHSolidIf*, PHSolidIf*, bool&);
%ignore Spr::PHSceneIf::GetPerformanceMeasure;
%ignore Spr::PHHapticEngineIf::Callback;
%ignore Spr::PHHapticEngineIf::SetCallbackBeforeStep;
%ignore Spr::PHHapticEngineIf::SetCallbackAfterStep;
%ignore Spr::PHHapticPointerIf::GetHapticForce;
%ignore Spr::PHHapticPointerIf::GetProxyVelocity;
%ignore Spr::PHFemVibrationIf::AddBoundaryCondition;
%ignore Spr::PHFemVibrationIf::AddVertexForceW;
%ignore Spr::PHFemMeshThermoIf::GetKMatInTet;
%ignore Spr::PHGenericJointCallback;
%ignore Spr::PHGenericJointIf::SetCallback;
%ignore Spr::PHFemThermoIf::GetKMatInTet;

// 2016/04/06 for dailybuild
%ignore Spr::PHSceneIf::GetOpEngine;
%ignore Spr::PHOpSpHashColliAgentIf::Initial;

%ignore Spr::PHHapticEngineIf::SetCallbackBeforeStep;
%ignore Spr::PHHapticEngineIf::SetCallbackAfterStep;
%ignore Spr::PHOpObjDesc;
%ignore Spr::PHOpObjIf;
%ignore Spr::PHOpEngineIf;

// 2017/08/30 for dailybuild
%ignore Spr::PH1DJointIf::CreateMotor;
%ignore Spr::PH1DJointIf::AddMotor;
%ignore Spr::PH1DJointIf::GetMotors;
%ignore Spr::PHBallJointIf::CreateMotor;
%ignore Spr::PHBallJointIf::AddMotor;
%ignore Spr::PHBallJointIf::GetMotors;

// 2017/10/25 for dailybuild
%ignore Spr::PHFemVibrationIf::FindNeighborTetrahedron;
%ignore Spr::PHHapticEngineIf::GetSolidPair;
%ignore Spr::PHHapticEngineIf::GetSolidPairInHaptic;
%ignore Spr::PHShapePairForHapticIf;
%ignore Spr::PHSolidPairForHapticIf;

%include "Utility/EPObject.i"
EXTEND_NEW(PHSolidDesc)
EXTEND_NEW(PHPathPoint)
EXTEND_NEW(PHSplineLimitNode)
EXTEND_N_GETS_TO_LIST(Spr::PHSceneIf,NSolids,GetSolids,PHSolidIf)
EXTEND_N_GET_TO_LIST(Spr::PHSdkIf				,NShape				,GetShape			,CDShapeIf			)
EXTEND_N_GET_TO_LIST(Spr::PHSceneIf				,NJoints			,GetJoint			,PHJointIf			)
EXTEND_N_GET_TO_LIST(Spr::PHSceneIf				,NContacts			,GetContact			,PHContactPointIf	)
EXTEND_N_GET_TO_LIST(Spr::PHSceneIf				,NFemMeshes			,GetFemMesh			,PHFemMeshIf		)
EXTEND_N_GET_TO_LIST(Spr::PHSceneIf				,NFemMeshesNew		,GetFemMeshNew		,PHFemMeshNewIf		)
EXTEND_N_GET_TO_LIST(Spr::PHSceneIf				,NRootNodes			,GetRootNode		,PHRootNodeIf		)
EXTEND_N_GET_TO_LIST(Spr::PHSceneIf				,NGears				,GetGear			,PHGearIf			)
EXTEND_N_GET_TO_LIST(Spr::PHSceneIf				,NPaths				,GetPath			,PHPathIf			)
EXTEND_N_GET_TO_LIST(Spr::PHSceneIf				,NRays				,GetRay				,PHRayIf			)
EXTEND_N_GET_TO_LIST(Spr::PHSceneIf				,NIKActuators		,GetIKActuator		,PHIKActuatorIf		)
EXTEND_N_GET_TO_LIST(Spr::PHSceneIf				,NIKEndEffectors	,GetIKEndEffector	,PHIKEndEffectorIf	)
EXTEND_N_GET_TO_LIST(Spr::PHSceneIf				,NEngines			,GetEngine			,PHEngineIf			)
EXTEND_N_GET_TO_LIST(Spr::PHSolidIf				,NShape				,GetShape			,CDShapeIf			)
//EXTEND_N_GET_TO_LIST(Spr::PHShapePairForLCPIf	,NSectionVertexes	,GetSectionVertex	,Vec3d				) //RuntimeDownCast
EXTEND_N_GET_TO_LIST(Spr::PHSolidIf				,NShape				,GetShape			,CDShapeIf			)
//---
%begin%{
#include "../../include/Springhead.h"

#include "../../include/EmbPython/SprEPVersion.h"
#include PYTHON_H_REL

#include "../../include/EmbPython/SprEPUtility.h"
#include "../../include/EmbPython/SprEPBase.h"
#include "../../include/EmbPython/SprEPFoundation.h"
#include "../../include/EmbPython/SprEPCollision.h"
%}
//--  
%include "../../include/Physics/SprPHDef.h"
%include "../../include/Physics/SprPHEngine.h"
%include "../../include/Physics/SprPHFemMesh.h"
%include "../../include/Physics/SprPHFemMeshNew.h"
%include "../../include/Physics/SprPHIK.h"
%include "../../include/Physics/SprPHJoint.h"
%include "../../include/Physics/SprPHJointLimit.h"
%include "../../include/Physics/SprPHNodeHandlers.h"
%include "../../include/Physics/SprPHOpSpHashAgent.h"
%include "../../include/Physics/SprPHScene.h"
%include "../../include/Physics/SprPHSdk.h"
%include "../../include/Physics/SprPHSolid.h"
%include "../../include/Physics/SprPHHaptic.h"
%include "../../include/Physics/SprPHSkeleton.h"
