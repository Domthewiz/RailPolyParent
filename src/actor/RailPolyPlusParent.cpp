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

    mRail.set_66((mParam0 >> 0x14) & 0xF, 1); // set our super-duper-pooper-scooper-secret behavior to override fall down

    if ((mParam0 & 8) != 0) {
        _1858[1] = mParam1 & 1;
        // condensedEventIDs = SwitchFlagMgr::instance()->condenseEventIds( mSwitchFlag0, mSwitchFlag1);
        // if ((SwitchFlagMgr::instance()->getSwitchFlag() & condensedEventIDs >> 0x20) == 0 &&
        //     (SwitchFlagMgr::instance()->getSwitchFlag() & condensedEventIDs) == 0) {
        if ((SwitchFlagMgr::instance()->getSwitchFlag() & mSwitchFlag0) == 0) {
            changeState(StateID_ControllerActive);
            return cResult_Success;
        }
    }
    changeState(StateID_ControllerPassive);
    return cResult_Success;
}

void RailPolyPlusParent::initRail() {
    tk::println("fluh");
    sead::Vector2f startingPosition;
    
    startingPosition.x = mPos.x;
    startingPosition.y = mPos.y;

    mInitialPosition.x = startingPosition.x;
    mInitialPosition.y = startingPosition.y;

    if ((mParam1 >> 0x14 & 0xF) != 0) {
        this->_184c = 0x10000000 * (mParam1 >> 0x18 & 0xF);
    }

    // RailPolyMgr::EndBehavior hackedEndBehavior = ((mParam0 >> 0x10 & 0x3) == 2) ? RailPolyMgr::cEndBehavior_GoToLoopStart : static_cast<RailPolyMgr::EndBehavior>(mParam0 >> 0x10 & 0x3);
    // hackedEndBehavior = ((mParam1 >> 0x4 & 0xF)) ? hackedEndBehavior : RailPolyMgr::cEndBehavior_Drop;
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
    // If the original end behavior was Fall Down
    tk::println("bruh bffr %u, %u, %u, %u", mRail.getCurrentNode()->unknown[0], mRail.getCurrentNode()->unknown[1], mRail.getCurrentNode()->unknown[2], mRail.getCurrentNode()->delay);
    if ((mParam0 >> 0x10 & 0x3) == 2) {
    }

    if (!RailPolyParentBase::execute()) {
        return false;
    }

    // RailPolyMgr::PathNode* realNode = mRail.getCurrentNode();
    // if (SwitchFlagMgr::instance()->getSwitchFlag() & mSwitchFlag0) {
    //     mRail.setCurrentNode(mRail.getPathNodes());
    // } else {
    //     mRail.setCurrentNode(realNode);
    // }
    // mPreviousSwitchFlagState = SwitchFlagMgr::instance()->getSwitchFlag() & mSwitchFlag0;
    
    return true;
}

}
