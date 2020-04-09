#include "abstractgraph.h"

AbstractGraph::AbstractGraph(const QString &label, const QString &postfix, QColor color, int precision, bool scientificNotation, QObject *parent)
    :QObject(parent)
{
    _visible = true;

    _color = color;

    _precision = precision;
    _scientificNotation = scientificNotation;

    _graphLegendItem = new GraphLegendItem(label, postfix, color, _precision, scientificNotation);
    connect(_graphLegendItem, &GraphLegendItem::visibleChanged, this, &AbstractGraph::setVisibleByWidget);
    connect(_graphLegendItem, &GraphLegendItem::colorChanged, this, &AbstractGraph::setColorByWidget);

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
    if (_graphLegendItem)
        _graphLegendItem->setVisibleValue(newValue);
}

void AbstractGraph::setColor(QColor newValue)
{
    _setColor(newValue);

    if (_graphLegendItem)
        _graphLegendItem->setColor(newValue);
}

void AbstractGraph::_setVisible(bool newValue)
{
    _visible = newValue;
}

void AbstractGraph::_setColor(QColor newValue)
{
    _color = newValue;
}
