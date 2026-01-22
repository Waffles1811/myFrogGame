//
// Created by jensp on 4/06/2025.
//

#include "levelEditorApp.h"

levelEditorApp::levelEditorApp() : playerView(std::make_shared<repr::view>()), curScale(1), curLayer(0) {
    std::shared_ptr<repr::concreteFactory> factory = std::make_shared<repr::concreteFactory>(playerView);
    editor = std::unique_ptr<world::levelEditor>( new world::levelEditor(factory));
    std::string type = "saveButton";
    std::string folder = "saveButton";
    std::shared_ptr<repr::button> saveButton = std::make_shared<repr::button>(type, folder, 1);
    buttons = {saveButton};
    playerView->addButton(saveButton);
}

void levelEditorApp::main_game_loop(){
    while (playerView->window->isOpen()) {
        processInputs();
        playerView->makeFrame(0, 0, 0);
        // ^^ change these numbers at some point :) probably get them from camera looking at player position
    }
}

void levelEditorApp::processInputs() {
    sf::Event event;
    while (playerView->window->pollEvent(event)) {
        bool buttonPressed = false;
        switch (event.type) {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape){
                    playerView->window->close();
                }
                break;
            case sf::Event::MouseButtonPressed:
                for (auto i : buttons){
                    if (i->getClicked(event.mouseButton.x, event.mouseButton.y)) {
                        buttonPressed = true;
                        switch (i->getType()) {
                            case buttonType::save:
                                std::ofstream file("newRoom.room");
                                uint32_t objectCount = objects.size();
                                file.write(reinterpret_cast<const char *>(&objectCount), sizeof(objectCount));
                                file.write(reinterpret_cast<const char *>(objects.data()),
                                           sizeof(saveFileObject) * objects.size());
                                file.close();
                                break;
                        }
                    }
                }
                if (not buttonPressed){
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        if( std::shared_ptr<world::entity> newEntity = editor->processClick(event.mouseButton.x, event.mouseButton.y, curLayer, curScale)){
                            objects.push_back(saveFileObject(newEntity->getXCoord(), newEntity->getYCoord(), curScale, curLayer, newEntity->getID()));
                        }
                    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
                        float x = event.mouseButton.x;
                        float y = -event.mouseButton.y;
                        auto dim = (editor->processRClick(x, y, curLayer));
                        if (dim.first!=0 or dim.second!=0) {
                            for (int j = 0; j < objects.size(); j++) {
                                auto i = objects[j];
                                if (i.getX() < x and i.getX() + dim.first > x and
                                    i.getY() > y and i.getY() - dim.second < y) {
                                    objects.erase(objects.begin() + j);
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
            case sf::Event::Closed:
                playerView->window->close(); // also exits program
                return;
        }
    }
}
