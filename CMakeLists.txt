cmake_minimum_required(VERSION 3.22.1)
project(littlegame)

set(CMAKE_CXX_STANDARD 17)

# Find SFML package
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
set(SRC_FILES
        main_source_files/main.cpp
        visual_source_files/view.cpp
        main_source_files/game.cpp
        world_source_files/entity.cpp
        world_source_files/hitbox.cpp
        world_source_files/entitycamera.cpp
        world_source_files/stopwatch.cpp
        world_source_files/rng.cpp
        world_source_files/world.cpp
        world_source_files/singletons.cpp
        world_source_files/abstractFactory.cpp
        visual_source_files/concreteFactory.cpp
        world_source_files/player.cpp
        visual_source_files/viewEntity.cpp
        visual_source_files/concreteCamera.cpp
        world_source_files/stationaryObject.cpp
        world_source_files/object.cpp
        world_source_files/levelEditor.cpp
        visual_source_files/button.cpp
        main_source_files/levelEditorApp.cpp
        visual_source_files/animationLibrary.cpp
)


add_executable(littlegame ${SRC_FILES})

target_link_libraries(littlegame sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
