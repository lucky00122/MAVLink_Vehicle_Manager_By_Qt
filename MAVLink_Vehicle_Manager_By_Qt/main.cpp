/*
 * File name: main.cpp
 * Purpose: A Control window to lauch multiple virtual vehicles to connect to QGC.
 * Creating Date: 2019.12.05
 * Author/Charge: Panda Wang (lucky00122@gmail.com)
 * Note: N/A
 */
#include "mavvehiclemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MavVehicleManager w;
    w.show();

    return a.exec();
}
