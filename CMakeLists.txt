
cmake_minimum_required(VERSION 3.20)

project(PIDDroneSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_executable(drone
    src/main.cpp
    src/entities/Drone.cpp
    src/engine/physics/PhysicsComponent.cpp
)

target_include_directories(drone PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(drone PRIVATE SFML::Graphics)
