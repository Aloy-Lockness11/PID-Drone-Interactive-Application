#include <gtest/gtest.h>
#include <stdexcept>
#include <toml++/toml.hpp>
#include <filesystem>

#include "engine/config/PhysicsConfigLoader.hpp"

//Test loading the default physics configuration

TEST(PhysicsConfigLoaderTest, LoadsEngineDefaults)
{
    const auto path = std::filesystem::path(TEST_PROJECT_ROOT) /
                  "src/engine/config/default_physics.toml";

    PhysicsConfig config = PhysicsConfigLoader::load(path.string());

    EXPECT_FLOAT_EQ(config.gravity, 9.81f);
    EXPECT_FLOAT_EQ(config.linearDamping, 0.3f);
}

//Testing Override rules in memory
//Testing for damping only as is the same for other overrides
TEST(PhysicsConfigLoaderTest, OverridesDampingOnly)
{
    auto defaults = toml::parse(R"(
        [world]
        gravity = 9.81

        [physics]
        linear_damping = 0.3
    )");

    auto overrides = toml::parse(R"(
        [physics]
        linear_damping = 0.5
    )");

    PhysicsConfig config =
        PhysicsConfigLoader::parse(defaults, &overrides);

    // Unspecified gravity is inherited
    EXPECT_FLOAT_EQ(config.gravity, 9.81f);

    // Damping uses the custom value
    EXPECT_FLOAT_EQ(config.linearDamping, 0.5f);
}

//Testing for invalid overrides

// Rejects negative damping override
TEST(PhysicsConfigLoaderTest, RejectsNegativeDampingOverride)
{
    auto defaults = toml::parse(R"(
        [world]
        gravity = 9.81

        [physics]
        linear_damping = 0.3
    )");

    auto overrides = toml::parse(R"(
        [physics]
        linear_damping = -0.5
    )");

    EXPECT_THROW(
        PhysicsConfigLoader::parse(defaults, &overrides),
        std::runtime_error
    );
}

// Tests for missing default gravity
// Should throw an error if gravity is not specified in the defaults
TEST(PhysicsConfigLoaderTest, RejectsMissingDefaultGravity)
{
    // Gravity is deliberately missing
    auto defaults = toml::parse(R"(
        [physics]
        linear_damping = 0.3
    )");

    EXPECT_THROW(
        PhysicsConfigLoader::parse(defaults),
        std::runtime_error
    );
}

//RejectsIncorrectOverrideType	"fast" cannot replace numeric damping
TEST(PhysicsConfigLoaderTest, RejectsIncorrectOverrideType)
{
    auto defaults = toml::parse(R"(
        [world]
        gravity = 9.81

        [physics]
        linear_damping = 0.3
    )");

    auto overrides = toml::parse(R"(
        [physics]
        linear_damping = "fast"
    )");

    EXPECT_THROW(
        PhysicsConfigLoader::parse(defaults, &overrides),
        std::runtime_error
    );
}

// Tests for missing override file
TEST(PhysicsConfigLoaderTest, RejectsMissingOverrideFile)
{
    auto defaults = toml::parse(R"(
        [world]
        gravity = 9.81

        [physics]
        linear_damping = 0.3
    )");

    const auto missingFilePath = std::filesystem::path(TEST_PROJECT_ROOT) /
                                 "nonexistent_override.toml";

    EXPECT_THROW(
        PhysicsConfigLoader::load(missingFilePath.string()),
        std::runtime_error
    );
}

// Tests for a specified but nonexistent file causing an error
TEST(PhysicsConfigLoaderTest, RejectsSpecifiedButNonexistentFile)
{
    const auto missingFilePath = std::filesystem::path(TEST_PROJECT_ROOT) /
                                 "nonexistent_override.toml";

    EXPECT_THROW(
        PhysicsConfigLoader::load(missingFilePath.string()),
        std::runtime_error
    );
}

// Tests for non-finite damping values
// RejectsNonFiniteDamping	NaN or infinity cannot enter physics calculations
TEST(PhysicsConfigLoaderTest, RejectsNonFiniteDamping)
{
    auto defaults = toml::parse(R"(
        [world]
        gravity = 9.81

        [physics]
        linear_damping = 0.3
    )");

    auto overrides = toml::parse(R"(
        [physics]
        linear_damping = "nan"
    )");

    EXPECT_THROW(
        PhysicsConfigLoader::parse(defaults, &overrides),
        std::runtime_error
    );
}

// Tests for out-of-range gravity values
// RejectsOutOfRangeGravity	Values too large for float are rejected
TEST(PhysicsConfigLoaderTest, RejectsOutOfRangeGravity)
{
    auto defaults = toml::parse(R"(
        [world]
        gravity = 9.81

        [physics]
        linear_damping = 0.3
    )");

    auto overrides = toml::parse(R"(
        [world]
        gravity = 1e40
    )");

    EXPECT_THROW(
        PhysicsConfigLoader::parse(defaults, &overrides),
        std::runtime_error
    );
}

