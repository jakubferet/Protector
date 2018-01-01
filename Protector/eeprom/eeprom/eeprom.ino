#include <EEPROM.h>
 
// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;
 
void setup()
{
  Serial.begin(115200);
  EEPROM.begin(512);  //Initialize EEPROM

  //clear EEPROM
  for (int i = 0; i < 512; i++){
    EEPROM.write(i, 0);
  }
 
  //Write string to eeprom
  String ahoj = "ahoj";
  for(int i=0;i<ahoj.length();i++) //loop upto string lenght www.length() returns length of string
  {
    EEPROM.write(0x0F+i,ahoj[i]); //Write one by one with starting address of 0x0F
  }
  EEPROM.commit();    //Store data to EEPROM

  ahoj="";
  
  for(int i=0;i<20;i++) {
    ahoj = ahoj + char(EEPROM.read(0x0F+i)); //Read one by one with starting address of 0x0F    
  }  
 
  Serial.print(ahoj);
}
 
void loop()
{
  //We dont have anything in loop as EEPROM writing is done only once
  delay(10);   
}
