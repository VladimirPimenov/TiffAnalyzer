#pragma once

#include <array>

#ifdef POLYGONCHECKER_EXPORTS
    #define POLYGONCHECKER_EXPORT __declspec(dllexport)
#else
    #define POLYGONCHECKER_EXPORT __declspec(dllimport)
#endif

class POLYGONCHECKER_EXPORT PolygonChecker
{
public:
    static bool isPointInPolygon(double x, double y, std::array<double, 4> polygonX, std::array<double, 4> polygonY);
    
    static bool isRectangleIntersectPolygon(std::array<double, 4> rectX, std::array<double, 4> rectY, std::array<double, 4> polygonX, std::array<double, 4> polygonY);
};