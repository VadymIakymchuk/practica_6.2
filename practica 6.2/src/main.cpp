#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <WebServer.h>
#define RST_PIN 27 //Pin 27 para el reset del RC522
#define SS_PIN 5 //Pin 5 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

const char* ssid = "Xiaomi_11T_Pro"; // Enter your SSID here
const char* password = "f5cbd8a82232"; //Enter your Password here
WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

// Handle root url (/)

void handle_root() {
server.send(200, "text/html", HTML);
}


void setup() {
Serial.begin(115200); //Iniciamos la comunicación serial


Serial.println("Try Connecting to ");
Serial.println(ssid);
// Connect to your wi-fi modem
WiFi.begin(ssid, password);
// Check wi-fi is connected to wi-fi network
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}

SPI.begin(); //Iniciamos el Bus SPI
mfrc522.PCD_Init(); // Iniciamos el MFRC522
Serial.println("Lectura del UID");


}
void loop() {
// Revisamos si hay nuevas tarjetas presentes
if ( mfrc522.PICC_IsNewCardPresent())
{
//Seleccionamos una tarjeta
if ( mfrc522.PICC_ReadCardSerial())
{
// Enviamos serialemente su UID
Serial.print("Card UID:");
for (byte i = 0; i < mfrc522.uid.size; i++) {
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
}
String HTML = "<!DOCTYPE html>\
<html>\
<body>\
<h1>" + char(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ") + "</h1>\
</body>\
</html>";
Serial.println();
// Terminamos la lectura de la tarjeta actual
mfrc522.PICC_HaltA();
}
}
}