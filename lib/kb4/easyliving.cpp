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

QString EasyLiving::formatDateTimeUiSeporator()
{
    return "@";
}

QString EasyLiving::formatDateTimeUi()
{
    return formatDateUi() + formatDateTimeUiSeporator() + formatTimeUi(true);
}

QString EasyLiving::postfixCelsius()
{
    return "°C";
}

QString EasyLiving::postfixAmpere()
{
    return "А";
}

QString EasyLiving::postfixMilli()
{
    return "м";
}
