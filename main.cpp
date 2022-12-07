/* ===== Built-in headers ===== */
#ifdef ESP32
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <ArduinoOTA.h>

#define RATE 115200


class NetworkActivities {
  public:
    class StartupNetworkActivities {
      public:
        void setupWIFI(); 
        void setupWIFIClient();
        void setupHTTPClient();
      private:
        WiFiClient client;
        HTTPClient http;

        // WiFi authorization data
        const char* _ssid = "_ssid";
        const char* _password = "_password";

        // HTTP connection authorization data
        const char* _serverName = "http://shashizv.beget.tech/post-esp-data.php";
        String apiKeyValue = "tPmAT5Ab3j7F9";
    };

    class DebugOTA {
      public:
        void setupOTA();  // Setuo OTA connection

      private:
        // Authorization data
        const char* _hostname = "ESP8266-00001";
        const char* _password = "0000";
    };

  private:
};

class SensorsActivities {
  public:
    void runActivities();
    void firstSensorStateChecker();
    void secondSensorStateChecker();

  private:
    int firstSensorPin = D5;
    int secondSensorPin = D6;
    bool firstSensorState = LOW;
    bool secondSensorState = LOW;
};

void SensorsActivities::runActivities() {
  #ifdef ESP8266
    #define TX 1
    #define RX 3
    #define A0 A0
    #define D0 16
    #define D1 5
    #define D2 4
    #define D3 0
    #define D4 2
    #define D5 14
    #define D6 12
    #define D7 13
    #define D8 15
  #endif

  SensorsActivities SensorsActivities;
  SensorsActivities.firstSensorStateChecker();
  SensorsActivities.secondSensorStateChecker();
}

void SensorsActivities::firstSensorStateChecker() {
  pinMode(firstSensorPin, INPUT);
  firstSensorState = digitalRead(firstSensorPin);

  Serial.print("First sensor state: ");

  if (firstSensorState == HIGH){
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
}

void SensorsActivities::secondSensorStateChecker() {
  pinMode(secondSensorPin, INPUT);
  secondSensorState = digitalRead(secondSensorPin);

  Serial.print("Second sensor state: ");

  if (secondSensorState == HIGH){
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }
}

void NetworkActivities::StartupNetworkActivities::setupWIFI() {
  // Setup serial port
  Serial.begin(RATE);
  Serial.println();
        
  WiFi.begin(_ssid, _password); // Begin WiFi
        
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(_ssid);

  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  // Connected to WiFi
  Serial.println(); 
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void NetworkActivities::StartupNetworkActivities::setupWIFIClient() {

}

 /* Sketch health check !!! */

void NetworkActivities::StartupNetworkActivities::setupHTTPClient() {
  // SensorsActivities SensorsActivities;
  bool firstSensorState = digitalRead(D5); // SensorsActivities.firstSensorStateChecker();
  bool secondSensorState = digitalRead(D6); // SensorsActivities.secondSensorStateChecker();

  Serial.println(firstSensorState);
  Serial.println(secondSensorState);

  http.begin(client, _serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Привести тип bool к String у firstSensorState и secondSensorState
  String httpRequestData = "api_key=" + apiKeyValue + "&sensor_1=" + firstSensorState + "&sensor_2=" + secondSensorState + "";

  Serial.print("httpRequestData: ");
  Serial.println(httpRequestData);

  int httpResponseCode = http.POST(httpRequestData);

  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    }
  else {
    Serial.print("Error code: ");
      Serial.println(httpResponseCode);
  }
  Serial.println("======================================");
  // Free resources
  http.end();
}

void NetworkActivities::DebugOTA::setupOTA() {
  ArduinoOTA.setHostname(_hostname);
  ArduinoOTA.setPassword(_password);
  ArduinoOTA.begin();
}

void setup(){
  NetworkActivities::StartupNetworkActivities networkConfig;
  NetworkActivities::DebugOTA debuggerConfig;

  SensorsActivities sensorConfig;
  
  networkConfig.setupWIFI();  // Setup Wi-Fi connection
  debuggerConfig.setupOTA();  // Setup OTA connection
}

void loop() {
  NetworkActivities::StartupNetworkActivities senderHTTP;
  SensorsActivities sensorConfig;
  sensorConfig.runActivities();
  senderHTTP.setupHTTPClient();

  ArduinoOTA.handle();

  delay(30000);
}
