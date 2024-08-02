#include "hal/gpio_types.h"

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <driver/gpio.h>

#include "freertos/FreeRTOS.h"
//include "freertos/task.h"
//#include <freertos/queue.h>

#define key_1  GPIO_NUM_12
#define key_2  GPIO_NUM_13
#define key_3  GPIO_NUM_14
#define led_2   GPIO_NUM_2
#define led_15  GPIO_NUM_15
#define led_4   GPIO_NUM_4

//QueueHandle_t gpio_evt_queue = NULL;
static int k1_on_off=0;

static void  IRAM_ATTR  int_key_1(void* arg)
{ gpio_intr_disable(key_1); 
  k1_on_off=1;
   {gpio_set_level(led_15,  !1);}
   {gpio_set_level(led_4 ,  !0);}
   {gpio_set_level(led_2 ,  !0);}
   
//uint32_t gpio_n = (uint32_t) arg;
  //   xQueueSendFromISR(gpio_evt_queue, &gpio_n, NULL);
gpio_intr_enable(key_1);     
}////////   //////////  /////////

static void  IRAM_ATTR int_key_2(void* arg)
{gpio_intr_disable(key_2);    
  k1_on_off=2;
   {gpio_set_level(led_15,  !0);}
   {gpio_set_level(led_4 ,  !1);}
   {gpio_set_level(led_2 ,  !0);}
   
  //  uint32_t gpio_n = (uint32_t) arg;
  //   xQueueSendFromISR(gpio_evt_queue, &gpio_n, NULL);
gpio_intr_enable(key_2);  	 
}////////   //////////  /////////

static void  IRAM_ATTR int_key_3(void* arg)
{ gpio_intr_disable(key_3);
  k1_on_off=3;
   {gpio_set_level(led_15,  !0);}
   {gpio_set_level(led_4 ,  !0);}
   {gpio_set_level(led_2 ,  !1);}
   
 //   uint32_t gpio_n = (uint32_t) arg;
  //   xQueueSendFromISR(gpio_evt_queue, &gpio_n, NULL);	 
gpio_intr_enable(key_3);	
}////////   //////////  /////////



void cfg_inp(void)///////////////////////////////////////////
{ gpio_reset_pin( key_1); 
  gpio_set_direction( key_1,  GPIO_MODE_INPUT); 
  gpio_set_pull_mode( key_1,  GPIO_PULLUP_ONLY);
    
  gpio_reset_pin(key_2);  
  gpio_set_direction( key_2,  GPIO_MODE_INPUT );  
  gpio_set_pull_mode( key_2,  GPIO_PULLUP_ONLY);

  gpio_reset_pin(key_3);  
  gpio_set_direction( key_3,  GPIO_MODE_INPUT );  
  gpio_set_pull_mode( key_3,  GPIO_PULLUP_ONLY); 	
}///////////////////////////////

void cfg_out(void)
{ gpio_reset_pin(led_2);  
  gpio_set_direction( led_2,  GPIO_MODE_OUTPUT  );  
  gpio_set_pull_mode( led_2,  GPIO_FLOATING);
  
  gpio_reset_pin(led_4);  
  gpio_set_direction( led_4,  GPIO_MODE_OUTPUT  );  
  gpio_set_pull_mode( led_4,  GPIO_FLOATING);

  gpio_reset_pin(led_15);  
  gpio_set_direction( led_15,  GPIO_MODE_OUTPUT  );  
  gpio_set_pull_mode( led_15,  GPIO_FLOATING);  
 	
}/////////////////////////////////------------------------------------------------

//static void task1(void* arg)
//{    uint32_t io_n;
//   for(;;) {
//        if(xQueueReceive(gpio_evt_queue, &io_n, portMAX_DELAY)) {
//            printf("= %d GPIO[%ld] intr, val: %d\n", k1_on_off, io_n, gpio_get_level(io_n));
//              sleep(1); //задержка       
//        }
//    }
//}////////////////////////////
void cfg_int_inp|(void)
{  gpio_set_intr_type(key_1, GPIO_INTR_ANYEDGE  );  
   gpio_set_intr_type(key_2, GPIO_INTR_ANYEDGE  );  
   gpio_set_intr_type(key_3, GPIO_INTR_ANYEDGE  );  

 esp_err_t err = gpio_install_isr_service(0);
 if (err == ESP_ERR_INVALID_STATE) 
     { printf( "GPIO isr service already installed"); };   
     gpio_isr_handler_add(key_1, int_key_1, (void *)key_1); 
     gpio_isr_handler_add(key_2, int_key_2, (void *)key_2);
     gpio_isr_handler_add(key_3, int_key_3, (void *)key_3);                 
     gpio_intr_enable(key_1);  
     gpio_intr_enable(key_2);   
     gpio_intr_enable(key_3);
 	
}///////////////////////////////////////
//------------------------------------------------
void app_main(void) /////////////////////////   
{   cfg_inp(); cfg_out(); uint8_t t=0; uint8_t clk=0;  
  
// gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t));
//    xTaskCreate(task1, "task1", 2048, NULL, 10, NULL);
     
 
while (1) {    printf("Hello from app_main!\n %d , clk = %d k1= %d k2=%d k3=%d int=%d \n", t, clk, 
                          gpio_get_level(key_1),
                          gpio_get_level(key_2),
                          gpio_get_level(key_3),
                          k1_on_off
                          );
 
//    clk++; if (clk>10) clk=0;			   //--задаёт условие мигания  двух светодиодов--
//if (t==0  )  {t=1; } else {t=0;}  //--задаёт условие мигания  светодиода--
// if (k1_on_off==0) { //если не была нажата кнопа           
//               gpio_set_level(led_2,  t);         
//   if (clk<5){ gpio_set_level(led_15,  !t);} else {gpio_set_level(led_15,  !0);}
//   if (clk>5){ gpio_set_level(led_4,  !t); } else {gpio_set_level(led_4 ,  !0);}
//   }               
      sleep(1); //задержка       
 //if (k1_on_off>0)  //если была нажата кнопа
//    { if (k1_on_off==1)    gpio_intr_enable(key_1);
//      if (k1_on_off==2)    gpio_intr_enable(key_2);
//      if (k1_on_off==3)    gpio_intr_enable(key_3);         
//          k1_on_off=0; 
//    } 
          

  }
}
