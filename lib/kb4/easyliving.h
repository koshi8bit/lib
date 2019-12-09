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

    EasyLiving();

    //double
    static QString formatDouble(double value, int precision = 3, bool scientificNotation = false, DoubleSeporatorSign seporatorSign = DoubleSeporatorSign::Comma);
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
    static QString formatTimeUi(bool showMS);
    static QString formatDateTimeUiSeporator(QString seporator = "@");
    static QString formatDateTimeUi(bool showMS);


    //postfix
    static QString postfixCelsius();
    static QString postfixAmpereRu();
    static QString postfixAmpereEn();
    static QString postfixVoltRu();
    static QString postfixVoltEn();
    static QString postfixEnergyRu();
    static QString postfixEnergyEn();
    static QString postfixWattRu();
    static QString postfixSievertRu();
    static QString postfixSievertEn();
    static QString postfixSievertPerHourRu();
    static QString postfixSievertPerHourEn();
    static QString postfixFluenceRu();
    static QString postfixFluenceEn();

    static QString postfixMilliRu();
    static QString postfixMilliEn();
    static QString postfixKiloRu();
    static QString postfixKiloEn();
    static QString postfixMegaRu();
    static QString postfixMegaEn();

    static QString postfixPersent();

    static QString postfixMilliAmpereRu();
    static QString postfixMilliAmpereEn();
    static QString postfixKiloVoltRu();


    //bool
    static bool isChecked(int arg1);

    //files
    static bool createDir(QString path);

};

#endif // EASYLIVING_H
