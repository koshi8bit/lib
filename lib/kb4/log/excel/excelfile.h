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
    explicit ExcelFile(QDateTime dt, QString datePattern, QString folder, QObject *parent = nullptr);
    ~ExcelFile();

    void append(QString message);
    bool openFile();
    bool push();
    bool isCreated();
    QString fileName;

private:
    QFile *file;
    QTextStream *stream;
    QString buffer;
    bool _isCreated;

signals:
    void errorOcurred(QString message);

public slots:
};

#endif // EXCELFILE_H
