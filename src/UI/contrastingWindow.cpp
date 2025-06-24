#include "../../include/contrastingWindow.h"

ContrastingWindow::ContrastingWindow(QWidget * parent = nullptr) : QDialog(parent)
{
    this->setFixedSize(400, 100);
	this->setWindowModality(Qt::WindowModality::WindowModal);
	
    minValueText = new QLabel("Минимальное значение");
	maxValueText = new QLabel("Максимальное значение");
	
	textBox = new QHBoxLayout();
	
	textBox->addWidget(minValueText);
	textBox->addWidget(maxValueText);
	
    okButton = new QPushButton();
	okButton->setText("Выполнить контрастирование");
    connect(okButton, &QPushButton::clicked, this, &ContrastingWindow::contrastingEvent);
    
	
	vWidgetsBox = new QVBoxLayout(this);
	vWidgetsBox->addLayout(textBox);
}

void ContrastingWindow::createGrayscaleContrastingWindow()
{
	this->setWindowTitle("Контрастирование Grayscale");

	QHBoxLayout * entryBox = new QHBoxLayout();
	
    grayscaleMinContastingEntry = new QLineEdit();
	grayscaleMaxContastingEntry = new QLineEdit();
	
	entryBox->addWidget(grayscaleMinContastingEntry);
	entryBox->addWidget(grayscaleMaxContastingEntry);
	
	vWidgetsBox->addLayout(entryBox);
	vWidgetsBox->addWidget(okButton);
	
	isGrayscaleContrasting = true;
}

void ContrastingWindow::createRgbContrastingWindow()
{
	this->setFixedHeight(200);
	
    QHBoxLayout * redEntryBox = new QHBoxLayout();
    QHBoxLayout * greenEntryBox = new QHBoxLayout();
    QHBoxLayout * blueEntryBox = new QHBoxLayout();
    
    QLabel * redText = new QLabel("R");
	QLabel * greenText = new QLabel("G");
	QLabel * blueText = new QLabel("B");
	
	redMinContastingEntry = new QLineEdit();
	redMaxContastingEntry = new QLineEdit();
	greenMinContastingEntry = new QLineEdit();
	greenMaxContastingEntry = new QLineEdit();
	blueMinContastingEntry = new QLineEdit();
	blueMaxContastingEntry = new QLineEdit();
	
	redEntryBox->addWidget(redText);
	redEntryBox->addWidget(redMinContastingEntry);
	redEntryBox->addWidget(redMaxContastingEntry);
	
	greenEntryBox->addWidget(greenText);
	greenEntryBox->addWidget(greenMinContastingEntry);
	greenEntryBox->addWidget(greenMaxContastingEntry);
	
	blueEntryBox->addWidget(blueText);
	blueEntryBox->addWidget(blueMinContastingEntry);
	blueEntryBox->addWidget(blueMaxContastingEntry);

	textBox->setAlignment(minValueText, Qt::AlignCenter);
	textBox->setAlignment(maxValueText, Qt::AlignCenter);

	vWidgetsBox->addLayout(redEntryBox);
	vWidgetsBox->addLayout(greenEntryBox);
	vWidgetsBox->addLayout(blueEntryBox);
	vWidgetsBox->addWidget(okButton);
	
	isGrayscaleContrasting = false;
}

void ContrastingWindow::createHistogramContrastingWindow()
{
	histogramCuttingPercentEntry = new QLineEdit();
	
	vWidgetsBox->addWidget(histogramCuttingPercentEntry);
	vWidgetsBox->addWidget(okButton);
}

Pixel16bit ContrastingWindow::getMinPixelParameters()
{
	if(isGrayscaleContrasting)
		return Pixel16bit
		{
			(uint16_t)(grayscaleMinContastingEntry->text().toUInt()),
			(uint16_t)(grayscaleMinContastingEntry->text().toUInt()),
			(uint16_t)(grayscaleMinContastingEntry->text().toUInt())
		};
	else
		return Pixel16bit
		{
			(uint16_t)(redMinContastingEntry->text().toUInt()),
			(uint16_t)(greenMinContastingEntry->text().toUInt()),
			(uint16_t)(blueMinContastingEntry->text().toUInt())
		};
}

Pixel16bit ContrastingWindow::getMaxPixelParameters()
{
	if(isGrayscaleContrasting)
		return Pixel16bit
		{
			(uint16_t)(grayscaleMaxContastingEntry->text().toUInt()),
			(uint16_t)(grayscaleMaxContastingEntry->text().toUInt()),
			(uint16_t)(grayscaleMaxContastingEntry->text().toUInt())
		};
	return Pixel16bit
	{
	    (uint16_t)(redMaxContastingEntry->text().toUInt()),
		(uint16_t)(greenMaxContastingEntry->text().toUInt()),
		(uint16_t)(blueMaxContastingEntry->text().toUInt())
	};
}

float ContrastingWindow::getHistogramCuttingPercent()
{
    return histogramCuttingPercentEntry->text().toFloat() / 100.0f;
}

void ContrastingWindow::setContrastingEvent(std::function<void()> eventHandler)
{
    contrastingEventHandler = eventHandler;
}

void ContrastingWindow::contrastingEvent()
{
    contrastingEventHandler();
}