cmake_minimum_required(VERSION 3.22.1)
project(littlegame)

set(CMAKE_CXX_STANDARD 11)

# Find SFML package
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
option(USE_VERSION_A "Use Version A of the project" ON)
if(USE_VERSION_A)  # version with library
    set(SRC_FILES
            main.cpp
            view.cpp
            game.cpp
            entity.cpp
            hitbox.cpp
            entitycamera.cpp
            entitymodel.cpp
            stopwatch.cpp
            rng.cpp
            world.cpp
            singletons.cpp
            abstractFactory.cpp
            viewEntity.cpp
            player.cpp
            concreteFactory.cpp
    )
else() # version without library
    set(SRC_FILES
            main.cpp
            view.cpp
            game.cpp
            library_source_files/entity.cpp
            library_source_files/hitbox.cpp
            library_source_files/entitycamera.cpp
            library_source_files/stopwatch.cpp
            library_source_files/rng.cpp
            library_source_files/world.cpp
            library_source_files/singletons.cpp
            library_source_files/abstractFactory.cpp
            concreteFactory.cpp
            library_source_files/player.cpp
            viewEntity.cpp
            concreteCamera.cpp
            library_source_files/stationaryObject.cpp
            library_source_files/stationaryObject.h
    )
endif()

add_executable(littlegame ${SRC_FILES})

target_link_libraries(littlegame sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
