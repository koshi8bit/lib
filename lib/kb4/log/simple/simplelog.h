#ifndef SIMPLELOG_H
#define SIMPLELOG_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QString>

#include <lib/kb4/easyliving.h>

//#define sl2(p1) qDebug() << p1; sl << p1;
//#define sl simpleLog->stream << "\n" <<

using namespace std;

class SimpleLog : public QObject
{
    Q_OBJECT
public:
    explicit SimpleLog(QString path, bool append = false, QObject *parent = nullptr);
    ~SimpleLog();
    QTextStream stream;

    void append(QString message);

private:
    QFile *file;
signals:

};

ostream& operator<<(ostream& os, const SimpleLog& sl);


#endif // SIMPLELOG_H
