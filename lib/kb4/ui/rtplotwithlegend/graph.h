#ifndef GRAPH_H
#define GRAPH_H

#include <QColor>

#include <lib/qcustomplot/qcustomplot.h>

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
    double _value;
    //ValueScaler valueScaler;
    QCustomPlot *_plot;
    QCPAxis *_yAxis;

    QCPGraph *_graph;
    QCPItemTracer *_tracer;
    GraphLegendItem *_graphLegendItem;

    QCPItemTracer *tracer();

    void setColor(QColor newColor, bool emitSignal);

signals:
    void visibleChanged(bool newValue);
    void colorChanged(QColor newValue);

public slots:
    void setVisible(bool newValue);
    void setColor(QColor newValue);

private slots:
    void setVisibleByWidget(bool newValue);
    void setColorByWidget(QColor newValue);

};

#endif // GRAPH_H
