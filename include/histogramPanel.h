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

	void updateHistogram(TIFF * image);
	void clearHistogram(); 
	
private:
	HistogramPainter * painter;
	
	TIFF * spectatedImage;

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


