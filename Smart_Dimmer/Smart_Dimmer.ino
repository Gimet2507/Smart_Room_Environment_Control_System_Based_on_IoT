/* Mendefinisikan template ID, Nama, dan Token otentikasi pada Blynk */
#define BLYNK_TEMPLATE_ID "TMPL6U8OomihZ"
#define BLYNK_TEMPLATE_NAME "Kelembaban IOT"
#define BLYNK_AUTH_TOKEN "OeF3CIW2uyzpmfmFL-PTEITzzFRHQCoC"

#include <ESP8266WiFi.h>                    // Wifi ESP8266
#include <BlynkSimpleEsp8266.h>             // Blynk
#include <RBDdimmer.h>
#include <DHT.h>

/* Mendefinisikan jaringan wifi dan token otentikasi pada Blynk */
char auth[] = "OeF3CIW2uyzpmfmFL-PTEITzzFRHQCoC";
char ssid[] = "tenda";
char pass[] = "duakelinci";

#define USE_SERIAL Serial
#define outputPin 12 //D6
#define zerocross 14 // D5 

#define DHTPIN 2  //D4      
#define DHTTYPE DHT22   // Mendefinisikan jenis sensor DHT22

BlynkTimer timer;                           // Mendefinisikan objek BlynkTimer

int newOutVal = 0; // Nilai baru untuk dimmer
dimmerLamp dimmer(outputPin, zerocross); // Inisialisasi dimmer
DHT dht(DHTPIN, DHTTYPE);                // Membuat objek sensor DHT

float temp = 0.0;     // Variabel untuk suhu
float humidity = 0.0; // Variabel untuk kelembapan
int lastOutVal = -1;    // Menyimpan nilai dimmer terakhir

const int relay1 = D1; //pin2
const int relay2 = D2; //A0 FOR ARDUINO/ 36 FOR ESP

int relayON = LOW; //relay nyala
int relayOFF = HIGH;

void setup() {
  USE_SERIAL.begin(9600);
  dimmer.begin(NORMAL_MODE, ON); // Inisialisasi dimmer
  dht.begin();                   // Inisialisasi sensor DHT22

  Blynk.begin(auth, ssid, pass);

  USE_SERIAL.println("Dimmer Program is starting...");

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop() {
  Blynk.run();  // Menjalankan Blynk
  timer.run();  // Menjalankan BlynkTimer
  
  // Membaca suhu dan kelembapan dari DHT22
  temp = dht.readTemperature(); // Membaca suhu dalam Celcius
  humidity = dht.readHumidity(); // Membaca kelembapan

  // Jika pembacaan gagal, tampilkan pesan kesalahan
  if (isnan(temp) || isnan(humidity)) {
    USE_SERIAL.println("Failed to read from DHT sensor!");
    delay(2000); // Tunggu 2 detik sebelum mencoba lagi
    return;
  }

  // Logika kontrol dimmer berdasarkan suhu
 
  if ( temp >= 0 && temp < 30){
    newOutVal = 100; // Nyalakan lampu penuh jika suhu kurang dari 30°C
    digitalWrite(relay1, relayOFF);
    digitalWrite(relay2, relayOFF);
    USE_SERIAL.print("Relay OFF ");
  } else if (temp >= 30 && temp<33){
    newOutVal=50;  // Nyalakan lampu dengan kecerahan 50% jika suhu antara 30°C dan 33°C
    digitalWrite(relay1, relayOFF);
    digitalWrite(relay2, relayOFF);
    USE_SERIAL.print("Relay OFF ");
  } else {
    newOutVal=0;   // Matikan lampu jika suhu lebih dari atau sama dengan 33°C
    digitalWrite(relay1, relayON);
    digitalWrite(relay2, relayON);
    USE_SERIAL.print("Relay ON ");
  }

  // Terapkan nilai dimmer jika berbeda dari nilai sebelumnya
  if (newOutVal != lastOutVal) {
    dimmer.setPower(newOutVal); 
    lastOutVal = newOutVal;
  }

  // Menampilkan suhu, kelembapan, dan persentase kecerahan lampu pada serial monitor
  USE_SERIAL.print("Temperature: ");
  USE_SERIAL.print(temp);
  USE_SERIAL.print(" °C, Humidity: ");
  USE_SERIAL.print(humidity);
  USE_SERIAL.print(" %, Lamp Power: ");
  USE_SERIAL.print(lastOutVal);
  USE_SERIAL.println("%");
 

  Blynk.virtualWrite(V0, temp);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, lastOutVal);
  Blynk.virtualWrite(V3, relay1);
  Blynk.virtualWrite(V4, relay2);

  delay(500); // Tunggu 2 detik sebelum pembacaan berikutnya
}

// Fungsi untuk memeriksa koneksi ke server Blynk
void checkConnection()
{
  if (!Blynk.connected()) {
    Serial.println("Reconnecting...");
    if (Blynk.connect()) {
      Serial.println("Reconnected!");
    } else {
      Serial.println("Reconnect failed!");
    }
  }
}