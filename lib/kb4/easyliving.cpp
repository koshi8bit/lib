#include "easyliving.h"

QLocale EasyLiving::localeMy = QLocale(QLocale::Russian);

EasyLiving::EasyLiving()
{
    //THIS IS NOT STATIC CONSTRUCTOR
    //localeMy.setNumberOptions(QLocale::OmitGroupSeparator);
}



//double
QString EasyLiving::formatDouble(double value, int precision, bool scientificNotation, EasyLiving::DoubleSeporatorSign seporatorSign, bool showGroupSeparator)
{
    char _format= scientificNotation ? 'e' : 'f';

    switch (seporatorSign)
    {
        case DoubleSeporatorSign::Comma:
            if (showGroupSeparator)
            {
                return QLocale(QLocale::Russian).toString(value, _format, precision);
            }
            else
            {
                localeMy.setNumberOptions(QLocale::OmitGroupSeparator);
                return localeMy.toString(value, _format, precision);
            }

        case DoubleSeporatorSign::Point:
            return QString::number(value, _format, precision);
    }

    auto message = EL_FORMAT_ERR(tr("Invalid seporator sign!"));
    qDebug() << message;
    return message;
}

bool EasyLiving::isBetween(double value, double min, double max)
{
    return (value >= min) && (value <= max);
}

bool EasyLiving::isEqualDouble(double a, double b)
{
    return qAbs(a - b) <= std::numeric_limits<double>::epsilon();
}

bool EasyLiving::isBetween(QDateTime value, QDateTime min, QDateTime max)
{
    return (value >= min) && (value <= max);
}

QString EasyLiving::dateTimeDelta(QDateTime begin, QDateTime end, bool daysOnly, bool showMs)
{
    int years=0, months=0, days, hours, minutes, seconds, milliseconds;

    EasyLiving::dateTimeDelta(begin, end, years, months, days,
                              hours, minutes, seconds, milliseconds, daysOnly);
    QTime time(hours, minutes, seconds, milliseconds);

    QString message;

    messageAppend(message, years, "y");
    messageAppend(message, months, "m", (years!=0));
    messageAppend(message, days, "d", (years!=0)||(months!=0));
    message.append(time.toString(EasyLiving::formatTimeUi(showMs)));
    return message;
}


void EasyLiving::messageAppend(QString &message, int value, QString postfix, bool forseAppend)
{
    if ((value != 0) || forseAppend)
    {
        message.append(QString("%1%2 ")
                       .arg(value, 2, 10, QChar('0'))
                       .arg(postfix));
    }
}

void EasyLiving::dateTimeDelta(QDateTime begin, QDateTime end, int &years, int &month, int &days,
                               int &hours, int &minutes, int &seconds, int &milliseconds, bool daysOnly)
{
    auto delta = qAbs(begin.toMSecsSinceEpoch() - end.toMSecsSinceEpoch());

    del(delta, milliseconds, 1000);
    del(delta, seconds, 60);
    del(delta, minutes, 60);
    del(delta, hours, 24);

    if (daysOnly)
    {
        days = static_cast<int>(delta);
    }
    else
    {
        del(delta, days, 30);
        del(delta, month, 12);
        years = static_cast<int>(delta);
    }
}

void EasyLiving::del(long long &delta, int &v, int divider)
{
    v = static_cast<int>(delta % divider);
    delta /= divider;
}



//dateTime
QString EasyLiving::formatDate()
{
    return "yyyy-MM-dd";
}

QString EasyLiving::formatDateFile()
{
    return formatDate();
}

QString EasyLiving::formatTimeFile()
{
    return "hh-mm-ss";
}

QString EasyLiving::formatDateTimeFileSeporator()
{
    return "--";
}

QString EasyLiving::formatDateTimeFile()
{
    return formatDateFile() + formatDateTimeFileSeporator() + formatTimeFile();
}

QString EasyLiving::formatDateUi()
{
    return formatDate();
}

QString EasyLiving::formatTimeUi(bool showMS)
{
    QString format = "hh:mm:ss";
    if (showMS)
        format += ".zzz";
    return format;
}

QString EasyLiving::formatDateTimeUiSeporator(QString seporator)
{
    return seporator;
}

QString EasyLiving::formatDateTimeUi(bool showMS)
{
    return formatDateUi() + formatDateTimeUiSeporator() + formatTimeUi(showMS);
}

QString EasyLiving::postfixCelsius()
{
    return tr("°C");
}

QString EasyLiving::postfixAmpere()
{
    return tr("А");
}

QString EasyLiving::postfixAmpereEn()
{
    return "A";
}

QString EasyLiving::postfixVolt()
{
    return tr("В");
}

QString EasyLiving::postfixVoltEn()
{
    return tr("V");
}

QString EasyLiving::postfixEnergy()
{
    return tr("эВ");
}

QString EasyLiving::postfixEnergyEn()
{
    return "eV";
}

QString EasyLiving::postfixWatt()
{
    return tr("Вт");
}

QString EasyLiving::postfixSievert()
{
    return tr("Зв");
}

QString EasyLiving::postfixSievertEn()
{
    return "Sv";
}

QString EasyLiving::postfixSievertPerHour()
{
    return postfixSievert() + tr("/Ч");
}

QString EasyLiving::postfixSievertPerHourEn()
{
    return postfixSievertEn() + "/h";
}

QString EasyLiving::postfixFluence()
{
    return tr("Кл");
}

QString EasyLiving::postfixFluenceEn()
{
    return "C";
}

QString EasyLiving::postfixMilli()
{
    return tr("м");
}

QString EasyLiving::postfixMilliEn()
{
    return "m";
}

QString EasyLiving::postfixKilo()
{
    return tr("к");
}

QString EasyLiving::postfixKiloEn()
{
    return "k";
}

QString EasyLiving::postfixMega()
{
    return tr("М");
}

QString EasyLiving::postfixMegaEn()
{
    return "M";
}

QString EasyLiving::postfixPersent()
{
    return tr("%");
}

QString EasyLiving::postfixMilliAmpere()
{
    return postfixMilli() + postfixAmpere();
}

QString EasyLiving::postfixMilliAmpereEn()
{
    return postfixMilliEn() + postfixAmpere();
}

QString EasyLiving::postfixKiloVolt()
{
    return EasyLiving::postfixKilo() + EasyLiving::postfixVolt();
}

QString EasyLiving::postfixKiloVoltEn()
{
    return postfixKiloEn() + postfixVoltEn();
}

bool EasyLiving::isChecked(int arg1)
{
    return arg1 == 2 ? true : false;
}

bool EasyLiving::createDir(QString path)
{
    QDir dir(path);
    if (!dir.exists()){
      dir.mkdir(".");
    }

    return dir.exists();
}

bool EasyLiving::writeFile(QString path, QString text, bool append)
{
    QFile file(path);
    QIODevice::OpenMode flags = QIODevice::WriteOnly;
    if (append) {
        flags |= QIODevice::Append;
    }

    if (file.open(flags)) {
        QTextStream stream(&file);
        stream << text;
        return true;
    }
    else
    {
        return false;
    }
}

QString EasyLiving::readFile(QString path)
{
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << EL_FORMAT_ERR("error opening file: ") << file.error();
        return "";
    }

    QTextStream instream(&file);
    QString line = instream.readAll();

    file.close();
    return line;

}

QString EasyLiving::pathConcat(QString path1, QString path2)
{
    path1 = QDir::fromNativeSeparators(path1);
    path2 = QDir::fromNativeSeparators(path2);
    auto finalPath = QDir(path1).filePath(path2);
    return finalPath;
}

QString EasyLiving::formatWindowTitle(QString text)
{
    return QString("%1 /// Aleksey K. [koshi8bit]").arg(text);
}


