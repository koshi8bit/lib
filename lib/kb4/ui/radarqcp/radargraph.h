#ifndef RADARGRAPH_H
#define RADARGRAPH_H

#include <lib/kb4/ui/radarqcp/abstractgraph.h>
#include <lib/kb4/ui/radarqcp/radarqcp.h>

class RadarGraph : public AbstractGraph
{
public:
    RadarGraph(const QString &label, const QString &postfix, QColor color, RadarQcp *plot,
               int precision = 3, bool scientificNotation = false);

public slots:
    void setValue(double newValue);

private:
    RadarQcp *plot;
};

#endif // RADARGRAPH_H
