/********************************** (C) COPYRIGHT  *******************************
 * File Name          : debug.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : This file contains all the functions prototypes for UART
 *                      Printf , Delay functions.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#include "debug.h"

/* Support Printf Function Definition */
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;


static u8  p_us=0;								   
static u16 p_ms=0;					

/*********************************************************************
 * @fn      Delay_Init
 *
 * @brief   Initializes Delay Funcation.
 *
 * @return  none
 */	
void Delay_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	p_us=SystemCoreClock/8000000;			  
	p_ms=(u16)p_us*1000;					   
}								    

/*********************************************************************
 * @fn      Delay_Us
 *
 * @brief   Microsecond Delay Time.
 *
 * @param   n - Microsecond number.
 *
 * @return  None
 */
void Delay_Us(u32 n)
{		
	u32 i;	
	
	SysTick->LOAD=n*p_us; 						  		 
	SysTick->VAL=0x00;        					
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	
	do
	{
		i=SysTick->CTRL;
	}while((i&0x01)&&!(i&(1<<16)));
	
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	
	SysTick->VAL =0X00;     	 
}

/*********************************************************************
 * @fn      Delay_Ms
 *
 * @brief   Millisecond Delay Time.
 *
 * @param   n - Millisecond number.
 *
 * @return  None
 */
void Delay_Ms(u16 n)
{	 		  	  
	u32 i;	
	
	SysTick->LOAD=(u32)n*p_ms;				
	SysTick->VAL =0x00;							
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	
	do
	{
		i=SysTick->CTRL;
	}while((i&0x01)&&!(i&(1<<16)));	
	
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	
	SysTick->VAL =0X00;        	    
} 


/*********************************************************************
 * @fn      fputc
 *
 * @brief   Support Printf Function 
 *
 * @param   data - UART send Data.
 *          
 * @return  data - UART send Data.
 */
int fputc(int data, FILE *f)
{
#if (DEBUG == DEBUG_UART1)
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	USART_SendData(USART1, (u8) data);
#elif (DEBUG == DEBUG_UART2)
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
  USART_SendData(USART2, (u8) data);	
#elif (DEBUG == DEBUG_UART3)
  while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);	
  USART_SendData(USART3, (u8) data);	
#endif
	
  return data;
}

/*********************************************************************
 * @fn      USART1_IRQHandler
 *
 * @brief   This function handles USART1 global interrupt request.
 *
 * @return  none
 */
extern void EasyCon_serial_task(int16_t byte);
void USART1_IRQHandler( void )
{
    if( USART_GetITStatus( USART1, USART_IT_RXNE ) != RESET )
    {
        //USART_ReceiveData( USART1 );
				EasyCon_serial_task(USART_ReceiveData( USART1 ));
    }
}

/*********************************************************************
 * @fn      USART_Printf_Init
 *
 * @brief   Initializes the USARTx peripheral.
 *
 * @param   baudrate - USART communication baud rate.
 *
 * @return  None
 */
void USART_Printf_Init(u32 baudrate)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure = {0};
	
#if (DEBUG == DEBUG_UART1)	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
#elif (DEBUG == DEBUG_UART2)
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
#elif (DEBUG == DEBUG_UART3)	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
#endif	
   
  USART_InitStructure.USART_BaudRate = baudrate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;

#if (DEBUG == DEBUG_UART1)	
  USART_Init(USART1, &USART_InitStructure); 
	USART1->STATR = 0x00C0;
//  USART_ITConfig( USART1, USART_IT_RXNE, ENABLE );
//  
//	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init( &NVIC_InitStructure );
	
	USART_Cmd(USART1, ENABLE);
#elif (DEBUG == DEBUG_UART2)	
  USART_Init(USART2, &USART_InitStructure); 
  USART_Cmd(USART2, ENABLE);
	
#elif (DEBUG == DEBUG_UART3)
  USART_Init(USART3, &USART_InitStructure); 
  USART_Cmd(USART3, ENABLE);
	
#endif	
}


