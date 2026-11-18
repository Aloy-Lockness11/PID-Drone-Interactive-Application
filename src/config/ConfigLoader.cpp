
#include "config/ConfigLoader.hpp"

#include <toml++/toml.hpp>
#include <limits>
#include <stdexcept>
#include <cmath>


ControlsConfig ConfigLoader::loadControls(
    const std::string& filePath)
{
    // Step 1: Read and parse the TOML file.
    auto data = toml::parse_file(filePath);

    // Step 2: Extract and validate its contents.
    return parseControls(data);
}

// Parse and validate the controls configuration from the TOML data.
ControlsConfig ConfigLoader::parseControls(
    const toml::table& data)
{
    auto manual = data["manual"];

    auto horizontalForce =
        manual["horizontal_force_newtons"].value<double>();

    auto verticalSpeed =
        manual["vertical_speed_metres_per_second"].value<double>();

    auto pitchSpeed =
        manual["pitch_speed_degrees_per_second"].value<double>();


    if (!horizontalForce || !std::isfinite(*horizontalForce) ||
        *horizontalForce < 0.0 ||
        *horizontalForce > std::numeric_limits<float>::max())
    {
        throw std::runtime_error(
            "Invalid horizontal_force_newtons"
        );
    }

    // Validate vertical speed
    if (!verticalSpeed || !std::isfinite(*verticalSpeed) ||
        *verticalSpeed < 0.0 ||
        *verticalSpeed > std::numeric_limits<float>::max())
    {
        throw std::runtime_error(
            "Invalid vertical_speed_metres_per_second"
        );
    }

    // Validate pitch speed
    if (!pitchSpeed || !std::isfinite(*pitchSpeed) ||
        *pitchSpeed < 0.0 ||
        *pitchSpeed > std::numeric_limits<float>::max())
    {
        throw std::runtime_error(
            "Invalid pitch_speed_degrees_per_second"
        );
    }

    return ControlsConfig{
        static_cast<float>(*horizontalForce),
        static_cast<float>(*verticalSpeed),
        static_cast<float>(*pitchSpeed)
    };
}

