#ifndef ERRORYGRAPH_H
#define ERRORYGRAPH_H

#include "simplegraph.h"

class ErrorYGraph : public SimpleGraph
{
public:
    ErrorYGraph(const QString &label, const QString &postfix, QColor color,
                 QCustomPlot *qcp, QCPAxis *yAxis, int precision = 3,
                 bool scientificNotation = false);
    void addData(double x, double y, double errorBottom, double errorTop);


private:


    // AbstractGraph interface
protected:
    QCPErrorBars *_errorBarsY;

    void updateLegendItem() override;
    void abstractSetVisible() override;
    void abstractSetColor() override;
};

#endif // ERRORYGRAPH_H
