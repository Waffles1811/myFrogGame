//
// Created by Game of Thrones on 7/05/2025.
//

#include "game.h"

game::game() {
    playerView = std::make_shared<repr::view>();
    std::shared_ptr<repr::concreteFactory> factory = std::make_shared<repr::concreteFactory>(playerView);
    world = std::unique_ptr<world::world>( new world::world(factory));
    stopwatchInc = std::unique_ptr<world::stopwatchFactory>(new world::stopwatchFactory());
    buttons = {};
}

void game::setup() {
    loadFromFile("newRoom.room");
}

void game::main_game_loop() {
    float timeSinceLastTic;
    stopwatchInc->getStopwatch()->timeTic();
    // called here so it isn't too long later
    while (playerView->window->isOpen()) {
        timeSinceLastTic = stopwatchInc->getStopwatch()->timeTic();
        processInputs();
        world->time_up(timeSinceLastTic);
        playerView->makeFrame(0, 0, timeSinceLastTic);
        // ^^ change these numbers at some point :) probably get them from camera looking at player position
    }
}

void game::processInputs() {
    sf::Event event;
    while (playerView->window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                // if a key being pressed adds speed it will be added every tic which will make the player very fast,
                // instead it sets a variable to true which moves the player
                if (event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::A) {
                    // ^ maybe change this back to scancode on windows, didn't work on linux for me
                    world->processInputs(movement::moveLeft);
                } else if (event.key.code == sf::Keyboard::Right or event.key.code == sf::Keyboard::D) {
                    world->processInputs(movement::moveRight);
                } else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::W){
                    world->processInputs(movement::faceUp);
                } else if (event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::S){
                    world->processInputs(movement::faceDown);
                } else if (event.key.code == sf::Keyboard::Space){
                    world->processInputs(movement::jump);
                } else if (event.key.code == sf::Keyboard::LShift){
                    world->processInputs(movement::dash);
                } else if (event.key.code == sf::Keyboard::Q){
                    world->processInputs(movement::wallCling);
                } else if (event.key.code == sf::Keyboard::Escape){
                    playerView->window->close();
                }
                break;
            case sf::Event::KeyReleased:
                // sets the variable to false again if the key isn't being pressed anymore
                if (event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::A) {
                    world->processInputs(movement::stopLeft);
                } else if (event.key.code == sf::Keyboard::Right or event.key.code == sf::Keyboard::D) {
                    world->processInputs(movement::stopRight);
                } else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::W){
                    world->processInputs(movement::stopUp);
                } else if (event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::S) {
                    world->processInputs(movement::stopDown);
                } else if (event.key.code == sf::Keyboard::Space){
                    world->processInputs(movement::stopJump);
                } else if (event.key.code == sf::Keyboard::Q){
                    world->processInputs(movement::stopCling);
                }
                break;
            case sf::Event::Closed:
                playerView->window->close(); // also exits program
                return;
        }
    }
}

void game::loadFromFile(std::string fileName) {
    // reads file
    std::ifstream file(fileName, std::ios::binary);
    uint32_t objectCount;
    file.read(reinterpret_cast<char*>(&objectCount), sizeof(objectCount));
    std::vector<saveFileObject> objects(objectCount);
    file.read(reinterpret_cast<char*>(objects.data()), sizeof(saveFileObject) * objectCount);
    file.close();
    playerView->reset();
    world->loadRoom(objects);
}

