
#pragma once

struct SimulationConfig
{
    // Rendering scale
    float pixelsPerMetre = 100.0f;

    // Screen position of the simulation origin
    float screenOriginX = 500.0f;
    float screenOriginY = 300.0f;

    // Convert world coordinates into screen coordinates
    float toScreenX(float metres) const
    {
        return screenOriginX + metres * pixelsPerMetre;
    }

    float toScreenY(float metres) const
    {
        return screenOriginY + metres * pixelsPerMetre;
    }
};
