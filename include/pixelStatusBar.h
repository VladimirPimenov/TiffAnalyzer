#pragma once

#include <QStatusBar>
#include <QLabel>

#include "rgb.h"

class PixelStatusBar: public QStatusBar
{
public:
    PixelStatusBar();
    
    void updateInfo(int x, int y, Pixel16bit pixel, Pixel16bit normalizedPixel);
    void clearInfo();
    
private:
    QLabel * coordsLabel;
    QLabel * rgb8Label;
    QLabel * rgb16Label;
};