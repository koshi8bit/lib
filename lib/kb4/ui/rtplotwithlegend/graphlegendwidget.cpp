#include "graphlegenditem.h"
#include "ui_graphlegenditem.h"

//TODO change name to GraphLegendItem
GraphLegendWidget::GraphLegendWidget(const QString &label, QColor color, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphLegendItem)
{
    ui->setupUi(this);
    this->label = label;

    changeColor(color);
    ui->checkBoxVisible->setChecked(true);
    setValue(0);

}

void GraphLegendWidget::changeColor(QColor &color)
{
    this->color = color;
    QString css = QString("background: %1;").arg(color.name());
    ui->pushButtonColor->setStyleSheet(css);
}

GraphLegendWidget::~GraphLegendWidget()
{
    delete ui;
}

void GraphLegendWidget::setValue(double value)
{
    ui->label->setText(QString("%1: %2")
                       .arg(label)
                       .arg(value, 0, 'f', 3, '0'));
}

void GraphLegendWidget::setValue(const QString &value)
{
    ui->label->setText(QString("%1: %2")
                       .arg(label)
                       .arg(value));
}

void GraphLegendWidget::on_checkBoxVisible_stateChanged(int arg1)
{
    auto visible = static_cast<bool>(arg1);
    emit visibleChanged(visible);
}

void GraphLegendWidget::on_pushButtonColor_clicked()
{
    auto color = QColorDialog::getColor(this->color, this, tr("Select Color"));
    if (color.isValid())
    {
        changeColor(color);

        emit colorChanged(color);
    }

}

void GraphLegendWidget::setVisibleValue(bool newValue)
{
    ui->checkBoxVisible->setChecked(newValue);
}
