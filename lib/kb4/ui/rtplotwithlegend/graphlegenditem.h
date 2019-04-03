#ifndef GRAPHLEGENDITEM_H
#define GRAPHLEGENDITEM_H

#include <QWidget>
#include <QColorDialog>

//FIXME
#include <lib/kb4/easyliving.h>


namespace Ui {
class GraphLegendItem;
}

class GraphLegendItem : public QWidget
{
    Q_OBJECT

public:
    explicit GraphLegendItem(const QString &label, const QString &postfix, QColor color, QWidget *parent = nullptr);
    ~GraphLegendItem();

    void setValue(double value);
    void setValue(const QString &value);

public slots:
    void setVisibleValue(bool newValue);
    void setColor(QColor &color);

private slots:
    void on_checkBoxVisible_stateChanged(int arg1);

    void on_pushButtonColor_clicked();

signals:
    void visibleChanged(bool newValue);
    void colorChanged(QColor newColor);

private:
    Ui::GraphLegendItem *ui;
    QString label;
    QString postfix;
    QColor color;

};

#endif // GRAPHLEGENDITEM_H
