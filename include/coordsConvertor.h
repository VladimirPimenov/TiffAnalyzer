#pragma once

#include <QString>
#include <cmath>

class CoordsConvertor
{
public: 
    static QString convertDdToKml(QString ddString);
    static QString convertDdmmssToKml(QString ddmmssString);
    
private:
    static QString convertDdmmssToDd(QString ddmmssString);
};