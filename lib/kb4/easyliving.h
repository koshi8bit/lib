#ifndef EASYLIVING_H
#define EASYLIVING_H

//https://github.com/koshi8bit/lib

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
//R"(raw\string)"
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
    static QLocale localeMy;
    //fixme double value, int precision = 3, bool scientificNotation = false, bool showGroupSeparator = false, bool seporatorPoint = false)
    static QString formatDouble(double value, int precision = 3, bool scientificNotation = false, DoubleSeporatorSign seporatorSign = DoubleSeporatorSign::Comma, bool showGroupSeparator = true);
    static bool isBetween(double value, double min, double max);
    static bool isEqualDouble(double a, double b);


    //dateTime
    static bool isBetween(QDateTime value, QDateTime min, QDateTime max);
    static QString formatDate();

    static QString formatDateFile();
    static QString formatTimeFile();
    static QString formatDateTimeFileSeporator();
    static QString formatDateTimeFile();

    static QString formatDateUi();
    static QString formatTimeUi(bool showMS = false);
    static QString formatDateTimeUiSeporator(QString seporator = "@");
    static QString formatDateTimeUi(bool showMS = false);


    //postfix
    static QString postfixCelsius();
    static QString postfixAmpere();
    static QString postfixAmpereEn();
    static QString postfixVolt();
    static QString postfixVoltEn();
    static QString postfixEnergy();
    static QString postfixEnergyEn();
    static QString postfixWatt();
    static QString postfixSievert();
    static QString postfixSievertEn();
    static QString postfixSievertPerHour();
    static QString postfixSievertPerHourEn();
    static QString postfixFluence();
    static QString postfixFluenceEn();

    static QString postfixMilli();
    static QString postfixMilliEn();
    static QString postfixKilo();
    static QString postfixKiloEn();
    static QString postfixMega();
    static QString postfixMegaEn();

    static QString postfixPersent();

    static QString postfixMilliAmpere();
    static QString postfixMilliAmpereEn();
    static QString postfixKiloVolt();
    static QString postfixKiloVoltEn();


    //bool
    static bool isChecked(int arg1);

    //files
    static bool createDir(QString path);
    static bool writeFile(QString path, QString text, bool append = false);
    static QString readFile(QString path);

    //ui
    static QString formatWindowTitle(QString text);

};

#endif // EASYLIVING_H
