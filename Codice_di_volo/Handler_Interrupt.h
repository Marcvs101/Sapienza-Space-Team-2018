//DISASTER RECOVERY HANDLER

#pragma once
#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "Utilita_Librerie.h"

extern STR_Sistema		Sistema;
extern STR_Telemetria	Telemetria;
extern STR_Sensori		Sensori;

void do_InterruptHandler();

#endif
