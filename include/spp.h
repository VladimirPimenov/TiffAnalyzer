#pragma once

#include <QString>
#include <QStringList>
#include <QDateTime>

#include <QFile>
#include <QXmlStreamReader>

#include <array>

class Spp
{
public:
    QDateTime dateAcquired;
    std::array<double, 4> latitudes;
    std::array<double, 4> longitudes;

    Spp(QString loadPath);

    void loadSpp(QString loadPath);
    
private:
    QString filePath;
};