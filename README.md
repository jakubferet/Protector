# Protector
Security system made of ESP8266 controlled via Nette web application

Cíl: bezpečnostní zařízení s využitím Arduino UNO a modulu ESP8266
- LED displej vyzívá k zadání hesla pro aktivaci systému
- po zadání správného hesla se spustí odpočet do aktivace alarmu
- po skončení odpočtu začne ultrazvukový senzor snímat vzdálenost k protější stěně
  - pokud se vzdálenost změní, spustí se odpočet do spuštění alarmu a objeví se výzva k zadání hesla
    - pokud je zadáno správné heslo, alarm se vypne a je nutné znovu zadat heslo pro jeho aktivaci
    - pokud heslo zadáno není, spustí se alarm
      - sputí se bzučák
      - rozsvítí se LED
      - odešle se E-mail
      - na displeji se objeví možnost zadání hesla pro vypnutí alarmu
        - po zadání správného hesla se vypne bzučák, zhasne LED a je nutné znovu zadat heslo pro opětovnou aktivaci
- možnost ovládat zařízení přes aplikaci díky modulu 8266
  - zkrátit nebo prodloužit časy
  - změnit heslo
  - nastavit automatické spuštění na určitou dobu
  - vypnout nebo zapnout systém na dálku
  - atd.
