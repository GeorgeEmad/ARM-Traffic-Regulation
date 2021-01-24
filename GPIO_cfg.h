#ifndef DIO_CFG_H
#define DIO_CFG_H

/**************** Typedefs , declarations and definitions ***************/

/* Direction datatype */
typedef enum
{
  INPUT,
  OUTPUT
  
}PinDir_t;

typedef enum
{
  PUR_NO,
  PUR_YES
  
}Pur_t;

typedef enum
{
  INT_NO,
  INT_YES

}Int_t;

/* PIN configuration datatype */
typedef struct
{
  Portx_t port;
  Pinx_t pin;
  PinDir_t direction;
  Pur_t pur;
  Int_t ints;

}PinConfig_t;


extern PinConfig_t PinConfigs[];
extern uint16_t PinConfigCount;

#endif
