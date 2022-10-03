
#include "STD_types.h"

#define PortA 1
#define PortB 2
#define PortC 3
#define PortD 4
#define PortE 5
#define PortF 6

#define Bit0 0
#define Bit1 1
#define Bit2 2
#define Bit3 3
#define Bit4 4
#define Bit5 5
#define Bit6 6
#define Bit7 7
#define Bit7 7
#define INPUT 0
#define OUTPUT 1

#define HIGH 1
#define LOW 0
#define TOGGEL 2

void DIO_Init(uint8 Port, uint8 PinNo, uint8 Direction);
uint8 DIO_ReadPin(uint8 Port, uint8 PinNo);
void DIO_WritePin(uint8 Port, uint8 PinNo, uint8 Value);
uint8 DIO_ReadPort(uint8 Port);
void DIO_WritePort(uint8 Port, uint8 Value);