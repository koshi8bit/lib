#include "abstractgraph.h"

AbstractGraph::AbstractGraph(const QString &label, const QString &postfix, QColor color,
                             QCustomPlot *qcp, int precision, bool scientificNotation)
    :QObject(qcp)
{
    _visible = true;

    _qcp = qcp;

    _color = color;

    _precision = precision;
    _scientificNotation = scientificNotation;

    _legendItem = new GraphLegendItem(label, postfix, color, _precision, scientificNotation);
    connect(_legendItem, &GraphLegendItem::visibleChanged, this, &AbstractGraph::setVisibleByWidget);
    connect(_legendItem, &GraphLegendItem::colorChanged, this, &AbstractGraph::setColorByWidget);

}

GraphLegendItem *AbstractGraph::legendItem()
{
    return _legendItem;
}

void AbstractGraph::setVisibleByWidget(bool newValue)
{
    _setVisible(newValue);
    emit visibleChanged(newValue);
}

void AbstractGraph::setColorByWidget(QColor newValue)
{
    _setColor(newValue);
    emit colorChanged(newValue);
}

void AbstractGraph::setVisible(bool newValue)
{
    //TODO autoscale without unsivible graphs
    _setVisible(newValue);
    if (_legendItem)
        _legendItem->setVisibleValue(newValue);
}

void AbstractGraph::setColor(QColor newValue)
{
    _setColor(newValue);

    if (_legendItem)
        _legendItem->setColor(newValue);
}

void AbstractGraph::_setVisible(bool newValue)
{
    _visible = newValue;
    abstractSetVisible(newValue);
    _qcp->replot();
}

void AbstractGraph::_setColor(QColor newValue)
{
    _color = newValue;
    abstractSetColor(newValue);
    _qcp->replot();
}
