#ifndef PORT_H
#define PORT_H

#include "driver/i2c.h"
#include "driver/gpio.h"
#include <stdio.h>


#define REG_IODIRA   0x00
#define REG_IODIRB   0x01
#define REG_IPOLA    0x02
#define REG_IPOLB    0x03
#define REG_GPINTENA 0x04
#define REG_GPINTENB 0x05
#define REG_DEFVALA  0x06
#define REG_DEFVALB  0x07
#define REG_INTCONA  0x08
#define REG_INTCONB  0x09
#define REG_IOCON    0x0A
#define REG_GPPUA    0x0C
#define REG_GPPUB    0x0D
#define REG_INTFA    0x0E
#define REG_INTFB    0x0F
#define REG_INTCAPA  0x10
#define REG_INTCAPB  0x11
#define REG_GPIOA    0x12
#define REG_GPIOB    0x13
#define REG_OLATA    0x14
#define REG_OLATB    0x15


typedef enum{
    OUT,
    IN
}dir_t;

class IO_2{

public:
    IO_2();
    //it will set up all default values for corresponding direction
    //if the dir is for input then set pullup regster also
    void setMode(uint8_t,dir_t);
    void on(uint8_t);
    void off(uint8_t);
    void setInt(uint8_t);


private:
    gpio_num_t scl = GPIO_NUM_2;
    gpio_num_t sda = GPIO_NUM_4;
    i2c_cmd_handle_t cmd;
    i2c_config_t conf;
    void set(uint8_t addr , uint8_t val);
    uint8_t* get(uint8_t addr);

};

#endif