#ifndef FILTERXAXIS_H
#define FILTERXAXIS_H

#include <QObject>
#include <QEvent>
#include <QDebug>

#include <lib/kb4/ui/qcustomplot/qcustomplot.h>

class FilterXAxis : public QObject
{
    Q_OBJECT
public:
    explicit FilterXAxis(QObject *parent = nullptr);

signals:


    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // FILTERXAXIS_H
