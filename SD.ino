// Tab for SD functions

void initSD(){
  pinMode(chipSelect, OUTPUT);                                          //initialize SD card
  
  while (!SD.begin(chipSelect)) {                                       //power LED will blink if no card is inserted
    Serial.println("No SD");
    SDCard = false;
  }
  SDCard = true;

  for (int i = 0; i < 100; i++) {                                       //Flight Log Name Cration
    Fname = String("Pres" + String(i / 10) + String(i % 10) + ".csv");
    if (!SD.exists(Fname.c_str())) {
      openFlightLog();
      break;
    }
  }
  
  Serial.println("Flight log created: " + Fname);

  String Fheader = "millis, analogMPX, voltageMPX, kpaMPX, atmMPX, analogSSC_MG, voltageSSC_MG, mbarSSC_MG, atmSSC_MG, ";
  Fheader += "analogSSC_PA, voltageSSC_PA, psiSSC_PA, atmSSC_PA";
  Flog.println(Fheader);
  Serial.println("File header added to SD...");

  closeFlightLog();
}


void printData() {

  // print data to serial monitor
  Serial.print("Millis Timing : \t\t\t\t");
  Serial.println(millis());
  Serial.print("MPX analog, voltage, kPa, ATM : \t\t");
  Serial.println(dataMPX);
  Serial.print("SSC_MG analog, voltage, mBar, ATM : \t\t");
  Serial.println(dataSSC_MG);
  Serial.print("SSC_PA analog, voltage, psi, ATM : \t\t");
  Serial.println(dataSSC_PA);
  Serial.print("\n\n\n");

  // print data to the SD card
  openFlightLog();
  delay(50);
  Flog.println(dataString);
  closeFlightLog();

}

void openFlightLog() {                                                  //Open flight log
  if (!flightLogOpen&&SDCard) {
    //add .c_str() next to Fname
    Flog = SD.open(Fname.c_str(), FILE_WRITE);
    flightLogOpen = true;
  }
  
}


void closeFlightLog() {                                                 //Close flight log
  if (flightLogOpen&&SDCard) {
    Flog.close();
    flightLogOpen = false;
  }
  
}
