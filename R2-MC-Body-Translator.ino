#include <SoftwareSerial.h>        // Durch diesen Include können wir die Funktionen
// der SoftwareSerial Bibliothek nutzen.
SoftwareSerial FromDuino(10,11);     //  Pin D10 ist RX, Pin D11 ist TX.// Senden an Marcduino Boards
SoftwareSerial ToDuinoDOME(8,9);       //  Pin D8 ist RX, Pin D9 ist TX.// Senden an Marcduino Boards
SoftwareSerial ToDuinoBODY(7,6);       //  Pin D7 ist RX, Pin D6 ist TX.// Senden an Marcduino Boards


String cmd; //Consohlen Input
String data;
byte debug = false; //Debug function

void setup()
{
  // Zuerst initialisieren wir die serielle Schnittstelle des Arduino.
  Serial.begin(9600); // Monitor for debugging
  Serial.println("##### R2MainController 13.09.2020 #####");
  Serial.println("Comandos von RC - CoinTaster - Wfif Modul werde verarbeitet");
  Serial.println("INPUT:  RX = 10   TX = 11");
  
  Serial.println("OUTPUT DOME:  RX = 8   TX =9 ");

   Serial.println("OUTPUT BODY:  RX = 7   TX =6 ");
  
  // Dann initialisieren wir die serielle Schnittstelle der SoftwareSerial Bibliothek.
 FromDuino.begin(9600);
  //delay(500);
 ToDuinoDOME.begin(9600);
 
 ToDuinoBODY.begin(9600);

}


void parseCommand(String cmd) {

    if (cmd.startsWith("!")) {
     
      data = cmd;
      data.remove(0,1);
      
      Serial.print("TO Command: ");
        Serial.println(data);
        ToDuinoBODY.print(data);
        ToDuinoBODY.print("\r");
        
      } else {
        ToDuinoDOME.print(cmd); ToDuinoDOME.print("\r");
      }
   
    if (cmd == ":CL00"){
      Serial.print("to Body"); 
      ToDuinoBODY.print(":CL00\r");
      }
    if (cmd == ":OP00"){ 
      Serial.print("to Body");
      ToDuinoBODY.print(":OP00\r");
      }
    
    
      
}
      

void loop()
{

  FromDuino.listen();
  
  if(FromDuino.available() > 0 )
    {      
       data = FromDuino.readStringUntil('\r');      
      if (data != "") {
        if (debug){
           // say what you got:
          Serial.print("I received from Input: ");
          Serial.println(data);
        }
          parseCommand(data);
          data = "";
          
          
      } // end data
    } // end serial


}
