#pragma once

#include <QFile>
#include <QTextStream>
#include <QDateTime>

class Logger
{
public:
    static void loggingMesssageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    
private:
    static QFile * getLogFile() 
    {
        static QFile file("./log.txt");
        return &file;
    }
};