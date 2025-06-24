#pragma once

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QLabel>
#include <QComboBox>
#include <QImage>
#include <QPushButton>
#include <QWidget>

#include <map>
#include <string>

#include "histogramPainter.h"
#include "tiff.h"

class HistogramPanel: public QWidget
{
public:
	HistogramPanel();

	void updateHistogram(TIFF * image, uint16_t minValue, uint16_t maxValue);
	void clearHistogram(); 
	
	uint16_t getMaxPixel16Value();
private:
	HistogramPainter * painter;
	
	TIFF * spectatedImage;
	
	uint16_t minValue;
	uint16_t maxValue;
	
	QComboBox * channelSelector;
	
	QVBoxLayout * panel;

	QGraphicsView * histogram;
	QGraphicsScene * scene = nullptr;

	QColor getChannelColor();
	
	void createHistogramPanel();
	void createChannelSelector();
	
	void reloadHistogramScene();
	
	void changeColor();
};


