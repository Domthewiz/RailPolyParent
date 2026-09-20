
#pragma once
#include <../REDCORE2.0HEADERS/ParentMovementMgr.h>
#include <RailPolyParent/actor/CenterSwingParentBase.h>

namespace RailPolyParent {
    
class CenterSwingMovementParent : public CenterSwingParentBase {
    public:
        static Profile* sProfile;
    
    public:
        CenterSwingMovementParent(const ActorCreateParam& param);
        ~CenterSwingMovementParent() override = default;
    
        Result create() override;
        bool execute() override;

        void setMovementParams();
    
    private:
        ParentMovementMgr   mMovementMgr;
};

}