int fase=0;

void setup() {
  int datipresenti=0;
  //read sd
  if (datipresenti==1) {
    //é reset recupera i parametri di missione
    //prendi dati dai sensori
    //aggiorna fase
    delay(100);
  } else {
    //leggi sensori
    //settare parametri missione
    //test
  }
  return
}

void loop() {
  // put your main code here, to run repeatedly:
  //settare variabili
  switch(fase) {
    case 0: //fase0 lancio e ascesa
      //prendi dati dai sensori
      //manda telemetria
      //if (realt>20 && vspeed<0) {
        //fase=1
        //aggiorna dati su sd
      //}
      //else {
        //delay(1000)
        //}
      break;
    case 1: //fase1 discesa alto profilo
      //check override
      //if (override) {
        //gestisci errore
        //}
      //else {
        //prendi dati dai sensori
        //controlli di volo
        //if (telemetria){
          //manda telemetria
          //}
        //if (realt<300) {
          //rilascia scudo
          //apri paracadute
          //fase=2
          //aggiorna sd
          //}
          //}
      delay(100)
      break;
    case 2: //fase2 discesa basso profilo atterraggio
      //prendi dati dai sensori
      //manda telemetria
      delay(1000)
      break;  
  }
}
