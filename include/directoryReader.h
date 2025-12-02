#pragma once

#include <filesystem>

#include <QDir>
#include <QDirIterator>

#include <QString>
#include <QStringList>

class DirectoryReader
{
public:
    static QStringList * findFilesInDirectory(QString directoryPath, QString fileFilter);
};