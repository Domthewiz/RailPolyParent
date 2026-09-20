#include "actor/ActorBase.h"
#include "math/seadMathCalcCommon.h"
#include <actor/Actor.h>
#include <graphics/AnimModel.h>
#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/DaenSwingParent.h>
#include <telkin/Print.h>

namespace RailPolyParent {

Profile* DaenSwingParent::sProfile = RailPolyParent::getRegistrar()->newProfile<DaenSwingParent>("swaydaenparent")
    .build();

DaenSwingParent::DaenSwingParent(const ActorCreateParam& param)
    : CenterSwingParentBase(param)
{ }

ActorBase::Result DaenSwingParent::create() {
    // tk::println("DaenSwingParent was created!");
    mInitialPosition = mPos;

    if (!CenterSwingParentBase::create()) {
        return cResult_Failed;
    }

    setOffsets();

    return cResult_Success;
}

bool DaenSwingParent::execute() {
    if (!CenterSwingParentBase::execute()) {
        return false;
    }

    f32 angleSin, angleCos;
    sead::Mathf::sinCosIdx(&angleSin, &angleCos, mAngle.z() + mAnglePhaseShift);
    mPos.x = mInitialPosition.x - (angleCos * mOffset.x);
    mPos.y = mInitialPosition.y - (angleSin * mOffset.y);

    return true;
}

void DaenSwingParent::setOffsets() {
    mOffset.x = 16.0f * ((mLayer > 7) ? (mLayer - 0x10) : mLayer);
    mOffset.y = 16.0f * ((mParamEx.course.init_state_flag > 7) ? (mParamEx.course.init_state_flag - 0x10) : mParamEx.course.init_state_flag);
    mAnglePhaseShift = ((mParamEx.course.link_id >> 4) & 0xF) << 0x1C;
}

}
