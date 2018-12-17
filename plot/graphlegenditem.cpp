#include "graphlegenditem.h"
#include "ui_graphlegenditem.h"

GraphLegendItem::GraphLegendItem(const QString &label, QColor color, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphLegendItem)
{
    ui->setupUi(this);
    this->label = label;

    QString css = QString("background:rgb(%1,%2,%3);")
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue());
    ui->pushButtonColor->setStyleSheet(css);
    ui->checkBoxVisible->setChecked(true);
    setValue(0);

}

GraphLegendItem::~GraphLegendItem()
{
    delete ui;
}

void GraphLegendItem::setValue(double value)
{
    ui->label->setText(QString("%1: %2")
                       .arg(label)
                       .arg(value, 0, 'f', 3, '0'));
}

void GraphLegendItem::setValue(const QString &value)
{
    ui->label->setText(QString("%1: %2")
                       .arg(label)
                       .arg(value));
}

void GraphLegendItem::on_checkBoxVisible_stateChanged(int arg1)
{
    auto visible = static_cast<bool>(arg1);
    emit visibleChanged(visible);
}

void GraphLegendItem::on_pushButtonColor_clicked()
{

}
