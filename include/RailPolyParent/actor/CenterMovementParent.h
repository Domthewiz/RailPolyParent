
#pragma once
#include <../REDCORE2.0HEADERS/ParentMovementMgr.h>
#include <RailPolyParent/actor/CenterRotationParentBase.h>

namespace RailPolyParent {
    
class CenterMovementParent : public CenterRotationParentBase {
    public:
        static Profile* sProfile;
    
    public:
        CenterMovementParent(const ActorCreateParam& param);
        ~CenterMovementParent() override = default;
    
        Result create() override;
        bool execute() override;

        void setMovementParams();
    
    private:
        ParentMovementMgr   mMovementMgr;
};

}