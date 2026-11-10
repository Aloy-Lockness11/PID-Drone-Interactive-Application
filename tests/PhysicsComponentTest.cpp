
#include <gtest/gtest.h>
#include "engine/physics/PhysicsComponent.hpp"

// Test that a newly created PhysicsComponent starts at rest with zero velocity and position.
TEST(PhysicsComponentTest, StartsAtRest)
{
    PhysicsComponent physics;

    EXPECT_FLOAT_EQ(0.0f, physics.getVelocityX());
    EXPECT_FLOAT_EQ(0.0f, physics.getVelocityY());

    EXPECT_FLOAT_EQ(0.0f, physics.getPositionX());
    EXPECT_FLOAT_EQ(0.0f, physics.getPositionY());
}


// Test that applying a force changes the velocity
TEST(PhysicsComponentTest, ForceChangesVelocity)
{
    PhysicsComponent physics;

    // Apply a horizontal force of 10 newtons
    physics.applyForce(10.0f, 0.0f);

    // Simulate one second
    physics.update(1.0f);

    // Expected horizontal velocity: 10 m/s
    EXPECT_FLOAT_EQ(10.0f, physics.getVelocityX());

    // No vertical force was applied
    EXPECT_FLOAT_EQ(0.0f, physics.getVelocityY());
}


// Test that applying a force changes the position using constant acceleration formula 
TEST(PhysicsComponentTest, ForceChangesPosition)
{
    PhysicsComponent physics;

    // Apply 10 newtons to our default 1 kg object
    physics.applyForce(10.0f, 0.0f);

    // Simulate one second
    physics.update(1.0f);

    // Expected displacement: 0.5 * 10 * 1^2 = 5 metres
    EXPECT_NEAR(5.0f, physics.getPositionX(), 0.0001f);

    // No vertical force or velocity
    EXPECT_FLOAT_EQ(0.0f, physics.getPositionY());
}


