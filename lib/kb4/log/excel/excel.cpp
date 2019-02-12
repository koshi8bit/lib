#include "excel.h"

const QString Excel::elementDelimeter = "\t";
const QString Excel::lineDelimeter = "\r\n";

//TODO clean from currentSession
Excel::Excel(QObject *parent)
    : Log(parent)
{

}

Excel::~Excel()
{
    delete currentSession;
    delete currentDay;

//    finalPush(currentSession);
//    finalPush(currentDay);
}

void Excel::configure(QString path, HeaderMode headerMode)
{
    auto _path = QDir(path);
    auto date = QDateTime::currentDateTime();

    currentDay = new ExcelFile(this);
    connect(currentDay, &ExcelFile::errorOcurred, this, &Excel::errorOcurred);
    currentDay->configure(date, KB4_FORMAT_DATE_FILE, _path.filePath(".days"));

    currentSession = new ExcelFile(this);
    connect(currentSession, &ExcelFile::errorOcurred, this, &Excel::errorOcurred);
    currentSession->configure(date, KB4_FORMAT_DATETIME_FILE, _path.filePath(".sessions"));

    this->headerMode = headerMode;
}

//void Excel::finalPush(ExcelFile *excelFile)
//{
//    if (excelFile->push())
//    {
//        delete excelFile;
//    }
//    else
//    {
//        emit errorOcurred(KB4_FORMAT_ERR(QString("Final push failed <%1>").arg(excelFile->fileName())));
//    }
//}

void Excel::appendToBuffers(QString message, bool addToCurrentDay)
{
    currentSession->append(message);
    if (addToCurrentDay)
        currentDay->append(message);
}

void Excel::finishConfigureChild()
{
    QString line;
    auto addToCurrentDay = currentDay->isCreated();

    if (headerMode.testFlag(Excel::PlotName))
    {
        auto prefix = headersPrefix();

        if (!prefix.isEmpty())
            line.append(prefix);

        foreach (auto channel, channels)
        {
            line.append(channel->plotName());
            line.append(elementDelimeter);
        }
        appendToBuffers(line, addToCurrentDay);
        appendToBuffers(lineDelimeter, addToCurrentDay);
        line.clear();
    }

    if (headerMode.testFlag(Excel::LogName))
    {
        auto prefix = headersPrefix();

        if (!prefix.isEmpty())
            line.append(prefix);

        foreach (auto channel, channels)
        {
            line.append(channel->logName());
            line.append(elementDelimeter);
        }
        appendToBuffers(line, addToCurrentDay);
        appendToBuffers(lineDelimeter, addToCurrentDay);
        line.clear();
    }

}


void Excel::push()
{
    currentSession->push();
    currentDay->push();
}

QString Excel::formatDoubleValue(double value)
{
    if (KB4_IS_EQUAL_DOUBLE(value, 0))
    {
        return QString("0");
    }

    if ((0.1 < value) && (value < 2000))
    {
        return  QLocale(QLocale::Russian).toString(value, 'f', 2);
    }
    else
    {
        return  QLocale(QLocale::Russian).toString(value, 'e', 2);
    }
}

void Excel::commit()
{
    QString line;
    QString value;

    auto prefix = commitPrefix();
    if (!prefix.isEmpty())
        line.append(prefix);

    foreach (auto channel, this->channels)
    {
        auto channel_double = dynamic_cast<ChannelT<double> *>(channel);
        if (channel_double)
        {
            value = formatDoubleValue(channel_double->value());


            //value = QString("%1").arg(channel_double->value(), 0, 'e', 2, '0');
            line.append(value);
            line.append(elementDelimeter);
            continue;
        }

        auto channel_bool = dynamic_cast<ChannelT<bool> *>(channel);
        if (channel_bool)
        {
            value = QString("%1").arg(channel_bool->value() ? 1 : 0);
            line.append(value);
            line.append(elementDelimeter);
            continue;
        }
    }
    appendToBuffers(line);
    appendToBuffers(lineDelimeter);
}
