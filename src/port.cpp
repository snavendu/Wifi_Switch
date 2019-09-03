#include "port.h"

IO_2::IO_2(){
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = sda;
    conf.scl_io_num = scl;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed=100000;
    ESP_ERROR_CHECK(i2c_param_config((i2c_port_t)0, &conf));
    ESP_ERROR_CHECK(i2c_driver_install((i2c_port_t)0, I2C_MODE_MASTER,0,0,0));
}

void IO_2::set(uint8_t addr , uint8_t val)
{
    uint8_t opcode = 0x20<<1;
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd,opcode,1);
    i2c_master_write_byte(cmd,addr,1);
    i2c_master_write_byte(cmd,val,1);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin((i2c_port_t)0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

}

uint8_t* IO_2::get(uint8_t addr)
{
    uint8_t* data;
    uint8_t opcode = (0x20<<1) + 1;
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd,opcode,1);
    i2c_master_write_byte(cmd,addr,1);
    // i2c_master_read(cmd,data,size-1,I2C_MASTER_ACK);
    // i2c_master_read(cmd,data,1,I2C_MASTER_NACK);
    i2c_master_read_byte(cmd,data,I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin((i2c_port_t)0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return data;
}

void IO_2::setMode(uint8_t pin,dir_t dir)
{   
    uint8_t addr;
//we have to check weather its gpioa or gpiob
    if(pin>7)
    {   
        pin = pin % 8;
        set(REG_IODIRA,dir<<pin);
        if(dir==IN)
        {
            set(REG_GPPUA,1<<pin);
        }
    }

    else if(pin<=7)
    {
        set(REG_IODIRB,dir<<pin);
        if(dir==IN)
        {
            set(REG_GPPUB,1<<pin);
        }

    }
}


void IO_2::on(uint8_t pin)
{
    if(pin>7)
    {
        pin = pin % 8;
        set(REG_OLATA,1<<pin);
    }
    else if(pin<=7)
    {
        set(REG_OLATB,1<<pin);
    }
}

void IO_2::off(uint8_t pin)
{
       if(pin>7)
    {
        pin = pin % 8;
        set(REG_OLATA,0<<pin);
    }
    else if(pin<=7)
    {
        set(REG_OLATB,0<<pin);
    }

}



