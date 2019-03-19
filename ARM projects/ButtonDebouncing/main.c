/*Led ON on button press
 * Author: Swapneel Naphade
 *
 * */

#include "stm32f10x.h"
#define BUTTON_CUSHION 2000


int main(void)
{
	//RCC clock config
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPBEN;;
	//output pin gpioc 13 config
	GPIOC->CRH &= ~(GPIO_CRH_CNF13);
	GPIOC->CRH &= ~(GPIO_CRH_MODE13_0);
	GPIOC->CRH |= GPIO_CRH_MODE13_1;
	//input pin gpiob 1 config
	GPIOB->CRL &= ~(GPIO_CRL_MODE1);
	GPIOB->CRL &= ~(GPIO_CRL_CNF1_0);
	GPIOB->CRL |= GPIO_CRL_CNF1_1;

	volatile char buttonPressed = 0;
	volatile int pressedCount = 0;
	volatile int releasedCount = 0;

    while(1)
    {
    	if(GPIOB->IDR & GPIO_IDR_IDR1){
    		if(buttonPressed == 0){
    			if(pressedCount > BUTTON_CUSHION){
    				buttonPressed = 1;
    				GPIOC->ODR ^= GPIO_ODR_ODR13; //Toggle LED state
    			}else{
    				pressedCount++;
    				releasedCount = 0;
    			}
    		}
    	}else{
    		if(buttonPressed == 1){
    			if(releasedCount > BUTTON_CUSHION){
       				buttonPressed = 0;
				}else{
					releasedCount++;
					pressedCount = 0;
				}
    		}
    	}

    }
}
