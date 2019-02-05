#ifndef MACRO_H
#define MACRO_H
 
#define GET_VARIABLE_NAME(Variable) (#Variable)

#define IS_EQUAL_DOUBLE(A,B) qAbs(A - B) <= std::numeric_limits<double>::epsilon()

#endif // MACRO_H
