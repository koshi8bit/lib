#ifndef VALUEDOUBLE_H
#define VALUEDOUBLE_H

#include <QWidget>
#include <lib/kb4/easyliving.h>

namespace Ui {
class ValueDouble;
}

class ValueDouble : public QWidget
{
    Q_OBJECT

public:
    explicit ValueDouble(QWidget *parent = nullptr);
    ~ValueDouble();

    void configure(QString name, QString postfix, int precision = 3, bool readOnly = true, bool scientificNotation = false, int fontSize = 8);


    void setNameAndPostfix(QString name, QString postfix);
    void setFontSize(int newValue);
    void setReadOnly(bool newValue);

private:
    bool _scientificNotation;
    int _precision;
    Ui::ValueDouble *ui;
    void _setFontSize(QWidget *widget, int newValue);

public slots:
    void setValue(double newValue);
};

#endif // VALUEDOUBLE_H
