/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-27 14:41:35
 * @LastEditTime : 2024-06-30 17:29:32
 * @Description  : 
 */
#ifndef __WIFIMANAGER_H__
#define __WIFIMANAGER_H__

#include <Arduino.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>
#include "config.h"

class WifiManager
{
    private:
        

        static void WiFiEvent(WiFiEvent_t event,WifiManager* _this);
        static void connect();
        void initialService();
        void initialOTA();
        
        AsyncWebServer otaWebServer = AsyncWebServer(80);

        int reconnnect_times = 0;

        const char* time_ntpServer = "pool.ntp.org";
        const long  time_gmtOffset_sec = 28800;
        const int   time_daylightOffset_sec = 3600;
        
        time_t boot_time = 0;

        static void onOTAStart();
        static void onOTAProgress(size_t current, size_t final);
        static void onOTAEnd(bool success);
        
        String deviceName = "";


    public:
        WifiManager();
        void begin();
        void check();

        time_t getBootTime();
        

};

#endif