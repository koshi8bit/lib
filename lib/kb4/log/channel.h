#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QColor>
#include <QDebug>

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(QString name, QString postfix, QStringList *path, QObject *parent = nullptr);

    //QColor color;

    QString plotName() const;
    QString widgetName() const;
    QString logName() const;
    QString postfix() const;

    void setPlotName(const QString &plotName);
    void setWidgetName(const QString &widgetName);

private:
    QString _plotName;
    QString _widgetName;
    QString _logName;
    QString _postfix;

protected:
    void _errorOccurred(QString message);


signals:
    void valueChanged();
    void errorOccurred(QString message);

public slots:
};

#endif // CHANNEL_H
