#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication>

#include <lib/kb4/macro.h>

class ErrorHandler : public QObject
{
    Q_OBJECT
public:
    explicit ErrorHandler(QObject *parent = nullptr);

private:
    static const QString errorSave;
    static const QString errorSend;
    static const QString okSend;
//    QFile *file;
//    QTextStream *stream;

    void showErrorMessage(QString messageToUser, QString error);


signals:

public slots:
    void errorOccurred(QString error);
};

#endif // ERRORHANDLER_H
