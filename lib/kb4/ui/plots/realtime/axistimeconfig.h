#ifndef AXISTIMECONFIG_H
#define AXISTIMECONFIG_H

#include <QDialog>
#include <lib/kb4/ui/qcustomplot/qcustomplot.h>

//#include <lib/kb4/ui/realtimeqcp/realtimeqcp.h>
#include <lib/kb4/easyliving.h>

namespace Ui {
class AxisTimeConfig;
}

class AxisTimeConfig : public QDialog
{
    Q_OBJECT



public:
    explicit AxisTimeConfig(QCPAxis *axis, QWidget *parent = nullptr);
    ~AxisTimeConfig();


private slots:
    void on_buttonBox_accepted();


    void on_spinBoxFullSec_valueChanged(int arg1);
    void spinBoxDaysHoursMinutesSecondsValueChanged(int arg1);

    void on_pushButtonTime010000_clicked();
    void on_pushButtonTime001000_clicked();
    void on_pushButtonTime000500_clicked();
    void on_pushButtonTime000100_clicked();
    void on_pushButtonTime000030_clicked();


private:
    Ui::AxisTimeConfig *ui;
    QCPAxis *axis;
    const int dayToSecond = 24 * 60 * 60;
    //RealTimeQCP *plot;


};

#endif // AXISTIMECONFIG_H
