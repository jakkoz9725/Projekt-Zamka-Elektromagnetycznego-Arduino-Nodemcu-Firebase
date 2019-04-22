#include<ESP8266WiFi.h>
#include<FirebaseArduino.h> //Biblioteka firebase
#include<time.h>
#define FIREBASE_HOST"<nazwa projektu firebase>.firebaseio.com"
#define FIREBASE_AUTH"<Sekretny klucz do bazy danych>"
#define WIFI_SSID"<WIFI LOGIN>"
#define WIFI_PASSWORD"<WIFI PASSWORD>"
String firebasedb="Control";
String chipId="123";
FirebaseArduino FirebaseStream;

void setup() {
pinMode(D8,INPUT);  //Arduino informuje o otwarciu zamka przy uzyciu karty zbliżeniowej
pinMode(D7,OUTPUT); //Przekazanie informacji o otwarciu zamka w aplikacji mobilnej,okienkowej czy konsoli firebase
pinMode(D6,OUTPUT); //Przekazanie informacji o blokadzie kart zbliżeniowych
pinMode(D0,OUTPUT); // Sterowanie
pinMode(D2,OUTPUT); // Dioda
pinMode(D1,OUTPUT); // RBG
digitalWrite(D0,HIGH);
digitalWrite(D2,HIGH);
digitalWrite(D1,HIGH);
WifiPolaczenie();
UstawianieFirebase();
}

void loop() {
if(FirebaseStream.getInt(firebasedb+"/colorRed")==1){ 
  digitalWrite(D0,LOW);
}else{
  digitalWrite(D0,HIGH);
}
if(FirebaseStream.getInt(firebasedb+"/colorGreen")==1){ 
  digitalWrite(D2,LOW);
}else{
  digitalWrite(D2,HIGH);
}
if(FirebaseStream.getInt(firebasedb+"/colorBlue")==1){ 
  digitalWrite(D1,LOW);
}else{
  digitalWrite(D1,HIGH);
}
if(digitalRead(D8) == HIGH){
  OtwieranieKarta();
}
if(FirebaseStream.getInt(firebasedb+"/cardsBlocked")==1){
  digitalWrite(D6,HIGH);
}else{
  digitalWrite(D6,LOW);
}
if(FirebaseStream.getInt(firebasedb+"/openByApp")==1){
    OtwieranieAplikacja();

}
}
void OtwieranieKarta(){
  FirebaseStream.setInt(firebasedb+"/openByCard",1);
  delay(1000);
  FirebaseStream.setInt(firebasedb+"/openByCard",0);
}
void OtwieranieAplikacja(){
  digitalWrite(D7,HIGH);
  FirebaseStream.setInt(firebasedb+"/openByApp",0);
  delay(500);
  digitalWrite(D7,LOW);
}
void WifiPolaczenie(){
WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
while(WiFi.status()!=WL_CONNECTED){
Serial.println("Connecting...");
delay(500);
}
Serial.print("Connected succesfully");
}
void UstawianieFirebase(){
configTime(3600,0,"pool.ntp.org","time.nist.gov"); // tba
FirebaseStream.begin(FIREBASE_HOST,FIREBASE_AUTH); // Rozpoczęcie połączenia z FireBase oraz konfiguracja\reset bazy danych
FirebaseStream.setInt(firebasedb+"/openByCard",0);
FirebaseStream.setInt(firebasedb+"/cardsBlocked",0);
FirebaseStream.setInt(firebasedb+"/openByApp",0);
FirebaseStream.setInt(firebasedb+"/colorRed",0);
FirebaseStream.setInt(firebasedb+"/colorBlue",0);
FirebaseStream.setInt(firebasedb+"/colorGreen",0);
FirebaseStream.stream("control");
}


