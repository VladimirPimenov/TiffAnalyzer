#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include <functional>

#include "rgb.h"

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
	float getRightCuttingPercent();
	float getLeftCuttingPercent();

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
	
	QLineEdit * histogramRightPercentEntry;
	QLineEdit * histogramLeftPercentEntry;
	
	std::function<void()> contrastingEventHandler;
	
	void createTextBox();
	QHBoxLayout * createContrastingEntryBox(QLabel * text, QLineEdit *& minEntry, QLineEdit *& maxEntry);
	
private slots:
	void contrastingEvent();
};