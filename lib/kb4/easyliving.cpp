#include "easyliving.h"

EasyLiving::EasyLiving()
{

}



//double
QString EasyLiving::formatDouble(double value, int precision, bool scientificNotation, EasyLiving::DoubleSeporatorSign seporatorSign)
{
    char _format;
    if (scientificNotation)
    {
        _format='e';
    }
    else
    {
        _format='f';
    }

    if (seporatorSign == DoubleSeporatorSign::Comma)
    {
        return QLocale(QLocale::Russian).toString(value, _format, precision);
    }

    if (seporatorSign == DoubleSeporatorSign::Point)
    {
        return QString::number(value, _format, precision);
    }

    auto message = EL_FORMAT_ERR("Invalid seporator sign!");
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

QString EasyLiving::postfixVolt()
{
    return "В";
}

QString EasyLiving::postfixWatt()
{
    return "Вт";
}

QString EasyLiving::postfixSievert()
{
    return "Зв";
}

QString EasyLiving::postfixSievertPerHour()
{
    return postfixSievert() + "/Ч";
}

QString EasyLiving::postfixFluence()
{
    return "Кл";
}

QString EasyLiving::postfixMilli()
{
    return "м";
}

QString EasyLiving::postfixKilo()
{
    return "к";
}

QString EasyLiving::postfixPersent()
{
    return "%";
}

QString EasyLiving::postfixMilliAmpere()
{
    return postfixMilli() + postfixAmpere();
}

QString EasyLiving::postfixKiloVolt()
{
    return EasyLiving::postfixKilo() + EasyLiving::postfixVolt();
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
