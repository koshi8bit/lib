#ifndef VALUEDOUBLE_H
#define VALUEDOUBLE_H

#include <QWidget>
#include <QLineEdit>

#include <lib/kb4/easyliving.h>
#include <lib/kb4/log/channeldouble.h>

namespace Ui {
class ValueDouble;
}

class ValueDouble : public QWidget
{
    Q_OBJECT

public:
    explicit ValueDouble(QWidget *parent = nullptr);
    ~ValueDouble();

    void configure(QString name, QString postfix, int precision = 3, bool hideSetWidget = true, bool scientificNotation = false, int fontSize = 10);
    void configure(ChannelDouble *channel, int precision = 3, bool hideSetWidget = true, bool scientificNotation = false, int fontSize = 10);
    void setRangeSetter(double min, double max);


    void setNameAndPostfix(QString name, QString postfix);
    void setFontSize(int newValue);
    void setTrusted(bool newValue);

    QLineEdit *valueWidget();

    const static QString trustedColor;
    const static QString notTrustedColor;

private:
    bool _scientificNotation;
    int _precision;
    Ui::ValueDouble *ui;
    void _setFontSize(QWidget *widget, int newValue);

    void setColor(QWidget *widget, QString newColor);

    void setMaxWidth();
    
signals:
    void valueChanged(double newValue);


public slots:
    void setValue(double newValue);
private slots:
    void on_pushButtonSet_clicked();
    void on_doubleSpinBoxValueSet_editingFinished();
};

#endif // VALUEDOUBLE_H
