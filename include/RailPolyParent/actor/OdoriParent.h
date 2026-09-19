
#pragma once
#include <RailPolyParent/actor/RailPolyParentBase.h>

namespace RailPolyParent {
    
    class OdoriParent : public RailPolyParentBase {
        public:
        static Profile* sProfile;
        
        public:
        OdoriParent(const ActorCreateParam& param);
        ~OdoriParent() override = default;
        
        Result create() override;
        bool execute() override;
        // bool draw() override;
        
        private:
        // AnimModel* mModel;
    };
}