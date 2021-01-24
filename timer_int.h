#ifndef TIMER_INT_H
#define TIMER_INT_H

#include "GPIO.h"
// Defined to increase readability of our code (T1--> Traffic 1 south to north ~ T2 --> Traffic 2 east to west ~ P --> pedestrians )
#define LED_GREEN_T1   (1U << 5)
#define LED_YELLOW_T1  (1U << 6)
#define LED_RED_T1     (1U << 7)

#define LED_GREEN_T2   (1U << 1)
#define LED_YELLOW_T2  (1U << 2)
#define LED_RED_T2     (1U << 3)

#define LED_GREEN_P1   (1U << 4)
#define LED_RED_P1     (1U << 3)
#define OFF            (0x00)
#define LED_GREEN_P2   (1U << 6)
#define LED_RED_P2     (1U << 7)

State_t PA[3];
State_t PE[3];

typedef enum
{
    NO_delay,
    PUSH_1_delayed,
    PUSH_2_delayed
}PUSH_delayed;

int FLAG_GPIO_Handler;
int Timer_reset_counter;
PUSH_delayed Waiting;

void Timer0A_Init(int);
void WIDETimer0A_Init(int);
void TIMER_P1_Handler(void);
void TimerA_ISR(void);
void traffic_init(void);
void GPIO_PUSH1_init(void);
void GPIO_PUSH2_init(void);



#endif
