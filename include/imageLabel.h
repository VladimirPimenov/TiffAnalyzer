#pragma once

#include <QLabel>
#include <QImage>
#include <QMouseEvent>
#include <QMenu>
#include <QPoint>

#include <string>

#include "tiff.h"

class ImageLabel: public QLabel
{
public:
	ImageLabel();
	
	QImage * image = nullptr;

	void loadTIFF(std::string loadPath, int channelNumber);
	void saveTIFF(std::string loadPath);
	
	void updateImage();

	void clearImageLabel();
	
private:
	TIFF tiffImage;	
};