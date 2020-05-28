#include "faultswidget.h"

FaultsWidget::FaultsWidget(QScrollArea *widget) : QWidget(widget)
{
    if (widget != nullptr)
        layoutFaults = new QVBoxLayout(widget->widget());
    else
        layoutFaults = new QVBoxLayout();

    auto spacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layoutFaults->addItem(spacer);

    _template = EasyLiving::readFile(":/faults/ui/faults/template.html");
}

void FaultsWidget::addFault(Fault *fault)
{
    layoutFaults->insertWidget(layoutFaults->count()-1, fault->widget());
    _faults.append(fault);

    connect(fault, &Fault::visibleChanged, [this](bool visible) {
        if (visible)
        {
            triggerFault(true);
        }
        else
        {
            foreach(auto elemnt, _faults)
            {
                if (elemnt->isVisible())
                {
                    triggerFault(true);
                    return;
                }
            }
            triggerFault(false);
        }
    });
}

void FaultsWidget::configureBorder(QLabel *tl, QLabel *t, QLabel *tr, QLabel *l, QLabel *r, QLabel *bl, QLabel *b, QLabel *br)
{
    border.append(tl);
    border.append(t);
    border.append(tr);
    border.append(l);
    border.append(r);
    border.append(bl);
    border.append(b);
    border.append(br);

    borderMessage.append(t);
    borderMessage.append(b);

    foreach(auto lbl, border)
    {
        lbl->setText("  ");
        lbl->setStyleSheet("background-color: red; color: yellow;");
    }

    foreach(auto lbl, borderMessage)
    {
        lbl->setText(QObject::tr("Обнаружены неисправности!"));
    }

    showFaultBorder(false);
}

void FaultsWidget::showFaultBorder(bool fault, QStringList faults)
{
    QString tmp;

    if (fault)
    {
        tmp = _template.arg(faults.join("<br/>"));
    }

    foreach(auto lbl, border)
    {
        lbl->setVisible(fault);

        if (fault)
        {
            lbl->setToolTip(tmp);
        }
    }
}

QStringList FaultsWidget::faults()
{
    QStringList result;
    foreach(auto elemnt, _faults)
    {
        if (elemnt->isVisible())
        {
            result.append(elemnt->message());
        }
    }
    return result;
}

bool FaultsWidget::isFaultTriggered() const
{
    return _isFaultTriggered;
}

void FaultsWidget::triggerFault(bool triggered)
{
    _isFaultTriggered = triggered;
    showFaultBorder(triggered, faults());
    emit faultTriggered(triggered);
}
