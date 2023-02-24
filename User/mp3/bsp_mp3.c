#include "bsp_mp3.h"
__IO uint32_t delay_time=0;

void MP3_Config(void)
{
	GPIO_InitTypeDef    GPIO_InitStruct;
	A_CLK_FUN (A1_CLK|A5_CLK,ENABLE); 
	GPIO_InitStruct.GPIO_Mode =GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin =A1_Pin|A2_Pin|A3_Pin|A4_Pin;
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_10MHz;
	GPIO_Init(A1_Port,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin =A5_Pin;
	GPIO_Init(A5_Port,&GPIO_InitStruct);
}

void MP3_Play(uint8_t count)
{
	//反码配置
	count =~(count);
	count =count&(0x1f);
	//逐位运算
	if((count&0x01) ==1)
		GPIO_SetBits(A1_Port,A1_Pin);
	else 
		GPIO_ResetBits(A1_Port,A1_Pin);
	if((count&0x02) ==2)
		GPIO_SetBits(A2_Port,A2_Pin);
	else 
		GPIO_ResetBits(A2_Port,A2_Pin);
	if((count&0x04) ==4)
		GPIO_SetBits(A3_Port,A3_Pin);
	else 
		GPIO_ResetBits(A3_Port,A3_Pin);
	if((count&0x08) ==8)
		GPIO_SetBits(A4_Port,A4_Pin);
	else 
		GPIO_ResetBits(A4_Port,A4_Pin);
	if((count&0x10) ==16)
		GPIO_SetBits(A5_Port,A5_Pin);
	else 
		GPIO_ResetBits(A5_Port,A5_Pin);
	delay_time =0;
	while(delay_time <200);//延时200ms
		GPIO_SetBits(A1_Port,A1_Pin);
		GPIO_SetBits(A2_Port,A2_Pin);
		GPIO_SetBits(A3_Port,A3_Pin);
		GPIO_SetBits(A4_Port,A4_Pin);
		GPIO_SetBits(A5_Port,A5_Pin);
}

