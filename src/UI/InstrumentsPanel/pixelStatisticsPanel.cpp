#include "../../../include/pixelStatisticsPanel.h"

#include "../../../include/rgb.h"

PixelStatisticsPanel::PixelStatisticsPanel()
{
	text = new QLabel("Спектральная характеристика пикселя");

    plot = new QCustomPlot();
	plot->setFixedSize(355, 355);
	
	plot->xAxis->setRange(0, 10);
    plot->yAxis->setRange(0, 10);
    plot->xAxis->setLabel("Длина волны, нм");
    plot->yAxis->setLabel("Яркость 16 бит");

    graphic = new QCPGraph(plot->xAxis, plot->yAxis);
    graphic->setPen(QPen(Qt::red));
    
    graphic->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    
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
    
    plot->yAxis->setRange(0, DEFAULT_MAX_Y);
    
    double maxY = *std::max_element(y.begin(), y.end());
    if(maxY > DEFAULT_MAX_Y)
    {
        plot->yAxis->setRange(0, maxY + 10);
    }
    
    graphic->setData(x, y);
    
    plot->xAxis->rescale();
    
    plot->replot();
}

void PixelStatisticsPanel::setVisible(bool isVisible)
{
    plot->setVisible(isVisible);
        
    text->setVisible(isVisible);
}