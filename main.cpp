
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
    const float horizontalAcceleration = 150.f;
    

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


        // Set the horizontal acceleration of the drone
        float inputAcceleration = 0.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            inputAcceleration -= horizontalAcceleration;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            inputAcceleration += horizontalAcceleration;
        }

        drone.setHorizontalAcceleration(inputAcceleration);
        drone.update(dt);

        // Rotate the drone based on keyboard input
        const float rotationSpeed = 90.f; // Degrees per second

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            drone.rotate(sf::degrees(-rotationSpeed * dt));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
        {
            drone.rotate(sf::degrees(rotationSpeed * dt));
        }




        // Draw the entire drone
        drone.draw(window);

        window.display();
    }

    return 0;
}