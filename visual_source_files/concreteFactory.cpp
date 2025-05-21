//
// Created by Thoros of Myr on 11/05/2025.
//

#include "concreteFactory.h"

#include <utility>


repr::concreteFactory::concreteFactory(std::shared_ptr<repr::view> _playerView) : playerView(std::move(_playerView)) {}

world::entity* repr::concreteFactory::produceEntity() {
    // make entity
    // add camera here
    return nullptr;
}

std::shared_ptr<world::player> repr::concreteFactory::producePlayer() {
    std::shared_ptr<world::player> player = std::make_shared<world::player>(world::player());
    player->initialize();
    std::shared_ptr<repr::concreteCamera> cam = std::make_shared<repr::concreteCamera>();
    player->setpCam(cam);
    std::shared_ptr<repr::concreteAnimationObserver> obs = std::make_shared<repr::concreteAnimationObserver>();
    player->setAnimationCamera(obs);
    std::string name = "player";
    std::shared_ptr<repr::viewEntity> model = std::make_shared<repr::viewEntity>(name, cam, 2.5);
    model->initialize(obs);
    playerView->addentity(model);
    return player;
}

std::shared_ptr<world::stationaryObject> repr::concreteFactory::produceObject(std::string& type) {
    std::shared_ptr<world::stationaryObject> object
                = std::make_shared<world::stationaryObject>(type, 300, -524, 136, 136);
    std::shared_ptr<repr::concreteCamera> cam = std::make_shared<repr::concreteCamera>();
    object->setpCam(cam);
    std::shared_ptr<repr::viewEntity> model = std::make_shared<repr::viewEntity>(type, cam, 1);
    model->initialize(nullptr);
    playerView->addentity(model);
    return object;
}


