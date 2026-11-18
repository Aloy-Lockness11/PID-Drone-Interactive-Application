
#include <SFML/Graphics.hpp>
#include "entities/Drone.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({1000, 600}),
        "Drone PID Simulator"
    );

    //Drone object setup and SimulationConfig initialization
    RenderingConfig config;
    Drone drone(config);

    sf::Clock clock;


    const float speed = 200.f;
    
    

    // Window settings

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        //STEP 1: Calculate the time elapsed since last frame
        const float dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }



        //STEP 2: Read keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            drone.move({0.f, -speed * dt});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            drone.move({0.f, speed * dt});
        }

        
        // Temporary horizontal force controls
        const float horizontalForce = 4.0f; // Newtons

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            drone.applyHorizontalForce(-horizontalForce);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            drone.applyHorizontalForce(horizontalForce);
        }

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

        //STEP 3: Update drone physics
        drone.update(dt);

        //STEP 4: Clear the window before drawing
        window.clear(sf::Color::Black);


        //STEP 5: Draw the drone
        drone.draw(window);

        window.display();
    }

    return 0;
}