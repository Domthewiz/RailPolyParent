
#pragma once
#include <RailPolyParent/actor/RailPolyParentBase.h>
#include <actor/LineMgr.h>

namespace RailPolyParent {
    
class LineFollowerParent : public RailPolyParentBase {
    public:
        static Profile* sProfile;
    
    public:
        LineFollowerParent(const ActorCreateParam& param);
        ~LineFollowerParent() override = default;
    
        Result create() override;
        bool execute() override;
    
    private:
        LineMgr     mLineFollower;
};

}