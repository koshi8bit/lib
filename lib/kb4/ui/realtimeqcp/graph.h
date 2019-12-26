#ifndef GRAPH_H
#define GRAPH_H

#include <QColor>

#include <lib/qcustomplot/qcustomplot.h>

#include "graphlegenditem.h"


class Graph : public QObject
{
    Q_OBJECT
public:
    explicit Graph(const QString &label, const QString &postfix, QColor color, QCustomPlot *plot, QCPAxis *yAxis, int precision = 3, bool scientificNotation = false);
    virtual ~Graph();

    QCPGraph *graph();

    GraphLegendItem *legendItem();
    //WARNING delete method graphLegendItem
    GraphLegendItem *graphLegendItem();

    //void addData(double valueCursor);
    void addData(double key, double valueCursor);

    double valueCursor();
    double valueLast();

    bool visible();
    void setGraphKey(double key);

private:
    QString label;
    QString _postfix;
    QColor _color;
    double _value;
    bool _visible;
    bool _scientificNotation;
    int _precision;
    //ValueScaler valueScaler;
    QCustomPlot *_plot;
    QCPAxis *_yAxis;

    QCPGraph *_graph;
    QCPItemTracer *_tracer;
    GraphLegendItem *_graphLegendItem;

    QCPItemTracer *tracer();

    void _setVisible(bool newValue);
    void _setColor(QColor newValue);

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
