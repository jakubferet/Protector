//function for reading values from EEPROM
String eepromRead(){
  pass="";
  //read the length of the password from the address 0 from the EEPROM
  vel = EEPROM.read(0);
  //read the password from the EEPROM
  for(int i=0;i<vel;i++) {
    pass = pass + char(EEPROM.read(10+i));   
  }
  //if the EEPROM is full, set the address to 0  
  if (address == 512){
    address = 0;
  }
  return pass;
}
