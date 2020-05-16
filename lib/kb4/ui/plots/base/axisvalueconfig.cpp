#include "axisvalueconfig.h"
#include "ui_axisvalueconfig.h"

AxisValueConfig::AxisValueConfig(QCPAxis *axis, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AxisValueConfig)
{
    ui->setupUi(this);

    this->axis = axis;


    ui->lineEditLabel->setText(axis->label());

    // { TESTS


    // } TESTS

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
    ui->spinBoxNumberPrecision->setValue(axis->numberPrecision());
    resize(300, 200);

}

AxisValueConfig::~AxisValueConfig()
{
    delete ui;
}

void AxisValueConfig::on_buttonBox_accepted()
{
    //qDebug() << size();

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
        axis->setNumberPrecision(ui->spinBoxNumberPrecision->value());


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
        axis->setNumberPrecision(ui->spinBoxNumberPrecision->value());

        return;
    }
}


void AxisValueConfig::on_radioButtonAuto_toggled(bool checked)
{
    ui->doubleSpinBoxMin->setEnabled(!checked);
    ui->doubleSpinBoxMax->setEnabled(!checked);

    ui->scientificNotationEditMin->setEnabled(!checked);
    ui->scientificNotationEditMax->setEnabled(!checked);
}

void AxisValueConfig::on_checkBoxLog10_stateChanged(int arg1)
{
    auto log10 = static_cast<bool>(arg1);

    if (log10)
    {
        axisType = AxisType::NumericScientificNotation;
        ui->doubleSpinBoxMin->setVisible(false);
        ui->doubleSpinBoxMax->setVisible(false);
        ui->scientificNotationEditMin->setVisible(true);
        ui->scientificNotationEditMax->setVisible(true);
        ui->spinBoxNumberPrecision->setValue(0);
    }
    else
    {
        axisType = AxisType::NumericStandardNotation;
        ui->doubleSpinBoxMin->setVisible(true);
        ui->doubleSpinBoxMax->setVisible(true);
        ui->scientificNotationEditMin->setVisible(false);
        ui->scientificNotationEditMax->setVisible(false);
        ui->spinBoxNumberPrecision->setValue(1);
    }

}

