#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QImage>
#include <QLabel>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include <QComboBox>
#include <QPushButton>

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
	
	int getColumnValue(int x);
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


