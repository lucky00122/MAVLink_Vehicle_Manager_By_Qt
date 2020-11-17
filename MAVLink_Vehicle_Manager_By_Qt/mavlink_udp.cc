/*
 * File name: mavlink_udp.c
 * Purpose: Simulate a vehicle which connects to QGC via MAVLink over UDP socket.
 * Creating Date: 2019.12.05
 * Author/Charge: Panda Wang (lucky00122@gmail.com)
 * Note: N/A
 */
#include "mavlink_udp.h"

mavlink_udp::mavlink_udp(quint16 Port, quint8 sysId): 
		_serverAddr(QHostAddress::AnyIPv4), _serverPort(Port), _systemId(sysId), 
		_socket(NULL), _mutex(NULL)
{
	apprintf("[%d]Launch Vehicle.\n", _systemId);
}

void mavlink_udp::udpInit(void)
{
	PRINT_MAVLINK_FUNC;

	_socket = new QUdpSocket();
	bool bIsSocketOK = false;

	//socket->setProxy(QNetworkProxy::NoProxy);

	//apprintf("Bind server IP:%s:%d...\n", qPrintable(_serverAddr.toString()), _serverPort);
	
	bIsSocketOK = _socket->bind(_serverAddr, _serverPort, QAbstractSocket::ReuseAddressHint | QAbstractSocket::ShareAddress);

	if(bIsSocketOK)
	{
		apprintf("Bind IP:%s:%d Success\n", qPrintable(_serverAddr.toString()), _serverPort);

		// Connect the receive Signal-Slot
		QObject::connect(_socket, &QUdpSocket::readyRead, this, &mavlink_udp::readBytes);
	}
	else
	{
		apprintf(RED("Bind IP:%s:%d Fail\n"), qPrintable(_serverAddr.toString()), _serverPort);
	}
	
	AP_Mutex_init(true);
	
	// Starting running UDP sender
	_IsthreadSenderOn = true;
	start();
}

void mavlink_udp::udpDeinit(void)
{
	PRINT_MAVLINK_FUNC;
	
	// Close sender thread
	_IsthreadSenderOn = false;

	// Wait for thread finishing
	while(!isFinished());

	// Close Socket
	if(_socket)	_socket->disconnectFromHost();
	_socket = NULL;

	// Deinit mutex
	AP_Mutex_init(false);
}

void mavlink_udp::run()
{
	mavlink_message_t msg;
	uint8_t buf[BUFFER_LENGTH];
	uint16_t len;
	
	while(_IsthreadSenderOn)
	{		
		// Send Messages
		/*Send Heartbeat HEARTBEAT */
		mavlink_msg_heartbeat_pack(_systemId, COMPONENT_ID, &msg, 
									MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
		len = mavlink_msg_to_send_buffer(buf, &msg);
		writeBytes(QByteArray((const char*)buf, len));
	
		PRINT_SENDER("[%d]HEARTBEAT: Type:%d Autopilot:%d MaxVer:200 BaseMode:%d SysState:%d\n", _systemId,
						MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, MAV_STATE_ACTIVE);

		/* Send Status SYS_STATUS */
		mavlink_msg_sys_status_pack(_systemId, COMPONENT_ID, &msg, 
									0, 0, 0, 500, 14800, 370, 80, 0, 0, 0, 0, 0, 0);
		len = mavlink_msg_to_send_buffer(buf, &msg);
		writeBytes(QByteArray((const char*)buf, len));
		//PRINT_SENDER("[%d]SYS_STATUS\n", _systemId);

		/* Send GLOBAL_POSITION_INT */
		mavlink_msg_global_position_int_pack(_systemId, COMPONENT_ID, &msg, 
										microsSinceEpoch(), 
										(GET_GPS_SCALED_VALUE(VEHICLE_GPS_LATITUDE)+VEHICLE_GPS_OFFSET(_systemId)), 
										(GET_GPS_SCALED_VALUE(VEHICLE_GPS_LONGITUDE)+VEHICLE_GPS_OFFSET(_systemId)), 
										VEHICLE_ALTITUDE_MSL, VEHICLE_ALTITUDE_GND, 
										0, 0, 0, UINT16_MAX);
		len = mavlink_msg_to_send_buffer(buf, &msg);
		writeBytes(QByteArray((const char*)buf, len));
		//PRINT_SENDER("[%d]GLOBAL_POSITION_INT\n", _systemId);
		
		/* Send attitude */
		mavlink_msg_attitude_pack(_systemId, COMPONENT_ID, &msg, 
									microsSinceEpoch(), 0.785, 0.17444, 1.58, // 45deg, 10deg ,90deg
									0.01, 0.02, 0.03);
		len = mavlink_msg_to_send_buffer(buf, &msg);
		writeBytes(QByteArray((const char*)buf, len));
		//PRINT_SENDER("[%d]ATTITUDE\n", _systemId);
		// End Send Messages
		
		memset(buf, 0, BUFFER_LENGTH);

		if(_IsthreadSenderOn)sleep(1);
	}
}

void mavlink_udp::readBytes(void)
{
	//PRINT_FUNC;

	if (!_socket)	return;

	int64_t dataSize = 0;
    QHostAddress senderAddr;
    quint16 senderPort;
	uint8_t buf[BUFFER_LENGTH];

	AP_Mutex_Get();
	
    while (_socket->hasPendingDatagrams())
    {
        dataSize = _socket->pendingDatagramSize();
		
        dataSize = _socket->readDatagram((char*)buf, dataSize, &senderAddr, &senderPort);

		if(dataSize)
		{
			//apprintf("Receive %ldbyts from %s:%d\n", dataSize, qPrintable(senderAddr.toString()), senderPort);

			parseMavlinkMessage(buf, dataSize);
		}
		else
		{
			apprintf(RED("[%d]%s Fail\n"), _systemId, __FUNCTION__);
		}
    }

	AP_Mutex_Put();
}

void mavlink_udp::writeBytes(const QByteArray data)
{
	//PRINT_FUNC;
	if (!_socket)	return;

	int8_t sendBytes = 0;
	QHostAddress ClientAddr = QHostAddress::LocalHost;
	
	//apprintf("Send data to IP:%s:%d...\n", qPrintable(ClientAddr.toString()), CLIENT_PORT);
	
	AP_Mutex_Get();
	
	if((sendBytes = _socket->writeDatagram(data, ClientAddr, CLIENT_PORT)) < 0)
	{
		apprintf(RED("[%d]%s Fail.\n"), _systemId, __FUNCTION__);
    }
	else
    {
		//apprintf("Send Success:%dbyts\n", sendBytes);
    }
	AP_Mutex_Put();
}

void mavlink_udp::parseMavlinkMessage(uint8_t* buf, int64_t bufSize)
{
	mavlink_message_t msg;
	mavlink_status_t status;
			
	for (int i = 0; i < bufSize; i++)
	{
		if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status) == MAVLINK_FRAMING_OK)
		{
			// Decode Message
			decodeMavlinkMessage(&msg);
		}
	}
}

void mavlink_udp::decodeMavlinkMessage(mavlink_message_t* msg)
{
	switch(msg->msgid)
	{
		case MAVLINK_MSG_ID_HEARTBEAT:
		{ 
			mavlink_heartbeat_t payload;
			
	     	mavlink_msg_heartbeat_decode(msg, &payload); 

			apprintf("HEARTBEAT: TYPE:%d AUTOPILOT:%d MODE:%d SUB_MODE:%d STATUS:%d VER:0x%X\n", 
						payload.type, payload.autopilot, payload.base_mode,
						payload.custom_mode, payload.system_status,
						payload.mavlink_version);

			break; 
		}
		case MAVLINK_MSG_ID_SYSTEM_TIME:
		{ 
			mavlink_system_time_t payload;
			
	     	mavlink_msg_system_time_decode(msg, &payload); 

			apprintf("SYSTEM_TIME: UNIX_T:%luus TIME:%ums\n", 
						payload.time_unix_usec, payload.time_boot_ms);

			break; 
		}
		case MAVLINK_MSG_ID_PARAM_REQUEST_READ:
		{ 
			mavlink_param_request_read_t payload;
			
	     	mavlink_msg_param_request_read_decode(msg, &payload); 

			if(IS_MY_MESSAGE(payload.target_system))
			{
				apprintf("[To %d]PARAM_REQUEST_READ: PARAM:%d NAME:%s COMP:%d\n", 
						payload.target_system, payload.param_index, payload.param_id, payload.target_component);

				AP_Send_Message_Param_Value(payload.param_index);
			}
			
			break; 
		} 
		case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
		{ 
			mavlink_param_request_list_t payload;
			
	     	mavlink_msg_param_request_list_decode(msg, &payload); 

			if(IS_MY_MESSAGE(payload.target_system))
			{
				apprintf("[To %d]PARAM_REQUEST_LIST: COMP:%d\n", 
							payload.target_system, payload.target_component);

				AP_Send_Message_Param_Value(AP_PARAM_INDEX_TOTAL);
			}
			
			break; 
		} 
		case MAVLINK_MSG_ID_MISSION_REQUEST_LIST:	// Respond MISSION_COUNT
		{ 
			mavlink_mission_request_list_t payload;
			
	     	mavlink_msg_mission_request_list_decode(msg, &payload); 

			if(IS_MY_MESSAGE(payload.target_system))
			{
				apprintf("[To %d]MISSION_REQUEST_LIST: MISSION_TYPE:%d, SYS:%d COMP:%d\n", 
							payload.target_system, payload.mission_type, payload.target_component);

				AP_Send_Message_Mission_count(payload.mission_type);
			}
			
			break; 
		} 
		case MAVLINK_MSG_ID_COMMAND_LONG:
		{ 
			mavlink_command_long_t payload;
			
	     	mavlink_msg_command_long_decode(msg, &payload);

			if(IS_MY_MESSAGE(payload.target_system))
			{
				apprintf("[To %d]", payload.target_system);
			
				AP_Decode_Command_Long(&payload);
			}

			break; 
		} 
		default:
			apprintf("\n[To %d]Received: MSG:%d SEQ:%d COMP:%d LEN:%d \n", 
					msg->sysid, msg->msgid, msg->seq, msg->compid, msg->len);
			break;
	}
}

void mavlink_udp::AP_Decode_Command_Long(mavlink_command_long_t* payload)
{
	mavlink_message_t msg;
	uint8_t buf[BUFFER_LENGTH];
	uint16_t len;
	
	switch(payload->command)
	{
		case MAV_CMD_REQUEST_PROTOCOL_VERSION:	// Respond PROTOCOL_VERSION
			apprintf("REQUEST_PROTOCOL_VERSION: Protocol:%d\n", (int)payload->param1);
			if(payload->param1)
			{
				mavlink_msg_protocol_version_pack(_systemId, COMPONENT_ID, &msg, 
													200, 100, 200, NULL, NULL);
				len = mavlink_msg_to_send_buffer(buf, &msg);
				writeBytes(QByteArray((const char*)buf, len));

				PRINT_SENDER("[%d]PROTOCOL_VERSION: Ver:200 MinVer:100 MaxVer:200\n", _systemId);

			}
			break;
		case MAV_CMD_REQUEST_AUTOPILOT_CAPABILITIES:	// Respond AUTOPILOT_VERSION
			apprintf("REQUEST_AUTOPILOT_CAPABILITIES: Version:%d\n", (int)payload->param1);
			if(payload->param1)
			{
				mavlink_msg_autopilot_version_pack(_systemId, COMPONENT_ID, &msg, 
													AP_MAV_PROTOCOL_CAPABILITY, 6, 3, 0, 0, NULL, NULL, NULL, 2019, 1120, 0, NULL);
				len = mavlink_msg_to_send_buffer(buf, &msg);
				writeBytes(QByteArray((const char*)buf, len));

				PRINT_SENDER("[%d]AUTOPILOT_VERSION: Cap:0x%x FSWVer:6 MSWVer:3 OSVer:0 BoardVer:0 VendorId:2019 ProductId:1120\n", _systemId, AP_MAV_PROTOCOL_CAPABILITY);
			}
			break;
		default:
			apprintf("COMMAND_LONG: CMD:%d P:%f %f %f %f %f %f %f COMP:%d COMF:%d\n", 
						payload->command, 
						payload->param1, payload->param2, payload->param3, payload->param4,
						payload->param5, payload->param6, payload->param7,
						payload->target_component, payload->confirmation);
			break;
	}
}

void mavlink_udp::AP_Send_Message_Param_Value(uint16_t param_index)
{
	mavlink_message_t msg;
	uint8_t buf[BUFFER_LENGTH];
	uint16_t len;

	if(param_index == AP_PARAM_INDEX_TOTAL)
	{
		mavlink_msg_param_value_pack(_systemId, COMPONENT_ID, &msg, 
									PARAM_NAME_ALTITUDE, 100, MAV_PARAM_TYPE_UINT8, AP_PARAM_INDEX_TOTAL, 0);
		len = mavlink_msg_to_send_buffer(buf, &msg);
		writeBytes(QByteArray((const char*)buf, len));
		PRINT_SENDER("[%d]PARAM_VALUE\n", _systemId);
	}
	else
	{
		mavlink_msg_param_value_pack(_systemId, COMPONENT_ID, &msg, 
									PARAM_NAME_ALTITUDE, 100, MAV_PARAM_TYPE_UINT8, AP_PARAM_INDEX_TOTAL, 0);
		len = mavlink_msg_to_send_buffer(buf, &msg);
		writeBytes(QByteArray((const char*)buf, len));
		PRINT_SENDER("[%d]PARAM_VALUE\n", _systemId);
	}
}

void mavlink_udp::AP_Send_Message_Mission_count(uint8_t mission_type)
{
	mavlink_message_t msg;
	uint8_t buf[BUFFER_LENGTH];
	uint16_t len;

	switch(mission_type)
	{
		default:
		case MAV_MISSION_TYPE_MISSION:
			mavlink_msg_mission_count_pack(_systemId, COMPONENT_ID, &msg, 
												_systemId, COMPONENT_ID, 0, mission_type);
			break;
	}
	
	len = mavlink_msg_to_send_buffer(buf, &msg);
	writeBytes(QByteArray((const char*)buf, len));
	PRINT_SENDER("[%d]MISSION_COUNT\n", _systemId);
}

/* QNX timer version */
#if (defined __QNX__) | (defined __QNXNTO__)
uint64_t mavlink_udp::microsSinceEpoch()
{
		
	struct timespec time;
		
	uint64_t micros = 0;
		
	clock_gettime(CLOCK_REALTIME, &time);  
	micros = (uint64_t)time.tv_sec * 1000000 + time.tv_nsec/1000;
		
	return micros;
}
#else
uint64_t mavlink_udp::microsSinceEpoch()
{
		
	struct timeval tv;
		
	uint64_t micros = 0;
		
	gettimeofday(&tv, NULL);  
	micros =  ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;
		
	return micros;
}
#endif
