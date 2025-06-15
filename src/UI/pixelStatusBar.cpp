#include "../../include/pixelStatusBar.h"

PixelStatusBar::PixelStatusBar()
{
    coordsLabel = new QLabel("Координаты:");
    coordsLabel->setAlignment(Qt::AlignRight);
    
    rgb16Label = new QLabel("RGB16:");
    rgb16Label->setAlignment(Qt::AlignRight);
    
    this->addWidget(coordsLabel, 1);
    this->addWidget(rgb16Label, 1);
}

void PixelStatusBar::updateInfo(int x, int y, Pixel16bit pixel)
{
    coordsLabel->setText(QString::fromStdString(
    "Координаты: (" + std::to_string(x) + ";" + std::to_string(y) + ")"
    ));
    rgb16Label->setText(QString::fromStdString(
    "RGB: (" + std::to_string(pixel.red) + ";" + std::to_string(pixel.green) + ";" + std::to_string(pixel.blue) + ")"
    ));
}

void PixelStatusBar::clearInfo()
{
    coordsLabel->setText("Координаты:");
    rgb16Label->setText("RGB16:");
}