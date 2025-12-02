#include "../../include/directoryReader.h"

QStringList * DirectoryReader::findFilesInDirectory(QString directoryPath, QString fileFilter)
{
    QStringList * files = new QStringList();
    
    QDirIterator it(directoryPath, QStringList(fileFilter), QDir::Files, QDirIterator::Subdirectories);
    
    while(it.hasNext())
    {
        it.next();
        files->append(it.filePath());
    }
    
    return files;
}