#ifndef MAIN
#define MAIN

#include "Utilita_Librerie.h"

STR_Sistema		Sistema;
STR_Telemetria	Telemetria;
STR_Sensori		Sensori;

void setup() {
	//UART
	Serial.begin(9600);

	//I2C
	Wire.begin();

	//SPI
	SPI.begin();

	//SERVO
	pinMode(PIN_SERVO,OUTPUT);
	
	//IMU
	//Sensori.IMU.MPU9250SelfTest(Sensori.IMU.selfTest);
	// Calibrate gyro and accelerometers, load biases in bias registers
	Sensori.IMU.calibrateMPU9250(Sensori.IMU.gyroBias, Sensori.IMU.accelBias);
	// Initialize device for active mode read of acclerometer, gyroscope, and temperature
	Sensori.IMU.initMPU9250();
	// Get sensor resolutions, only need to do this once
	Sensori.IMU.getAres();
	Sensori.IMU.getGres();

	//BMP SDO ALTO
	Sensori.BMP.begin();
	Sistema.Altitudine = Sensori.BMP.readAltitude(1013.25);

	//Memory
	Sensori.Flash.setup(PIN_MEM_CS,PIN_MEM_RESET,PIN_MEM_PROTECT); //(csPin, resetPin, wpPin);
	//delay(10);
	Sensori.Flash.begin();
	
	//Controllo disaster
	if ((char) EEPROM.read(0) == '1'){	//FLAG in memoria settato a 1
		do_DisasterRecovery();
		return;							//Non proseguire ed entra nel loop
	}

	//Ottieni e inizializza i dati fondamentali
	//while (Coprocessore_Dati::GPSsats == 0){
		Coprocessore::ottieniDati();
	//}
	Sistema.AltitudineTerra = Sistema.Altitudine;
	Sistema.InizioMissione = Coprocessore_Dati::GPStempo;
	
	//Aggiorna lo stato software
	Sistema.StatoAttuale = STATE_PRELAUNCH;
	Sistema.StatoPrecedente = STATE_INIT;
	Telemetria.AggiornaCampo(STATE_PRELAUNCH, TLM_SOFTWARE_STATE);
	Telemetria.AggiornaCampo(STATE_INIT, TLM_PREVIOUS_STATE);

	//Arma il disaster recovery
	update_DisasterRecovery();
	//arm_DisasterRecovery();
	//
	return;
}

void loop() {
	//Switcha sugli stati
	switch (Sistema.StatoAttuale){
		case STATE_PRELAUNCH:{
			do_PrelancioAscesa();
			break;
		} case STATE_ASCENT:{
			do_PrelancioAscesa();
			break;
		} case STATE_HIGH_DESCENT:{
			do_DiscesaAlta();
			break;
		} case STATE_TRANSITION:{
			do_DiscesaAlta();
			break;
		} case STATE_LOW_DESCENT:{
			do_DiscesaBassa();
			break;
		} case STATE_LANDED:{
			do_DiscesaBassa();
			break;
		} case STATE_INTERRUPT:{
			do_InterruptHandler();
			break;
		} case STATE_DISASTER:{
			do_DisasterRecovery();
			break;
		} case STATE_HIBERNATION:{
			do_PrelancioAscesa();
			break;
		} default:{
			Sistema.StatoAttuale = STATE_HIGH_DESCENT;
			do_DiscesaAlta();
			break;
		}
	}
	
	//Aggiorna variabili fondamentali
	update_DisasterRecovery();
	return;
}

#endif
