#pragma once

#include <QLabel>
#include <QImage>
#include <QComboBox>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

#include <string>

#include "tiff.h"

class ImageLabel: public QLabel
{
public:
	ImageLabel();
	
	QImage * image = nullptr;
	
	QDialog * channelSelectionWindow;
	QVBoxLayout * widgetsBox;
	QComboBox * channelsList;
	QPushButton * okButton;

	std::string tiffLoadPath;

	void loadTIFF(std::string loadPath, int channelNumber);
	void saveTIFF(std::string loadPath);
	
	void updateImage();

	void clearImageLabel();
	
private:
	TIFF tiffImage;	
	
	void openChannelSelectionWindow(int channelsCount);
	
	void channelSelectedEventHandler();
};