#include "easyliving.h"

EasyLiving::EasyLiving()
{

}

QString EasyLiving::FormatDouble(double value, int precision, EasyLiving::DoubleSeporatorSign seporatorSign)
{
    if (seporatorSign == DoubleSeporatorSign::Comma)
    {
        return QLocale(QLocale::Russian).toString(value, 'f', precision);
    }

    if (seporatorSign == DoubleSeporatorSign::Point)
    {
        return QString::number(value, 'f', precision);
    }


}
