#pragma once

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>

#include "httpRequest.h"
#include "httpResponse.h"

#include <functional>

#ifdef HTTPCLIENT_LIB
#define HTTPCLIENT_EXPORT __declspec(dllexport)
#else
#define HTTPCLIENT_EXPORT __declspec(dllimport)
#endif

class HTTPCLIENT_EXPORT HttpClient: public QObject
{
public:
    HttpClient(QNetworkAccessManager * httpManager);
    
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