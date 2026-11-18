
cmake_minimum_required(VERSION 3.20)

project(PIDDroneSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)
find_package(tomlplusplus CONFIG REQUIRED)

add_executable(drone
    src/main.cpp
    src/entities/Drone.cpp
    src/engine/physics/PhysicsComponent.cpp
    src/config/ConfigLoader.cpp
)

target_include_directories(drone PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(drone PRIVATE
    SFML::Graphics
    tomlplusplus::tomlplusplus
)

#TESTING
#--------------------------
# Enable unit testing
enable_testing()

# Find GoogleTest
find_package(GTest REQUIRED)

# Create our test executable
add_executable(physics_tests
    tests/PhysicsComponentTest.cpp
    tests/RenderingConfigTest.cpp
    tests/ConfigLoaderTest.cpp
    src/engine/physics/PhysicsComponent.cpp
    src/config/ConfigLoader.cpp
)

# Allow tests to include headers from src/
target_include_directories(physics_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link GoogleTest and tomlplusplus
target_link_libraries(physics_tests PRIVATE
    GTest::gtest_main
    tomlplusplus::tomlplusplus
)

# Register our tests with CTest
include(GoogleTest)


gtest_discover_tests(physics_tests
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

