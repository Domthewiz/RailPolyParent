// #include "actor/ActorBase.h"
// #include "utility/Direction.h"
// #include <actor/Actor.h>
// #include <graphics/AnimModel.h>
// #include <RailPolyParent/RailPolyParent.h>
// #include <RailPolyParent/actor/PairObjMovementParent.h>
// #include <red/util/SpriteUtil.h>
// #include <../REDCORE2.0HEADERS/SwitchFlagMgr.h>
// #include <telkin/Print.h>

// // This sprite is literally impossible to edit.
// namespace RailPolyParent {

// Profile* PairObjMovementParent::sProfile = RailPolyParent::getRegistrar()->newProfile<PairObjMovementParent>("pairobjmp")
//     .build();

// PairObjMovementParent::PairObjMovementParent(const ActorCreateParam& param)
//     : PairObjParentBase(param)
// { }

// ActorBase::Result PairObjMovementParent::create() {

//     if (!PairObjParentBase::create()) {
//         return cResult_Failed;
//     }

//     // If two way movement type not decided
//     if (!mTwoWayTypeOfMovement) {
//         mTwoWayTypeOfMovement = cTypeOfMovement_Go;
//     }
//     mReal_54 = mTwoWay.get_4c();
//     mReal_58 = mTwoWay.get_50();
//     mTwoWay.set_30(677777);
//     mTwoWay.set_3c(677777);
    
//     return cResult_Success;
// }

// bool PairObjMovementParent::execute() {
    
    
//     tk::println("30 %u, 3c %u, 40 %u, 44 %u, 48 %u,4c %u, 50 %u, 54 %u, 58 %u, 5c %u",mTwoWay.get_30(), mTwoWay.get_3c(),mTwoWay.get_40(),mTwoWay.getDisplacement(),mTwoWay.get_48(),mTwoWay.get_4c(),mTwoWay.get_50(),mTwoWay.get_54(),mTwoWay.get_58(),mTwoWay.get_5c());
    
//     if (!PairObjParentBase::execute()) { return false; }
//     // tk::println("Bree %u, %u", SwitchFlagMgr::instance()->isActivated(mSwitchFlag0 - 1), mSwitchFlag0);
//     if (mPrevSwitchFlag != SwitchFlagMgr::instance()->isActivated(mSwitchFlag0 - 1)) {
//         if (SwitchFlagMgr::instance()->isActivated(mSwitchFlag0 - 1)) {
//             PairObjParentBase::create();
//             mTwoWay.set_30(96);
//             mTwoWay.getStateMgr().changeState(PairObjMgr::StateID_Accelerating);
//         } else {
//             PairObjParentBase::create();
//             mTwoWay.initialize(mParam1 >> 0x14 & 0xF, static_cast<DirType>(mParam1 >> 0x14 & 0xF));
//             mTwoWay.set_3c(96);
//             mTwoWay.getStateMgr().changeState(PairObjMgr::StateID_Accelerating);
//         }
//     }
    
//     mPrevSwitchFlag = SwitchFlagMgr::instance()->isActivated(mSwitchFlag0 - 1);
//     // tk::println("internal::LogFormat format \n_1828, %u\n_182c, %u\n_1830, %u\n_1834, %u\n_1838, %f\n_183c, %u\n_1840, %u\n_1844 %u\n",_1828,_182c,_1830,_1834,_1838,sead::Mathf::idx2deg(_183c),_1840,_1844);
//     // if (*mTwoWay.getStateMgr().getStateID() == PairObjMgr::StateID_Static) {
//     //     } else {
//     //         // tk::println("Brbbee");
//     //         if (SwitchFlagMgr::instance()->isActivated(mSwitchFlag0 - 1)) {
//     //             // mTwoWay.setVelocity(-mTwoWay.getVelocity());
//     //             // _1838 = 0.0f;
//     //             // mTwoWay.getStateMgr().changeState(PairObjMgr::StateID_Static);
//     //             // mTwoWay.setComeAccelerationRate(0.0f);
//     //         } else {
//     //             mTwoWay.set_54(mReal_54);
//     //             mTwoWay.set_58(mReal_58);
//     //             // mTwoWay.setComeAccelerationRate(mRealComeVelocity);
//     //         }
//     //     }
//     // }



//     return true;
// }

// }
