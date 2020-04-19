#ifndef RADARTEMPERATURE4GRAPH_H
#define RADARTEMPERATURE4GRAPH_H

#include "radargraph.h"
#include <lib/kb4/log/channeldouble.h>

class RadarTemperature4Graph : public RadarGraph
{
public:
    RadarTemperature4Graph(const QString &label, QColor color, QCustomPlot *qcp,
                           ChannelDouble *up, ChannelDouble *right,
                           ChannelDouble *down, ChannelDouble *left,
                           int precision = 3, bool scientificNotation = false,
                           int lineWidth = 1);

    ChannelDouble *up, *right, *down, *left;

    void calcDeviation();

    double offset() const;
    void setOffset(double offset);

private:
    double _offset=0;

};

#endif // RADARTEMPERATURE4GRAPH_H
