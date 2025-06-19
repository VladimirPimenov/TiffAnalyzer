#pragma once

#include <QLabel>
#include <QImage>
#include <QComboBox>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>

#include <string>
#include <fstream>

#include "tiff.h"
#include "imagePainter.h"
#include "channelSelectionWindow.h"
#include "contrastingWindow.h"
#include "pixelStatusBar.h"
#include "histogramPanel.h"

class ImageLabel: public QLabel
{
public:
	ImageLabel();
	
	ChannelSelectionWindow * channelSelector;
	ContrastingWindow * contrastingWin;
	
	PixelStatusBar * statusBar;
	
	HistogramPanel * histrogram;

	std::string tiffLoadPath;

	void loadGrayscaleTIFF(std::string loadPath);
	void loadRgbTIFF(std::string loadPath);
	
	void standartContrasting();
	
	void updateImage();

	void clearImageLabel();
	
private:
	TIFF * tiffImage;	
	QImage * image = nullptr;
	
	ImagePainter * painter;
	
	uint16_t minNormalizationValue = 0;
	uint16_t maxNormalizationValue = 255;
	
	void openGrayscaleSelectionWindow(int channelsCount);
	void openRgbSelectionWindow(int channelsCount);

	void grayScaleSelectedEvent();
	void rgbSelectedEvent();
	void standartContrastingEvent();
	
	void mouseMoveEvent(QMouseEvent * event) override;
};