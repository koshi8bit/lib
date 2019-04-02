#ifndef EASYLIVING_H
#define EASYLIVING_H

#include <QObject>
#include <QString>
#include <QLocale>

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

    static QString FormatDouble(double value, int precision = 3, DoubleSeporatorSign seporatorSign = DoubleSeporatorSign::Comma);
};

#endif // EASYLIVING_H
