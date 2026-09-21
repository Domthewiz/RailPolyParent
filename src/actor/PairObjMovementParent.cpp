#include "actor/ActorBase.h"
#include <actor/Actor.h>
#include <graphics/AnimModel.h>
#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/PairObjMovementParent.h>
#include <red/util/SpriteUtil.h>
#include <../REDCORE2.0HEADERS/SwitchFlagMgr.h>
#include <telkin/Print.h>

// Initially was going to be a universally-controlled two-way controller, but it never ended up panning out
namespace RailPolyParent {

Profile* PairObjMovementParent::sProfile = RailPolyParent::getRegistrar()->newProfile<PairObjMovementParent>("pairobjmp")
    .build();

PairObjMovementParent::PairObjMovementParent(const ActorCreateParam& param)
    : PairObjParentBase(param)
{ }

ActorBase::Result PairObjMovementParent::create() {

    if (!PairObjParentBase::create()) {
        return cResult_Failed;
    }

    // If two way movement type not decided
    if (!mTwoWayTypeOfMovement) {
        mTwoWayTypeOfMovement = cTypeOfMovement_Go;
    }

    return cResult_Success;
}

bool PairObjMovementParent::execute() {
    mTwoWayLastMovementSign = (sead::Mathf::sign(mTwoWay.getGoTargetVelocity()) == 1.0f) ? sead::Mathf::sign(mTwoWayVelocity) : -sead::Mathf::sign(mTwoWayVelocity);
    
    if (!PairObjParentBase::execute()) {
        return false;
    }

    if (mTwoWayLastMovementSign == 1.0f) {
        mTwoWayTypeOfMovement = cTypeOfMovement_Go;
    } else {
        mTwoWayTypeOfMovement = cTypeOfMovement_Come;
    }
    if (*mTwoWay.getStateMgr().getStateID() == PairObjMgr::StateID_Static) {
        
        if (mTwoWayTypeOfMovement == cTypeOfMovement_Go) {
            tk::println("Bree %u, %u", SwitchFlagMgr::instance()->isActivated(mSwitchFlag0 - 1), mSwitchFlag0);
            if (!SwitchFlagMgr::instance()->isActivated(mSwitchFlag0 - 1)) {
                mTwoWay.setVelocity(0.0f);
                mTwoWay.getStateMgr().changeState(PairObjMgr::StateID_Static);

            }
            return true;
        }
        
        tk::println("Brbbee");
        if (SwitchFlagMgr::instance()->isActivated(mSwitchFlag0 - 1)) {
                mTwoWay.setVelocity(0.0f);
                mTwoWay.getStateMgr().changeState(PairObjMgr::StateID_Static);
        }
    }
        // if (sead::Mathf::abs(mTwoWayVelocity) >= 0.01f) {
    //     mTwoWayLastMovementSign = (sead::Mathf::sign(mTwoWay.getGoTargetVelocity()) == 1.0f) ? sead::Mathf::sign(mTwoWayVelocity) : -sead::Mathf::sign(mTwoWayVelocity);
        
    //     if (!PairObjParentBase::execute()) {
    //         return false;
    //     }
        
    //     tk::println("mTwoWayLastMovementSign, %f", mTwoWayLastMovementSign);
    //     if (mTwoWayLastMovementSign == 1.0f) {
    //         mTwoWayTypeOfMovement = cTypeOfMovement_Go;
    //     } else {
    //         mTwoWayTypeOfMovement = cTypeOfMovement_Come;
    //     }
    //     return true;
    // }
    


    return true;
}

}
