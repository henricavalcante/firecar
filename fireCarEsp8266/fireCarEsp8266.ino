#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

String t = "0";
String d = "90";

void setup() {
  Serial.begin(19200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/");
}

void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
  }

  if (Firebase.available()) {
     FirebaseObject event = Firebase.readEvent();
     String eventType = event.getString("type");
     eventType.toLowerCase();
     if (eventType == "put") {
       String path = event.getString("path");
       String data = event.getString("data");
       writeString(data, path);
     }
  }  
}

void writeString(String stringData, String channel) {

  for (int i = 0; i < stringData.length(); i++)
  {
    Serial.write(stringData[i]);
  }
  Serial.write(channel[1]);

}
