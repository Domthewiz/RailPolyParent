
#pragma once
#include <RailPolyParent/actor/CenterSwingParentBase.h>

namespace RailPolyParent {
    
class DaenSwingParent : public CenterSwingParentBase {
    public:
        static Profile* sProfile;
    
    public:
        DaenSwingParent(const ActorCreateParam& param);
        ~DaenSwingParent() override = default;
    
        Result create() override;
        bool execute() override;

        void setOffsets();
    
    private:
        sead::Vector3f  mInitialPosition;
        sead::Vector2f  mOffset;
        Angle           mAnglePhaseShift;
};

}