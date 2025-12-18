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
    
    QLineEdit * xField;
    QLineEdit * yField;
    QLabel * xFieldText;
    QLabel * yFieldText;
    
    QLineEdit * x1Field;
    QLineEdit * x2Field;
    QLineEdit * y1Field;
    QLineEdit * y2Field;
    QLabel * x1FieldText;
    QLabel * x2FieldText;
    QLabel * y1FieldText;
    QLabel * y2FieldText;
    
    QLabel * kmlPathLabel;
    QPushButton * selectKmlButton;
    
    QLabel * leftUpperCornerX;
    QLabel * leftUpperCornerY;
    QLabel * rightUpperCornerX;
    QLabel * rightUpperCornerY;
    QLabel * leftLowerCornerX;
    QLabel * leftLowerCornerY;
    QLabel * rightLowerCornerX;
    QLabel * rightLowerCornerY;
    
    QLabel * corner1Text;
    QLabel * corner2Text;
    QLabel * corner3Text;
    QLabel * corner4Text;
    
    QLabel * kmlXText1;
    QLabel * kmlYText1;
    QLabel * kmlXText2;
    QLabel * kmlYText2;
    QLabel * kmlXText3;
    QLabel * kmlYText3;
    QLabel * kmlXText4;
    QLabel * kmlYText4;
    
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
    void setTwoCoordsPanelVisible(bool isVisible);
    void setFourCoordsPanelVisible(bool isVisible);
    void setKmlCoordsPanelVisible(bool isVisible);
    
    QStringList * filterSppList(QStringList * sppList);
    void fillKmlCornerLabels(Kml * kml);
    
    void openRouteDirectoryEvent();
    void routeSearchEvent();
    void openKmlEvent();
    
    QStringList * findRoutesByPoint(QStringList * sppList);
    QStringList * findRoutesByRectangle(QStringList * sppList);
    QStringList * findRoutesByKml(QStringList * sppList);
};