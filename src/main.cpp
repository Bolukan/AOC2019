#include <Arduino.h>

// WiFi
#include <ESP8266WiFi.h>
#include "secrets.h"
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FS.h>

#include <dayAOC201901.h>

#define APP_NAME "Advent of Code 2019"
#define FILENAME "/input201901"

// wifi
#ifndef SECRETS_H
#define SECRETS_H
const char WIFI_SSID[] = "*** WIFI SSID ***";
const char WIFI_PASSWORD[] = "*** WIFI PASSWORD ***";
#endif

// ************************************ FUNCTION *******************************

// ***********************************  WIFI  **********************************

// More events: https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFiGeneric.h

void onSTAConnected(WiFiEventStationModeConnected e /*String ssid, uint8 bssid[6], uint8 channel*/)
{
  Serial.printf("WiFi Connected: SSID %s @ BSSID %.2X:%.2X:%.2X:%.2X:%.2X:%.2X Channel %d\n",
                e.ssid.c_str(), e.bssid[0], e.bssid[1], e.bssid[2], e.bssid[3], e.bssid[4], e.bssid[5], e.channel);
}

void onSTADisconnected(WiFiEventStationModeDisconnected e /*String ssid, uint8 bssid[6], WiFiDisconnectReason reason*/)
{
  Serial.printf("WiFi Disconnected: SSID %s BSSID %.2X:%.2X:%.2X:%.2X:%.2X:%.2X Reason %d\n",
                e.ssid.c_str(), e.bssid[0], e.bssid[1], e.bssid[2], e.bssid[3], e.bssid[4], e.bssid[5], e.reason);
  // Reason: https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/src/ESP8266WiFiType.h
}

void onSTAGotIP(WiFiEventStationModeGotIP e /*IPAddress ip, IPAddress mask, IPAddress gw*/)
{
  Serial.printf("WiFi GotIP: localIP %s SubnetMask %s GatewayIP %s\n",
                e.ip.toString().c_str(), e.mask.toString().c_str(), e.gw.toString().c_str());
}

void SetupWiFi()
{
  static WiFiEventHandler e1, e2, e4;
  // WiFi events
  e1 = WiFi.onStationModeConnected(onSTAConnected);
  e2 = WiFi.onStationModeDisconnected(onSTADisconnected);
  e4 = WiFi.onStationModeGotIP(onSTAGotIP);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoConnect(false);  // do not automatically connect on power on to the last used access point
  WiFi.setAutoReconnect(true); // attempt to reconnect to an access point in case it is disconnected
  WiFi.persistent(false);      // Store no SSID/PASSWORD in flash
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

// ***********************************  OTA  ***********************************

void OTAonStart()
{
  String type;
  if (ArduinoOTA.getCommand() == U_FLASH)
  {
    type = "sketch";
  }
  else
  { // U_SPIFFS
    type = "filesystem";
  }
  // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
  Serial.println("OTA Start. Type: " + type);
}

void OTAonEnd()
{
  Serial.println("\nOTA End");
}

void OTAonProgress(unsigned int progress, unsigned int total)
{
  Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
};

void OTAonError(ota_error_t error)
{
  Serial.printf("Error[%u]: ", error);
  if (error == OTA_AUTH_ERROR)
  {
    Serial.println("Auth Failed");
  }
  else if (error == OTA_BEGIN_ERROR)
  {
    Serial.println("Begin Failed");
  }
  else if (error == OTA_CONNECT_ERROR)
  {
    Serial.println("Connect Failed");
  }
  else if (error == OTA_RECEIVE_ERROR)
  {
    Serial.println("Receive Failed");
  }
  else if (error == OTA_END_ERROR)
  {
    Serial.println("End Failed");
  }
};

void SetupOTA()
{
  char hostname[12];
  sprintf(hostname, "esp-%06x", ESP.getChipId());
  ArduinoOTA.setHostname(hostname);
  ArduinoOTA.onStart(OTAonStart);
  ArduinoOTA.onEnd(OTAonEnd);
  ArduinoOTA.onProgress(OTAonProgress);
  ArduinoOTA.onError(OTAonError);
  ArduinoOTA.begin();
}

// ***********************************  ...  ***********************************

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(APP_NAME);

  SetupWiFi();
  SetupOTA();

  DayAOC201901 day(FILENAME);
  day.Part1();
  day.Part2();

}

void loop()
{
  ArduinoOTA.handle();
}