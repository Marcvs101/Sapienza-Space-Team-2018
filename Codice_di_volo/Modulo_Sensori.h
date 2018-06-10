//M101

#pragma once
#ifndef STR_SENSORI_H
#define STR_SENSORI_H

#include "Utilita_Librerie.h"

class STR_Sensori{
	public:
		DataFlash		Flash;
		MPU9250			IMU;
		Adafruit_BMP280	BMP;
};

#endif
