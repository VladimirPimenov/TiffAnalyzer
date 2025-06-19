#include "../../include/contrastingWindow.h"

ContrastingWindow::ContrastingWindow(QWidget * parent = nullptr) : QDialog(parent)
{
    this->setFixedSize(400, 100);
	this->setWindowModality(Qt::WindowModality::WindowModal);
	
	minContrastingValueEntry = new QLineEdit();
	maxContrastingValueEntry = new QLineEdit();
	
    okButton = new QPushButton();
	okButton->setText("Выполнить контрастирование");
    connect(okButton, &QPushButton::clicked, this, &ContrastingWindow::contrastingEvent);
			
	vWidgetsBox = new QVBoxLayout(this);
	hWidgetsBox = new QHBoxLayout();
	
	hWidgetsBox->addWidget(minContrastingValueEntry);
	hWidgetsBox->addWidget(maxContrastingValueEntry);
	
	vWidgetsBox->addLayout(hWidgetsBox);
	vWidgetsBox->addWidget(okButton);
}

uint16_t ContrastingWindow::getMinValue()
{
    return minContrastingValueEntry->text().toInt();
}

uint16_t ContrastingWindow::getMaxValue()
{
    return maxContrastingValueEntry->text().toInt();
}

void ContrastingWindow::setContrastingEvent(std::function<void()> eventHandler)
{
    contrastingEventHandler = eventHandler;
}

void ContrastingWindow::contrastingEvent()
{
    contrastingEventHandler();
}