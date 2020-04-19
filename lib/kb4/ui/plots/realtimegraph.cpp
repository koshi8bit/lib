#include "realtimegraph.h"

RealTimeGraph::RealTimeGraph(const QString &label, const QString &postfix,
                             QColor color, QCustomPlot *qcp, QCPAxis *yAxis, int precision,
                             bool scientificNotation)
    :AbstractGraph(label, postfix, color, qcp, precision, scientificNotation)
{

}

void RealTimeGraph::abstractSetVisible(bool newValue)
{

}

void RealTimeGraph::abstractSetColor(QColor newValue)
{

}
