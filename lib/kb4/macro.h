#ifndef MACRO_H
#define MACRO_H
 
#define KB4_GET_VARIABLE_NAME(Variable) (#Variable)

#define KB4_IS_EQUAL_DOUBLE(A,B) qAbs(A - B) <= std::numeric_limits<double>::epsilon()

#define KB4_DATE_FORMAT "yyyy-MM-dd"

#define KB4_DATE_FILE_FORMAT KB4_DATE_FORMAT
#define KB4_TIME_FILE_FORMAT "hh-mm-ss"
#define KB4_DATETIME_FILE_FORMAT KB4_DATE_FILE_FORMAT "--" KB4_TIME_FILE_FORMAT

#define KB4_DATE_UI_FORMAT KB4_DATE_FORMAT
#define KB4_TIME_UI_FORMAT "hh:mm:ss.zzz"
#define KB4_DATETIME_UI_FORMAT KB4_DATE_UI_FORMAT "@" KB4_TIME_UI_FORMAT

#endif // MACRO_H
