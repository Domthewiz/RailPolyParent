#include <actor/Actor.h>
#include <graphics/AnimModel.h>
#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/LineFollowerParent.h>
#include <telkin/Print.h>
#include <red/util/SpriteUtil.h>

namespace RailPolyParent {

Profile* LineFollowerParent::sProfile = RailPolyParent::getRegistrar()->newProfile<LineFollowerParent>("line_fp")
    .build();

LineFollowerParent::LineFollowerParent(const ActorCreateParam& param)
    : RailPolyParentBase(param)
{ }

ActorBase::Result LineFollowerParent::create() {
    // tk::println("LineFollowerParent was created!");
    static sead::SafeArray<f32, 10> lineSpeeds {
        1.0f, 0.5f, 1.5f, 2.0f, 2.5f,
        3.0f, 3.5f, 4.0f, 4.5f, 5.0f
    };

    bool mGoesLeft  = red::SpriteUtil::getNybble12(this) == 0;
    f32  mLineSpeed = lineSpeeds[red::SpriteUtil::getNybble11(this)];

    sead::Vector2f mLinePos(mPos.x, mPos.y);
    mLineFollower.init(mLinePos, mLayer, mLineSpeed, static_cast<LineMgr::Type>(red::SpriteUtil::getNybble9(this)), mGoesLeft);
    mLineFollower.startLineMove(false);

    return RailPolyParentBase::create();
}

bool LineFollowerParent::execute() {
    mLineFollower.execute();
    mPos.x = mLineFollower.getPos().x;
    mPos.y = mLineFollower.getPos().y;
    
    return true;
}

}
