//M101

#pragma once
#ifndef GENERAL_H
#define GENERAL_H

//Librerie dei sensori
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <MPU9250.h>
#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DataFlash.h>

//Librerie del cansat
#include "Definizioni_Comandi_cansat.h"
#include "Definizioni_Stati_software.h"
#include "Definizioni_Missione.h"
#include "Definizioni_Pin.h"
#include "Definizioni_Comandi_Coprocessore.h"

#include "Modulo_Sensori.h"
#include "Modulo_Telemetria.h"
#include "Modulo_VariabiliSistema.h"

#include "Handler_Coprocessore.h"
#include "Handler_DisasterRecovery.h"
#include "Handler_Interrupt.h"

#include "Fase_DiscesaAlta.h"
#include "Fase_DiscesaBassa.h"
#include "Fase_PrelancioAscesa.h"

#endif
