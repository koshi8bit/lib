#ifndef FAULTSWIDGET_H
#define FAULTSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>

#include <lib/kb4/easyliving.h>

#include "fault.h"


class FaultsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FaultsWidget(QScrollArea *widget = nullptr);
    void addFault(Fault *fault);

    void configureBorder(QLabel* tl, QLabel* t, QLabel* tr, QLabel* l, QLabel* r, QLabel* bl, QLabel* b, QLabel* br);
    void showFaultBorder(bool fault, QStringList faults = {});

    QStringList faults();

    bool isFaultTriggered() const;

private:
    QVBoxLayout *layoutFaults;
    QVector<Fault*> _faults;
    bool _isFaultTriggered = false;

    void triggerFault(bool triggered);

    QVector<QLabel*> border;
    QVector<QLabel*> borderMessage;

    QString _template;

signals:
    void faultTriggered(bool fault);

};

#endif // FAULTSWIDGET_H
