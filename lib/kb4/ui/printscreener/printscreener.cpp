#include "printscreener.h"
#include "ui_printscreener.h"

PrintScreener::PrintScreener(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintScreener)
{
    ui->setupUi(this);
}

PrintScreener::~PrintScreener()
{
    delete ui;
}

bool PrintScreener::save(QWidget *widget)
{
    auto defaultFileName = QDateTime::currentDateTime().toString(EasyLiving::formatDateTimeFile());
    auto defaultPath = EasyLiving::pathConcat(qApp->applicationDirPath(), defaultFileName);

    QString fileName = QFileDialog::getSaveFileName(widget, tr("Save File"),
                               defaultPath,
                               tr("PNG (*.png);;JPEG (*.jpeg *.jpg)"));

    if (fileName.isEmpty())
        return false;

    auto result = widget->grab().save(fileName);
    if (!result)
    {
        auto message = tr("Ошибка сохранения");
        qCritical() << EL_FORMAT_ERR(message);
        QMessageBox::critical(widget, tr("Error"), message);
    }
    return result;

}


void PrintScreener::on_buttonBox_clicked(QAbstractButton *button)
{
    //
}
