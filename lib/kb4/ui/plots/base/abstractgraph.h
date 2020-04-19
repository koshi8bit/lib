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
    explicit AbstractGraph(const QString &_label, const QString &postfix, QColor color,
                           QCustomPlot *qcp = nullptr, int precision = 3,
                           bool scientificNotation = false);

    QString label() const;
    QString postfix() const;
    QColor color() const;
    bool visible() const;
    bool scientificNotation() const;
    int precision() const;
    QCustomPlot *qcp();

    GraphLegendItem *legendItem();

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
    QString _label;
    QString _postfix;
    QColor _color;
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
