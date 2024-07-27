#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include "DHT.h"

WebServer server(80);
Preferences preferences;

String ssid = "";
String password = "";

const int SensorPin1 = 36;
const int SensorPin2 = 39;
const int SensorPin3 = 34;
const int SensorPin4 = 35;
const int SensorPin5 = 32;

const int airvalue = 2590;
const int watervalue = 1050;

unsigned long startTime;

float humidity = 0;
float temperature = 0;
float hi = 0;

DHT dht(33, DHT22);

void handleRoot() {
  int soil1 = analogRead(SensorPin1);
  int soil2 = analogRead(SensorPin2);
  int soil3 = analogRead(SensorPin3);
  int soil4 = analogRead(SensorPin4);
  int soil5 = analogRead(SensorPin5);

  if(millis()>startTime+2000){
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    startTime=millis();
  }

  String data = "{\"soil1\":\"" + String(soil1) + 
                "\",\"soil2\":\"" + String(soil2) +
                "\",\"soil3\":\"" + String(soil3) + 
                "\",\"soil4\":\"" + String(soil4) + 
                "\",\"soil5\":\"" + String(soil5) + 
                "\",\"humidity\":\"" + String(humidity) +
                "\",\"temperature\":\"" + String(temperature) +
                "\"}";
  server.send(200, "application/json", data);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleSaveGet() {
  String html = "<html>"
                "<head><meta name='viewport' content='width=device-width, initial-scale=1'><head>"
                "<body>"
                "<h1>ESP32 Input Form</h1>"
                "<form action='/save' method='post'>"
                "ssid: <input type='text' name='ssid'><br>"
                "password: <input type='text' name='password'><br>"
                "<input type='submit' value='Save'>"
                "</form>"
                "<h2>Saved Values:</h2>"
                "ssid: " + ssid + "<br>"
                "</body></html>";

  server.send(200, "text/html", html);
}

void handleSavePost() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");

  preferences.putString("ssid", ssid);
  preferences.putString("password", password);

  server.send(200, "text/html", "Recieved new ssid and password, restarting board.");
  preferences.end();
  ESP.restart();
}

void wifiSetServer() {
    WiFi.softAP("sernsor_server");
    server.on("/", HTTP_GET, handleSaveGet);
    server.on("/save", HTTP_POST, handleSavePost);
    Serial.println(WiFi.softAPIP());
}

void setup() {
  Serial.begin(115200);

  preferences.begin("credentials", false);

  ssid = preferences.getString("ssid", "");
  password = preferences.getString("password", "");

  if (ssid == "" || password == ""){
    wifiSetServer();
  }
  else {
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.println("");

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10) {
      delay(500);
      Serial.print(".");
      attempts++;
    }

    if (WiFi.status() != WL_CONNECTED) {
      wifiSetServer();
    }
    else{
      Serial.println("");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());

      server.on("/", handleRoot);
      preferences.end();
      dht.begin();
      startTime=millis();
    }
  }
  server.enableCORS();
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop() {
  server.handleClient();
  delay(2);
}