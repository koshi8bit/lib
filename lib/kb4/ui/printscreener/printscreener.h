#ifndef PRINTSCREENER_H
#define PRINTSCREENER_H

#include <QAbstractButton>
#include <QDialog>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include <lib/kb4/easyliving.h>

namespace Ui {
class PrintScreener;
}

class PrintScreener : public QDialog
{
    Q_OBJECT

public:
    explicit PrintScreener(QWidget *parent = nullptr);
    ~PrintScreener();

    static bool save(QWidget *widget);


private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::PrintScreener *ui;
};

#endif // PRINTSCREENER_H
