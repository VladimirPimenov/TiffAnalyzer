#include "../../include/kml.h"

Kml::Kml(QString loadPath)
{
    loadKml(loadPath);
}

void Kml::loadKml(QString loadPath)
{
    QFile * kml = new QFile(loadPath);
    kml->open(QFile::ReadOnly);
    
    if(kml->isOpen())
    {
        QXmlStreamReader * xmlReader = new QXmlStreamReader(kml);
        xmlReader->readNext();
        
        while(!xmlReader->atEnd())
        {
            if(xmlReader->name() == "coordinates")
            {
                parseStringToCoordinates(xmlReader->readElementText());
            }
            
            xmlReader->readNext();
        }
        kml->close();
    }
}

void Kml::parseStringToCoordinates(QString string)
{
    QStringList coords = string.split(' ');
    QStringList nums;
    
    for(unsigned i = 0; i < coords.size() - 2; i++)
    {
        nums = coords[i].split(',');
        
        longitudes[3 - i] = nums[0].toDouble();
        latitudes[3 - i] = nums[1].toDouble();
    }
    std::swap(longitudes[2], longitudes[3]);
    std::swap(latitudes[2], latitudes[3]);
}