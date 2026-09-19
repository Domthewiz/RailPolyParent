#include "RailPolyParent/actor/CenterRotationParentBase.h"
#include "actor/ActorBase.h"
#include "math/seadMathCalcCommon.h"
#include <actor/Actor.h>
#include <graphics/AnimModel.h>
#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/DaenParent.h>
#include <telkin/Print.h>

namespace RailPolyParent {

Profile* DaenParent::sProfile = RailPolyParent::getRegistrar()->newProfile<DaenParent>("daenparent")
    .build();

DaenParent::DaenParent(const ActorCreateParam& param)
    : CenterRotationParentBase(param)
{ }

ActorBase::Result DaenParent::create() {
    tk::println("DaenParent was created!");
    mInitialPosition = mPos;

    if (!CenterRotationParentBase::create()) {
        return cResult_Failed;
    }

    setOffsets();

    return cResult_Success;
}

bool DaenParent::execute() {
    if (!CenterRotationParentBase::execute()) {
        return false;
    }

    f32 angleSin, angleCos;
    sead::Mathf::sinCosIdx(&angleSin, &angleCos, mAngle.z() + mAnglePhaseShift);
    mPos.x = mInitialPosition.x - (angleCos * mOffset.x);
    mPos.y = mInitialPosition.y - (angleSin * mOffset.y);

    return true;
}

void DaenParent::setOffsets() {
    mOffset.x = 16.0f * ((mLayer > 7) ? (mLayer - 0xF) : mLayer);
    mOffset.y = 16.0f * ((mParamEx.course.init_state_flag > 7) ? (mParamEx.course.init_state_flag - 0xF) : mParamEx.course.init_state_flag);
    mAnglePhaseShift = ((mParamEx.course.link_id >> 4) & 0xF) << 0x1C;
}

}
