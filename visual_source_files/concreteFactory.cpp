//
// Created by Thoros of Myr on 11/05/2025.
//

#include "concreteFactory.h"

#include <utility>


repr::concreteFactory::concreteFactory(std::shared_ptr<repr::view> _playerView) : playerView(std::move(_playerView)) {
    library = std::make_shared<animationLibrary>(animationLibrary("assets"));
}

world::entity* repr::concreteFactory::produceEntity() {
    // make entity
    // add camera here
    return nullptr;
}

std::shared_ptr<world::player> repr::concreteFactory::producePlayer(float x, float y, int layer, float scale) {
    std::string name = "player";
    std::shared_ptr<repr::viewEntity> model = std::make_shared<repr::viewEntity>(name, name, scale);
    model->initialiseAnimations(library, "default");
    std::shared_ptr<repr::concreteCamera> cam = std::make_shared<repr::concreteCamera>(model);
    std::shared_ptr<repr::concreteAnimationObserver> obs =
            std::make_shared<repr::concreteAnimationObserver>(model);
    std::shared_ptr<repr::concreteOrientationObserver> orobs =
            std::make_shared<repr::concreteOrientationObserver>(model);
    std::shared_ptr<world::player> player = std::make_shared<world::player>(world::player(x, y));
    player->initialize();
    player->setpCam(cam, layer);
    player->setAnimationCameras(obs, orobs);
    playerView->addEntity(model, layer);
    return player;
}

std::shared_ptr<world::stationaryObject> repr::concreteFactory::produceObject(std::string& type, float x, float y,
                                                                              int layer, float scale) {

    std::string name = "kevin";
    std::shared_ptr<repr::viewEntity> model = std::make_shared<repr::viewEntity>(name, name, scale);
    std::shared_ptr<repr::concreteCamera> cam = std::make_shared<repr::concreteCamera>(model);
    std::shared_ptr<world::stationaryObject> object = std::make_shared<world::stationaryObject>(objectID::kevin, x, y, 136*scale, 136*scale);
    object->setpCam(cam, layer);
    playerView->addEntity(model, layer);
    return object;
}

std::shared_ptr<world::stationaryObject> repr::concreteFactory::produceWall(std::string &type, float x, float y, int layer, float scale) {
    std::string folder = "wall";
    std::string name = "rockWall";
    std::shared_ptr<repr::viewEntity> model = std::make_shared<repr::viewEntity>(name, folder, scale);
    std::shared_ptr<repr::concreteCamera> cam = std::make_shared<repr::concreteCamera>(model);
    std::shared_ptr<world::stationaryObject> object = std::make_shared<world::stationaryObject>(objectID::rockWall, x, y, 50*scale, 50*scale);
    object->setpCam(cam, layer);
    playerView->addEntity(model, layer);
    return object;
}


