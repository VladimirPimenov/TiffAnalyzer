#include "../../include/routeFinder.h"

bool isPointInPolygon(double x, double y, std::array<double, 4> & polygonX, std::array<double, 4> & polygonY)
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

QStringList * RouteFinder::findRoutesByCoordsAndData(double x, double y, QDateTime startDate, QDateTime endDate, QStringList * sppList)
{
    QStringList * filteredSppList = new QStringList();

    for(QString sppPath : *sppList)
    {
        Spp spp = Spp(sppPath);

        bool isPointInside = isPointInPolygon(x, y, spp.longitudes, spp.latitudes);

        if(isPointInside && spp.dateAcquired >= startDate && spp.dateAcquired <= endDate)
        {
            filteredSppList->append(sppPath);
            
            qInfo().noquote() << "Найден маршрут" << sppPath;
        }
    }

    if(filteredSppList->empty())
        qInfo().noquote() << "Маршруты не найдены";

    return filteredSppList;
}

 QStringList * RouteFinder::findRoutesByCoordsAndData(double x1, double y1, double x2, double y2, QDateTime startDate, QDateTime endDate, QStringList * sppList)
{
    QStringList * filteredSppList = new QStringList();

    std::array<double, 4> rectX = {x1, x1, x2, x2};
    std::array<double, 4> rectY = {y1, y2, y2, y1};
    
    for(QString sppPath : *sppList)
    {
        Spp spp = Spp(sppPath);
        
        bool hasIntersect = false;

        for (int i = 0; i < 4; ++i) 
        {
            if (isPointInPolygon(spp.longitudes[i], spp.latitudes[i], rectX, rectY)) 
            {
                hasIntersect = true;
                break;
            }
        }

        if (!hasIntersect) 
        {
            for (int i = 0; i < 4; ++i) 
            {
                if (isPointInPolygon(rectX[i], rectY[i], spp.longitudes, spp.latitudes)) 
                {
                    hasIntersect = true;
                    break;
                }
            }
        }

        if (!hasIntersect) 
        {
            for (int i = 0; i < 4; ++i) 
            {
                double polygon1x = spp.longitudes[i];
                double polygon1y = spp.latitudes[i];
                double polygon2x = spp.longitudes[(i + 1) % 4];
                double polygon2y = spp.latitudes[(i + 1) % 4];

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
        }
            
        if(hasIntersect && spp.dateAcquired >= startDate && spp.dateAcquired <= endDate)
        {
            filteredSppList->append(sppPath);
            
            qInfo().noquote() << "Найден маршрут" << sppPath;
        }
    }
    
    if(filteredSppList->empty())
        qInfo().noquote() << "Маршруты не найдены";

    return filteredSppList;
}