#include "axisconfig.h"
#include "ui_axisconfig.h"

AxisConfig::AxisConfig(QCPAxis *axis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisConfig)
{
    ui->setupUi(this);

    this->axis = axis;


    ui->lineEditLabel->setText(axis->label());

    auto t1 = QDateTime(QDate(2018, 12, 12), QTime(22, 54, 00)).toTime_t();
    auto t2 = axis->range().lower;

    if (t2 > t1)
    {
        axisType = AxisType::aeDateTime;

        ui->radioButtonAuto->setVisible(false);
        ui->radioButtonManual->setVisible(false);
        ui->labelMin->setVisible(false);
        ui->labelMax->setVisible(false);
        ui->doubleSpinBoxMin->setVisible(false);
        ui->doubleSpinBoxMax->setVisible(false);

        ui->spinBoxSec->setValue(ceil(axis->range().upper - axis->range().lower));

    }
    else
    {
        axisType = AxisType::aeNumeric;

        ui->labelSecOnScreen->setVisible(false);
        ui->spinBoxSec->setVisible(false);

        ui->doubleSpinBoxMin->setValue(axis->range().lower);
        ui->doubleSpinBoxMax->setValue(axis->range().upper);
    }


}

AxisConfig::~AxisConfig()
{
    delete ui;
}

void AxisConfig::on_buttonBox_accepted()
{
    axis->setLabel(ui->lineEditLabel->text());

    if (ui->radioButtonAuto->isChecked())
    {
        foreach(auto graph, axis->graphs())
        {
            graph->rescaleValueAxis(false, true);
        }
        return;
    }

    if (axisType == AxisType::aeNumeric)
    {
        axis->setRange(
                       ui->doubleSpinBoxMin->value(),
                       ui->doubleSpinBoxMax->value());
        return;
    }

    if (axisType == AxisType::aeDateTime)
    {

        axis->setRangeLower(axis->range().upper - ui->spinBoxSec->value());
        return;
    }
}


void AxisConfig::on_radioButtonAuto_toggled(bool checked)
{
    qDebug() << checked;
    ui->doubleSpinBoxMin->setEnabled(!checked);
    ui->doubleSpinBoxMax->setEnabled(!checked);
}
