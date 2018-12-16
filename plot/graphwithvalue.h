#ifndef GRAPHWITHVALUE_H
#define GRAPHWITHVALUE_H

#include "qcustomplot.h"


class GraphWithValue : public QObject
{
    Q_OBJECT
public:
    explicit GraphWithValue(QObject *parent = nullptr);
private:
    QString label;
    double value; // ?
    QColor color;
    bool visible;
    //ValueScaler valueScaler;
    QCPItemTracer tracer;
    QCPGraph graph;

signals:

public slots:
};

#endif // GRAPHWITHVALUE_H
