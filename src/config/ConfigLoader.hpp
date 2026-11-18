#pragma once

#include <string>

#include "config/SimulationTimingConfig.hpp"
#include "config/ControlsConfig.hpp"

class ConfigLoader
{
public:
    static SimulationTimingConfig loadSimulation(
        const std::string& filePath
    );

    static ControlsConfig loadControls(
        const std::string& filePath
    );
};
