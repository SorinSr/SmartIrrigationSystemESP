#define BLYNK_TEMPLATE_ID " "
#define BLYNK_DEVICE_NAME " "
#define BLYNK_AUTH_TOKEN " "

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

WiFiClient client;
 
#define DHTPIN 4
#define DHTTYPE DHT11   

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int relay = 13;
const int waterLevelSensor = 35;
const int moistureLevelSensor = 34;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = " ";
char pass[] = " ";

int waterLevel;
int moistureLevel;

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendTempHumid(){
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
    
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }else{
    Serial.println("Temperature and humidity:");
    Serial.println(temperature);
    Serial.println(humidity);
  }

  Blynk.virtualWrite(V5, humidity);
  Blynk.virtualWrite(V6, temperature);

}

void sendMoistureTriggerRelay(){
  waterLevel = analogRead(waterLevelSensor);
  waterLevel = map(waterLevel,0,2000,0,100);

//  moistureLevel = ( 100.00 - ( (analogRead(moistureLevelSensor) / 1023.00) * 100.00 ) );

  moistureLevel = analogRead(moistureLevelSensor);
  moistureLevel = map(moistureLevel,4080,1380,0,100);

  if(moistureLevel > 100){
    moistureLevel = 100;
    }

  int limit = 30;
  if( moistureLevel < limit ){
      digitalWrite(relay, LOW);
      Serial.println("Current IS Flowing");
    }else{
      digitalWrite(relay, HIGH);
      Serial.println("Current NOT Flowing");
    }
  
  Blynk.virtualWrite(V2, waterLevel);
  Blynk.virtualWrite(V3, moistureLevel);

  Serial.println("Water level:  ");
  Serial.println(waterLevel);
  Serial.println("Soil moisture:  ");
  Serial.println(moistureLevel);
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();

  Serial.print("V1 received is: ");
  Serial.println(pinValue);

  if (pinValue != 0){
      digitalWrite(relay, LOW);
      Serial.println("Current IS Flowing");
      sleep(10);
  }else{
      digitalWrite(relay, HIGH);
      Serial.println("Current NOT Flowing");
    }
}

void setup()
{
  Serial.begin(115200);
  
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  Serial.println("Current not Flowing");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }

  Blynk.begin(auth, ssid, pass);

    dht.begin();

  timer.setInterval(3000L, sendTempHumid);
  timer.setInterval(6000L, sendMoistureTriggerRelay);
   
}

void loop()
{
  Blynk.run();
  timer.run();
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  moistureLevel = analogRead(moistureLevelSensor);
  moistureLevel = map(moistureLevel,4080,1380,0,100);

  if(moistureLevel > 100){
    moistureLevel = 100;
  }
  
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("T: ");
  display.print(temperature);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(248);
  display.setTextSize(2);
  display.print("C");

  display.setTextSize(2);
  display.setCursor(0, 25);
  display.print("H: ");
  display.print(humidity);
  display.print(" %"); 

  display.setTextSize(2);
  display.setCursor(0, 50);
  display.print("M: ");
  display.print(moistureLevel);
  display.setTextSize(2);
  display.print(" %");

  display.display();
}
