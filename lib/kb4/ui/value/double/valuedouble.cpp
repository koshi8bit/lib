#include "valuedouble.h"
#include "ui_valuedouble.h"

const QString ValueDouble::trustedColor = "#000000";
const QString ValueDouble::notTrustedColor = "#AFAFAF";

ValueDouble::ValueDouble(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValueDouble)
{
    ui->setupUi(this);
    ui->lineEditValueGet->setReadOnly(true);
    connect(ui->doubleSpinBoxValueSet, SIGNAL(valueChanged(double)), this, SIGNAL(valueChanged(double)));

}

ValueDouble::~ValueDouble()
{
    delete ui;
}

void ValueDouble::configure(QString name, QString postfix, int precision, bool hideSetWidget, bool scientificNotation, int fontSize)
{
    setNameAndPostfix(name, postfix);
    _precision = precision;

    ui->doubleSpinBoxValueSet->setVisible(!hideSetWidget);
    ui->doubleSpinBoxValueSet->setDecimals(_precision);


    _scientificNotation = scientificNotation;
    setFontSize(fontSize);
    setValue(0);
}

void ValueDouble::setTrusted(bool newValue)
{
    QString color;
    if (newValue)
    {
        color = trustedColor;
    }
    else
    {
        color = notTrustedColor;
    }

    setColor(ui->labelNameAndPostfix, color);
    setColor(ui->lineEditValueGet, color);
}

QLineEdit *ValueDouble::valueWidget()
{
    return ui->lineEditValueGet;
}

void ValueDouble::setFontSize(int newValue)
{
    _setFontSize(ui->labelNameAndPostfix, newValue);
    _setFontSize(ui->lineEditValueGet, newValue);
    _setFontSize(ui->doubleSpinBoxValueSet, newValue);

    if (newValue == 30)
    {
        this->setMinimumHeight(71);
    }

    if (newValue == 25)
    {
        this->setMinimumHeight(62);
    }
}

void ValueDouble::setNameAndPostfix(QString name, QString postfix)
{
    auto s = QString("%1 (%2):").arg(name, postfix);
    ui->labelNameAndPostfix->setText(s);
}

void ValueDouble::setValue(double newValue)
{
    auto str = EasyLiving::formatDouble(newValue, _precision, _scientificNotation);
    ui->lineEditValueGet->setText(str);
}

void ValueDouble::_setFontSize(QWidget *widget, int newValue)
{
    auto _font = widget->font();
    _font.setPointSize(newValue);
    widget->setFont(_font);
}

void ValueDouble::setColor(QWidget *widget, QString newColor)
{
    widget->setStyleSheet(QString("color: %1").arg(newColor));
}
