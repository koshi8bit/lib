#ifndef ABSTRACTGRAPH_H
#define ABSTRACTGRAPH_H

#include <QObject>
#include <QColor>
#include <lib/qcustomplot/qcustomplot.h>

#include "graphlegenditem.h"

class AbstractGraph : public QObject
{
    Q_OBJECT
public:
    explicit AbstractGraph(const QString &label, const QString &postfix, QColor color,
                           QCustomPlot *qcp = nullptr, int precision = 3,
                           bool scientificNotation = false);
    GraphLegendItem *legendItem();

    bool visible() const;

    QCustomPlot *qcp();

signals:
    void visibleChanged(bool newValue);
    void colorChanged(QColor newValue);

private slots:
    void setVisibleByWidget(bool newValue);
    void setColorByWidget(QColor newValue);

public slots:
    void setVisible(bool newValue);
    void setColor(QColor newValue);

private:
    QString label;
    QString _postfix;
    QColor _color;
    double _valueCursor;
    bool _visible;
    bool _scientificNotation;
    int _precision;
    QCustomPlot *_qcp;

    void _setVisible(bool newValue);
    void _setColor(QColor newValue);

protected:
    GraphLegendItem *_legendItem;

    virtual void abstractSetVisible(bool newValue) = 0;
    virtual void abstractSetColor(QColor newValue) = 0;

};


#endif // ABSTRACTGRAPH_H
