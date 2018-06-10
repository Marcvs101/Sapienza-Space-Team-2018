//M101

#pragma once
#ifndef STR_SENSORI_H
#define STR_SENSORI_H

#include "Utilita_Librerie.h"

class STR_Sensori{
	public:
		SoftwareSerial*	GPSSeriale;
		TinyGPS			GPS;
		MPU9250			IMU;
		Adafruit_BMP280	BMP;
		SoftwareSerial*	Radio;
};

#endif
