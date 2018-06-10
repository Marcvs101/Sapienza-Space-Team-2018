#include "Utilita_Librerie.h"

bool	camera		= false;
int		camera_ctr	= 0;
bool	wind		= false;
int		wind_ctr	= 0;
bool	buzzer		= false;
int		buzzer_ctr	= 0;

char			TX_buffer[CMD_PROC_DISP_WIND+8];

float			GPSlat,GPSlon	= 0;
unsigned long	GPStempo		= 0;
long			GPSaltitude		= 0;
unsigned short	GPSsats			= 0;

float			Windspeed	= 0;
uint32_t		Freq		= 0;
char			canale		= 0;

//GPS stuff
TinyGPS GPS;
SoftwareSerial GPSserial(4,3);
bool newGPSData = false;

void setup() {
	//I2C SETUP
	Wire.begin(SLAVE_I2C);
	Wire.onReceive(EventoRicezione);
	Wire.onRequest(EventoRichiesta);
	//GPS
	GPSserial.begin(9600);
	Serial.begin(9600);
	//Serial.println("INIT");
	//CAMERA
	pinMode(PIN_CAMERA_PWR,OUTPUT);
	pinMode(PIN_CAMERA_MODE,OUTPUT);
	digitalWrite(PIN_CAMERA_PWR,LOW);
	digitalWrite(PIN_CAMERA_MODE,LOW);
	//BUZZER
	pinMode(PIN_BUZZER,OUTPUT);
	//WIND
	pinMode(PIN_WIND_PWR,OUTPUT);
	digitalWrite(PIN_WIND_PWR,LOW);
	//RADIO
	SPI.begin();
//	AD9911_init();

	//Setup I2C buffer
	TX_buffer[CMD_PROC_DISP_GPS_LON-1] = ',';
	TX_buffer[CMD_PROC_DISP_GPS_ALT-1] = ',';
	TX_buffer[CMD_PROC_DISP_GPS_SATS-1] = ',';
	TX_buffer[CMD_PROC_DISP_GPS_TIME-1] = ',';
	TX_buffer[CMD_PROC_DISP_WIND-1] = ',';
}

void bufferingDati(){
	cli();
	char buff[9];
	dtostrf((double) GPSlat, 3, 6, buff);
	strncpy(&(TX_buffer[CMD_PROC_DISP_GPS_LAT]),(const char*) buff,8);
	memset(buff,'\0',9);
	dtostrf((double) GPSlon, 3, 6, buff);
	strncpy(&(TX_buffer[CMD_PROC_DISP_GPS_LON]),(const char*) buff,8);
	memset(buff,'\0',9);
	ltoa(GPSaltitude, buff, 16);
	strncpy(&(TX_buffer[CMD_PROC_DISP_GPS_ALT]),(const char*) buff,4);
	memset(buff,'\0',9);
	itoa((unsigned int) GPSsats, buff, 16);
	strncpy(&(TX_buffer[CMD_PROC_DISP_GPS_SATS]),(const char*) buff,2);
	memset(buff,'\0',9);
	ultoa(GPStempo, buff, 16);
	strncpy(&(TX_buffer[CMD_PROC_DISP_GPS_TIME]),(const char*) buff,8);
	memset(buff,'\0',9);
	dtostrf((double) Windspeed, 3, 6, buff);
	strncpy(&(TX_buffer[CMD_PROC_DISP_WIND]),(const char*) buff,8);
	sei();
}

static void delayGPS(unsigned long ms){
	unsigned long start = millis();
	do {
		while (GPSserial.available()){ 
			if (GPS.encode(GPSserial.read())) { newGPSData = true; }
		}
	} while (millis() - start < ms);
}

void loop() {
	//Query GPS
	if (newGPSData){
		unsigned long dummy1, dummy2;
		// Get latitude and longitude
		GPS.f_get_position(&GPSlat, &GPSlon, &dummy1);
		// Get current time
		GPS.get_datetime(&dummy2, &GPStempo, &dummy1);
		// Get number of satellites
		GPSsats = GPS.satellites();
		//reset flag
		newGPSData = false;
	}

	unsigned long chars;
	unsigned short sent, fail;
	GPS.stats(&chars, &sent, &fail);
	//Serial.println("Read: " + String(chars) + " , recognized: " + String(sent) + " , fail: " + String(fail));

	//Handle Camera
	if (camera == true && camera_ctr < 8){
		switch (camera_ctr){
			case 0:{
				digitalWrite(PIN_CAMERA_PWR,HIGH);
				break;
			} case 3:{
				digitalWrite(PIN_CAMERA_PWR,LOW);
				break;
			} case 4:{
				digitalWrite(PIN_CAMERA_MODE,HIGH);
				break;
			} case 6:{
				digitalWrite(PIN_CAMERA_MODE,LOW);
				break;
			}
		}
		camera_ctr++;
	}

	//Handle Buzzer
	if (buzzer == true){
		//tone(PIN_BUZZER,1000,500);
		if (buzzer_ctr%2 == 0){
			digitalWrite(PIN_BUZZER,HIGH);
		} else {
			digitalWrite(PIN_BUZZER,LOW);
		}
		buzzer_ctr++;
	} else {
		digitalWrite(PIN_BUZZER,LOW);
	}
	
	//Handle Wind
	if (wind == true && wind_ctr <= 4){
		//Sensor heating
		wind_ctr++;
	} else if (wind == true && wind_ctr > 4){
		//Sensor functional
		Windspeed = pow(((((float) analogRead(PIN_WIND_OUT)) - 264.0)/ 108.817), 3.36814);

		//Handle Transmitter
		Freq = MISSIONE_FREQUENZA_BASE + (MISSIONE_FREQUENZA_STEP*canale) + (Windspeed*MISSIONE_FREQUENZA_UNIT);
//		AD9911_single_tone(Freq,0,0x3ff);
		
	}

	bufferingDati();
	//
	delayGPS(1000);
}

void EventoRicezione(int howMany) {	//Get data from master
	byte comando;
	if (Wire.available() > 0) {
		comando = Wire.read();
	}

	switch(comando){
		case CMD_PROC_STAGE:{
			//Servomotor is on master, may want to depower stuff
			
			break;
		} case CMD_PROC_CAMERA_ON:{
			camera_ctr = 0;
			camera = true;
			break;
		} case CMD_PROC_CAMERA_OFF:{
			camera_ctr = 0;
			camera = false;
			break;
		} case CMD_PROC_WIND_ON:{
			wind_ctr = 0;
			wind = true;
			break;
		} case CMD_PROC_WIND_OFF:{
			wind_ctr = 0;
			wind = false;
			break;
		} case CMD_PROC_CHANNEL:{
			if (Wire.available() > 0) {
				canale = Wire.read();
			}
			break;
		} case CMD_PROC_BUZZER_ON:{
			buzzer_ctr = 0;
			buzzer = true;
			break;
		} case CMD_PROC_BUZZER_OFF:{
			buzzer_ctr = 0;
			buzzer = false;
			break;
		}
	}

	//Svuota pipeline
	while (Wire.available() > 0) {
		comando = Wire.read();
	}
}

void EventoRichiesta(int howMany) {	//Send data to master
	int written = 0;
	for (int i=0; i<CMD_PROC_DISP_WIND+4; i++){
		if (TX_buffer[i] != '\0'){
			Wire.write(TX_buffer[i]);
		}
	}
}
