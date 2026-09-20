
#pragma once
#include <RailPolyParent/actor/RailPolyParentBase.h>

namespace RailPolyParent {
    
class RailPolyPlusParent : public RailPolyParentBase {
    public:
        enum CustomEndBehavior {
            cCustomEndBehavior_Vanilla = 0,
            cCustomEndBehavior_StopLoopEvent,
        };
    public:
        static Profile* sProfile;
    
    public:
        RailPolyPlusParent(const ActorCreateParam& param);
        ~RailPolyPlusParent() override = default;
    
        Result create() override;
        bool execute() override;

        void initRail();
        void stopLoopEventBehavior();
    
    private:
        bool            mPreviousSwitchFlagState;
        sead::Vector2f  mRailPreviousPos;
        sead::Vector2f  mRailPreviousSpeed;
        u16             mRailStoredNodeIdx1;
};

}