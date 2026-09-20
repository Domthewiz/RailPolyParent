
#pragma once
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

        void setOffsets();
    
    private:
        sead::Vector3f  mInitialPosition;
        sead::Vector2f  mOffset;
        Angle           mAnglePhaseShift;
};

}