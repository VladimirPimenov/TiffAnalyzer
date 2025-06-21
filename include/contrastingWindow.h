#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "rgb.h"

#include <functional>

class ContrastingWindow: public QDialog
{
public:
    ContrastingWindow(QWidget * parent);
    
    void createGrayscaleContrastingWindow();
    void createRgbContrastingWindow();
	void createHistogramContrastingWindow();
    
	void setContrastingEvent(std::function<void()> eventHandler);
	
	Pixel16bit getMinPixelParameters();
	Pixel16bit getMaxPixelParameters();

private:
	bool isGrayscaleContrasting;
	
	QVBoxLayout * vWidgetsBox;
	
	QHBoxLayout * textBox;
	
	QLabel * minValueText;
	QLabel * maxValueText;
	
	QPushButton * okButton;
	
	QLineEdit * grayscaleMinContastingEntry;
	QLineEdit * grayscaleMaxContastingEntry;
	
	QLineEdit * redMinContastingEntry;
	QLineEdit * redMaxContastingEntry;
	QLineEdit * greenMinContastingEntry;
	QLineEdit * greenMaxContastingEntry;
	QLineEdit * blueMinContastingEntry;
	QLineEdit * blueMaxContastingEntry;
	
	QLineEdit * histogramCuttingPercentEntry;
	
	std::function<void()> contrastingEventHandler;
	
private slots:
	void contrastingEvent();
};