//DISASTER RECOVERY HANDLER
//Responsabili: Marco

//Direttive di preprocessore
#include "Handler_DisasterRecovery.h"

//Funzione principale
void do_DisasterRecovery(){
	//Dichiarazione variabili
	long velocita_verticale = 0;
	byte memoria[DISASTER_DISP_TEMPO+4];
	
	//Logica
	Sistema.Altitudine = Sensori.BMP.readAltitude(1013.25);
	velocita_verticale = Sensori.BMP.readAltitude(1013.25) - Sistema.Altitudine;

	recover_DisasterRecovery();

	if (velocita_verticale < 0l){
		Sistema.StatoAttuale = STATE_HIGH_DESCENT;
		Sistema.StatoPrecedente = STATE_DISASTER;
		Telemetria.AggiornaCampo(STATE_HIGH_DESCENT, TLM_SOFTWARE_STATE);
		Telemetria.AggiornaCampo(STATE_DISASTER, TLM_PREVIOUS_STATE);
	} else {
		Sistema.StatoAttuale = STATE_ASCENT;
		Sistema.StatoPrecedente = STATE_DISASTER;
		Telemetria.AggiornaCampo(STATE_ASCENT, TLM_SOFTWARE_STATE);
		Telemetria.AggiornaCampo(STATE_DISASTER, TLM_PREVIOUS_STATE);
	}
	return;
}

//Funzioni di servizio
void arm_DisasterRecovery(){
	EEPROM.update(0,'1');
}

void disarm_DisasterRecovery(){
	EEPROM.update(0,'\0');
}

void recover_DisasterRecovery(){
	char buff[9];
	memset(buff,'\0',9);
	for (int i=DISASTER_DISP_ALT; i<DISASTER_DISP_ALT+4; i++){
		buff[i-DISASTER_DISP_ALT] = EEPROM.read(i);
	}
	Sistema.AltitudineTerra = strtol((const char*) buff,0,10);
	memset(buff,'\0',9);
	for (int i=DISASTER_DISP_PACCHETTI; i<DISASTER_DISP_PACCHETTI+4; i++){
		buff[i-DISASTER_DISP_PACCHETTI] = EEPROM.read(i);
	}
	Sistema.NumeroPacchetti = strtoul((const char*) buff,0,10);
	memset(buff,'\0',9);
	for (int i=DISASTER_DISP_TEMPO; i<DISASTER_DISP_TEMPO+8; i++){
		buff[i-DISASTER_DISP_TEMPO] = EEPROM.read(i);
	}
	Sistema.InizioMissione = strtoul((const char*) buff,0,10);
}

void update_DisasterRecovery(){
	char buff[9];
	memset(buff,'\0',9);
	ltoa(Sistema.Altitudine,buff,10);
	for (int i=DISASTER_DISP_ALT;i<DISASTER_DISP_ALT+4;i++){
		EEPROM.update(i,buff[i-DISASTER_DISP_ALT]);
	}
	memset(buff,'\0',9);
	ultoa(Sistema.NumeroPacchetti,buff,10);
	for (int i=DISASTER_DISP_PACCHETTI;i<DISASTER_DISP_PACCHETTI+4;i++){
		EEPROM.update(i,buff[i-DISASTER_DISP_PACCHETTI]);
	}
	memset(buff,'\0',9);
	ultoa(Sistema.InizioMissione,buff,10);
	for (int i=DISASTER_DISP_TEMPO;i<DISASTER_DISP_TEMPO+8;i++){
		EEPROM.update(i,buff[i-DISASTER_DISP_TEMPO]);
	}
}

