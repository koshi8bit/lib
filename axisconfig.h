#ifndef AXISCONFIG_H
#define AXISCONFIG_H

#include <QWidget>

namespace Ui {
class AxisConfig;
}

class AxisConfig : public QWidget
{
    Q_OBJECT

public:
    explicit AxisConfig(QWidget *parent = nullptr);
    ~AxisConfig();

private:
    Ui::AxisConfig *ui;
};

#endif // AXISCONFIG_H
