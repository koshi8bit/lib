#include "easyliving.h"

EasyLiving::EasyLiving()
{

}



//double
QString EasyLiving::formatDouble(double value, int precision, bool scientificNotation, EasyLiving::DoubleSeporatorSign seporatorSign)
{
    char _format= scientificNotation ? 'e' : 'f';

    switch (seporatorSign)
    {
        case DoubleSeporatorSign::Comma:
            return QLocale(QLocale::Russian).toString(value, _format, precision);

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

QString EasyLiving::postfixEnergy()
{
    return tr("Эв");
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

QString EasyLiving::formatWindowTitle(QString text)
{
    return QString("%1 /// Alexey Koshkarev AKA koshi8bit AKA kent_brockman4").arg(text);
}
