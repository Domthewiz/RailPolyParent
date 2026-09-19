
#pragma once
#include <RailPolyParent/actor/CenterRotationParentBase.h>

namespace RailPolyParent {
    
class DaenParent : public CenterRotationParentBase {
    public:
        static Profile* sProfile;
    
    public:
        DaenParent(const ActorCreateParam& param);
        ~DaenParent() override = default;
    
        Result create() override;
        bool execute() override;

        void setOffsets();
    
    private:
        sead::Vector3f  mInitialPosition;
        sead::Vector2f  mOffset;
        Angle           mAnglePhaseShift;
};

}