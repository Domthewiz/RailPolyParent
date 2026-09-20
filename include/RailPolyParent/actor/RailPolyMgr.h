#pragma once

#include <actor/ActorState.h>

class RailPolyMgr
{
public:
    struct PathNode
    {
        u16 x;
        u16 y;
        f32 speed;
        f32 accel;
        u16 delay;
        u8  unknown[3];
    };
    static_assert(sizeof(PathNode) == 0x14);

    enum EndBehavior : u8
    {
        cEndBehavior_Stop = 0,
        cEndBehavior_GoToLoopStart,
        cEndBehavior_Drop,
        cEndBehavior_StopWithQuake,
    };

public:
    // Address: 0x02977ED0
    void initialize(sead::Vector2f& pos, u32 path_id, bool strict_movement, u8 end_behavior, u32 start_node, u16 loop_start_node, f32 param_8);
    // Address: 0x02977E1C
    bool setRailInfo(u32 param_2);

    bool isState(StateID* state_id) const
    {
        return mStateMgr.getStateID() == state_id;
    }

    void setState(StateID state_id)
    {
        mStateMgr.changeState(state_id);
    }

    FStateMgr<RailPolyMgr> getStateMgr() const
    {
        return mStateMgr;
    }

    PathNode* getPathNodes() const
    {
        return mPathNodes;
    }

    PathNode* getCurrentNode() const
    {
        return mCurrentNode;
    }

    sead::Vector3f getModeDir() const
    {
        return mModeDir;
    }

    sead::Vector2f getPos() const
    {
        return mPos;
    }

    sead::Vector2f getSpeed() const
    {
        return mSpeed;
    }

    Angle get_48() const
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

    f32 getSpeedMag() const
    {
        return mSpeedMag;
    }

    u16 getNodeCount() const
    {
        return mNodeCount;
    }

    u16 getCurrentNodeIdx() const
    {
        return mCurrentNodeIdx;
    }

    u16 getRemainingDelay() const
    {
        return mRemainingDelay;
    }

    u16 getLoopStartIdx() const
    {
        return mLoopStartIdx;
    }

    u16 getUnkNodeIdx2() const
    {
        return mUnkNodeIdx2;
    }

    bool isStrictMovement() const
    {
        return mStrictMovement;
    }

    u8 get_63(u32 index) const
    {
        return _63[index];
    }

    EndBehavior getEndBehavior() const
    {
        return mEndBehavior;
    }
    
    u8 get_66(u32 index) const
    {
        return _66[index];
    }

    void setPathNodes(PathNode* setter)
    {
        mPathNodes = setter;
    }

    void setCurrentNode(PathNode* setter)
    {
        mCurrentNode = setter;
    }

    void setModeDir(sead::Vector3f setter)
    {
        mModeDir = setter;
    }

    void setPos(sead::Vector2f setter)
    {
        mPos = setter;
    }

    void setSpeed(sead::Vector2f setter)
    {
        mSpeed = setter;
    }

    void set_48(Angle setter)
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

    void setSpeedMag(f32 setter)
    {
        mSpeedMag = setter;
    }

    void setNodeCount(u16 setter)
    {
        mNodeCount = setter;
    }

    void setCurrentNodeIdx(u16 setter)
    {
        mCurrentNodeIdx = setter;
    }

    void setRemainingDelay(u16 setter)
    {
        mRemainingDelay = setter;
    }

    void setLoopStartIdx(u16 setter)
    {
        mLoopStartIdx = setter;
    }

    void setUnkNodeIdx2(u16 setter)
    {
        mUnkNodeIdx2 = setter;
    }

    void setStrictMovement(bool setter)
    {
        mStrictMovement = setter;
    }

    void set_63(u8 setter, u8 index)
    {
        _63[index] = setter;
    }

    void setEndBehavior(EndBehavior setter)
    {
        mEndBehavior = setter;
    }
    
    void set_66(u8 setter, u8 index)
    {
        _66[index] = setter;
    }

    // StateID_Drop:                    0x1022BECC
    // initializeState_Drop:            0x029788E0
    // executeState_Drop:               0x029788E4
    // finalizeState_Drop:              0x02978E2C
    DECLARE_STATE_ID(RailPolyMgr, Drop);

    // StateID_RailMove:                0x1022BE6C
    // initializeState_RailMove:        0x02978E1C
    // executeState_RailMove:           0x0297801C
    // finalizeState_RailMove:          0x02978E20
    DECLARE_STATE_ID(RailPolyMgr, RailMove);

    // StateID_RailMoveEnd:             0x1022BEAC
    // initializeState_RailMoveEnd:     0x02978890
    // executeState_RailMoveEnd:        0x029788C8
    // finalizeState_RailMoveEnd:       0x029788D4
    DECLARE_STATE_ID(RailPolyMgr, RailMoveEnd);

    // StateID_RailMoveWait:            0x1022BE8C
    // initializeState_RailMoveWait:    0x02978E24
    // executeState_RailMoveWait:       0x0297886C
    // finalizeState_RailMoveWait:      0x02978E28
    DECLARE_STATE_ID(RailPolyMgr, RailMoveWait);

    // StateID_SearchRailID:            0x1022BE4C
    // initializeState_SearchRailID:    0x02978E10
    // executeState_SearchRailID:       0x02978E14
    // finalizeState_SearchRailID:      0x02978E18
    DECLARE_STATE_ID(RailPolyMgr, SearchRailID);

protected:
    FStateMgr<RailPolyMgr>  mStateMgr;
    PathNode*               mPathNodes;
    PathNode*               mCurrentNode;
    sead::Vector3f          mModeDir;
    sead::Vector2f          mPos;
    sead::Vector2f          mSpeed;
    Angle                   _48;
    Angle                   _4c;
    u32                     _50;
    f32                     mSpeedMag;
    u16                     mNodeCount;
    u16                     mCurrentNodeIdx;
    u16                     mRemainingDelay;
    u16                     mLoopStartIdx;
    u16                     mUnkNodeIdx2;
    bool                    mStrictMovement;
    u8                      _63[2];
    EndBehavior             mEndBehavior;
    u8                      _66[2];
};
static_assert(sizeof(RailPolyMgr) == 0x68);
