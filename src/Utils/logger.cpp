#include "../../include/logger.h"

void Logger::loggingMesssageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile * logFile = getLogFile();

    QTextStream out(logFile);
	
	logFile->open(QFile::Append | QFile::Text);
	
    out << QDateTime::currentDateTime().toString("dd-mm-yyyy hh:mm:ss ");
    
	switch(type)
	{
	    case QtInfoMsg:
            out << "[INF] ";
            break;
        case QtWarningMsg:
            out << "[WAR] ";
            break;
        case QtDebugMsg:
            out << "[DEB] ";
            break;
        default:
            out << "[ERR] ";
            break;
	}
	
    out << msg << Qt::endl;
    
    logFile->close();
}
