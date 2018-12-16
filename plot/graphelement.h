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
    QCPGraph *graph();
    void addData(double key, double value);

private:
    QString label;
    double value; // ?
    QColor color;
    bool visible;
    //ValueScaler valueScaler;
    //QCustomPlot *plot;
    QCPGraph *_graph;
    QCPItemTracer *_tracer;

signals:

public slots:
};

#endif // GRAPHWITHVALUE_H
