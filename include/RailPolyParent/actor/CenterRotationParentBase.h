#pragma once

#include <actor/Actor.h>
#include <RailPolyParent/actor/CenterRotationMgr.h>

class CenterRotationParentBase : public Actor
{
    SEAD_RTTI_OVERRIDE(CenterRotationParentBase, Actor);

public:
    // Address: 0x02722BF0
    CenterRotationParentBase(const ActorCreateParam& param);
    ~CenterRotationParentBase() override { }

    // Address: 0x02722D54
    Actor::Result create() override;
    // Address: 0x02722E30
    bool execute() override;

    u8 get_27c(u8 index) const
    {
        return _27c[index];
    }

    CenterRotationMgr getControl() const
    {
        return mControl;
    }

    void set_27c(u8 setter,u8 index)
    {
        _27c[index] = setter;
    }

protected:
    u8                  _27c[4];
    CenterRotationMgr   mControl;
};
static_assert(sizeof(CenterRotationParentBase) == 0x2F0, "CenterRotationParentBase size mismatch");
