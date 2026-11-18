
#pragma once

struct RenderingConfig
{
    unsigned int windowWidth = 1000;
    unsigned int windowHeight = 600;
    unsigned int fpsLimit = 60;

    float pixelsPerMetre = 100.f;
    float screenOriginX = 500.f;
    float screenOriginY = 300.f;

    float toScreenX(float metres) const
    {
        return screenOriginX + metres * pixelsPerMetre;
    }

    float toScreenY(float metres) const
    {
        return screenOriginY + metres * pixelsPerMetre;
    }
};
