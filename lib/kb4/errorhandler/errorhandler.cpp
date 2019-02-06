#include "errorhandler.h"

const QString ErrorHandler::errorSave = "Возникла критическая ошибка!\nНевозможно сохранить файл.\nПокажи это окно Лехе (или сфотай и отправь через WatsUp)";
const QString ErrorHandler::errorSend = "Возникла критическая ошибка!\nОтправка логов не удалась, но логи сохранены в файл.\nСообщи Лехе!";
const QString ErrorHandler::okSend = "Возникла критическая ошибка!\nЛоги отправлены Лехе!";

ErrorHandler::ErrorHandler(QObject *parent) : QObject(parent)
{

}

void ErrorHandler::showErrorMessage(QString messageToUser, QString error)
{
    QMessageBox mb;
    mb.setText(messageToUser);
    mb.setInformativeText(error);
    mb.setIcon(QMessageBox::Critical);
    mb.exec();
}

void ErrorHandler::errorOccurred(QString error)
{
    auto date = QDateTime::currentDateTime().toString(KB4_FORMAT_DATETIME_FILE);
    auto fileName = QString("crash-%1.log").arg(date);
    auto file = new QFile(fileName);

    if (!file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << error;
        showErrorMessage(errorSave, error);
        return;
    }

    auto stream = new QTextStream(file);
    *stream << error;
    stream->flush();
    file->close();

    if (file->size() == 0)
    {
        showErrorMessage(errorSave, error);
        return;
    }

    showErrorMessage(errorSend, file->fileName());
    QCoreApplication::exit(-1);

}

