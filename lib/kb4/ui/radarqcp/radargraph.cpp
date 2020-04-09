#include "radargraph.h"

RadarGraph::RadarGraph(const QString &label, const QString &postfix, QColor color,
                       RadarQcp *plot, int precision, bool scientificNotation)
    :AbstractGraph(label, postfix, color, precision, scientificNotation, plot)
{
    this->plot = plot;
}

void RadarGraph::setValue(double newValue)
{
    _graphLegendItem->setValue(newValue);
}
