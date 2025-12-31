#include "../../../include/calibrationWindow.h"

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

void CalibrationWindow::setDateTime(QDateTime startDateTime)
{
    startDateField->setDate(startDateTime.date());
    startTimeField->setTime(startDateTime.time());
    endDateField->setDate(startDateTime.date().addMonths(1));
    endTimeField->setTime(startDateTime.time());
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
    
    onePointCoordsPanel = new OnePointCoordsPanel();
    onePointCoordsPanel->setInputChangedEvent([this](){ routeSearchEvent(); });
    
    rectangleCoordsPanel = new RectangleCoordsPanel();
    rectangleCoordsPanel->setInputChangedEvent([this](){ routeSearchEvent(); });
    
    coordsInputTable->addLayout(onePointCoordsPanel);
    coordsInputTable->addLayout(rectangleCoordsPanel);
    
    switchCoordinatesSelection(1);
}

void CalibrationWindow::createKmlCoordsWidgets()
{
    kmlCoordsPanel = new KmlCoordsPanel();
    kmlCoordsPanel->setInputChangedEvent([this](){ routeSearchEvent(); });

    kmlTable->addLayout(kmlCoordsPanel);
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
            onePointCoordsPanel->setVisible(true);
            rectangleCoordsPanel->setVisible(false);
            isOnePointChecking = true;
            break;
        case 1:
            onePointCoordsPanel->setVisible(false);
            rectangleCoordsPanel->setVisible(true);
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
            kmlCoordsPanel->setVisible(false);
            switchCoordinatesSelection(isOnePointChecking ? 0 : 1);
            setCoordinatesFormatPanelVisile(true);
            break;
        case 1:
            isUserInput = false;
            onePointCoordsPanel->setVisible(false);
            rectangleCoordsPanel->setVisible(false);
            kmlCoordsPanel->setVisible(true);
            setCoordinatesFormatPanelVisile(false);
            break;
    }
    routeSearchEvent();
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

QStringList * CalibrationWindow::findRoutesByPoint(QStringList * sppList)
{
    QDateTime startDate = QDateTime(startDateField->date(), startTimeField->time());
    QDateTime endDate = QDateTime(endDateField->date(), endTimeField->time());

    QString xString = onePointCoordsPanel->getX();
    QString yString = onePointCoordsPanel->getY();

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

    QStringList * xString = rectangleCoordsPanel->getX();
    QStringList * yString = rectangleCoordsPanel->getY();
    
    if(ddFormFlag->isChecked())
    {
        (*xString)[0] = CoordsConvertor::convertDdToKml((*xString)[0]);
        (*xString)[1] = CoordsConvertor::convertDdToKml((*xString)[1]);
        (*yString)[0] = CoordsConvertor::convertDdToKml((*yString)[0]);
        (*yString)[1] = CoordsConvertor::convertDdToKml((*yString)[1]);
    }
    else if(ddmmssFormFlag->isChecked())
    {
        (*xString)[0] = CoordsConvertor::convertDdmmssToKml((*xString)[0]);
        (*xString)[1] = CoordsConvertor::convertDdmmssToKml((*xString)[1]);
        (*yString)[0] = CoordsConvertor::convertDdmmssToKml((*yString)[0]);
        (*yString)[1] = CoordsConvertor::convertDdmmssToKml((*yString)[1]);
    }
    
    return RouteFinder::findRoutesByCoordsAndData((*xString)[0].toDouble(), (*yString)[0].toDouble(), 
                                                    (*xString)[1].toDouble(), (*yString)[1].toDouble(), 
                                                    startDate, endDate, sppList);
}

QStringList * CalibrationWindow::findRoutesByKml(QStringList * sppList)
{
    QDateTime startDate = QDateTime(startDateField->date(), startTimeField->time());
    QDateTime endDate = QDateTime(endDateField->date(), endTimeField->time());

    QStringList * xString = kmlCoordsPanel->getX();
    QStringList * yString = kmlCoordsPanel->getY();
    
    std::array<double, 4> x = 
    {
        (*xString)[0].toDouble(), 
        (*xString)[1].toDouble(), 
        (*xString)[2].toDouble(), 
        (*xString)[3].toDouble()
    };
    std::array<double, 4> y = 
    {
        (*yString)[0].toDouble(), 
        (*yString)[1].toDouble(), 
        (*yString)[2].toDouble(), 
        (*yString)[3].toDouble()
    };
    
    return RouteFinder::findRoutesByCoordsAndData(x, y, startDate, endDate, sppList);
}