#ifndef RADARQCP_H
#define RADARQCP_H

#include <QWidget>

namespace Ui {
class RadarQcp;
}

class RadarQcp : public QWidget
{
    Q_OBJECT

public:
    explicit RadarQcp(QWidget *parent = nullptr);
    ~RadarQcp();

private:
    Ui::RadarQcp *ui;
};

#endif // RADARQCP_H
