#ifndef EXCELSIMPLE_H
#define EXCELSIMPLE_H

#include "excel.h"

class ExcelSimple : public QObject
{
public:
    ExcelSimple(QString filename, QObject *parent = nullptr);

    void configure(QString filename);

    void addLine(QStringList list);
    void addLine(QList<double> list);
    void addLine(QString line);

private:
    QString filename;
};

#endif // EXCELSIMPLE_H
