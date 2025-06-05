//
// Created by Beric Dondarion on 11/05/2025.
//

#ifndef LITTLEGAME_CONCRETEFACTORY_H
#define LITTLEGAME_CONCRETEFACTORY_H
#include "../world_source_files/abstractFactory.h"
#include "view.h"
namespace repr{
class concreteFactory : public world::abstractFactory {
        std::shared_ptr<repr::view> playerView;
    public:
        concreteFactory(std::shared_ptr<repr::view>);
        world::entity* produceEntity() override;
        std::shared_ptr<world::player> producePlayer(float x, float y, int layer, float scale) override;
        std::shared_ptr<world::stationaryObject> produceObject(std::string& type, float x, float y, int layer, float scale) override;
        std::shared_ptr<world::stationaryObject> produceWall(std::string& type, float x, float y, int layer, float scale) override;
};
}

#endif //LITTLEGAME_CONCRETEFACTORY_H
