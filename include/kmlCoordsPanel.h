#pragma once

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QFileDialog>

#include <QString>
#include <QStringList>

#include <functional>

#include "kml.h"

#include <QDebug>

class KmlCoordsPanel: public QVBoxLayout
{
public:
    KmlCoordsPanel();

    void setVisible(bool isVisible);
    
    void setInputChangedEvent(std::function<void()> eventHandler);

    QStringList * getX();
    QStringList * getY();

private:
    QVBoxLayout * vBox;

    QLabel * kmlPathLabel;
    QPushButton * selectKmlButton;
    
    QLabel * leftUpperCornerX;
    QLabel * leftUpperCornerY;
    QLabel * rightUpperCornerX;
    QLabel * rightUpperCornerY;
    QLabel * leftLowerCornerX;
    QLabel * leftLowerCornerY;
    QLabel * rightLowerCornerX;
    QLabel * rightLowerCornerY;
    
    QLabel * corner1Text;
    QLabel * corner2Text;
    QLabel * corner3Text;
    QLabel * corner4Text;
    
    QLabel * kmlXText1;
    QLabel * kmlYText1;
    QLabel * kmlXText2;
    QLabel * kmlYText2;
    QLabel * kmlXText3;
    QLabel * kmlYText3;
    QLabel * kmlXText4;
    QLabel * kmlYText4;
    
    std::function<void()> inputChangedEventHandler;
    
    void fillKmlCornerLabels(Kml * kml);
    
    void inputChangedEvent();
    void openKmlEvent();
};