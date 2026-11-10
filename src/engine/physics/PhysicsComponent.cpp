#include "PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent()
{

}

void PhysicsComponent::applyForce(float fx, float fy)
{
    forceX += fx;
    forceY += fy;
}


void PhysicsComponent::update(float dt)
{
    // Calculate acceleration using Newton's second law
    float accelerationX = forceX / mass;
    float accelerationY = forceY / mass;

    // Calculate displacement using constant acceleration
    positionX += velocityX * dt
               + 0.5f * accelerationX * dt * dt;

    positionY += velocityY * dt
               + 0.5f * accelerationY * dt * dt;

    // Update velocity
    velocityX += accelerationX * dt;
    velocityY += accelerationY * dt;

    // Reset accumulated forces
    forceX = 0.0f;
    forceY = 0.0f;
}


float PhysicsComponent::getPositionX() const
{
    return positionX;
}

float PhysicsComponent::getPositionY() const
{
    return positionY;
}

float PhysicsComponent::getVelocityX() const
{
    return velocityX;
}

float PhysicsComponent::getVelocityY() const
{
    return velocityY;
}

float PhysicsComponent::getMass() const
{
    return mass;
}