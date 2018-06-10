//FASE DI DISCESA AD ALTE PRESTAZIONI
//Responsabili: Marco

//Direttive di preprocessore
#include "Fase_DiscesaAlta.h"

//Funzione principale
void do_DiscesaAlta(){
	//Dichiarazione variabili
	long vecchiaAltitudine = Sistema.Altitudine;
	
	//Logica di volo
	
	//Raccolta dati sensori
	
	//Note sulla telemetria
	//	TEAM_ID, PACKET_COUNT, SOFTWARE_STATE, PREVIOUS_STATE sono prefillati dalla libreria Telemetria
	//	MISSION_TIME, GPS_TIME, GPS_LATITUDE, GPS_LONGITUDE, GPS_ALTITUDE, GPS_SATS sono presi dal GPS
	//	TILT_X, TILT_Y, TILT_Z sono presi dall'IMU
	//	ALT_SENSOR, PRESSURE, TEMP sono presi dal BMP
	//	VOLTAGE, WIND_SPEED sono presi per il culo
	//Fine note sulla telemetria

	//SLAVE -> GPS, Wind sensor
	Coprocessore::ottieniDati();
	
	//IMU
	// If intPin goes high, all data registers have new data
	// On interrupt, check if data ready interrupt
	if (Sensori.IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01){
		Sensori.IMU.readAccelData(Sensori.IMU.accelCount);// Read the x/y/z adc values

		// Now we'll calculate the accleration value into actual g's
		// This depends on scale being set
		Sensori.IMU.ax = (float)Sensori.IMU.accelCount[0] * Sensori.IMU.aRes; // - Sensori.IMU.accelBias[0];
		Sensori.IMU.ay = (float)Sensori.IMU.accelCount[1] * Sensori.IMU.aRes; // - Sensori.IMU.accelBias[1];
		Sensori.IMU.az = (float)Sensori.IMU.accelCount[2] * Sensori.IMU.aRes; // - Sensori.IMU.accelBias[2];

		Sensori.IMU.readGyroData(Sensori.IMU.gyroCount);// Read the x/y/z adc values

		// Calculate the gyro value into actual degrees per second
		// This depends on scale being set
		Sensori.IMU.gx = (float)Sensori.IMU.gyroCount[0] * Sensori.IMU.gRes;
		Sensori.IMU.gy = (float)Sensori.IMU.gyroCount[1] * Sensori.IMU.gRes;
		Sensori.IMU.gz = (float)Sensori.IMU.gyroCount[2] * Sensori.IMU.gRes;
		
		//Calcola gli angoli
		float r,t,p;
		r = sqrt(Sensori.IMU.ax*Sensori.IMU.ax + Sensori.IMU.ay*Sensori.IMU.ay + Sensori.IMU.az*Sensori.IMU.az);
		t = atan2(Sensori.IMU.ay, Sensori.IMU.ax);
		p = acos(Sensori.IMU.az / r);

		//fai update della telemetria
		Telemetria.AggiornaCampo(t*((float)360/(float)(2*PI)), TLM_TILT_X);//fare test una volta montato l'IMU
		Telemetria.AggiornaCampo(p*((float)360/(float)(2*PI)), TLM_TILT_Y);
		Telemetria.AggiornaCampo(Sensori.IMU.gz, TLM_TILT_Z);
	}

	//BMP
	Telemetria.AggiornaCampo((long)Sensori.BMP.readTemperature(), TLM_TEMP);
	Telemetria.AggiornaCampo((long)Sensori.BMP.readPressure(), TLM_PRESSURE);
	Sistema.Altitudine = Sensori.BMP.readAltitude(1013.25);
	Telemetria.AggiornaCampo(Sistema.Altitudine, TLM_ALT_SENSOR);

	//Partitore di tensione
	Telemetria.AggiornaCampo(analogRead(PIN_BAT_VOLT) , TLM_VOLTAGE);
	
	//Invio Telemetria
	Telemetria.Invia();

	//Aggiornamento disaster recovery
	update_DisasterRecovery();

	//Inizio del ciclo veloce
	for (int i=0;i<10;i++){
		//Controllo segnali radio
		if (Serial.available()){
			do_InterruptHandler();
			return;
		}
		
		//Altitudine necessaria al controllo
		Sistema.Altitudine = Sensori.BMP.readAltitude(1013.25);
		
		//Controllo condizioni di uscita
		if ((Sistema.Altitudine - (Sistema.Altitudine - vecchiaAltitudine)*2 - Sistema.AltitudineTerra < MISSIONE_APERTURA_PARACADUTE) && (Sistema.Altitudine - vecchiaAltitudine) < 0){
			
			//Esegui lo staging
			tone(PIN_SERVO,1000,350);
			Coprocessore::eseguiComando(CMD_PROC_STAGE);
			
			//Cambio fase
			Sistema.StatoPrecedente = STATE_TRANSITION;
			Sistema.StatoAttuale = STATE_LOW_DESCENT;
		}
		
		delay(100);	// 0.1 secondi
	}
	//Fine ciclo veloce

	//Aggiorna telemetria per lo stato
	Sistema.StatoPrecedente = Sistema.StatoAttuale;
	Telemetria.AggiornaCampo(Sistema.StatoAttuale,TLM_PREVIOUS_STATE);
	
	return;
};
