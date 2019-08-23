#ifndef EVENTS_H
#define EVENTS_H
#include "esp_event_loop.h"
#include "esp_event.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//we will try to imitate the eventemitter concept of node
//in espidf there two types of event loop , one is default and another is user custom
//we will init event loop and then make some handler and then make a emit function
//lets do it  

#define ARGS void* args , esp_event_base_t base , int32_t id , void* data

typedef enum{
    WIFI,
    IP
}event_type;


class Events{
    public:
   
    Events(bool,event_type);
    void  on(int32_t, esp_event_handler_t);
    void emit(const char *);
  
    
    private:
    esp_event_loop_handle_t loop_handle;
    bool user;
    esp_event_base_t base_id;
    
};

#endif