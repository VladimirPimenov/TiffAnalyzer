#include "../../include/snapshotLoadWindow.h"

SnapshotLoadWindow::SnapshotLoadWindow(QWidget * parent, HttpClient * httpClient): QDialog(parent)
{
    this->setWindowModality(Qt::WindowModality::WindowModal);
    this->setWindowTitle("Загрузка данных снимка");
    this->setFixedSize(400, 200);

    vWidgetBox = new QVBoxLayout(this);
    
    QLabel * text = new QLabel("Введите логин и пароль RadCalNet");
    text->setAlignment(Qt::AlignCenter);
    
    QGridLayout * userDataTable = new QGridLayout();
    
    QLabel * loginText = new QLabel("Логин");
    QLabel * passwordText = new QLabel("Пароль");
    loginField = new QLineEdit();
    passwordField = new QLineEdit();
    
    userDataTable->addWidget(loginText, 0, 0);
    userDataTable->addWidget(passwordText, 1, 0);
    userDataTable->addWidget(loginField, 0, 1);
    userDataTable->addWidget(passwordField, 1, 1);
    
    dateTimeField = new QDateTimeEdit(QDateTime::currentDateTime());
    
    loadButton = new QPushButton("Загрузить данные снимка");
    
    messageText = new QLabel();
    messageText->setAlignment(Qt::AlignCenter);
    
    vWidgetBox->addWidget(text);
    vWidgetBox->addLayout(userDataTable);
    vWidgetBox->addWidget(dateTimeField);
    vWidgetBox->addWidget(loadButton);
    vWidgetBox->addWidget(messageText);
    
    connect(loadButton, &QPushButton::clicked, this, &SnapshotLoadWindow::loadSnapshotEvent);
    
    loader = new SnapshotLoader(httpClient);
    loader->setCallMessageHandler([this](QString message){loaderMessageEvent(message);});
} 

void SnapshotLoadWindow::setLoadDateTime(QDateTime dateTime)
{
    dateTimeField->setDateTime(dateTime);
}

void SnapshotLoadWindow::loadSnapshotEvent()
{
    messageText->setText("Идёт загрузка...");

    loader->setAuthentification(loginField->text(), passwordField->text());
    loader->loadSnapshotByDatetime(dateTimeField->dateTime());
}

void SnapshotLoadWindow::loaderMessageEvent(QString message)
{
    messageText->setText(message);
}