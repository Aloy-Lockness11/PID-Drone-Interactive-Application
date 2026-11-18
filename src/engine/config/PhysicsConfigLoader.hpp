
#pragma once

#include <string>
#include <toml++/toml.hpp>
#include "engine/config/PhysicsConfig.hpp"

class PhysicsConfigLoader
{
public:
    // Load defaults and optional application overrides
    static PhysicsConfig load(
        const std::string& defaultPath,
        const std::string& overridePath = ""
    );

    // Parse and merge already-loaded TOML data
    static PhysicsConfig parse(
        const toml::table& defaults,
        const toml::table* overrides = nullptr
    );
};
