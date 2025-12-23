#include "../../include/routeFinder.h"

QStringList * RouteFinder::findRoutesByCoordsAndData(double x, double y, QDateTime startDate, QDateTime endDate, QStringList * sppList)
{
    QStringList * filteredSppList = new QStringList();

    for(QString sppPath : *sppList)
    {
        Spp spp = Spp(sppPath);

        bool isPointInside = PolygonChecker::isPointInPolygon(x, y, spp.longitudes, spp.latitudes);

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

QStringList * RouteFinder::findRoutesByCoordsAndData(std::array<double, 4> x, std::array<double, 4> y, QDateTime startDate, QDateTime endDate, QStringList * sppList)
{
    QStringList * filteredSppList = new QStringList();
    
    for(QString sppPath : *sppList)
    {
        Spp spp = Spp(sppPath);
        
        bool hasIntersect = false;

        for (int i = 0; i < 4; ++i) 
        {
            if (PolygonChecker::isPointInPolygon(spp.longitudes[i], spp.latitudes[i], x, y)) 
            {
                hasIntersect = true;
                break;
            }
        }

        if (!hasIntersect) 
        {
            for (int i = 0; i < 4; ++i) 
            {
                if (PolygonChecker::isPointInPolygon(x[i], y[i], spp.longitudes, spp.latitudes)) 
                {
                    hasIntersect = true;
                    break;
                }
            }
        }
        
        if (!hasIntersect) 
            hasIntersect = PolygonChecker::isRectangleIntersectPolygon(x, y, spp.longitudes, spp.latitudes);
            
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

 QStringList * RouteFinder::findRoutesByCoordsAndData(double x1, double y1, double x2, double y2, QDateTime startDate, QDateTime endDate, QStringList * sppList)
{
    std::array<double, 4> rectX = {x1, x1, x2, x2};
    std::array<double, 4> rectY = {y1, y2, y2, y1};
    
    return findRoutesByCoordsAndData(rectX, rectY, startDate, endDate, sppList);
}