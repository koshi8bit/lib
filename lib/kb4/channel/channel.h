#ifndef CHANNEL_H
#define CHANNEL_H

#include <QObject>
#include <QColor>

class Channel : public QObject
{
    Q_OBJECT
public:
    explicit Channel(QString postfix, QObject *parent = nullptr);

    QString postfix() const;

private:
    QString _postfix;


signals:
    void valueChanged();

public slots:
};

#endif // CHANNEL_H
