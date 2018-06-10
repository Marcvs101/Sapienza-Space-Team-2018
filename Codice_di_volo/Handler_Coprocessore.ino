//RICHIESTA DATI ALLO SLAVE
//Responsabili: 

//Direttive di preprocessore
#include "Handler_Coprocessore.h"

//Inizializza variabili globali di Coprocessore_Dati
float			Coprocessore_Dati::GPSlat = 0.0;
float			Coprocessore_Dati::GPSlon = 0.0;
long			Coprocessore_Dati::GPSalt = 0;
unsigned int	Coprocessore_Dati::GPSsats = 0;
unsigned long	Coprocessore_Dati::GPStempo = 0;
float			Coprocessore_Dati::Windspeed = 0;

void Coprocessore::ottieniDati(){
	char buff[CMD_PROC_DISP_WIND+8];
	Wire.requestFrom(SLAVE_I2C, CMD_PROC_DISP_WIND+8);		// request 6 bytes from slave device #8
	
	//Leggi dati sul bus
	int index = 0;
	while (Wire.available() && (index < CMD_PROC_DISP_WIND+7)) {
		buff[index] = Wire.read();
		index++;
	}

	//Sbroglia i dati man mano
	char* ptr;
	Coprocessore_Dati::GPSlat = (float) strtod((const char*)buff,&ptr);
	Coprocessore_Dati::GPSlon = (float) strtod((const char*)(ptr+1),&ptr);
	Coprocessore_Dati::GPSalt = strtol((const char*)((ptr)+1),&ptr,16);
	Coprocessore_Dati::GPSsats = (unsigned int) strtoul((const char*)((ptr)+1),&ptr,16);
	Coprocessore_Dati::GPStempo = strtoul((const char*)((ptr)+1),&ptr,16);
	Coprocessore_Dati::Windspeed = (float) strtod((const char*)((ptr)+1),&ptr);

	//Caricali in telemetria
	Telemetria.AggiornaCampo(Coprocessore_Dati::GPSlat,		TLM_GPS_LATITUDE);
	Telemetria.AggiornaCampo(Coprocessore_Dati::GPSlon,		TLM_GPS_LONGITUDE);
	Telemetria.AggiornaCampo(Coprocessore_Dati::GPSalt,		TLM_GPS_ALTITUDE);
	Telemetria.AggiornaCampo(Coprocessore_Dati::GPSsats,	TLM_GPS_SATS);
	Telemetria.AggiornaCampo(Coprocessore_Dati::GPStempo,	TLM_GPS_TIME);
	Telemetria.AggiornaCampo(Coprocessore_Dati::Windspeed,	TLM_WIND_SPEED);
	Telemetria.AggiornaCampo(Coprocessore_Dati::GPStempo - Sistema.InizioMissione, TLM_MISSION_TIME);
}

void Coprocessore::eseguiComando(char cmd){
	Wire.beginTransmission(SLAVE_I2C);
	Wire.write(cmd);
	Wire.endTransmission();
}

