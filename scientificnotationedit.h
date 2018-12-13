#ifndef SCIENTIFICNOTATIONEDIT_H
#define SCIENTIFICNOTATIONEDIT_H

#include <QLineEdit>
#include <QValidator>
#include <QDoubleValidator>
#include <QLocale>
#include <QDebug>

class ScientificNotationEdit : public QLineEdit
{
public:
    explicit ScientificNotationEdit(QWidget *parent = nullptr);

    void setValue(double value);
    double value();

};

#endif // SCIENTIFICNOTATIONEDIT_H
