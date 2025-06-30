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
#include "rgb.h"
#include "imagePainter.h"
#include "channelSelectionWindow.h"
#include "contrastingWindow.h"
#include "pixelStatusBar.h"
#include "histogramPanel.h"
#include "bmp.h"
#include "ImageConverter.h"

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
	
	void saveImageAsBmp(std::string savePath);
	
	void standartContrasting();
	void histogramContrasting();
	void resetContrasting();
	
	void updateImage(uint16_t min16bitValue, uint16_t max16bitValue);

	void clearImageLabel();
	
	bool hasImage();
	
private:
	TIFF * image16bit;	
	QImage * image8bit;
	
	ImagePainter * painter;
	
	Pixel16bit minNormalizationPixel;
	Pixel16bit maxNormalizationPixel;
	
	void openGrayscaleSelectionWindow(int channelsCount);
	void openRgbSelectionWindow(int channelsCount);

	void grayScaleSelectedEvent();
	void rgbSelectedEvent();
	void standartContrastingEvent();
	void histogramContrastingEvent();
	
	void mouseMoveEvent(QMouseEvent * event) override;
	
	void resetContrastingParams();
};