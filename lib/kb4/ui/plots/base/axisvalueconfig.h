#ifndef AXISVALUECONFIG_H
#define AXISVALUECONFIG_H

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
    explicit AxisValueConfig(QCPAxis *axis, QWidget *parent = nullptr);
    ~AxisValueConfig();


    enum AxisType
    {
        NumericStandardNotation,
        NumericScientificNotation
    };
    Q_ENUM(AxisType)


private slots:
    void on_buttonBox_accepted();

    void on_radioButtonAuto_toggled(bool checked);

    void on_checkBoxLog10_stateChanged(int arg1);


private:
    Ui::AxisValueConfig *ui;
    QCPAxis *axis;
    AxisType axisType;

};

#endif // AXISVALUECONFIG_H
