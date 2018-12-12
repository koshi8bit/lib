#include "colorsetter.h"

ColorSetter::ColorSetter(QObject *parent) : QObject(parent)
{
    colors = new QQueue<QColor>();
    colors->enqueue(QColor("#FFFFFF"));
    colors->enqueue(QColor("#FF4242"));
    colors->enqueue(QColor("#0EFF00"));
    colors->enqueue(QColor("#42C2FF"));
    colors->enqueue(QColor("#D2FF71"));
    colors->enqueue(QColor("#CD59FF"));
    colors->enqueue(QColor("#FFB312"));
    colors->enqueue(QColor("#4245FF"));
    colors->enqueue(QColor("#FF42B6"));
    colors->enqueue(QColor("#59FFF4"));
}

QColor ColorSetter::getColor()
{
    if (!colors->isEmpty())
        return colors->dequeue();
    else
        return QColor("#FFFFFF");
}


