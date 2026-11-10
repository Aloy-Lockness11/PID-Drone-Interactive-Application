
#include "Drone.hpp"


Drone::Drone()
{
    // Position of the complete drone in the window
    setPosition({500.f, 300.f});

    // Body
    body.setSize({50.f, 15.f});
    body.setFillColor(sf::Color(150, 150, 150));
    body.setOrigin({25.f, 7.5f});
    body.setPosition({0.f, 0.f});

    // Left arm
    leftArm.setSize({45.f, 3.f});
    leftArm.setFillColor(sf::Color(110, 120, 135));
    leftArm.setOrigin({45.f, 1.5f});
    leftArm.setPosition({0.f, 0.f});
    leftArm.setRotation(sf::degrees(12.f));

    // Right arm
    rightArm.setSize({45.f, 3.f});
    rightArm.setFillColor(sf::Color(110, 120, 135));
    rightArm.setOrigin({0.f, 1.5f});
    rightArm.setPosition({0.f, 0.f});
    rightArm.setRotation(sf::degrees(-12.f));

    // Motors
    leftMotor.setSize({6.f, 6.f});
    leftMotor.setFillColor(sf::Color(13, 72, 106));
    leftMotor.setOrigin({3.f, 3.f});
    leftMotor.setPosition({-44.f, -15.f});

    rightMotor.setSize({6.f, 6.f});
    rightMotor.setFillColor(sf::Color(13, 72, 106));
    rightMotor.setOrigin({3.f, 3.f});
    rightMotor.setPosition({44.f, -15.f});

    // Propellers
    leftPropeller.setSize({40.f, 2.5f});
    leftPropeller.setFillColor(sf::Color(80, 210, 240));
    leftPropeller.setOrigin({20.f, 1.25f});
    leftPropeller.setPosition({-44.f, -20.5f});

    rightPropeller.setSize({40.f, 2.5f});
    rightPropeller.setFillColor(sf::Color(80, 210, 240));
    rightPropeller.setOrigin({20.f, 1.25f});
    rightPropeller.setPosition({44.f, -20.5f});
}



void Drone::draw(sf::RenderWindow& window)
{
    sf::RenderStates states;
    states.transform = getTransform();

    window.draw(leftArm, states);
    window.draw(rightArm, states);

    window.draw(leftMotor, states);
    window.draw(rightMotor, states);

    window.draw(body, states);

    window.draw(leftPropeller, states);
    window.draw(rightPropeller, states);
}

void Drone::setHorizontalAcceleration(float acceleration)
{
    accelerationX = acceleration;
}


void Drone::update(float dt)
{
    // Horizontal acceleration from keyboard input
    velocityX += accelerationX * dt;

    // Apply simple linear drag
    const float drag = 0.3f;
    velocityX -= velocityX * drag * dt;

    // Update the drone's position
    move({velocityX * dt, 0.f});
}