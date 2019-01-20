#ifndef GRAPHLEGENDITEM_H
#define GRAPHLEGENDITEM_H

#include <QWidget>
#include <QColorDialog>

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

private slots:
    void on_checkBoxVisible_stateChanged(int arg1);

    void on_pushButtonColor_clicked();

signals:
    void visibleChanged(bool newValue);
    void colorChanged(QColor newColor);

private:
    Ui::GraphLegendItem *ui;
    QString label;
    QColor color;
    void changeColor();
};

#endif // GRAPHLEGENDITEM_H
