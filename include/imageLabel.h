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
#include "instrumentsPanel.h"

#include "channelSelectionWindow.h"
#include "contrastingWindow.h"

#include "sppTable.h"

#include "pixelReader.h"
#include "histogramCalculator.h"

class ImageLabel: public QLabel
{
public:
	ImageLabel();
	
	void loadNewTIFF(std::string loadPath);
	void loadGrayscaleTIFF();
	void loadRgbTIFF();
	
	void linkInstrumentsPanel(InstrumentsPanel * instrumentsPanel);
	void linkPixelStatusBar(PixelStatusBar * statusBar);
	
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
	HistogramCalculator * histogramCalculator;
	
	ChannelSelectionWindow * channelSelector;
	ContrastingWindow * contrastingWin;
	InstrumentsPanel * instrumentsPanel;
	PixelStatusBar * statusBar;
	
	QMenu * contextMenu;
	
	SppTable * sppTable;
	
	void createContextMenu();
	
	void loadSppTable();
	void requestSppFilePath();
	
	void updateHistogram();
	
	void openGrayscaleSelectionWindow(int channelsCount);
	void openRgbSelectionWindow(int channelsCount);

	void grayScaleSelectedEvent();
	void rgbSelectedEvent();
	void standartContrastingEvent();
	void histogramContrastingEvent();
	
	void resetContrastingParams();
	
	void showChannelsInfo();

	void updatePixelGraphic(int x, int y, bool addNew);
	
	void mouseMoveEvent(QMouseEvent * event) override;
	void mouseReleaseEvent(QMouseEvent * event) override;
};