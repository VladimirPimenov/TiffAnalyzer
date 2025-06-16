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

class HistogramPainter;

class HistogramPanel: public QWidget
{
	friend class HistogramPainter;

public:
	HistogramPanel();

	void updateHistogram(QImage * image);
	void clearHistogram(); 
	
private:
	HistogramPainter * painter;
	
	QImage * spectatedImage;

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


