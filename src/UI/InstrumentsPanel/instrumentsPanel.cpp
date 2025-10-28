#include "../../../include/instrumentsPanel.h"

InstrumentsPanel::InstrumentsPanel()
{
    imagePanel = new ImageOptionsPanel();
    pixelPanel = new PixelStatisticsPanel();
    
    this->addLayout(imagePanel);
    this->addLayout(pixelPanel);
}

void InstrumentsPanel::paintPixelGraphics(uint16_t * pixelValues, double * waveLengthValues, int channelsCount)
{
    pixelPanel->paintPixelGraphics(pixelValues, waveLengthValues, channelsCount);
}

void InstrumentsPanel::paintHistogramGraphics(std::map<uint16_t, int> & colorFrequency)
{
    imagePanel->paintImageHistogram(colorFrequency);
}

void InstrumentsPanel::setHistogramCutting(Pixel16bit leftCuttingValues, Pixel16bit rightCuttingValues)
{
    imagePanel->setCutting(leftCuttingValues, rightCuttingValues);
}

void InstrumentsPanel::setGrayscaleSelectedEvent(std::function<void()> eventHandler)
{
    imagePanel->setGrayscaleSelectedEvent(eventHandler);
}

void InstrumentsPanel::setRgbSelectedEvent(std::function<void()> eventHandler)
{
    imagePanel->setRgbSelectedEvent(eventHandler);

}
void InstrumentsPanel::setStandartContrastingEvent(std::function<void()> eventHandler)
{
    imagePanel->setStandartContrastingEvent(eventHandler);
}
void InstrumentsPanel::setHistogramContrastingEvent(std::function<void()> eventHandler)
{
    imagePanel->setHistogramContrastingEvent(eventHandler);
}
void InstrumentsPanel::setResetContrastingEvent(std::function<void()> eventHandler)
{
    imagePanel->setResetContrastingEvent(eventHandler);
}
void InstrumentsPanel::setColorChangedEvent(std::function<void()> eventHandler)
{
    imagePanel->setColorChangedEvent(eventHandler);
}

void InstrumentsPanel::setVisible(bool isVisible)
{
    imagePanel->setVisible(isVisible);
    pixelPanel->setVisible(isVisible);
}

void InstrumentsPanel::setEnabled(bool isEnable)
{
    imagePanel->setEnabled(isEnable);
    pixelPanel->setEnabled(isEnable);
}

QColor InstrumentsPanel::getHistogramSelectedColor()
{
    return imagePanel->getChannelColor();
}