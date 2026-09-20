#include "actor/ActorBase.h"
#include <actor/Actor.h>
#include <graphics/AnimModel.h>
#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/CenterSwingMovementParent.h>
#include <red/util/SpriteUtil.h>
#include <telkin/Print.h>

namespace RailPolyParent {

Profile* CenterSwingMovementParent::sProfile = RailPolyParent::getRegistrar()->newProfile<CenterSwingMovementParent>("swaycentermp")
    .build();

CenterSwingMovementParent::CenterSwingMovementParent(const ActorCreateParam& param)
    : CenterSwingParentBase(param)
{ }

ActorBase::Result CenterSwingMovementParent::create() {
    // Setting: Movement Type
    const u8 movementType = mLayer;
    if (movementType > ParentMovementType::cPos_KinokoLift) {
        tk::fatal("MagicPlatform invalid movement type");
        return cResult_Failed;
    }
    
    u32 movementMask = mMovementMgr.getTypeMask(static_cast<ParentMovementType>(movementType));

    // Helps prevent the pivotal-rotation from bugging out
    if (movementMask == cPos_CenterRotation) {
        
        ParentMovementMgr::PivotalRotationSettings pivotSettings;
        pivotSettings.position       = mPos;
        pivotSettings.movement_id    = mParamEx.course.init_state_flag;
        pivotSettings.movement_mask  = movementMask;
        pivotSettings.pivot_center   = sead::Vector3f(0.0f, 0.0f, 0.0f);
        pivotSettings.upside_down    = 0;
        pivotSettings.gyroscopic     = 0;
        pivotSettings.tilted         = 0;
        pivotSettings._21            = 0;
        pivotSettings.movement_param = 1;

        mMovementMgr.linkPivotal2(pivotSettings);
    } else {
        mMovementMgr.link(mPos, movementMask, mParamEx.course.init_state_flag);
    }

    setMovementParams();
    // helps avoid crashes for some reason
    if(mMovementMgr.getParentActorID() != this->getActorUniqueID()) {}

    // helps avoid crashes for some reason
    mMovementMgr.execute();

    // tk::println("CenterSwingMovementParent was created!");

    if (!CenterSwingParentBase::create()) {
        return cResult_Failed;
    }

    return cResult_Success;
}

bool CenterSwingMovementParent::execute() {
    if (!CenterSwingParentBase::execute()) {
        return false;
    }

    mMovementMgr.execute();
    mPos.x = mMovementMgr.getPosition().x;
    mPos.y = mMovementMgr.getPosition().y;

    return true;
}

void CenterSwingMovementParent::setMovementParams() {
        static sead::SafeArray<f32, 16> twoWayDistanceMultiplierArr {
            1.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f, 1.3f, 1.4f, 1.5f
        };
        static sead::SafeArray<f32, 16> boltMovementSpeedArr {
            1.0f, 0.25f, 0.5f, 0.75f, 0.0f, 1.5f, 2.0f, 2.5f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f
        };

        ParentMovementType mvtp = static_cast<ParentMovementType>(mLayer);
        if (mvtp == ParentMovementType::cPos_FloorGyration) {
            mMovementMgr.setFloorGyrationAngle(0x1000000 * red::SpriteUtil::getNybbleRange(this, 23, 24));
            ParentMovementMgr::MovementProperties newproperty = mMovementMgr.getMovementProperties();
            newproperty.hill_distance_offset = -16.0f * red::SpriteUtil::getNybble19(this);
            mMovementMgr.setMovementProperties(newproperty);
        } else if (mvtp == ParentMovementType::cPos_GoAndCome) {
            mMovementMgr.setTwoWayDistanceMultiplier(twoWayDistanceMultiplierArr[red::SpriteUtil::getNybble23(this)] + (0.01f * red::SpriteUtil::getNybble24(this)));
        } else if (mvtp == ParentMovementType::cPos_Screw) {
            mMovementMgr.setBoltSpeed(boltMovementSpeedArr[red::SpriteUtil::getNybble23(this)]);
            mMovementMgr.setBoltDirection(static_cast<DirType>(red::SpriteUtil::getNybble24(this)));
        } else if (mvtp == ParentMovementType::cPos_ShiftingPlatform) {
            mMovementMgr.setRectPlatformInfo(static_cast<RectPlatformInfo>(red::SpriteUtil::getNybble24(this)));
        }
    }
}
