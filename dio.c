
#include "bitwise_operation.h"
#include "tm4c123gh6pm.h"
#include "dio.h"

void DIO_Init(uint8 Port, uint8 PinNo, uint8 Direction)
{
  if((Port<=PortF)&&(PinNo<=Bit7))
  {
          switch(Port)
          {
          case PortA:
            {
              Set_Bit(SYSCTL_RCGCGPIO_R,Bit0);
              while((SYSCTL_PRGPIO_R&0x00000001) == 0){};
              GPIO_PORTA_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTA_CR_R,PinNo);
              if(Direction==INPUT)
                {
                    Clear_Bit(GPIO_PORTA_DIR_R,PinNo);
                }
              else if(Direction==OUTPUT)
                {
                    Set_Bit(GPIO_PORTA_DIR_R,PinNo);
                }
                    Set_Bit(GPIO_PORTA_DEN_R,PinNo);
              break;
            }
          case PortB:
            {
              Set_Bit(SYSCTL_RCGCGPIO_R,Bit1);
              while((SYSCTL_PRGPIO_R&0x00000002) == 0){};
              GPIO_PORTB_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTB_CR_R,PinNo);
              if(Direction==INPUT)
                {
                    Clear_Bit(GPIO_PORTB_DIR_R,PinNo);
                }
              else if(Direction==OUTPUT)
                {
                    Set_Bit(GPIO_PORTB_DIR_R,PinNo);
                }
                    Set_Bit(GPIO_PORTB_DEN_R,PinNo);
              break;
            }
          case PortC:
            {
              Set_Bit(SYSCTL_RCGCGPIO_R,Bit2);
              while((SYSCTL_PRGPIO_R&0x00000004) == 0){};
              GPIO_PORTC_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTC_CR_R,PinNo);
              if(Direction==INPUT)
                {
                    Clear_Bit(GPIO_PORTC_DIR_R,PinNo);
                }
              else if(Direction==OUTPUT)
                {
                    Set_Bit(GPIO_PORTC_DIR_R,PinNo);
                }
                    Set_Bit(GPIO_PORTC_DEN_R,PinNo);
              break;
            }
          case PortD:
            {
              Set_Bit(SYSCTL_RCGCGPIO_R,Bit3);
              while((SYSCTL_PRGPIO_R&0x00000008) == 0){};
              GPIO_PORTD_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTD_CR_R,PinNo);
              if(Direction==INPUT)
                {
                    Clear_Bit(GPIO_PORTD_DIR_R,PinNo);
                }
              else if(Direction==OUTPUT)
                {
                    Set_Bit(GPIO_PORTD_DIR_R,PinNo);
                }
                    Set_Bit(GPIO_PORTD_DEN_R,PinNo);
              break;
            }
          case PortE:
            {
              Set_Bit(SYSCTL_RCGCGPIO_R,Bit4);
              while((SYSCTL_PRGPIO_R&0x00000010) == 0){};
              GPIO_PORTE_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTE_CR_R,PinNo);
              if(Direction==INPUT)
                {
                    Clear_Bit(GPIO_PORTE_DIR_R,PinNo);
                }
              else if(Direction==OUTPUT)
                {
                    Set_Bit(GPIO_PORTE_DIR_R,PinNo);
                }
                    Set_Bit(GPIO_PORTE_DEN_R,PinNo);
              break;
            }
          case PortF:
            {
              Set_Bit(SYSCTL_RCGCGPIO_R,Bit5);
              while((SYSCTL_PRGPIO_R&0x00000020) == 0){};
              GPIO_PORTF_LOCK_R = 0x4C4F434B;
              Set_Bit(GPIO_PORTF_CR_R,PinNo);
              if(Direction==INPUT)
                {
                    Clear_Bit(GPIO_PORTF_DIR_R,PinNo);
                }
              else if(Direction==OUTPUT)
                {
                    Set_Bit(GPIO_PORTF_DIR_R,PinNo);
                }
              if(PinNo==Bit0 || PinNo==Bit4)
              {
                    Set_Bit(GPIO_PORTF_PUR_R,PinNo);
              }

                    Set_Bit(GPIO_PORTF_DEN_R,PinNo);
              break;
            }
          }
  }
}
uint8 DIO_ReadPin(uint8 Port, uint8 PinNo)
{
	uint8 ret_value=0;
               switch(Port)
		{
		case PortA : ret_value = Get_Bit(GPIO_PORTA_DATA_R, PinNo);break;
		case PortB : ret_value = Get_Bit(GPIO_PORTB_DATA_R, PinNo);break;
		case PortC : ret_value = Get_Bit(GPIO_PORTC_DATA_R, PinNo);break;
		case PortD : ret_value = Get_Bit(GPIO_PORTD_DATA_R, PinNo);break;
		case PortE : ret_value = Get_Bit(GPIO_PORTE_DATA_R, PinNo);break;
		case PortF : ret_value = Get_Bit(GPIO_PORTF_DATA_R, PinNo);break;
                 }
        return ret_value;
}
void DIO_WritePin(uint8 Port, uint8 PinNo, uint8 Value)
{
        if(Value==LOW)
        {
                switch(Port)
                {
                case PortA: Clear_Bit(GPIO_PORTA_DATA_R, PinNo); break;
                case PortB: Clear_Bit(GPIO_PORTB_DATA_R, PinNo); break;
                case PortC: Clear_Bit(GPIO_PORTC_DATA_R, PinNo); break;
                case PortD: Clear_Bit(GPIO_PORTD_DATA_R, PinNo); break;
                case PortE: Clear_Bit(GPIO_PORTE_DATA_R, PinNo); break;
                case PortF: Clear_Bit(GPIO_PORTF_DATA_R, PinNo); break;
                }
        }
        else if(Value==HIGH)
        {
                switch(Port)
                {
                case PortA: Set_Bit(GPIO_PORTA_DATA_R, PinNo); break;
                case PortB: Set_Bit(GPIO_PORTB_DATA_R, PinNo); break;
                case PortC: Set_Bit(GPIO_PORTC_DATA_R, PinNo); break;
                case PortD: Set_Bit(GPIO_PORTD_DATA_R, PinNo); break;
                case PortE: Set_Bit(GPIO_PORTE_DATA_R, PinNo); break;
                case PortF: Set_Bit(GPIO_PORTF_DATA_R, PinNo); break;
                }
        }
        else if(Value==TOGGEL)
        {
                switch(Port)
                {
                case PortA: Toggle_Bit(GPIO_PORTA_DATA_R, PinNo); break;
                case PortB: Toggle_Bit(GPIO_PORTB_DATA_R, PinNo); break;
                case PortC: Toggle_Bit(GPIO_PORTC_DATA_R, PinNo); break;
                case PortD: Toggle_Bit(GPIO_PORTD_DATA_R, PinNo); break;
                case PortE: Toggle_Bit(GPIO_PORTE_DATA_R, PinNo); break;
                case PortF: Toggle_Bit(GPIO_PORTF_DATA_R, PinNo); break;
                }
        }
}
uint8 DIO_ReadPort(uint8 Port)
{
      uint8 ret_value;
      switch(Port)
      {
      case PortA: ret_value = GPIO_PORTA_DATA_R; break;
      case PortB: ret_value = GPIO_PORTB_DATA_R; break;
      case PortC: ret_value = GPIO_PORTC_DATA_R; break;
      case PortD: ret_value = GPIO_PORTD_DATA_R; break;
      case PortE: ret_value = GPIO_PORTE_DATA_R; break;
      case PortF: ret_value = GPIO_PORTF_DATA_R; break;
      }
      return ret_value;
}
void DIO_WritepPort(uint8 Port, uint8 Value)
{
      switch(Port)
      {
      case PortA: GPIO_PORTA_DATA_R = Value; break;
      case PortB: GPIO_PORTB_DATA_R = Value; break;
      case PortC: GPIO_PORTC_DATA_R = Value; break;
      case PortD: GPIO_PORTD_DATA_R = Value; break;
      case PortE: GPIO_PORTE_DATA_R = Value; break;
      case PortF: GPIO_PORTF_DATA_R = Value; break;
      }
}
