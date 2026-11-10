
#pragma once

class PhysicsComponent {
private:
    // Physical properties
    float mass = 1.0f;

    // Position in metres
    float positionX = 0.0f;
    float positionY = 0.0f;

    // Velocity in metres per second
    float velocityX = 0.0f;
    float velocityY = 0.0f;

    // Accumulated forces in newtons
    float forceX = 0.0f;
    float forceY = 0.0f;

public:
    PhysicsComponent();

    void applyForce(float fx, float fy);
    void update(float dt);

    float getPositionX() const;
    float getPositionY() const;

    float getVelocityX() const;
    float getVelocityY() const;
};
