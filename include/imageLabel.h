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
#include <QMessageBox>
#include <QFileDialog>

#include <cmath>

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

#include "wavescaleTable.h"

#include "pixelReader.h"
#include "histogramCalculator.h"

class ImageLabel: public QLabel
{
public:
	ImageLabel(PixelStatusBar * statusBar, InstrumentsPanel * instrumentsPanel);
	
	void loadTIFF(QString tiffPath);
	void setWavescaleTable(WavescaleTable * table);
	
	void saveImageAsBmp(std::string savePath);
	
	void standartContrasting();
	void histogramContrasting();
	void resetContrasting();
	
	void updateImage();
	
	void clearImageLabel();
	
	bool hasImage();
	
private:
	Tiff * image16bit;	
	QImage * image8bit;
	
	ImagePainter * painter;
	HistogramCalculator * histogramCalculator;
	
	ChannelSelectionWindow * channelSelector;
	ContrastingWindow * contrastingWin;
	InstrumentsPanel * instrumentsPanel;
	PixelStatusBar * statusBar;
	
	QMenu * contextMenu;
	
	WavescaleTable * wavescaleTable;
	
	void loadGrayscaleTIFF();
	void loadRgbTIFF();
	
	void createContextMenu();
	
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