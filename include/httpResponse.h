#pragma once

#include <QNetworkReply>
#include <QString>

class HttpResponse
{
public:
    QNetworkReply * content;
    
    QString url;
    
    int httpStatus;
};