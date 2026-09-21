#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/ActorPositionCopier.h>

#include <actor/ActorMgr.h>

#include <red/util/SpriteUtil.h>

namespace RailPolyParent {
    Profile* ActorPositionCopier::cProfile = RailPolyParent::getRegistrar()->newProfile<ActorPositionCopier>("actorpositioncopier")
        .build();
    
    ActorPositionCopier::ActorPositionCopier(const ActorCreateParam& param)
        : Actor(param)
        , mWasResolved(false)
    { }

    ActorBase::Result ActorPositionCopier::create() {
        mMovementType = static_cast<ParentMovementType>(red::SpriteUtil::getNybble5(this));

        u32 movementMask = mMovementMgr.getTypeMask(mMovementType);

        if (mMovementType == ParentMovementType::cPos_CenterRotation) {
            mMovementMgr.linkPivotal(mPos, movementMask, getMovementID());
        } else {
            mMovementMgr.link(mPos, movementMask, getMovementID());
        }

        mMovementMgr.execute();
       
        return cResult_Success;
    }

    bool ActorPositionCopier::execute() {
        Actor* actor = resolveDependent();

        if (actor == nullptr) {
            if (mWasResolved) {
                // actor has disappeared
                mWasResolved = false;
                mDependentID = 0;
            }
            return false;
        } else {
            if (!mWasResolved) {
                mWasResolved = true;
                mDependentID = actor->getActorUniqueID();
            }
        }

        mMovementMgr.execute();
        actor->getPos() = mPos = mMovementMgr.getPosition();
        
        return true;
    }

    Actor* ActorPositionCopier::resolveDependent() const {
        if (mWasResolved) {
            // check if actor still exists

            if (mDependentID == 0) {
                return nullptr;
            }

            return static_cast<Actor*>(ActorMgr::instance()->getActorPtr(mDependentID));
        }

        // find one

        ActorMgr* actors = ActorMgr::instance();

        for (ActorMgr::iterator it = actors->getActorBegin(); it != actors->getActorEnd(); it++) {
            Actor* actor = static_cast<Actor*>(*it);
            
            if (actor == nullptr || actor->getProfile() == ActorPositionCopier::cProfile) {
                continue;
            }

            const u8 linkID = actor->getParamEx().course.init_state_flag;
            if (linkID == getLinkID()) {
                return actor;
            }
        }

        return nullptr;
    }
}
