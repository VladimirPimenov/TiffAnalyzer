#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

#include <QPushButton>

#include "../src/Libs/qcustomplot.h"

const unsigned DEFAULT_MAX_Y = 10000;

class PixelStatisticsPanel: public QVBoxLayout
{
public:
    PixelStatisticsPanel();
    
	void paintDynamicPixelGraphic(uint16_t * pixelValues, double * waveLengthValues, int channelsCount, int pixelX, int pixelY);
	void addPixelGraphic(uint16_t * pixelValues, double * waveLengthValues, int channelsCount, int pixelX, int pixelY);
	void removePixelGraphic(unsigned graphicIndex);
	
    void setVisible(bool isVisible);
    void setEnabled(bool isEnabled);
    
    bool isPixelSelecting;
private:
    QCustomPlot * plot;
    
	QLabel * text;
	
	QPushButton * addPixelGraphicButton;
	QPushButton * switchLegendButton;
	QPushButton * switchMarkersButton;
	
	bool isMarkersVisible;
	
	void scaleVerticalAxis();
	void replot();
	
	void createOptionsTable();	
	
	void selectPixelGraphicEvent();
	void switchLegendEvent();
	void switchMarkersEvent();
};