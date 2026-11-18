
cmake_minimum_required(VERSION 3.20)

project(PIDDroneSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
find_package(SFML 3 REQUIRED COMPONENTS Graphics)
find_package(tomlplusplus CONFIG REQUIRED)

# ---------------------------------------
# Reusable physics engine library
# ---------------------------------------
add_library(physics_engine STATIC
    src/engine/physics/PhysicsComponent.cpp
    src/engine/config/PhysicsConfigLoader.cpp
)

target_include_directories(physics_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(physics_engine PUBLIC
    tomlplusplus::tomlplusplus
)

# ---------------------------------------
# Drone simulator
# ---------------------------------------
add_executable(drone
    src/main.cpp
    src/entities/Drone.cpp
    src/config/ConfigLoader.cpp
)

target_include_directories(drone PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(drone PRIVATE
    physics_engine
    SFML::Graphics
    tomlplusplus::tomlplusplus
)



# ---------------------------------------
# Testing
# ---------------------------------------
enable_testing()

find_package(GTest REQUIRED)

add_executable(physics_tests
    tests/PhysicsComponentTest.cpp
    tests/RenderingConfigTest.cpp
    tests/ControlsConfigLoaderTest.cpp
    tests/RenderingConfigLoaderTest.cpp
    tests/PhysicsConfigLoaderTest.cpp

    src/config/ConfigLoader.cpp
)

target_include_directories(physics_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(physics_tests PRIVATE
    GTest::gtest_main
    physics_engine
    tomlplusplus::tomlplusplus
)

# Provide an absolute project path to the tests
target_compile_definitions(physics_tests PRIVATE
    TEST_PROJECT_ROOT="${CMAKE_CURRENT_SOURCE_DIR}"
)

include(GoogleTest)

gtest_discover_tests(physics_tests
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
