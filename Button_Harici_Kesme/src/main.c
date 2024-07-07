#include "stm32f4xx.h"
GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void GPIO_Config(){
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFGEN,ENABLE);

GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_PuPd =GPIO_PuPd_NOPULL;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

GPIO_Init(GPIOD , &GPIO_InitStruct);

GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_PuPd =GPIO_PuPd_DOWN;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

GPIO_Init(GPIOA , &GPIO_InitStruct);


}
void delay(uint32_t time)
{
	while(time--);
}
void EXTI_Config(){
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA , GPIO_PinSource0);
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0xFF;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI_IRQHandler()
{
	if(EXTI_GetFlagStatus(EXTI_Line0) != RESET)
	{
		GPIO_ResetBits(GPIOD , GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(1680000);
		GPIO_SetBits(GPIOD , GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(1680000);
		GPIO_ResetBits(GPIOD , GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(1680000);
		GPIO_SetBits(GPIOD , GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		delay(1680000);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
int main(void)
{
GPIO_Config();
EXTI_Config();
  while (1)
  {
	  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

  }
}
