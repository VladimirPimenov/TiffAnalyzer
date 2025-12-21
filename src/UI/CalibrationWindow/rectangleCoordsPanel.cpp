#include "../../../include/rectangleCoordsPanel.h"

RectangleCoordsPanel::RectangleCoordsPanel()
{
    QWidget * mockParent = new QWidget();

    x1Field = new QLineEdit(mockParent);
    x2Field = new QLineEdit(mockParent);
    y1Field = new QLineEdit(mockParent);
    y2Field = new QLineEdit(mockParent);
    x1Field->setFixedWidth(100);
    x2Field->setFixedWidth(100);
    y1Field->setFixedWidth(100);
    y2Field->setFixedWidth(100);
    
    connect(x1Field, &QLineEdit::textChanged, this, &RectangleCoordsPanel::inputChangedEvent);
    connect(y1Field, &QLineEdit::textChanged, this, &RectangleCoordsPanel::inputChangedEvent);
    connect(x2Field, &QLineEdit::textChanged, this, &RectangleCoordsPanel::inputChangedEvent);
    connect(y2Field, &QLineEdit::textChanged, this, &RectangleCoordsPanel::inputChangedEvent);
            
    x1FieldText = new QLabel("x1", mockParent);
    y1FieldText = new QLabel("y1", mockParent);
    x2FieldText = new QLabel("x2", mockParent);
    y2FieldText = new QLabel("y2", mockParent);
    
    x1FieldText->setAlignment(Qt::AlignCenter);
    x2FieldText->setAlignment(Qt::AlignCenter);
    y1FieldText->setAlignment(Qt::AlignCenter);
    y2FieldText->setAlignment(Qt::AlignCenter);
    
    this->addWidget(x1FieldText, 0, 0);
    this->addWidget(y1FieldText, 0, 1);
    this->addWidget(x2FieldText, 0, 2);
    this->addWidget(y2FieldText, 0, 3);
    this->addWidget(x1Field, 1, 0);
    this->addWidget(y1Field, 1, 1);
    this->addWidget(x2Field, 1, 2);
    this->addWidget(y2Field, 1, 3);
}

void RectangleCoordsPanel::setVisible(bool isVisible)
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

void RectangleCoordsPanel::setInputChangedEvent(std::function<void()> eventHandler)
{
    inputChangedEventHandler = eventHandler;
}

void RectangleCoordsPanel::inputChangedEvent()
{
    inputChangedEventHandler();
}

QStringList * RectangleCoordsPanel::getX()
{
    QStringList * xString = new QStringList();
    
    xString->append(x1Field->text().isEmpty() ? "0.0" : x1Field->text().replace(',', '.'));
    xString->append(x2Field->text().isEmpty() ? "0.0" : x2Field->text().replace(',', '.'));
    
    return xString;
}

QStringList * RectangleCoordsPanel::getY()
{
    QStringList * yString = new QStringList();
    
    yString->append(y1Field->text().isEmpty() ? "0.0" : y1Field->text().replace(',', '.'));
    yString->append(y2Field->text().isEmpty() ? "0.0" : y2Field->text().replace(',', '.'));
    
    return yString;
}