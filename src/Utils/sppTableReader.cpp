#include "../../include/sppTableReader.h"

void SppTableReader::readSppData(QString filePath, std::map<unsigned, std::map<QString, double>> & sppData)
{
    QFile * spp = new QFile(filePath);
    spp->open(QFile::ReadOnly);
    
    if(spp->isOpen())
    {
        QXmlStreamReader * xmlReader = new QXmlStreamReader(spp);
        xmlReader->readNext();
        
        std::map<QString, double> block;
        unsigned channelNum = 0;
        
        while(!xmlReader->atEnd())
        {
            QString tagName = xmlReader->name().toString();
            
            if(tagName == "WaveLength")
            {
                block.clear();
                
                while(xmlReader->readNextStartElement())
                {
                    if(xmlReader->name() == "ChannelNumber")
                        channelNum = xmlReader->readElementText().toUInt();
                    else
                        block[xmlReader->name().toString()] = xmlReader->readElementText().toDouble();
                }
                sppData[channelNum] = block;
            }
            xmlReader->readNext();
        }
        spp->close();
    }
}