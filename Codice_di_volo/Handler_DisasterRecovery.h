//DISASTER RECOVERY HANDLER

#pragma once
#ifndef DISASTER_RECOVERY_H
#define DISASTER_RECOVERY_H

#define DISASTER_DISP_FLAG		0
#define DISASTER_DISP_ALT		1
#define DISASTER_DISP_PACCHETTI	5
#define DISASTER_DISP_TEMPO		9

#include "Utilita_Librerie.h"

extern STR_Sistema		Sistema;
extern STR_Telemetria	Telemetria;
extern STR_Sensori		Sensori;

void do_DisasterRecovery();
void arm_DisasterRecovery();
void update_DisasterRecovery();
void disarm_DisasterRecovery();

#endif
