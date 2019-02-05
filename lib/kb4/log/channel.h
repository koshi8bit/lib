#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QColor>

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(QString plotText, QStringList logName, QObject *parent = nullptr);

    QString plotText();
    QString uiText();
    QStringList logName();

    //QColor color;


//    static QString toExcel(QStringList *list);
//    static QString toSQL(QStringList *list);

private:
    QString _plotText;
    QString _uiText;
    QStringList _logName;


signals:
    void valueChanged();

public slots:
};

#endif // CHANNEL_H
