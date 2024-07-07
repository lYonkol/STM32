
#include "stm32f4xx.h"
GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void GPIO_Config(){
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE);
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);


GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_PuPd =GPIO_PuPd_NOPULL;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

GPIO_Init(GPIOD , &GPIO_InitStruct);

GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_PuPd =GPIO_PuPd_DOWN;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

GPIO_Init(GPIOA , &GPIO_InitStruct);
}

void EXTI_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFGEN,ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA , GPIO_PinSource0);
	EXTI_InitStruct.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn | EXTI1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);
}


int main(void)
{
GPIO_Config();
  while (1)
  {

  }
}
