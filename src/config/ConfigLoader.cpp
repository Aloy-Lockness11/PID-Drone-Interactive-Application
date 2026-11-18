
#include "config/ConfigLoader.hpp"

#include <toml++/toml.hpp>
#include <stdexcept>
#include <cstdint>

SimulationTimingConfig ConfigLoader::loadSimulation(
    const std::string& filePath)
{
    // Read the TOML file
    auto data = toml::parse_file(filePath);

    // Find the simulation section
    auto simulation = data["simulation"];

    // Read required values
    auto hz = simulation["physics_update_hz"].value<int64_t>();

    auto maxTime =
        simulation["max_frame_time_seconds"].value<double>();

    // Validate required settings and types
    if (!hz || *hz <= 0 || *hz > 1000)
    {
        throw std::runtime_error(
            "physics_update_hz must be between 1 and 1000"
        );
    }

    if (!maxTime || !(*maxTime > 0.0) ||
        !(*maxTime <= 1.0))
    {
        throw std::runtime_error(
            "max_frame_time_seconds must be greater than 0 and at most 1"
        );
    }

    // Return a validated configuration
    return SimulationTimingConfig{
        static_cast<int>(*hz),
        *maxTime
    };
}
