//M101

#include "Modulo_Telemetria.h"

/* NOTE SULLA TELEMETRIA
 * 
 * 1 Byte	- <SOFTWARE_STATE>,<PREVIOUS_STATE>
 * 2 Bytes	- <TEMP>,<VOLTAGE>,<WIND_SPEED>,<GPS_SATS>
 * 4 Bytes	- <TEAM_ID>,<MISSION_TIME>,<PACKET_COUNT>,<ALT_SENSOR>,<PRESSURE>,<TEMPERATURE>,<GPS_TIME>
 * 8 Bytes	- <GPS_LATITUDE>,<GPS_LONGITUDE>,<GPS_ALTITUDE>,<TILT_X>,<TILT_Y>,<TILT_Z>
 */

//Funzioni
STR_Telemetria::STR_Telemetria(){
	memset(this->buffer,'0',TLM_DISP_WIND_SPEED+10);
	this->buffer[TLM_DISP_MISSION_TIME-1] = ',';
	this->buffer[TLM_DISP_PACKET_COUNT-1] = ',';
	this->buffer[TLM_DISP_ALT_SENSOR-1] = ',';
	this->buffer[TLM_DISP_PRESSURE-1] = ',';
	this->buffer[TLM_DISP_TEMP-1] = ',';
	this->buffer[TLM_DISP_VOLTAGE-1] = ',';
	this->buffer[TLM_DISP_GPS_TIME-1] = ',';
	this->buffer[TLM_DISP_GPS_LATITUDE-1] = ',';
	this->buffer[TLM_DISP_GPS_LONGITUDE-1] = ',';
	this->buffer[TLM_DISP_GPS_ALTITUDE-1] = ',';
	this->buffer[TLM_DISP_GPS_SATS-1] = ',';
	this->buffer[TLM_DISP_TILT_X-1] = ',';
	this->buffer[TLM_DISP_TILT_Y-1] = ',';
	this->buffer[TLM_DISP_TILT_Z-1] = ',';
	this->buffer[TLM_DISP_SOFTWARE_STATE-1] = ',';
	this->buffer[TLM_DISP_PREVIOUS_STATE-1] = ',';
	this->buffer[TLM_DISP_WIND_SPEED-1] = ',';
	this->buffer[TLM_DISP_WIND_SPEED+8] = '\n';
	this->buffer[TLM_DISP_WIND_SPEED+9] = '\r';
	//
	strncpy(&(this->buffer[TLM_DISP_TEAM_ID]),"2978",4);
	//
	this->FlashPage = 0;
	this->FlashBuffer = 0;
	this->FlashOffset = 0;
}

void STR_Telemetria::AggiornaCampo(int valore, int campo){
	switch(campo){
		case TLM_VOLTAGE:{		//2B
			char buff[5];
			itoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_VOLTAGE]),(const char*) &(buff),2);
		break;}
		case TLM_GPS_SATS:{		//2B
			char buff[5];
			itoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_GPS_SATS]),(const char*) &(buff),2);
		break;}
		case TLM_SOFTWARE_STATE:{//1B
			this->buffer[TLM_DISP_SOFTWARE_STATE] = (char) valore + '0';
		break;}
		case TLM_PREVIOUS_STATE:{//1B
			this->buffer[TLM_DISP_PREVIOUS_STATE] = (byte) valore + '0';
		break;}
	}
}

void STR_Telemetria::AggiornaCampo(unsigned int valore, int campo){
	switch(campo){
		case TLM_VOLTAGE:{		//2B
			char buff[5];
			itoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_VOLTAGE]),(const char*) &(buff),2);
		break;}
		case TLM_GPS_SATS:{		//2B
			char buff[5];
			itoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_GPS_SATS]),(const char*) &(buff),2);
		break;}
		case TLM_SOFTWARE_STATE:{//1B
			this->buffer[TLM_DISP_SOFTWARE_STATE] = (byte) valore + '0';
		break;}
		case TLM_PREVIOUS_STATE:{//1B
			this->buffer[TLM_DISP_PREVIOUS_STATE] = (byte) valore + '0';
		break;}
	}
}

void STR_Telemetria::AggiornaCampo(long valore, int campo){
	switch(campo){
		case TLM_TEAM_ID:{		//4B
			char buff[5];
			ltoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_TEAM_ID]),(const char*) buff,4);
		break;}
		case TLM_MISSION_TIME:{	//4B
			char buff[5];
			ltoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_MISSION_TIME]),(const char*) buff,4);
		break;}
		case TLM_PACKET_COUNT:{	//4B
			char buff[5];
			ltoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_PACKET_COUNT]),(const char*) buff,4);
		break;}
		case TLM_ALT_SENSOR:{	//4B
			char buff[5];
			ltoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_ALT_SENSOR]),(const char*) buff,4);
		break;}
		case TLM_PRESSURE:{		//4B
			char buff[5];
			ltoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_PRESSURE]),(const char*) buff,4);
		break;}
		case TLM_TEMP:{			//4B
			char buff[5];
			ltoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_TEMP]),(const char*) buff,4);
		break;}
		case TLM_GPS_TIME:{		//4B
			char buff[5];
			ultoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_GPS_TIME]),(const char*) buff,4);
		break;}
		case TLM_GPS_ALTITUDE:{	//4B
			char buff[5];
			ltoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_GPS_ALTITUDE]),(const char*) buff,4);
		break;}
	}
}

void STR_Telemetria::AggiornaCampo(unsigned long valore, int campo){
	switch(campo){
		case TLM_TEAM_ID:{		//4B
			char buff[5];
			ultoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_TEAM_ID]),(const char*) buff,4);
		break;}
		case TLM_MISSION_TIME:{	//4B
			char buff[9];
			ultoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_MISSION_TIME]),(const char*) buff,8);
		break;}
		case TLM_PACKET_COUNT:{	//4B
			char buff[5];
			ultoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_PACKET_COUNT]),(const char*) buff,4);
		break;}
		case TLM_ALT_SENSOR:{	//4B
			char buff[5];
			ultoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_ALT_SENSOR]),(const char*) buff,4);
		break;}
		case TLM_PRESSURE:{		//4B
			char buff[5];
			ultoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_PRESSURE]),(const char*) buff,4);
		break;}
		case TLM_TEMP:{			//4B
			char buff[5];
			ultoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_TEMP]),(const char*) buff,4);
		break;}
		case TLM_GPS_TIME:{		//4B
			char buff[9];
			ultoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_GPS_TIME]),(const char*) buff,8);
		break;}
		case TLM_GPS_ALTITUDE:{	//4B
			char buff[5];
			ultoa(valore, buff,10);
			strncpy(&(this->buffer[TLM_DISP_GPS_ALTITUDE]),(const char*) buff,4);
		break;}
	}
}

void STR_Telemetria::AggiornaCampo(float valore, int campo){
	switch(campo){
		case TLM_GPS_LATITUDE:{	//8B
			char buff[9];
			dtostrf((double) valore, 3, 4, buff);  //3 is mininum width, 4 is precision
			strncpy(&(this->buffer[TLM_DISP_GPS_LATITUDE]),(const char*) buff,8);
		break;}
		case TLM_GPS_LONGITUDE:{//8B
			char buff[9];
			dtostrf((double) valore, 3, 4, buff);  //3 is mininum width, 4 is precision
			strncpy(&(this->buffer[TLM_DISP_GPS_LONGITUDE]),(const char*) buff,8);
		break;}
		case TLM_TILT_X:{		//8B
			char buff[9];
			dtostrf((double) valore, 3, 4, buff);  //3 is mininum width, 4 is precision
			strncpy(&(this->buffer[TLM_DISP_TILT_X]),(const char*) buff,8);
		break;}
		case TLM_TILT_Y:{		//8B
			char buff[9];
			dtostrf((double) valore, 3, 4, buff);  //3 is mininum width, 4 is precision
			strncpy(&(this->buffer[TLM_DISP_TILT_Y]),(const char*) buff,8);
		break;}
		case TLM_TILT_Z:{		//8B
			char buff[9];
			dtostrf((double) valore, 3, 4, buff);  //3 is mininum width, 4 is precision
			strncpy(&(this->buffer[TLM_DISP_TILT_Z]),(const char*) buff,8);
		break;}
		case TLM_WIND_SPEED:{	//8B
			char buff[9];
			dtostrf((double) valore, 3, 4, buff);
			strncpy(&(this->buffer[TLM_DISP_WIND_SPEED]),(const char*) buff,8);
		break;}
	}
}

void STR_Telemetria::Invia(){
/*	//Memoria
	Sensori.Flash.bufferWrite(this->FlashBuffer, this->FlashOffset);	//write on buffer
	for (int i=0; i<TLM_DISP_WIND_SPEED+6; i++){
		if (this->buffer[i] != '\0'){
			if (this->FlashOffset >= DF_45DB161_PAGESIZE){
				Sensori.Flash.bufferToPage(this->FlashBuffer, this->FlashPage);
				this->FlashPage++;
				if (this->FlashBuffer == 0) this->FlashBuffer = 1;
				else this->FlashBuffer = 0;
				this->FlashOffset = 0;
				Sensori.Flash.bufferWrite(this->FlashBuffer, this->FlashOffset);
			}
			SPI.transfer(this->buffer[i]);
			this->FlashOffset++;
		}
	}
	Sensori.Flash.bufferToPage(this->FlashBuffer, this->FlashPage);		// Transfer buffer 1 to page 7
*/
	//Radio
	for (int i=0; i<TLM_DISP_WIND_SPEED+10; i++){
		if (this->buffer[i] != '\0'){
			Serial.write(this->buffer[i]);
		}
	}

	Sistema.NumeroPacchetti++;
	this->AggiornaCampo(Sistema.NumeroPacchetti, TLM_PACKET_COUNT);
	this->AggiornaCampo(Sistema.StatoAttuale, TLM_SOFTWARE_STATE);
	
}
