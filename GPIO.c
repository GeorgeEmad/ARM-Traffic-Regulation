#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "GPIO.h"
#include "GPIO_cfg.h"
#include "timer_int.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_timer.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

/* Function to write to I/O pins */
void DIO_WritePin(Portx_t port,Pinx_t pin,State_t state)
{
  /* Check which port the pin belongs to */
  switch(port)
  {
    case PORT_A:
    
      if( state == HIGH )
      {
        SET_BIT(GPIO_PORTA_DATA_R,pin);
      }
      else if( state == LOW )
      {
        CLR_BIT(GPIO_PORTA_DATA_R,pin);
      }  
      
      break;
    
    case PORT_B:
    
      if( state == HIGH )
      {
        SET_BIT(GPIO_PORTB_DATA_R,pin);
      }
      else if( state == LOW )
      {
        CLR_BIT(GPIO_PORTB_DATA_R,pin);
      } 
    
      break;
      
    case PORT_C:
    
      if( state == HIGH )
      {
        SET_BIT(GPIO_PORTC_DATA_R,pin);
      }
      else if( state == LOW )
      {
        CLR_BIT(GPIO_PORTC_DATA_R,pin);
      } 
    
      break;

    case PORT_D:
    
      if( state == HIGH )
      {
        SET_BIT(GPIO_PORTD_DATA_R,pin);
      }
      else if( state == LOW )
      {
        CLR_BIT(GPIO_PORTD_DATA_R,pin);
      }
    
      break; 
      
      case PORT_E:
    
      if( state == HIGH )
      {
        SET_BIT(GPIO_PORTE_DATA_R,pin);
      }
      else if( state == LOW )
      {
        CLR_BIT(GPIO_PORTE_DATA_R,pin);
      }
    
      break;
      
      case PORT_F:
    
      if( state == HIGH )
      {
        SET_BIT(GPIO_PORTF_DATA_R,pin);
      }
      else if( state == LOW )
      {
        CLR_BIT(GPIO_PORTF_DATA_R,pin);
      }
    
      break;
  }
}

/* Function to read from I/O pins */
State_t DIO_ReadPin(Portx_t port,Pinx_t pin)
{
  State_t val;
  
  /* Check which port the pin belongs to */
  switch(port)
  {
    case PORT_A:
    
      if( GET_BIT(GPIO_PORTA_DATA_R,pin) )
      {
        val = HIGH;
      }
      else
      {
        val = LOW;
      }  
      
      break;
    
    case PORT_B:
    
      if( GET_BIT(GPIO_PORTB_DATA_R,pin) )
      {
        val = HIGH;
      }
      else
      {
        val = LOW;
      }  
    
      break;
      
    case PORT_C:
    
      if( GET_BIT(GPIO_PORTC_DATA_R,pin) )
      {
        val = HIGH;
      }
      else
      {
        val = LOW;
      } 
    
      break;

    case PORT_D:
    
      if( GET_BIT(GPIO_PORTD_DATA_R,pin) )
      {
        val = HIGH;
      }
      else
      {
        val = LOW;
      } 
    
      break; 
      
      case PORT_E:
    
      if( GET_BIT(GPIO_PORTE_DATA_R,pin) )
      {
        val = HIGH;
      }
      else
      {
        val = LOW;
      } 
    
      break; 
      
      case PORT_F:
    
      if( GET_BIT(GPIO_PORTF_DATA_R,pin) )
      {
        val = HIGH;
      }
      else
      {
        val = LOW;
      } 
    
      break; 
  }
  
  return val;
}


/* Function to init DIO module and configure all pins */

void DIO_init(void){

   int i;

  /* Execute all configurations */
  for(i = 0;i < PinConfigCount; i++)
  {
    switch(PinConfigs[i].port)
    {
      case PORT_A:

        SET_BIT(SYSCTL_RCGCGPIO_R, PORT_A);
        while((SYSCTL_PRGPIO_R&0x00000001) == 0){};
        SET_BIT(GPIO_PORTA_CR_R, PinConfigs[i].pin);
        SET_BIT(GPIO_PORTA_DEN_R, PinConfigs[i].pin);
        GPIO_PORTA_LOCK_R = UNLOCK;

        if(PinConfigs[i].direction == OUTPUT)
        {
          SET_BIT(GPIO_PORTA_DIR_R, PinConfigs[i].pin);
        }
        else if(PinConfigs[i].direction == INPUT)
        {
          CLR_BIT(GPIO_PORTA_DIR_R, PinConfigs[i].pin);
          if(PinConfigs[i].pur == PUR_YES)
          {
          SET_BIT(GPIO_PORTA_PUR_R, PinConfigs[i].pin);
          }
          if(PinConfigs[i].ints == INT_YES)
          {
          int k=(1<<PinConfigs[i].pin);
          GPIOIntDisable(GPIO_PORTA_BASE, k);
          GPIOIntRegister(GPIO_PORTA_BASE, GPIOA_Handler);
          GPIOIntEnable(GPIO_PORTA_BASE, k);
          }
        }

        break;

      case PORT_B:

        SET_BIT(SYSCTL_RCGCGPIO_R, PORT_B);
        while((SYSCTL_PRGPIO_R&0x00000002) == 0){};
        SET_BIT(GPIO_PORTB_CR_R, PinConfigs[i].pin);
        SET_BIT(GPIO_PORTB_DEN_R, PinConfigs[i].pin);
        GPIO_PORTB_LOCK_R = UNLOCK;

        if(PinConfigs[i].direction == OUTPUT)
        {
          SET_BIT(GPIO_PORTB_DIR_R, PinConfigs[i].pin);
        }
        else if(PinConfigs[i].direction == INPUT)
        {
          CLR_BIT(GPIO_PORTB_DIR_R, PinConfigs[i].pin);
          if(PinConfigs[i].pur == PUR_YES)
          {
          SET_BIT(GPIO_PORTB_PUR_R, PinConfigs[i].pin);
          }
          if(PinConfigs[i].ints == INT_YES)
          {
          GPIOIntDisable(GPIO_PORTB_BASE, 1<<PinConfigs[i].pin);
          GPIOIntRegister(GPIO_PORTB_BASE, GPIOB_Handler);
          GPIOIntEnable(GPIO_PORTB_BASE, 1<<PinConfigs[i].pin);
          }
        }

        break;

      case PORT_C:

        SET_BIT(SYSCTL_RCGCGPIO_R, PORT_C);
        while((SYSCTL_PRGPIO_R&0x00000004) == 0){};
        SET_BIT(GPIO_PORTC_CR_R, PinConfigs[i].pin);
        SET_BIT(GPIO_PORTC_DEN_R, PinConfigs[i].pin);
        GPIO_PORTC_LOCK_R = UNLOCK;

        if(PinConfigs[i].direction == OUTPUT)
        {
          SET_BIT(GPIO_PORTC_DIR_R, PinConfigs[i].pin);
        }
        else if(PinConfigs[i].direction == INPUT)
        {
          CLR_BIT(GPIO_PORTC_DIR_R, PinConfigs[i].pin);
          if(PinConfigs[i].pur == PUR_YES)
          {
          SET_BIT(GPIO_PORTC_PUR_R, PinConfigs[i].pin);
          }
          if(PinConfigs[i].ints == INT_YES)
          {
          GPIOIntDisable(GPIO_PORTC_BASE, 1<<PinConfigs[i].pin);
          GPIOIntRegister(GPIO_PORTC_BASE, GPIOC_Handler);
          GPIOIntEnable(GPIO_PORTC_BASE, 1<<PinConfigs[i].pin);
          }
        }

        break;

      case PORT_D:

        SET_BIT(SYSCTL_RCGCGPIO_R, PORT_D);
         while((SYSCTL_PRGPIO_R&0x00000008) == 0){};
        SET_BIT(GPIO_PORTD_CR_R, PinConfigs[i].pin);
        SET_BIT(GPIO_PORTD_DEN_R, PinConfigs[i].pin);
        GPIO_PORTD_LOCK_R = UNLOCK;

        if(PinConfigs[i].direction == OUTPUT)
        {;
          SET_BIT(GPIO_PORTD_DIR_R, PinConfigs[i].pin);
        }
        else if(PinConfigs[i].direction == INPUT)
        {
          CLR_BIT(GPIO_PORTD_DIR_R, PinConfigs[i].pin);
          if(PinConfigs[i].pur == PUR_YES)
          {
          SET_BIT(GPIO_PORTD_PUR_R, PinConfigs[i].pin);
          }
          if(PinConfigs[i].ints == INT_YES)
          {
          GPIOIntDisable(GPIO_PORTD_BASE, 1<<PinConfigs[i].pin);
          GPIOIntRegister(GPIO_PORTD_BASE, GPIOD_Handler);
          GPIOIntEnable(GPIO_PORTD_BASE, 1<<PinConfigs[i].pin);
          }
        }

        break;
        case PORT_E:

        SET_BIT(SYSCTL_RCGCGPIO_R, PORT_E);
        while((SYSCTL_PRGPIO_R&0x00000010) == 0){};
        SET_BIT(GPIO_PORTE_CR_R, PinConfigs[i].pin);
        SET_BIT(GPIO_PORTE_DEN_R, PinConfigs[i].pin);
        GPIO_PORTE_LOCK_R = UNLOCK;

        if(PinConfigs[i].direction == OUTPUT)
        {
          SET_BIT(GPIO_PORTE_DIR_R, PinConfigs[i].pin);
        }
        else if(PinConfigs[i].direction == INPUT)
        {;
          CLR_BIT(GPIO_PORTE_DIR_R, PinConfigs[i].pin);
          if(PinConfigs[i].pur == PUR_YES)
          {
          SET_BIT(GPIO_PORTE_PUR_R, PinConfigs[i].pin);
          }
          if(PinConfigs[i].ints == INT_YES)
          {
          GPIOIntDisable(GPIO_PORTE_BASE, (1<<PinConfigs[i].pin));
          GPIOIntRegister(GPIO_PORTE_BASE, GPIOE_Handler);
          GPIOIntEnable(GPIO_PORTE_BASE, (1<<PinConfigs[i].pin));
          }
        }

        break;

        case PORT_F:

        SET_BIT(SYSCTL_RCGCGPIO_R, PORT_F);
        while((SYSCTL_PRGPIO_R&0x00000020) == 0){};
        SET_BIT(GPIO_PORTF_CR_R, PinConfigs[i].pin);
        SET_BIT(GPIO_PORTF_DEN_R, PinConfigs[i].pin);
        GPIO_PORTF_LOCK_R = UNLOCK;

        if(PinConfigs[i].direction == OUTPUT)
        {
          SET_BIT(GPIO_PORTF_DIR_R, PinConfigs[i].pin);
        }
        else if(PinConfigs[i].direction == INPUT)
        {
          CLR_BIT(GPIO_PORTF_DIR_R, PinConfigs[i].pin);
          if(PinConfigs[i].pur == PUR_YES)
          {
          SET_BIT(GPIO_PORTF_PUR_R, PinConfigs[i].pin);
          }
          if(PinConfigs[i].ints == INT_YES)
          {
              int k=(1<<PinConfigs[i].pin);
          GPIOIntDisable(GPIO_PORTF_BASE, k);
          GPIOIntRegister(GPIO_PORTF_BASE, GPIOF_Handler);
          GPIOIntEnable(GPIO_PORTF_BASE, k);
          }
        }

        break;
    }
  }

}

