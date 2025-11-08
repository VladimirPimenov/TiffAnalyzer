#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

#include "../src/Libs/qcustomplot.h"

#include "histogramCalculator.h"

#include <map>
#include <functional>

class ImageOptionsPanel: public QVBoxLayout
{
public: 
    ImageOptionsPanel();
    
	void paintImageHistogram(std::map<uint16_t, int> & colorFrequency);

    void setVisible(bool isVisible);
    void setEnabled(bool isEnable);
    
    void setCutting(Pixel16bit leftCuttingValues, Pixel16bit rightCuttingValues);
    
    void setGrayscaleSelectedEvent(std::function<void()> eventHandler);
	void setRgbSelectedEvent(std::function<void()> eventHandler);
    void setStandartContrastingEvent(std::function<void()> eventHandler);
    void setHistogramContrastingEvent(std::function<void()> eventHandler);
    void setResetContrastingEvent(std::function<void()> eventHandler);
    void setColorChangedEvent(std::function<void()> eventHandler);
    
	QColor getChannelColor();
    
private:
	QComboBox * channelSelector;
    
    QPushButton * grayscaleButton;
    QPushButton * rgbButton;
    QPushButton * standartContrastingButton;
	QPushButton * histogramContrastingButton;
	QPushButton * resetContrastingButton;
	QPushButton * resetHistogramScaleButton;
	
	QLabel * histogramText;
	QLabel * optionsText;
	
	QCustomPlot * plot;
	QCPBars * histogram;
	
	Pixel16bit leftCuttingValues;
	Pixel16bit rightCuttingValues;
	
	int leftCuttingValue;
	int rightCuttingValue;
	
	void createChannelSelector();
	void createHistogram();
	void createOptionsTable();
	
	void switchCutting();
	
	std::function<void()> grayscaleSelectedEventHandler;
	std::function<void()> rgbSelectedEventHandler;
	std::function<void()> standartContrastingEventHandler;
	std::function<void()> histogramContrastingEventHandler;
	std::function<void()> resetContrastingEventHandler;
	std::function<void()> colorChangedEventHandler;
	
	void resetHistogramScale();

private slots:
	void grayscaleSelectedEvent();
	void rgbSelectedEvent();
	void standartContrastingEvent();
	void histogramContrastingEvent();
	void resetContrastingEvent();
	void colorChangedEvent();
};