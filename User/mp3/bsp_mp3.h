#ifndef __BSP_MP3_H
#define __BSP_MP3_H

#include "stm32f10x.h"

#define A_CLK_FUN	RCC_APB2PeriphClockCmd

#define A1_CLK	 RCC_APB2Periph_GPIOB
#define A1_Port	 GPIOB
#define A1_Pin	 GPIO_Pin_12
#define A2_Port	 GPIOB
#define A2_Pin	 GPIO_Pin_13
#define A3_Port	 GPIOB
#define A3_Pin	 GPIO_Pin_14
#define A4_Port	 GPIOB
#define A4_Pin	 GPIO_Pin_15
#define A5_CLK	 RCC_APB2Periph_GPIOC
#define A5_Port	 GPIOC
#define A5_Pin	 GPIO_Pin_11

/*
	1.����������ɣ���ʼ�ɼ�����
	2.��Χ���䡣50~65 ���������Щ����Ҫע��
	3.					90~110�������ʹ��죬�Ƿ������˶���ͣ������Ϣһ�°�
	4.�����µĸ赥���ͣ�Ҫ���Ÿ�����

*/

void MP3_Config(void);
void MP3_Play(uint8_t count);
#endif
