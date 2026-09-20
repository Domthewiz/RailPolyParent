#pragma once

#include <RailPolyParent/actor/CenterSwingMgr.h>
#include <actor/Actor.h>
#include <RailPolyParent/actor/CenterRotationMgr.h>

class CenterSwingParentBase : public Actor
{
    SEAD_RTTI_OVERRIDE(CenterSwingParentBase, Actor);

public:
    // Address: 0x02724B8C
    CenterSwingParentBase(const ActorCreateParam& param);
    ~CenterSwingParentBase() override { }

    // Address: 0x02724C30
    Actor::Result create() override;
    // Address: 0x02724CA0
    bool execute() override;

    CenterSwingMgr getSwing() const
    {
        return mSwing;
    }

protected:
    CenterSwingMgr   mSwing;
};
static_assert(sizeof(CenterSwingParentBase) == 0x2A4, "CenterSwingParentBase size mismatch");
