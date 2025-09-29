#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include "qcustomplot.h"

#include <QPen>
#include <QColor>

class PixelGraphicsWindow: public QWidget
{
public:
    PixelGraphicsWindow();
    
	void paintPixelGraphics(uint16_t * pixelValues, double * waveLengthValues, int channelsCount);
	
	void show();
	
private:
	QCustomPlot * plot;
	QCPGraph * graphic;
	
    QGraphicsView * graphics;
	QGraphicsScene * scene = nullptr;
};