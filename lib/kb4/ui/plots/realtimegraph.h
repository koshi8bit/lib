#ifndef REALTIMEGRAPH_H
#define REALTIMEGRAPH_H

#include <lib/qcustomplot/qcustomplot.h>

#include <lib/kb4/ui/plots/base/abstractgraph.h>

class RealTimeGraph: public AbstractGraph
{
public:
    RealTimeGraph(const QString &label, const QString &postfix, QColor color,
                  QCustomPlot *qcp, QCPAxis *yAxis, int precision = 3,
                  bool scientificNotation = false);
    virtual ~RealTimeGraph();

    //TODO ?rename to qcpGraph
    QCPGraph *graph();

    GraphLegendItem *legendItem();
    //WARNING delete method graphLegendItem
    GraphLegendItem *graphLegendItem();

    //void addData(double valueCursor);
    void addData(double key, double valueCursor);

    double valueCursor();
    double valueLast();

    bool visible();
    void updateValue();
    void moveCursor(double key);
    void moveCursor2(double key);
    void setCursor2Visible(bool newValue);


private:
    QString label;
    QString _postfix;
    QColor _color;
    double _valueCursor;
    bool _visible;
    bool _scientificNotation;
    int _precision;
    //ValueScaler valueScaler;
    QCPAxis *_yAxis;

    QCPGraph *_graph;

    void configureCursor(QCPItemTracer **cursor);
    QCPItemTracer *_cursor, *_cursor2;
    GraphLegendItem *_graphLegendItem;

    // AbstractGraph interface
protected:
    void abstractSetVisible(bool newValue) override;
    void abstractSetColor(QColor newValue) override;
};

#endif // REALTIMEGRAPH_H
