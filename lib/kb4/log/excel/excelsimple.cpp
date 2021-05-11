#include "excelsimple.h"

ExcelSimple::ExcelSimple(QString filename, QObject *parent, bool pushOnCommit)
    : QObject(parent)
{
    this->filename = filename;
    this->_pushOnCommit = pushOnCommit;
}

void ExcelSimple::commit(QStringList list)
{
    auto line = list.join(Excel::elementDelimeter);

    commit(line);
}

void ExcelSimple::commit(QList<double> list)
{
    QStringList l;

    foreach (auto element, list)
    {
        l.append(EasyLiving::formatDouble(element, 3, true, false));
    }

    commit(l);
}

void ExcelSimple::commit(QList<QString> list)
{
    QStringList l(list);
    commit(l);
}

void ExcelSimple::commit(QString line)
{
    line = line.append(Excel::lineDelimeter);
    if (pushOnCommit())
    {
        EasyLiving::writeFile(filename, line, true);
    }
    else
    {
        buffer.append(line);
    }
}

bool ExcelSimple::push()
{
    auto writeOk = EasyLiving::writeFile(filename, buffer, true);
    if (writeOk)
        buffer.clear();
    else
        qCritical() << EL_FORMAT_ERR("Ошибка сохранения");

    return writeOk;
}

bool ExcelSimple::pushOnCommit() const
{
    return _pushOnCommit;
}

void ExcelSimple::setPushOnCommit(bool pushOnCommit)
{
    _pushOnCommit = pushOnCommit;
}
