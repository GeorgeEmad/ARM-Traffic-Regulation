#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_timer.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "timer_int.h"

int main()
{
   DIO_init();
   Timer0A_Init(1000);
   WIDETimer0A_Init(2000);
   traffic_init();
   while(1){

   }
  return 0;
}
