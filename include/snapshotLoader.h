#pragma once

#include <QString>
#include <QDateTime>
#include <QDate>

#include <QFile>
#include <QDir>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <functional>

#include "httpRequest.h"
#include "httpResponse.h"
#include "httpClient.h"

#include "logger.h"

class SnapshotLoader
{
public:
    SnapshotLoader();

    void loadSnapshotByDatetime(QDateTime dateTime);
    
    void setAuthentification(QString login, QString password);
    
    void setCallMessageHandler(std::function<void(QString)> eventHandler);
    
private:
    const QString radCalNetUrl = "https://www.radcalnet.org/api/json/LCFR/data/";
    const QString dateFormat = "ddd, dd MMM yyyy hh:mm:ss 'GMT'";
    const QString savePath = "./siteData/";

    QString login;
    QString password;
    QDateTime requestedDateTime;
    
    HttpClient * httpClient;
    HttpResponse * httpResponse;

    void findNearDateShapshot();
    void loadAndSaveSnapshotData(QString snapshotName);
    void saveSnapshot();
    
    std::function<void(QString)> callMessageEventHandler;
};