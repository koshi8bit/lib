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

    hideFaultBorder();
}

void FaultsWidget::showFaultBorder(QString str)
{
    auto tooltip = _template.arg(str);

    foreach(auto lbl, border)
    {
        lbl->setVisible(true);
        lbl->setToolTip(tooltip);
    }
}

void FaultsWidget::showFaultBorder(QStringList faults)
{
    showFaultBorder(faults.join(joiner));
}

void FaultsWidget::hideFaultBorder()
{
    foreach(auto lbl, border)
    {
        lbl->setVisible(false);
    }
}

void FaultsWidget::configureSharedVariable(bool enableWriteFromNet)
{
    sharedVariable = new ChannelQString("faults", "", this);
    sharedVariable->configureSharedVariable(enableWriteFromNet);
    connect(sharedVariable, &Channel::valueChanged, [this]() {
        auto str = sharedVariable->value();
        if(str.isEmpty())
        {
            hideFaultBorder();
        }
        else
        {
            showFaultBorder(str);
        }
    });
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

void FaultsWidget::triggerFault(bool triggered, bool updateSharedVariable)
{
    _isFaultTriggered = triggered;
    if (triggered)
    {
        showFaultBorder(faults());

        if (sharedVariable || updateSharedVariable)
            sharedVariable->setValue(faults().join(joiner));
    }
    else
    {
        hideFaultBorder();

        if (sharedVariable || updateSharedVariable)
            sharedVariable->setValue("");
    }

    emit faultTriggered(triggered);
}
