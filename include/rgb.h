#pragma once

#include <cstdint>

const unsigned MAX_PIXEL_8BIT_VALUE = 255;
const unsigned MAX_PIXEL_16BIT_VALUE = 65535;

struct RgbChannels 
{
    int red; 
    int green; 
    int blue;
};

struct Pixel16bit
{
    uint16_t red; 
    uint16_t green; 
    uint16_t blue;
};

struct Pixel8bit
{
    uint8_t red; 
    uint8_t green; 
    uint8_t blue;
};