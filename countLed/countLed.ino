#include <Servo.h> 
#define  encoderPinA  2   // Tương ứng chân DT trên Encoder:    right (labeled DT on our decoder, yellow wire)
#define encoderPos x
int a=6;

int quangtro = A5;

#define DongCoRung 3
#define QuanHut   9
#define DongCoBuoc1 5
#define DongCoBuoc2 6
#define DongCoBuoc3 7
#define DongCoBuoc4 8
Servo gServo;
int i;
int j;

volatile unsigned char x = 0; 
unsigned char lastReportedPos = 1;   
static boolean rotating=false;     
boolean A_set = false;   
//voi HoatDong()
//    {
//      
//    }

void setup() {
  gServo.attach(QuanHut); 
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(DongCoRung, OUTPUT);
  pinMode(QuanHut , OUTPUT);
  pinMode(DongCoBuoc1 , OUTPUT);
  pinMode(DongCoBuoc2 , OUTPUT);
  pinMode(DongCoBuoc3 , OUTPUT);
  pinMode(DongCoBuoc4 , OUTPUT);
// Chân encoder trên ngắt 0 (chân 2): encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  Serial.begin(9600);  // chuyển dữ liệu lên cổng Serial Port

  digitalWrite(DongCoRung, HIGH); 
  digitalWrite(QuanHut, HIGH);
  digitalWrite(DongCoBuoc1, LOW);  
  digitalWrite(DongCoBuoc2, LOW);
  digitalWrite(DongCoBuoc3, LOW);  
  digitalWrite(DongCoBuoc4, LOW); 

 delay(10);
gServo.write(90);
delay(10);
}
void loop() 
{
  rotating = true; 
  if (lastReportedPos != encoderPos)
  {
    Serial.print("So LED:");
    Serial.println(encoderPos, DEC);
    lastReportedPos = encoderPos;

  }

  int giatriQuangtro = analogRead(quangtro);// đọc giá trị quang trở
  if (giatriQuangtro >= 1000) {
    digitalWrite(2, HIGH); 
   } else {
      digitalWrite(2, LOW); 
   }

  
  Serial.println(giatriQuangtro); // Xuất giá trị ra Serial Monitor

 
 if(encoderPos ==2)
    
        {

          delay(10);
          gServo.write(0); 
          delay(1000);      
          for(i=0;i<5;i++)
          {

           //  digitalWrite(QuanHut, LOW);    
             digitalWrite(DongCoRung, HIGH);  
             delay(1000); 
           }        

             
           digitalWrite(DongCoRung, LOW);
           delay(1);
           for(j=0;j<127;j++)
           {   
         
             digitalWrite(DongCoBuoc1, LOW);  
             digitalWrite(DongCoBuoc2, HIGH); 
             delay(a); 
             digitalWrite(DongCoBuoc1, HIGH); 
             digitalWrite(DongCoBuoc2, LOW);  
             delay(a);
             digitalWrite(DongCoBuoc3, LOW);  
             digitalWrite(DongCoBuoc4, HIGH); 
             delay(a); 
             digitalWrite(DongCoBuoc3, HIGH);  
             digitalWrite(DongCoBuoc4, LOW); 
             delay(a); 

           }
           
           gServo.write(90);
           delay(1000);
           digitalWrite(DongCoRung, HIGH);
           encoderPos=0;
           delay(100); 
        }

    }
    
void doEncoderA(){
  if ( rotating ) 
   delay (1);
  if( digitalRead(encoderPinA) != A_set ) 
  { 
    A_set = !A_set;
    if ( A_set  )
    encoderPos += 1;
    rotating = false;  
    delay(10);
  }
}
