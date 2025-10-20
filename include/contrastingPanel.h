#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

#include "../src/Libs/qcustomplot.h"

#include "histogramCalculator.h"

#include <map>
#include <functional>

class ContrastingPanel: public QVBoxLayout
{
public: 
    ContrastingPanel();
    
	void paintImageHistogram(std::map<uint16_t, int> & colorFrequency);

    void setVisible(bool isVisible);
    void setEnabled(bool isEnable);
    
    void setCutting(Pixel16bit leftCuttingValues, Pixel16bit rightCuttingValues);
    
    void setStandartContrastingEvent(std::function<void()> eventHandler);
    void setHistogramContrastingEvent(std::function<void()> eventHandler);
    void setResetContrastingEvent(std::function<void()> eventHandler);
    void setColorChangedEvent(std::function<void()> eventHandler);
    
	QColor getChannelColor();
    
private:
	QComboBox * channelSelector;
    
    QPushButton * standartContrastingButton;
	QPushButton * histogramContrastingButton;
	QPushButton * resetContrastingButton;
	QPushButton * resetScaleButton;
	
	QLabel * histogramText;
	QLabel * contrastingText;
	
	QCustomPlot * plot;
	QCPBars * histogram;
	
	Pixel16bit leftCuttingValues;
	Pixel16bit rightCuttingValues;
	
	int leftCuttingValue;
	int rightCuttingValue;
	
	void createChannelSelector();
	void createHistogram();
	void createContrastingOptions();
	
	void switchCutting();
	
	std::function<void()> standartContrastingEventHandler;
	std::function<void()> histogramContrastingEventHandler;
	std::function<void()> resetContrastingEventHandler;
	std::function<void()> colorChangedEventHandler;
	
	void resetScale();

private slots:
	void standartContrastingEvent();
	void histogramContrastingEvent();
	void resetContrastingEvent();
	void colorChangedEvent();
};