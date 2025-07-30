#include "../../include/contrastingWindow.h"

ContrastingWindow::ContrastingWindow(QWidget * parent = nullptr) : QDialog(parent)
{
    this->setFixedSize(400, 100);
	this->setWindowModality(Qt::WindowModality::WindowModal);
	
    okButton = new QPushButton();
	okButton->setText("Выполнить контрастирование");
    connect(okButton, &QPushButton::clicked, this, &ContrastingWindow::contrastingEvent);
    
	textBox = new QHBoxLayout();
	
	vWidgetsBox = new QVBoxLayout(this);
	vWidgetsBox->addLayout(textBox);
}

void ContrastingWindow::createGrayscaleContrastingWindow()
{
	this->setWindowTitle("Контрастирование Grayscale");
	
	isGrayscaleContrasting = true;

	createTextBox();

	QHBoxLayout * entryBox = createContrastingEntryBox(new QLabel(),
													grayscaleMinContastingEntry,
													grayscaleMaxContastingEntry);
	
	vWidgetsBox->addLayout(entryBox);
	vWidgetsBox->addWidget(okButton);
}

void ContrastingWindow::createRgbContrastingWindow()
{
	this->setFixedHeight(200);
	
	isGrayscaleContrasting = false;
	
	createTextBox();
	
	textBox->setAlignment(minValueText, Qt::AlignCenter);
	textBox->setAlignment(maxValueText, Qt::AlignCenter);
	
	QHBoxLayout * redEntryBox = createContrastingEntryBox(new QLabel("R"), 
													redMinContastingEntry,
													redMaxContastingEntry);
	QHBoxLayout * greenEntryBox = createContrastingEntryBox(new QLabel("G"), 
													greenMinContastingEntry,
													greenMaxContastingEntry);
	QHBoxLayout * blueEntryBox = createContrastingEntryBox(new QLabel("B"), 
													blueMinContastingEntry,
													blueMaxContastingEntry);
	vWidgetsBox->addLayout(redEntryBox);
	vWidgetsBox->addLayout(greenEntryBox);
	vWidgetsBox->addLayout(blueEntryBox);
	vWidgetsBox->addWidget(okButton);
}

void ContrastingWindow::createHistogramContrastingWindow()
{
	this->setFixedWidth(500);

	histogramRightPercentEntry = new QLineEdit();
	histogramLeftPercentEntry = new QLineEdit();
	
	QHBoxLayout * persentEntryBox = new QHBoxLayout();
	
	persentEntryBox->addWidget(histogramLeftPercentEntry);
	persentEntryBox->addWidget(histogramRightPercentEntry);
	
	QLabel * text = new QLabel("Введите процент обрезки гистограммы слева и справа по количеству пикселей");
	textBox->addWidget(text);
	textBox->setAlignment(text, Qt::AlignCenter);
	
	vWidgetsBox->addLayout(persentEntryBox);
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

float ContrastingWindow::getRightCuttingPercent()
{
    return histogramRightPercentEntry->text().toFloat();
}

float ContrastingWindow::getLeftCuttingPercent()
{
    return histogramLeftPercentEntry->text().toFloat();
}

void ContrastingWindow::createTextBox()
{
    minValueText = new QLabel("Минимальное значение");
	maxValueText = new QLabel("Максимальное значение");
	
	textBox->addWidget(minValueText);
	textBox->addWidget(maxValueText);
}

QHBoxLayout * ContrastingWindow::createContrastingEntryBox(QLabel * text, QLineEdit *& minEntry, QLineEdit *& maxEntry)
{
	minEntry = new QLineEdit();
	maxEntry = new QLineEdit();

    QHBoxLayout * entryBox = new QHBoxLayout();
    
    entryBox->addWidget(text);
    entryBox->addWidget(minEntry);
    entryBox->addWidget(maxEntry);
    
    return entryBox;
}

void ContrastingWindow::setContrastingEvent(std::function<void()> eventHandler)
{
    contrastingEventHandler = eventHandler;
}

void ContrastingWindow::contrastingEvent()
{
    contrastingEventHandler();
}