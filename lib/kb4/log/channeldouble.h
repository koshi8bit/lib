#ifndef CHANNELDOUBLE_H
#define CHANNELDOUBLE_H

#include "channelt.h"

#include <lib/kb4/ui/realtimeqcp/realtimeqcp.h>
#include <lib/kb4/ui/realtimeqcp/graph.h>
#include <lib/kb4/ui/plots/base/abstractplot.h>
#include <lib/kb4/ui/plots/base/abstractgraph.h>

class ChannelDouble : public ChannelT<double>
{
    Q_OBJECT
public:
    ChannelDouble(QString name, QString postfix, QObject *parent = nullptr);
    ChannelDouble(QString name, QString postfix, QStringList &path, QObject *parent = nullptr);
    ChannelDouble(QString sharedVariableName, QObject *parent = nullptr);




//    ChannelDouble(QString sharedVariableName, QString postfix, bool connectWrite=false, QObject *parent = nullptr);

//    ChannelDouble(QString name, QString postfix, QStringList &prefix, QObject *parent = nullptr);
//    ChannelDouble(QString name, QString postfix, QStringList *prefix, QObject *parent = nullptr);
//  TODO DELETE LATER
    void addGraphToPlot(RealTimeQCP *plot, bool visible=true);
    //AbstractGraph *addGraphToPlot(AbstractPlot *plot, bool visible=true);

    bool scientificNotation();
    void setScientificNotation(bool newValue);

    int precision() const;
    void setPrecision(int precision);

    void setToScaledFunc(std::function<double(double)> f);
    void setRawValue(double newValue);

    void setToRawFunc(std::function<double(double)> f);
    double rawValue();

    Graph *graph() const;

private:
    Graph *_graph = nullptr;
    AbstractGraph *_abstractGraph = nullptr;

    int _precision;
    bool _scientificNotation = false;

    //double (*toScaledFunc)(double) = nullptr;
    std::function<double(double)> toScaledFunc = nullptr;

    double _rawValue;
    //double (*toRawFunc)(double) = nullptr;
    std::function<double(double)> toRawFunc = nullptr;

    void configure();
signals:
    //TODO: template fuck
    //void valueChangedDouble(double newValue);

protected:
    void valueChangedChild() override;
    void _valueChanged();
private slots:
};

#endif // CHANNELDOUBLE_H
