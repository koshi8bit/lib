#include "excelsimple.h"

ExcelSimple::ExcelSimple(QString filename, QObject *parent)
    : QObject(parent)
{
    this->filename = filename;
}

void ExcelSimple::addLine(QStringList list)
{
    auto line = list.join(Excel::elementDelimeter)
            .append(Excel::lineDelimeter);

    addLine(line);
}

void ExcelSimple::addLine(QList<double> list)
{
    QStringList l;

    foreach (auto element, list)
    {
        l.append(EasyLiving::formatDouble(element));
    }

    addLine(l);
}

void ExcelSimple::addLine(QString line)
{
    EasyLiving::writeFile(filename, line, true);
}
