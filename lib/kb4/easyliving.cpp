#include "easyliving.h"

EasyLiving::EasyLiving()
{

}

//double
QString EasyLiving::formatDouble(double value, int precision, EasyLiving::DoubleSeporatorSign seporatorSign)
{
    if (seporatorSign == DoubleSeporatorSign::Comma)
    {
        return QLocale(QLocale::Russian).toString(value, 'f', precision);
    }

    if (seporatorSign == DoubleSeporatorSign::Point)
    {
        return QString::number(value, 'f', precision);
    }

    auto message = KB4_FORMAT_ERR("Invalid seporator sign!");
    qDebug() << message;
    return message;
}

bool EasyLiving::isEqualDouble(double a, double b)
{
    return qAbs(a - b) <= std::numeric_limits<double>::epsilon();
}


//dateTime
QString EasyLiving::formatDate(QDateTime *dt)
{
    return dt->toString("yyyy-MM-dd");
}

QString EasyLiving::formatDateFile(QDateTime *dt)
{
    return formatDate(dt);
}

QString EasyLiving::formatTimeFile()
{
    return "hh-mm-ss";
}

QString EasyLiving::formatDateTimeFileSeporator()
{
    return "--";
}

QString EasyLiving::formatDateTimeFile(QDateTime *dt)
{
    return formatDateFile(dt) + formatDateTimeFileSeporator() + formatTimeFile();
}

QString EasyLiving::formatDateUi(QDateTime *dt)
{
    return formatDate(dt);
}

QString EasyLiving::formatTimeUi(QDateTime *dt, bool showMS)
{
    QString format = "hh:mm:ss";
    if (showMS)
        format += ".zzz";
    return dt->toString(format);
}

QString EasyLiving::formatDateTimeUiSeporator()
{
    return "@";
}

QString EasyLiving::formatDateTimeUi(QDateTime dt)
{
    return formatDateTimeUi(&dt);
}

QString EasyLiving::formatDateTimeUi(QDateTime *dt)
{
    return formatDateUi(dt) + formatDateTimeUiSeporator() + formatTimeUi(dt, true);
}
