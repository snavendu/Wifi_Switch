#include"gpio.h"

esp_err_t IO::init(uint8_t pin , mode mode)
{
    gpio_config_t conf ;
    conf.pin_bit_mask = 1<<pin;
    
    switch(mode)
    {
        case OUTPUT:
            conf.mode=GPIO_MODE_OUTPUT;
            break;
        case INPUT:
            conf.mode=GPIO_MODE_INPUT;
            break;
    }
    if(mode==INPUT)
    {
        conf.pull_up_en = GPIO_PULLUP_ENABLE;
        conf.pull_down_en =GPIO_PULLDOWN_DISABLE;
    }

    else if(mode==OUTPUT)
    {
        conf.pull_up_en = GPIO_PULLUP_DISABLE;
        conf.pull_down_en =GPIO_PULLDOWN_DISABLE;
    }
    conf.intr_type = GPIO_INTR_DISABLE;

   return  gpio_config(&conf);

}

esp_err_t IO::setMode(uint8_t pin, mode mode)
{
    switch(mode)
    {
        case OUTPUT:
            return gpio_set_direction((gpio_num_t)pin,GPIO_MODE_OUTPUT);
            break;
        case INPUT:
            return gpio_set_direction((gpio_num_t)pin,GPIO_MODE_INPUT);
            break;
        default:
            break;
    }
     
     return ESP_OK;

}

int IO::get(uint8_t pin)
{
   return gpio_get_level((gpio_num_t)pin);
}

void  IO::setIntr(uint8_t pin , gpio_isr_t handle )
{

    gpio_set_intr_type((gpio_num_t)pin,GPIO_INTR_NEGEDGE);
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);
    gpio_isr_handler_add((gpio_num_t)pin,handle,NULL);

}

esp_err_t IO::on(uint8_t pin)
{
    return gpio_set_level((gpio_num_t)pin,1);
}

esp_err_t IO::off(uint8_t pin)
{
    return gpio_set_level((gpio_num_t)pin,0);
}