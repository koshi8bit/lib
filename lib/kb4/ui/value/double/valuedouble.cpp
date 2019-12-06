#include "valuedouble.h"
#include "ui_valuedouble.h"

ValueDouble::ValueDouble(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValueDouble)
{
    ui->setupUi(this);
}

ValueDouble::~ValueDouble()
{
    delete ui;
}

void ValueDouble::configure(QString name, QString postfix, bool readOnly, int fontSize)
{
    setNameAndPostfix(name, postfix);
    setReadOnly(readOnly);
    setFontSize(fontSize);
}

void ValueDouble::setReadOnly(bool newValue)
{
    ui->doubleSpinBoxValue->setButtonSymbols(newValue ? QAbstractSpinBox::ButtonSymbols::NoButtons : QAbstractSpinBox::ButtonSymbols::UpDownArrows);
    ui->doubleSpinBoxValue->setReadOnly(newValue);
}

void ValueDouble::setFontSize(int newValue)
{
    _setFontSize(ui->labelNameAndPostfix, newValue);
    _setFontSize(ui->doubleSpinBoxValue, newValue);
}

void ValueDouble::setNameAndPostfix(QString name, QString postfix)
{
    auto s = QString("%1 (%2)").arg(name, postfix);
    ui->labelNameAndPostfix->setText(s);
}

void ValueDouble::setValue(double newValue)
{
    ui->doubleSpinBoxValue->setValue(newValue);
}

void ValueDouble::_setFontSize(QWidget *widget, int newValue)
{
    auto _font = widget->font();
    _font.setPointSize(newValue);
    widget->setFont(_font);
}
