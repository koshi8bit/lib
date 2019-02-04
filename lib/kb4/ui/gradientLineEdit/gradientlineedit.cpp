#include "gradientlineedit.h"

GradientLineEdit::GradientLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    _range = new QCPRange(0, 0);

    _gradient = new QCPColorGradient();
    _gradient->clearColorStops();
    _gradient->setColorStopAt(0, QColor("#0000ff"));
    _gradient->setColorStopAt(0.9, QColor("#ff6600"));
    _gradient->setColorStopAt(1, QColor("#ff0000"));

    setAlignment(Qt::AlignCenter);
    display(0);
}

void GradientLineEdit::setMinMax(double min, double max)
{
    _range->lower = min;
    _range->upper = max;
}

void GradientLineEdit::setRange(QCPRange *range, bool deleteOld)
{
    if (deleteOld)
        delete _range;

    _range = range;
}

void GradientLineEdit::setColorGradient(QCPColorGradient *gradient, bool deleteOld)
{
    if (deleteOld)
        delete _gradient;

    _gradient = gradient;
}

void GradientLineEdit::display(double value)
{
    auto css = QString("background: %1; color: #FFFFFF").arg(QColor(_gradient->color(value, *_range)).name());
    auto text = QString("%1").arg(value, 0, 'f', 2, '0');
    setText(text);
    setStyleSheet(css);
}




