
#include <stdint.h>
#include<stdio.h>


uint32_t volatile *pCLKBaseOff=(uint32_t*)0x40023830 ; //RCC_AHB1ENR BASE+OFFSET
uint32_t volatile *pModAddress=(uint32_t*)0x40020C00; //GPIOD MODER ADRESS
uint32_t volatile *pOdrAddress=(uint32_t*)0x40020C14;// GPIOD MODER+ODR ADRESS (ODR IS OFFSET)


void led_init(void)
{
	 *pCLKBaseOff |= (1UL<<3);  // Firstly I open the clock RCC_AHB1ENR
	 *pModAddress &= ~(3UL<<24); // Secondly pin12 area is set clear
	 *pModAddress |= (1UL<<24); // thirdly pin12 area is set output


}


void led_on(uint8_t pin)
{
	*pOdrAddress |=(1UL<<pin);


}



int main(void)
{

	led_init();
	led_on(12);



	for(uint32_t i=0;i<300000;i++);













	for(;;);
}
