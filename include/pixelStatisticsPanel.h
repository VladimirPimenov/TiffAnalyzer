#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#include "qcustomplot.h"

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