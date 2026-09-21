#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/ActorPositionCopier.h>

#include <actor/ActorMgr.h>

#include <red/util/SpriteUtil.h>
#include <red/profile/ProfileEx.h>

namespace RailPolyParent {
    Profile* ActorPositionCopier::cProfile = RailPolyParent::getRegistrar()->newProfile<ActorPositionCopier>("actor_position_copier")
        .build();
    
    ActorPositionCopier::ActorPositionCopier(const ActorCreateParam& param)
        : Actor(param)
        , mWasResolved(false)
    { }

    bool shouldIgnoreActor(const Actor*);

    ActorBase::Result ActorPositionCopier::create() {
        mMovementType = static_cast<ParentMovementType>(red::SpriteUtil::getNybble5(this));

        u32 movementMask = mMovementMgr.getTypeMask(mMovementType);

        if (mMovementType == ParentMovementType::cPos_CenterRotation) {
            mMovementMgr.linkPivotal(mPos, movementMask, getMovementID());
        } else {
            mMovementMgr.link(mPos, movementMask, getMovementID());
        }

        setMovementParameters();

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
    
    void ActorPositionCopier::setMovementParameters() {
        static sead::SafeArray<f32, 16> twoWayDistanceMultiplierArr {
            1.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f
        };

        static sead::SafeArray<f32, 16> boltMovementSpeedArr {
            1.0f, 0.25f, 0.5f, 0.75f, 0.0f, 1.5f, 2.0f, 2.5f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f
        };

        const u32 setting = red::SpriteUtil::getNybbleRange(this, 7, 8);
        const u8 settingUpper = red::SpriteUtil::getNybble7(this);
        const u8 settingLower = red::SpriteUtil::getNybble8(this);
        const u8 setting2 = red::SpriteUtil::getNybble9(this);

        switch (mMovementType) {
            case cPos_FloorGyration: {
                mMovementMgr.setFloorGyrationAngle(0x1000000 * setting);
                ParentMovementMgr::MovementProperties newproperty = mMovementMgr.getMovementProperties();
                newproperty.hill_distance_offset = -16.0f * setting2;
                mMovementMgr.setMovementProperties(newproperty);
                break;
            }

            case cPos_GoAndCome: {
                mMovementMgr.setTwoWayDistanceMultiplier(twoWayDistanceMultiplierArr[red::SpriteUtil::getNybble23(this)] + (0.01f * settingLower));
                break;
            }

            case cPos_Screw: {
                mMovementMgr.setBoltSpeed(boltMovementSpeedArr[settingUpper]);
                mMovementMgr.setBoltDirection(static_cast<DirType>(settingLower));
                break;
            }
            
            case cPos_ShiftingPlatform: {
                mMovementMgr.setRectPlatformInfo(static_cast<RectPlatformInfo>(settingLower));
                break;
            }
        }
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
            
            if (actor == nullptr || actor->getProfile() == ActorPositionCopier::cProfile || shouldIgnoreActor(actor)) {
                continue;
            }

            const u8 linkID = actor->getParamEx().course.init_state_flag;
            actor->getProfile();
            if (linkID == getLinkID()) {
                return actor;
            }
        }

        return nullptr;
    }

    bool shouldIgnoreActor(const Actor* actor) {
        if (actor->getProfileID() < ProfileInfo::cProfileID_Max) {
            return false;
        }

        const sead::SafeString name = red::ProfileEx::getName(actor->getProfileID());

        if (name.isEmpty()) {
            return false;
        }

        const char* forbidden[] = {
            "zap:actor_spawner_simple",
            "zap:actor_spawner_ex"
        };

        for (const char* f : forbidden) {
            if (name.isEqual(f)) {
                return true;
            }
        }

        return false;
    }
}
