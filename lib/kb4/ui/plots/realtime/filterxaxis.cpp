#include "filterxaxis.h"

FilterXAxis::FilterXAxis(QObject *parent) : QObject(parent)
{

}

bool FilterXAxis::eventFilter(QObject *watched, QEvent *event)
{
    qDebug() << "eventFilter" << event;

    if (event->type() != QEvent::HoverEnter)
        return QObject::eventFilter(watched, event);

    qDebug() << "HoverEnter";

    auto axis = dynamic_cast<QCPAxis*>(watched);
    qDebug() << axis;

    if (axis)
        qDebug() << axis->label();

    return QObject::eventFilter(watched, event);
}

