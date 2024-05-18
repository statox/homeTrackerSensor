/*
 *  Simple HTTP get webclient test
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid     = "CHANGEME";
const char* password = "CHANGEME";

const char* host = "api.statox.fr";

void blink(int times, int length, int interval) {
  Serial.print("Blink");

  for (int i=0; i<times; i++) {
    Serial.print(".");
    digitalWrite(0, LOW);
    delay(length);
    digitalWrite(0, HIGH);
    delay(interval);
  }
  Serial.println();
}

void scanSSIDS() {
  Serial.print("Disconnecting ... ");
  Serial.println();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("Scan start ... ");
  int n = WiFi.scanNetworks();
  Serial.print(n);
  Serial.println(" network(s) found");
  for (int i = 0; i < n; i++)
  {
    Serial.println(WiFi.SSID(i));
  }
  Serial.println();
}

void connectToSSID() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(". ");
    Serial.print(WiFi.status());
    Serial.println();
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

int getRemoteTime(WiFiClient& client) {
    String path = "/health/getRemoteTime";
    String url = "http://" + String(host) + path;

    String remoteTimeResponse = httpGETRequest(url);
    JSONVar parsedRemoteTimeResponse = JSON.parse(remoteTimeResponse);
    int remoteTime = parsedRemoteTimeResponse["time"];

    return remoteTime;
}

void setup() {
  Serial.begin(9600);
  pinMode(0, OUTPUT);

  blink(10, 100, 100);
  delay(10000);
  blink(5, 800, 100);

  // We start by connecting to a WiFi network
  //scanSSIDS();
  connectToSSID();
}

void loop() {
    delay(10000);
    blink(2, 500, 500);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    int remoteTime = getRemoteTime(client);
    Serial.println("Remote time");
    Serial.println(remoteTime);

    Serial.println();
}
