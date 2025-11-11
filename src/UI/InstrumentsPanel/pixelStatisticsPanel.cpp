#include "../../../include/pixelStatisticsPanel.h"

#include "../../../include/rgb.h"
#include <ctime>

PixelStatisticsPanel::PixelStatisticsPanel()
{
    srand(time(0));

	text = new QLabel("Спектральная характеристика пикселя");

    plot = new QCustomPlot();
    plot->addGraph();
    
	plot->setFixedSize(355, 355);
	
	plot->xAxis->setRange(0, 10);
    plot->yAxis->setRange(0, 10);
	
    plot->xAxis->setLabel("Длина волны, нм");
    plot->yAxis->setLabel("Яркость 16 бит");
    
    isPixelSelect = false;
    isMarkersVisible = true;
    
	this->addWidget(text);
    this->addWidget(plot);
    
    createOptionsTable();

    connect(plot, &QCustomPlot::legendClick, this, [this](QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event) { legendClickedEvent(legend, item, event); } );  
    
    this->addStretch(1);
}

QPen chooseGraphicPen()
{
    int red = rand() % (255 - 0 + 1) + 0;
    int green = rand() % (255 - 0 + 1) + 0;
    int blue = rand() % (255 - 0 + 1) + 0;
        
    return QPen(QColor(red, green, blue));
}

void PixelStatisticsPanel::paintDynamicPixelGraphic(uint16_t * pixelValues, double * waveLengthValues, int channelsCount, int pixelX, int pixelY)
{
    QVector<double> x(channelsCount), y(channelsCount);
    
    for(int i = 0; i < channelsCount; i++)
    {
        x[i] = waveLengthValues[i];
        y[i] = pixelValues[i];
    }
    
    std::string graphTitle = std::to_string(pixelX) + ";" + std::to_string(pixelY);
    
    plot->graph(0)->setPen(QPen(Qt::red));
    plot->graph(0)->setName(QString::fromStdString(graphTitle));
    
    if(isMarkersVisible)
        plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    else
        plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 0));
    
    plot->graph(0)->setData(x, y);
    
    replot();
}

void PixelStatisticsPanel::addPixelGraphic(uint16_t * pixelValues, double * waveLengthValues, int channelsCount, int pixelX, int pixelY)
{
    if(plot->graphCount() == 5)
        return;
        
    QVector<double> x(channelsCount), y(channelsCount);
    
    for(int i = 0; i < channelsCount; i++)
    {
        x[i] = waveLengthValues[i];
        y[i] = pixelValues[i];
    }
    
    QCPGraph * graphic = plot->addGraph();
    
    std::string graphTitle = std::to_string(pixelX) + ";" + std::to_string(pixelY);
    
    graphic->setName(QString::fromStdString(graphTitle));
    graphic->setPen(chooseGraphicPen());
    
    if(isMarkersVisible)
        graphic->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    else
        graphic->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 0));
    
    graphic->setData(x, y);
    
    replot();
}

void PixelStatisticsPanel::scaleVerticalAxis()
{
    double maxY = DEFAULT_MAX_Y;
    bool found;
    
    for(int graphIndex = 0; graphIndex < plot->graphCount(); graphIndex++)
    {
        QCPGraph * graph = plot->graph(graphIndex);
        QCPRange verticalRange = graph->data()->valueRange(found);
        
        if(verticalRange.upper > maxY)
            maxY = verticalRange.upper;
    }
    
    plot->yAxis->setRange(0, maxY);
}

void PixelStatisticsPanel::replot()
{
    plot->xAxis->rescale();
    scaleVerticalAxis();
    plot->replot();
}

void PixelStatisticsPanel::createOptionsTable()
{
    QGridLayout * optionsButtonsTable = new QGridLayout();
    
    addPixelGraphicButton = new QPushButton();
    switchLegendButton = new QPushButton();
    switchMarkersButton = new QPushButton();
    
    addPixelGraphicButton->setCheckable(true);
    switchLegendButton->setCheckable(true);
    switchMarkersButton->setCheckable(true);
    
    addPixelGraphicButton->setToolTip("Добавить график пикселя");
    switchLegendButton->setToolTip("Переключить легенду");
    switchMarkersButton->setToolTip("Переключить маркеры");
    
    addPixelGraphicButton->setIcon(QIcon(":Icons/addGraphicButton"));
    switchLegendButton->setIcon(QIcon(":Icons/legendButton"));
    switchMarkersButton->setIcon(QIcon(":Icons/markersButton"));
    
    connect(addPixelGraphicButton, &QPushButton::toggled, this, &PixelStatisticsPanel::selectPixelGraphicEvent);
    connect(switchLegendButton, &QPushButton::clicked, this, &PixelStatisticsPanel::switchLegendEvent);
    connect(switchMarkersButton, &QPushButton::clicked, this, &PixelStatisticsPanel::switchMarkersEvent);
    
    optionsButtonsTable->addWidget(addPixelGraphicButton, 0, 0);
    optionsButtonsTable->addWidget(switchLegendButton, 0, 1);
    optionsButtonsTable->addWidget(switchMarkersButton, 0, 2);
    
    this->addLayout(optionsButtonsTable);
} 

void PixelStatisticsPanel::setVisible(bool isVisible)
{
    plot->setVisible(isVisible);
        
    text->setVisible(isVisible);
    
    addPixelGraphicButton->setVisible(isVisible);
    switchLegendButton->setVisible(isVisible);
    switchMarkersButton->setVisible(isVisible);
}

void PixelStatisticsPanel::setEnabled(bool isEnabled)
{   
    addPixelGraphicButton->setEnabled(isEnabled);
    switchLegendButton->setEnabled(isEnabled);
    switchMarkersButton->setEnabled(isEnabled);
}

void PixelStatisticsPanel::selectPixelGraphicEvent()
{
    isPixelSelect = !isPixelSelect;
}

void PixelStatisticsPanel::switchLegendEvent()
{
    plot->legend->setVisible(!plot->legend->visible());
    
    plot->replot();
}

void PixelStatisticsPanel::switchMarkersEvent()
{
    int graphCount = plot->graphCount();
    
    if(graphCount == 0)
        return;
        
    for(int graphIndex = 0; graphIndex < graphCount; graphIndex++)
    {
        if(isMarkersVisible)
            plot->graph(graphIndex)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 0));
        else
            plot->graph(graphIndex)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    }
    plot->replot();
    
    isMarkersVisible = !isMarkersVisible;
}

bool PixelStatisticsPanel::isPixelSelecting()
{
    return isPixelSelect;
} 

int getGraphIndex(QCustomPlot * plot, QCPGraph * graph)
{
    for(int graphIndex = 0; graphIndex < plot->graphCount(); graphIndex++)
    {
        if(graph == plot->graph(graphIndex))
            return graphIndex;
    }
}

void PixelStatisticsPanel::legendClickedEvent(QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event)
{
    QCPPlottableLegendItem * plottableItem = (QCPPlottableLegendItem*)(item);
    
    if(!plottableItem)
        return;
        
    QCPGraph * graphic = (QCPGraph*)(plottableItem->plottable());
    
    if(getGraphIndex(plot, graphic) != 0)
    {
        plot->removeGraph(graphic);
        replot();
    }
}