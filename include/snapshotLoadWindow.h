#pragma once

#include <QDialog>

#include <QVBoxLayout>
#include <QGridLayout>

#include <QPushButton>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QLabel>

#include <QString>

#include "snapshotLoader.h"

class SnapshotLoadWindow: public QDialog
{
public:
    SnapshotLoadWindow(QWidget * parent);
    
    void setLoadDateTime(QDateTime dateTime);
    
private:
    QVBoxLayout * vWidgetBox;
    
    QLineEdit * loginField;
    QLineEdit * passwordField;
    
    QLabel * messageText;

    QDateTimeEdit * dateTimeField;
    
    QPushButton * loadButton;
    
    SnapshotLoader * loader;
    
    void loadSnapshotEvent();
    
    void loaderMessageEvent(QString message);
};