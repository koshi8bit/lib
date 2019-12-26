#include "graph.h"


Graph::Graph(const QString &label, const QString &postfix, QColor color, QCustomPlot *plot, QCPAxis *yAxis, int precision, bool scientificNotation)
    : QObject(plot)
{
    _plot = plot;
    _yAxis = yAxis;

    _visible = true;

    _color = color;


    _graph = plot->addGraph(plot->xAxis, yAxis);
    _graph->setName(label);
    _graph->setPen(color);
    _graph->setLineStyle(QCPGraph::LineStyle::lsStepLeft);


    configureTracer(&_tracer);
    configureTracer(&_tracer2);

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

//void Graph::addData(double valueCursor)
//{
//    addData(RealTimeQCP:)
//}

void Graph::addData(double key, double value)
{
    _graph->addData(key, value);
}

double Graph::valueCursor()
{
    return _valueCursor;
}

double Graph::valueLast()
{
    //TODO tima45
    qWarning() << EL_FORMAT_ERR("Method is not completed");
    return 0;
    //return _graph->data()->last());
}

bool Graph::visible()
{
    return _visible;
}

void Graph::updateValue()
{
    if (_tracer2->visible())
    {
        auto deltaValue = _tracer->position->value() - _tracer2->position->value();
        _graphLegendItem->setValue(deltaValue, true);
    }
    else
    {
        _graphLegendItem->setValue(_valueCursor);
    }
    _valueCursor = _tracer->position->value();
}

void Graph::moveCursor(double key)
{
    if (visible())
    {
        _tracer->setGraphKey(key);
        updateValue();
    }
}

void Graph::moveCursor2(double key)
{
    if (visible())
    {
        _tracer2->setGraphKey(key);
    }
}

void Graph::configureTracer(QCPItemTracer **tracer)
{
    (*tracer) = new QCPItemTracer(_plot);
    (*tracer)->setGraph(_graph);
    (*tracer)->setInterpolating(true);
    (*tracer)->setStyle(QCPItemTracer::tsCircle);
    (*tracer)->setPen(_graph->pen());
    (*tracer)->setBrush(_color);
    (*tracer)->setSize(5);
}

void Graph::setTracer2Visible(bool newValue)
{
    _tracer2->setVisible(newValue);
    qDebug() << _tracer2->visible();
}

void Graph::setVisible(bool newValue)
{
    //TODO autoscale without unsivible graphs
    _setVisible(newValue);
    _graphLegendItem->setVisibleValue(newValue);
}


void Graph::_setVisible(bool newValue)
{
    _graph->setVisible(newValue);
    _tracer->setVisible(newValue);
    _visible = newValue;
}

void Graph::_setColor(QColor newValue)
{
    _color = newValue;
    _graph->setPen(newValue);
    _tracer->setPen(_graph->pen());
    _tracer->setBrush(newValue);
}

void Graph::setVisibleByWidget(bool newValue)
{
    _setVisible(newValue);
    emit visibleChanged(newValue);
}


void Graph::setColor(QColor newValue)
{
    _setColor(newValue);

    _graphLegendItem->setColor(newValue);
}

void Graph::setColorByWidget(QColor newValue)
{
    _setColor(newValue);
    emit colorChanged(newValue);
}

