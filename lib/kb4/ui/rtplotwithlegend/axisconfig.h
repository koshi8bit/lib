#ifndef AXISCONFIG_H
#define AXISCONFIG_H

#include <QDialog>
#include <lib/qcustomplot/qcustomplot.h>

namespace Ui {
class AxisConfig;
}

class AxisConfig : public QDialog
{
    Q_OBJECT



public:
    explicit AxisConfig(QCPAxis *axis, bool isXAxis, QWidget *parent = nullptr);
    ~AxisConfig();


    enum AxisType
    {
        NumericStandardNotation,
        NumericScientificNotation,
        DateTime
    };
    Q_ENUM(AxisType)


private slots:
    void on_buttonBox_accepted();

    void on_radioButtonAuto_toggled(bool checked);

    void on_checkBoxLog10_stateChanged(int arg1);



    void on_spinBoxFullSec_valueChanged(int arg1);
    void spinBoxHoursMinutesSecondsValueChanged(int arg1);

private:


    Ui::AxisConfig *ui;
    QCPAxis *axis;
    AxisType axisType;


};

#endif // AXISCONFIG_H
