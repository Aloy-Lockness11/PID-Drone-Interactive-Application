
#pragma once

#include <string>
#include "config/SimulationTimingConfig.hpp"

class ConfigLoader
{
public:
    static SimulationTimingConfig loadSimulation(
        const std::string& filePath
    );
};
