#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>

#include <lib/kb4/macro.h>

class ErrorHandler : public QObject
{
    Q_OBJECT
public:
    explicit ErrorHandler(QObject *parent = nullptr);

private:
//    QFile *file;
//    QTextStream *stream;


signals:

public slots:
    void errorOccurred(QString message);
};

#endif // ERRORHANDLER_H
