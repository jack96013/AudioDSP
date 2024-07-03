/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-27 22:02:38
 * @LastEditTime : 2024-07-02 23:05:08
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
    String macString = WiFi.macAddress();
    macString.replace(":", "");
    
    deviceName += String(DEVICE_NAME);
    deviceName += "-";
    deviceName += macString.substring(8);

    WiFi.onEvent(std::bind(&WifiManager::WiFiEvent, std::placeholders::_1, this));
    // wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(this->connect));
    WiFi.setHostname(deviceName.c_str());
    
    Serial.print(F("Device Name: "));
    Serial.println(deviceName);
    connect();

    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    Serial.println("Listing SPIFFS files:");
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file) {
        Serial.print("FILE: ");
        Serial.print(file.name());
        Serial.print("\tSIZE: ");
        Serial.println(file.size());
        file = root.openNextFile();
    }
        
}

void WifiManager::check()
{
    ElegantOTA.loop();
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
    if (!MDNS.begin(deviceName.c_str()))
    {
        Serial.println("Error starting mDNS");
    }

    initialOTA();
}

void WifiManager::initialOTA()
{
    webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                    { request->send(200, "text/plain", "Hi! This is ElegantOTA AsyncDemo."); });

    webServer.serveStatic("/test/", SPIFFS, "/").setDefaultFile("index.html");
    
    ElegantOTA.begin(&webServer); // Start ElegantOTA
    ElegantOTA.setAutoReboot(true);
    // ElegantOTA callbacks
    ElegantOTA.onStart(onOTAStart);
    ElegantOTA.onProgress(onOTAProgress);
    ElegantOTA.onEnd(onOTAEnd);
    
    webServer.begin();
    Serial.println("HTTP server started");
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

void WifiManager::onOTAStart()
{
    // Log when OTA has started
    Serial.println("OTA update started!");
    // <Add your own code here>
}

void WifiManager::onOTAProgress(size_t current, size_t final)
{
    // Log every 1 second
    static unsigned long ota_progress_millis = 0;
    if (millis() - ota_progress_millis > 1000)
    {
        ota_progress_millis = millis();
        Serial.printf("OTA Progress Current: %u bytes, Final: %u bytes\n", current, final);
    }
}

void WifiManager::onOTAEnd(bool success)
{
    // Log when OTA has finished
    if (success)
    {
        Serial.println("OTA update finished successfully!");
    }
    else
    {
        Serial.println("There was an error during OTA update!");
    }
    // <Add your own code here>
}