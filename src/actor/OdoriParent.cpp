#include <actor/Actor.h>
#include <graphics/AnimModel.h>
#include <RailPolyParent/RailPolyParent.h>
#include <RailPolyParent/actor/OdoriParent.h>
#include <telkin/Print.h>

namespace RailPolyParent {

Profile* OdoriParent::sProfile = RailPolyParent::getRegistrar()->newProfile<OdoriParent>("odoriparent")
    .build();

OdoriParent::OdoriParent(const ActorCreateParam& param)
    : RailPolyParentBase(param)
{ }

ActorBase::Result OdoriParent::create() {
    // tk::println("OdoriParent was created!");

    return RailPolyParentBase::create();
}

bool OdoriParent::execute() {
    if (!RailPolyParentBase::execute()) {
        return false;
    }
    // mPos.x += 1.0f;
    return true;
}

}
