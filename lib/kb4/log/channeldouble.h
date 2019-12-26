#ifndef CHANNELDOUBLE_H
#define CHANNELDOUBLE_H

#include "channelt.h"

#include <lib/kb4/ui/realtimeqcp/realtimeqcp.h>
#include <lib/kb4/ui/realtimeqcp/graph.h>

class ChannelDouble : public ChannelT<double>
{
public:
    ChannelDouble(QString name, QString postfix, QObject *parent = nullptr);
    ChannelDouble(QString name, QString postfix, QStringList &path, QObject *parent = nullptr);
    ChannelDouble(QString sharedVariableName, QObject *parent = nullptr);




//    ChannelDouble(QString sharedVariableName, QString postfix, bool connectWrite=false, QObject *parent = nullptr);

//    ChannelDouble(QString name, QString postfix, QStringList &prefix, QObject *parent = nullptr);
//    ChannelDouble(QString name, QString postfix, QStringList *prefix, QObject *parent = nullptr);
    void setGraph(Graph *graph);
    bool isScientificNotation();
    void setScientificNotation(bool newValue);

    void setRawValue(double newValue);
    void setToScaledFunc(std::function<double(double)> f);

    void setToRawFunc(std::function<double(double)> f);
    double rawValue();
private:
    Graph *graph;
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
    void addDataToGraph();
};

#endif // CHANNELDOUBLE_H
