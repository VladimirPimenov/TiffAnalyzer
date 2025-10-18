#include "../../include/pixelStatisticsPanel.h"

#include "../../include/rgb.h"

PixelStatisticsPanel::PixelStatisticsPanel()
{
	text = new QLabel("Спектральная характеристика пикселя\n\n");

    plot = new QCustomPlot();
	plot->setFixedSize(350, 350);
	plot->xAxis->setRange(0, 1);
    plot->yAxis->setRange(0, 1);

    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plot->axisRect()->setRangeDrag(Qt::Horizontal);
    plot->axisRect()->setRangeZoom(Qt::Horizontal);
    plot->axisRect()->setRangeZoomAxes(plot->xAxis, NULL);
    
    graphic = new QCPGraph(plot->xAxis, plot->yAxis);
    graphic->setPen(QPen(Qt::red));
    
	this->addWidget(text);
    this->addWidget(plot);
    
    this->addStretch(1);
}

void PixelStatisticsPanel::paintPixelGraphics(uint16_t * pixelValues, double * waveLengthValues, int channelsCount)
{   
    QVector<double> x(channelsCount), y(channelsCount);
    
    for(int i = 0; i < channelsCount; i++)
    {
        x[i] = waveLengthValues[i];
        y[i] = pixelValues[i];
    }
    
    plot->xAxis->setRange(0, 500);
    
    graphic->setData(x, y);
    
    plot->xAxis->setLabel("Длина волны");
    plot->yAxis->setLabel("Яркость");
    
    plot->rescaleAxes();
    
    plot->yAxis->setRange(0, MAX_PIXEL_16BIT_VALUE);
    
    plot->replot();
}

void PixelStatisticsPanel::setVisible(bool isVisible)
{
    if(isVisible)
    {
        plot->setVisible(true);
        
        text->setVisible(true);
    }
    else
    {
        plot->setVisible(false);
        
        text->setVisible(false);
    }
}