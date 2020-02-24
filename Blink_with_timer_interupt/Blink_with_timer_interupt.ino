/*
  Kedap-kedip LED / LED Blink
  dengan menggunakan intterupsi timer atau tanpa menggunakan fungsi delay()
  alternatif lain selain fungsi millis().
  Sangat-sangat di rekomendasikan memahami cara kerja interupsi.

  Gunakan "CodeVision Wizzard", linkdonwload :
  http://www.hpinfotech.ro/cvavr-download.html
  Download dan install yang "Evaluation" saja
  Untuk menggenerate nilai register-register interupt
  Lihat di tutorial gambar.
 */

#define SET_AS_OUTPUT(DDRn,x)   DDRn  |=  (1 << x)
#define SET_TOGGLE(PORTn,x)     PORTn ^=  (1 << x)

const int ledPin =  LED_BUILTIN;// the number of the LED pin

int cnt_500mS;
int ledState = LOW;             // ledState used to set the LED

//----------------------------------------------------------  Board Setup / Initialization
void setup() 
{
  //SET_AS_OUTPUT(DDRB, 5);   //  Led indikator arduino Nano di pin 13 = PortB.5
  pinMode(13, OUTPUT);
  cnt_500mS=0;
  //------------------------------------------- Nilai-nilai interupsi timer 1  
  // Timer/Counter 1 initialization
  // Clock source: System Clock
  // Clock value: 62.500 kHz
  // Mode: Normal top=0xFFFF
  // OC1A output: Disconnected
  // OC1B output: Disconnected
  // Noise Canceler: Off
  // Input Capture on Falling Edge
  // Timer Period: 50.08 ms
  // Timer1 Overflow Interrupt: On
  // Input Capture Interrupt: Off
  // Compare A Match Interrupt: Off
  // Compare B Match Interrupt: Off
  TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
  TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);
  TCNT1H=0xF3;
  TCNT1L=0xC6;
  ICR1H=0x00;
  ICR1L=0x00;
  OCR1AH=0x00;
  OCR1AL=0x00;
  OCR1BH=0x00;
  OCR1BL=0x00;
  
  // Timer/Counter 1 Interrupt(s) initialization
  TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (1<<TOIE1);
  //  Lihat tutorial CodeWizard AVR untuk nilai interupsi timer
  sei();      //  global interupt enable
}

//----------------------------------------------------------  Running Application
void loop()
{
  //-----------------------------------   50 mS x 10 = 500 mS
  if (cnt_500mS >= 10)    //  lebih aman pakai >= daripada ==
  {
    cnt_500mS = 0;        //  jangan lupa di "Reset" nilainya
    //------------------------  the myNinja way :D
    SET_TOGGLE(PORTB, 5);    
    //------------------------  the arduino way
  /*if (ledState == LOW)  ledState = HIGH;
          else            ledState = LOW;
    digitalWrite(ledPin, ledState);
    //*/
  }
}

ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
  TCNT1H=0xF3;
  TCNT1L=0xC6;  //  reset nilai timer (Lihat tutorial gambar)
  cnt_500mS++;
  //cnt_led1++;     //  misal ada led1  800 mS
  //cnt_led2++;     //  misal ada led2  250 mS
  //cnt_apalah++;   //  misal ada lainnya
}
