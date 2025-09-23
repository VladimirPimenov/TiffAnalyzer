#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include <QPen>
#include <QColor>

class PixelGraphicsWindow: public QWidget
{
public:
    PixelGraphicsWindow();

    void paintAxisX(int minValue, int maxValue);
	void paintAxisY(int minValue, int maxValue);
	
	void paintPixelGraphics(uint16_t * pixelValues, double * waveLengthValues, int channelsCount);
	
	void show();
	
private:
    int axisOffset;
    float XScale;
	float Yscale;

    QGraphicsView * graphics;
	QGraphicsScene * scene = nullptr;
};