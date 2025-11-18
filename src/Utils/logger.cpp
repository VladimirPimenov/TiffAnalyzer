#include "../../include/logger.h"

void Logger::loggingMesssageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QFile * logFile = getLogFile();

    QTextStream out(logFile);
	
	logFile->open(QFile::Append | QFile::Text);
	
    out << QDateTime::currentDateTime().toString("dd-mm-yyyy hh:mm:ss ");
    out << msg << Qt::endl;
    
    logFile->close();
}
