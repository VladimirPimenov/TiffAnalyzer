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
#include "channelSelectionWindow.h"
#include "pixelStatusBar.h"
#include "pixelsNormalizer.h"

class ImageLabel: public QLabel
{
public:
	ImageLabel();
	
	QImage * image = nullptr;
	
	ChannelSelectionWindow * channelSelector;
	PixelStatusBar * statusBar;

	std::string tiffLoadPath;

	void loadGrayscaleTIFF(std::string loadPath);
	void loadRgbTIFF(std::string loadPath);
	
	void updateImage();

	void clearImageLabel();
	
private:
	TIFF * tiffImage;	
	
	void openGrayscaleSelectionWindow(int channelsCount);
	void openRgbSelectionWindow(int channelsCount);

	void grayscaleSelectedEvent();
	void rgbSelectedEvent();
	
	void mouseMoveEvent(QMouseEvent * event) override;
};