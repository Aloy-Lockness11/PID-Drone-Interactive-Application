
#pragma once

#include <SFML/Graphics.hpp>

class Drone : public sf::Transformable {
private:
    sf::RectangleShape body;

    sf::RectangleShape leftArm;
    sf::RectangleShape rightArm;

    sf::RectangleShape leftMotor;
    sf::RectangleShape rightMotor;

    sf::RectangleShape leftPropeller;
    sf::RectangleShape rightPropeller;

public:
    Drone();

    void draw(sf::RenderWindow& window);
};
