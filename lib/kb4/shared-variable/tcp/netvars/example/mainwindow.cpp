#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    var1 = new NetVar<double>("DoubleValue");
    var2 = new NetVar<bool>("BoolValue");
    var3 = new NetVar<QString>("StringValue");
    connect(var1,SIGNAL(newValue()),this,SLOT(updateValue1()));
    connect(var2,SIGNAL(newValue()),this,SLOT(updateValue2()));
    connect(var3,SIGNAL(newValue()),this,SLOT(updateValue3()));
    l = new QLocale(QLocale::Russian);
}

MainWindow::~MainWindow()
{
    delete ui;

    var1->deleteLater();
    var2->deleteLater();
    var3->deleteLater();
}

void MainWindow::notyfiConnection()
{
    qDebug() << "new Connection!!!!!!!";
}

void MainWindow::updateValue1()
{
    ui->V1SpinBox->setValue(var1->value());
}

void MainWindow::updateValue2()
{
    ui->checkBox->setChecked(var2->value());
}

void MainWindow::updateValue3()
{
    ui->lineEdit->setText(var3->value());
}


void MainWindow::on_pushButton_clicked()
{
    var1->send();
}

void MainWindow::on_pushButton_2_clicked()
{
    var2->send();
}

void MainWindow::on_pushButton_3_clicked()
{
    var3->send();
}

void MainWindow::on_askBt_clicked()
{
    var1->ask();
}

void MainWindow::on_askBt_2_clicked()
{
    var2->ask();
}

void MainWindow::on_askBt_3_clicked()
{
    var3->ask();
}

void MainWindow::on_V1SpinBox_valueChanged(double arg1)
{
    var1->setValue(arg1);
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    var2->setValue(checked);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    var3->setValue(arg1);
}
