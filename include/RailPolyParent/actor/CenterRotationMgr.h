#pragma once

#include <utility/Angle.h>
#include <actor/ActorState.h>

class CenterRotationMgr
{
public:
    // Address: 0x027232D0
    void initialize(Angle *z_rot, sead::Vector3f& position, u64 events, u32 spinning_speed, s32 swing_arc, s32 initial_arc, s32 event_mode_lower_bits, bool clockwise, u8 movement_id, bool nybble_9_mask_2, bool nybble_10_mask_2, bool nybble_10_mask_1, bool nybble_9_mask_4, u32 nybble_10_mask_4, u32 event_mode_top_bits);
    // Address: 0x027234A8
    void execute(u64 events);

    Angle getRotationZ() const
    {
        return mRotationZ;
    }

    sead::Vector3f* getPos() const
    {
        return mPos;
    }

    u8 get_2c(u8 index) const
    {
        return _2c[index];
    }

    u64 getEvents() const
    {
        return mEvents;
    }

    f32 get_38() const
    {
        return _38;
    }

    u32 get_3c() const
    {
        return _3c;
    }

    Angle getRotationRate() const
    {
        return mRotationRate;
    }

    u32 get_44() const
    {
        return _44;
    }

    u32 get_48() const
    {
        return _48;
    }

    Angle get_4c() const
    {
        return _4c;
    }

    u32 get_50() const
    {
        return _50;
    }

    u32 get_54() const
    {
        return _54;
    }

    Angle getRotationTarget() const
    {
        return mRotationTarget;
    }
    
    u8 get_5c() const
    {
        return _5c;
    }

    u8 get_5d() const
    {
        return _5d;
    }

    bool getDoQuake() const
    {
        return mDoQuake;
    }

    u8 get_5f() const
    {
        return _5f;
    }

    u8 get_60() const
    {
        return _60;
    }

    bool getTargetAngleReached() const
    {
        return mTargetAngleReached;
    }

    u8 get_62() const
    {
        return _62;
    }

    u8 get_63() const
    {
        return _63;
    }

    u8 get_64() const
    {
        return _64;
    }

    u8 get_65() const
    {
        return _65;
    }

    bool getDidQuake() const
    {
        return mDidQuake;
    }

    u8 getEventModeLowBits() const
    {
        return mEventModeLowBits;
    }

    bool getClockwise() const
    {
        return mClockwise;
    }

    u8 get_69() const
    {
        return _69;
    }

    bool getClockwise2() const
    {
        return mClockwise2;
    }

    u8 getMovementID() const
    {
        return mMovementID;
    }

    u8 get_6c() const
    {
        return _6c;
    }

    u8 get_6d(u8 index) const
    {
        return _6d[index];
    }

    void setRotationZ(Angle setter)
    {
        mRotationZ = setter;
    }

    void setPos(sead::Vector3f setter)
    {
        *mPos = setter;
    }

    void set_2c(u8 setter, u8 index)
    {
        _2c[index] = setter;
    }

    void setEvents(u64 setter)
    {
        mEvents = setter;
    }

    void set_38(f32 setter)
    {
        _38 = setter;
    }

    void set_3c(u32 setter)
    {
        _3c = setter;
    }

    void setRotationRate(Angle setter)
    {
        mRotationRate = setter;
    }

    void set_44(u32 setter)
    {
        _44 = setter;
    }

    void set_48(u32 setter)
    {
        _48 = setter;
    }

    void set_4c(Angle setter)
    {
        _4c = setter;
    }

    void set_50(u32 setter)
    {
        _50 = setter;
    }

    void set_54(u32 setter)
    {
        _54 = setter;
    }

    void setRotationTarget(Angle setter)
    {
        mRotationTarget = setter;
    }
    
    void set_5c(u8 setter)
    {
        _5c = setter;
    }

    void set_5d(u8 setter)
    {
        _5d = setter;
    }

    void setDoQuake(bool setter)
    {
        mDoQuake = setter;
    }

    void set_5f(u8 setter)
    {
        _5f = setter;
    }

    void set_60(u8 setter)
    {
        _60 = setter;
    }

    void setTargetAngleReached(bool setter)
    {
        mTargetAngleReached = setter;
    }

    void set_62(u8 setter)
    {
        _62 = setter;
    }

    void set_63(u8 setter)
    {
        _63 = setter;
    }

    void set_64(u8 setter)
    {
        _64 = setter;
    }

    void set_65(u8 setter)
    {
        _65 = setter;
    }

    void setDidQuake(bool setter)
    {
        mDidQuake = setter;
    }

    void setEventModeLowBits(u8 setter)
    {
        mEventModeLowBits = setter;
    }

    void setClockwise(bool setter)
    {
        mClockwise = setter;
    }

    void set_69(u8 setter)
    {
        _69 = setter;
    }

    void setClockwise2(bool setter)
    {
        mClockwise2 = setter;
    }

    void setMovementID(u8 setter)
    {
        mMovementID = setter;
    }

    void set_6c(u8 setter)
    {
        _6c = setter;
    }

    u8 set_6d(u8 index)
    {
        return _6d[index];
    }

    // StateID_RotateTo:                        0x10220C6C
    // initializeState_RotateTo:                0x027236D8
    // executeState_RotateTo:                   0x027236F4
    // finalizeState_RotateTo:                  0x027237B0
    DECLARE_STATE_ID(CenterRotationMgr, RotateTo);

    // StateID_EventContinuousRotate:           0x10220C8C
    // initializeState_EventContinuousRotate:   0x027237B4
    // executeState_EventContinuousRotate:      0x02723828
    // finalizeState_EventContinuousRotate:     0x02723980
    DECLARE_STATE_ID(CenterRotationMgr, EventContinuousRotate);

    // StateID_Unknown3:                        0x10220CAC
    // initializeState_Unknown3:                0x02723984
    // executeState_Unknown3:                   0x027239B8
    // finalizeState_Unknown3:                  0x02723A9C
    DECLARE_STATE_ID(CenterRotationMgr, Unknown3);

    // StateID_Unknown4:                        0x10220CCC
    // initializeState_Unknown4:                0x02723AA8
    // executeState_Unknown4:                   0x02723AC4
    // finalizeState_Unknown4:                  0x02723B08
    DECLARE_STATE_ID(CenterRotationMgr, Unknown4);

    // StateID_Unknown5:                        0x10220CEC
    // initializeState_Unknown5:                0x02723B0C
    // executeState_Unknown5:                   0x02723B1C
    // finalizeState_Unknown5:                  0x02723D14
    DECLARE_STATE_ID(CenterRotationMgr, Unknown5);

protected:
    FStateMgr<CenterRotationMgr>    mStateMgr;
    Angle                           mRotationZ;
    sead::Vector3f*                 mPos;
    u8                              _2c[4];
    u64                             mEvents;
    f32                             _38;
    u32                             _3c;
    Angle                           mRotationRate;
    u32                             _44;
    u32                             _48;
    Angle                           _4c;
    u32                             _50;
    u32                             _54;
    Angle                           mRotationTarget;
    u8                              _5c;
    u8                              _5d;
    bool                            mDoQuake;
    u8                              _5f;
    u8                              _60;
    bool                            mTargetAngleReached;
    u8                              _62;
    u8                              _63; // nybble 10 mask 2
    u8                              _64;
    u8                              _65;
    bool                            mDidQuake;
    u8                              mEventModeLowBits;
    bool                            mClockwise;
    u8                              _69;
    bool                            mClockwise2;
    u8                              mMovementID;
    u8                              _6c;
    u8                              _6d[3];
};
static_assert(sizeof(CenterRotationMgr) == 0x70, "CenterRotationMgr size mismatch");
