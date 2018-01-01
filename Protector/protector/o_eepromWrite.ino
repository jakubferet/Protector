//function for saving values into EEPROM
void eepromWrite(){
  //set the EEPROM address to 0
  address = 0;
  //clear the EEPROM
  for (int i = 0; i < 512; i++){
    EEPROM.write(i, 0);
  }
  //write the length of the password into the EEPROM
  EEPROM.write(address,vel); 
  //divide the password into individual numbers and save them into the EEPROM
  for(int i=0;i<pass.length();i++){
    EEPROM.write(10+i,pass[i]); 
  }
  //store data to EEPROM 
  EEPROM.commit();     
}
