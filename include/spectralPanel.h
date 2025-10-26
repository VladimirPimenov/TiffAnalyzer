#pragma once

#include <QVBoxLayout>

#include "contrastingPanel.h"
#include "pixelStatisticsPanel.h"

#include "rgb.h"

class SpectralPanel: public QVBoxLayout
{
public:
    SpectralPanel();
    
	void paintPixelGraphics(uint16_t * pixelValues, double * waveLengthValues, int channelsCount);
	void paintHistogramGraphics(std::map<uint16_t, int> & colorFrequency);
    
    void setHistogramCutting(Pixel16bit leftCuttingValues, Pixel16bit rightCuttingValues);
    
    void setStandartContrastingEvent(std::function<void()> eventHandler);
    void setHistogramContrastingEvent(std::function<void()> eventHandler);
    void setResetContrastingEvent(std::function<void()> eventHandler);
    void setColorChangedEvent(std::function<void()> eventHandler);
    
    void setVisible(bool isVisible);
    void setEnabled(bool isEnable);
    
	QColor getHistogramSelectedColor();
  
private:
    ContrastingPanel * contrastingPanel;
    PixelStatisticsPanel * pixelPanel;      
};