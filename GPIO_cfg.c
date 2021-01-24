#include "GPIO.h"
#include <stdint.h>
#include "GPIO_cfg.h"

/* Array contains all I/O configurations */
PinConfig_t PinConfigs[] = 
                          {
                           {PORT_A,PIN5,OUTPUT},
                           {PORT_A,PIN6,OUTPUT},
                           {PORT_A,PIN7,OUTPUT},
                           {PORT_E,PIN1,OUTPUT},
                           {PORT_E,PIN2,OUTPUT},
                           {PORT_E,PIN3,OUTPUT},

                           {PORT_A,PIN3,OUTPUT},
                           {PORT_A,PIN4,OUTPUT},
                           {PORT_D,PIN6,OUTPUT},
                           {PORT_D,PIN7,OUTPUT},

                           {PORT_A,PIN2,INPUT,PUR_YES,INT_YES},
                           {PORT_F,PIN4,INPUT,PUR_YES,INT_YES}
                          };

/* Number of configurations  */
uint16_t PinConfigCount = sizeof(PinConfigs)/sizeof(PinConfig_t);
