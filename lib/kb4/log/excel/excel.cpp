#include "excel.h"

const QString Excel::elementDelimeter = "\t";
const QString Excel::lineDelimeter = "\r\n";




Excel::Excel(HeaderMode headerMode, QString externalFolder, QObject *parent)
    : Log(parent)
{
    auto date = QDateTime::currentDateTime();
    local = new ExcelFile(date, QString("./log"));
    remote = new ExcelFile(date, externalFolder);

    this->headerMode = headerMode;
}



Excel::~Excel()
{
    finalPush(local);
    finalPush(remote);
}

void Excel::finalPush(ExcelFile *excelFile)
{
    if (excelFile->push())
    {
        delete excelFile;
    }
    else
    {
        emit errorOcurred(QString("Final push failed <%1>").arg(excelFile->fileName));
    }
}

void Excel::appendToBuffers(QString message)
{
    local->append(message);
    remote->append(message);
}

void Excel::finishConfigure()
{
    QString line;

    if (headerMode.testFlag(Excel::PlotText))
    {
        auto prefix = headersPrefix(TimePrefixLanguage::Ru);

        if (!prefix.isEmpty())
            line.append(prefix);

        foreach (auto channel, channels)
        {
            line.append(channel->plotText());
            line.append(elementDelimeter);
        }
        appendToBuffers(line);
        appendToBuffers(lineDelimeter);
        line.clear();
    }

    if (headerMode.testFlag(Excel::LogName))
    {
        auto prefix = headersPrefix(TimePrefixLanguage::En);

        if (!prefix.isEmpty())
            line.append(prefix);

        foreach (auto channel, channels)
        {
            line.append(channel->logName().join("."));
            line.append(elementDelimeter);
        }
        appendToBuffers(line);
        appendToBuffers(lineDelimeter);
        line.clear();
    }


}




void Excel::push()
{
    local->push();
    remote->push();
}

QString Excel::formatDoubleValue(double value)
{
    if (qAbs(value - 0) <= std::numeric_limits<double>::epsilon())
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
