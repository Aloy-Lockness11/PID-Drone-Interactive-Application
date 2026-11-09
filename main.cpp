
#include <SFML/Graphics.hpp>

#include "Drone.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1000, 600}),
        "Drone PID Simulator"
    );

    //Drone object animation
    Drone drone;

    drone.move({100.f, 0.f});
    drone.setRotation(sf::degrees(15.f));


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

        // Draw the entire drone
        drone.draw(window);

        window.display();
    }

    return 0;
}