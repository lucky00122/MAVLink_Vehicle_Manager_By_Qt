/*
 * File name: mavvehiclemanager.cpp
 * Purpose: Simulate multiple vehicles to connect to QGC via MAVLink over UDP socket.
 * Creating Date: 2019.12.05
 * Author/Charge: Panda Wang (lucky00122@gmail.com)
 * Note: N/A
 */
#include <QRandomGenerator>

#include "mavvehiclemanager.h"
#include "ui_mavvehiclemanager.h"

MavVehicleManager::MavVehicleManager(QWidget *parent) : QMainWindow(parent), ui(new Ui::MavVehicleManager)
{
    PRINT_FUNC;

    ui->setupUi(this);

    QStringList cityname;
    cityname<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10";
    ui->comboBox->addItems(cityname);


    // Initial lineEdit List
    _sysIds.append(ui->lineEdit);
    _sysIds.append(ui->lineEdit_2);
    _sysIds.append(ui->lineEdit_3);
    _sysIds.append(ui->lineEdit_4);
    _sysIds.append(ui->lineEdit_5);
    _sysIds.append(ui->lineEdit_6);
    _sysIds.append(ui->lineEdit_7);
    _sysIds.append(ui->lineEdit_8);
    _sysIds.append(ui->lineEdit_9);
    _sysIds.append(ui->lineEdit_10);

	// Set the system ID range
    _lineEditRange = new QIntValidator(MAVLINK_SYS_ID_MIN, MAVLINK_SYS_ID_MAX, this);

    // Use Iterator method of Qlist to set all lineEdits' Validators
    for(QLineEdit* target: _sysIds)
    {
        target->setValidator(_lineEditRange);
    }

    // Initialize all input enable state
    _SetInputEnable(true);
}

MavVehicleManager::~MavVehicleManager()
{
    PRINT_FUNC;

	_sysIds.clear();

    _sysIds.~QList();

    delete _lineEditRange;

    _mavlink.~QList();
	
    delete ui;
}

void MavVehicleManager::on_comboBox_currentIndexChanged(int index)
{
    PRINT_FUNC;

    Q_UNUSED(index)
	
    _SetInputEnable(true);
}

void MavVehicleManager::on_RandomSysID_clicked()
{
    PRINT_FUNC;
	
    quint32 v = 0;

    for(QLineEdit* target: _sysIds)
    {
        if(target->isEnabled())
        {
            // Produce random number by global from MAVLINK_SYS_ID_MIN to MAVLINK_SYS_ID_MAX
            v = (QRandomGenerator::global()->generate()) % MAVLINK_SYS_ID_MAX + MAVLINK_SYS_ID_MIN;

            // Show the random number in lineEdits
            target->clear();
            target->insert(QString::number(v));
        }
    }
}

void MavVehicleManager::on_Launch_clicked()
{
    PRINT_FUNC;
	
    int err = 0;
	
    // Validate the range of system IDs
	for(int i = 0; i <= ui->comboBox->currentIndex(); i++)
    {
        if(!_sysIds.at(i)->hasAcceptableInput())
        {
            err++;
        }
	}

    if(err)
    {
        apprintf(RED("[ERR] System ID error. (Range: %d - %d)"), MAVLINK_SYS_ID_MIN, MAVLINK_SYS_ID_MAX);
        return;
    }

    // Disable buttons
    _SetInputEnable(false);


    // Start to launch vehicles

    // Initial MAVLink Server
    for(int i = 0; i <= ui->comboBox->currentIndex(); i++)
    {
        _mavlink.append(new mavlink_udp((SERVER_PORT + i), _sysIds.at(i)->displayText().toShort()));

    	_mavlink.at(i)->udpInit();
    }
}

void MavVehicleManager::on_Stop_clicked()
{
    PRINT_FUNC;
	
	ui->Stop->setEnabled(false);
	
    // Deinitial MAVLink Server
    for(mavlink_udp * iterator: _mavlink)
    {
    	iterator->udpDeinit();

		delete iterator;
    }
	
	_mavlink.clear();

	_SetInputEnable(true);
}

void MavVehicleManager::_SetInputEnable(bool bEnable)
{
    if(bEnable)
    {
	    int i = 0;
		
		// ComboBox & RandomSysID Button
        ui->comboBox->setEnabled(true);
        ui->RandomSysID->setEnabled(true);

		// LineEdit
	    for(;i <= ui->comboBox->currentIndex() && i < _sysIds.size(); i++)
	    {
	        _sysIds.at(i)->setEnabled(true);
	    }
	    for(;i < _sysIds.size(); i++)
	    {
	        _sysIds.at(i)->setEnabled(false);
	        _sysIds.at(i)->clear();
	        //_sysIds.at(i)->insert("");
	    }

		// Launch Button
        ui->Launch->setEnabled(true);
        for(int j = 0; _sysIds.size() && j <= ui->comboBox->currentIndex(); j++)
        {
            if(!_sysIds.at(j)->hasAcceptableInput())
            {
                ui->Launch->setEnabled(false);
                break;
            }
        }

		// Stop Button
		ui->Stop->setEnabled(false);
    }
    else
    {
        // Disable buttons
        for(QLineEdit* target: _sysIds)
        {
            target->setEnabled(false);
        }
        ui->comboBox->setEnabled(false);
        ui->RandomSysID->setEnabled(false);
        ui->Launch->setEnabled(false);
		ui->Stop->setEnabled(true);
    }
}

void MavVehicleManager::on_lineEdit_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    _SetInputEnable(true);
}

void MavVehicleManager::on_lineEdit_2_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    _SetInputEnable(true);
}

void MavVehicleManager::on_lineEdit_3_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    _SetInputEnable(true);
}

void MavVehicleManager::on_lineEdit_4_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    _SetInputEnable(true);
}

void MavVehicleManager::on_lineEdit_5_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    _SetInputEnable(true);
}

void MavVehicleManager::on_lineEdit_6_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    _SetInputEnable(true);
}

void MavVehicleManager::on_lineEdit_7_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    _SetInputEnable(true);
}

void MavVehicleManager::on_lineEdit_8_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    _SetInputEnable(true);
}

void MavVehicleManager::on_lineEdit_9_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    _SetInputEnable(true);
}

void MavVehicleManager::on_lineEdit_10_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    _SetInputEnable(true);
}
