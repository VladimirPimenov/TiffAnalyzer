#include "../../../include/kmlCoordsPanel.h"

KmlCoordsPanel::KmlCoordsPanel()
{
    kmlPathLabel = new QLabel();
	kmlPathLabel->setStyleSheet("border: 1px solid black");
    
    selectKmlButton = new QPushButton("Выбрать KML");
    selectKmlButton->setFixedWidth(100);
    
    QHBoxLayout * row = new QHBoxLayout();
    row->addWidget(kmlPathLabel);
    row->addWidget(selectKmlButton);
    
    this->addLayout(row);
    
    connect(selectKmlButton, &QPushButton::clicked, this, &KmlCoordsPanel::openKmlEvent);

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
    
    this->addLayout(panel);
}

void KmlCoordsPanel::setVisible(bool isVisible)
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

void KmlCoordsPanel::fillKmlCornerLabels(Kml * kml)
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

void KmlCoordsPanel::setInputChangedEvent(std::function<void()> eventHandler)
{
    inputChangedEventHandler = eventHandler;
}

void KmlCoordsPanel::openKmlEvent()
{
    QString kmlPath = QFileDialog::getOpenFileName(new QWidget(), "Открыть файл", "./", "KML (*.kml)");
    
    if(kmlPath.isEmpty())
        return;
        
    kmlPathLabel->setText(kmlPath);
    
    Kml * kml = new Kml(kmlPath);
    
    qInfo().noquote() << "Открыт файл полигона KML" << kmlPath;
    
    fillKmlCornerLabels(kml);
    
    inputChangedEvent();
}

void KmlCoordsPanel::inputChangedEvent()
{
    inputChangedEventHandler();
}

QStringList * KmlCoordsPanel::getX()
{
    QStringList * xString = new QStringList();

    xString->append(leftUpperCornerX->text().isEmpty() ? "0.0" : leftUpperCornerX->text());
    xString->append(rightUpperCornerX->text().isEmpty() ? "0.0" : rightUpperCornerX->text());
    xString->append(leftLowerCornerX->text().isEmpty() ? "0.0" : leftLowerCornerX->text());
    xString->append(rightLowerCornerX->text().isEmpty() ? "0.0" : rightLowerCornerX->text());
    
    return xString;
}

QStringList * KmlCoordsPanel::getY()
{
    QStringList * yString = new QStringList();

    yString->append(leftUpperCornerY->text().isEmpty() ? "0.0" : leftUpperCornerY->text());
    yString->append(rightUpperCornerY->text().isEmpty() ? "0.0" : rightUpperCornerY->text());
    yString->append(leftLowerCornerY->text().isEmpty() ? "0.0" : leftLowerCornerY->text());
    yString->append(rightLowerCornerY->text().isEmpty() ? "0.0" : rightLowerCornerY->text());
    
    return yString;
}