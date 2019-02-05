#ifndef EXCELFILE_H
#define EXCELFILE_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDateTime>

class ExcelFile : public QObject
{
    Q_OBJECT
public:
    explicit ExcelFile(QDateTime dt, QString folder, QObject *parent = nullptr);
    void append(QString message);
    bool openFile();
    bool push();
    QString fileName;

private:
    QFile *file;
    QTextStream *stream;
    QString buffer;

signals:
    void errorOcurred(QString message);

public slots:
};

#endif // EXCELFILE_H
