#include "../../include/calibrationWindow.h"

void fillLabelByStringsList(QLabel * label, QList<QString> & strings);

CalibrationWindow::CalibrationWindow(QWidget * parent = nullptr): QDialog(parent)
{
	this->setWindowModality(Qt::WindowModality::WindowModal);
	this->setWindowTitle("Калибровка");
    this->setFixedSize(800, 400);
		
	vWidgetsBox = new QVBoxLayout(this);
    
	createDirectorySelectionWidgets();
	createDateSelectionWidgets();
	createCoordinatesFormatWidgets();
	createCoordinatesSelectionWidgets();
    createOutputPanel();
    
} 

void CalibrationWindow::createDirectorySelectionWidgets()
{
	directoryLabel = new QLabel();
	directoryLabel->setStyleSheet("border: 1px solid black");
	
	selectDirectoryButton = new QPushButton("...");
	selectDirectoryButton->setFixedWidth(50);
	
    connect(selectDirectoryButton, &QPushButton::clicked, this, &CalibrationWindow::openDirectoryEvent);

    QLabel * text = new QLabel("Путь к директории для поиска");
    text->setAlignment(Qt::AlignCenter);
    
    QHBoxLayout * row = new QHBoxLayout();
    
    vWidgetsBox->addWidget(text);
    row->addWidget(directoryLabel);
    row->addWidget(selectDirectoryButton);
    
    vWidgetsBox->addLayout(row);
}

void CalibrationWindow::createDateSelectionWidgets()
{
	startDateField = new QDateEdit();
    startTimeField = new QTimeEdit();
    endDateField = new QDateEdit();
    endTimeField = new QTimeEdit();
    
    startTimeField->setDisplayFormat("hh:mm:ss");
    endTimeField->setDisplayFormat("hh:mm:ss");
    
    QLabel * startDateText = new QLabel("Дата начала");
    QLabel * startTimeText = new QLabel("Время начала");
    QLabel * endDateText = new QLabel("Дата конца");
    QLabel * endTimeText = new QLabel("Время конца");
    
    QGridLayout * dateSelectionTable = new QGridLayout();
    
    dateSelectionTable->addWidget(startDateText, 0, 0);
    dateSelectionTable->addWidget(startTimeText, 0, 1);
    dateSelectionTable->addWidget(endDateText, 0, 2);
    dateSelectionTable->addWidget(endTimeText, 0, 3);
    dateSelectionTable->addWidget(startDateField, 1, 0);
    dateSelectionTable->addWidget(startTimeField, 1, 1);
    dateSelectionTable->addWidget(endDateField, 1, 2);
    dateSelectionTable->addWidget(endTimeField, 1, 3);
    
    vWidgetsBox->addLayout(dateSelectionTable);
}

void CalibrationWindow::createCoordinatesFormatWidgets()
{
	ddFormFlag = new QRadioButton("DD.DDDD");
	ddmmssFormFlag = new QRadioButton("DDMMSS");
	kmlFormFlag = new QRadioButton("KML");
	ddFormFlag->setChecked(true);
	
	QButtonGroup * formatButtons = new QButtonGroup();
	formatButtons->addButton(ddFormFlag);
	formatButtons->addButton(ddmmssFormFlag);
	formatButtons->addButton(kmlFormFlag);

	QLabel * formatText = new QLabel("Формат координат:");

    QHBoxLayout * row1 = new QHBoxLayout();
    row1->addWidget(formatText);
    row1->addWidget(ddFormFlag);
    row1->addWidget(ddmmssFormFlag);
    row1->addWidget(kmlFormFlag);
    
    row1->addStretch();
    
    twoCoordsFlag = new QRadioButton("2 координаты");
    fourCoordsFlag = new QRadioButton("4 координаты");
    fourCoordsFlag->setChecked(true);
    
    QButtonGroup * countButtons = new QButtonGroup();
    countButtons->addButton(twoCoordsFlag, 0);
    countButtons->addButton(fourCoordsFlag, 1);
    
    connect(countButtons, &QButtonGroup::idClicked, this, &CalibrationWindow::switchCoordinatesSelection);
    
	QLabel * countText = new QLabel("Количество координат:");
    
    QHBoxLayout * row2 = new QHBoxLayout();
    row2->addWidget(countText);
    row2->addWidget(twoCoordsFlag);
    row2->addWidget(fourCoordsFlag);
    
    row2->addStretch();
    
    vWidgetsBox->addLayout(row1);
    vWidgetsBox->addLayout(row2);
}

void CalibrationWindow::createCoordinatesSelectionWidgets()
{
    QLabel * text = new QLabel("Десятичные градусы");
    
    twoCoordsPanel = new QGridLayout();
    xField = new QLineEdit();
    yField = new QLineEdit();
    
    xFieldText = new QLabel("x");
    yFieldText = new QLabel("y");
    xFieldText->setAlignment(Qt::AlignCenter);
    yFieldText->setAlignment(Qt::AlignCenter);
    xField->setFixedWidth(100);
    yField->setFixedWidth(100);
    
    twoCoordsPanel->addWidget(xFieldText, 0, 0);
    twoCoordsPanel->addWidget(yFieldText, 0, 1);
    twoCoordsPanel->addWidget(xField, 1, 0);
    twoCoordsPanel->addWidget(yField, 1, 1);
    
    fourCoordsPanel = new QGridLayout();
    x1Field = new QLineEdit();
    x2Field = new QLineEdit();
    y1Field = new QLineEdit();
    y2Field = new QLineEdit();
    x1Field->setFixedWidth(100);
    x2Field->setFixedWidth(100);
    y1Field->setFixedWidth(100);
    y2Field->setFixedWidth(100);
            
    x1FieldText = new QLabel("x1");
    y1FieldText = new QLabel("y1");
    x2FieldText = new QLabel("x2");
    y2FieldText = new QLabel("y2");
    x1FieldText->setAlignment(Qt::AlignCenter);
    x2FieldText->setAlignment(Qt::AlignCenter);
    y1FieldText->setAlignment(Qt::AlignCenter);
    y2FieldText->setAlignment(Qt::AlignCenter);
    
    fourCoordsPanel->addWidget(x1FieldText, 0, 0);
    fourCoordsPanel->addWidget(y1FieldText, 0, 1);
    fourCoordsPanel->addWidget(x2FieldText, 0, 2);
    fourCoordsPanel->addWidget(y2FieldText, 0, 3);
    fourCoordsPanel->addWidget(x1Field, 1, 0);
    fourCoordsPanel->addWidget(y1Field, 1, 1);
    fourCoordsPanel->addWidget(x2Field, 1, 2);
    fourCoordsPanel->addWidget(y2Field, 1, 3);
    
    vWidgetsBox->addLayout(twoCoordsPanel);
    vWidgetsBox->addLayout(fourCoordsPanel);
    
    switchCoordinatesSelection(1);
}

void CalibrationWindow::createOutputPanel()
{
    scrollArea = new QScrollArea();
    outputLabel = new QLabel();
    outputLabel->setAlignment(Qt::AlignTop);
    
    scrollArea->setWidget(outputLabel);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    
    vWidgetsBox->addWidget(scrollArea);
}

void CalibrationWindow::switchCoordinatesSelection(int id)
{
    switch(id)
    {
        case 0:
            setTwoCoordsPanelVisible(true);
            setFourCoordsPanelVisible(false);
            break;
        case 1:
            setTwoCoordsPanelVisible(false);
            setFourCoordsPanelVisible(true);
            break;
    }
}

void CalibrationWindow::setTwoCoordsPanelVisible(bool isVisible)
{
    xField->setVisible(isVisible);
    yField->setVisible(isVisible);
    
    xFieldText->setVisible(isVisible);
    yFieldText->setVisible(isVisible);
}

void CalibrationWindow::setFourCoordsPanelVisible(bool isVisible)
{
    x1Field->setVisible(isVisible);
    x2Field->setVisible(isVisible);
    y1Field->setVisible(isVisible);
    y2Field->setVisible(isVisible);
    
    x1FieldText->setVisible(isVisible);
    x2FieldText->setVisible(isVisible);
    y1FieldText->setVisible(isVisible);
    y2FieldText->setVisible(isVisible);
}

void CalibrationWindow::openDirectoryEvent()
{
	QString directoryPath = QFileDialog::getExistingDirectory(this, "Открыть папку", "./");
    
    if(directoryPath.isEmpty())
        return;
        
    directoryLabel->setText(directoryPath);
    
    QList<QString> files = DirectoryReader::readDirectory(directoryPath, {"*.spp"});
    
    fillLabelByStringsList(outputLabel, files);
    
}

void fillLabelByStringsList(QLabel * label, QList<QString> & strings)
{
    label->clear();
    if(strings.isEmpty())
    {
        label->setText("Ничего не найдено");
        return;
    }

    for(QString str : strings)
    {
        label->setText(label->text() + str + '\n');
    }
}