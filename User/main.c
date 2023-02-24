
// ADC 单通道采集

#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "bsp_TiMbase.h" 
#include "bsp_mp3.h"
#include "bsp_ili9341_lcd.h"

// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue;
__IO uint32_t sample_time=0;
//uint32_t threshold_size[100] ={0};
//uint32_t threshold=0;
//uint32_t pre_threshold=0;
//uint32_t heart_rate;
// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal; 
float pbuffer[threahold_long];
float heart_rate[3];
float hearts;
char dispBuff[100];
	

int main(void)
{	
	uint32_t i=0,j,k=0,m =0;
	float  max_gat[2][2];
  float mids, *mid = &mids;
  float differs[1], *differa = differs;
  float sum = 0;
  float nums, *num = &nums;
	//初始化
	for(i=0;i<2;i++){
		for(j=0;j<2;j++){
			max_gat[i][j] =0;
		}
	}
	ILI9341_Init(); 
  USART_Config();
	ADCx_Init();
	MP3_Config();
	BASIC_TIM_Init();
	
	ILI9341_GramScan ( 3 );
	LCD_SetFont(&Font24x32);
	LCD_SetColors(BLACK,YELLOW);
	ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);
	ILI9341_DispStringLine_EN_CH(LINE(1),"  国立浪速大学医学部-第一内科");
	ILI9341_DispStringLine_EN_CH(LINE(2),"  指导教授 第一内科常琦教授");
	ILI9341_DispStringLine_EN_CH(LINE(3),"  贾卓璇博士|严潼颖博士");
	ILI9341_DispStringLine_EN_CH(LINE(5),"  祝您健康");
	printf("\r\n ----配置完成开始检测心率----\r\n");
	sample_time =0;
	k =0;
	//MP3_Play(0x1);
	while (1)
	{
		if(sample_time ==50)//50ms
		{
			ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // 读取转换的AD值
			//printf("%f  ",ADC_ConvertedValueLocal);
			
			pbuffer[k] =ADC_ConvertedValueLocal;
			//printf(" %.2f ",pbuffer[k]);
			sample_time =0;
			k++;
		}

			if(k ==threahold_long)
			{
						//动态阈值检测和心率结果给出
				if (max1(pbuffer, mid, num) == 1){
						max_gat[0][0] = *mid;
						max_gat[1][0] = *num;
						pbuffer[(int)nums-1] =0;
				}

				if (max1(pbuffer, mid, num) == 1) {
						//鍥涗釜鏁版眰闂撮殧涓や釜鐨勫樊,缁撴灉鏀惧叆涓�涓暟缁刣iffer
					max_gat[0][1] =*mid;
					max_gat[1][1] =*num;			
					
					 differ(max_gat[1], differa);
					if((*differa)<0)
							(*differa) =-(*differa);
				
				sum = sum+(*differa);
				sum =60000.0/(sum*50);
				if(sum<110 &&sum >50){
				//printf("\n%.0f\n",sum);
				//均值滤波
				heart_rate[m%3] =sum;
				if((m%3) ==0)
				{
					if(((heart_rate[0]+heart_rate[1]+heart_rate[2])/3.0) >50&&((heart_rate[0]+heart_rate[1]+heart_rate[2])/3.0)<110)
					{
						printf("%.0f ",(heart_rate[0]+heart_rate[1]+heart_rate[2])/3.0);
					hearts =(heart_rate[0]+heart_rate[1]+heart_rate[2])/3.0;
					sprintf(dispBuff,"当前的心率为：%.0f 次/每分",hearts);
					LCD_ClearLine(LINE(4));
					ILI9341_DispStringLine_EN_CH(LINE(4),dispBuff);
					//if(((heart_rate[0]+heart_rate[1]+heart_rate[2])/3.0)<=65)
						//MP3_Play(0x2);
					//if(((heart_rate[0]+heart_rate[1]+heart_rate[2])/3.0)>=110)
						//MP3_Play(0x3);
					}
				}	
				m++;
			}
			k =0;//重新记录采样数组
			sum =0;
		}
	
	
	}	
}
/*********************************************END OF FILE**********************/
}
