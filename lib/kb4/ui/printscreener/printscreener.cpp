#include "printscreener.h"

PrintScreener::PrintScreener()
{

}

bool PrintScreener::save(QWidget *widget)
{
    auto defaultFileName = QDateTime::currentDateTime().toString(EasyLiving::formatDateTimeFile());
    auto defaultPath = EasyLiving::pathConcat(qApp->applicationDirPath(), defaultFileName);

    QString fileName = QFileDialog::getSaveFileName(widget, QObject::tr("Save File"),
                               defaultPath,
                               QObject::tr("PNG (*.png);;JPEG (*.jpeg *.jpg)"));

    if (fileName.isEmpty())
        return false;

    auto result = widget->grab().save(fileName);
    if (!result)
    {
        auto message = QObject::tr("Ошибка сохранения");
        qCritical() << EL_FORMAT_ERR(message);
        QMessageBox::critical(widget, QObject::tr("Error"), message);
    }
    return result;

}
