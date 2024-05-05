#include "button.h"


/*
	set up a GPIO pin to be used as an input button.
	
	@parameters
	GPIOx : must be a value from GPIOA -> GPIOF.
	PIN : must be from 0 to 7 or withdraw ASAP.
	PUR_EN : is this is set to 0 then only pull down resistor is enabled, if this is set to 1 then only pull up resistor is enabled.
	
	@note
	There are some GPIO pins that has special considerations (need CR and unlocking w bta3 fa fakes) at page 671 in DATA SHEET (PA[5:0], PB[3:2], PC[3:0],PD[7], PF[0]).
	
*/

void set_up_button(GPIOA_Type* GPIOx, uint8_t PIN, uint8_t PUR_EN)
{
	if(PIN>7) return;
	
	if     (GPIOx == GPIOA) SYSCTL->RCGCGPIO |= 0x01; // Enable clock for PORTA
	else if(GPIOx == GPIOB) SYSCTL->RCGCGPIO |= 0x02; // Enable clock for PORTB
	else if(GPIOx == GPIOC) SYSCTL->RCGCGPIO |= 0x04; // Enable clock for PORTC
	else if(GPIOx == GPIOD) SYSCTL->RCGCGPIO |= 0x08; // Enable clock for PORTD
	else if(GPIOx == GPIOE) SYSCTL->RCGCGPIO |= 0x10; // Enable clock for PORTE
	else if(GPIOx == GPIOF) SYSCTL->RCGCGPIO |= 0x20; // Enable clock for PORTF
	else return;
	
	
	if(PUR_EN){
	 GPIOx->PDR |= ~(1<<PIN); 					// Disable Pull down resistor for PIN.
   GPIOx->PUR |=  (1<<PIN);           // Enable Pull Up resistor for PIN.
	}
	else
	{
	 GPIOx->PUR |= ~(1<<PIN); 					// Disable Pull up resistor for PIN.
   GPIOx->PDR |=  (1<<PIN);           // Enable Pull down resistor for PIN.
	}
	
   GPIOx->DIR |= ~(1<<PIN);           // set PIN as an input (button). 
   GPIOx->DEN |=  (1<<PIN);           // digital enable GPIO pin.
}
