#ifndef COLORSETTER_H
#define COLORSETTER_H

#include <QObject>
#include <QStack>
#include <QQueue>
#include <QColor>
#include <QtDebug>

#include <lib/kb4/easyliving.h>

class ColorSetter : public QObject
{
    Q_OBJECT
public:
    explicit ColorSetter(QObject *parent = nullptr);

    QColor getColor();

private:
    QQueue<QColor> *colors;


signals:

public slots:
};

#endif // COLORSETTER_H
