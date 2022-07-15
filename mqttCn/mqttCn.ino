
#include <M5Stack.h>
#include <WiFi.h>
#include <ThingsBoard.h>    // ThingsBoard SDK

// WiFi access point
#define WIFI_AP_NAME        "INCUBATEC"
// WiFi password
#define WIFI_PASSWORD       "incubatin"
int status = WL_IDLE_STATUS;

//Thingsboard acces data
#define TOKEN               "ATOKEN-TESTING"
// ThingsBoard server instance.
#define THINGSBOARD_SERVER  "multiaire.smartaraucania.org"

// Initialize ThingsBoard client
WiFiClient espClient;
// Initialize ThingsBoard instance
ThingsBoard tb(espClient);
// Set to true if application is subscribed for the RPC messages.
bool subscribed = false;



void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  InitWiFi();
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
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN, 1883)) {
      Serial.println("Failed to connect");
      return;
    }
  }
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
