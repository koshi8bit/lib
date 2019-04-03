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
    static QString formatDate(QDateTime *dt);

    static QString formatDateFile(QDateTime *dt);
    static QString formatTimeFile();
    static QString formatDateTimeFileSeporator();
    static QString formatDateTimeFile(QDateTime *dt);

    static QString formatDateUi(QDateTime *dt);
    static QString formatTimeUi(QDateTime *dt, bool showMS);
    static QString formatDateTimeUiSeporator();
    static QString formatDateTimeUi(QDateTime dt);
    static QString formatDateTimeUi(QDateTime *dt);


    //errors
};

#endif // EASYLIVING_H
