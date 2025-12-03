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
            filteredSppList->append(sppPath);
    }

    return filteredSppList;
}

 QStringList * RouteFinder::findRoutesByCoordsAndData(double x1, double y1, double x2, double y2, QDateTime startDate, QDateTime endDate, QStringList * sppList)
{
    QStringList * filteredSppList = new QStringList();
    
    for(QString sppPath : *sppList)
    {
        Spp spp = Spp(sppPath);
        
        bool isRectangleInside = isPointInPolygon(x1, y1, spp.longitudes, spp.latitudes)
            && isPointInPolygon(x1, y2, spp.longitudes, spp.latitudes)
            && isPointInPolygon(x2, y2, spp.longitudes, spp.latitudes)
            && isPointInPolygon(x2, y1, spp.longitudes, spp.latitudes);
            
        if(isRectangleInside && spp.dateAcquired >= startDate && spp.dateAcquired <= endDate)
            filteredSppList->append(sppPath);
    }

    return filteredSppList;
}