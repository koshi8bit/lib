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
    _graph->setAdaptiveSampling(true);


    configureCursor(&_cursor);
    configureCursor(&_cursor2);
    _cursor2->setVisible(false);

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
    if (visible())
    {
        if (_cursor2->visible())
        {
            auto deltaValue = _cursor->position->value() - _cursor2->position->value();
            _graphLegendItem->setValue(deltaValue, true);
        }
        else
        {
            _graphLegendItem->setValue(_valueCursor);
        }
        _valueCursor = _cursor->position->value();
    }
}

void Graph::moveCursor(double key)
{
    _cursor->setGraphKey(key);
    if (visible())
    {
        updateValue();
    }
}

void Graph::moveCursor2(double key)
{
    if (visible())
    {
        _cursor2->setGraphKey(key);
    }
}

void Graph::configureCursor(QCPItemTracer **cursor)
{
    (*cursor) = new QCPItemTracer(_plot);
    (*cursor)->setGraph(_graph);
    //(*cursor)->setInterpolating(true);
    (*cursor)->setStyle(QCPItemTracer::tsCircle); // tsCircle
    (*cursor)->setPen(_graph->pen());
    (*cursor)->setBrush(_color);
    (*cursor)->setSize(5);
}

void Graph::setCursor2Visible(bool newValue)
{
    if (visible()) {
        _cursor2->setVisible(newValue);
    }
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
    _cursor->setVisible(newValue);
    if (!newValue)
        _cursor2->setVisible(false);
    _visible = newValue;
}

void Graph::_setColor(QColor newValue)
{
    _color = newValue;
    _graph->setPen(newValue);
    _cursor->setPen(_graph->pen());
    _cursor->setBrush(newValue);

    _cursor2->setPen(_graph->pen());
    _cursor2->setBrush(newValue);
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

