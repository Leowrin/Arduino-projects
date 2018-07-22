/*A tester :  - Si l'inversion dans le if initial; nloop++ et power down fonctionne
              - si le delay      "           "    permet de baisser le dernier delay.

*/


#include <TimeLib.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <SD.h>
#include <SPI.h>
#include <LowPower.h>
#include <Wire.h>

//définition de l'appel de librairie File par logfile
File logfile;

//définition des variables
float temp;
String info;
byte nloop=0;



void setup() {

SD.begin(10);

}



void loop() {

  if(nloop<225){
    nloop++;
    delay(5);
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  else{

    //définition de l'appel de librairie tm par tm
    tmElements_t tm;

    if (RTC.read(tm)) {
    //définition des températures
    temp=analogRead(A0);
    temp=temp*(5.0 / 1023.0 * 100.0);

    //définition de la date + temp dans la variable info
    info=tm.Day;
    info+="/";
    info+=tm.Month;
    info+=" ";
    info+=tm.Hour;
    info+=":";
    info+=tm.Minute;
    info+=":";
    info+=tm.Second;
    //
    info+=",";
    info+=temp;

    //écriture sur carte SD
    logfile = SD.open("log.csv", FILE_WRITE);
    logfile.println(info);
    logfile.close();
    //delay de bon fonctionnement, problème sur l'écriture de la carte, le power down, arrivant trop vite sinon.
    delay(30);

    nloop=0;
    }

  }

}
