#pragma once

#include <actor/ActorState.h>
#include <RailPolyParent/actor/PairObjMgr.h>

class PairObjParentBase : public ActorState
{
    SEAD_RTTI_OVERRIDE(PairObjParentBase, ActorState); // sTypeInfo 0x101EB624

public:
    // Address: 0x02847ABC
    PairObjParentBase(const ActorCreateParam& param);
    ~PairObjParentBase() override { }

    // Address: 0x02847D18
    Actor::Result create() override;
    // Address: 0x02847E40
    bool execute() override;

protected:
    PairObjMgr  mTwoWay2;
    f32         _1828;
    f32         _182c;
    f32         _1830;
    f32         _1834;
    f32         _1838;
    f32         _183c;
    f32         _1840;
    f32         _1844;
    PairObjMgr  mTwoWay;
    f32         _18a8;
    f32         _18ac;
    f32         mTwoWayDisplacement;
    f32         mTwoWayVelocity;
    f32         mBaseSpeedMax;
    f32         _18bc;
};
static_assert(sizeof(PairObjParentBase) == 0x18C0, "PairObjParentBase size mismatch");
