/*
 * File name: mavvehiclemanager.h
 * Purpose: Simulate multiple vehicles to connect to QGC via MAVLink over UDP socket.
 * Creating Date: 2019.12.05
 * Author/Charge: Panda Wang (lucky00122@gmail.com)
 * Note: N/A
 */
#ifndef MAVVEHICLEMANAGER_H
#define MAVVEHICLEMANAGER_H

#include <QMainWindow>
#include <QLineEdit>
#include <QIntValidator>

#include "mavlink_udp.h"

#define MAVLINK_SYS_ID_MIN  1
#define MAVLINK_SYS_ID_MAX  254

namespace Ui {
class MavVehicleManager;
}

class MavVehicleManager : public QMainWindow//, public QIntValidator
{
    Q_OBJECT

public:
    explicit MavVehicleManager(QWidget *parent = nullptr);
    ~MavVehicleManager();

    // Virtual function of QIntValidator
    //QValidateor::State validate(QString &input, int &pos) const override;

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_RandomSysID_clicked();

    void on_Launch_clicked();

    void on_Stop_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_lineEdit_8_textChanged(const QString &arg1);

    void on_lineEdit_9_textChanged(const QString &arg1);

    void on_lineEdit_10_textChanged(const QString &arg1);

private:
    void _SetInputEnable(bool bEnable);

    Ui::MavVehicleManager *ui;

    QList<QLineEdit *>  _sysIds; // QLineEdit List for system IDs

    QIntValidator *_lineEditRange;

    QList<mavlink_udp *> _mavlink;
};

#endif // MAVVEHICLEMANAGER_H
