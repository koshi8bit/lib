#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QColor>
#include <QDebug>

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(QString name, QString postfix, QObject *parent = nullptr);
    explicit Channel(QString name, QString postfix, QStringList &path, QObject *parent = nullptr);

    //QColor color;

    QString plotName() const;
    void setPlotName(const QString plotName);
    QString widgetName() const;
    void setWidgetName(const QString widgetName);
    QString logName() const;
    QString postfix() const;

    const QString seporator = "/";

private:
    explicit Channel(QString plotName, QString widgetName, QString postfix, QObject *parent = nullptr);

    QString _plotName;
    QString _widgetName;
    QString _logName;
    QString _postfix;

protected:
    void setLogName(const QString logName);

    void _errorOccurred(QString message);


signals:
    void valueChanged();
    void errorOccurred(QString message);

public slots:
};

#endif // CHANNEL_H
