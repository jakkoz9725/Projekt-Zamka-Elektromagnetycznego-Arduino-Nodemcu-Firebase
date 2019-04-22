#include <SoftwareSerial.h>
#include <MFRC522.h>
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>

const byte Karta[] = {0x69, 0x2A, 0xD6, 0x73}; // Kod karty używanej do otwierania zamka
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);

MFRC522 rfid(10, 9);
MFRC522::MIFARE_Key key;
boolean zablokowanePrzezFirebase;

void setup() {

  pinMode(8,OUTPUT);    // Stan wysoki przekazuje informacje do NodeMCU, że użyta została karta zbliżeniowa
  pinMode(5,OUTPUT);	// Sterowanie przekaźnikiem
  pinMode(7,INPUT);		// NodeMCU wysyła informacje o otwarciu zamka przy użyciu aplikacji mobilnej/okienkowej(windows) ew. z poziomu konsoli Firebase
  pinMode(6,INPUT);		// Blokada karty zbliżeniowej
  lcd.noDisplay();
  lcd.noBacklight();  
  SPI.begin();
  rfid.PCD_Init();
  digitalWrite(8,LOW);
}

void loop() {
  digitalWrite(5,LOW);
if(digitalRead(7) == HIGH){
  OtwarcieZamka();
}

if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()){
if (SprawdzenieKarty()){
if(SprawdzenieBlokady()){
rfid.PICC_HaltA();
rfid.PCD_StopCrypto1();
digitalWrite(8,HIGH);
OtwarcieZamka();
}
else{
  lcd.clear();
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("   Zablokowane");
  lcd.setCursor(0,1); 
  lcd.print("-----------------");
  delay(2000);
  lcd.noDisplay();
  lcd.noBacklight();
}
}
}
}
void OtwarcieZamka(){
    lcd.clear();
    lcd.begin(16,2);
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("     Witaj");  
	digitalWrite(5,HIGH);
	delay(1000);
	digitalWrite(8,LOW);
	delay(2000);
	digitalWrite(5,LOW);
  lcd.noDisplay();
  lcd.noBacklight();
}

boolean SprawdzenieBlokady(){
  if(digitalRead(6) == HIGH){
    return false;
  }else{
    return true;
  }
}
boolean SprawdzenieKarty(){
if(rfid.uid.uidByte[0] == Karta[0] &&
rfid.uid.uidByte[1] == Karta[1] &&
rfid.uid.uidByte[2] == Karta[2] &&
rfid.uid.uidByte[3] == Karta[3]){
  return true;
}
else{
  return false;
}
}


