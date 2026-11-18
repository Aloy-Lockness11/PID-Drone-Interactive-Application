
#include <gtest/gtest.h>
#include <stdexcept>
#include <toml++/toml.hpp>
#include <filesystem>

#include "config/ConfigLoader.hpp"

// Integration test: read the actual TOML file
TEST(RenderingConfigLoaderTest, LoadsValidRenderingConfig)
{
    const auto path = std::filesystem::path(TEST_PROJECT_ROOT) /
                  "settings/rendering.toml";

    RenderingConfig config = ConfigLoader::loadRendering(path.string());

    EXPECT_EQ(config.windowWidth, 1000u);
    EXPECT_EQ(config.windowHeight, 600u);
    EXPECT_EQ(config.fpsLimit, 60u);

    EXPECT_FLOAT_EQ(config.pixelsPerMetre, 100.0f);
    EXPECT_FLOAT_EQ(config.screenOriginX, 500.0f);
    EXPECT_FLOAT_EQ(config.screenOriginY, 300.0f);
}
 

// Test: Reject zero window width
TEST(RenderingConfigLoaderTest, RejectsZeroWindowWidth)
{
    auto data = toml::parse(R"(
        [window]
        width = 0
        height = 600
        fps_limit = 60

        [camera]
        pixels_per_metre = 100.0
        origin_x = 500.0
        origin_y = 300.0
    )");

    EXPECT_THROW(
        ConfigLoader::parseRendering(data),
        std::runtime_error
    );
}

// Test: Reject zero window height
TEST(RenderingConfigLoaderTest, RejectsZeroWindowHeight)
{
    auto data = toml::parse(R"(
        [window]
        width = 1000
        height = 0
        fps_limit = 60

        [camera]
        pixels_per_metre = 100.0
        origin_x = 500.0
        origin_y = 300.0
    )");

    EXPECT_THROW(
        ConfigLoader::parseRendering(data),
        std::runtime_error
    );
}

// Test: Reject zero FPS limit
TEST(RenderingConfigLoaderTest, RejectsZeroFpsLimit)
{
    auto data = toml::parse(R"(
        [window]
        width = 1000
        height = 600
        fps_limit = 0

        [camera]
        pixels_per_metre = 100.0
        origin_x = 500.0
        origin_y = 300.0
    )");

    EXPECT_THROW(
        ConfigLoader::parseRendering(data),
        std::runtime_error
    );
}

// Test: Reject zero pixels per metre
TEST(RenderingConfigLoaderTest, RejectsZeroPixelsPerMetre)
{
    auto data = toml::parse(R"(
        [window]
        width = 1000
        height = 600
        fps_limit = 60

        [camera]
        pixels_per_metre = 0.0
        origin_x = 500.0
        origin_y = 300.0
    )");

    EXPECT_THROW(
        ConfigLoader::parseRendering(data),
        std::runtime_error
    );
}

// Test: Reject negative window width
TEST(RenderingConfigLoaderTest, RejectsNegativeWindowWidth)
{
    auto data = toml::parse(R"(
        [window]
        width = -1000
        height = 600
        fps_limit = 60

        [camera]
        pixels_per_metre = 100.0
        origin_x = 500.0
        origin_y = 300.0
    )");

    EXPECT_THROW(
        ConfigLoader::parseRendering(data),
        std::runtime_error
    );
}

// Test: Reject negative window height
TEST(RenderingConfigLoaderTest, RejectsNegativeWindowHeight)
{
    auto data = toml::parse(R"(
        [window]
        width = 1000
        height = -600
        fps_limit = 60

        [camera]
        pixels_per_metre = 100.0
        origin_x = 500.0
        origin_y = 300.0
    )");

    EXPECT_THROW(
        ConfigLoader::parseRendering(data),
        std::runtime_error
    );
}

// Test: Reject negative FPS limit
TEST(RenderingConfigLoaderTest, RejectsNegativeFPSLimit)
{
    auto data = toml::parse(R"(
        [window]
        width = 1000
        height = 600
        fps_limit = -60

        [camera]
        pixels_per_metre = 100.0
        origin_x = 500.0
        origin_y = 300.0
    )");

    EXPECT_THROW(
        ConfigLoader::parseRendering(data),
        std::runtime_error
    );
}



