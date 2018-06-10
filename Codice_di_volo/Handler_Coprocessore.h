//RICHIESTA DATI ALLO SLAVE

#pragma once
#ifndef COPROC_H
#define COPROC_H

#include "Utilita_Librerie.h"

class Coprocessore {
	public:
		static void ottieniDati();
		static void eseguiComando(char comando);
};

class Coprocessore_Dati {
	public:
		static float			GPSlat;
		static float			GPSlon;
		static long				GPSalt;
		static unsigned int		GPSsats;
		static unsigned long	GPStempo;
		static float			Windspeed;
};

#endif
