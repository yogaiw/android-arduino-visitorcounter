#include <LiquidCrystal_I2C.h>
#include <Adafruit_MLX90614.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <FirebaseArduino.h>

LiquidCrystal_I2C lcd (0x27, 20,4);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//Inisiasi Sensor Suhu dan Jarak
float data = 0;
const int trigPin = 13; //D7
const int echoPin = 12; //D6
long duration;
int distance;

//Inisiasi Buzzer
int buzzer = 14; // D5

//Inisiasi PIR Sensor
int pir1 = 16; // D0 IN
int pir2 = 0; //D3 OUT

//Variabel penghitungan pengunjung
int in = 0, out = 0, count = 0;

//inisiasi increment
int randomKey=0;

//Milis
unsigned long waktuSebelum0 = 0;
unsigned long waktuSebelum1 = 0;
unsigned long waktuSebelum2 = 0;
unsigned long waktuSebelum3 = 0;
unsigned long interval1 = 2000;
unsigned long interval2 = 3000;
unsigned long interval3 = 3500;

//Firebase
#define FIREBASE_HOST "YOUR FIREBASE HOST"
#define FIREBASE_AUTH "YOUR FIREBASE AUTH"

//Wifi Setting
#define WIFI_SSID "Master"
#define WIFI_PASSWORD "tekanenter10x"


void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pir1, INPUT);
  pinMode(pir2, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(pir1, LOW);
  digitalWrite(pir2, LOW);


  lcd.begin();
  lcd.setCursor(6,1);
  lcd.print("Viscount");
  lcd.setCursor(4,2);
  lcd.print("Thermometer");
  delay(4000);
  lcd.clear();

  connect_wifi();
  mlx.begin();
 
}

void connect_wifi(){

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Masukan Wifi");
    lcd.setCursor(4,1);
    lcd.print("SSID:Master");
    lcd.setCursor(2,2);
    lcd.print("Pw:tekanenter10x");
    delay(1000);
    }

  lcd.clear();
  lcd.setCursor(5,1);
  lcd.print("Terhubung");
  lcd.setCursor(4,2);
  lcd.print("Ke Internet");
  delay(2000);
  lcd.clear();
  Serial.println();
  Serial.print("connected: ");
  Serial.println("Ip Address: ");
  Serial.print(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {
  unsigned long waktuSekarang = millis();
  long visin = digitalRead(pir1);
  long visout = digitalRead(pir2);
  data = mlx.readObjectTempC()+2;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if(waktuSekarang - waktuSebelum0 > 1500){
    if (distance <= 4){
       if (data >= 37.3 && data <= 100){     
         for(int i=0; i<5; i++){
          digitalWrite(buzzer, HIGH);
          delay(250);
          digitalWrite(buzzer, LOW);
          delay(250);
          }  
        delay(10);
        lcd.clear();
        lcd.setCursor(5, 0);
        lcd.print("Suhu Tubuh");
        lcd.setCursor(3, 1);
        lcd.print("Melebihi Batas");
        lcd.setCursor(2, 2);
        lcd.print("Suhu Tubuh: ");
        lcd.setCursor(13, 2);
        lcd.print(data);
        delay(1000);
        lcd.clear();

        randomKey++;
        String directory = "Suhu";
        String path = directory+"/"+randomKey+"/suhu";

        Firebase.setFloat(path, data);
        
      }
      if(data >= 0 && data < 37.3){
        
        digitalWrite(buzzer, HIGH);
        delay(250);
        digitalWrite(buzzer, LOW);
        
        delay(10);
        lcd.clear();
        lcd.setCursor(3, 1);
        lcd.print("Cek Suhu Tubuh");
        lcd.setCursor(2, 2);
        lcd.print("Suhu Tubuh: ");
        lcd.setCursor(13, 2);
        lcd.print(data);
        delay(1000);
        lcd.clear();

        randomKey++;
        String directory = "Suhu";
        String path = directory+"/"+randomKey+"/suhu";
        
        Firebase.setFloat(path, data);
        
        }
      else{
        digitalWrite(buzzer, HIGH);
        delay(250);
        digitalWrite(buzzer, LOW);

        delay(10);
        lcd.clear();
        lcd.setCursor(6, 1);
        lcd.print("Silahkan");
        lcd.setCursor(2, 2);
        lcd.print("Coba Sekali Lagi");
        delay(1000);
        lcd.clear();
        }
    }

    waktuSebelum0 = waktuSekarang;
  }


  if(waktuSekarang - waktuSebelum1 > interval1){
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print("Total: ");
      lcd.setCursor(12,0);
      lcd.print(count);
      lcd.setCursor(2,1);
      lcd.print("in: ");
      lcd.setCursor(5,1);
      lcd.print(in);
      lcd.setCursor(11,1);
      lcd.print("out: ");
      lcd.setCursor(15,1);
      lcd.print(out);
      lcd.setCursor(3, 2);
      lcd.print("Cek Suhu Tubuh");
      lcd.setCursor(2, 3);
      lcd.print("Dekatkan Tangan");

     waktuSebelum1 = waktuSekarang;
    }

    if(waktuSekarang - waktuSebelum2 > interval2){
       digitalWrite(pir1, LOW);

       if (visin == HIGH){      
        count=count+1; 
        in = in+1;
        for(int i=0; i<2; i++){
          digitalWrite(buzzer, HIGH);
          delay(100);
          digitalWrite(buzzer, LOW);
          delay(100);
          }
      
        Firebase.setInt("Data/masuk", in);
        if (Firebase.failed()) {
        Serial.print("Gagal memasukan data 'masuk' ke firebase");
        Serial.println(Firebase.error());  
        return;
        }
        Firebase.setInt("Data/total", count);
        if (Firebase.failed()) {
          Serial.print("Gagal memasukan data 'total' ke firebase");
          Serial.println(Firebase.error());  
          return;
          }
      } 

       waktuSebelum2 = waktuSekarang;
    }
    if(waktuSekarang - waktuSebelum3 > interval3){
      digitalWrite(pir2, LOW);

      if (visout == HIGH){
         count=count-1; 
         out = out+1;
         for(int i=0; i<2; i++){
          digitalWrite(buzzer, HIGH);
          delay(100);
          digitalWrite(buzzer, LOW);
          delay(100);
          }
         
         Firebase.setInt("Data/keluar", out);
         if (Firebase.failed()) {
            Serial.print("Gagal memasukan data 'keluar' ke firebase");
            Serial.println(Firebase.error());  
            return;
           }
         Firebase.setInt("Data/total", count);
          if (Firebase.failed()) {
            Serial.print("Gagal memasukan data 'total' ke firebase");
            Serial.println(Firebase.error());  
            return;
            }
        }

      waktuSebelum3 = waktuSekarang;
      }
}