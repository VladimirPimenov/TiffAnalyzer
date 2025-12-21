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

#include <QDebug>

#include <array>

#include "onePointCoordsPanel.h"
#include "rectangleCoordsPanel.h"
#include "kmlCoordsPanel.h"

#include "directoryReader.h"
#include "routeFinder.h"
#include "coordsConvertor.h"
#include "kml.h"

class CalibrationWindow: public QDialog
{
public:
    CalibrationWindow(QWidget * parent);
    
private:
    QVBoxLayout * vWidgetsBox;
    
    QVBoxLayout * coordsInputTable;
    QVBoxLayout * kmlTable;
    
    QLabel * routeDirectoryLabel;
    QPushButton * selectDirectoryButton;

    QDateEdit * startDateField;
    QTimeEdit * startTimeField;
    QDateEdit * endDateField;
    QTimeEdit * endTimeField;
    
    QRadioButton * userInputFlag;
    QRadioButton * kmlInputFlag;
    
    QRadioButton * ddFormFlag;
    QRadioButton * ddmmssFormFlag;
    QRadioButton * kmlFormFlag;
    
    QRadioButton * twoCoordsFlag;
    QRadioButton * fourCoordsFlag;
    
    QLabel * coordsFormatText;
    QLabel * coordsCountText;
    
    OnePointCoordsPanel * onePointCoordsPanel;
    RectangleCoordsPanel * rectangleCoordsPanel;
    KmlCoordsPanel * kmlCoordsPanel;
    
    QLabel * outputLabel;
    QScrollArea * scrollArea;
    
    bool isOnePointChecking;
    bool isUserInput;
    
    void createDirectorySelectionWidgets();
    void createDateSelectionWidgets();
    void createInputTypeWidgets();
    
    void createKmlCoordsWidgets();
    
    void createCoordinatesFormatWidgets();
    void createCoordinatesSelectionWidgets();
    
    void createOutputPanel();
    
    void switchInputTypeSelection(int id);
    void switchCoordinatesSelection(int id);
    
    void setCoordinatesFormatPanelVisile(bool isVisible);
    
    QStringList * filterSppList(QStringList * sppList);
    
    void openRouteDirectoryEvent();
    void routeSearchEvent();
    
    QStringList * findRoutesByPoint(QStringList * sppList);
    QStringList * findRoutesByRectangle(QStringList * sppList);
    QStringList * findRoutesByKml(QStringList * sppList);
};