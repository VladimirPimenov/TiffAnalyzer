#include "../../../include/onePointCoordsPanel.h"

OnePointCoordsPanel::OnePointCoordsPanel()
{
    QWidget * mockParent = new QWidget();

    xField = new QLineEdit(mockParent);
    yField = new QLineEdit(mockParent);
    
    connect(xField, &QLineEdit::textChanged, this, &OnePointCoordsPanel::inputChangedEvent);
    connect(yField, &QLineEdit::textChanged, this, &OnePointCoordsPanel::inputChangedEvent);
    
    xFieldText = new QLabel("x", mockParent);
    yFieldText = new QLabel("y", mockParent);
    xFieldText->setAlignment(Qt::AlignCenter);
    yFieldText->setAlignment(Qt::AlignCenter);
    xField->setFixedWidth(100);
    yField->setFixedWidth(100);
    
    this->addWidget(xFieldText, 0, 0);
    this->addWidget(yFieldText, 0, 1);
    this->addWidget(xField, 1, 0);
    this->addWidget(yField, 1, 1);
}

void OnePointCoordsPanel::setVisible(bool isVisible)
{
    xField->setVisible(isVisible);
    yField->setVisible(isVisible);
    
    xFieldText->setVisible(isVisible);
    yFieldText->setVisible(isVisible);
}

void OnePointCoordsPanel::setInputChangedEvent(std::function<void()> eventHandler)
{
    inputChangedEventHandler = eventHandler;
}

void OnePointCoordsPanel::inputChangedEvent()
{
    inputChangedEventHandler();
}

QString OnePointCoordsPanel::getX()
{
    return xField->text().isEmpty() ? "0.0" : xField->text().replace(',', '.');
}

QString OnePointCoordsPanel::getY()
{
    return yField->text().isEmpty() ? "0.0" : yField->text().replace(',', '.');
}