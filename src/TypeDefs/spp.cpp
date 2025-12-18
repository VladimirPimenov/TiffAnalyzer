#include "../../include/spp.h"

void parseStringToArray(QString string, std::array<double, 4> & array)
{
    QStringList nums = string.split(',');
    
    for(unsigned i = 0; i < array.size(); i++)
    {
        array[i] = nums[i].toDouble();
    }
}

Spp::Spp(QString loadPath)
{
    loadSpp(loadPath);
}

void Spp::loadSpp(QString loadPath)
{
    QFile * spp = new QFile(loadPath);
    spp->open(QFile::ReadOnly);
    
    if(spp->isOpen())
    {
        QXmlStreamReader * xmlReader = new QXmlStreamReader(spp);
        xmlReader->readNext();
        
        while(!xmlReader->atEnd())
        {
            if(xmlReader->name() == "dDateAcquired")
            {
                dateAcquired = QDateTime::fromString(xmlReader->readElementText(), "yyyy-MM-ddTHH:mm:sszzz");
            }
            if(xmlReader->name() == "PointLatArr")
            {
                parseStringToArray(xmlReader->readElementText(), latitudes);
            }
            if(xmlReader->name() == "PointLonArr")
            {
                parseStringToArray(xmlReader->readElementText(), longitudes);
            }
            
            xmlReader->readNext();
        }
        spp->close();
    }
}