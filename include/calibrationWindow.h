#pragma once

#include <QDialog>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <QDateEdit>
#include <QTimeEdit>
#include <QGridLayout>
#include <QLineEdit>
#include <QScrollArea>
#include <QScrollBar>

#include <QFileDialog>

#include "directoryReader.h"
#include "routeFinder.h"
#include "coordsConvertor.h"

class CalibrationWindow: public QDialog
{
public:
    CalibrationWindow(QWidget * parent);
    
private:
    QVBoxLayout * vWidgetsBox;
    
    QLabel * directoryLabel;
    QPushButton * selectDirectoryButton;

    QDateEdit * startDateField;
    QTimeEdit * startTimeField;
    QDateEdit * endDateField;
    QTimeEdit * endTimeField;
    
    QRadioButton * ddFormFlag;
    QRadioButton * ddmmssFormFlag;
    QRadioButton * kmlFormFlag;
    
    QRadioButton * twoCoordsFlag;
    QRadioButton * fourCoordsFlag;
    
    QGridLayout * twoCoordsPanel;
    QLineEdit * xField;
    QLineEdit * yField;
    QLabel * xFieldText;
    QLabel * yFieldText;
    
    QGridLayout * fourCoordsPanel;
    QLineEdit * x1Field;
    QLineEdit * x2Field;
    QLineEdit * y1Field;
    QLineEdit * y2Field;
    QLabel * x1FieldText;
    QLabel * x2FieldText;
    QLabel * y1FieldText;
    QLabel * y2FieldText;
    
    QPushButton * searchButton;
    
    QLabel * outputLabel;
    QScrollArea * scrollArea;
    
    bool isOnePointChecking;
    
    void createDirectorySelectionWidgets();
    void createDateSelectionWidgets();
    void createCoordinatesFormatWidgets();
    void createCoordinatesSelectionWidgets();
    void createOutputPanel();
    
    void switchCoordinatesSelection(int id);
    
    void setTwoCoordsPanelVisible(bool isVisible);
    void setFourCoordsPanelVisible(bool isVisible);
    
    QStringList * filterSppList(QStringList * sppList);
    
    void openDirectoryEvent();
    void routeInputChangedEvent();
};