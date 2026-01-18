#include "../../include/snapshotLoader.h"

SnapshotLoader::SnapshotLoader(HttpClient * httpClient)
{
    this->httpClient = httpClient;
}

void SnapshotLoader::loadSnapshotByDatetime(QDateTime dateTime)
{
    requestedDateTime = dateTime;

    HttpRequest * request = new HttpRequest();
	httpResponse = new HttpResponse();
    
    request->requestUrl = radCalNetUrl;
	request->login = login;
	request->password = password;
	
    httpClient->setReceivedEvent([this](){ findNearDateShapshot(); });
    httpClient->get(request, httpResponse);  
}

void SnapshotLoader::setAuthentification(QString login, QString password)
{
    this->login = login;
    this->password = password;
}

void SnapshotLoader::findNearDateShapshot()
{
    if(httpResponse->httpStatus != 200)
    {
        if(httpResponse->httpStatus == 401)
            callMessageEventHandler("Неверный логин или пароль!");
        else
            callMessageEventHandler("Произошла ошибка при загрузке!");
            
        qWarning().noquote() << "Произошла ошибка при загрузке файла. Код ошибки:" << httpResponse->httpStatus;
		return;
    }
	
    QString inputSite;
    QString outputSite;
    qint64 diff;
    qint64 minDiff = requestedDateTime.secsTo(requestedDateTime.addYears(100));
    
    QJsonDocument json = QJsonDocument::fromJson(httpResponse->content->readAll());
    QJsonArray jsonArray = json.array();
    
    for(auto value : jsonArray)
    {
        QJsonObject obj = value.toObject();
        
        QString currentSite = obj["name"].toString(); 
        QStringList nameParts = currentSite.split('_');
        
        int year = nameParts.at(1).toInt();
        int dayOfYear = nameParts.at(2).toInt();
        QString type = nameParts.at(3).split('.')[2];
        
        QDateTime dateTime = QDateTime(QDate(year, 1, 1));
        dateTime = dateTime.addDays(dayOfYear - 1);
        
        diff = std::abs(requestedDateTime.secsTo(dateTime));
        if(diff <= minDiff)
        {
            if(type == "input")
                inputSite = currentSite;
            else
                outputSite = currentSite;
            minDiff = diff;
        }
    }
    loadAndSaveSnapshotData(inputSite);
    loadAndSaveSnapshotData(outputSite);
    callMessageEventHandler("Загрузка успешно завершена");
}

void SnapshotLoader::loadAndSaveSnapshotData(QString snapshotName)
{
    HttpRequest * request = new HttpRequest();
    
    request->requestUrl = radCalNetUrl + snapshotName;
    request->login = login;
    request->password = password;
    
    httpClient->setReceivedEvent([this](){ saveSnapshot(); });
    httpClient->get(request, httpResponse);
}

void SnapshotLoader::saveSnapshot()
{
    QStringList urlParts = httpResponse->url.split('/');
    QString fileName = urlParts[urlParts.length() - 1];
    
    QDir dirMaker = QDir::current();
    dirMaker.mkdir(savePath);
    
    QFile * file = new QFile(savePath + fileName);
    file->open(QFile::WriteOnly);
    
    if(file->isOpen())
    {
        file->write(httpResponse->content->readAll());
        file->close();
        
        qInfo().noquote() << "Загружен файл данных снимка " + fileName;
    }
}

void SnapshotLoader::setCallMessageHandler(std::function<void(QString)> eventHandler)
{
    callMessageEventHandler = eventHandler;
}