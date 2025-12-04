#include "../../include/coordsConvertor.h"

QString CoordsConvertor::convertDdmmssToKml(QString ddmmssString)
{
    QString ddString = convertDdmmssToDd(ddmmssString);
    return convertDdToKml(ddString);
}

QString CoordsConvertor::convertDdToKml(QString ddString)
{
    double dd = ddString.toDouble();
    
    int degrees = dd;
    
    if(degrees <= 0)
        degrees = 180 + degrees;
    
    double trash = 0.0;
    double fracPart = modf(dd, &trash);

    return QString::number(degrees + fracPart);
}

QString CoordsConvertor::convertDdmmssToDd(QString ddmmssString)
{
    double ddmmss = ddmmssString.toDouble();
    double degrees = std::trunc(ddmmss / 10000);
    double minutes = std::trunc(std::fmod(ddmmss, 10000) / 100);
    double seconds = std::fmod(ddmmss, 100);

    return QString::number(degrees + minutes / 60.0 + seconds / 3600.0);
}