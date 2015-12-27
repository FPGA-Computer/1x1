#include "stm32F030 iot.h"

void SystemInit(void)
{
}

void Init(void)
{
	// Default HSI: On 8MHz
	
	// GPIO default: input
	// PA13, PA14 = SWD
	
	// Enable GPIO clocks
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOFEN;
	
  // Select pin types	
	GPIOA->MODER = PIN_ALT(PA14_SWCLK)|PIN_ALT(PA13_SWDIO)|
	               PIN_OUTPUT(PA10_SDA)|PIN_OUTPUT(PA9_SCL)|
		             PIN_OUTPUT(PA7_MOSI)|PIN_OUTPUT(PA6_MISO)|
		             PIN_OUTPUT(PA5_SCK)|PIN_OUTPUT(PA4_nSS)|	
		             PIN_OUTPUT(PA3_RXD)|PIN_OUTPUT(PA2_TXD)|	
		             PIN_OUTPUT(PA1_nCS)|PIN_OUTPUT(PA0_CE);
	
	GPIOB->MODER = PIN_OUTPUT(PB1_IRQ);
	GPIOF->MODER = PIN_OUTPUT(PF1_OSC_OUT)|PIN_OUTPUT(PF0_OSC_IN);
}

void Delay(void)
{
	uint32_t i;
	
	for(i=0x1ffff;i;i--)
	  /* */;
}

void LED(uint8_t pos, uint8_t on_off)
{
	uint32_t Set_Reset;
	
	Set_Reset = on_off?0:16;
	
	switch(pos)
	{
		case 8:
		case 9:
			GPIOA->BSRR = 1<< (pos-8+PA9_SCL+Set_Reset);
			break;
		
		case 10:
			GPIOB->BSRR = 1<< (PB1_IRQ+Set_Reset);
			break;
		
		case 11:
		case 12:
			GPIOF->BSRR = 1<< (pos-11+PF0_OSC_IN+Set_Reset);
			break;
		
		default:
			if(pos<=7)
        GPIOA->BSRR = 1<< (pos + Set_Reset);
		}
}

int main(void)
{
	uint16_t i;
	
	Init();
	
	while(1)
	{	
		for(i=0;i<13;i++)
		{
			LED(i,1);
			Delay();
			LED(i,0);		
		}
	}
}
