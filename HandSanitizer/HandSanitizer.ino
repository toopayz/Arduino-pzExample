#include <HCSR04.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

UltraSonicDistanceSensor SensorTangan(A15, A14);    //  trig=A15  Echo=A14  
UltraSonicDistanceSensor SensorKiri  (A13, A12);    //  trig=A13  Echo=A12  
UltraSonicDistanceSensor SensorKanan (A11, A10);    //  trig=A11  Echo=A10  
//atau   
//UltraSonicDistanceSensor SensorTangan(A15,A14), SensorKiri (A13,A12), SensorKanan(A11,A10);

int JarakTangan, KiriCm, KananCm;

void setup ()
{
    Serial.begin(9600);   // We initialize serial connection so that we could print values from sensor.
    myservo.attach(9);    // attaches the servo on pin 9 to the servo object
}

void loop ()
{ //--------------------------------------------------------  Baca semua sensor ultrasonic
  delay(1000);
  JarakTangan = SensorTangan.measureDistanceCm();
  KiriCm      = SensorKiri.measureDistanceCm();   // siapa tau pakai sensor tambahan
  KananCm     = SensorKanan.measureDistanceCm();  // siapa tau pakai sensor tambahan
  //--------------------------------------------------------  Tampilkan
  Serial.println(String("A: ")+JarakTangan+String(" Cm"));
  Serial.println(String("B: ")+KiriCm     +String(" Cm"));
  Serial.println(String("C: ")+KananCm    +String(" Cm"));
  //--------------------------------------------------------  If then sensor
  if (JarakTangan>=3 && JarakTangan<=10)  // sensor kadang baca -1 jadi data di filter 3~10 Cm
  {
    Serial.println("PRESSED..."); 
    myservo.write(90);  //  PRESS 90 derajat tergantung mekanik desain.
    delay(2000);
    myservo.write(0);   //  RELEASE
    Serial.println("RELEASED..."); 
    while(JarakTangan<=10)
    {
      // tunggu sampai tangan menjauh biar tidak ngelock...
      JarakTangan = SensorTangan.measureDistanceCm();
      delay(200);
    }
    Serial.println("NEXT Please...^^..."); 
  }
  //--------------------------------------------------------  hanya tanda 1 siklus
  Serial.println("-----------------------"); 
}


