#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

#include <QString>
#include <QStringList>

#include <functional>

class RectangleCoordsPanel: public QGridLayout
{
public:
    RectangleCoordsPanel();

    void setVisible(bool isVisible);
    
    void setInputChangedEvent(std::function<void()> eventHandler);

    QStringList * getX();
    QStringList * getY();

private:
    QLineEdit * x1Field;
    QLineEdit * x2Field;
    QLineEdit * y1Field;
    QLineEdit * y2Field;
    QLabel * x1FieldText;
    QLabel * x2FieldText;
    QLabel * y1FieldText;
    QLabel * y2FieldText;
    
    std::function<void()> inputChangedEventHandler;
    
    void inputChangedEvent();
};