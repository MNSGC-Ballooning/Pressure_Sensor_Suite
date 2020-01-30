// Functions for each pressure sensor


// All output voltages are stepped down to 3.333V

// Transfer functions for all analog pressure sensors are provided in the data sheets...
// further derivations were required to separate out the pressure value variables

void getMPXData() {
  analogMPX = analogRead(MPX_PIN);
  voltageMPX = analogMPX * (3.333/8196);
  kpaMPX = 94.429*(voltageMPX/3.333) + 14.334;
  atmMPX = kpaMPX * KPA_TO_ATM;
}

void getSSC_MGData() {
  analogSSC_MG = analogRead(SSC_MG_PIN);
  voltageSSC_MG = analogSSC_MG * (3.333/8196);
  mbarSSC_MG = (voltageSSC_MG - 0.333) * (250/2.664);
  atmSSC_MG = mbarSSC_MG * MBAR_TO_ATM; 
}

void getSSC_PAData() {
  analogSSC_PA = analogRead(SSC_PA_PIN);
  voltageSSC_PA = analogSSC_PA * (3.333/8196);
  psiSSC_PA = (voltageSSC_PA - 0.333) * (15/2.664);
  atmSSC_PA = psiSSC_PA * PSI_TO_ATM; 
}


void getDataStrings() {
  dataMPX = String(analogMPX) + ", " + String(voltageMPX, 4) + ", " + String(kpaMPX, 4) + ", " + String(atmMPX, 4);
  dataSSC_MG = String(analogSSC_MG) + ", " + String(voltageSSC_MG, 4) + ", " + String(mbarSSC_MG, 4) + ", " + String(atmSSC_MG, 4);
  dataSSC_PA = String(analogSSC_PA) + ", " + String(voltageSSC_PA, 4) + ", " + String(psiSSC_PA, 4) + ", " + String(atmSSC_PA, 4);
  dataString = String(millis()) + ", " + dataMPX + ", " + dataSSC_MG + ", " + dataSSC_PA;
}
