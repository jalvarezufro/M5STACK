//SGP30 needs 15 seconds to initialize calibration after power on.
//The screen will display TVOC and CO2

#include <M5Stack.h>
#include "Adafruit_SGP30.h"
#include <WiFi.h>
#include <ThingsBoard.h>    // ThingsBoard SDK

// WiFi access point
#define WIFI_AP_NAME        "POCO X3 Pro"
// WiFi password
#define WIFI_PASSWORD       "javihermoso"
int status = WL_IDLE_STATUS;

//Thingsboard acces data
#define TOKEN               "ATOKEN-TESTING"
// ThingsBoard server instance.
#define THINGSBOARD_SERVER  "multiaire.smartaraucania.org"

Adafruit_SGP30 sgp;
int i = 15;
long last_millis = 0;
void header(const char *string, uint16_t color)
{
    M5.Lcd.fillScreen(color);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.fillRect(0, 0, 320, 30, TFT_BLACK);
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.drawString(string, 160, 3, 4); 
}



void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  InitWiFi();
//  M5.begin(true, false, true, true);
//  header("SGP30 TEST",TFT_BLACK);
//  Serial.println("SGP30 test");
//  if (! sgp.begin()){
//    Serial.println("Sensor not found :(");
//    while (1);
//  }
//  
//  M5.Lcd.drawString("TVOC:", 50, 40, 4);
//  M5.Lcd.drawString("eCO2:", 50, 80, 4);
//  Serial.print("Found SGP30 serial #");
//  Serial.print(sgp.serialnumber[0], HEX);
//  Serial.print(sgp.serialnumber[1], HEX);
//  Serial.println(sgp.serialnumber[2], HEX);
//  M5.Lcd.drawString("Initialization...", 140, 180, 4);
}



void loop() {
  delay(1000);
  
   // Reconnect to WiFi, if needed
  if (WiFi.status() != WL_CONNECTED) {
    reconnect();
    return;
  }

  // Reconnect to ThingsBoard, if needed
  if (!tb.connected()) {
    subscribed = false;

    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }
  
//  while(i > 0) {    
//    if(millis()- last_millis > 1000) {
//      last_millis = millis();
//      i--;
//      M5.Lcd.fillRect(198, 120, 40, 20, TFT_BLACK);
//      M5.Lcd.drawNumber(i, 20, 120, 4);
//    }        
//  }
//  M5.Lcd.fillRect(0, 120, 300, 30, TFT_BLACK);
//
//  if (! sgp.IAQmeasure()) {
//    Serial.println("Measurement failed");
//    return;
//  }
//  M5.Lcd.fillRect(100, 40, 220, 90, TFT_BLACK);
//  M5.Lcd.drawNumber(sgp.TVOC, 120, 40 , 4); //tvoc
//  M5.Lcd.drawString("ppb", 200, 40, 4);
//  M5.Lcd.drawNumber(sgp.eCO2, 120, 80, 4);  //eCO2
//  M5.Lcd.drawString("ppm", 200, 80, 4);
//  Serial.print("TVOC "); Serial.print(sgp.TVOC); Serial.print(" ppb\t");
//  Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");
// 
//  delay(1000);
}

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}


void reconnect() {
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to AP");
  }
}
