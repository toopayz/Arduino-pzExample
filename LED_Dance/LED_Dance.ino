
#define DDR_LED                 DDRC
#define PORT_LED                PORTC       //  led di posisi PC0 ~ PC7 = 8 buah LED
                                            //  Arduino UNO bisa di no pin 0 ~ 7
                                            //  PD0 ~ PD7 + PB0 ~ PB5
#define SET_AS_OUTPUT(DDRx)     DDRx   = 0xFF
#define ALL_LED_LOW(PORTx)      PORTx  = 0x00
#define ALL_LED_HIGH(PORTx)     PORTx  = 0xFF
#define LED_LOW(PORTx,n)        PORTx &= ~(1 << n) 
#define LED_HIGH(PORTx,n)       PORTx |=  (1 << n)

#define MAX_DUTYCYCLE           100

typedef enum {csNone=0, csPingPong, csToOut, csInOut, csLeft, csFadeInOut, csRider}mystate;

mystate LedDance;
int ledval=0, ledarr[8];

//----------------------------------------------------------  LED Function
void LED_LEFT(void)
{
  for (ledval=0; ledval<=7; ledval++)
  {
    ALL_LED_LOW(PORT_LED);
    LED_HIGH(PORT_LED, ledval);    
    delay(50);
  }
}

void LED_RIGHT(void)
{
  ledval = 8;
  while(ledval--)
  {
    ALL_LED_LOW(PORT_LED);
    LED_HIGH(PORT_LED, ledval);
    delay(50);
  }
}

void LED_OUT(void)
{
  int iA=0b00010000, iB=0b00001000;
  ledval = iA | iB;
  while(ledval!=0b10000001)
  {
    ledval = iA | iB;
    PORT_LED = ledval;
    delay(100);
    iA <<= 1;
    iB >>= 1;
  }
}

void LED_IN(void)
{
  int iA=0b10000000, iB=0b00000001;
  ledval = iA | iB;
  while(ledval!=0b00011000)
  {
    ledval = iA | iB;
    PORT_LED = ledval;
    delay(100);
    iA >>= 1;
    iB <<= 1;
  }
}

void LED_FADEIN(void)
{
  int dutyoff, dutyon;
  ledval = MAX_DUTYCYCLE;
  while(ledval--)
  {
    dutyon =  ledval;
    ALL_LED_LOW(PORT_LED);
    while(dutyon--)   delayMicroseconds(200);
    //-----------------------------------------
    dutyoff = MAX_DUTYCYCLE - ledval;
    ALL_LED_HIGH(PORT_LED);
    while(dutyoff--)  delayMicroseconds(200);
  }
}

void LED_FADEOUT(void)
{
  int dutyoff, dutyon;
  ledval = MAX_DUTYCYCLE;
  while(ledval--)
  {
    dutyon =  ledval;
    ALL_LED_HIGH(PORT_LED);
    while(dutyon--)   delayMicroseconds(200);
    //-----------------------------------------
    dutyoff = MAX_DUTYCYCLE - ledval;
    ALL_LED_LOW(PORT_LED);
    while(dutyoff--)  delayMicroseconds(200);
  }
}

//----------------------------------------------------------  Board Setup / Initialization
void setup() 
{
  // put your setup code here, to run once:
  SET_AS_OUTPUT(DDR_LED);
  ALL_LED_LOW(PORT_LED);
}

//----------------------------------------------------------  Running Application
void loop()
{
  // put your main code here, to run repeatedly:
  LED_FADEIN();
  LED_FADEOUT();
  LED_LEFT();
  LED_RIGHT();
  LED_OUT();
  LED_IN();
}

