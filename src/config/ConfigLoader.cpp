
#include "config/ConfigLoader.hpp"

#include <toml++/toml.hpp>
#include <limits>
#include <stdexcept>
#include <cmath>

//CONTROLS CONFIG 

// Load the controls configuration from a TOML file.
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

//RENDERING CONFIG 

// Load the rendering configuration from a TOML file.
RenderingConfig ConfigLoader::loadRendering(
    const std::string& filePath)
{
    auto data = toml::parse_file(filePath);

    return parseRendering(data);
}

// Parse and validate the rendering configuration from the TOML data.
RenderingConfig ConfigLoader::parseRendering(
    const toml::table& data)
{
    auto window = data["window"];
    auto camera = data["camera"];

    auto width = window["width"].value<int64_t>();
    auto height = window["height"].value<int64_t>();
    auto fpsLimit = window["fps_limit"].value<int64_t>();

    auto pixelsPerMetre =
        camera["pixels_per_metre"].value<double>();

    auto originX = camera["origin_x"].value<double>();
    auto originY = camera["origin_y"].value<double>();

    // Validate window dimensions and frame-rate limit
    if (!width || *width <= 0 ||
        *width > std::numeric_limits<unsigned int>::max())
    {
        throw std::runtime_error("Invalid window width");
    }

    if (!height || *height <= 0 ||
        *height > std::numeric_limits<unsigned int>::max())
    {
        throw std::runtime_error("Invalid window height");
    }

    if (!fpsLimit || *fpsLimit <= 0 ||
        *fpsLimit > std::numeric_limits<unsigned int>::max())
    {
        throw std::runtime_error("Invalid FPS limit");
    }

    // Validate camera settings
    if (!pixelsPerMetre || !std::isfinite(*pixelsPerMetre) ||
        *pixelsPerMetre <= 0.0 ||
        *pixelsPerMetre > std::numeric_limits<float>::max())
    {
        throw std::runtime_error("Invalid pixels_per_metre");
    }

    if (!originX || !std::isfinite(*originX) ||
        std::abs(*originX) > std::numeric_limits<float>::max())
    {
        throw std::runtime_error("Invalid camera origin_x");
    }

    if (!originY || !std::isfinite(*originY) ||
        std::abs(*originY) > std::numeric_limits<float>::max())
    {
        throw std::runtime_error("Invalid camera origin_y");
    }

    return RenderingConfig{
        static_cast<unsigned int>(*width),
        static_cast<unsigned int>(*height),
        static_cast<unsigned int>(*fpsLimit),
        static_cast<float>(*pixelsPerMetre),
        static_cast<float>(*originX),
        static_cast<float>(*originY)
    };
}


