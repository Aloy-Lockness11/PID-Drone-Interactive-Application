
#include <gtest/gtest.h>
#include "engine/physics/PhysicsComponent.hpp"

TEST(PhysicsComponentTest, StartsAtRest)
{
    PhysicsComponent physics;

    EXPECT_FLOAT_EQ(0.0f, physics.getVelocityX());
    EXPECT_FLOAT_EQ(0.0f, physics.getVelocityY());

    EXPECT_FLOAT_EQ(0.0f, physics.getPositionX());
    EXPECT_FLOAT_EQ(0.0f, physics.getPositionY());
}
