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
	
	void updateImage();

	void clearImageLabel();
	
	bool hasImage();
	
private:
	TIFF * image16bit;	
	QImage * image8bit;
	
	ImagePainter * painter;
	
	QMenu * contextMenu;
	
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
	
	uint16_t findMinContrasingValue(float leftCuttingPercent);
	uint16_t findMaxContrasingValue(float rightCuttingPersent);
	
	void resetContrastingParams();
	
	void showChannelsInfo();
	
	void mouseMoveEvent(QMouseEvent * event) override;
	void mouseReleaseEvent(QMouseEvent * event) override;
};