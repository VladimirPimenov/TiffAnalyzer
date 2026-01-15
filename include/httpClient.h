#pragma once

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>

#include "httpRequest.h"
#include "httpResponse.h"

#include <functional>

#include "logger.h"

class HttpClient: public QObject
{
public:
    HttpClient();
    
    void get(HttpRequest * request, HttpResponse * response);
    
    void setReceivedEvent(std::function<void()> eventHandler);
    
private:
    QNetworkAccessManager * httpManager;
    
    HttpRequest * request;
    HttpResponse * response;
    
    void onResult(QNetworkReply *reply);
    void onAuthentificationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    
    std::function<void()> responseReceivedEventHandler;
};