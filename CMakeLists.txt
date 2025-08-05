cmake_minimum_required(VERSION 3.22.1)
project(littlegame)

set(CMAKE_CXX_STANDARD 17)

# Find SFML package
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
option(USE_VERSION_A "Use Version A of the project" ON)
if(USE_VERSION_A)  # version with library
    set(SRC_FILES
            main_source_files/main.cpp
            visual_source_files/view.cpp
            main_source_files/game.cpp
            entity.cpp
            hitbox.cpp
            entitycamera.cpp
            entitymodel.cpp
            stopwatch.cpp
            rng.cpp
            world.cpp
            singletons.cpp
            abstractFactory.cpp
            visual_source_files/viewEntity.cpp
            player.cpp
            visual_source_files/concreteFactory.cpp
            object.cpp
            levelEditor.cpp
            visual_source_files/button.cpp
            main_source_files/levelEditorApp.cpp
            visual_source_files/animationLibrary.cpp

    )
else() # version without library
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
endif()

add_executable(littlegame ${SRC_FILES})

target_link_libraries(littlegame sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
