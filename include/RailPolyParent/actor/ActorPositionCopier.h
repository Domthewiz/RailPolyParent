#pragma once

#include <actor/Actor.h>
#include <map_obj/ParentMovementMgr.h>

namespace RailPolyParent {
    class ActorPositionCopier : public Actor {
    public:
        static Profile* cProfile;

    public:
        ActorPositionCopier(const ActorCreateParam& param);
        ~ActorPositionCopier() override = default;

        Result create() override;
        bool execute() override;

        Actor* resolveDependent() const;
        
        u8 getMovementID() const {
            return getParamEx().course.movement_id;
        }

        u8 getLinkID() const {
            return getParamEx().course.link_id;
        }
    private:
        ParentMovementType mMovementType;
        ParentMovementMgr mMovementMgr;
        ActorUniqueID mDependentID;
        bool mWasResolved;
    };
}
