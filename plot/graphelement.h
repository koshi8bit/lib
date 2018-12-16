#ifndef GRAPHWITHVALUE_H
#define GRAPHWITHVALUE_H

#include <QColor>
#include "qcustomplot.h"


class GraphElement : public QObject
{
    Q_OBJECT
public:
    explicit GraphElement(const QString &label, QColor color, QCustomPlot *plot, QCPAxis *yAxis, QObject *parent = nullptr);
    virtual ~GraphElement();

    QCPItemTracer *tracer();

private:
    QString label;
    double value; // ?
    QColor color;
    bool visible;
    //ValueScaler valueScaler;
    //QCustomPlot *plot;
    QCPGraph *graph;
    QCPItemTracer *_tracer;

signals:

public slots:
};

#endif // GRAPHWITHVALUE_H
