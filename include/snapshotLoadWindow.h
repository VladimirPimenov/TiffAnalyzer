#pragma once

#include <QDialog>

#include <QVBoxLayout>
#include <QGridLayout>

#include <QPushButton>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QLabel>

class SnapshotLoadWindow: public QDialog
{
public:
    SnapshotLoadWindow(QWidget * parent);
    
    void setLoadDateTime(QDateTime dateTime);
    
private:
    QVBoxLayout * vWidgetBox;
    
    QLineEdit * loginField;
    QLineEdit * passwordField;

    QDateTimeEdit * dateTimeField;
    
    QPushButton * loadButton;
    
    void loadSnapshotEvent();
};