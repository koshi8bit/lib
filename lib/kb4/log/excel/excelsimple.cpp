#include "excelsimple.h"

ExcelSimple::ExcelSimple(QString filename, QObject *parent)
    : QObject(parent)
{
    this->filename = filename;
}

void ExcelSimple::addLine(QStringList list)
{
    auto line = list.join(Excel::elementDelimeter);

    addLine(line);
}

void ExcelSimple::addLine(QList<double> list)
{
    QStringList l;

    foreach (auto element, list)
    {
        l.append(EasyLiving::formatDouble(element, 3, true, EasyLiving::Comma, false));
    }

    addLine(l);
}

void ExcelSimple::addLine(QString line)
{
    line = line.append(Excel::lineDelimeter);
    EasyLiving::writeFile(filename, line, true);
}
