#include <RailPolyParent/actor/CenterRotationParentBase.h>
#include <actor/ActorUniqueID.h>
#include <telkin/Print.h>
#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/RailPolyParentBase.h>
#include <telkin/Telkin.h>
#include <map_obj/ParentMovementMgr.h>
#include <actor/ActorMgr.h>

#include <RailPolyParent/actor/DaenParent.h>
#include <RailPolyParent/actor/OdoriParent.h>
#include <RailPolyParent/actor/RailPolyPlusParent.h>

red::Registrar* RailPolyParent::getRegistrar() {
    static red::Registrar sRegistrar("railpolyp");
    return &sRegistrar;
}

void main() { } // don't care :)

// RailPolyParent - Add Dancing controller

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
        if (targetactor->getProfile() == RailPolyParent::OdoriParent::sProfile || targetactor->getProfile() == RailPolyParent::RailPolyPlusParent::sProfile) {
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
        if (targetactor->getProfile() == RailPolyParent::OdoriParent::sProfile || targetactor->getProfile() == RailPolyParent::RailPolyPlusParent::sProfile) {
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
        if (targetactor->getProfile() == RailPolyParent::DaenParent::sProfile) {
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

void RailPolyMgr::initializeState_Drop() {
    tk::println("bruh i just got hacked lmao %u", _66[1]);
    if (!(_66[1] & 0xF)) {
        return;
    }
    mStateMgr.changeState(StateID_RailMove);
}
tBranch(0x029788E0, RailPolyMgr::initializeState_Drop, tk::BranchType::b); // RailPolyMgr::initializeState_Drop()
