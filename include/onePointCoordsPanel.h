#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

#include <QString>

#include <functional>

class OnePointCoordsPanel: public QGridLayout
{
public:
    OnePointCoordsPanel();

    void setVisible(bool isVisible);

    void setInputChangedEvent(std::function<void()> eventHandler);

    QString getX();
    QString getY();

private:
    QLineEdit * xField;
    QLineEdit * yField;
    QLabel * xFieldText;
    QLabel * yFieldText;
    
    std::function<void()> inputChangedEventHandler;
    
    void inputChangedEvent();
};