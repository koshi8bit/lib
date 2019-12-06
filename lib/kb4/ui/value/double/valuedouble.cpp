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

void ValueDouble::configure(QString name, QString postfix, int precision, bool readOnly, bool scientificNotation, int fontSize)
{
    setNameAndPostfix(name, postfix);
    setReadOnly(readOnly);
    _precision = precision;
    _scientificNotation = scientificNotation;
    setFontSize(fontSize);
    setValue(0);
}

void ValueDouble::setReadOnly(bool newValue)
{
    //ui->doubleSpinBoxValue->setButtonSymbols(newValue ? QAbstractSpinBox::ButtonSymbols::NoButtons : QAbstractSpinBox::ButtonSymbols::UpDownArrows);
    ui->lineEditValue->setReadOnly(newValue);
}

void ValueDouble::setFontSize(int newValue)
{
    _setFontSize(ui->labelNameAndPostfix, newValue);
    _setFontSize(ui->lineEditValue, newValue);
}

void ValueDouble::setNameAndPostfix(QString name, QString postfix)
{
    auto s = QString("%1 (%2):").arg(name, postfix);
    ui->labelNameAndPostfix->setText(s);
}

void ValueDouble::setValue(double newValue)
{
    auto str = EasyLiving::formatDouble(newValue, _precision, _scientificNotation);
    ui->lineEditValue->setText(str);
}

void ValueDouble::_setFontSize(QWidget *widget, int newValue)
{
    auto _font = widget->font();
    _font.setPointSize(newValue);
    widget->setFont(_font);
}
