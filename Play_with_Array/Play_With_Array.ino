#include <SPI.h>

//  array 1 dimensi bernilai biner..
//  Klo biner berurutan tidak perlu dibuat begini karena biner-nya = desimalnya..
//  Sengaja di tulis urut biar mudah dilihat siapa tau mau di isi dengan biner yang random..
//  Dalami konsepnya biar implementasinya bisa kemana-mana
const byte dtbiner[] = {
  0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00001000, 0b00001001, 0b00001010, 0b00001011, 0b00001100, 0b00001101, 0b00001110, 0b00001111, \
  0b00010000, 0b00010001, 0b00010010, 0b00010011, 0b00010100, 0b00010101, 0b00010110, 0b00010111, 0b00011000, 0b00011001, 0b00011010, 0b00011011, 0b00011100, 0b00011101, 0b00011110, 0b00011111, \
  0b00100000, 0b00100001, 0b00100010, 0b00100011, 0b00100100, 0b00100101, 0b00100110, 0b00100111, 0b00101000, 0b00101001, 0b00101010, 0b00101011, 0b00101100, 0b00101101, 0b00101110, 0b00101111, \
  0b00110000, 0b00110001, 0b00110010, 0b00110011, 0b00110100, 0b00110101, 0b00110110, 0b00110111, 0b00111000, 0b00111001, 0b00111010, 0b00111011, 0b00111100, 0b00111101, 0b00111110, 0b00111111, \
  0b01000000, 0b01000001, 0b01000010, 0b01000011, 0b01000100, 0b01000101, 0b01000110, 0b01000111, 0b01001000, 0b01001001, 0b01001010, 0b01001011, 0b01001100, 0b01001101, 0b01001110, 0b01001111, \
  0b01010000, 0b01010001, 0b01010010, 0b01010011, 0b01010100, 0b01010101, 0b01010110, 0b01010111, 0b01011000, 0b01011001, 0b01011010, 0b01011011, 0b01011100, 0b01011101, 0b01011110, 0b01011111, \
  0b01100000, 0b01100001, 0b01100010, 0b01100011, 0b01100100, 0b01100101, 0b01100110, 0b01100111, 0b01101000, 0b01101001, 0b01101010, 0b01101011, 0b01101100, 0b01101101, 0b01101110, 0b01101111
  };

//  array 2 dimensi referensi nilai berkaitan dengan array dtbiner[]
//  Nilai High LOW atur sesuai kebutuhan
const unsigned char outHiLow[][8] = {
  {HIGH, HIGH,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW}, \
  { LOW, HIGH, HIGH,  LOW,  LOW,  LOW,  LOW,  LOW}, \
  {HIGH, HIGH,  LOW, HIGH, HIGH,  LOW,  LOW, HIGH}, \
  {HIGH, HIGH, HIGH,  LOW,  LOW, HIGH, HIGH, HIGH}, \
  {HIGH,  LOW, HIGH, HIGH, HIGH, HIGH,  LOW, HIGH}, \
  {HIGH, HIGH, HIGH,  LOW,  LOW, HIGH, HIGH, HIGH}, \
  { LOW,  LOW,  LOW,  LOW, HIGH, HIGH, HIGH, HIGH}, \
  {HIGH, HIGH,  LOW,  LOW,  LOW,  LOW, HIGH, HIGH}, \
  {HIGH, HIGH, HIGH,  LOW,  LOW,  LOW,  LOW, HIGH}, \
  {HIGH, HIGH, HIGH, HIGH,  LOW,  LOW,  LOW, HIGH}, \
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, \
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, \
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, \
  {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}
  };

/*
  #include <myAnotherFile.h>
  variable dtbiner[] dan outHiLow[][]
  di atas harusnya di buat di file terpisah biar gak pusing dan enak editnya.
*/

const unsigned char ldr[7]  = { 3,  4,  5,  6,  8,  9, 10};       //  pin input
const unsigned char ot[8]   = {11, 12, 13, 14, 15, 16, 17, 18};   //  pin output
unsigned char vrbit[7], vrX;
byte          my8bit;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {}
  Serial.write("Application Begin.\r\n");         //Cek serial di terminal
  //------------------------------ jumlah array 7
  for (vrX=0; vrX<7; vrX++)
  {
    //pinMode(ldr1,INPUT);
    //digitalWrite(ldr1,HIGH);
    pinMode(ldr[vrX],INPUT_PULLUP);    // sama aja
  }
  //------------------------------ jumlah array 8
  //  klo jumlah arraynya sama dengan ldr[x]
  //  bisa dalam 1 for saja, tidak 2 seperti ini.
  //  di akalin harusnya bisa
  for (vrX=0; vrX<8; vrX++)
  {
    pinMode(ot[vrX],OUTPUT);
    digitalWrite(ot[vrX],LOW);
  }
}

void loop()
{
  delay(200);   //  delay loop(), posisi di atas ataupun di bawah sama saja.
                //  klo konstant enak taruh di atas biar bisa di edit sesukanya
                //  meskipun code tambah panjang.
  //------------------------------ Baca input
  my8bit = 0;
  for (vrX=0; vrX<7; vrX++)
  {
    vrbit[vrX] = digitalRead(ldr[vrX]);
    my8bit    |= vrbit[vrX] << vrX;     //  nilai input 1/0 dijadikan pada 1 variable
  }
  //------------------------------ Tentukan Mode dan Output
  for (vrX=0; vrX<8; vrX++)
  {
    digitalWrite (ot[vrX], outHiLow[my8bit][vrX]);
  }
}
