//M101

#pragma once
#ifndef STR_TELEMETRIA_H
#define STR_TELEMETRIA_H

#include "Utilita_Librerie.h"

#define TLM_DISP_TEAM_ID		0
#define TLM_DISP_MISSION_TIME	TLM_DISP_TEAM_ID		+ 4 + 1
#define TLM_DISP_PACKET_COUNT	TLM_DISP_MISSION_TIME	+ 8 + 1
#define TLM_DISP_ALT_SENSOR		TLM_DISP_PACKET_COUNT	+ 4 + 1
#define TLM_DISP_PRESSURE		TLM_DISP_ALT_SENSOR		+ 4 + 1
#define TLM_DISP_TEMP			TLM_DISP_PRESSURE		+ 4 + 1
#define TLM_DISP_VOLTAGE		TLM_DISP_TEMP			+ 4 + 1
#define TLM_DISP_GPS_TIME		TLM_DISP_VOLTAGE		+ 2 + 1
#define TLM_DISP_GPS_LATITUDE	TLM_DISP_GPS_TIME		+ 8 + 1
#define TLM_DISP_GPS_LONGITUDE	TLM_DISP_GPS_LATITUDE	+ 8 + 1
#define TLM_DISP_GPS_ALTITUDE	TLM_DISP_GPS_LONGITUDE	+ 8 + 1
#define TLM_DISP_GPS_SATS		TLM_DISP_GPS_ALTITUDE	+ 4 + 1
#define TLM_DISP_TILT_X			TLM_DISP_GPS_SATS		+ 2 + 1
#define TLM_DISP_TILT_Y			TLM_DISP_TILT_X			+ 8 + 1
#define TLM_DISP_TILT_Z			TLM_DISP_TILT_Y			+ 8 + 1
#define TLM_DISP_SOFTWARE_STATE	TLM_DISP_TILT_Z			+ 8 + 1
#define TLM_DISP_PREVIOUS_STATE	TLM_DISP_SOFTWARE_STATE	+ 1 + 1
#define TLM_DISP_WIND_SPEED		TLM_DISP_PREVIOUS_STATE	+ 1 + 1

/* NOTE SULLA TELEMETRIA
 * 
 * 1 Byte	- <SOFTWARE_STATE>,<PREVIOUS_STATE>
 * 2 Bytes	- <TEMP>,<VOLTAGE>,<WIND_SPEED>,<GPS_SATS>
 * 4 Bytes	- <TEAM_ID>,<PACKET_COUNT>,<ALT_SENSOR>,<PRESSURE>,<TEMPERATURE>
 * 8 Bytes	- <MISSION_TIME>,<GPS_TIME>,<GPS_LATITUDE>,<GPS_LONGITUDE>,<GPS_ALTITUDE>,<TILT_X>,<TILT_Y>,<TILT_Z>
 * 
 * Tot 2+6+20+56
 */

class STR_Telemetria{
	private:
		char buffer[TLM_DISP_WIND_SPEED+10];
		uint16_t FlashPage;
		uint8_t FlashBuffer;
		uint16_t FlashOffset;
	public:
		STR_Telemetria();
		void AggiornaCampo(int valore, int campo);
		void AggiornaCampo(unsigned int valore, int campo);
		void AggiornaCampo(long valore, int campo);
		void AggiornaCampo(unsigned long valore, int campo);
		void AggiornaCampo(float valore, int campo);
		void Invia();
};

//Nella funzione AggiornaCampo, passare come secondo argomento la macro TLM desiderata
//Ad esempio, per aggiornare l'altitudine scrivere
//NomeVariabileTelemetria.AggiornaCampo(123.4,TLM_ALT_SENSOR);
#define TLM_TEAM_ID			1
#define TLM_MISSION_TIME	2
#define TLM_PACKET_COUNT	3
#define TLM_ALT_SENSOR		4
#define TLM_PRESSURE		5
#define TLM_TEMP			6
#define TLM_VOLTAGE			7
#define TLM_GPS_TIME		8
#define TLM_GPS_LATITUDE	9
#define TLM_GPS_LONGITUDE	10
#define TLM_GPS_ALTITUDE	11
#define TLM_GPS_SATS		12
#define TLM_TILT_X			13
#define TLM_TILT_Y			14
#define TLM_TILT_Z			15
#define TLM_SOFTWARE_STATE	16
#define TLM_PREVIOUS_STATE	17
#define TLM_WIND_SPEED		18

//Come usare la libreria:
//Per prima cosa fillare i campi con la funzione AggiornaCampo
//Una volta aggiornati tutti (anche non perforza tutti) i campi, usare la funzione Invia
//Il comando Invia si occuperà di passare a terra l'intera stringa di telemetria
//I valori precedentemente inseriti rimangono in memoria fino al prossimo AggiornaCampo
//A quel punto la funzione sovrascriverà SOLO il campo specificato


#endif
