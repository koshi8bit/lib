#include "axisconfig.h"
#include "ui_axisconfig.h"

AxisConfig::AxisConfig(QCPAxis *axis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisConfig)
{
    ui->setupUi(this);

    this->axis = axis;


    ui->lineEditLabel->setText(axis->label());

    // { TESTS


    // } TESTS


    auto t1 = QDateTime(QDate(2018, 12, 12), QTime(22, 54, 00)).toTime_t();
    auto t2 = axis->range().lower;

    if (t2 > t1)
    {
        axisType = AxisType::DateTime;

        ui->radioButtonAuto->setVisible(false);
        ui->radioButtonManual->setVisible(false);
        ui->labelMin->setVisible(false);
        ui->labelMax->setVisible(false);
        ui->checkBoxLog10->setVisible(false);
        ui->doubleSpinBoxMin->setVisible(false);
        ui->doubleSpinBoxMax->setVisible(false);
        ui->scientificNotationEditMin->setVisible(false);
        ui->scientificNotationEditMax->setVisible(false);


        ui->spinBoxSec->setValue(ceil(axis->range().upper - axis->range().lower));
        return;

    }

    ui->labelSecOnScreen->setVisible(false);
    ui->spinBoxSec->setVisible(false);

    ui->scientificNotationEditMin->setValue(axis->range().lower);
    ui->scientificNotationEditMax->setValue(axis->range().upper);
    ui->doubleSpinBoxMin->setValue(axis->range().lower);
    ui->doubleSpinBoxMax->setValue(axis->range().upper);


    if (axis->scaleType() == QCPAxis::ScaleType::stLogarithmic)
    {
        axisType = AxisType::NumericScientificNotation;

        ui->checkBoxLog10->setChecked(true);

        ui->doubleSpinBoxMin->setVisible(false);
        ui->doubleSpinBoxMax->setVisible(false);

    }
    else
    {
        axisType = AxisType::NumericStandardNotation;

        ui->checkBoxLog10->setChecked(false);


        ui->scientificNotationEditMin->setVisible(false);
        ui->scientificNotationEditMax->setVisible(false);

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

    if (axisType == AxisType::NumericStandardNotation)
    {
        axis->setRange(
                       ui->doubleSpinBoxMin->value(),
                       ui->doubleSpinBoxMax->value());

        axis->setScaleType(QCPAxis::stLinear);
        QSharedPointer<QCPAxisTicker> ticker(new QCPAxisTicker);
        axis->setTicker(ticker);
        axis->setNumberFormat("f");
        axis->setNumberPrecision(1);

        return;
    }

    if (axisType == AxisType::NumericScientificNotation)
    {
        axis->setRange(
                       ui->scientificNotationEditMin->value(),
                       ui->scientificNotationEditMax->value());

        axis->setScaleType(QCPAxis::stLogarithmic);
        QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
        axis->setTicker(logTicker);
        axis->setNumberFormat("eb");
        axis->setNumberPrecision(0);

        return;
    }


    if (axisType == AxisType::DateTime)
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

void AxisConfig::on_checkBoxLog10_stateChanged(int arg1)
{
    auto log10 = static_cast<bool>(arg1);

    if (log10)
    {
        axisType = AxisType::NumericScientificNotation;
        ui->doubleSpinBoxMin->setVisible(false);
        ui->doubleSpinBoxMax->setVisible(false);
        ui->scientificNotationEditMin->setVisible(true);
        ui->scientificNotationEditMax->setVisible(true);
    }
    else
    {
        axisType = AxisType::NumericStandardNotation;
        ui->doubleSpinBoxMin->setVisible(true);
        ui->doubleSpinBoxMax->setVisible(true);
        ui->scientificNotationEditMin->setVisible(false);
        ui->scientificNotationEditMax->setVisible(false);
    }

}

void AxisConfig::on_pushButton_clicked()
{

}
