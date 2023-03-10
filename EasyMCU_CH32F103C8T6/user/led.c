#include "ch32f10x.h"
#include "debug.h"

void ledb_on(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void ledb_off(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}

void ledb_test(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOC, &GPIO_InitStructure );
		
		for(int i=0; i<3; i++)
		{
			ledb_on();
			Delay_Ms(300);
			ledb_off();
			Delay_Ms(300);
		}
}
