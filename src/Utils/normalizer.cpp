#include "../../include/normalizer.h"

int Normalizer::minMaxNormalization(uint16_t x, uint16_t minX, uint16_t maxX, uint16_t a, uint16_t b)
{
    /* 
    Формула minMax-нормализации в диапазоне [a; b]:
    x' = (x - min(x)) * (b - a) / (max(x) - min(x)) + a
    */
    int normalized = (b - a) * ((x - minX) / (double)(maxX - minX)) + a;
    
    return normalized;
}