
#include "engine/config/PhysicsConfigLoader.hpp"

#include <cmath>
#include <limits>
#include <stdexcept>

// Load and merge physics configuration from TOML files
PhysicsConfig PhysicsConfigLoader::load(
    const std::string& defaultPath,
    const std::string& overridePath)
{
    // Always load the engine defaults
    auto defaults = toml::parse_file(defaultPath);

    // No custom configuration requested
    if (overridePath.empty())
    {
        return parse(defaults);
    }

    // Load the application's custom settings
    auto overrides = toml::parse_file(overridePath);

    // Combine defaults and overrides
    return parse(defaults, &overrides);
}

// Parse and merge already-loaded TOML data

PhysicsConfig PhysicsConfigLoader::parse(
    const toml::table& defaults,
    const toml::table* overrides)
{
    // Read required engine defaults
    auto gravity =
        defaults["world"]["gravity"].value<double>();

    auto damping =
        defaults["physics"]["linear_damping"].value<double>();

    // Every engine default must exist and have the correct type
    if (!gravity || !damping)
    {
        throw std::runtime_error(
            "Missing or invalid default physics settings"
        );
    }

    // Apply optional application overrides
    if (overrides != nullptr)
    {
        auto customGravity = (*overrides)["world"]["gravity"];
        auto customDamping = (*overrides)["physics"]["linear_damping"];

        // Override only if the key exists
        if (customGravity)
        {
            auto value = customGravity.value<double>();

            if (!value)
            {
                throw std::runtime_error(
                    "Invalid gravity override"
                );
            }

            gravity = value;
        }

        if (customDamping)
        {
            auto value = customDamping.value<double>();

            if (!value)
            {
                throw std::runtime_error(
                    "Invalid linear_damping override"
                );
            }

            damping = value;
        }
    }

    // Validate the final merged values
    if (!std::isfinite(*gravity) ||
        std::abs(*gravity) > std::numeric_limits<float>::max())
    {
        throw std::runtime_error(
            "Gravity must be finite and within float range"
        );
    }

    if (!std::isfinite(*damping) ||
        *damping < 0.0 ||
        *damping > std::numeric_limits<float>::max())
    {
        throw std::runtime_error(
            "Linear damping must be non-negative and finite"
        );
    }

    return PhysicsConfig{
        static_cast<float>(*gravity),
        static_cast<float>(*damping)
    };
}
