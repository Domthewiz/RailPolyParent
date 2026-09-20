#include "RailPolyParent/actor/RailPolyMgr.h"
#include "RailPolyParent/actor/RailPolyParentBase.h"
#include "actor/ActorBase.h"
#include <actor/Actor.h>
#include <graphics/AnimModel.h>
#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/RailPolyPlusParent.h>
#include <telkin/Print.h>
#include <map/SwitchFlagMgr.h>

namespace RailPolyParent {

Profile* RailPolyPlusParent::sProfile = RailPolyParent::getRegistrar()->newProfile<RailPolyPlusParent>("railppp")
    .build();

RailPolyPlusParent::RailPolyPlusParent(const ActorCreateParam& param)
    : RailPolyParentBase(param)
{ }

ActorBase::Result RailPolyPlusParent::create() {

    mPreviousSwitchFlagState = SwitchFlagMgr::instance()->getSwitchFlag() & mSwitchFlag0;
    
    u64 condensedEventIDs;

    _17c8 = mPos;
    _183c[0] = mParam0 >> 0x12 & 1;

    // Legitametly copy-pasted from ghidra so this code is super unreadable
    if ((mParam1 >> 0x14 & 0xF) != 0) {
        _1848[0] = 1;

        mSineAmplitude = (mParam1 >> 0x14 & 0xF) * 8.0f;
        mSinePhaseShift = 0x400000 * (mParam1 >> 0x10 & 0xF);

        if ((mParam1 & 0x10000000) != 0) {
            _1858[0] = 1;
        }
    }

    mVisibleAreaOffset.x = 0.0;
    mVisibleAreaOffset.y = 0.0;

    initRail();

    if ((mParam0 & 8) != 0) {
        _1858[1] = mParam1 & 1;
        if ((SwitchFlagMgr::instance()->getSwitchFlag() & mSwitchFlag0) == 0) {
            changeState(StateID_ControllerActive);
            return cResult_Success;
        }
    }
    changeState(StateID_ControllerPassive);
    return cResult_Success;
}

void RailPolyPlusParent::initRail() {
    sead::Vector2f startingPosition;
    
    startingPosition.x = mPos.x;
    startingPosition.y = mPos.y;

    mInitialPosition.x = startingPosition.x;
    mInitialPosition.y = startingPosition.y;

    if ((mParam1 >> 0x14 & 0xF) != 0) {
        this->_184c = 0x10000000 * (mParam1 >> 0x18 & 0xF);
    }

    mRail.initialize(
        startingPosition, 
        mParam1 >> 0x8 & 0xFF, // Use different nybbles so we can use all 255 ids
        mParam0 >> 0x13 & 1,
        (mParam0 >> 0x10 & 0x3), 
        mParam0 >> 0x18, 
        mParam0 >> 8 & 0xFF, 
        0.0);
    return;
}


bool RailPolyPlusParent::execute() {
    
    mRailPreviousPos = mRail.getPos();
    mRailPreviousSpeed = mRail.getSpeed();

    if (!RailPolyParentBase::execute()) {
        return false;
    }
    
    if ((mParam0 >> 0x10 & 0x3) == RailPolyMgr::cEndBehavior_Drop) {
        // Custom behavior, I plan to add more in the future but this will be sufficient
        switch (mParam0 >> 0x14 & 0xF) {
            case cCustomEndBehavior_Vanilla:
                break;
            case cCustomEndBehavior_StopLoopEvent:
                stopLoopEventBehavior();
                break;
        }
    }

    return true;
}

void RailPolyPlusParent::stopLoopEventBehavior() {
    if (mRail.isState(&RailPolyMgr::StateID_Drop)) {
        // To counteract the "drop"
        mRail.setPos(mRailPreviousPos);
        mRail.setSpeed(mRailPreviousSpeed);

        // Do some trickery with the path node count, current node, and loop node. but it works :)
        if (SwitchFlagMgr::instance()->isActivated(mSwitchFlag1 - 1)) {
            mRail.setCurrentNodeIdx(0);
            if (mRail.getNodeCount() != mRail.getLoopStartIdx()) {
                mRailStoredNodeIdx1 = mRail.getNodeCount();
                mRail.setCurrentNode(mRail.getPathNodes());
                mRail.getStateMgr().changeState(RailPolyMgr::StateID_RailMove);
            }
            mRail.setNodeCount(mRail.getLoopStartIdx());
            
            return;
        }
        if (mRail.getNodeCount() == mRail.getLoopStartIdx()) {
            mRail.setNodeCount(mRailStoredNodeIdx1);
            mRail.setCurrentNodeIdx(mRail.getLoopStartIdx());
            mRail.setCurrentNode(mRail.getPathNodes() + mRail.getLoopStartIdx());
            mRail.getStateMgr().changeState(RailPolyMgr::StateID_RailMove);
        }
        return;
    }
}

}
