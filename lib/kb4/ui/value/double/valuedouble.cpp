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
    setName(name);
    setPostfix(postfix);
    setPrecision(precision);

    ui->doubleSpinBoxValueSet->setVisible(!hideSetWidget);
    ui->pushButtonSet->setVisible(!hideSetWidget);

    ui->doubleSpinBoxValueSet->setDecimals(this->precision());

    setScientificNotation(scientificNotation);
    setFontSize(fontSize);
    setValue(0);

    setMaxWidth();

}

void ValueDouble::configure(ChannelDouble *getChannel, int fontSize)
{
    connect(getChannel, &ChannelDouble::valueChangedDouble, this, &ValueDouble::setValue);
    configure(getChannel->widgetName(), getChannel->postfix(), getChannel->precision(),
              true, getChannel->scientificNotation(), fontSize);
}

void ValueDouble::configure(ChannelDouble *getChannel, ChannelDouble *setChannel, int fontSize)
{
    connect(getChannel, &ChannelDouble::valueChangedDouble, this, &ValueDouble::setValue);
    connect(this, &ValueDouble::valueChanged, setChannel, &ChannelDouble::setValue);
    configure(getChannel->widgetName(), getChannel->postfix(), getChannel->precision(),
              false, getChannel->scientificNotation(), fontSize);
}


void ValueDouble::setFontSize(int newValue)
{
    _setFontSize(ui->labelName, newValue);
    _setFontSize(ui->labelPostfix, newValue);
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

    setColor(ui->labelName, color);
    setColor(ui->labelPostfix, color);
    setColor(ui->lineEditValueGet, color);
}

QLineEdit *ValueDouble::valueGet()
{
    return ui->lineEditValueGet;
}

QLabel *ValueDouble::labelPostfix()
{
    return ui->labelPostfix;
}

QString ValueDouble::postfix() const
{
    return _postfix;
}

void ValueDouble::setPostfix(const QString &postfix)
{
    ui->labelPostfix->setText(postfix);
    _postfix = postfix;
}

void ValueDouble::syncAligment(ValueDouble *sample, bool syncValueGet)
{
    syncAligment(labelPostfix(), sample->labelPostfix());
    if (syncValueGet)
    {
        syncAligment(valueGet(), sample->valueGet());
    }
}

void ValueDouble::syncAligment(QWidget *w1, QWidget *w2)
{
    auto w1Wwidth = w1->width();
    auto w2Wwidth = w2->width();
    auto max = qMax(w1Wwidth, w2Wwidth);

    w1->setMinimumWidth(max);
    w2->setMinimumWidth(max);
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
    ui->labelName->setText(name);
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

    auto tmp = EasyLiving::formatDouble(value(), 3, scientificNotation());
    clipboard->setText(tmp);
    emit valueCopyedToClipboard(tmp, QString("Значение '%1' скопировано в буфер обмена (%2)").arg(name()).arg(tmp));

    QWidget::mouseDoubleClickEvent(event);

}
