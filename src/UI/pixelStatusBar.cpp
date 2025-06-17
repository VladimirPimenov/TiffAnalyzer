#include "../../include/pixelStatusBar.h"

PixelStatusBar::PixelStatusBar()
{
    coordsLabel = new QLabel("Координаты:");
    coordsLabel->setAlignment(Qt::AlignRight);
    
    rgb8Label = new QLabel("RGB8:");
    rgb8Label->setAlignment(Qt::AlignRight);
    
    rgb16Label = new QLabel("RGB16:");
    rgb16Label->setAlignment(Qt::AlignRight);
    
    this->addWidget(coordsLabel, 1);
    this->addWidget(rgb8Label, 1);
    this->addWidget(rgb16Label, 1);
}

void PixelStatusBar::updateInfo(int x, int y, Pixel16bit pixel, Pixel16bit normalizedPixel)
{
    QString coords = QString::fromStdString(
    "Координаты: (" + std::to_string(x) + ";" + std::to_string(y) + ")");
    QString rgb8 = QString::fromStdString(
    "RGB8: (" + std::to_string(normalizedPixel.red) + ";" + std::to_string(normalizedPixel.green) + ";" + std::to_string(normalizedPixel.blue) + ")");
    QString rgb16 = QString::fromStdString(
    "RGB16: (" + std::to_string(pixel.red) + ";" + std::to_string(pixel.green) + ";" + std::to_string(pixel.blue) + ")");
    
    coordsLabel->setText(coords);
    rgb8Label->setText(rgb8);
    rgb16Label->setText(rgb16);
}

void PixelStatusBar::clearInfo()
{
    coordsLabel->setText("Координаты:");
    rgb8Label->setText("RGB8:");
    rgb16Label->setText("RGB16:");
}