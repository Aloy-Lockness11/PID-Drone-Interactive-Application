
#pragma once

#include <string>
#include <toml++/toml.hpp>

#include "config/SimulationTimingConfig.hpp"
#include "config/ControlsConfig.hpp"
#include "config/RenderingConfig.hpp"

class ConfigLoader
{
public:
    static SimulationTimingConfig loadSimulation(
        const std::string& filePath
    );

    // CONTROLS CONFIG

    // Load the controls configuration from a TOML file.
    static ControlsConfig loadControls(
        const std::string& filePath
    );

    // Parse and validate the controls configuration from the TOML data.
    static ControlsConfig parseControls(
        const toml::table& data
    );

    // RENDERING CONFIG

    // Load the rendering configuration from a TOML file.
    static RenderingConfig loadRendering(
        const std::string& filePath
    );

    // Parse and validate the rendering configuration from the TOML data.
    static RenderingConfig parseRendering(
        const toml::table& data
    );


};
