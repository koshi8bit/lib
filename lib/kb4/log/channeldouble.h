#ifndef CHANNELDOUBLE_H
#define CHANNELDOUBLE_H

#include "channelt.h"

#include <lib/kb4/ui/rtplotwithlegend/axis2/rtplotwithlegend.h>
#include <lib/kb4/ui/rtplotwithlegend/graph.h>

class ChannelDouble : public ChannelT<double>
{
public:
    ChannelDouble(QString name, QString postfix, QStringList *prefix, QObject *parent = nullptr);
    void setGraph(Graph *graph);
    bool isScientificNotation();
    void setScientificNotation(bool newValue);

    void setRawValue(double newValue);
    //std::function<void()> heavyWork;
    void setToScaledFunc(double(*f)(double));

    void setToRawFunc(double(*f)(double));
    double rawValue();
private:
    Graph *graph;
    bool _scientificNotation = false;
    double (*toScaledFunc)(double) = nullptr;

    double _rawValue;
    double (*toRawFunc)(double) = nullptr;

signals:
    //TODO: template fuck
    //void valueChangedDouble(double newValue);

protected:
    void valueChangedChild() override;
    void _valueChanged();
private slots:
    void addDataToGraph();
};

#endif // CHANNELDOUBLE_H
