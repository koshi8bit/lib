#include "graph.h"


Graph::Graph(const QString &label, const QString &postfix, QColor color, QCustomPlot *plot, QCPAxis *yAxis, int precision, bool scientificNotation)
    : QObject(plot)
{
    _plot = plot;
    _yAxis = yAxis;

    _visible = true;


    _graph = plot->addGraph(plot->xAxis, yAxis);
    _graph->setName(label);
    _graph->setPen(color);
    _graph->setLineStyle(QCPGraph::LineStyle::lsStepLeft);


    _tracer = new QCPItemTracer(plot);
    _tracer->setGraph(_graph);
    _tracer->setInterpolating(true);
    _tracer->setStyle(QCPItemTracer::tsCircle);
    _tracer->setPen(_graph->pen());
    _tracer->setBrush(color);
    _tracer->setSize(5);

    _precision = precision;
    _scientificNotation = scientificNotation;

    _graphLegendItem = new GraphLegendItem(label, postfix, color, _precision, scientificNotation);
    connect(_graphLegendItem, &GraphLegendItem::visibleChanged, this, &Graph::setVisibleByWidget);
    connect(_graphLegendItem, &GraphLegendItem::colorChanged, this, &Graph::setColorByWidget);

}

Graph::~Graph()
{
    //FIXME exception
    //_graph->deleteLater();
    //_tracer->deleteLater();

    //_graphLegendItem->deleteLater();
}

QCPItemTracer *Graph::tracer()
{
    return _tracer;
}

QCPGraph *Graph::graph()
{
    return _graph;
}

GraphLegendItem *Graph::legendItem()
{
    return graphLegendItem();
}

GraphLegendItem *Graph::graphLegendItem()
{
    return _graphLegendItem;
}

void Graph::addData(double key, double value)
{
    _graph->addData(key, value);
}

double Graph::value()
{
    return _value;
}

bool Graph::visible()
{
    return _visible;
}

void Graph::setGraphKey(double key)
{
    if (visible())
    {
        _tracer->setGraphKey(key);
        _value = _tracer->position->value();
        _graphLegendItem->setValue(_value);
    }
}

void Graph::setVisible(bool newValue)
{
    //TODO autoscale without unsivible graphs
    _graph->setVisible(newValue);
    _tracer->setVisible(newValue);
    _graphLegendItem->setVisibleValue(newValue);
    _visible = newValue;
}


void Graph::setVisibleByWidget(bool newValue)
{
    _graph->setVisible(newValue);
    _tracer->setVisible(newValue);
    _visible = newValue;
    emit visibleChanged(newValue);
}


void Graph::setColor(QColor newValue)
{
    _color = newValue;
    _graph->setPen(newValue);

    _tracer->setPen(_graph->pen());
    _tracer->setBrush(newValue);

    _graphLegendItem->setColor(newValue);
}

void Graph::setColorByWidget(QColor newValue)
{
    _graph->setPen(newValue);
    _tracer->setPen(_graph->pen());
    _tracer->setBrush(newValue);
    emit colorChanged(newValue);
}
