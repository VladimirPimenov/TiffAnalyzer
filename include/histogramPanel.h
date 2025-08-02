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

	void setImage(TIFF * image);

	void updateHistogram();
	void clearHistogram(); 
	
	void setCutting(uint16_t leftValue, uint16_t rightValue);
	
	int getColumnValue(int x);
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


