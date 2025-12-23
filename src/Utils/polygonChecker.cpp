#include "../../include/polygonChecker.h"

int findPointPositionRelativeLine(double line1x, double line1y, 
                            double line2x, double line2y, 
                            double px, double py)
{
    double res = (line2y - line1y) * (px - line2x) - (line2x - line1x) * (py - line2y);

    if (res == 0) 
        return 0;

    return (res > 0) ? 1 : 2;
}


bool isPointInLine(double line1x, double line1y, double line2x, double line2y, double px, double py)
{
    if (px <= std::max(line1x, line2x) 
        && px >= std::min(line1x, line2x) 
        && py <= std::max(line1y, line2y)
        && py >= std::min(line1y, line2y))
        return true;

    return false;
}

bool isLinesIntersect(double p1x, double p1y, double p2x, double p2y,
                         double p3x, double p3y, double p4x, double p4y)
{
    int pos1 = findPointPositionRelativeLine(p1x, p1y, p2x, p2y, p3x, p3y);
    int pos2 = findPointPositionRelativeLine(p1x, p1y, p2x, p2y, p4x, p4y);
    int pos3 = findPointPositionRelativeLine(p3x, p3y, p4x, p4y, p1x, p1y);
    int pos4 = findPointPositionRelativeLine(p3x, p3y, p4x, p4y, p2x, p2y);

    if (pos1 != pos2 && pos3 != pos4)
        return true;

    if (isPointInLine(p1x, p1y, p2x, p2y, p3x, p3y)
        || isPointInLine(p1x, p1y, p2x, p2y, p4x, p4y)
        || isPointInLine(p3x, p3y, p4x, p4y, p1x, p1y)
        || isPointInLine(p3x, p3y, p4x, p4y, p2x, p2y)) 
        return true;

    return false;
}

bool PolygonChecker::isPointInPolygon(double x, double y, 
                                std::array<double, 4> polygonX, 
                                std::array<double, 4> polygonY)
{
    bool isInside = false;
    int j = 3;

    for (int i = 0; i < 4; i++) 
    {
        if((polygonY[i] > y) != (polygonY[j] > y)
        && (x < (polygonX[j] - polygonX[i]) * 
        (y - polygonY[i]) / (polygonY[j] - polygonY[i]) + polygonX[i])
        ) 
            isInside = !isInside;
            
        j = i;
    }
    
    return isInside;
}

bool PolygonChecker::isRectangleIntersectPolygon(std::array<double, 4> rectX, 
                                                std::array<double, 4> rectY, 
                                                std::array<double, 4> polygonX, 
                                                std::array<double, 4> polygonY)
{
    bool hasIntersect = false;
    
    for (int i = 0; i < 4; ++i) 
    {
        double polygon1x = polygonX[i];
        double polygon1y = polygonY[i];
        double polygon2x = polygonX[(i + 1) % 4];
        double polygon2y = polygonY[(i + 1) % 4];

        for (int j = 0; j < 4; ++j) 
        {
            double rect1x = rectX[j];
            double rect1y = rectY[j];
            double rect2x = rectX[(j + 1) % 4];
            double rect2y = rectY[(j + 1) % 4];

            if (isLinesIntersect(polygon1x, polygon1y, polygon2x, polygon2y,
                                rect1x, rect1y, rect2x, rect2y)) 
            {
                hasIntersect = true;
                break;
            }
        }
        if (hasIntersect) 
            break;
    }
    
    return hasIntersect;
}