#include "../../include/snapshotLoadWindow.h"

#include <iostream>

SnapshotLoadWindow::SnapshotLoadWindow(QWidget * parent = nullptr): QDialog(parent)
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
    
    vWidgetBox->addWidget(text);
    vWidgetBox->addLayout(userDataTable);
    vWidgetBox->addWidget(dateTimeField);
    vWidgetBox->addWidget(loadButton);
    
    connect(loadButton, &QPushButton::clicked, this, &SnapshotLoadWindow::loadSnapshotEvent);
} 

void SnapshotLoadWindow::setLoadDateTime(QDateTime dateTime)
{
    dateTimeField->setDateTime(dateTime);
}

void SnapshotLoadWindow::loadSnapshotEvent()
{
}