#ifndef MQTT_H
#define MQTT_H

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"
#include "esp_event_loop.h"
#include "string.h"
#include "esp_log.h"
#include "gpio.h"


class MQTT {

public:
    MQTT(const char *);
    void subscribe(const char *);
    void publish(const char * , const char * );
    esp_err_t start();
    static esp_err_t handler(esp_mqtt_event_handle_t );
    esp_mqtt_client_handle_t  client;
    static SemaphoreHandle_t xSemaphore ;
private:
};

#endif