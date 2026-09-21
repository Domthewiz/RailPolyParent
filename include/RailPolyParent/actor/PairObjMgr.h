#pragma once

#include "state/FStateMgr.h"
#include <utility/Direction.h>
#include <state/FStateID.h>
#include <types.h>

class PairObjMgr
{
public:
    // Address: 0x02858F00
    void initialize(u32 distance, DirType direction);

    FStateMgr<PairObjMgr> getStateMgr() const
    {
        return mStateMgr;
    }
    
    f32 getBaseDistance() const
    {
        return mBaseDistance;
    }
    
    f32 getGoAccelerationRate() const
    {
        return mGoAccelerationRate;
    }
    
    f32 getGoTargetVelocity() const
    {
        return mGoTargetVelocity;
    }
    
    u32 get_30() const
    {
        return _30;
    }
    
    f32 getComeAccelerationRate() const
    {
        return mComeAccelerationRate;
    }
    
    f32 getComeTargetVelocity() const
    {
        return mComeTargetVelocity;
    }
    
    f32 get_3c() const
    {
        return _3c;
    }
    
    u32 get_40() const
    {
        return _40;
    }
    
    f32 getDisplacement() const
    {
        return mDisplacement;
    }
    
    u32 get_48() const
    {
        return _48;
    }
    
    u32 get_4c() const
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
    
    u32 get_58() const
    {
        return _58;
    }
    
    u8 get_5c() const
    {
        return _5c;
    }
    
    u8 get_5d() const
    {
        return _5d;
    }
    
    u8 get_5e() const
    {
        return _5e;
    }
    
    u8 get_5f() const
    {
        return _5f;
    }
    
    void setBaseDistance(f32 setter)
    {
        mBaseDistance = setter;
    }
    
    void setGoAccelerationRate(f32 setter)
    {
        mGoAccelerationRate = setter;
    }
    
    void setGoTargetVelocity(f32 setter)
    {
        mGoTargetVelocity = setter;
    }
    
    void set_30(u32 setter)
    {
        _30 = setter;
    }
    
    void setComeAccelerationRate(f32 setter)
    {
        mComeAccelerationRate = setter;
    }
    
    void setComeTargetVelocity(f32 setter)
    {
        mComeTargetVelocity = setter;
    }
    
    void set_3c(f32 setter)
    {
        _3c = setter;
    }
    
    void set_40(u32 setter)
    {
        _40 = setter;
    }
    
    void setDisplacement(f32 setter)
    {
        mDisplacement = setter;
    }
    
    void set_48(u32 setter)
    {
        _48 = setter;
    }
    
    void set_4c(u32 setter)
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
    
    void set_58(u32 setter)
    {
        _58 = setter;
    }
    
    void set_5c(u8 setter)
    {
        _5c = setter;
    }
    
    void set_5d(u8 setter)
    {
        _5d = setter;
    }
    
    void set_5e(u8 setter)
    {
        _5e = setter;
    }
    
    void set_5f(u8 setter)
    {
        _5f = setter;
    }
    
    // StateID_Accelerating:                    0x10226D00
    // initializeState_Accelerating:            0x029788E0 Not right
    // executeState_Accelerating:               0x029788E4 Not right
    // finalizeState_Accelerating:              0x02978E2C Not right
    DECLARE_STATE_ID(PairObjMgr, Accelerating);

    // StateID_ConstantMotion:                0x10226D20
    // initializeState_ConstantMotion:        0x02978E1C Not right
    // executeState_ConstantMotion:           0x0297801C Not right
    // finalizeState_ConstantMotion:          0x02978E20 Not right
    DECLARE_STATE_ID(PairObjMgr, ConstantMotion);

    // StateID_Decelerating:             0x10226D40
    // initializeState_Decelerating:     0x02978890 Not right
    // executeState_Decelerating:        0x029788C8 Not right
    // finalizeState_Decelerating:       0x029788D4 Not right
    DECLARE_STATE_ID(PairObjMgr, Decelerating);

    // StateID_Static:            0x10226D60
    // initializeState_Static:    0x02978E24 Not right
    // executeState_Static:       0x0297886C Not right
    // finalizeState_Static:      0x02978E28 Not right
    DECLARE_STATE_ID(PairObjMgr, Static);

protected:
    FStateMgr<PairObjMgr>   mStateMgr;
    f32                     mBaseDistance;
    f32                     mGoAccelerationRate;
    f32                     mGoTargetVelocity;
    u32                     _30;
    f32                     mComeAccelerationRate;
    f32                     mComeTargetVelocity;
    f32                     _3c;
    u32                     _40;
    f32                     mDisplacement;
    u32                     _48;
    u32                     _4c;
    u32                     _50;
    u32                     _54;
    u32                     _58;
    u8                      _5c;
    u8                      _5d;
    u8                      _5e;
    u8                      _5f;
};
static_assert(sizeof(PairObjMgr) == 0x60, "PairObjMgr size mismatch");