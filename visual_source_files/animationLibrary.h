//
// Created by waffle_laptop on 5/08/25.
//

#ifndef LITTLEGAME_ANIMATIONLIBRARY_H
#define LITTLEGAME_ANIMATIONLIBRARY_H
#include <map>
#include <string>
#include <fstream>
#include <filesystem>
#include "../json.hpp"
using json = nlohmann::json;



class animationLibrary {
    std::unordered_map<std::string, std::unordered_map<std::string, json>> library; // outer map uses name of entity, inner map uses name of animation
public:
    animationLibrary(std::string folderPath);// reads out all the animations in a folder
    void readFolder(std::string folderPath);
    json getAnimation(std::string entity, std::string anim);
};


#endif //LITTLEGAME_ANIMATIONLIBRARY_H
