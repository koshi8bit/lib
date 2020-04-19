#include "realtimegraph.h"

RealTimeGraph::RealTimeGraph(const QString &label, const QString &postfix,
                             QColor color, QCustomPlot *qcp, int precision,
                             bool scientificNotation)
    :AbstractGraph(label, postfix, color, qcp, precision, scientificNotation)
{

}
