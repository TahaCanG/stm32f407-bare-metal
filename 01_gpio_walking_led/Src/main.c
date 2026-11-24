
#include <stdint.h>
#include<stdio.h>


#define LED_GREEN (12)
#define LED_ORANGE (13)
#define LED_RED (14)
#define LED_BLUE (15)
#define DELAY_COUNT (500000)
#define RCC_AHB1ENR_GPIODEN  (1UL<<3)




uint32_t volatile *pCLKBaseOff=(uint32_t*)0x40023830 ; //RCC_AHB1ENR BASE+OFFSET
uint32_t volatile *pModAddress=(uint32_t*)0x40020C00; //GPIOD MODER ADRESS
uint32_t volatile *pOdrAddress=(uint32_t*)0x40020C14;// GPIOD MODER+ODR ADRESS (ODR IS OFFSET)


void led_init(void)
{
	 *pCLKBaseOff |=  RCC_AHB1ENR_GPIODEN ; // Enable GPIOD clock (RCC_AHB1ENR, bit 3)


	 *pModAddress &= ~(3UL<<24); // Clear PD12 mode bits
	 *pModAddress |= (1UL<<24); // Set PD12 as output (01)

	 *pModAddress &= ~(3UL<<26); // Clear PD13 mode bits
	 *pModAddress |= (1UL<<26);  // Set PD13 as output (01)

	 *pModAddress &= ~(3UL<<28); // Clear PD14 mode bits
	 *pModAddress |= (1UL<<28); // Set PD14 as output (01)

	 *pModAddress &= ~(3UL<<30); // Clear PD15 mode bits
	 *pModAddress |= (1UL<<30); // Set PD15 as output (01)


}


void led_on(uint8_t pin)
{
	*pOdrAddress |=(1UL<<pin);


}


void led_off(uint8_t pin)
{
	*pOdrAddress &= ~(1UL<<pin);


}


 void delay(uint32_t count)
{
	for(uint32_t i=0;i<count;i++);


}



int main(void)
{

	led_init();
	while(1)
	{
		for(uint8_t pin=LED_GREEN;pin<=LED_BLUE;pin++)
		{

			led_on(pin);
			delay(DELAY_COUNT);
			led_off(pin);

		}

		for(uint8_t pin=LED_GREEN;pin<=LED_BLUE;pin++)
		{
			led_on(pin);


		}
		delay(DELAY_COUNT);

		for(uint8_t pin=LED_GREEN;pin<=LED_BLUE;pin++)
				{
					led_off(pin);


				}
		delay(DELAY_COUNT);




	}



	for(;;);
}
