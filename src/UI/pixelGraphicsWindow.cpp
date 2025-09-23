#include "../../include/pixelGraphicsWindow.h"
#include <iostream>
#include "../../include/normalizer.h"

PixelGraphicsWindow::PixelGraphicsWindow(): QWidget()
{
    axisOffset = 50;
    
    graphics = new QGraphicsView();
    scene = new QGraphicsScene();
    
    graphics->setScene(scene);
}

void PixelGraphicsWindow::paintAxisX(int minX, int maxX)
{
	QPen pen = Qt::black;
	QBrush brush = Qt::black;
	
    scene->addRect(axisOffset, 0, 500, 1, pen, brush);

	scene->addRect(axisOffset + 500 / 4, 0, 1, -5, pen, brush);
	scene->addRect(axisOffset + 500 / 2, 0, 1, -5, pen, brush);
	scene->addRect(axisOffset + 500 * 3 / 4, 0, 1, -5, pen, brush);
	scene->addRect(axisOffset + 500, 0, 1, -5, pen, brush);
	
	int middle = (maxX + minX) / 2;
	
	QGraphicsTextItem * x0 = scene->addText(QString::fromStdString(std::to_string(minX)));
	QGraphicsTextItem * x1 = scene->addText(QString::fromStdString(std::to_string((minX + middle) / 2)));
	QGraphicsTextItem * x2 = scene->addText(QString::fromStdString(std::to_string(middle)));
	QGraphicsTextItem * x3 = scene->addText(QString::fromStdString(std::to_string((middle + maxX) / 2)));
	QGraphicsTextItem * x4 = scene->addText(QString::fromStdString(std::to_string(maxX)));
	
	x0->setPos(axisOffset - 15 + 0, 0);
	x1->setPos(axisOffset - 15 + 500 / 4, 0);
	x2->setPos(axisOffset - 15 + 500 / 2, 0);
	x3->setPos(axisOffset - 15 + 500 * 3 / 4, 0);
	x4->setPos(axisOffset - 15 + 500, 0);
}

void PixelGraphicsWindow::paintAxisY(int minValue, int maxValue)
{
    int height = 500;
    
	QPen pen = Qt::black;
	QBrush brush = Qt::black;

	scene->addRect(axisOffset, 0, 1, -500, pen, brush);
	
	scene->addRect(axisOffset, -height / 4, 5, 1, pen, brush);
	scene->addRect(axisOffset, -height / 2, 5, 1, pen, brush);
	scene->addRect(axisOffset, -height * 3 / 4, 5, 1, pen, brush);
	scene->addRect(axisOffset, -height, 5, 1, pen, brush);
	
	QGraphicsItem * y1 = scene->addText(QString::fromStdString(std::to_string(maxValue / 4)));
	QGraphicsItem * y2 = scene->addText(QString::fromStdString(std::to_string(maxValue / 2)));
	QGraphicsItem * y3 = scene->addText(QString::fromStdString(std::to_string(maxValue * 3 / 4)));
	QGraphicsItem * y4 = scene->addText(QString::fromStdString(std::to_string(maxValue)));

	y1->setPos(0, -500 / 4 - 10);
	y2->setPos(0, -500 / 2 - 10);
	y3->setPos(0, -500 * 3 / 4 - 10);
	y4->setPos(0, -500 - 10);
}

void PixelGraphicsWindow::paintPixelGraphics(uint16_t * pixelValues, double * waveLengthValues, int channelsCount)
{
	QPen pen = Qt::red;

	int scaledY1, scaledY2;
	int minY = 0;
	int maxY = 0;
	int minX = waveLengthValues[0];
	int maxX = 0;
	
	int step = 500 / channelsCount;
	
	for(int i = 0; i < channelsCount; i++)
	{
		if(pixelValues[i] < minY)
			minY = pixelValues[i];
		
	    if(pixelValues[i] > maxY)
			maxY = pixelValues[i];
			
		if(waveLengthValues[i] < minX)
			minX = waveLengthValues[i];
			
		if(waveLengthValues[i] > maxX)
			maxX = waveLengthValues[i];
	}	
	
	paintAxisX(minX, maxX);
	paintAxisY(minY, maxY);
	
	int x = 0;
	
    for(int i = 1; i < channelsCount; i++)
    {
		scaledY1 = Normalizer::minMaxNormalization(pixelValues[i-1], minY, maxY, 0, 500);
		scaledY2 = Normalizer::minMaxNormalization(pixelValues[i], minY, maxY, 0, 500);
    
        scene->addLine(x + axisOffset, -scaledY1, (x + step + axisOffset), -scaledY2, pen);
        
        x += step;
    }
}

void PixelGraphicsWindow::show()
{
    graphics->show();
}