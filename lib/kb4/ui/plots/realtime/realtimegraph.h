#ifndef REALTIMEGRAPH_H
#define REALTIMEGRAPH_H

#include <lib/qcustomplot/qcustomplot.h>

#include <lib/kb4/ui/plots/base/abstractgraph.h>

class RealTimeGraph: public AbstractGraph
{
public:
    RealTimeGraph(const QString &_label, const QString &postfix, QColor color,
                  QCustomPlot *qcp, QCPAxis *yAxis, int precision = 3,
                  bool scientificNotation = false);
    virtual ~RealTimeGraph();

    //TODO ?rename to qcpGraph
    QCPGraph *graph();

    //void addData(double valueCursor);
    void addData(double key, double valueCursor);

    double valueCursor();
    double valueLast();

    void updateValue();
    void moveCursor(double key);
    void moveCursor2(double key);
    void setCursor2Visible(bool newValue);


private:
    double _valueCursor;
    //ValueScaler valueScaler;
    QCPAxis *_yAxis;

    QCPGraph *_graph;

    void configureCursor(QCPItemTracer **cursor);
    QCPItemTracer *_cursor, *_cursor2;

    // AbstractGraph interface
protected:
    void abstractSetVisible(bool newValue) override;
    void abstractSetColor(QColor newValue) override;
};

#endif // REALTIMEGRAPH_H