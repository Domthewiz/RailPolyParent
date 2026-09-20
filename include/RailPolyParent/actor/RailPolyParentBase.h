#pragma once

#include <actor/ActorState.h>
#include <RailPolyParent/actor/RailPolyMgr.h>

class RailPolyParentBase : public ActorState
{
    SEAD_RTTI_OVERRIDE(RailPolyParentBase, ActorState);

public:
    // Address: 0x0286BE94
    RailPolyParentBase(const ActorCreateParam& param);
    ~RailPolyParentBase() override { }

    // Address: 0x0286C11C
    Actor::Result create() override;
    // Address: 0x0286C268
    bool execute() override;

    // StateID_ControllerActive:          0x1022737C
    // initializeState_ControllerActive:  0x0286C69C
    // executeState_ControllerActive:     0x0286C6A0
    // finalizeState_ControllerActive:    0x0286CD90
    DECLARE_STATE_ID(RailPolyParentBase, ControllerActive);

    // StateID_ControllerPassive:         0x1022739C
    // initializeState_ControllerPassive: 0x0286C710
    // executeState_ControllerPassive:    0x0286C714
    // finalizeState_ControllerPassive:   0x0286CD94
    DECLARE_STATE_ID(RailPolyParentBase, ControllerPassive);

public:
    // Address: 0x0286C09C
    void initRail();

protected:
    sead::Vector3f  _17c8;
    RailPolyMgr     mRail;
    u8              _183c[4];
    sead::Vector2f  mInitialPosition;
    u8              _1848[4];
    Angle           _184c;
    Angle           mSinePhaseShift;
    f32             mSineAmplitude;
    u8              _1858[8];
};
static_assert(sizeof(RailPolyParentBase) == 0x1860, "RailPolyParentBase size mismatch");
