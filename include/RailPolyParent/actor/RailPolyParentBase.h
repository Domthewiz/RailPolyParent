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

public:
    // Address: 0x0286C09C
    void initRail();
protected:
    u8              _17c8[12];
    RailPolyMgr     mRail;
    u8              _183c[4];
    sead::Vector2f  mInitialPosition;
    u8              _1848[4];
    Angle           _184c;
    u8              _1850[16];
};
static_assert(sizeof(RailPolyParentBase) == 0x1860, "RailPolyParentBase size mismatch");
