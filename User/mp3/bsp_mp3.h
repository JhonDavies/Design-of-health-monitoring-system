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
	1.开机配置完成，开始采集心率
	2.范围分配。50~65 你的心率有些慢，要注意
	3.					90~110您的心率过快，是否在做运动，停下来休息一下吧
	4.你有新的歌单推送，要播放歌曲了

*/

void MP3_Config(void);
void MP3_Play(uint8_t count);
#endif
