
#pragma once

#include <SFML/Graphics.hpp>
#include "config/SimulationConfig.hpp"
#include "engine/physics/PhysicsComponent.hpp"

class Drone : public sf::Transformable {
private:

    
    // Adds SimulationConfig to the drone for rendering purposes
    SimulationConfig config;

    // Adds physics engine capabilities to the drone
    PhysicsComponent physics;

    sf::RectangleShape body;

    sf::RectangleShape leftArm;
    sf::RectangleShape rightArm;

    sf::RectangleShape leftMotor;
    sf::RectangleShape rightMotor;

    sf::RectangleShape leftPropeller;
    sf::RectangleShape rightPropeller;

public:

    //Constructor that initializes the drone with a given SimulationConfig
    explicit Drone(const SimulationConfig& config);

    // Set the horizontal acceleration of the drone
    void applyHorizontalForce(float force);
    void update(float dt);


    void draw(sf::RenderWindow& window);
};
