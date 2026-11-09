
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
    sf::Clock clock;

    const float speed = 200.f;

    
    // Window settings

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        //time elapsed since last frame
        const float dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);


        // Handle keyboard input for drone movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            drone.move({0.f, -speed * dt});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            drone.move({0.f, speed * dt});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            drone.move({-speed * dt, 0.f});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            drone.move({speed * dt, 0.f});
        }

        
        // Draw the entire drone
        drone.draw(window);

        window.display();
    }

    return 0;
}