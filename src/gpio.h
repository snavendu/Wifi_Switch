#ifndef GPIO_H
#define GPIO_H

#include "driver/gpio.h"
#include "stdarg.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"


class IO{

public:
    typedef enum {
        INPUT,
        OUTPUT
    }mode;
     //basic or common configuration
    SemaphoreHandle_t xSemaphore= xSemaphoreCreateBinary();;
    
    esp_err_t init( uint8_t,mode);
    esp_err_t setMode(uint8_t,mode );
    void  setIntr(uint8_t ,gpio_isr_t );
    int get(uint8_t);
    esp_err_t on(uint8_t);
    esp_err_t off(uint8_t);
    esp_err_t reset(uint8_t);
    
private:

    
};


#endif