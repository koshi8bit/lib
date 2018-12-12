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

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AxisConfig *ui;
    QCPAxis *axis;
};

#endif // AXISCONFIG_H
