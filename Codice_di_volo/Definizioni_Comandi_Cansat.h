//M101

#pragma once
#ifndef CMD_H
#define CMD_H

//COMANDI STANDARD DISPONIBILI SOLO NEL PRELANCIO
#define CMD_RESET		"A1"
#define CMD_SLEEP		"A2"
#define CMD_WAKEUP		"A3"
#define CMD_SHUTDOWN	"A4"
#define CMD_SETCHAN		"A5" // + ONE CHAR [1-8]

//COMANDI DI OVERRIDE
#define CMD_OVRD_SETSTATE	"O1" // + ONE CHAR [0-6]
#define CMD_OVRD_PARACHUTE	"O2"
#define CMD_OVRD_SETGROUND	"O3" // + TWO CHARS, HEXADECIMAL ENCODING (SEE https://stackoverflow.com/questions/3464194/how-can-i-convert-an-integer-to-a-hexadecimal-string-in-c)
#define CMD_OVRD_SETTIME	"O4" // + TWO CHARS, HEXADECIMAL ENCODING (SEE https://stackoverflow.com/questions/3464194/how-can-i-convert-an-integer-to-a-hexadecimal-string-in-c)

#endif
