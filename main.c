#include "tm4c123gh6pm.h"
#include "dio.h"
#include "bitwise_operation.h"
#include "stdio.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"

void TIMER0A_INT(unsigned int);
void GPIOI_INT(void);
volatile unsigned int counter = 1;
volatile unsigned int counter2 = 0;
volatile unsigned int counter_previous = 0;
volatile unsigned int counter2_previous = 0;
volatile unsigned int current_time = 0;
void TIMERA_DElAYMS(unsigned int);

int main()
{
  DIO_Init(PortB,Bit2,OUTPUT); // traffic light1 green light 
  DIO_Init(PortB,Bit0,OUTPUT); // traffic light1 yellow light 
  DIO_Init(PortB,Bit1,OUTPUT); // traffic light1 red light 
  DIO_Init(PortD,Bit3,OUTPUT); //traffic light2 red light 
  DIO_Init(PortD,Bit0,OUTPUT); //traffic light2 green light 
  DIO_Init(PortD,Bit1,OUTPUT); //traffic light2 yellow light 
  DIO_Init(PortE,Bit1,OUTPUT); // pedestrian traffic light1 green light
  DIO_Init(PortE,Bit2,OUTPUT); // pedestrian traffic light1 red light
  DIO_Init(PortE,Bit4,OUTPUT); // pedestrian traffic light2 green light
  DIO_Init(PortE,Bit5,OUTPUT); // pedestrian traffic light2 red light
  DIO_Init(PortF,Bit4,INPUT); // pedestrian traffic light1 interrupt
  DIO_Init(PortF,Bit0,INPUT); // pedestrian traffic light2 interrupt
  GPIOI_INT();
  
  while (1)
  {
    if (counter_previous != counter)
    {
     switch (counter){
     case(1):
        DIO_WritePin(PortB,Bit1,LOW);
        DIO_WritePin(PortF,Bit2,LOW);
        DIO_WritePin(PortE,Bit1,LOW);
        DIO_WritePin(PortE,Bit2,HIGH);
        DIO_WritePin(PortB,Bit2,HIGH);
        TIMER0A_INT(5);
         break;
     case (2):
        DIO_WritePin(PortB,Bit2,LOW);
        DIO_WritePin(PortF,Bit2,LOW);
        DIO_WritePin(PortB,Bit0,HIGH);
        TIMER0A_INT(2);
        break;
     case (3):
       DIO_WritePin(PortD,Bit3,LOW);
        DIO_WritePin(PortB,Bit2,LOW);
        DIO_WritePin(PortF,Bit2,LOW);
        DIO_WritePin(PortB,Bit0,LOW);
        DIO_WritePin(PortE,Bit2,LOW);
        DIO_WritePin(PortB,Bit1,HIGH);
        DIO_WritePin(PortE,Bit1,HIGH);
        TIMER0A_INT(1);
        break;
    }
    }
    if ( counter2_previous != counter2)
    {
     switch (counter2){
     case(1):
        DIO_WritePin(PortD,Bit3,LOW);
        DIO_WritePin(PortF,Bit2,LOW);
        DIO_WritePin(PortE,Bit4,LOW);
        DIO_WritePin(PortE,Bit5,HIGH);
        DIO_WritePin(PortD,Bit0,HIGH);
        TIMER0A_INT(5);
        break;
     case (2):
        DIO_WritePin(PortD,Bit0,LOW);
        DIO_WritePin(PortF,Bit2,LOW);
        DIO_WritePin(PortD,Bit1,HIGH);
        TIMER0A_INT(2);
        break;
     case (3):
        DIO_WritePin(PortB,Bit1,LOW);
        DIO_WritePin(PortD,Bit0,LOW);
        DIO_WritePin(PortF,Bit2,LOW);
        DIO_WritePin(PortD,Bit1,LOW);
        DIO_WritePin(PortE,Bit5,LOW);
        DIO_WritePin(PortE,Bit4,HIGH);
        DIO_WritePin(PortD,Bit3,HIGH);
        TIMER0A_INT(1);
        break;
    }
    }
    
  }
  
  return 0;
}

void GPIOPF_Handler(void)
{
  GPIO_PORTF_ICR_R = 0x11;
  if (counter == 1)
  {
        current_time = TimerValueGet(TIMER0_BASE,TIMER_A);      
        DIO_WritePin(PortB,Bit1,LOW);
        DIO_WritePin(PortE,Bit2,LOW);
        DIO_WritePin(PortB,Bit2,LOW);
        DIO_WritePin(PortE,Bit1,HIGH);
        DIO_WritePin(PortB,Bit1,HIGH);
        TIMERA_DElAYMS(5000);
        DIO_WritePin(PortE,Bit1,LOW);
        DIO_WritePin(PortB,Bit1,LOW);
        DIO_WritePin(PortB,Bit2,HIGH);
        DIO_WritePin(PortE,Bit2,HIGH);
        TIMERA_DElAYMS(current_time/16000);
        counter = 1;
           if (counter2 == 1)
  {
        current_time = TimerValueGet(TIMER0_BASE,TIMER_A);
        DIO_WritePin(PortD,Bit0,LOW);
        DIO_WritePin(PortE,Bit5,LOW);
        DIO_WritePin(PortE,Bit4,HIGH);
        DIO_WritePin(PortD,Bit3,HIGH);
        TIMERA_DElAYMS(5000);
        DIO_WritePin(PortE,Bit4,LOW);
        DIO_WritePin(PortD,Bit3,LOW);
        DIO_WritePin(PortE,Bit5,HIGH);
        DIO_WritePin(PortD,Bit0,HIGH);
        TIMERA_DElAYMS(current_time/16000);
        counter2 = 1;
  }
  }
  
}

void TIMERA0_Handler()
{
    TIMER0_ICR_R = 0X01;
    if (counter2 == 0)
    {
    switch (counter){
     case(1):
       DIO_WritePin(PortB,Bit1,LOW);
        DIO_WritePin(PortB,Bit2,LOW);
        counter++;
        break;
     case (2):
        DIO_WritePin(PortB,Bit2,LOW);
        DIO_WritePin(PortB,Bit0,LOW);
        counter++;
        break;
     case (3):
        DIO_WritePin(PortB,Bit2,LOW);
        DIO_WritePin(PortB,Bit0,LOW);
        DIO_WritePin(PortB,Bit1,HIGH);
        counter2 = 1;
        break;
    }
    }
   else if ( counter2 != 0)
    {
     switch (counter2){
     case(1):
       DIO_WritePin(PortD,Bit3,LOW);
        DIO_WritePin(PortD,Bit0,LOW);
        counter2++;
        break;
     case (2):
        DIO_WritePin(PortD,Bit0,LOW);
        DIO_WritePin(PortF,Bit2,LOW);
        DIO_WritePin(PortD,Bit1,LOW);
        counter2++;
        break;
     case (3):
        DIO_WritePin(PortD,Bit0,LOW);
        DIO_WritePin(PortD,Bit1,LOW);
        DIO_WritePin(PortD,Bit3,HIGH);
        counter = 1;
        counter2 = 0;
        break;
    }
    }
}
void TIMER0A_INT(unsigned int time)
{
  SYSCTL_RCGCTIMER_R |= 0x01; 
  TIMER0_CTL_R = 0x0;
  TIMER0_CFG_R = 0x0;
  TIMER0_TAMR_R = 0x02;
  TIMER0_CTL_R |= 0x03;
  TIMER0_ICR_R = 0X01;
  TIMER0_TAILR_R = 16000000*time -1;
  TIMER0_IMR_R = 0X01;
  NVIC_EN0_R = 1 << 19;
  counter_previous = counter;
  counter2_previous = counter2;
  
}
void GPIOI_INT(void)
{
    GPIO_PORTF_IS_R = 0x0 ;
    GPIO_PORTF_IBE_R =0x0;
    GPIO_PORTF_IEV_R = 0x0;
    GPIO_PORTF_ICR_R = 0X11;
    Set_Bit(GPIO_PORTF_IM_R,Bit4);
    Set_Bit(GPIO_PORTF_IM_R,Bit0);
    NVIC_EN0_R = 1 << 30 ;
}
void TIMERA_DElAYMS(unsigned int time)
{
  TIMER0_CTL_R = 0x0;
  TIMER0_TAILR_R = 16000*time -1;
  TIMER0_ICR_R = 0x01;
  TIMER0_CTL_R |= 0x03;
  while(Get_Bit(TIMER0_RIS_R,Bit0) == 0);
}
 