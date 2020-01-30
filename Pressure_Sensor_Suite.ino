// Script to test out 4 different pressure sensors
// 1. MPX4100A
// 2. Honeywell SSCDRNN250MGAA5
// 3. Honeywell SSCSANN015PAAA5  

// include libraries
#include <SD.h>
#include <MS5611.h>


// define macros
#define MPX_PIN A20       // completely arbitrary
#define SSC_MG_PIN A16
#define SSC_PA_PIN A13

#define PSI_TO_ATM 0.068046
#define MBAR_TO_ATM 0.000986923
#define KPA_TO_ATM 0.00986923


// SD variables
const int chipSelect = BUILTIN_SDCARD;
String Fname;
File Flog;
boolean SDCard = true;
boolean flightLogOpen = false;
String dataString;

// MPX4100A variables
float analogMPX;                                                //Analog number given by sensor
float voltageMPX;                                               //Voltage calculated from analog number
float kpaMPX;                                                   //kPa calculated from voltage
float atmMPX;                                                   //ATM calculated from PSI
String dataMPX;

// For the two Honeywell pressure sensors...
// MG denotes gage pressure outputted in milliBars
// PA denotes absolute preesure outputted in PSI

// SSCDRNN250MGAA5 variables 
float analogSSC_MG;                                             //Analog number given by sensor
float voltageSSC_MG;                                            //Voltage calculated from analog number
float mbarSSC_MG;                                               //millibar calculated from voltage
float atmSSC_MG;                                                //ATM calculated from millibar
String dataSSC_MG;

// SSCSANN015PAAA5 variables
float analogSSC_PA;                                             //Analog output
float voltageSSC_PA;                                            //Voltage calculated
float psiSSC_PA;                                                //psi calculated from voltage transfer function
float atmSSC_PA;                                                //ATM calculated from psi
String dataSSC_PA;

void setup() {
  Serial.begin(9600);

  analogReadResolution(13);

  initSD();

  Serial.print("Setup completed...\n\n");
  
}

void loop() {
  getMPXData();
  getSSC_MGData();
  getSSC_PAData();
  
  getDataStrings();
  printData();

  delay(1000);

}
