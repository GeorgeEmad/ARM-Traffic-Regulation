#include <stdint.h>
#include <stdbool.h>
#include "bitwise_operation.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_timer.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "tm4c123gh6pm.h"
#include "timer_int.h"
#include "GPIO.h"


//function to initialize timer0A
void Timer0A_Init(int time){
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)){}

  TimerDisable(TIMER0_BASE, TIMER_BOTH);
  TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC); //determine timer mode
  TimerLoadSet(TIMER0_BASE, TIMER_A,16000*time-1);  // load value
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;
  TimerIntRegister(TIMER0_BASE, TIMER_A, TimerA_ISR);
  TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  TimerEnable(TIMER0_BASE, TIMER_A);

}

void WIDETimer0A_Init(int time){
  SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER0)){
   }
  TimerDisable(WTIMER0_BASE, TIMER_BOTH);
  TimerConfigure(WTIMER0_BASE, TIMER_CFG_A_PERIODIC); //determine timer mode
  TimerLoadSet(WTIMER0_BASE, TIMER_A,16000*time-1);  // load value
  WTIMER0_ICR_R = TIMER_ICR_TATOCINT;
  TimerIntRegister(WTIMER0_BASE, TIMER_A, TIMER_P1_Handler);
  Timer_reset_counter=16000*time-1;
//  IntPrioritySet(INT_GPIOF, 0xE0);
}


void TimerA_ISR(void){
    // Cars traffic
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;
    static int counter = 0;
    static int flag = 0;
    counter++;
    if(counter == 5 && flag ==0){ // the system stops the green light of traffic 1 and enables the yellow light after 5 seconds
        GPIO_PORTA_DATA_BITS_R[LED_GREEN_T1] = OFF;
        GPIO_PORTA_DATA_BITS_R[LED_YELLOW_T1] = LED_YELLOW_T1;
    }
    else if(counter == 7 && flag ==0){ // the system stops the Yellow light of traffic 1 and enables the red light after 7 seconds (5 for green & 2 for yellow)
        GPIO_PORTA_DATA_BITS_R[LED_YELLOW_T1] = OFF;
        GPIO_PORTA_DATA_BITS_R[LED_RED_T1] = LED_RED_T1;
    }
    else if(counter == 8 && flag ==0){  // the system stops the red light of traffic 1 and enables the green light of traffic 2
        GPIO_PORTE_DATA_BITS_R[LED_RED_T2] = OFF;
        GPIO_PORTE_DATA_BITS_R[LED_GREEN_T2] = LED_GREEN_T2;
        counter = 0;
        flag=1; // when flag is equal to 1, this means we start working now on traffic 2
    }
    else if(counter == 5 && flag ==1){ // the system stops the green light of traffic 2 and enables the yellow light of traffic 2
        GPIO_PORTE_DATA_BITS_R[LED_GREEN_T2] = OFF;
        GPIO_PORTE_DATA_BITS_R[LED_YELLOW_T2] = LED_YELLOW_T2;
    }
    else if(counter == 7 && flag ==1){ // the system stops the yellow light of traffic 2 and enables the red light of traffic 2
        GPIO_PORTE_DATA_BITS_R[LED_YELLOW_T2] = OFF;
        GPIO_PORTE_DATA_BITS_R[LED_RED_T2] = LED_RED_T2;
     }
     else if(counter == 8 && flag ==1){ //after 1 second the sequence of the traffic light is repeated
        GPIO_PORTE_DATA_BITS_R[LED_RED_T2] = OFF;
        GPIO_PORTA_DATA_BITS_R[LED_GREEN_T1] = LED_GREEN_T1;
        counter = 0;
        flag = 0;
        traffic_init();
     }
}

void traffic_init(void){
    GPIO_PORTA_DATA_BITS_R[LED_RED_T1 | LED_YELLOW_T1] = OFF;
    GPIO_PORTA_DATA_BITS_R[LED_GREEN_T1] = LED_GREEN_T1;
    GPIO_PORTE_DATA_BITS_R[LED_GREEN_T2 | LED_YELLOW_T2] = OFF;
    GPIO_PORTE_DATA_BITS_R[LED_RED_T2] = LED_RED_T2;

    GPIO_PORTA_DATA_BITS_R[LED_RED_P1] = LED_RED_P1;
    GPIO_PORTA_DATA_BITS_R[LED_GREEN_P1] = OFF;
    GPIO_PORTD_DATA_BITS_R[LED_RED_P2] = LED_RED_P2;
    GPIO_PORTD_DATA_BITS_R[LED_GREEN_P2] = OFF;

}

void TIMER_P1_Handler(void)
{
    WTIMER0_ICR_R  = TIMER_ICR_TATOCINT;
    FLAG_GPIO_Handler = 0;
    GPIO_PORTA_DATA_BITS_R[LED_RED_P1] = LED_RED_P1;
    GPIO_PORTA_DATA_BITS_R[LED_GREEN_P1] = OFF;

    GPIO_PORTD_DATA_BITS_R[LED_RED_P2] = LED_RED_P2;
    GPIO_PORTD_DATA_BITS_R[LED_GREEN_P2] = OFF;
    TimerDisable(WTIMER0_BASE, TIMER_BOTH);

    if(Waiting== PUSH_1_delayed || Waiting== PUSH_2_delayed)
    {
      if(Waiting== PUSH_1_delayed){
          GPIO_PORTA_DATA_BITS_R[LED_RED_P1] = OFF;
          GPIO_PORTA_DATA_BITS_R[LED_GREEN_P1] = LED_GREEN_P1;
      }
      else if(Waiting== PUSH_2_delayed){
          GPIO_PORTD_DATA_BITS_R[LED_RED_P2] = OFF;
          GPIO_PORTD_DATA_BITS_R[LED_GREEN_P2] = LED_GREEN_P2;
      }

      WTIMER0_TAV_R=Timer_reset_counter;
      TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT);
      TimerEnable(WTIMER0_BASE, TIMER_A);
      Waiting= NO_delay;
    }
    else if(Waiting == NO_delay)
    {
        DIO_WritePin(PORT_A,PIN5,PA[0]);
        DIO_WritePin(PORT_A,PIN6,PA[1]);
        DIO_WritePin(PORT_A,PIN7,PA[2]);

        DIO_WritePin(PORT_E,PIN1,PE[0]);
        DIO_WritePin(PORT_E,PIN2,PE[1]);
        DIO_WritePin(PORT_E,PIN3,PE[2]);
        TimerEnable(TIMER0_BASE, TIMER_A);
    }
}


void GPIOF_Handler()
{
        GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
        Waiting= PUSH_1_delayed;
        double GetTimerValue=TimerValueGet64(WTIMER0_BASE);
        double totTimer=(Timer_reset_counter/2);

        if( GetTimerValue >= totTimer)// TIMER is counting down so GetTimerValue >= totTimer means that 1 second has not passed yet
        {
            TimerDisable(TIMER0_BASE, TIMER_BOTH);
            Waiting= NO_delay;

            if(FLAG_GPIO_Handler == 0)
            {
                FLAG_GPIO_Handler = 1;
                PA[0] = DIO_ReadPin(PORT_A,PIN5);
                PA[1] = DIO_ReadPin(PORT_A,PIN6);
                PA[2] = DIO_ReadPin(PORT_A,PIN7);
                GPIO_PORTA_DATA_BITS_R[LED_GREEN_T1 | LED_YELLOW_T1] = OFF;
                GPIO_PORTA_DATA_BITS_R[LED_RED_T1] = LED_RED_T1;

                PE[0] = DIO_ReadPin(PORT_E,PIN1);
                PE[1] = DIO_ReadPin(PORT_E,PIN2);
                PE[2] = DIO_ReadPin(PORT_E,PIN3);
                GPIO_PORTE_DATA_BITS_R[LED_GREEN_T2 | LED_YELLOW_T2] = OFF;
                GPIO_PORTE_DATA_BITS_R[LED_RED_T2] = LED_RED_T2;
            }
            GPIO_PORTA_DATA_BITS_R[LED_RED_P1] = OFF;
            GPIO_PORTA_DATA_BITS_R[LED_GREEN_P1] = LED_GREEN_P1;

            WTIMER0_TAV_R=Timer_reset_counter;
            TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT);
            TimerEnable(WTIMER0_BASE, TIMER_A);
        }
}

void GPIOA_Handler()
{
        GPIOIntClear(GPIO_PORTA_BASE, GPIO_INT_PIN_2);
        Waiting= PUSH_2_delayed;

        double GetTimerValue=TimerValueGet64(WTIMER0_BASE);
        double totTimer=(Timer_reset_counter/2);
        if( GetTimerValue >= totTimer)
        {
        TimerDisable(TIMER0_BASE, TIMER_BOTH);
        Waiting= NO_delay;

        if(FLAG_GPIO_Handler == 0){
            FLAG_GPIO_Handler = 1;
            PA[0] = DIO_ReadPin(PORT_A,PIN5);
            PA[1] = DIO_ReadPin(PORT_A,PIN6);
            PA[2] = DIO_ReadPin(PORT_A,PIN7);
            GPIO_PORTA_DATA_BITS_R[LED_GREEN_T1 | LED_YELLOW_T1] = OFF;
            GPIO_PORTA_DATA_BITS_R[LED_RED_T1] = LED_RED_T1;

            PE[0] = DIO_ReadPin(PORT_E,PIN1);
            PE[1] = DIO_ReadPin(PORT_E,PIN2);
            PE[2] = DIO_ReadPin(PORT_E,PIN3);
            GPIO_PORTE_DATA_BITS_R[LED_GREEN_T2 | LED_YELLOW_T2] = OFF;
            GPIO_PORTE_DATA_BITS_R[LED_RED_T2] = LED_RED_T2;
       }
        GPIO_PORTD_DATA_BITS_R[LED_RED_P2] = OFF;
        GPIO_PORTD_DATA_BITS_R[LED_GREEN_P2] = LED_GREEN_P2;

        WTIMER0_TAV_R=Timer_reset_counter;
        TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT);
        TimerEnable(WTIMER0_BASE, TIMER_A);
        }
}


