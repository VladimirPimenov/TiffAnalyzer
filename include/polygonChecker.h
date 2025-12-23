#pragma once

#include <array>

class PolygonChecker
{
public:
    static bool isPointInPolygon(double x, double y, std::array<double, 4> polygonX, std::array<double, 4> polygonY);
    
    static bool isRectangleIntersectPolygon(std::array<double, 4> rectX, std::array<double, 4> rectY, std::array<double, 4> polygonX, std::array<double, 4> polygonY);
};