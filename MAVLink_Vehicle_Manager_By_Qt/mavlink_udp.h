//#pragma once

#ifndef MAVLINK_UDP_H
#define MAVLINK_UDP_H
/*
 * File name: mavlink_udp.h
 * Purpose: Simulate a vehicle which connects to QGC via MAVLink over UDP socket.
 * Creating Date: 2019.12.05
 * Author/Charge: Panda Wang (lucky00122@gmail.com)
 * Note: N/A
 */
#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QMutex>
#include <QThread>

#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include <mavlink.h>

//#define COMPILER_QT


#define CLIENT_IP		"127.0.0.1"
#define CLIENT_PORT		14550	// QGC UDP port
#define SERVER_PORT		14551
#define SYSTEM_ID		1
#define COMPONENT_ID	MAV_COMP_ID_AUTOPILOT1
#define BUFFER_LENGTH	2041 // minimum buffer size that can be used with qnx (I don't know why)

// Parameter Name Definitions
#define PARAM_NAME_ALTITUDE	"altitude"
#define AP_MAV_PROTOCOL_CAPABILITY MAV_PROTOCOL_CAPABILITY_MAVLINK2|\
									MAV_PROTOCOL_CAPABILITY_PARAM_FLOAT
// GLOBAL_POSITION_INT data
#define VEHICLE_GPS_LATITUDE			(float)24.9725460
#define VEHICLE_GPS_LONGITUDE			(float)121.5500510
#define VEHICLE_GPS_OFFSET(sysId)		((int32_t)sysId-128)*1000
#define GET_GPS_SCALED_VALUE(degree)	(int32_t)((float)degree*10000000)
#define VEHICLE_ALTITUDE_MSL	500000	// mm
#define VEHICLE_ALTITUDE_GND	400000	// mm


 /******************COLOR PRINTING DEFINITIONS *******************/
#define ESC_COLOR_NORMAL   "\033[m"
#define ESC_COLOR_BLACK    "\033[30m"
#define ESC_COLOR_RED      "\033[31m"
#define ESC_COLOR_GREEN    "\033[32m"
#define ESC_COLOR_YELLOW   "\033[33m"
#define ESC_COLOR_BLUE     "\033[34m"
#define ESC_COLOR_MAGENTA  "\033[35m"
#define ESC_COLOR_CYAN     "\033[36m"
#define ESC_COLOR_WHITE    "\033[37m"


/******************COLOR PRINTING DEFINITIONS *******************/
#define NORMAL( x )  ESC_COLOR_NORMAL  x
#define BLACK( x )   ESC_COLOR_BLACK   x ESC_COLOR_NORMAL
#define RED( x )     ESC_COLOR_RED     x ESC_COLOR_NORMAL
#define GREEN( x )   ESC_COLOR_GREEN   x ESC_COLOR_NORMAL
#define YELLOW( x )  ESC_COLOR_YELLOW  x ESC_COLOR_NORMAL
#define BLUE( x )    ESC_COLOR_BLUE    x ESC_COLOR_NORMAL
#define MAGENTA( x ) ESC_COLOR_MAGENTA x ESC_COLOR_NORMAL
#define CYAN( x )    ESC_COLOR_CYAN    x ESC_COLOR_NORMAL
#define WHITE( x )   ESC_COLOR_WHITE   x ESC_COLOR_NORMAL

#ifdef COMPILER_QT
#define PRINT_FUNC							qDebug(GREEN("%s"), __FUNCTION__)
#define PRINT_MAVLINK_FUNC					qDebug(GREEN("[%d]%s"), _systemId, __FUNCTION__)
#define PRINT_SENDER(str, args...)			qDebug(YELLOW(str), ##args )
#define printf_color(color, str, args...)   qDebug(color str ESC_COLOR_NORMAL "\r", ##args )
#define fprintf_color(color, str, args...)  fprintf(stderr, color str ESC_COLOR_NORMAL "\r", ##args )
#define apprintf(str, args...)				qDebug(str, ##args )
#else
#define PRINT_FUNC							printf(GREEN("%s\n"), __FUNCTION__)
#define PRINT_MAVLINK_FUNC					printf(GREEN("[%d]%s\n"), _systemId, __FUNCTION__)
#define PRINT_SENDER(str, args...)			printf(YELLOW(str), ##args )
#define printf_color(color, str, args...)   printf(color str ESC_COLOR_NORMAL "\r", ##args )
#define fprintf_color(color, str, args...)  fprintf(stderr, color str ESC_COLOR_NORMAL "\r", ##args )
#define apprintf(str, args...)				printf(str, ##args )
#endif

#define printf_black(str, args...)     printf_color(  ESC_COLOR_BLACK,   str, ##args )
#define fprintf_black(str, args...)    fprintf_color( ESC_COLOR_BLACK,   str, ##args )
#define printf_red(str, args...)       printf_color(  ESC_COLOR_RED,     str, ##args )
#define fprintf_red(str, args...)      fprintf_color( ESC_COLOR_RED,     str, ##args )
#define printf_green(str, args...)     printf_color(  ESC_COLOR_GREEN,   str, ##args )
#define fprintf_green(str, args...)    fprintf_color( ESC_COLOR_GREEN,   str, ##args )
#define printf_yellow(str, args...)    printf_color(  ESC_COLOR_YELLOW,  str, ##args )
#define fprintf_yellow(str, args...)   fprintf_color( ESC_COLOR_YELLOW,  str, ##args )
#define printf_blue(str, args...)      printf_color(  ESC_COLOR_BLUE,    str, ##args )
#define fprintf_blue(str, args...)     fprintf_color( ESC_COLOR_BLUE,    str, ##args )
#define fprintf_magenta(str, args...)  fprintf_color( ESC_COLOR_MAGENTA, str, ##args )
#define printf_magenta(str, args...)   printf_color(  ESC_COLOR_MAGENTA, str, ##args )
#define fprintf_cyan(str, args...)     fprintf_color( ESC_COLOR_CYAN,    str, ##args )
#define printf_cyan(str, args...)      printf_color(  ESC_COLOR_CYAN,    str, ##args )
#define fprintf_white(str, args...)    fprintf_color( ESC_COLOR_WHITE,   str, ##args )
#define printf_white(str, args...)     printf_color(  ESC_COLOR_WHITE,   str, ##args )

#define IS_MY_MESSAGE(sysId)	(sysId == _systemId || sysId == 0)

typedef enum _AP_PARAM_INDEX{
	AP_PARAM_INDEX_ALTITUDE,
	AP_PARAM_INDEX_TOTAL,
}AP_PARAM_INDEX;
	

class mavlink_udp : public QThread
{
	Q_OBJECT
		
public:
	mavlink_udp(quint16 Port, quint8 sysId);
	~mavlink_udp(){PRINT_MAVLINK_FUNC;}
	
	void udpInit(void);
	void udpDeinit(void);
	void writeBytes(const QByteArray data);
	void parseMavlinkMessage(uint8_t* buf, int64_t bufSize);
	void decodeMavlinkMessage(mavlink_message_t* msg);
	void AP_Decode_Command_Long(mavlink_command_long_t* payload);
	void AP_Send_Message_Param_Value(uint16_t param_index);
	void AP_Send_Message_Mission_count(uint8_t mission_type);

	void AP_Mutex_init(bool bInit){
		if(bInit)
		{
			if(!_mutex)	_mutex = new QMutex(QMutex::Recursive);
		}
		else
		{
			if(_mutex)	delete _mutex;
			_mutex = NULL;
		}
	}
	void AP_Mutex_Get(void)
	{
		if(_mutex)	_mutex->lock();
	}
	void AP_Mutex_Put(void)
	{
		if(_mutex)	_mutex->unlock();
	}
	void run() override;	// Qthread virtual protected function
	
	uint64_t microsSinceEpoch();


public slots:
	void readBytes(void);
	
private:
	QHostAddress 	_serverAddr;
	quint16			_serverPort;
	quint8			_systemId;
	QUdpSocket* 	_socket;
	QMutex*			_mutex;
	bool			_IsthreadSenderOn;
};

#endif	/* MAVLINK_UDP_H */
