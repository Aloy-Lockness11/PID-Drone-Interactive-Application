
#include "config/ConfigLoader.hpp"

#include <toml++/toml.hpp>
#include <stdexcept>
#include <cmath>

ControlsConfig ConfigLoader::loadControls(
    const std::string& filePath)
{
    // Parse the TOML configuration file
    auto data = toml::parse_file(filePath);

    // Read the manual controls section
    auto manual = data["manual"];

    auto horizontalForce =
        manual["horizontal_force_newtons"].value<double>();

    auto verticalSpeed =
        manual["vertical_speed_metres_per_second"].value<double>();

    auto pitchSpeed =
        manual["pitch_speed_degrees_per_second"].value<double>();

    // Validate horizontal force
    if (!horizontalForce || !std::isfinite(*horizontalForce) ||
        *horizontalForce < 0.0)
    {
        throw std::runtime_error(
            "horizontal_force_newtons must be non-negative and finite"
        );
    }

    // Validate vertical speed
    if (!verticalSpeed || !std::isfinite(*verticalSpeed) ||
        *verticalSpeed < 0.0)
    {
        throw std::runtime_error(
            "vertical_speed_metres_per_second must be non-negative and finite"
        );
    }

    // Validate pitch speed
    if (!pitchSpeed || !std::isfinite(*pitchSpeed) ||
        *pitchSpeed < 0.0)
    {
        throw std::runtime_error(
            "pitch_speed_degrees_per_second must be non-negative and finite"
        );
    }

    return ControlsConfig{
        static_cast<float>(*horizontalForce),
        static_cast<float>(*verticalSpeed),
        static_cast<float>(*pitchSpeed)
    };
}
