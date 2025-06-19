#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include <functional>

class ContrastingWindow: public QDialog
{
public:
    ContrastingWindow(QWidget * parent);
    
	void setContrastingEvent(std::function<void()> eventHandler);
	
	uint16_t getMinValue();
	uint16_t getMaxValue();

private:
	QVBoxLayout * vWidgetsBox;
	QHBoxLayout * hWidgetsBox;
	
	QPushButton * okButton;
	
	QLineEdit * minContrastingValueEntry;
	QLineEdit * maxContrastingValueEntry;
	
	std::function<void()> contrastingEventHandler;
	
	void createGrayscaleContrastingWindow();
	void createRgbContrastingWindow();
	
private slots:
	void contrastingEvent();
};