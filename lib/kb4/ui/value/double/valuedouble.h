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
    void configure(ChannelDouble *channel, bool hideSetWidget = true, int fontSize = 10, bool connectSlot = true);
    void setRangeSetter(double min, double max);

    QString name() const;
    void setName(const QString &name);

    int precision() const;
    void setPrecision(int precision);

    bool scientificNotation() const;
    void setScientificNotation(bool scientificNotation);

    double value() const;

    void setNameAndPostfix(QString name, QString postfix);
    void setFontSize(int newValue);
    void setTrusted(bool newValue);

    QLineEdit *valueWidget();

    const static QString trustedColor;
    const static QString notTrustedColor;





private:
    int _precision;
    bool _scientificNotation;
    double _value;
    QString _name;
    Ui::ValueDouble *ui;
    void _setFontSize(QWidget *widget, int newValue);

    void setColor(QWidget *widget, QString newColor);

    void setMaxWidth();
    
signals:
    void valueChanged(double newValue);
    void valueCopyedToClipboard(QString newValue, QString message);


public slots:
    void setValue(double newValue);

private slots:
    void on_pushButtonSet_clicked();
    void on_doubleSpinBoxValueSet_editingFinished();

    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // VALUEDOUBLE_H
