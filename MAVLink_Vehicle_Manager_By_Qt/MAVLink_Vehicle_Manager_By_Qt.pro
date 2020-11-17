#-------------------------------------------------
#
# Project created by QtCreator 2019-11-29T15:41:35
#
#-------------------------------------------------

QT       += \
        core gui \
        network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mavlink_qt_vehicle_manager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mavvehiclemanager.cpp \
    mavlink_udp.cc

INCLUDEPATH += \
        include/common/

HEADERS += \
        mavvehiclemanager.h \
    include/common/common.h \
    include/common/mavlink.h \
    include/common/mavlink_msg_actuator_control_target.h \
    include/common/mavlink_msg_actuator_output_status.h \
    include/common/mavlink_msg_adsb_vehicle.h \
    include/common/mavlink_msg_altitude.h \
    include/common/mavlink_msg_att_pos_mocap.h \
    include/common/mavlink_msg_attitude.h \
    include/common/mavlink_msg_attitude_quaternion.h \
    include/common/mavlink_msg_attitude_quaternion_cov.h \
    include/common/mavlink_msg_attitude_target.h \
    include/common/mavlink_msg_auth_key.h \
    include/common/mavlink_msg_autopilot_version.h \
    include/common/mavlink_msg_battery_status.h \
    include/common/mavlink_msg_button_change.h \
    include/common/mavlink_msg_camera_capture_status.h \
    include/common/mavlink_msg_camera_image_captured.h \
    include/common/mavlink_msg_camera_information.h \
    include/common/mavlink_msg_camera_settings.h \
    include/common/mavlink_msg_camera_trigger.h \
    include/common/mavlink_msg_cellular_status.h \
    include/common/mavlink_msg_change_operator_control.h \
    include/common/mavlink_msg_change_operator_control_ack.h \
    include/common/mavlink_msg_collision.h \
    include/common/mavlink_msg_command_ack.h \
    include/common/mavlink_msg_command_int.h \
    include/common/mavlink_msg_command_long.h \
    include/common/mavlink_msg_control_system_state.h \
    include/common/mavlink_msg_data_stream.h \
    include/common/mavlink_msg_data_transmission_handshake.h \
    include/common/mavlink_msg_debug.h \
    include/common/mavlink_msg_debug_float_array.h \
    include/common/mavlink_msg_debug_vect.h \
    include/common/mavlink_msg_distance_sensor.h \
    include/common/mavlink_msg_encapsulated_data.h \
    include/common/mavlink_msg_estimator_status.h \
    include/common/mavlink_msg_extended_sys_state.h \
    include/common/mavlink_msg_fence_status.h \
    include/common/mavlink_msg_file_transfer_protocol.h \
    include/common/mavlink_msg_flight_information.h \
    include/common/mavlink_msg_follow_target.h \
    include/common/mavlink_msg_global_position_int.h \
    include/common/mavlink_msg_global_position_int_cov.h \
    include/common/mavlink_msg_global_vision_position_estimate.h \
    include/common/mavlink_msg_gps2_raw.h \
    include/common/mavlink_msg_gps2_rtk.h \
    include/common/mavlink_msg_gps_global_origin.h \
    include/common/mavlink_msg_gps_inject_data.h \
    include/common/mavlink_msg_gps_input.h \
    include/common/mavlink_msg_gps_raw_int.h \
    include/common/mavlink_msg_gps_rtcm_data.h \
    include/common/mavlink_msg_gps_rtk.h \
    include/common/mavlink_msg_gps_status.h \
    include/common/mavlink_msg_heartbeat.h \
    include/common/mavlink_msg_high_latency.h \
    include/common/mavlink_msg_high_latency2.h \
    include/common/mavlink_msg_highres_imu.h \
    include/common/mavlink_msg_hil_actuator_controls.h \
    include/common/mavlink_msg_hil_controls.h \
    include/common/mavlink_msg_hil_gps.h \
    include/common/mavlink_msg_hil_optical_flow.h \
    include/common/mavlink_msg_hil_rc_inputs_raw.h \
    include/common/mavlink_msg_hil_sensor.h \
    include/common/mavlink_msg_hil_state.h \
    include/common/mavlink_msg_hil_state_quaternion.h \
    include/common/mavlink_msg_home_position.h \
    include/common/mavlink_msg_isbd_link_status.h \
    include/common/mavlink_msg_landing_target.h \
    include/common/mavlink_msg_link_node_status.h \
    include/common/mavlink_msg_local_position_ned.h \
    include/common/mavlink_msg_local_position_ned_cov.h \
    include/common/mavlink_msg_local_position_ned_system_global_offset.h \
    include/common/mavlink_msg_log_data.h \
    include/common/mavlink_msg_log_entry.h \
    include/common/mavlink_msg_log_erase.h \
    include/common/mavlink_msg_log_request_data.h \
    include/common/mavlink_msg_log_request_end.h \
    include/common/mavlink_msg_log_request_list.h \
    include/common/mavlink_msg_logging_ack.h \
    include/common/mavlink_msg_logging_data.h \
    include/common/mavlink_msg_logging_data_acked.h \
    include/common/mavlink_msg_manual_control.h \
    include/common/mavlink_msg_manual_setpoint.h \
    include/common/mavlink_msg_memory_vect.h \
    include/common/mavlink_msg_message_interval.h \
    include/common/mavlink_msg_mission_ack.h \
    include/common/mavlink_msg_mission_changed.h \
    include/common/mavlink_msg_mission_clear_all.h \
    include/common/mavlink_msg_mission_count.h \
    include/common/mavlink_msg_mission_current.h \
    include/common/mavlink_msg_mission_item.h \
    include/common/mavlink_msg_mission_item_int.h \
    include/common/mavlink_msg_mission_item_reached.h \
    include/common/mavlink_msg_mission_request.h \
    include/common/mavlink_msg_mission_request_int.h \
    include/common/mavlink_msg_mission_request_list.h \
    include/common/mavlink_msg_mission_request_partial_list.h \
    include/common/mavlink_msg_mission_set_current.h \
    include/common/mavlink_msg_mission_write_partial_list.h \
    include/common/mavlink_msg_mount_orientation.h \
    include/common/mavlink_msg_named_value_float.h \
    include/common/mavlink_msg_named_value_int.h \
    include/common/mavlink_msg_nav_controller_output.h \
    include/common/mavlink_msg_obstacle_distance.h \
    include/common/mavlink_msg_odometry.h \
    include/common/mavlink_msg_onboard_computer_status.h \
    include/common/mavlink_msg_open_drone_id_authentication.h \
    include/common/mavlink_msg_open_drone_id_basic_id.h \
    include/common/mavlink_msg_open_drone_id_location.h \
    include/common/mavlink_msg_open_drone_id_message_pack.h \
    include/common/mavlink_msg_open_drone_id_operator_id.h \
    include/common/mavlink_msg_open_drone_id_self_id.h \
    include/common/mavlink_msg_open_drone_id_system.h \
    include/common/mavlink_msg_optical_flow.h \
    include/common/mavlink_msg_optical_flow_rad.h \
    include/common/mavlink_msg_orbit_execution_status.h \
    include/common/mavlink_msg_param_ext_ack.h \
    include/common/mavlink_msg_param_ext_request_list.h \
    include/common/mavlink_msg_param_ext_request_read.h \
    include/common/mavlink_msg_param_ext_set.h \
    include/common/mavlink_msg_param_ext_value.h \
    include/common/mavlink_msg_param_map_rc.h \
    include/common/mavlink_msg_param_request_list.h \
    include/common/mavlink_msg_param_request_read.h \
    include/common/mavlink_msg_param_set.h \
    include/common/mavlink_msg_param_value.h \
    include/common/mavlink_msg_ping.h \
    include/common/mavlink_msg_play_tune.h \
    include/common/mavlink_msg_play_tune_v2.h \
    include/common/mavlink_msg_position_target_global_int.h \
    include/common/mavlink_msg_position_target_local_ned.h \
    include/common/mavlink_msg_power_status.h \
    include/common/mavlink_msg_protocol_version.h \
    include/common/mavlink_msg_radio_status.h \
    include/common/mavlink_msg_raw_imu.h \
    include/common/mavlink_msg_raw_pressure.h \
    include/common/mavlink_msg_rc_channels.h \
    include/common/mavlink_msg_rc_channels_override.h \
    include/common/mavlink_msg_rc_channels_raw.h \
    include/common/mavlink_msg_rc_channels_scaled.h \
    include/common/mavlink_msg_request_data_stream.h \
    include/common/mavlink_msg_resource_request.h \
    include/common/mavlink_msg_safety_allowed_area.h \
    include/common/mavlink_msg_safety_set_allowed_area.h \
    include/common/mavlink_msg_scaled_imu.h \
    include/common/mavlink_msg_scaled_imu2.h \
    include/common/mavlink_msg_scaled_imu3.h \
    include/common/mavlink_msg_scaled_pressure.h \
    include/common/mavlink_msg_scaled_pressure2.h \
    include/common/mavlink_msg_scaled_pressure3.h \
    include/common/mavlink_msg_serial_control.h \
    include/common/mavlink_msg_servo_output_raw.h \
    include/common/mavlink_msg_set_actuator_control_target.h \
    include/common/mavlink_msg_set_attitude_target.h \
    include/common/mavlink_msg_set_gps_global_origin.h \
    include/common/mavlink_msg_set_home_position.h \
    include/common/mavlink_msg_set_mode.h \
    include/common/mavlink_msg_set_position_target_global_int.h \
    include/common/mavlink_msg_set_position_target_local_ned.h \
    include/common/mavlink_msg_setup_signing.h \
    include/common/mavlink_msg_sim_state.h \
    include/common/mavlink_msg_smart_battery_info.h \
    include/common/mavlink_msg_smart_battery_status.h \
    include/common/mavlink_msg_statustext.h \
    include/common/mavlink_msg_statustext_long.h \
    include/common/mavlink_msg_storage_information.h \
    include/common/mavlink_msg_supported_tunes.h \
    include/common/mavlink_msg_sys_status.h \
    include/common/mavlink_msg_system_time.h \
    include/common/mavlink_msg_terrain_check.h \
    include/common/mavlink_msg_terrain_data.h \
    include/common/mavlink_msg_terrain_report.h \
    include/common/mavlink_msg_terrain_request.h \
    include/common/mavlink_msg_time_estimate_to_target.h \
    include/common/mavlink_msg_timesync.h \
    include/common/mavlink_msg_trajectory_representation_bezier.h \
    include/common/mavlink_msg_trajectory_representation_waypoints.h \
    include/common/mavlink_msg_tunnel.h \
    include/common/mavlink_msg_uavcan_node_info.h \
    include/common/mavlink_msg_uavcan_node_status.h \
    include/common/mavlink_msg_utm_global_position.h \
    include/common/mavlink_msg_v2_extension.h \
    include/common/mavlink_msg_vfr_hud.h \
    include/common/mavlink_msg_vibration.h \
    include/common/mavlink_msg_vicon_position_estimate.h \
    include/common/mavlink_msg_video_stream_information.h \
    include/common/mavlink_msg_video_stream_status.h \
    include/common/mavlink_msg_vision_position_estimate.h \
    include/common/mavlink_msg_vision_speed_estimate.h \
    include/common/mavlink_msg_wheel_distance.h \
    include/common/mavlink_msg_wifi_config_ap.h \
    include/common/mavlink_msg_wind_cov.h \
    include/common/testsuite.h \
    include/common/version.h \
    mavlink_udp.h

FORMS += \
        mavvehiclemanager.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
