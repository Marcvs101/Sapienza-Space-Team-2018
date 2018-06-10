//M101

#pragma once
#ifndef CMD_PROC_H
#define CMD_PROC_H

#define SLAVE_I2C	8

//COMANDI INTER-PROCESSORE
#define CMD_PROC_STAGE		'1'
#define CMD_PROC_CAMERA_ON	'2'
#define CMD_PROC_CAMERA_OFF	'3'
#define CMD_PROC_WIND_ON	'4'
#define CMD_PROC_WIND_OFF	'5'
#define CMD_PROC_CHANNEL	'6'
#define CMD_PROC_BUZZER_ON	'7'
#define CMD_PROC_BUZZER_OFF	'8'

//SPIAZZAMENTO DATI
#define CMD_PROC_DISP_GPS_LAT	0
#define CMD_PROC_DISP_GPS_LON	CMD_PROC_DISP_GPS_LAT + 8 + 1
#define CMD_PROC_DISP_GPS_ALT	CMD_PROC_DISP_GPS_LON + 8 + 1
#define CMD_PROC_DISP_GPS_SATS	CMD_PROC_DISP_GPS_ALT + 4 + 1
#define CMD_PROC_DISP_GPS_TIME	CMD_PROC_DISP_GPS_SATS + 2 + 1
#define CMD_PROC_DISP_WIND		CMD_PROC_DISP_GPS_TIME + 4 + 1

#endif
