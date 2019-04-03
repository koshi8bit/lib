#ifndef EASYLIVING_H
#define EASYLIVING_H

#include <QObject>
#include <QString>
#include <QLocale>
#include <QDebug>
#include <QDateTime>

#include "macro.h"

class EasyLiving : public QObject
{
    Q_OBJECT

public:
    enum DoubleSeporatorSign
    {
        Comma,
        Point
    };
    Q_ENUM(DoubleSeporatorSign)

    EasyLiving();

    //double
    static QString formatDouble(double value, int precision = 3, DoubleSeporatorSign seporatorSign = DoubleSeporatorSign::Comma);
    static bool isEqualDouble(double a, double b);


    //dateTime
    static QString formatDate();

    static QString formatDateFile();
    static QString formatTimeFile();
    static QString formatDateTimeFileSeporator();
    static QString formatDateTimeFile();

    static QString formatDateUi();
    static QString formatTimeUi(bool showMS);
    static QString formatDateTimeUiSeporator();
    static QString formatDateTimeUi();


    //postfix
    static QString postfixCelsius();
    static QString postfixAmpere();
    static QString postfixVolt();
    static QString postfixWatt();

    static QString postfixMilli();
    static QString postfixKilo();

};

#endif // EASYLIVING_H
