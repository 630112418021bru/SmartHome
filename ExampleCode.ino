#include <TridentTD_LineNotify.h>
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPLCKLSNqq_"
#define BLYNK_TEMPLATE_NAME "Smart home security system"
#define BLYNK_AUTH_TOKEN "fC9QOBVm6A63Q-lTcqmYoqWSA35TIiYR"
#define LINE_TOKEN "JmBsr4fAsgYt6SqRqYCy3Bh0EThwte1BCt89CVEUsIY"


#include "DHT.h"
#define DHTPIN D5    // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
int inputLIGHT = A0;
int ledLIGHT = D0;
int vallight = 0;
int ledfan = D1;
int inputsmok = A0;
int ledPin2= D2;
int valsmok = 0;
int buzzer = D4;
int digitalPin = D8;
int valpir = 0;

boolean flag = 1;
boolean A = true;

char ssid[] = "Mi 10T Pro";
char pass[] = "12345678";
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
  Serial.println(LINE.getVersion());
  pinMode(buzzer, OUTPUT);
  pinMode(digitalPin, INPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.println("DHTxx test!");
  dht.begin();
  pinMode(ledfan, OUTPUT);
  LINE.setToken(LINE_TOKEN);
  Serial.begin(9600);
   pinMode(ledLIGHT, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);


  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  




  valsmok = analogRead(inputsmok);  //อ่านค่าสัญญาณ analog ขา5
  Serial.print("valsmok = "); // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(valsmok); // พิมพ์ค่าของตัวแปร val
  vallight = analogRead(inputLIGHT);
  Serial.print("vallight = "); // พิมพ์ข้อความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(vallight); // พิมพ์ค่าของตัวแปร val


if (vallight > 680) { 
  while (flag==1){
    digitalWrite(ledLIGHT, HIGH);
     WidgetLED LED(V0);
    LED.on();
    LINE.notify("ไฟติดแล้วงับ");
    flag = 0 ;
  }

  } else {
    while (flag==0){
    digitalWrite(ledLIGHT,LOW);
    WidgetLED LED(V0);
    LED.off(); 
    LINE.notify("ไฟดับแล้วงับ");
    flag = 1 ; 
    } 
  }
    if (valsmok > 600) { 
    while(A==true){
    WidgetLED LED(V4);
    LED.on();
    digitalWrite(buzzer ,HIGH); 
    LINE.notify("พบควัน");
    A = false;

    }

  } else {
    while(A==false){
    WidgetLED LED(V4);
    LED.off();
    digitalWrite(buzzer , LOW); 
    A = true;
    }


  }
    Blynk.virtualWrite(V5, t);
  delay(500);

  Blynk.run();
}


