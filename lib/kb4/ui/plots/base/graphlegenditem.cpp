#include "graphlegenditem.h"
#include "ui_graphlegenditem.h"

GraphLegendItem::GraphLegendItem(const QString &label, const QString &postfix, QColor color, int precision, bool scientificNotation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphLegendItem)
{
    ui->setupUi(this);
    this->label = label;
    this->postfix = postfix;
    setColor(color);
    this->precision = precision;
    ui->checkBoxVisible->setChecked(true);
    setLabelText(label);
    this->scientificNotation = scientificNotation;

}

void GraphLegendItem::setColor(QColor &color)
{
    this->color = color;
    QString css = QString("background: %1;").arg(color.name());
    ui->pushButtonColor->setStyleSheet(css);
}

GraphLegendItem::~GraphLegendItem()
{
    delete ui;
}

void GraphLegendItem::setValue(double value, bool showDelta)
{
    if (scientificNotation)
    {
        setValue(EasyLiving::formatDouble(value, precision, true), showDelta);
    }
    else
    {
        setValue(EasyLiving::formatDouble(value, precision), showDelta);
    }
}

void GraphLegendItem::setValue(const QString &value, bool showDelta)
{
    auto _template = QString("%1: ") + (showDelta ? "Δ" : "") + "%2";

    auto text = QString(_template)
                       .arg(label)
                       .arg(value);

    if (!postfix.isEmpty())
    {
        //text.append(" (" + postfix + ")");
        text.append(" " + postfix);
    }

    ui->label->setText(text);
}

void GraphLegendItem::setLabelText(const QString &string)
{
    ui->label->setText(string);
}

void GraphLegendItem::on_checkBoxVisible_stateChanged(int arg1)
{
    auto visible = EasyLiving::isChecked(arg1);
    if (!visible)
    {
        setValue(noValueText);
    }
    emit visibleChanged(visible);
}

void GraphLegendItem::on_pushButtonColor_clicked()
{
    auto color = QColorDialog::getColor(this->color, this, tr("Выберите цвет"));
    if (color.isValid())
    {
        setColor(color);

        emit colorChanged(color);
    }

}

void GraphLegendItem::setVisibleValue(bool newValue)
{
    ui->checkBoxVisible->setChecked(newValue);
    if (!newValue)
    {
        setValue(noValueText);
    }
}
