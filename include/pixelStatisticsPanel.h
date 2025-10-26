#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "../src/Libs/qcustomplot.h"

const unsigned DEFAULT_MAX_X = 500;
const unsigned DEFAULT_MAX_Y = 10000;

class PixelStatisticsPanel: public QVBoxLayout
{
public:
    PixelStatisticsPanel();
    
	void paintPixelGraphics(uint16_t * pixelValues, double * waveLengthValues, int channelsCount);
    
    void setVisible(bool isVisible);
    
private:
    QCustomPlot * plot;
	QCPGraph * graphic;
	
	QLabel * text;
};