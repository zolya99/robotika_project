#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
char ch;
int red_light_pin= 19;
int green_light_pin = 20;
int blue_light_pin = 21;

int speaker_pin = 5;
String code = "";
String code1 = "open";
String code2 = "closed";
int delay_unit = 250;


int motorPin1 = 7;
int motorPin2 = 8;

#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

void point(){
  digitalWrite(speaker_pin, HIGH);
  delay(333);
  digitalWrite(speaker_pin, LOW);
  delay(333);
  }

void line(){
digitalWrite(speaker_pin, HIGH);
delay(1000);
digitalWrite(speaker_pin, LOW);
delay(1000);
  
  }

void setup() {

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  
  lcd.begin();
  Serial.begin(9600);
  delay(5000);// Initiate a serial communication
  SPI.begin();// Initiate  SPI bus
  
  lcd.backlight();
  mfrc522.PCD_Init();   // Initiate MFRC522
  
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  pinMode(speaker_pin, OUTPUT);
  lcd.println("card to read");
  //Approximate your card to the reader
  

}
void loop() {
  RGB_color(0,255,255); // Red
  

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if (content.substring(1) == "C3 8A 1B 24" || "47 2B 37 53" ) //change here the UID of the card/cards that you want to give access
  {
    lcd.clear();
    lcd.println("Authorized access");
    RGB_color(173,255,47); // Green
    digitalWrite(motorPin1, HIGH);
    /*digitalWrite(speaker_pin, HIGH);
    delay(3000);
    digitalWrite(speaker_pin, LOW);*/
    
    //o
    line();
    delay(100);
    line();
    delay(100);
    line();
    delay(100 * 4);
    //p
    point();
    delay(100);
    line();
    delay(100);
    line();
    delay(100);
    point();
    delay(100 * 4);
    //e
    point();
    delay(100 * 4);
    //n
    line();
    delay(100);
    point();
    delay(100 * 4);
    digitalWrite(motorPin1, LOW);
    
  }
 
 else   {
    lcd.clear();
    lcd.println(" Access denied");
    RGB_color(0,255,255); 
    delay(3000);
  }

  
  
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}






void morse(){
  if(ch == 'c'){
    c();
  }
  else if(ch == 'l'){
    l();
  }
  else if(ch == 'o'){
    o();
  }
  else if(ch == 's'){
    s();
  }
  else if(ch == 'e'){
    e();
  }
  else if(ch == 'd'){
    d();
  }
  else if(ch == 'p'){
    p();
  }
  else if(ch == 'n'){
    n();
  }
  
}

void String2Morse(){
 int len = code.length();
  for (int i = 0; i < len; i++){
    ch = code.charAt(i);
    morse();
  }
}



void c(){
  line();
  delay(delay_unit);
  point();
  delay(delay_unit);
  line();
  delay(delay_unit);
  point();
  delay(delay_unit * 5);
}

void d(){
  line();
  delay(delay_unit);
  point();
  delay(delay_unit);
  point();
  delay(delay_unit * 5);
}

void e(){
  point();
  delay(delay_unit * 5);
}

void l(){
  point();
  delay(delay_unit);
  line();
  delay(delay_unit);
  point();
  delay(delay_unit);
  point();
  delay(delay_unit * 5);
}

void n(){
  line();
  delay(delay_unit);
  point();
  delay(delay_unit * 5);
}

void o(){
  line();
  delay(delay_unit);
  line();
  delay(delay_unit);
  line();
  delay(delay_unit * 5);
}

void p(){
  point();
  delay(delay_unit);
  line();
  delay(delay_unit);
  line();
  delay(delay_unit);
  point();
  delay(delay_unit * 5);
}

void s(){
  point();
  delay(delay_unit);
  point();
  delay(delay_unit);
  point();
  delay(delay_unit * 5);
}
