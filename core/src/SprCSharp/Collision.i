#	Do not edit. RunSwig.bat will update this file.

%module Collision

// %feature �� %include �����O�Ɏw�肷�邱��.
//
%feature("returns_array") Spr::CDConvexMeshIf::GetVertices;
%feature("returns_array") Spr::CDBoxIf::GetVertices;

%include "../../include/SprBase.h"
%include "../../include/Base/Env.h"
%include "../../include/Foundation/SprObject.h"
%include "../../include/Collision/SprCDShape.h"
%include "../../include/Collision/SprCDDetector.h"
%include "../../include/Collision/SprCDSpHash.h"
/*
#define DOUBLECOLON :: 
%include "../../include/Springhead.h"
%include "../../include/base/Env.h"
%include "../../include/Foundation/SprObject.h"
%include "../../include/Foundation/SprScene.h"
%include "../../include/Foundation/SprUTTimer.h"
%include "../../include/Collision/SprCDShape.h"
%include "../../include/Base/BaseDebug.h"
%include "../../src/Foundation/UTTypeDesc.h"
%include "../Foundation/Foundation.h"
%include "../Foundation/Object.h"
%include "../Foundation/Scene.h"
%include "../Foundation/UTBaseType.h"
%include "../Foundation/UTClapack.h"
%include "../Foundation/UTDllLoader.h"
%include "../Foundation/UTDllLoaderImpl.h"
%include "../Foundation/UTLoadContext.h"
%include "../Foundation/UTLoadHandler.h"
%include "../Foundation/UTMMTimer.h"
%include "../Foundation/UTPath.h"
%include "../Foundation/UTPreciseTimer.h"
%include "../Foundation/UTQPTimer.h"
%include "../Foundation/UTSocket.h"
%include "../Foundation/UTTimer.h"
%include "../Foundation/UTTypeDesc.h"
%include "../Collision/CDBox.h"
%include "../Collision/CDCapsule.h"
%include "../Collision/CDConvex.h"
%include "../Collision/CDConvexMesh.h"
%include "../Collision/CDConvexMeshInterpolate.h"
%include "../Collision/CDCutRing.h"
%include "../Collision/CDDetectorImp.h"
%include "../Collision/CDQuickHull2D.h"
%include "../Collision/CDQuickHull2DImp.h"
%include "../Collision/CDQuickHull3D.h"
%include "../Collision/CDQuickHull3DImp.h"
%include "../Collision/CDRoundCone.h"
%include "../Collision/CDShape.h"
%include "../Collision/CDSphere.h"
%include "../Collision/Collision.h"
*/
