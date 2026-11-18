#include <filesystem>
#include <gtest/gtest.h>
#include <stdexcept>
#include <toml++/toml.hpp>

#include "config/ConfigLoader.hpp"

// Test that the ConfigLoader correctly loads valid controls configuration
TEST(ControlsConfigLoaderTest, LoadsValidControls)
{
    const auto path = std::filesystem::path(TEST_PROJECT_ROOT) /
                  "settings/controls.toml";

    ControlsConfig config = ConfigLoader::loadControls(path.string());

    EXPECT_FLOAT_EQ(4.0f, config.horizontalForceNewtons);
    EXPECT_FLOAT_EQ(2.0f, config.verticalSpeedMetresPerSecond);
    EXPECT_FLOAT_EQ(90.0f, config.pitchSpeedDegreesPerSecond);
}


// Test that the ConfigLoader rejects negative horizontal force values
TEST(ControlsConfigLoaderTest, RejectsNegativeHorizontalForce)
{
    // Create TOML data directly in memory
    auto data = toml::parse(R"(
        [manual]
        horizontal_force_newtons = -4.0
        vertical_speed_metres_per_second = 2.0
        pitch_speed_degrees_per_second = 90.0
    )");

    // Verify that the loader rejects invalid values
    EXPECT_THROW(
        ConfigLoader::parseControls(data),
        std::runtime_error
    );
}

// Test that the ConfigLoader rejects negative vertical speed values
TEST(ControlsConfigLoaderTest, RejectsNegativeVerticalSpeed)
{
    auto data = toml::parse(R"(
        [manual]
        horizontal_force_newtons = 4.0
        vertical_speed_metres_per_second = -2.0
        pitch_speed_degrees_per_second = 90.0
    )");

    EXPECT_THROW(
        ConfigLoader::parseControls(data),
        std::runtime_error
    );
}

// Test that the ConfigLoader rejects negative pitch speed values
TEST(ControlsConfigLoaderTest, RejectsNegativePitchSpeed)
{
    auto data = toml::parse(R"(
        [manual]
        horizontal_force_newtons = 4.0
        vertical_speed_metres_per_second = 2.0
        pitch_speed_degrees_per_second = -90.0
    )");

    EXPECT_THROW(
        ConfigLoader::parseControls(data),
        std::runtime_error
    );
}


// Test that the ConfigLoader rejects missing horizontal force values
TEST(ControlsConfigLoaderTest, RejectsMissingHorizontalForce)
{
    auto data = toml::parse(R"(
        [manual]
        vertical_speed_metres_per_second = 2.0
        pitch_speed_degrees_per_second = 90.0
    )");

    EXPECT_THROW(
        ConfigLoader::parseControls(data),
        std::runtime_error
    );
}


// Test that the checks reject incorrect value types
TEST(ControlsConfigLoaderTest, RejectsIncorrectValueType)
{
    auto data = toml::parse(R"(
        [manual]
        horizontal_force_newtons = "fast"
        vertical_speed_metres_per_second = 2.0
        pitch_speed_degrees_per_second = 90.0
    )");

    EXPECT_THROW(
        ConfigLoader::parseControls(data),
        std::runtime_error
    );
}

