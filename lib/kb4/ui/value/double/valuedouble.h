#ifndef VALUEDOUBLE_H
#define VALUEDOUBLE_H

#include <QWidget>

namespace Ui {
class ValueDouble;
}

class ValueDouble : public QWidget
{
    Q_OBJECT

public:
    explicit ValueDouble(QWidget *parent = nullptr);
    ~ValueDouble();

    void configure(QString name, QString postfix, bool readOnly = true, int fontSize = 14);
    void setValue(double newValue);

    void setName(QString newValue);
    void setPostfix(QString newValue);
    void setFontSize(int newValue);
    void setReadOnly(bool newValue);

private:
    Ui::ValueDouble *ui;
    void _setFontSize(QWidget *widget, int newValue);
};

#endif // VALUEDOUBLE_H
