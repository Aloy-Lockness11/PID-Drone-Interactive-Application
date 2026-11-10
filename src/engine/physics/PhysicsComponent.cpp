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
    // Newton's second law: F = ma
    float accelerationX = forceX / mass;
    float accelerationY = forceY / mass;

    // Update velocity
    velocityX += accelerationX * dt;
    velocityY += accelerationY * dt;

    // Update position
    positionX += velocityX * dt;
    positionY += velocityY * dt;

    // Clear forces for the next simulation update
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
