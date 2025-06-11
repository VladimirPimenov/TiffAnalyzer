#include "../../include/imageLabel.h"

ImageLabel::ImageLabel(): QLabel(){}

void ImageLabel::loadGrayscaleTIFF(std::string loadPath)
{
	tiffLoadPath = loadPath;
	
	tiffImage = new TIFF();
	
	tiffImage->loadTiffMetadata(tiffLoadPath);
	
	openGrayscaleSelectionWindow(tiffImage->channelsCount);
}

void ImageLabel::loadRgbTIFF(std::string loadPath)
{
	tiffLoadPath = loadPath;
	
	tiffImage->loadTiffMetadata(tiffLoadPath);
	
    openRgbSelectionWindow(tiffImage->channelsCount);
}

void ImageLabel::openGrayscaleSelectionWindow(int channelsCount)
{
	channelSelectionWindow = new QDialog(this);
	
	channelSelectionWindow->setWindowTitle("Grayscale");
	channelSelectionWindow->resize(500, channelSelectionWindow->width());	
	channelSelectionWindow->resize(50, channelSelectionWindow->height());	
	channelSelectionWindow->setWindowModality(Qt::WindowModality::WindowModal);
	
	okButton = new QPushButton();
	
	okButton->setText("Загрузить канал");
	connect(okButton, &QPushButton::clicked, this, &ImageLabel::channelSelectedEvent);
	
    grayscaleChannelsList = new QComboBox();
    
	for(int channelNumber = 1; channelNumber < channelsCount; channelNumber++)
	{
	    grayscaleChannelsList->addItem(QString::fromStdString(std::to_string(channelNumber)));
	}
	
	vWidgetsBox = new QVBoxLayout(channelSelectionWindow);
	
	vWidgetsBox->addWidget(grayscaleChannelsList);
	vWidgetsBox->addWidget(okButton);
	
	channelSelectionWindow->show();
}

void ImageLabel::openRgbSelectionWindow(int channelsCount)
{
    channelSelectionWindow = new QDialog(this);
	
	channelSelectionWindow->setWindowTitle("Grayscale");
	channelSelectionWindow->resize(500, channelSelectionWindow->width());	
	channelSelectionWindow->resize(50, channelSelectionWindow->height());	
	channelSelectionWindow->setWindowModality(Qt::WindowModality::WindowModal);
	
	okButton = new QPushButton();
	
	okButton->setText("Загрузить каналы");
	connect(okButton, &QPushButton::clicked, this, &ImageLabel::rgbSelectedEvent);
	
    redChannelsList = new QComboBox();
    greenChannelsList = new QComboBox();
    blueChannelsList = new QComboBox();
    
	for(int channelNumber = 1; channelNumber < channelsCount; channelNumber++)
	{
	    redChannelsList->addItem(QString::fromStdString(std::to_string(channelNumber)));
	    greenChannelsList->addItem(QString::fromStdString(std::to_string(channelNumber)));
	    blueChannelsList->addItem(QString::fromStdString(std::to_string(channelNumber)));
	}
	
	vWidgetsBox = new QVBoxLayout(channelSelectionWindow);
	hWidgetBox = new QHBoxLayout();
	
	hWidgetBox->addWidget(redChannelsList);
	hWidgetBox->addWidget(greenChannelsList);
	hWidgetBox->addWidget(blueChannelsList);
	
	vWidgetsBox->addLayout(hWidgetBox);
	vWidgetsBox->addWidget(okButton);
	
	channelSelectionWindow->show();
}

void ImageLabel::updateImage()
{
	PixelsNormalizer::normalizePixelValues(tiffImage);

	image = new QImage(tiffImage->width, tiffImage->height, QImage::Format_RGB888);
	
	for(int y = 0; y < tiffImage->height; y++)
	{
		for(int x = 0; x < tiffImage->width; x++)
		{
			(*image).setPixel(x, y, qRgb(tiffImage->pixels[y][x].red, tiffImage->pixels[y][x].green, tiffImage->pixels[y][x].blue));
		}
	}
	
	
	setPixmap(QPixmap::fromImage(*image));
}

void ImageLabel::channelSelectedEvent()
{
    int channel = grayscaleChannelsList->currentText().toInt() - 1;
    
    channelSelectionWindow->close();
    
	tiffImage->loadGrayscale(tiffLoadPath, channel);
	updateImage();
}

void ImageLabel::rgbSelectedEvent()
{
    int redChannel = redChannelsList->currentText().toInt() - 1;
    int greenChannel = greenChannelsList->currentText().toInt() - 1;
    int blueChannel = blueChannelsList->currentText().toInt() - 1;
    
    RgbChannels channels = {redChannel, greenChannel, blueChannel};
    
    channelSelectionWindow->close();
    
    tiffImage->loadRgb(tiffLoadPath, channels);
    updateImage();
}


void ImageLabel::clearImageLabel()
{
	this->clear();
    image = nullptr;
    tiffImage->~TIFF();
}