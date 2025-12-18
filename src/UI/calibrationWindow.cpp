#include "../../include/calibrationWindow.h"

void fillLabelByStringsList(QLabel * label, QStringList * strings)
{
    label->clear();
    if(strings->isEmpty())
    {
        label->setText("Ничего не найдено");
        return;
    }

    for(QString str : *strings)
    {
        label->setText(label->text() + str + '\n');
    }
}

CalibrationWindow::CalibrationWindow(QWidget * parent = nullptr): QDialog(parent)
{
	this->setWindowModality(Qt::WindowModality::WindowModal);
	this->setWindowTitle("Калибровка");
    this->setFixedSize(800, 500);
		
	vWidgetsBox = new QVBoxLayout(this);
	coordsInputTable = new QVBoxLayout();
	kmlTable = new QVBoxLayout();
    
	createDirectorySelectionWidgets();
	createDateSelectionWidgets();
	createInputTypeWidgets();
	
	createCoordinatesFormatWidgets();
	createCoordinatesSelectionWidgets();
	vWidgetsBox->addLayout(coordsInputTable);
	
	createKmlCoordsWidgets();
	vWidgetsBox->addLayout(kmlTable);
	
    createOutputPanel();
    
    switchInputTypeSelection(0);
    switchCoordinatesSelection(0);
} 

void CalibrationWindow::createDirectorySelectionWidgets()
{
	routeDirectoryLabel = new QLabel();
	routeDirectoryLabel->setStyleSheet("border: 1px solid black");
	
	selectDirectoryButton = new QPushButton("Выбрать путь");
	selectDirectoryButton->setFixedWidth(100);
	
    connect(selectDirectoryButton, &QPushButton::clicked, this, &CalibrationWindow::openRouteDirectoryEvent);

    QLabel * text = new QLabel("Путь к директории для поиска");
    text->setAlignment(Qt::AlignCenter);
    
    QHBoxLayout * row = new QHBoxLayout();
    
    vWidgetsBox->addWidget(text);
    row->addWidget(routeDirectoryLabel);
    row->addWidget(selectDirectoryButton);
    
    vWidgetsBox->addLayout(row);
}

void CalibrationWindow::createDateSelectionWidgets()
{
	startDateField = new QDateEdit(QDate::currentDate());
    startTimeField = new QTimeEdit(QTime::currentTime());
    endDateField = new QDateEdit(QDate::currentDate().addMonths(1));
    endTimeField = new QTimeEdit(QTime::currentTime());
    
    connect(startDateField, &QDateEdit::dateChanged, this, &CalibrationWindow::routeSearchEvent);
    connect(startTimeField, &QTimeEdit::timeChanged, this, &CalibrationWindow::routeSearchEvent);
    connect(endDateField, &QDateEdit::dateChanged, this, &CalibrationWindow::routeSearchEvent);
    connect(endTimeField, &QTimeEdit::timeChanged, this, &CalibrationWindow::routeSearchEvent);
    
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

void CalibrationWindow::createInputTypeWidgets()
{
    QLabel * text = new QLabel("Ввод координат: ");

    userInputFlag = new QRadioButton("Ручной ввод координат");
    kmlInputFlag = new QRadioButton("Загрузка координат из KML");
    userInputFlag->setChecked(true);
    
	QButtonGroup * inputTypeButtons = new QButtonGroup();
    inputTypeButtons->addButton(userInputFlag, 0);
    inputTypeButtons->addButton(kmlInputFlag, 1);
    
    connect(inputTypeButtons, &QButtonGroup::idClicked, this, &CalibrationWindow::switchInputTypeSelection);
    
    QHBoxLayout * row = new QHBoxLayout();
    row->addWidget(text);
    row->addWidget(userInputFlag);
    row->addWidget(kmlInputFlag);
    
    row->addStretch();
    
    vWidgetsBox->addLayout(row);
}

void CalibrationWindow::createCoordinatesFormatWidgets()
{
	ddFormFlag = new QRadioButton("DD.DDDD");
	ddmmssFormFlag = new QRadioButton("DDMMSS");
	kmlFormFlag = new QRadioButton("KML");
	kmlFormFlag->setChecked(true);
	
	QButtonGroup * formatButtons = new QButtonGroup();
	formatButtons->addButton(ddFormFlag);
	formatButtons->addButton(ddmmssFormFlag);
	formatButtons->addButton(kmlFormFlag);
	
    connect(formatButtons, &QButtonGroup::idClicked, this, &CalibrationWindow::routeSearchEvent);

	coordsFormatText = new QLabel("Формат координат:");

    QHBoxLayout * row1 = new QHBoxLayout();
    row1->addWidget(coordsFormatText);
    row1->addWidget(ddFormFlag);
    row1->addWidget(ddmmssFormFlag);
    row1->addWidget(kmlFormFlag);
    
    row1->addStretch();
    
    twoCoordsFlag = new QRadioButton("2 координаты");
    fourCoordsFlag = new QRadioButton("4 координаты");
    twoCoordsFlag->setChecked(true);
    
    QButtonGroup * countButtons = new QButtonGroup();
    countButtons->addButton(twoCoordsFlag, 0);
    countButtons->addButton(fourCoordsFlag, 1);
    
    connect(countButtons, &QButtonGroup::idClicked, this, &CalibrationWindow::switchCoordinatesSelection);
    
	coordsCountText = new QLabel("Количество координат:");
    
    QHBoxLayout * row2 = new QHBoxLayout();
    row2->addWidget(coordsCountText);
    row2->addWidget(twoCoordsFlag);
    row2->addWidget(fourCoordsFlag);
    
    row2->addStretch();
    
    coordsInputTable->addLayout(row1);
    coordsInputTable->addLayout(row2);
}

void CalibrationWindow::createCoordinatesSelectionWidgets()
{
    QLabel * text = new QLabel("Десятичные градусы");
    
    QGridLayout * twoCoordsPanel = new QGridLayout();
    xField = new QLineEdit(this);
    yField = new QLineEdit(this);
    
    connect(xField, &QLineEdit::textChanged, this, &CalibrationWindow::routeSearchEvent);
    connect(yField, &QLineEdit::textChanged, this, &CalibrationWindow::routeSearchEvent);
    
    xFieldText = new QLabel("x", this);
    yFieldText = new QLabel("y", this);
    xFieldText->setAlignment(Qt::AlignCenter);
    yFieldText->setAlignment(Qt::AlignCenter);
    xField->setFixedWidth(100);
    yField->setFixedWidth(100);
    
    twoCoordsPanel->addWidget(xFieldText, 0, 0);
    twoCoordsPanel->addWidget(yFieldText, 0, 1);
    twoCoordsPanel->addWidget(xField, 1, 0);
    twoCoordsPanel->addWidget(yField, 1, 1);
    
    QGridLayout * fourCoordsPanel = new QGridLayout();
    x1Field = new QLineEdit(this);
    x2Field = new QLineEdit(this);
    y1Field = new QLineEdit(this);
    y2Field = new QLineEdit(this);
    x1Field->setFixedWidth(100);
    x2Field->setFixedWidth(100);
    y1Field->setFixedWidth(100);
    y2Field->setFixedWidth(100);
    
    connect(x1Field, &QLineEdit::textChanged, this, &CalibrationWindow::routeSearchEvent);
    connect(y1Field, &QLineEdit::textChanged, this, &CalibrationWindow::routeSearchEvent);
    connect(x2Field, &QLineEdit::textChanged, this, &CalibrationWindow::routeSearchEvent);
    connect(y2Field, &QLineEdit::textChanged, this, &CalibrationWindow::routeSearchEvent);
            
    x1FieldText = new QLabel("x1", this);
    y1FieldText = new QLabel("y1", this);
    x2FieldText = new QLabel("x2", this);
    y2FieldText = new QLabel("y2", this);
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
    
    coordsInputTable->addLayout(twoCoordsPanel);
    coordsInputTable->addLayout(fourCoordsPanel);
    
    switchCoordinatesSelection(1);
}

void CalibrationWindow::createKmlCoordsWidgets()
{
    kmlPathLabel = new QLabel();
	kmlPathLabel->setStyleSheet("border: 1px solid black");
    
    selectKmlButton = new QPushButton("Выбрать KML");
    selectKmlButton->setFixedWidth(100);
    
    QHBoxLayout * row = new QHBoxLayout();
    row->addWidget(kmlPathLabel);
    row->addWidget(selectKmlButton);
    
    vWidgetsBox->addLayout(row);
    
    connect(selectKmlButton, &QPushButton::clicked, this, &CalibrationWindow::openKmlEvent);

    QGridLayout * panel = new QGridLayout();
    
    corner1Text = new QLabel("Левый верхний угол");
    corner2Text = new QLabel("Правый верхний угол");
    corner3Text = new QLabel("Левый нижний угол");
    corner4Text = new QLabel("Правый нижний угол");
    
    corner1Text->setAlignment(Qt::AlignCenter);
    corner2Text->setAlignment(Qt::AlignCenter);
    corner3Text->setAlignment(Qt::AlignCenter);
    corner4Text->setAlignment(Qt::AlignCenter);
    
    kmlXText1 = new QLabel("x");
    kmlYText1 = new QLabel("y");
    kmlXText2 = new QLabel("x");
    kmlYText2 = new QLabel("y");
    kmlXText3 = new QLabel("x");
    kmlYText3 = new QLabel("y");
    kmlXText4 = new QLabel("x");
    kmlYText4 = new QLabel("y");
    
    kmlXText1->setAlignment(Qt::AlignCenter);
    kmlYText1->setAlignment(Qt::AlignCenter);
    kmlXText2->setAlignment(Qt::AlignCenter);
    kmlYText2->setAlignment(Qt::AlignCenter);
    kmlXText3->setAlignment(Qt::AlignCenter);
    kmlYText3->setAlignment(Qt::AlignCenter);
    kmlXText4->setAlignment(Qt::AlignCenter);
    kmlYText4->setAlignment(Qt::AlignCenter);

    leftUpperCornerX = new QLabel("0.0");
    leftUpperCornerY = new QLabel("0.0");
    rightUpperCornerX = new QLabel("0.0");
    rightUpperCornerY = new QLabel("0.0");
    leftLowerCornerX = new QLabel("0.0");
    leftLowerCornerY = new QLabel("0.0");
    rightLowerCornerX = new QLabel("0.0");
    rightLowerCornerY = new QLabel("0.0");
    
    leftUpperCornerX->setAlignment(Qt::AlignCenter);
    leftUpperCornerY->setAlignment(Qt::AlignCenter);
    rightUpperCornerX->setAlignment(Qt::AlignCenter);
    rightUpperCornerY->setAlignment(Qt::AlignCenter);
    leftLowerCornerX->setAlignment(Qt::AlignCenter);
    leftLowerCornerY->setAlignment(Qt::AlignCenter);
    rightLowerCornerX->setAlignment(Qt::AlignCenter);
    rightLowerCornerY->setAlignment(Qt::AlignCenter);
    
    leftUpperCornerX->setFixedWidth(100);
    leftUpperCornerY->setFixedWidth(100);
    rightUpperCornerX->setFixedWidth(100);
    rightUpperCornerY->setFixedWidth(100);
    leftLowerCornerX->setFixedWidth(100);
    leftLowerCornerY->setFixedWidth(100);
    rightLowerCornerX->setFixedWidth(100);
    rightLowerCornerY->setFixedWidth(100);
    
    panel->addWidget(corner1Text, 0, 0, 1, 2);
    panel->addWidget(kmlXText1, 1, 0);
    panel->addWidget(kmlYText1, 1, 1);
    panel->addWidget(leftUpperCornerX, 2, 0);
    panel->addWidget(leftUpperCornerY, 2, 1);
    
    panel->addWidget(corner2Text, 0, 2, 1, 2);
    panel->addWidget(kmlXText2, 1, 2);
    panel->addWidget(kmlYText2, 1, 3);
    panel->addWidget(rightUpperCornerX, 2, 2);
    panel->addWidget(rightUpperCornerY, 2, 3);
    
    panel->addWidget(corner3Text, 3, 0, 1, 2);
    panel->addWidget(kmlXText3, 4, 0);
    panel->addWidget(kmlYText3, 4, 1);
    panel->addWidget(leftLowerCornerX, 5, 0);
    panel->addWidget(leftLowerCornerY, 5, 1);
    
    panel->addWidget(corner4Text, 3, 2, 1, 2);
    panel->addWidget(kmlXText4, 4, 2);
    panel->addWidget(kmlYText4, 4, 3);
    panel->addWidget(rightLowerCornerX, 5, 2);
    panel->addWidget(rightLowerCornerY, 5, 3);

    kmlTable->addLayout(panel);
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
            isOnePointChecking = true;
            break;
        case 1:
            setTwoCoordsPanelVisible(false);
            setFourCoordsPanelVisible(true);
            isOnePointChecking = false;
            break;
    }
    routeSearchEvent();
}

void CalibrationWindow::switchInputTypeSelection(int id)
{
    switch(id)
    {
        case 0:
            isUserInput = true;
            setKmlCoordsPanelVisible(false);
            switchCoordinatesSelection(isOnePointChecking ? 0 : 1);
            setCoordinatesFormatPanelVisile(true);
            break;
        case 1:
            isUserInput = false;
            setTwoCoordsPanelVisible(false);
            setFourCoordsPanelVisible(false);
            setKmlCoordsPanelVisible(true);
            setCoordinatesFormatPanelVisile(false);
            break;
    }
    routeSearchEvent();
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

void CalibrationWindow::setKmlCoordsPanelVisible(bool isVisible)
{
    kmlPathLabel->setVisible(isVisible);
    selectKmlButton->setVisible(isVisible);

    kmlXText1->setVisible(isVisible);
    kmlYText1->setVisible(isVisible);
    kmlXText2->setVisible(isVisible);
    kmlYText2->setVisible(isVisible);
    kmlXText3->setVisible(isVisible);
    kmlYText3->setVisible(isVisible);
    kmlXText4->setVisible(isVisible);
    kmlYText4->setVisible(isVisible);

    corner1Text->setVisible(isVisible);
    corner2Text->setVisible(isVisible);
    corner3Text->setVisible(isVisible);
    corner4Text->setVisible(isVisible);

    leftUpperCornerX->setVisible(isVisible);
    leftUpperCornerY->setVisible(isVisible);
    rightUpperCornerX->setVisible(isVisible);
    rightUpperCornerY->setVisible(isVisible);
    leftLowerCornerX->setVisible(isVisible);
    leftLowerCornerY->setVisible(isVisible);
    rightLowerCornerX->setVisible(isVisible);
    rightLowerCornerY->setVisible(isVisible);
}

void CalibrationWindow::setCoordinatesFormatPanelVisile(bool isVisible)
{
    ddFormFlag->setVisible(isVisible);
	ddmmssFormFlag->setVisible(isVisible);
	kmlFormFlag->setVisible(isVisible);
	
	twoCoordsFlag->setVisible(isVisible);
    fourCoordsFlag->setVisible(isVisible);
    
    coordsFormatText->setVisible(isVisible);
    coordsCountText->setVisible(isVisible);
}

void CalibrationWindow::openRouteDirectoryEvent()
{
	QString directoryPath = QFileDialog::getExistingDirectory(this, "Открыть папку", "./");
    
    if(directoryPath.isEmpty())
        return;
        
    routeDirectoryLabel->setText(directoryPath);
        
    routeSearchEvent();
}

void CalibrationWindow::openKmlEvent()
{
    QString kmlPath = QFileDialog::getOpenFileName(this, "Открыть файл", "./", "KML (*.kml)");
    
    if(kmlPath.isEmpty())
        return;
        
    kmlPathLabel->setText(kmlPath);
    
    Kml * kml = new Kml(kmlPath);
    
    qInfo().noquote() << "Открыт файл полигона KML" << kmlPath;
    
    fillKmlCornerLabels(kml);
    
    routeSearchEvent();
}

void CalibrationWindow::routeSearchEvent()
{
    QString directoryPath = routeDirectoryLabel->text();

    if(directoryPath.isEmpty())
        return;
    
    QStringList * sppList = DirectoryReader::findFilesInDirectory(directoryPath, "*.spp");
    
    qInfo().noquote() << "Выполняется поиск маршрутов в папке" << directoryPath;
    
    sppList = filterSppList(sppList);
    
    fillLabelByStringsList(outputLabel, sppList);
}

QStringList * CalibrationWindow::filterSppList(QStringList * sppList)
{
    QDateTime startDate = QDateTime(startDateField->date(), startTimeField->time());
    QDateTime endDate = QDateTime(endDateField->date(), endTimeField->time());

    if(isUserInput)
    {
        if(isOnePointChecking)
            sppList = findRoutesByPoint(sppList);
        else
            sppList = findRoutesByRectangle(sppList);
    }
    else
        sppList = findRoutesByKml(sppList);
    
    return sppList;
}

void CalibrationWindow::fillKmlCornerLabels(Kml * kml)
{
    leftUpperCornerX->setText(QString::fromStdString(std::to_string(kml->longitudes[0])));
    rightUpperCornerX->setText(QString::fromStdString(std::to_string(kml->longitudes[1])));
    leftLowerCornerX->setText(QString::fromStdString(std::to_string(kml->longitudes[2])));
    rightLowerCornerX->setText(QString::fromStdString(std::to_string(kml->longitudes[3])));
    
    leftUpperCornerY->setText(QString::fromStdString(std::to_string(kml->latitudes[0])));
    rightUpperCornerY->setText(QString::fromStdString(std::to_string(kml->latitudes[1])));
    leftLowerCornerY->setText(QString::fromStdString(std::to_string(kml->latitudes[2])));
    rightLowerCornerY->setText(QString::fromStdString(std::to_string(kml->latitudes[3])));
}

QStringList * CalibrationWindow::findRoutesByPoint(QStringList * sppList)
{
    QDateTime startDate = QDateTime(startDateField->date(), startTimeField->time());
    QDateTime endDate = QDateTime(endDateField->date(), endTimeField->time());

    QString xString = xField->text().isEmpty() ? "0.0" : xField->text().replace(',', '.');
    QString yString = yField->text().isEmpty() ? "0.0" : yField->text().replace(',', '.');

    if(ddFormFlag->isChecked())
    {
        xString = CoordsConvertor::convertDdToKml(xString);
        yString = CoordsConvertor::convertDdToKml(yString);
    }
    else if(ddmmssFormFlag->isChecked())
    {
        xString = CoordsConvertor::convertDdmmssToKml(xString);
        yString = CoordsConvertor::convertDdmmssToKml(yString);
    }
    
    return RouteFinder::findRoutesByCoordsAndData(xString.toDouble(), yString.toDouble(), startDate, endDate, sppList);
}

QStringList * CalibrationWindow::findRoutesByRectangle(QStringList * sppList)
{
    QDateTime startDate = QDateTime(startDateField->date(), startTimeField->time());
    QDateTime endDate = QDateTime(endDateField->date(), endTimeField->time());
    
    QString x1String = x1Field->text().isEmpty() ? "0.0" : x1Field->text().replace(',', '.');
    QString y1String = y1Field->text().isEmpty() ? "0.0" : y1Field->text().replace(',', '.');
    QString x2String = x2Field->text().isEmpty() ? "0.0" : x2Field->text().replace(',', '.');
    QString y2String = y2Field->text().isEmpty() ? "0.0" : y2Field->text().replace(',', '.');
    
    if(ddFormFlag->isChecked())
    {
        x1String = CoordsConvertor::convertDdToKml(x1String);
        x2String = CoordsConvertor::convertDdToKml(x2String);
        y1String = CoordsConvertor::convertDdToKml(y1String);
        y2String = CoordsConvertor::convertDdToKml(y2String);
    }
    else if(ddmmssFormFlag->isChecked())
    {
        x1String = CoordsConvertor::convertDdmmssToKml(x1String);
        x2String = CoordsConvertor::convertDdmmssToKml(x2String);
        y1String = CoordsConvertor::convertDdmmssToKml(y1String);
        y2String = CoordsConvertor::convertDdmmssToKml(y2String);
    }
    
    return RouteFinder::findRoutesByCoordsAndData(x1String.toDouble(), y1String.toDouble(), 
                                                    x2String.toDouble(), y2String.toDouble(), 
                                                    startDate, endDate, sppList);
}

QStringList * CalibrationWindow::findRoutesByKml(QStringList * sppList)
{
    QDateTime startDate = QDateTime(startDateField->date(), startTimeField->time());
    QDateTime endDate = QDateTime(endDateField->date(), endTimeField->time());
    
    double leftUpperCornerXValue = leftUpperCornerX->text().isEmpty() ? 0.0 : leftUpperCornerX->text().toDouble();
    double leftUpperCornerYValue = leftUpperCornerY->text().isEmpty() ? 0.0 : leftUpperCornerY->text().toDouble();
    double rightUpperCornerXValue = rightUpperCornerX->text().isEmpty() ? 0.0 : rightUpperCornerX->text().toDouble();
    double rightUpperCornerYValue = rightUpperCornerY->text().isEmpty() ? 0.0 : rightUpperCornerY->text().toDouble();
    double leftLowerCornerXValue = leftLowerCornerX->text().isEmpty() ? 0.0 : leftLowerCornerX->text().toDouble();
    double leftLowerCornerYValue = leftLowerCornerY->text().isEmpty() ? 0.0 : leftLowerCornerY->text().toDouble();
    double rightLowerCornerXValue= rightLowerCornerX->text().isEmpty() ? 0.0 : rightLowerCornerX->text().toDouble();
    double rightLowerCornerYValue= rightLowerCornerY->text().isEmpty() ? 0.0 : rightLowerCornerY->text().toDouble();
    
    std::array<double, 4> x = {leftUpperCornerXValue, rightUpperCornerXValue, rightLowerCornerXValue, leftLowerCornerXValue};
    std::array<double, 4> y = {leftUpperCornerYValue, rightUpperCornerYValue, rightLowerCornerYValue, leftLowerCornerYValue};
    
    return RouteFinder::findRoutesByCoordsAndData(x, y, startDate, endDate, sppList);
}