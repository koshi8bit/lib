# lib
Library with most common classes, that are developed during BNCT project

## Getting Started
This lib is tested in Qt 5.14.0 and Qt Creator 4.11.0

* Check examples in *main.c* and *mainwindow.cpp* files to see, how to use lib
* Add *lib* folder to your project
* Add in .pro file this lines
```
QT += core gui printsupport network
INCLUDEPATH += ./
```
* Fin. You are perfect!

## Running the tests
Now tests are not avaliable, but soon they will be implemented

# Most common classes and methods:

## EasyLeaving

* formatDouble
* formatDateTime
* default physical postfixes
* isBetween (double)
* isEqualDouble

## UI

### RealTimeQCP

Realtime plot with
* Full axis config (time and value). for Y axis it is possible to set **Scientific notation and precision**
* Powerful **legend and mouse iterations**
* It is possible to add **cursor** (like in a oscilloscope) and see delta time and values in legend. 
* Legend allow to change graph **color and visibility**.
* It is possible to use **2 seporated Y axies**
This plot is based on QCustomPlot

![RealTimeQCP](readme-pic/realtimeqcp01.png)
![RealTimeQCP](readme-pic/realtimeqcp02.png)
![RealTimeQCP](readme-pic/realtimeqcp03.png)
![RealTimeQCP](readme-pic/realtimeqcp04.png)
![RealTimeQCP](readme-pic/realtimeqcp05.png)

### GradientLineEdit

This is QLineEdit with color representation of double value. *(May be better to inherit from QDoubleSpinBox)*

### Worker

Background worker, that works in sepoporated thread. Good for heavy tasks.

### ErrorHandler

Custom error handler. Not shure this is common for C++


## Author

 **Alexey K** koshi8bit@mail.ru
 
## Acknowledgments

* [Qt developers](https://www.qt.io/)
* [QCustomPlot](https://www.qcustomplot.com/) library developers 
* Work colleagues and Budker Institute of Nuclear Physics
* My wife and dog

## License
If use - please provide link to this repository
```
https://github.com/koshi8bit/lib
```

