#include "valuedouble.h"
#include "ui_valuedouble.h"

const QString ValueDouble::trustedColor = "#000000";
const QString ValueDouble::notTrustedColor = "#CFCFCF";

ValueDouble::ValueDouble(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValueDouble)
{
    ui->setupUi(this);
    ui->lineEditValueGet->setReadOnly(true);
    //connect(ui->doubleSpinBoxValueSet, SIGNAL(valueChanged(double)), this, SIGNAL(valueChanged(double)));


}

ValueDouble::~ValueDouble()
{
    delete ui;
}


void ValueDouble::configure(QString name, QString postfix, int precision, bool hideSetWidget, bool scientificNotation, int fontSize)
{
    setNameAndPostfix(name, postfix);
    setPrecision(precision);

    ui->doubleSpinBoxValueSet->setVisible(!hideSetWidget);
    ui->pushButtonSet->setVisible(!hideSetWidget);

    ui->doubleSpinBoxValueSet->setDecimals(this->precision());

    setScientificNotation(scientificNotation);
    setFontSize(fontSize);
    setValue(0);

    setMaxWidth();

}

void ValueDouble::configure(ChannelBool *channel, bool hideSetWidget, int fontSize, bool connectSlot)
{
    if (connectSlot)
    {
        connect(channel, &ChannelBool::valueChangedDouble, this, &ValueDouble::setValue);
    }

    configure(channel->widgetName(), channel->postfix(), channel->precision(), hideSetWidget, channel->scientificNotation(), fontSize);
}


void ValueDouble::setFontSize(int newValue)
{
    _setFontSize(ui->labelNameAndPostfix, newValue);
    _setFontSize(ui->lineEditValueGet, newValue);
    _setFontSize(ui->doubleSpinBoxValueSet, newValue);
    _setFontSize(ui->pushButtonSet, newValue);

    if (newValue == 30)
    {
        this->setMinimumHeight(71);
    }

    if (newValue == 25)
    {
        this->setMinimumHeight(62);
    }

    if (newValue == 14)
    {
        this->setMinimumHeight(36);
    }

    if (newValue == 8)
    {
        this->setMinimumHeight(38);
    }
}

void ValueDouble::setMaxWidth()
{
    QFontMetrics fm(ui->lineEditValueGet->font());
    auto str = EasyLiving::formatDouble(123, _precision, _scientificNotation);
    auto maxWidth = fm.horizontalAdvance(str);
    ui->lineEditValueGet->setMaximumWidth(static_cast<int>(maxWidth*1.2)+10);
}

void ValueDouble::setRangeSetter(double min, double max)
{
    ui->doubleSpinBoxValueSet->setRange(min, max);
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

double ValueDouble::value() const
{
    return _value;
}

QString ValueDouble::name() const
{
    return _name;
}

void ValueDouble::setName(const QString &name)
{
    _name = name;
}

bool ValueDouble::scientificNotation() const
{
    return _scientificNotation;
}

void ValueDouble::setScientificNotation(bool scientificNotation)
{
    _scientificNotation = scientificNotation;
}

int ValueDouble::precision() const
{
    return _precision;
}

void ValueDouble::setPrecision(int precision)
{
    _precision = precision;
}

void ValueDouble::setNameAndPostfix(QString name, QString postfix)
{
    setName(name);
    auto s = QString("%1 (%2):").arg(name, postfix);
    ui->labelNameAndPostfix->setText(s);
}

void ValueDouble::setValue(double newValue)
{
    _value = newValue;
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

void ValueDouble::on_pushButtonSet_clicked()
{
    emit valueChanged(ui->doubleSpinBoxValueSet->value());
}

void ValueDouble::on_doubleSpinBoxValueSet_editingFinished()
{
    emit valueChanged(ui->doubleSpinBoxValueSet->value());
}

void ValueDouble::mouseDoubleClickEvent(QMouseEvent *event)
{
    QClipboard *clipboard = QApplication::clipboard();
    auto valueStr = EasyLiving::formatDouble(value(), _precision, _scientificNotation);

    auto tmp = ui->lineEditValueGet->text();
    clipboard->setText(tmp);

    QWidget::mouseDoubleClickEvent(event);

    emit valueCopyedToClipboard(tmp, QString("Значение '%1' скопировано в буфер обмена (%2)").arg(name()).arg(tmp));

}
