#ifndef GRAPHWITHVALUE_H
#define GRAPHWITHVALUE_H

#include <QColor>
#include "qcustomplot.h"
#include "graphlegenditem.h"


class GraphElement : public QObject
{
    Q_OBJECT
public:
    explicit GraphElement(const QString &label, QColor color, QCustomPlot *plot, QCPAxis *yAxis, QObject *parent = nullptr);
    virtual ~GraphElement();

    QCPGraph *graph();
    GraphLegendItem *graphLegendItem();
    void addData(double key, double value);

    void setGraphKey(double key);

private:
    QString label;
    double value; // ?
    QColor color;
    bool visible;
    //ValueScaler valueScaler;
    //QCustomPlot *plot;
    QCPGraph *_graph;
    QCPItemTracer *_tracer;
    GraphLegendItem *_graphLegendItem;

    QCPItemTracer *tracer();

signals:

public slots:
};

#endif // GRAPHWITHVALUE_H
