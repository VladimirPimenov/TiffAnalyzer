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
#include "pixelStatusBar.h"
#include "histogramPanel.h"

class ImageLabel: public QLabel
{
public:
	ImageLabel();
	
	ChannelSelectionWindow * channelSelector;
	PixelStatusBar * statusBar;
	HistogramPanel * histrogram;

	std::string tiffLoadPath;

	void loadGrayscaleTIFF(std::string loadPath);
	void loadRgbTIFF(std::string loadPath);
	
	void updateImage();

	void clearImageLabel();
	
private:
	TIFF * tiffImage;	
	QImage * image = nullptr;
	
	ImagePainter * painter;
	
	void openGrayscaleSelectionWindow(int channelsCount);
	void openRgbSelectionWindow(int channelsCount);

	void channelsSelectedEvent();
	
	void mouseMoveEvent(QMouseEvent * event) override;
};