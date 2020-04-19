#include "realtimegraph.h"

RealTimeGraph::RealTimeGraph(const QString &label, const QString &postfix,
                             QColor color, QCustomPlot *qcp, QCPAxis *yAxis, int precision,
                             bool scientificNotation)
    :AbstractGraph(label, postfix, color, qcp, precision, scientificNotation)
{
    _yAxis = yAxis;
    _graph = qcp->addGraph(qcp->xAxis, yAxis);
    _graph->setName(label);
    ///
    QPen pen;
    pen.setColor(color);
    pen.setWidth(1);
    _graph->setPen(pen);

    ///
    _graph->setLineStyle(QCPGraph::LineStyle::lsStepLeft);
    _graph->setAdaptiveSampling(true);


    configureCursor(&_cursor);
    configureCursor(&_cursor2);
    _cursor2->setVisible(false);
}

RealTimeGraph::~RealTimeGraph()
{
    //FIXME exception
//    _graph->deleteLater();
//    legendItem()->deleteLater();
//    _cursor->deleteLater();
//    _cursor2->deleteLater();
}


QCPGraph *RealTimeGraph::graph()
{
    return _graph;
}

//void Graph::addData(double valueCursor)
//{
//    addData(RealTimeQCP:)
//}

void RealTimeGraph::addData(double key, double value)
{
    if (_graph)
        _graph->addData(key, value);
}

double RealTimeGraph::valueCursor()
{
    return _valueCursor;
}

double RealTimeGraph::valueLast()
{
    qWarning() << EL_FORMAT_ERR("Method is not completed");
    return 0;
    //return _graph->data()->last());
}

void RealTimeGraph::updateValue()
{
    if (visible())
    {
        if (legendItem())
        {
            if (_cursor2->visible())
            {
                auto deltaValue = _cursor->position->value() - _cursor2->position->value();
                    legendItem()->setValue(deltaValue, true);
            }
            else
            {
                legendItem()->setValue(_valueCursor);
            }
        }
        _valueCursor = _cursor->position->value();
    }
}

void RealTimeGraph::moveCursor(double key)
{
    _cursor->setGraphKey(key);
    if (visible())
    {
        updateValue();
    }
}

void RealTimeGraph::moveCursor2(double key)
{
    if (visible())
    {
        _cursor2->setGraphKey(key);
    }
}

void RealTimeGraph::configureCursor(QCPItemTracer **cursor)
{
    (*cursor) = new QCPItemTracer(qcp());
    (*cursor)->setGraph(_graph);
    //(*cursor)->setInterpolating(true);
    (*cursor)->setStyle(QCPItemTracer::tsCircle); // tsCircle
    (*cursor)->setPen(_graph->pen());
    (*cursor)->setBrush(color());
    (*cursor)->setSize(5);
}

void RealTimeGraph::setCursor2Visible(bool newValue)
{
    if (visible()) {
        _cursor2->setVisible(newValue);
    }
}

void RealTimeGraph::abstractSetVisible(bool newValue)
{
    _graph->setVisible(newValue);
    _cursor->setVisible(newValue);
    if (!newValue)
        _cursor2->setVisible(false);
}

void RealTimeGraph::abstractSetColor(QColor newValue)
{
    _graph->setPen(newValue);
    _cursor->setPen(_graph->pen());
    _cursor->setBrush(newValue);

    _cursor2->setPen(_graph->pen());
    _cursor2->setBrush(newValue);
}
