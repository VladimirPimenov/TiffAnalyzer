#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>

#include <functional>

#include "rgb.h"

class ChannelSelectionWindow: public QDialog
{
public:
    ChannelSelectionWindow(QWidget * parent);
    
    void createGrayscaleChannelSelector(int channelsCount);
    void createRgbChannelSelector(int channelsCount);
    
    void setChannelSelectedEvent(std::function<void()> eventHandler);
    
    RgbChannels getSelectedChannels();
    
private:
	bool isGrayscaleChannel;

	QVBoxLayout * vWidgetsBox;
	
	QComboBox * grayscaleChannelsList;
	QComboBox * redChannelsList;
	QComboBox * greenChannelsList;
	QComboBox * blueChannelsList;
	
	QPushButton * okButton;
	
	std::function<void()> channelSelectedEventHandler;

	void showCloseMessage();

private slots:
	void channelSelectedEvent();
};