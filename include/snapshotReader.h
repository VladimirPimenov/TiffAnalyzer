#pragma once

#include <QString>
#include <QStringList>
#include <QTime>

#include <QFile>
#include <QTextStream>

#include <map>
#include <array>

class SnapshotReader
{
public:
    static void readSnapshotInfoFromFile(QString filePath, QTime time, std::map<QString, QString> & parameters, std::array<double, 211> & reflectance);
};