#include "mqtt.h"


MQTT::MQTT(const char * url)
{
    esp_mqtt_client_config_t cfg;
    cfg.event_handle=handler;
    cfg.host="192.168.1.17";
    cfg.uri=url;
    cfg.port=1883;
    cfg.client_id=NULL;
    cfg.username=NULL;
    cfg.password=NULL;
    cfg.lwt_topic=NULL;
    cfg.lwt_msg=NULL;
    cfg.lwt_qos=1;
    cfg.lwt_retain=0;
    cfg.lwt_msg_len=256;
    cfg.disable_clean_session=1;
    cfg.keepalive=120;
    cfg.disable_auto_reconnect=0;
    cfg.user_context=NULL;
    cfg.task_prio=5;
    cfg.task_stack=6144*2;
    cfg.buffer_size=2048;
    cfg.cert_pem=NULL;
    cfg.client_cert_pem=NULL;
    cfg.client_key_pem=NULL;
    cfg.transport=MQTT_TRANSPORT_OVER_TCP;
    //cfg.refresh_connection_after_ms=10;

   // esp_logi("mqtt","username %s",cfg.username);

   client=esp_mqtt_client_init(&cfg);
    
}


void MQTT::subscribe(const char* topic)
{

}


void MQTT::publish(const char * topic, const char* mess)
{

}


esp_err_t MQTT::handler(esp_mqtt_event_handle_t event)
{
   esp_mqtt_client_handle_t client = event->client;
   switch(event->event_id)
   {
       case MQTT_EVENT_CONNECTED:
       ESP_LOGI("MQTT","connected");
       esp_mqtt_client_subscribe(client,"0",1);
       esp_mqtt_client_publish(client,"0","hi from esp 32",15,2,0);
       break;
       case MQTT_EVENT_DATA:
       ESP_LOGI("mqtt","length : %d , topic %s",event->topic_len,event->topic);
       ESP_LOGI("mqtt","length : %d , data %s",event->data_len,event->data);
       default:
       break;
   }

   return ESP_OK;
}

esp_err_t MQTT::start()
{
   return  esp_mqtt_client_start(client);
}