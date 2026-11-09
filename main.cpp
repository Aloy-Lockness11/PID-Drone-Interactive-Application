
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1000, 600}),
        "Drone PID Simulator"
    );

    //Drone object animation

    // Drone body
    sf::RectangleShape droneBody({100.f, 30.f});
    droneBody.setFillColor(sf::Color(150, 150, 150));
    droneBody.setOrigin({50.f, 15.f});
    droneBody.setPosition({500.f, 300.f});

    // Drone arms and motors
    sf::RectangleShape leftArm({90.f, 6.f});
    leftArm.setFillColor(sf::Color(110, 120, 135));
    leftArm.setOrigin({90.f, 3.f});
    leftArm.setPosition({500.f, 300.f});
    leftArm.setRotation(sf::degrees(12.f));

    sf::RectangleShape leftMotor({12.f, 12.f});
    leftMotor.setFillColor(sf::Color(13, 72, 106));
    leftMotor.setOrigin({6.f, 6.f});
    leftMotor.setPosition({412.f, 270.f});
 
    sf::RectangleShape rightArm({90.f, 6.f});
    rightArm.setFillColor(sf::Color(110, 120, 135));
    rightArm.setOrigin({0.f, 3.f});
    rightArm.setPosition({500.f, 300.f});
    rightArm.setRotation(sf::degrees(-12.f));

    sf::RectangleShape rightMotor({12.f, 12.f});
    rightMotor.setFillColor(sf::Color(13, 72, 106));
    rightMotor.setOrigin({6.f, 6.f});
    rightMotor.setPosition({588.f, 270.f});

    // Drone propellers
    sf::RectangleShape leftPropeller({80.f, 5.f});
    leftPropeller.setFillColor(sf::Color(80, 210, 240));
    leftPropeller.setOrigin({40.f, 2.5f});
    leftPropeller.setPosition({412.f, 259.f});

    sf::RectangleShape rightPropeller({80.f, 5.f});
    rightPropeller.setFillColor(sf::Color(80, 210, 240));
    rightPropeller.setOrigin({40.f, 2.5f});
    rightPropeller.setPosition({588.f, 259.f});



    // Window settings

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // Draw the drone
        window.draw(droneBody);
        window.draw(leftArm);
        window.draw(rightArm);
        window.draw(leftMotor);
        window.draw(rightMotor);
        window.draw(leftPropeller);
        window.draw(rightPropeller);

        window.display();
    }

    return 0;
}
