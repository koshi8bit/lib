#ifndef AXISCONFIG_H
#define AXISCONFIG_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class AxisConfig;
}

class AxisConfig : public QDialog
{
    Q_OBJECT



public:
    explicit AxisConfig(QCPAxis *axis, QWidget *parent = nullptr);
    ~AxisConfig();

    enum AxisType
    {
        aeNumeric,
        aeDateTime
    };
    Q_ENUM(AxisType)


private slots:
    void on_buttonBox_accepted();

    void on_radioButtonAuto_toggled(bool checked);

private:


    Ui::AxisConfig *ui;
    QCPAxis *axis;
    AxisType axisType;


};

#endif // AXISCONFIG_H
