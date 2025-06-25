#include "../../include/channelSelectionWindow.h"

#include <QMessageBox>
#include <iostream>

ChannelSelectionWindow::ChannelSelectionWindow(QWidget * parent = nullptr) : QDialog(parent)
{
    this->setFixedSize(400, 100);
	this->setWindowModality(Qt::WindowModality::WindowModal);
	
    okButton = new QPushButton();
	okButton->setText("Загрузить канал");
    connect(okButton, &QPushButton::clicked, this, &ChannelSelectionWindow::channelSelectedEvent);
			
	vWidgetsBox = new QVBoxLayout(this);
}

void ChannelSelectionWindow::createGrayscaleChannelSelector(int channelsCount)
{
    this->setWindowTitle("Grayscale");

    grayscaleChannelsList = new QComboBox();
    
    for(int channelNumber = 1; channelNumber < channelsCount; channelNumber++)
	{
	    grayscaleChannelsList->addItem(QString::fromStdString(std::to_string(channelNumber)));
	}
	
	vWidgetsBox->addWidget(grayscaleChannelsList);
	vWidgetsBox->addWidget(okButton);
	
	isGrayscaleChannel = true;
}

void ChannelSelectionWindow::createRgbChannelSelector(int channelsCount)
{
    this->setWindowTitle("RGB");

    redChannelsList = new QComboBox();
    greenChannelsList = new QComboBox();
    blueChannelsList = new QComboBox();
    
	for(int channelNumber = 1; channelNumber < channelsCount; channelNumber++)
	{
	    redChannelsList->addItem(QString::fromStdString(std::to_string(channelNumber)));
	    greenChannelsList->addItem(QString::fromStdString(std::to_string(channelNumber)));
	    blueChannelsList->addItem(QString::fromStdString(std::to_string(channelNumber)));
	}
	
	QHBoxLayout * hWidgetBox = new QHBoxLayout();
	
	hWidgetBox->addWidget(redChannelsList);
	hWidgetBox->addWidget(greenChannelsList);
	hWidgetBox->addWidget(blueChannelsList);
	
	vWidgetsBox->addLayout(hWidgetBox);
	vWidgetsBox->addWidget(okButton);
	
	isGrayscaleChannel = false;
}

RgbChannels ChannelSelectionWindow::getSelectedChannels()
{
    if(isGrayscaleChannel)
        
        return RgbChannels
        {
            grayscaleChannelsList->currentText().toInt() - 1,
            grayscaleChannelsList->currentText().toInt() - 1,
            grayscaleChannelsList->currentText().toInt() - 1
        };
    else
        return RgbChannels
        {
            redChannelsList->currentText().toInt() - 1,
            greenChannelsList->currentText().toInt() - 1,
            blueChannelsList->currentText().toInt() - 1
        };
}

void ChannelSelectionWindow::setChannelSelectedEvent(std::function<void()> eventHandler)
{
    channelSelectedEventHandler = eventHandler;
}

void ChannelSelectionWindow::channelSelectedEvent()
{
    channelSelectedEventHandler();
}