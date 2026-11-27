

#include <stdint.h>
#include<stdio.h>


#define LED_GREEN (12)
#define LED_ORANGE (13)
#define LED_RED (14)
#define LED_BLUE (15)
#define DELAY_COUNT (500000) // 500ms second/2  half second
#define RCC_AHB1ENR_GPIODEN  (1UL<<3)
#define RCC_AHB1ENR_GPIOAEN  (1UL<<0)
#define DEBOUNCE_COUNT (50000) // 0,05 second




uint32_t volatile *pCLKBaseOff=(uint32_t*)0x40023830 ; //RCC_AHB1ENR BASE+OFFSET
uint32_t volatile *pModAddress=(uint32_t*)0x40020C00; //GPIOD MODER ADRESS
uint32_t volatile *pOdrAddress=(uint32_t*)0x40020C14;// GPIOD MODER+ODR ADRESS (ODR IS OFFSET)



uint32_t volatile *pModAddress_A= (uint32_t*)0x40020000;
uint32_t volatile *pGPIO_IDR_A = (uint32_t*)0x40020010;





void button_init(void)
{

	 *pCLKBaseOff |= RCC_AHB1ENR_GPIOAEN;

	 *pModAddress_A &= ~(3UL<<0);

}


uint8_t button_is_pressed(void)
{
	if(*pGPIO_IDR_A & (1UL<<0))
	{
		return 1;


	}
  return 0;


}


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


 void mode_all_off(void)
  {

 		for(uint8_t pin=LED_GREEN;pin<=LED_BLUE;pin++)
 				{
 					led_off(pin);


 				}

  }




 void mode_all_blink(void)
 {


		for(uint8_t pin=LED_GREEN;pin<=LED_BLUE;pin++)
		{
			led_on(pin);

		}

		 delay(DELAY_COUNT);
		 mode_all_off();
		 delay(DELAY_COUNT);


 }

 void mode_walking(void)
 {


		for(uint8_t pin=LED_GREEN;pin<=LED_BLUE;pin++)
		{

			led_on(pin);
			delay(DELAY_COUNT);
			led_off(pin);

		}


 }









int main(void)
{


	led_init();
	button_init();
	uint8_t mode=0;
	uint8_t prev_state=0;

 while(1)
 {
	uint8_t curr_state =button_is_pressed();

	if((prev_state==0) && (curr_state==1) )
	{
		delay(DEBOUNCE_COUNT);

		if(button_is_pressed()==1)
		{
			mode++;


			if(mode==3)
			{
              mode=0;

			}

		}



	}


 prev_state=curr_state;

 switch (mode){

 case 0:
 mode_walking();
 break;

 case 1:
 mode_all_blink();
 break;

 case 2:
 mode_all_off();
 break;


 default:
 mode=0;
 break;


 }





 }



}



