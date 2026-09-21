
#pragma once
#include "PairObjParentBase.h"

namespace RailPolyParent {
    
class PairObjMovementParent : public PairObjParentBase {
    public:
        static Profile* sProfile;

        enum TypeOfMovement : u8
        {
            cTypeOfMovement_Num = 0,
            cTypeOfMovement_Go = 1,
            cTypeOfMovement_Come = 2,
        };
    
    public:
        PairObjMovementParent(const ActorCreateParam& param);
        ~PairObjMovementParent() override = default;
    
        Result create() override;
        bool execute() override;

    
    private:
        f32             mTwoWayLastMovementSign;
        TypeOfMovement  mTwoWayTypeOfMovement;
        bool            mNotMoving;
};

}