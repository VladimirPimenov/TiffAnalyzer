#include "../../include/pixelGraphicsWindow.h"
#include <iostream>
#include "../../include/normalizer.h"

PixelGraphicsWindow::PixelGraphicsWindow(): QWidget()
{
	plot = new QCustomPlot();
	plot->setFixedSize(500, 500);
	
    graphic = new QCPGraph(plot->xAxis, plot->yAxis);
    graphic->setPen(QPen(Qt::red));
    
    plot->addPlottable(graphic);
}

void PixelGraphicsWindow::paintPixelGraphics(uint16_t * pixelValues, double * waveLengthValues, int channelsCount)
{   
    QVector<double> x(channelsCount), y(channelsCount);
    
    for(int i = 0; i < channelsCount; i++)
    {
        x[i] = waveLengthValues[i];
        y[i] = pixelValues[i];
    }
    
    plot->xAxis->setRange(0, 500);
    plot->yAxis->setRange(0, 66000);
    
    graphic->setData(x, y);
    
    plot->xAxis->setLabel("Длина волны");
    plot->yAxis->setLabel("Яркость");
    
    plot->rescaleAxes();
    plot->replot();
}

void PixelGraphicsWindow::show()
{
    plot->show();
}