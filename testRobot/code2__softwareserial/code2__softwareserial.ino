/*
SoftwareSerialParser
(based on SoftwareSerialExample.ino)

Description: Software to parse serial data from ESP8266 and
move motors controlled by L298N motor drive.

Author: Lucio A. Rocha
Last update: 12/03/2017

 */
#include <SoftwareSerial.h>

int IN3 = 8; //IN3 motor = pino no arduino
int IN4 = 7;
//int ENB = 6; // ENB eh o pino de controle de velocidade no motor

int IN1 = 5; //IN1 motor = pino no arduino
int IN2 = 4;
//int ENA = 3; // ENA eh o pino de controle de velocidade no motor

int TIME_MOVE=2000; //Tempo de cada movimento

SoftwareSerial mySerial(0, 1); // RX, TX

void setup() {

 // pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  //pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("SoftwareSerialParser Started!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}


void moveMotor(char c){
   
   Serial.println(c);

   switch (c){
    //Up
    case '1': 
      //Prepara a saida do motor
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      //Prepara a saida do motor
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      //Move
     // analogWrite(ENA, 255);
      // analogWrite(ENB, 255);
      delay(TIME_MOVE);  
      //Desliga o motor e espera
      //analogWrite(ENA, 0);
      //analogWrite(ENB, 0);      
      break;
    //LeftUp
    case '2':       
      //Prepara a saida do motor
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      //Move      
      //analogWrite(ENB, 255);
      delay(TIME_MOVE);  
      //Desliga o motor e espera      
      //analogWrite(ENB, 0);      
      break;      
    //RightUp
    case '3':       
      //Prepara a saida do motor
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);      
      //Move
      //analogWrite(ENA, 255);      
      delay(TIME_MOVE);  
      //Desliga o motor e espera
      //analogWrite(ENA, 0);
      break;
    //LeftDown
    case '4':       
      //Prepara a saida do motor
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      //Move      
      //analogWrite(ENB, 255);
      delay(TIME_MOVE);  
      //Desliga o motor e espera      
      //analogWrite(ENB, 0);      
      break;        
      //RightDown
    case '5':       
      //Prepara a saida do motor
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);      
      //Move
      //analogWrite(ENA, 255);      
      delay(TIME_MOVE);  
      //Desliga o motor e espera
      //analogWrite(ENA, 0);
      break;
      //Down
    case '6':                
//Prepara a saida do motor
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      //Prepara a saida do motor
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      //Move
      // analogWrite(ENA, 255);
      // analogWrite(ENB, 255);
      delay(TIME_MOVE);  
      //Desliga o motor e espera
      // analogWrite(ENA, 0);
      // analogWrite(ENB, 0);      
      break;
  //Stop
    case '7':                
      //Desliga o motor e espera
      // analogWrite(ENA, 0);
      // analogWrite(ENB, 0);      
      break;      
    default:
      break;
   }//end switch
 
}


void parseMove(String response){
      Serial.print("[");
      String movement="";
      int i=0;
      char c = response[i];
      while (i<4){ //Take first 5 chars from readings of ESP8266 line
        c = response[i];
        movement+=c;
        Serial.print(c);
        i=i+1;
     }
    //Takes on more char to identify the number of movement
    c = response[i];
    if (movement=="SETM"){     
      movement+=c;
      Serial.println("\n===========================================");      
      Serial.println(movement);
      Serial.println(c);

      //c is the number of movement
      moveMotor(c);

      Serial.println("-------------------------------------------");  
    }
     Serial.print("]");
}  

void loop() { // run over and over
  String response = "";
  bool achou=false;  
  while (mySerial.available()) {
    response = mySerial.readStringUntil('\n');
    Serial.println(response);

    parseMove(response);
   
  }
}
