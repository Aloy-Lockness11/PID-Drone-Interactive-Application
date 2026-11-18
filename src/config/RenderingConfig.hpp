#pragma once

struct RenderingConfig
{
    // Pixels representing one metre
    float pixelsPerMetre = 100.0f;

    // Screen origin in pixels
    float screenOriginX = 500.0f;
    float screenOriginY = 300.0f;

    // World metres to screen pixels
    float toScreenX(float metres) const
    {
        return screenOriginX + metres * pixelsPerMetre;
    }

    float toScreenY(float metres) const
    {
        return screenOriginY + metres * pixelsPerMetre;
    }
};
