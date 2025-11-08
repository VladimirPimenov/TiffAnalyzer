#pragma once

#include <QVBoxLayout>

#include "imageOptionsPanel.h"
#include "pixelStatisticsPanel.h"

#include "rgb.h"

class InstrumentsPanel: public QVBoxLayout
{
public:
    InstrumentsPanel();
    
	void updateDynamicPixelGraphic(uint16_t * pixelValues, double * waveLengthValues, int channelsCount, int pixelX, int pixelY);
	void addPixelGraphic(uint16_t * pixelValues, double * waveLengthValues, int channelsCount, int pixelX, int pixelY);
	
	void paintHistogramGraphics(std::map<uint16_t, int> & colorFrequency);
    
    void setHistogramCutting(Pixel16bit leftCuttingValues, Pixel16bit rightCuttingValues);
    
    void setGrayscaleSelectedEvent(std::function<void()> eventHandler);
	void setRgbSelectedEvent(std::function<void()> eventHandler);
    void setStandartContrastingEvent(std::function<void()> eventHandler);
    void setHistogramContrastingEvent(std::function<void()> eventHandler);
    void setResetContrastingEvent(std::function<void()> eventHandler);
    void setColorChangedEvent(std::function<void()> eventHandler);
    
    void setVisible(bool isVisible);
    void setEnabled(bool isEnabled);
    
	QColor getHistogramSelectedColor();
  
    bool isPixelSelecting();
private:
    ImageOptionsPanel * imagePanel;
    PixelStatisticsPanel * pixelPanel;      
};