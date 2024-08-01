#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include<Adafruit_Sensor.h>
//  network 
const char* ssid = "YATEC";
const char* password = "YATEC123";

#define DHTPIN 2 // Digital pin 
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

void handleRoot();

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin(); // Initialize DHT sensor

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Temperature = ");
  Serial.print(temperature, 1);
  Serial.println(" °C");
  Serial.print("Humidity = ");
  Serial.print(humidity, 1);
  Serial.println(" %");

  delay(1000);
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1 style='text-align:center;'>Weather Moniter</h1>";
  html += "<div style='display:flex; justify-content:center;'>";
  html += "<div style='margin:25px; text-align:center;'>";
  html += "<h2>Temperature Value</h2>";
  html += "<p style='font-size:48px;'>" + String(dht.readTemperature(),1) + " &deg;C</p>";
  html += "</div>";
  html += "<div style='margin:25px; text-align:center;'>";
  html += "<h2>Humidity Value</h2>";
  html += "<p style='font-size:55px;'>" + String(dht.readHumidity()) + " %</p>";
  html += "</div>";
  html += "</div>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}
