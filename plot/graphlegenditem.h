#ifndef GRAPHLEGENDITEM_H
#define GRAPHLEGENDITEM_H

#include <QWidget>

namespace Ui {
class GraphLegendItem;
}

class GraphLegendItem : public QWidget
{
    Q_OBJECT

public:
    explicit GraphLegendItem(const QString &label, QColor color, QWidget *parent = nullptr);
    ~GraphLegendItem();

    void setValue(double value);
    void setValue(const QString &value);

private:
    Ui::GraphLegendItem *ui;
    QString label;
};

#endif // GRAPHLEGENDITEM_H
