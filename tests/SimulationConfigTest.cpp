
#include <gtest/gtest.h>
#include "config/SimulationConfig.hpp"

TEST(SimulationConfigTest, ConvertsMetresToPixels)
{
    SimulationConfig config;

    EXPECT_FLOAT_EQ(500.0f, config.toScreenX(0.0f));
    EXPECT_FLOAT_EQ(300.0f, config.toScreenY(0.0f));

    EXPECT_FLOAT_EQ(700.0f, config.toScreenX(2.0f));
    EXPECT_FLOAT_EQ(200.0f, config.toScreenY(-1.0f));
}

TEST(SimulationConfigTest, SupportsDifferentScales)
{
    SimulationConfig config;

    config.pixelsPerMetre = 50.0f;

    EXPECT_FLOAT_EQ(600.0f, config.toScreenX(2.0f));
}
