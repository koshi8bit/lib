#ifndef SCIENTIFICNOTATIONEDIT_H
#define SCIENTIFICNOTATIONEDIT_H

#include <QLineEdit>
#include <QValidator>
#include <QDoubleValidator>
#include <QLocale>
#include <QDebug>
#include <QRegExp>

class ScientificNotationEdit : public QLineEdit
{
public:
    explicit ScientificNotationEdit(QWidget *parent = nullptr);

    void setValue(double value);
    double value();

private:
    QRegExpValidator  *validator;

};

#endif // SCIENTIFICNOTATIONEDIT_H
