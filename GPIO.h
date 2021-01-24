#ifndef GPIO_H
#define GPIO_H


/**************** Typedefs , declarations and definitions ***************/

#define UNLOCK 0x4C4F434B

/* PORT datatype */
typedef enum
{
  PORT_A,
  PORT_B,
  PORT_C,
  PORT_D,
  PORT_E,
  PORT_F
  
}Portx_t;

/* PIN datatype */
typedef enum
{
  PIN0,
  PIN1,
  PIN2,
  PIN3,
  PIN4,
  PIN5,
  PIN6,
  PIN7
  
}Pinx_t;

typedef enum
{
  LOW,
  HIGH
    
}State_t;

/* Function prototypes */
void DIO_WritePin(Portx_t port,Pinx_t pin,State_t state);
State_t DIO_ReadPin(Portx_t port,Pinx_t pin);
void DIO_init(void);
void __attribute__((weak)) GPIOA_Handler();
void __attribute__((weak)) GPIOB_Handler();
void __attribute__((weak)) GPIOC_Handler();
void __attribute__((weak)) GPIOD_Handler();
void __attribute__((weak)) GPIOE_Handler();
void __attribute__((weak)) GPIOF_Handler();

#endif
