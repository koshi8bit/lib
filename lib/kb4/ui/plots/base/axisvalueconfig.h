#ifndef AXISTIMECONFIG_H
#define AXISTIMECONFIG_H

#include <QDialog>
#include <lib/kb4/ui/qcustomplot/qcustomplot.h>

#include <lib/kb4/easyliving.h>

namespace Ui {
class AxisValueConfig;
}

class AxisValueConfig : public QDialog
{
    Q_OBJECT



public:
    explicit AxisValueConfig(QCPAxis *axis, bool isXAxis, QWidget *parent = nullptr);
    ~AxisValueConfig();


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
    void spinBoxDaysHoursMinutesSecondsValueChanged(int arg1);

    void on_pushButtonTime010000_clicked();
    void on_pushButtonTime001000_clicked();
    void on_pushButtonTime000500_clicked();
    void on_pushButtonTime000100_clicked();
    void on_pushButtonTime000030_clicked();


private:
    Ui::AxisValueConfig *ui;
    QCPAxis *axis;
    AxisType axisType;
    const int dayToSecond = 24 * 60 * 60;
    //RealTimeQCP *plot;


};

#endif // AXISTIMECONFIG_H
