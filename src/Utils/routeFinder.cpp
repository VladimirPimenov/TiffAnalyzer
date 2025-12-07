#include "../../include/routeFinder.h"

bool isPointInPolygon(double x, double y, std::array<double, 4> & polygonX, std::array<double, 4> & polygonY)
{
    bool isInside = false;
    int j = 3;

    for (int i = 0; i < 4; i++) 
    {
        if((polygonY[i] > y) != (polygonY[j] > y)
        && (x < (polygonX[j] - polygonX[i]) * (y - polygonY[i]) / 
            (polygonY[j] - polygonY[i]) + polygonX[i])
        ) 
            isInside = !isInside;
            
        j = i;
    }
    
    return isInside;
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