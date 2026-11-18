
#include <gtest/gtest.h>

#include "config/ConfigLoader.hpp"

// Test that the ConfigLoader correctly loads valid controls configuration
TEST(ConfigLoaderTest, LoadsValidControls)
{
    ControlsConfig config =
        ConfigLoader::loadControls("settings/controls.toml");

    EXPECT_FLOAT_EQ(4.0f, config.horizontalForceNewtons);
    EXPECT_FLOAT_EQ(2.0f, config.verticalSpeedMetresPerSecond);
    EXPECT_FLOAT_EQ(90.0f, config.pitchSpeedDegreesPerSecond);
}
