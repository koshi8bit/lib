#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QColor>

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(QString name, QStringList *path, QObject *parent = nullptr);

    //QColor color;

    QString plotName() const;
    QString widgetName() const;
    QString logName() const;

    void setPlotName(const QString &plotName);

private:
    QString _plotName;
    QString _widgetName;
    QString _logName;


signals:
    void valueChanged();

public slots:
};

#endif // CHANNEL_H
