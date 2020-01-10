#include "simplelog.h"


SimpleLog::SimpleLog(QString path, bool append, QObject *parent)
    : QObject(parent)
{
    file = new QFile(path);
    QIODevice::OpenMode flags = QIODevice::WriteOnly;
    if (append) {
        flags |= QIODevice::Append;
    }

    if (file->open(flags)) {
        stream.setDevice(file);
    }
    else
    {
        qCritical() << EL_FORMAT_ERR("Stream open err") << file->errorString();
    }
}

SimpleLog::~SimpleLog()
{
    file->close();
    file->deleteLater();
}

void SimpleLog::append(QString message, bool critical)
{
    auto formattedMessage = QString("%1 %2\n")
            .arg(QDateTime::currentDateTime().toString(EasyLiving::formatDateTimeUi(true)))
            .arg(message);

    if (critical)
    {
        qDebug() << message;
    }
    else
    {
        qCritical() << message;
    }


    stream.flush();
}





//ostream &operator<<(ostream &os, const SimpleLog &sl)
//{
//    qDebug() << "aa";
//    return os;
//}
