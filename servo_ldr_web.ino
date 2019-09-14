#include <Servo.h> // include the servo library
#include "RTClib.h"
#define led_alarma 5


RTC_DS1307 rtc;
Servo servoMotor; 




char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int analogPin = A0; // Pin donde conectaremos la LDR
int analogValue = 0; // Variable que almacena el valor de la LDR
int servoPin = 2; // Pin de control del Servo
int value;
int offset =20;// set the correction offset value
int i;
int nocturno=6; // luz nocturna
void alarma ();
void voltaje();
void ldr();
int volt;
void Write_SDcard();
void setup() 

{
  
  pinMode(led_alarma, OUTPUT);
  
  pinMode(nocturno, OUTPUT);
  servoMotor.attach(servoPin); 
  while (!Serial); // for Leonardo/Micro/Zero
 
  Serial.begin(115200);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  if (! rtc.isrunning()) {
  Serial.println("RTC is NOT running!");
  // following line sets the RTC to the date & time this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
   //rtc.adjust(DateTime(2019, 8, 10, 21, 48, 0));
  }
 }
 
}


void loop()
{
  voltaje();
  ldr();
  alarma();
  
}

void alarma () {
  DateTime now = rtc.now();

  while (now.hour() == 7 && now.minute() == 38)
  {
    digitalWrite(led_alarma, HIGH);
    if(i<2)
     {
       servoMotor.write(0); // bajada de barrera
       delay(1000);
       servoMotor.write(90);
       delay(1000);
       servoMotor.write(180);
       delay(1000);
       i++;
     }
    else
     {
     break;
     }
   }
   digitalWrite(led_alarma, LOW);
  /* imprimir fecha */
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(1000);
}

void voltaje()
{
   volt = analogRead(A1);// read the input
   double voltage = map(volt,0,1023, 0, 2500) + offset;// map 0-1023 to 0-2500 and add correction offset
   voltage /=100;// divide by 100 to get the decimal values
   Serial.print("Voltage: ");
   Serial.print(voltage);//print the voltge
   Serial.println("V");
   delay(500);
  }
void ldr()
{
  analogValue = analogRead(analogPin); // lectura del valor de la LDR

  Serial.print("ldr=   ");
  Serial.println(analogValue); 

  if (analogValue<5)
  {
    digitalWrite(nocturno, HIGH);
    delay(1000);
    }
  else 
   digitalWrite(nocturno, LOW);
 
}

 
