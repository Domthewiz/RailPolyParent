
#pragma once
#include <RailPolyParent/actor/RailPolyParentBase.h>

namespace RailPolyParent {
    
class RailPolyPlusParent : public RailPolyParentBase {
    public:
        static Profile* sProfile;
    
    public:
        RailPolyPlusParent(const ActorCreateParam& param);
        ~RailPolyPlusParent() override = default;
    
        Result create() override;
        bool execute() override;

        void initRail();
    
    private:
        bool    mPreviousSwitchFlagState;
};

}