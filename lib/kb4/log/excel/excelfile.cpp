#include "excelfile.h"

//file->close();

ExcelFile::ExcelFile(QObject *parent) : QObject(parent)
{

}

ExcelFile::~ExcelFile()
{
    push();

    //stream->close();
    file->close();
}

bool ExcelFile::configure(QDateTime dt, QString datePattern, QString folder)
{
    auto date = dt.toString(datePattern);

    auto dir = QDir();
    if (!dir.exists(folder))
    {
        if (!dir.mkpath(folder))
        {
            auto message = KB4_FORMAT_ERR(QString("Error creating folder <%1>").arg(folder));
            qDebug() << message;
            emit errorOcurred(message);
            return false;
        }
    }

    auto fileName = QString("%1.xls").arg(date);
    fileName = QDir(folder).filePath(fileName);
    file = new QFile(fileName);

    if (!openFile())
    {
        auto message = QString("Error open file <%1>").arg(fileName);
        qDebug() << message;
        emit errorOcurred(message);
        return false;
    }

    return true;
}

void ExcelFile::append(QString message)
{
    buffer.append(message);
}

bool ExcelFile::openFile()
{
    _isCreated = !file->exists();
    if (file->open(QIODevice::WriteOnly | QIODevice::Append))
    {
        stream = new QTextStream(file);
        return true;
    }
    return false;
}

bool ExcelFile::push()
{
    auto sizeBefore = file->size();
    *stream << buffer;
    stream->flush();
    auto sizeAfter = file->size();

    if(sizeAfter - sizeBefore > 0)
    {
        buffer.clear();
        return true;
    }
    file->close();
    openFile();
    return false;
}

bool ExcelFile::isCreated()
{
    return _isCreated;
}

QString ExcelFile::fileName()
{
    return file->fileName();
}



