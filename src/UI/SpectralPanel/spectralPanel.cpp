#include "../../../include/spectralPanel.h"

SpectralPanel::SpectralPanel()
{
    contrastingPanel = new ContrastingPanel();
    pixelPanel = new PixelStatisticsPanel();
    
    this->addLayout(contrastingPanel);
    this->addLayout(pixelPanel);
}

void SpectralPanel::paintPixelGraphics(uint16_t * pixelValues, double * waveLengthValues, int channelsCount)
{
    pixelPanel->paintPixelGraphics(pixelValues, waveLengthValues, channelsCount);
}

void SpectralPanel::paintHistogramGraphics(std::map<uint16_t, int> & colorFrequency)
{
    contrastingPanel->paintImageHistogram(colorFrequency);
}

void SpectralPanel::setHistogramCutting(Pixel16bit leftCuttingValues, Pixel16bit rightCuttingValues)
{
    contrastingPanel->setCutting(leftCuttingValues, rightCuttingValues);
}
    
void SpectralPanel::setStandartContrastingEvent(std::function<void()> eventHandler)
{
    contrastingPanel->setStandartContrastingEvent(eventHandler);
}
void SpectralPanel::setHistogramContrastingEvent(std::function<void()> eventHandler)
{
    contrastingPanel->setHistogramContrastingEvent(eventHandler);
}
void SpectralPanel::setResetContrastingEvent(std::function<void()> eventHandler)
{
    contrastingPanel->setResetContrastingEvent(eventHandler);
}
void SpectralPanel::setColorChangedEvent(std::function<void()> eventHandler)
{
    contrastingPanel->setColorChangedEvent(eventHandler);
}

void SpectralPanel::setVisible(bool isVisible)
{
    contrastingPanel->setVisible(isVisible);
    pixelPanel->setVisible(isVisible);
}

void SpectralPanel::setEnabled(bool isEnable)
{
    contrastingPanel->setEnabled(isEnable);
    pixelPanel->setEnabled(isEnable);
}

QColor SpectralPanel::getHistogramSelectedColor()
{
    return contrastingPanel->getChannelColor();
}