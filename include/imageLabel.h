#pragma once

#include <QLabel>
#include <QImage>
#include <QComboBox>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <string>
#include <fstream>

#include "tiff.h"
#include "pixelsNormalizer.h"

class ImageLabel: public QLabel
{
public:
	ImageLabel();
	
	QImage * image = nullptr;
	
	QDialog * channelSelectionWindow;
	QVBoxLayout * vWidgetsBox;
	QComboBox * grayscaleChannelsList;
	
	QHBoxLayout * hWidgetBox;
	QComboBox * redChannelsList;
	QComboBox * greenChannelsList;
	QComboBox * blueChannelsList;
	
	QPushButton * okButton;

	std::string tiffLoadPath;

	void loadGrayscaleTIFF(std::string loadPath);
	void loadRgbTIFF(std::string loadPath);
	
	void updateImage();

	void clearImageLabel();
	
private:
	TIFF * tiffImage;	
	
	void openGrayscaleSelectionWindow(int channelsCount);
	void openRgbSelectionWindow(int channelsCount);
	
	void channelSelectedEvent();
	void rgbSelectedEvent();
};