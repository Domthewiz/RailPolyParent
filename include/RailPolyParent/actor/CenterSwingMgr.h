#pragma once

#include <utility/Angle.h>
#include <actor/ActorState.h>

class CenterSwingMgr
{
public:
    // Address: 0x02724F38
    void initialize(Angle *angle_z, s32 sway_arc, s32 sway_speed, u8 sway_delay, s32 clockwise, u32 nybble_9_mask_2, u8 event_activated, s32 arc_middle_rotation, s32 sway_start_offset);
    // Address: 0x02725138
    void execute(Angle *angle_z, u64 events);

    Angle get_0() const
    {
        return _0;
    }

    Angle getSwayStartOffset() const
    {
        return mSwayStartOffset;
    }

    Angle getSwayRate() const
    {
        return mSwayRate;
    }

    Angle getArcMiddleRotation() const
    {
        return mArcMiddleRotation;
    }

    u8 get_10() const
    {
        return _10;
    }

    u8 get_11() const
    {
        return _11;
    }

    u8 getUnkSwayStartOffset() const
    {
        return mUnkSwayStartOffset;
    }

    u8 getEventActivated() const
    {
        return mEventActivated;
    }

    u8 get_14() const
    {
        return _14;
    }

    u8 getSwingDelay() const
    {
        return mSwingDelay;
    }

    u8 getClockwise() const
    {
        return mClockwise;
    }

    u8 get_17(u8 index) const
    {
        return _17[index];
    }

    void set_0(Angle setter)
    {
        _0 = setter;
    }

    void setSwayStartOffset(Angle setter)
    {
        mSwayStartOffset = setter;
    }

    void setSwayRate(Angle setter)
    {
        mSwayRate = setter;
    }

    void setArcMiddleRotation(Angle setter)
    {
        mArcMiddleRotation = setter;
    }

    void set_10(u8 setter)
    {
        _10 = setter;
    }

    void set_11(u8 setter)
    {
        _11 = setter;
    }

    void setUnkSwayStartOffset(u8 setter)
    {
        mUnkSwayStartOffset = setter;
    }

    void setEventActivated(u8 setter)
    {
        mEventActivated = setter;
    }

    void set_14(u8 setter)
    {
        _14 = setter;
    }

    void setSwingDelay(u8 setter)
    {
        mSwingDelay = setter;
    }

    void setClockwise(u8 setter)
    {
        mClockwise = setter;
    }

    void set_17(u8 setter, u8 index)
    {
        _17[index] = setter;
    }

protected:
    Angle   _0;
    Angle   mSwayStartOffset;
    Angle   mSwayRate;
    Angle   mArcMiddleRotation;
    u8      _10;
    u8      _11;
    u8      mUnkSwayStartOffset;
    u8      mEventActivated;
    u8      _14;
    u8      mSwingDelay;
    u8      mClockwise;
    u8      _17[17];
};
static_assert(sizeof(CenterSwingMgr) == 0x28, "CenterSwingMgr size mismatch");
