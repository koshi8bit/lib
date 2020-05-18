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

    void on_checkBoxScientificNotationAxis_toggled(bool checked);

    void on_checkBoxAutoscale_toggled(bool checked);

private:
    Ui::AxisValueConfig *ui;
    const QString scientificNotationFormat = "eb", standatrFormat = "f";
    QCPAxis *axis;
    AxisType axisType;

};

#endif // AXISVALUECONFIG_H
