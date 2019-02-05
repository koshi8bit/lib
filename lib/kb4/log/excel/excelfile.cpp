#include "excelfile.h"

//file->close();

ExcelFile::ExcelFile(QDateTime dt, QString folder, QObject *parent) : QObject(parent)
{
    auto date = dt.toString("yyyy-MM-dd--hh-mm-ss");

    auto d = QDir(folder);
    if (!d.exists())
    {
        if (!QDir().mkdir(folder))
        {
            auto message = QString("Error creating folder <%1>").arg(folder);
            qDebug() << message;
            emit errorOcurred(message);

        }
    }

    fileName = QString("%1.xls").arg(date);
    fileName = QDir(folder).filePath(fileName);
    file = new QFile(fileName);

    if (!openFile())
    {
        auto message = QString("Error creating folder <%1>").arg(fileName);
        qDebug() << message;
        emit errorOcurred(message);
    }
}

ExcelFile::~ExcelFile()
{
    push();

    //stream->close();
    file->close();
}

void ExcelFile::append(QString message)
{
    buffer.append(message);
}

bool ExcelFile::openFile()
{
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



