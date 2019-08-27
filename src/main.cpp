#include "events.h"
#include "Wifi.h"
#include "nvs_flash.h"
#include "gpio.h"
#include "esp_log.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/netif.h"
#include "esp_event_loop.h"
#include "mqtt.h"


 extern "C" {
 int app_main(void);
 }



Wifi wifi;
IO io;

void ISR(void*)
{
  xSemaphoreGiveFromISR(io.xSemaphore, NULL);
}

void Switch(void* arg)
{
  bool status = 0;
  int count = 0;
  xEventGroupWaitBits(wifi.wifi_event_group,wifi.CONNECTED_BIT,false,true,portMAX_DELAY);
  while(1)
  {
    if(xSemaphoreTake(io.xSemaphore,portMAX_DELAY) == pdTRUE)
    {
      if(status)
      {
        io.off(4);
        status=0;
        ESP_LOGI("led","led is off and status is %d  and pressed %d times",(int)status ,count);
      }

      else if(!status){
        io.on(4);
        status=1;
        ESP_LOGI("led","led is off and status is %d  and pressed %d times",(int)status ,count);
        
      }
    }
  }
}



int app_main()
{
   
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    io.xSemaphore = xSemaphoreCreateBinary();
    esp_log_level_set("led", ESP_LOG_INFO); 
    
    

    wifi.init(WIFI_MODE_STA); 
    io.init(2,IO::INPUT);
    io.init(4,IO::OUTPUT);
    io.setIntr(2,ISR);

    xEventGroupWaitBits(wifi.wifi_event_group,wifi.CONNECTED_BIT,false,true,portMAX_DELAY);

    //mqtt.start();
    MQTT mqtt("mqtt://localhost");
    ESP_ERROR_CHECK(mqtt.start());

    xTaskCreate(Switch,"Switch",2048,NULL,10,NULL);
  
    while(1)
    {
        vTaskDelay(10);
    }
 

    return 0;
}