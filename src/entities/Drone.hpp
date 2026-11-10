
#pragma once

#include <SFML/Graphics.hpp>

class Drone : public sf::Transformable {
private:

    // Horizontal velocity and acceleration of the drone
    float velocityX = 0.f;
    float accelerationX = 0.f;

    sf::RectangleShape body;

    sf::RectangleShape leftArm;
    sf::RectangleShape rightArm;

    sf::RectangleShape leftMotor;
    sf::RectangleShape rightMotor;

    sf::RectangleShape leftPropeller;
    sf::RectangleShape rightPropeller;

public:
    Drone();

    // Set the horizontal acceleration of the drone
    void setHorizontalAcceleration(float acceleration);
    void update(float dt);


    void draw(sf::RenderWindow& window);
};
