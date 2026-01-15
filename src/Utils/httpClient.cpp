#include "../../include/httpClient.h"
#include <iostream>
HttpClient::HttpClient()
{
    httpManager = new QNetworkAccessManager();
    
    connect(httpManager, &QNetworkAccessManager::finished, this, &HttpClient::onResult);
    connect(httpManager, &QNetworkAccessManager::authenticationRequired, this, &HttpClient::onAuthentificationRequired);
}

void HttpClient::get(HttpRequest * request, HttpResponse * response)
{
    this->request = request;
    QNetworkRequest r = QNetworkRequest(request->requestUrl);

    this->response = response;
    
    qInfo().noquote() << "Отправлен HTTP GET запрос по адресу " + request->requestUrl;
    
    httpManager->get(r);
}

void HttpClient::onResult(QNetworkReply *reply)
{
    response->httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    response->content = reply;
    response->url = reply->url().toString();
    
    qInfo().noquote() << "Получен ответ на запрос. HTTP код: " + reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
    
    responseReceivedEventHandler();
}

void HttpClient::onAuthentificationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    authenticator->setUser(request->login);
    authenticator->setPassword(request->password);
}

void HttpClient::setReceivedEvent(std::function<void()> eventHandler)
{
    responseReceivedEventHandler = eventHandler;
}