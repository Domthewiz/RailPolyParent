#include "RailPolyParent/actor/CenterSwingMovementParent.h"
#include "RailPolyParent/actor/DaenSwingParent.h"
#include "RailPolyParent/actor/LineFollowerParent.h"
#include "actor/ActorPtrCache.h"
#include <RailPolyParent/actor/CenterSwingParentBase.h>
#include <RailPolyParent/actor/CenterRotationParentBase.h>
#include <actor/ActorUniqueID.h>
#include <telkin/Print.h>
#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/RailPolyParentBase.h>

#include <telkin/Telkin.h>

#include <../REDCORE2.0HEADERS/ParentMovementMgr.h>
#include <actor/ActorMgr.h>
#include <RailPolyParent/actor/CenterMovementParent.h>
#include <RailPolyParent/actor/DaenParent.h>
#include <RailPolyParent/actor/OdoriParent.h>
#include <RailPolyParent/actor/RailPolyPlusParent.h>
#include <RailPolyParent/actor/PairObjParentBase.h>
#include <RailPolyParent/actor/PairObjMovementParent.h>

red::Registrar* RailPolyParent::getRegistrar() {
    static red::Registrar sRegistrar("railpolyp");
    return &sRegistrar;
}

void main() { } // don't care :)

// There's probably a much better way to do this but i'm lazy lmao

RailPolyParentBase* ParentMovementMgr_fetchPath(ParentMovementMgr* _this) {
    u8 movementId = _this->getMovementID();

    ActorMgr* actorMgr = ActorMgr::instance();
    for (auto it = actorMgr->getActorBegin(); it != actorMgr->getActorEnd(); it++) {
        if (*it == nullptr) {
            continue;
        }

        RailPolyParentBase* targetactor = sead::DynamicCast<RailPolyParentBase>(*it);
        if (!targetactor) {
            continue;
        }
        
        if (targetactor->getParamEx().course.movement_id != movementId) {
            continue;
        }
        
        // if we come across one of my custom movement controllers, accept it.
        if (targetactor->getProfile() == RailPolyParent::OdoriParent::sProfile || targetactor->getProfile() == RailPolyParent::RailPolyPlusParent::sProfile || targetactor->getProfile() == RailPolyParent::LineFollowerParent::sProfile) {
            return targetactor;
        }
        
        // 0xd is the Path controller profile id
        if (targetactor->getProfileID() == 0xd) {
            return targetactor;
        }
    }
    return nullptr;
}
tBranch(0x02849E54, ParentMovementMgr_fetchPath, tk::BranchType::b); // ParentMovementMgr::fetchPath(ParentMovementMgr*)

class PathControlledActor : public ActorState
{
public:
    // Address: 0x0287ACD0
    RailPolyParentBase* getController();

    u8 getMovementID()
    {
        return mMovementID;
    }
protected:
    sead::Vector3f  mFinalPositionMaybe;
    ActorUniqueID   mControllerUniqueID;
    u8              _17d8[2];
    u8              mMovementID;
    u8              _17db[5];
};
static_assert(sizeof(PathControlledActor) == 0x17E0, "PathControlledActor size mismatch");

RailPolyParentBase* PathControlledActor_getController(u32 movement_id) {
    u8 movementId = movement_id;

    ActorMgr* actorMgr = ActorMgr::instance();
    for (auto it = actorMgr->getActorBegin(); it != actorMgr->getActorEnd(); it++) {
        if (*it == nullptr) {
            continue;
        }

        RailPolyParentBase* targetactor = sead::DynamicCast<RailPolyParentBase>(*it);
        if (!targetactor) {
            continue;
        }
        
        if (targetactor->getParamEx().course.movement_id != movementId) {
            continue;
        }
        
        // if we come across one of my custom movement controllers, accept it.
        if (targetactor->getProfile() == RailPolyParent::OdoriParent::sProfile || targetactor->getProfile() == RailPolyParent::RailPolyPlusParent::sProfile || targetactor->getProfile() == RailPolyParent::LineFollowerParent::sProfile) {
            return targetactor;
        }
        
        // 0xd is the Path controller profile id
        if (targetactor->getProfileID() == 0xd) {
            return targetactor;
        }
    }
    return nullptr;
}
tBranch(0x0287ACD0, PathControlledActor_getController, tk::BranchType::b); // PathControlledActor::getController(u32 movement_id)

CenterRotationParentBase* scanCenterRotation(u32 movement_id) {
    u8 movementId = movement_id;

    ActorMgr* actorMgr = ActorMgr::instance();
    for (auto it = actorMgr->getActorBegin(); it != actorMgr->getActorEnd(); it++) {
        if (*it == nullptr) {
            continue;
        }

        CenterRotationParentBase* targetactor = sead::DynamicCast<CenterRotationParentBase>(*it);
        if (!targetactor) {
            continue;
        }
        
        if (targetactor->getControl().getMovementID() != movementId) {
            continue;
        }
        
        // if we come across one of my custom movement controllers, accept it.
        if (targetactor->getProfile() == RailPolyParent::DaenParent::sProfile || targetactor->getProfile() == RailPolyParent::CenterMovementParent::sProfile) {
            return targetactor;
            
        }
        // 0x28 is the spinning pivotal rotation controller profile id
        if (targetactor->getProfileID() == 0x28) {
            return targetactor;
        }
    }
    return nullptr;
}
tBranch(0x0287A2A4, scanCenterRotation, tk::BranchType::b); // scanCenterRotation(u32 movement_id)

CenterSwingParentBase* scanCenterSwing(u32 movement_id) {
    u8 movementId = movement_id;

    ActorMgr* actorMgr = ActorMgr::instance();
    for (auto it = actorMgr->getActorBegin(); it != actorMgr->getActorEnd(); it++) {
        if (*it == nullptr) {
            continue;
        }

        CenterSwingParentBase* targetactor = sead::DynamicCast<CenterSwingParentBase>(*it);
        if (!targetactor) {
            continue;
        }
        
        if (targetactor->getParamEx().course.movement_id != movementId) {
            continue;
        }
        
        // if we come across one of my custom movement controllers, accept it.
        if (targetactor->getProfile() == RailPolyParent::DaenSwingParent::sProfile || targetactor->getProfile() == RailPolyParent::CenterSwingMovementParent::sProfile) {
            return targetactor;
            
        }
        // 0x27 is the swaying pivotal rotation controller profile id
        if (targetactor->getProfileID() == 0x27) {
            return targetactor;
        }
    }
    return nullptr;
}
tBranch(0x0287A1E8, scanCenterSwing, tk::BranchType::b); // scanCenterSwing(u32 movement_id)

PairObjParentBase* ParentMovementMgr_fetchTwoWay(ParentMovementMgr* _this) {
    u8 movementId = _this->getMovementID();

    ActorMgr* actorMgr = ActorMgr::instance();
    for (auto it = actorMgr->getActorBegin(); it != actorMgr->getActorEnd(); it++) {
        if (*it == nullptr) {
            continue;
        }

        PairObjParentBase* targetactor = sead::DynamicCast<PairObjParentBase>(*it);
        if (!targetactor) {
            continue;
        }
        
        if (targetactor->getParamEx().course.movement_id != movementId) {
            continue;
        }
        
        // if we come across one of my custom movement controllers, accept it.
        if (targetactor->getProfile() == RailPolyParent::PairObjMovementParent::sProfile) {
            return targetactor;
        }
        
        // 0xb is the two way controller profile id
        if (targetactor->getProfileID() == 0xb) {
            return targetactor;
        }
    }
    return nullptr;
}
tBranch(0x02849F10, ParentMovementMgr_fetchTwoWay, tk::BranchType::b); // ParentMovementMgr::ParentMovementMgr_fetchTwoWay(ParentMovementMgr*)
