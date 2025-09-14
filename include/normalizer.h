#pragma once

#include <cstdint>

class Normalizer
{
public:
    static int minMaxNormalization(uint16_t x, uint16_t minX, uint16_t maxX, uint16_t a, uint16_t b);
};