#pragma once

#include <QNetworkReply>

class HttpResponse
{
public:
    QNetworkReply * content;
    
    int httpStatus;
};