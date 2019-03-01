#ifndef CRMOTIONCONTROLLER_H
#define CRMOTIONCONTROLLER_H

#include <Foundation/SprObject.h>
#include <Foundation/Object.h>

#include <Creature/SprCRTimeSeries.h>

namespace Spr { ;

class CRMotionController : public Object {
public:
	CRSolidsTimeSeries solidsConstraints;
	CRJointsTimeSeries jointsConstraints;

public:
	virtual void SetSolidsConstraints(CRSolidsTimeSeries s) {
		this->solidsConstraints = s;
	}
	virtual CRSolidsTimeSeries GetSolidsConstraints() {
		return this->solidsConstraints;
	}
	virtual void AddSolidsConstraint(CRSolidsTimeSlice s) {
		this->solidsConstraints.solidsTimeSlice.push_back(s);
		// <!!> �\�[�g�͂��Ȃ��H����Ƃ��āA�ǂ��ŁH
	}
	virtual void SetJointsConstraints(CRJointsTimeSeries j) {
		this->jointsConstraints = j;
	}
	virtual CRJointsTimeSeries GetJointsConstraints() {
		return this->jointsConstraints;
	}
	virtual void AddJointsConstraint(CRJointsTimeSlice j) {
		this->jointsConstraints.jointsTimeSlice.push_back(j);
	}

	virtual void GetAction() {
		// �����Ԃł̖ڕW�p�x��Ԃ�

	}
};
}

#endif // CRMOTIONCONTROLLER_H