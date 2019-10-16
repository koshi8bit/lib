#include "graphlegenditem.h"
#include "ui_graphlegenditem.h"

GraphLegendItem::GraphLegendItem(const QString &label, const QString &postfix, QColor color, bool scientificNotation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphLegendItem)
{
    ui->setupUi(this);
    this->label = label;
    this->postfix = postfix;

    setColor(color);
    ui->checkBoxVisible->setChecked(true);
    setValue(0);
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

void GraphLegendItem::setValue(double value)
{
    if (scientificNotation)
    {
        setValue(EasyLiving::formatDouble(value, 'e'));
    }
    else
    {
        setValue(EasyLiving::formatDouble(value));
    }

}

void GraphLegendItem::setValue(const QString &value)
{
    auto text = QString("%1: %2")
                       .arg(label)
                       .arg(value);

    if (!postfix.isEmpty())
    {
        //text.append(" (" + postfix + ")");
        text.append(" " + postfix);
    }

    ui->label->setText(text);
}

void GraphLegendItem::on_checkBoxVisible_stateChanged(int arg1)
{
    //auto visible = static_cast<bool>(arg1);
    auto visible = arg1 == 2 ? true : false;
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
}
