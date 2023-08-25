#include <SPI.h>
#include <WiFiNINA.h>
#include <ThingSpeak.h>

// Replace with your Wi-Fi credentials
char ssid[] = "Choudhary (2)";
char pass[] = "12345678";

// ThingSpeak settings
unsigned long channelID = 2250688;
const char* writeAPIKey = "0KXAT1261KZJ21IW";

// LDR sensor pin
const int ldrPin = A7;

// Create a WiFi client object
WiFiClient client;

void setup() {
  Serial.begin(9600);

  // Check for the WiFi module on the board
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi module not found!");
    while (true);
  }

  // Attempt to connect to Wi-Fi network
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.println("Attempting to connect to WiFi...");
    delay(1000);
  }

  Serial.println("Connected to WiFi");
  
  // Initialize ThingSpeak with the WiFi client
  ThingSpeak.begin(client);
}

void loop() {
  int ldrValue = analogRead(ldrPin); // Read LDR value
  Serial.println("LDR Value: " + String(ldrValue));
  
  // Update ThingSpeak channel with LDR value
  ThingSpeak.setField(1, ldrValue); // Use field number 1 for LDR value
  int response = ThingSpeak.writeFields(channelID, writeAPIKey);
  
  if (response == 200) {
    Serial.println("Channel update successful");
  } else {
    Serial.println("Problem updating channel. HTTP error code: " + String(response));
  }
  
  delay(30000); // Delay before the next update (30 seconds)
}
