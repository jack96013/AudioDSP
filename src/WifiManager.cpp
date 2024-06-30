/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-27 22:02:38
 * @LastEditTime : 2024-06-30 13:53:07
 * @Description  : 
 */
/*
 * @Author: TZU-CHIEH,HSU
 * @Date: 2023-08-01 20:33:25
 * @LastEditors: TZU-CHIEH,HSU
 * @LastEditTime: 2023-08-27 03:15:33
 * @Description:
 */
#include "WifiManager.h"

WifiManager::WifiManager()
{
}

void WifiManager::begin()
{
    // deviceName += String(DEVICE_NAME);
    // deviceName += String(ESP.GETcHIP);

    WiFi.onEvent(std::bind(&WifiManager::WiFiEvent, std::placeholders::_1, this));
    // wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(this->connect));
    WiFi.setHostname(DEVICE_NAME);
    connect();
}

void WifiManager::check()
{
    // ElegantOTA.loop();
}

time_t WifiManager::getBootTime()
{
    return boot_time;
}

void WifiManager::connect()
{
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void WifiManager::initialService()
{
    if (!MDNS.begin(DEVICE_NAME))
    {
        Serial.println("Error starting mDNS");
    }

    initialOTA();

}

void WifiManager::initialOTA()
{
    // otaWebServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    //     request->send(200, "text/plain", "Hi! This is ElegantOTA AsyncDemo.");
    // });

    // ElegantOTA.begin(&otaWebServer);    // Start ElegantOTA
    // ElegantOTA.setAutoReboot(true);
    // // ElegantOTA callbacks
    // ElegantOTA.onStart(onOTAStart);
    // ElegantOTA.onProgress(onOTAProgress);
    // ElegantOTA.onEnd(onOTAEnd);

    // otaWebServer.begin();
    // Serial.println("HTTP server started");
}

void WifiManager::WiFiEvent(WiFiEvent_t event, WifiManager *_this)
{
    Serial.printf("[WiFi-event] event: %d\n", event);
    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        _this->initialService();
        _this->reconnnect_times = 0;
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        Serial.println("WiFi lost connection");
        // xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
        // xTimerStart(_this->wifiReconnectTimer, 0);
        // _this->reconnnect_times ++;
        // if (_this->reconnnect_times >= 10)
        // {
        //     ESP.restart();
        // }
        break;
    }
}

void WifiManager::onOTAStart() {
  // Log when OTA has started
  Serial.println("OTA update started!");
  // <Add your own code here>
}

void WifiManager::onOTAProgress(size_t current, size_t final) {
  // Log every 1 second
  static unsigned long ota_progress_millis = 0;
  if (millis() - ota_progress_millis > 1000) {
    ota_progress_millis = millis();
    Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
  }
}

void WifiManager::onOTAEnd(bool success) {
  // Log when OTA has finished
  if (success) {
    Serial.println("OTA update finished successfully!");
  } else {
    Serial.println("There was an error during OTA update!");
  }
  // <Add your own code here>
}