#ifndef TreeNodeTest_H
#define TreeNodeTest_H

#include <Springhead.h>
#include <Framework/SprFWApp.h>
#include <Base/Combination.h>
#include <Collision/CDDetectorImp.h>
#include <Physics/PHSolid.h>

using namespace Spr;


class TreeNodeTest : public FWApp{
public:
	// 剛体に使う変数
	std::vector<PHSolidIf*> links[2];
	std::vector<PHBallJointIf*> joints[2];
	//デバック表示に使う変数
	void Init(int argc, char* argv[]);		
	void BuildScene();
	void UserFunc();
	void Keyboard(int key, int x, int y);
}; 
extern TreeNodeTest ttest;

#endif