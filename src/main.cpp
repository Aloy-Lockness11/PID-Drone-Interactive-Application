#include "config/ConfigLoader.hpp"
#include <exception>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "entities/Drone.hpp"

int main()
{
    ControlsConfig controls;

    try
    {
        controls = ConfigLoader::loadControls(
            "settings/controls.toml"
        );
    }
    catch (const std::exception& error)
    {
        std::cerr << "Failed to load controls: "
                  << error.what() << '\n';

        return 1;
    }



    // Initialize the SFML window
    sf::RenderWindow window(
        sf::VideoMode({1000, 600}),
        "Drone PID Simulator"
    );

    //Drone object setup and rendering configuration initialization
    RenderingConfig config;
    Drone drone(config);

    sf::Clock clock;
    
    
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            drone.applyHorizontalForce(
                -controls.horizontalForceNewtons
            );
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            drone.applyHorizontalForce(
                controls.horizontalForceNewtons
            );
        }
        
        
        // Temporary direct vertical controls
        const float verticalMovement =
            controls.verticalSpeedMetresPerSecond *
            config.pixelsPerMetre * dt;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            drone.move({0.f, -verticalMovement});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            drone.move({0.f, verticalMovement});
        }


        // Rotate the drone based on keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            drone.rotate(sf::degrees(
                -controls.pitchSpeedDegreesPerSecond * dt
            ));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
        {
            drone.rotate(sf::degrees(
                controls.pitchSpeedDegreesPerSecond * dt
            ));
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