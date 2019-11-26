#ifndef EASYLIVING_H
#define EASYLIVING_H

#include <QObject>
#include <QString>
#include <QLocale>
#include <QDebug>
#include <QDateTime>
#include <QDir>

//errors
#define EL_FORMAT_ERR(message) (QStringList() << "ACHTUNG! " << Q_FUNC_INFO << ": " << message).join("")

//variables
#define EL_GET_VARIABLE_NAME(Variable) (#Variable)

//raw string
//???
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

    enum Format
    {
        StandardNotation,    // f
        ScientificNotation   // e
    };
    Q_ENUM(Format)

    EasyLiving();

    //double
    static QString formatDouble(double value, int precision = 3, Format format = Format::StandardNotation, DoubleSeporatorSign seporatorSign = DoubleSeporatorSign::Comma);
    static bool isBetween(double value, double min, double max);
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
    static QString postfixSievert();
    static QString postfixSievertPerHour();

    static QString postfixMilli();
    static QString postfixKilo();

    static QString postfixPersent();

    static QString postfixMilliAmpere();


    //bool
    static bool isChecked(int arg1);

    //files
    static bool createDir(QString path);

};

#endif // EASYLIVING_H
