#pragma once

#include <QString>
#include <QStringList>
#include <QDateTime>

#include <QDebug>

#include <array>

#include "polygonChecker.h"
#include "spp.h"

#ifdef ROUTEFINDER_EXPORTS
    #define ROUTEFINDER_EXPORT __declspec(dllexport)
#else
    #define ROUTEFINDER_EXPORT __declspec(dllimport)
#endif

class ROUTEFINDER_EXPORT RouteFinder
{
public:
    static QStringList * findRoutesByCoordsAndData(double x, double y, QDateTime startDate, QDateTime endDate, QStringList * sppList);
    static QStringList * findRoutesByCoordsAndData(double x1, double y1, double x2, double y2, QDateTime startDate, QDateTime endDate, QStringList * sppList);
    static QStringList * findRoutesByCoordsAndData(std::array<double, 4> x, std::array<double, 4> y, QDateTime startDate, QDateTime endDate, QStringList * sppList);
};