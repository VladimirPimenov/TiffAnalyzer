#include "../../include/snapshotReader.h"

#include <iostream>

int findColumnByTime(QTime time, QStringList timeString)
{
    for(int column = 0; column < timeString.size(); column++)
    {
        QString columnTime = timeString[column];
        
        if(time == QTime::fromString(columnTime))
            return column;
    }
    return 0;
}

void parseString(QString inputString, QString * tag, QStringList * values, QString separator)
{
    int splitIndex = inputString.indexOf(QRegExp(separator));
    
    QString valuesString = inputString.mid(splitIndex + 1);
    *values = valuesString.split(QRegExp("\\s+"), Qt::SkipEmptyParts);
    
    *tag = inputString.mid(0, splitIndex);
}

void SnapshotReader::readSnapshotInfoFromFile(QString filePath, QTime time, std::map<QString, QString> & parameters, std::array<double, 211> & data)
{
    QFile * infoFile = new QFile(filePath);
    infoFile->open(QFile::ReadOnly);
    
    if(infoFile->isOpen())
    {
        QTextStream fileStream(infoFile);
        QString line;
        
        QString rowHeader;
        QStringList values;
        int column = -1;
        
        int dataRow = 0;
        
        while(!fileStream.atEnd())
        {
            line = fileStream.readLine();

            if(line.size() == 0)
                continue;

            if(line.contains(':'))
            {
                parseString(line, &rowHeader, &values, ":");

                if(rowHeader == "UTC")
                    column = findColumnByTime(time, values);
                
                if(column != -1)
                    parameters[rowHeader] = values[column];
            }
            else
            {
                parseString(line, &rowHeader, &values, "\\s+");

                data[dataRow] = values[column].toDouble();
                dataRow++;

                if(rowHeader.toInt() == 2500)
                    break;            
            }
        }
    
        infoFile->close();
    }
}