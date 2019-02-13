#ifndef MACRO_H
#define MACRO_H
 
//variables
#define KB4_GET_VARIABLE_NAME(Variable) (#Variable)

//double
#define KB4_FORMAT_DOUBLE(value) QString::number(value, 'f', 2)
#define KB4_IS_EQUAL_DOUBLE(A,B) qAbs(A - B) <= std::numeric_limits<double>::epsilon()

//dateTime
#define KB4_FORMAT_DATE "yyyy-MM-dd"

#define KB4_FORMAT_DATE_FILE KB4_FORMAT_DATE
#define KB4_FORMAT_TIME_FILE "hh-mm-ss"
#define KB4_FORMAT_DATETIME_FILE_SEPORATOR "--"
#define KB4_FORMAT_DATETIME_FILE KB4_FORMAT_DATE_FILE KB4_FORMAT_DATETIME_FILE_SEPORATOR KB4_FORMAT_TIME_FILE

#define KB4_FORMAT_DATE_UI KB4_FORMAT_DATE
#define KB4_FORMAT_TIME_UI_MS "hh:mm:ss.zzz"
#define KB4_FORMAT_TIME_UI_NO_MS "hh:mm:ss"
#define KB4_FORMAT_DATETIME_UI_SEPORATOR "@"
#define KB4_FORMAT_DATETIME_UI KB4_FORMAT_DATE_UI KB4_FORMAT_DATETIME_UI_SEPORATOR KB4_FORMAT_TIME_UI_MS

//errors
#define KB4_FORMAT_ERR(message) (QStringList() << "ACHTUNG! " << Q_FUNC_INFO << ": " << message).join("")

//postfix
#define KB4_POSTFIX_CELSIUS "°C"
#define KB4_POSTFIX_AMPERE "А"
#define KB4_POSTFIX_VOLT "В"
#define KB4_POSTFIX_WATT "Вт"

#define KB4_POSTFIX_KILO "к"
#define KB4_POSTFIX_MILLI "м"

#endif // MACRO_H
