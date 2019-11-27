#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "netvars/netvars.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void notyfiConnection();

private slots:
    void updateValue1();
    void updateValue2();
    void updateValue3();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_askBt_clicked();

    void on_askBt_2_clicked();

    void on_askBt_3_clicked();

    void on_V1SpinBox_valueChanged(double arg1);

    void on_checkBox_toggled(bool checked);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    NetVar<double> * var1;
    NetVar<bool> * var2;
    NetVar<QString> * var3;
    QLocale *l;
};
#endif // MAINWINDOW_H
