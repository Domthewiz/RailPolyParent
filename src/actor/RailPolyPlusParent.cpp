#include "RailPolyParent/actor/RailPolyMgr.h"
#include "RailPolyParent/actor/RailPolyParentBase.h"
#include "actor/ActorBase.h"
#include <actor/Actor.h>
#include <graphics/AnimModel.h>
#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/RailPolyPlusParent.h>
#include <telkin/Print.h>
#include <../REDCORE2.0HEADERS/SwitchFlagMgr.h> // TODO!: Fix once redcore 2.0.0 releases
#include <red/util/SpriteUtil.h>

namespace RailPolyParent {

Profile* RailPolyPlusParent::sProfile = RailPolyParent::getRegistrar()->newProfile<RailPolyPlusParent>("railppp")
    .build();

RailPolyPlusParent::RailPolyPlusParent(const ActorCreateParam& param)
    : RailPolyParentBase(param)
{ }

ActorBase::Result RailPolyPlusParent::create() {
    mInitialPos = mPos;

    // Setting: Movement Type
    const u8 movementType = mLayer;
    if (movementType > ParentMovementType::cPos_KinokoLift) {
        tk::fatal("MagicPlatform invalid movement type");
        return cResult_Failed;
    }
    
    u32 movementMask = mMovementMgr.getTypeMask(static_cast<ParentMovementType>(movementType));

    // Helps prevent the pivotal-rotation from bugging out
    if (movementMask == cPos_CenterRotation) {
        
        ParentMovementMgr::PivotalRotationSettings pivotSettings;
        pivotSettings.position       = mPos;
        pivotSettings.movement_id    = mParamEx.course.init_state_flag;
        pivotSettings.movement_mask  = movementMask;
        pivotSettings.pivot_center   = sead::Vector3f(0.0f, 0.0f, 0.0f);
        pivotSettings.upside_down    = 0;
        pivotSettings.gyroscopic     = 0;
        pivotSettings.tilted         = 0;
        pivotSettings._21            = 0;
        pivotSettings.movement_param = 1;

        mMovementMgr.linkPivotal2(pivotSettings);
    } else {
        mMovementMgr.link(mPos, movementMask, mParamEx.course.init_state_flag);
    }

    setMovementParams();
    // helps avoid crashes for some reason
    if(mMovementMgr.getParentActorID() != this->getActorUniqueID()) {}

    // helps avoid crashes for some reason
    mMovementMgr.execute();

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

    if (mParamEx.course.init_state_flag) {
        mMovementMgr.execute();
        mPos.x += mMovementMgr.getPosition().x - mInitialPos.x;
        mPos.y += mMovementMgr.getPosition().y - mInitialPos.y;
    }

    return true;
}

void RailPolyPlusParent::setMovementParams() {
        static sead::SafeArray<f32, 16> twoWayDistanceMultiplierArr {
            1.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f
        };
        static sead::SafeArray<f32, 16> boltMovementSpeedArr {
            1.0f, 0.25f, 0.5f, 0.75f, 0.0f, 1.5f, 2.0f, 2.5f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f
        };

        ParentMovementType mvtp = static_cast<ParentMovementType>(mLayer);
        if (mvtp == ParentMovementType::cPos_FloorGyration) {
            mMovementMgr.setFloorGyrationAngle(0x1000000 * red::SpriteUtil::getNybbleRange(this, 23, 24));
            ParentMovementMgr::MovementProperties newproperty = mMovementMgr.getMovementProperties();
            newproperty.hill_distance_offset = -16.0f * red::SpriteUtil::getNybble19(this);
            mMovementMgr.setMovementProperties(newproperty);
        } else if (mvtp == ParentMovementType::cPos_GoAndCome) {
            mMovementMgr.setTwoWayDistanceMultiplier(twoWayDistanceMultiplierArr[red::SpriteUtil::getNybble23(this)] + (0.01f * red::SpriteUtil::getNybble24(this)));
        } else if (mvtp == ParentMovementType::cPos_Screw) {
            mMovementMgr.setBoltSpeed(boltMovementSpeedArr[red::SpriteUtil::getNybble23(this)]);
            mMovementMgr.setBoltDirection(static_cast<DirType>(red::SpriteUtil::getNybble24(this)));
        } else if (mvtp == ParentMovementType::cPos_ShiftingPlatform) {
            mMovementMgr.setRectPlatformInfo(static_cast<RectPlatformInfo>(red::SpriteUtil::getNybble24(this)));
        }
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
