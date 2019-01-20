#ifndef GRAPHWITHVALUE_H
#define GRAPHWITHVALUE_H

#include <QColor>
#include "qcustomplot.h"
#include "graphlegenditem.h"


class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(const QString &label, QColor color, QCustomPlot *plot, QCPAxis *yAxis, QObject *parent = nullptr);
    virtual ~Graph();

    QCPGraph *graph();
    GraphLegendItem *graphLegendItem();
    void addData(double key, double value);
    double value();
    void setGraphKey(double key);

private:
    QString label;
    QColor color;
    bool visible;
    double _value;
    //ValueScaler valueScaler;
    QCustomPlot *_plot;
    QCPAxis *_yAxis;

    QCPGraph *_graph;
    QCPItemTracer *_tracer;
    GraphLegendItem *_graphLegendItem;

    QCPItemTracer *tracer();

signals:

public slots:

private slots:
    void visibleChanged(bool newValue);
    void colorChanged(QColor newColor);
};

#endif // GRAPHWITHVALUE_H
