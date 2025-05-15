//
// Created by Game of Thrones on 7/05/2025.
//

#include "game.h"
game::game() {
    playerView = std::make_shared<repr::view>();
    std::shared_ptr<repr::concreteFactory> factory = std::make_shared<repr::concreteFactory>(playerView);
    world = std::unique_ptr<world::world>( new world::world(factory));
    stopwatchInc = std::unique_ptr<world::stopwatchFactory>(new world::stopwatchFactory());
}

void game::setup() {
    world->setup();
}

void game::main_game_loop() {
    float timeSinceLastTic = stopwatchInc->getStopwatch()->timeTic();
    // called here so it isn't too long later
    while (playerView->window->isOpen()) {
        timeSinceLastTic = stopwatchInc->getStopwatch()->timeTic();
        processInputs();
        world->time_up(timeSinceLastTic);
        playerView->makeframe(0, 0);
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
                    world->goLeft();
                } else if (event.key.code == sf::Keyboard::Right or event.key.code == sf::Keyboard::D) {
                    world->goRight();
                } else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::W){
                    world->faceUp();
                } else if (event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::S){
                    world->faceDown();
                } else if (event.key.code == sf::Keyboard::Space){
                    world->jump();
                } else if (event.key.code == sf::Keyboard::LShift){
                    world->dash();
                } else if (event.key.code == sf::Keyboard::Q){
                    world->clingToWall();
                }

                break;
            case sf::Event::KeyReleased:
                // sets the variable to false again if the key isn't being pressed anymore
                if (event.key.code == sf::Keyboard::Left or event.key.code == sf::Keyboard::A) {
                    world->stopLeft();
                } else if (event.key.code == sf::Keyboard::Right or event.key.code == sf::Keyboard::D) {
                    world->stopRight();
                } else if (event.key.code == sf::Keyboard::Up or event.key.code == sf::Keyboard::W){
                    world->stopUp();
                } else if (event.key.code == sf::Keyboard::Down or event.key.code == sf::Keyboard::S) {
                    world->stopDown();
                } else if (event.key.code == sf::Keyboard::Q){
                    world->releaseWall();
                }
                break;
            case sf::Event::Closed:
                playerView->window->close(); // also exits program
                return;
        }
    }
}