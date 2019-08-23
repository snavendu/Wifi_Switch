#ifndef WIFI_H
#define WIFI_H

#include <stdio.h>
#include "esp_system.h"
#include "esp_wifi.h"
#include <string.h>
#include "esp_log.h"
#include "nvs_flash.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "Wifi.h"

//wifi consist of some steps 
//first is to init lwip and wifi => done in condtructor function 
//second configure wifi
//start pshase 
//connect phase


class Wifi{
    public:
    static EventGroupHandle_t wifi_event_group;
    static const int CONNECTED_BIT = BIT0;
   
    Wifi() ;
    void init(wifi_mode_t);
   // esp_err_t configure();
    esp_err_t start();
    esp_err_t connect();
    esp_err_t stop();
    esp_err_t reinit();
    //we will config ,set the mode , scan and after that we will connect
    private:

    void mode_init(wifi_mode_t );
    esp_err_t scan();
    wifi_init_config_t init_cfg;
    wifi_config_t sta_cfg;
    static esp_err_t handler(void*,system_event_t*);
    const char * ap_ssid;
    const char * ap_password;
    const char * sta_ssid = "iot";
    const char * sta_password = "";
    



};

#endif