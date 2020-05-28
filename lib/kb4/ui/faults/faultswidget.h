#ifndef FAULTSWIDGET_H
#define FAULTSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>

#include <lib/kb4/easyliving.h>
#include <lib/kb4/log/channelqstring.h>

#include "fault.h"


class FaultsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FaultsWidget(QScrollArea *widget = nullptr);
    void addFault(Fault *fault);

    void configureBorder(QLabel* tl, QLabel* t, QLabel* tr, QLabel* l, QLabel* r, QLabel* bl, QLabel* b, QLabel* br);
    void showFaultBorder(QString str);
    void showFaultBorder(QStringList faults);
    void hideFaultBorder();

    QString faults();

    bool isFaultTriggered() const;




private:
    const QString joiner = "<br/>";
    QVBoxLayout *layoutFaults;
    QVector<Fault*> _faults;
    bool _isFaultTriggered = false;


    QVector<QLabel*> border;
    QVector<QLabel*> borderMessage;

    QString _template;

signals:
    void faultTriggered(bool fault, QString faults);

public slots:
    void triggerFaults(QString faults);

};

#endif // FAULTSWIDGET_H
