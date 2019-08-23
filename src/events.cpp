#include "events.h"

Events::Events(bool u,event_type base){
    user=u;
   if(base == WIFI)
   {
       ESP_EVENT_DEFINE_BASE(WIFI_EVENT);
       base_id = WIFI_EVENT;

   }
   else if(base==IP)
   {
       ESP_EVENT_DEFINE_BASE(IP_EVENT);
       base_id = IP_EVENT;
   }


    
    if(user==1)
    {
        
        esp_event_loop_args_t loop_args = {
            .queue_size = 3,
            .task_name = "user_loop", // task will be created
            .task_priority = uxTaskPriorityGet(NULL),
            .task_stack_size = 2048,
            .task_core_id = tskNO_AFFINITY
        };
        
        esp_event_loop_create(&loop_args,&loop_handle);
    }

  
    

}

void Events::on(int32_t event , esp_event_handler_t handler)
{   
    
    if(user==1)
    {
        esp_event_handler_register_with(loop_handle,base_id,event,handler,NULL);
    }

    else ESP_ERROR_CHECK(esp_event_handler_register(base_id,event,handler,NULL));
}


