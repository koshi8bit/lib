#ifndef AXISCONFIG_H
#define AXISCONFIG_H

#include <QWidget>

#include "qcustomplot.h"

namespace Ui {
class AxisConfig;
}

class AxisConfig : public QWidget
{
    Q_OBJECT

public:
    explicit AxisConfig(QCPAxis *axis, QWidget *parent = nullptr);
    ~AxisConfig();

private:
    Ui::AxisConfig *ui;
    QCPAxis *axis;
};

#endif // AXISCONFIG_H
