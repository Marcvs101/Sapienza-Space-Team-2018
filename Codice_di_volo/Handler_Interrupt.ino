//INTERRUPT HANDLER
//Responsabili: Marco

//Direttive di preprocessore
#include "Handler_Interrupt.h"

extern STR_Telemetria	Telemetria;
extern STR_Sistema		Sistema;

//Funzioni ausiliarie

//Funzione principale
void do_InterruptHandler(){
	//Dichiarazione variabili
	char messaggio[7];
	char opcode[3];
	char payload[5];
	unsigned long payloadNumber;
	unsigned int letti = 0;
	memset(messaggio, '\0', 7);
	memset(opcode, '\0', 3);
	memset(payload, '\0', 5);
	
	//Logica
	while (Serial.available()){
		char c = Serial.read();
		if (letti < 2){
			messaggio[letti] = c;
			opcode[letti] = c;
		}else if (letti >= 2 && letti < 6){
			messaggio[letti] = c;
			payload[letti-2] = c;
		}
		letti++;
	}
	
	if (letti < 2) {return;} //crepamale
	
	if (strcmp(opcode, CMD_OVRD_SETSTATE) == 0){
		payloadNumber = strtoul(payload,0,10);

		if (payloadNumber >= STATE_PRELAUNCH && payloadNumber <= STATE_LANDED ){
			Sistema.StatoAttuale = payloadNumber;
			Telemetria.AggiornaCampo(payloadNumber, TLM_SOFTWARE_STATE);
		}
		
	} else if (strcmp(opcode, CMD_OVRD_PARACHUTE) == 0){
		tone(PIN_SERVO,1000,350);
		Coprocessore::eseguiComando(CMD_PROC_STAGE);
		
	} else if (strcmp(opcode, CMD_OVRD_SETGROUND) == 0){
		payloadNumber = strtol(payload,0,16);
		Sistema.AltitudineTerra = payloadNumber;

	} else if (strcmp(opcode,CMD_OVRD_SETTIME) == 0){
		payloadNumber = strtoul(payload,0,16);
		Sistema.InizioMissione = payloadNumber;

	} else if (strcmp(opcode, CMD_RESET) == 0){
		//Not implemented
		
	} else if (strcmp(opcode, CMD_SLEEP) == 0){
		//Not implemented
		
	} else if (strcmp(opcode, CMD_WAKEUP) == 0){
		//Not implemented
		
	} else if (strcmp(opcode, CMD_SHUTDOWN) == 0){
		disarm_DisasterRecovery();
		
	} else if (strcmp(opcode, CMD_SETCHAN) == 0){
		payloadNumber = strtoul(payload,0,10);
		//Not implemented
		
	}

	Sistema.StatoPrecedente = STATE_INTERRUPT;
	Telemetria.AggiornaCampo(STATE_INTERRUPT, TLM_PREVIOUS_STATE);

	return;
};
