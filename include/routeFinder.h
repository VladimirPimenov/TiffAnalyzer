#pragma once

#include <QString>
#include <QStringList>
#include <QDateTime>

#include <QDebug>

#include "spp.h"

class RouteFinder
{
public:
    static QStringList * findRoutesByCoordsAndData(double x, double y, QDateTime startDate, QDateTime endDate, QStringList * sppList);
    static QStringList * findRoutesByCoordsAndData(double x1, double y1, double x2, double y2, QDateTime startDate, QDateTime endDate, QStringList * sppList);
};