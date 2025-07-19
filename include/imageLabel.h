#pragma once

#include <QLabel>
#include <QImage>
#include <QComboBox>
#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QMenu>
#include <QPoint>

#include <string>
#include <fstream>

#include "tiff.h"
#include "rgb.h"
#include "bmp.h"

#include "imagePainter.h"
#include "imageConverter.h"

#include "pixelStatusBar.h"
#include "histogramPanel.h"
#include "channelSelectionWindow.h"
#include "contrastingWindow.h"

#include "sppTable.h"

class ImageLabel: public QLabel
{
public:
	ImageLabel();
	
	ChannelSelectionWindow * channelSelector;
	ContrastingWindow * contrastingWin;
	
	PixelStatusBar * statusBar;
	
	HistogramPanel * histrogram;

	std::string tiffPath;

	void loadNewTIFF(std::string loadPath);
	void loadGrayscaleTIFF();
	void loadRgbTIFF();
	
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
	
	QMenu * contextMenu;
	
	Pixel16bit minNormalizationPixel;
	Pixel16bit maxNormalizationPixel;
	
	SppTable * sppTable;
	
	void createContextMenu();
	
	void loadSppTable();
	void requestSppFilePath();
	
	void openGrayscaleSelectionWindow(int channelsCount);
	void openRgbSelectionWindow(int channelsCount);

	void grayScaleSelectedEvent();
	void rgbSelectedEvent();
	void standartContrastingEvent();
	void histogramContrastingEvent();
	
	void resetContrastingParams();
	
	void showChannelsInfo();
	
	void mouseMoveEvent(QMouseEvent * event) override;
	void mouseReleaseEvent(QMouseEvent * event) override;
};