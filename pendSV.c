/**
*********************************************************************************************************
*                                                
*                                      (c) Copyright 2020-2030
*                                           All Rights Reserved
*
* @File    : 
* @By      : liwei
* @Version : V0.01
* @Github  :liyinuoman2017
*********************************************************************************************************
**/

/*
*********************************************************************************************************
Includes 
*********************************************************************************************************
*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
/*
*********************************************************************************************************
Define
*********************************************************************************************************
*/


/*
*********************************************************************************************************
Typedef
*********************************************************************************************************
*/



/*
*********************************************************************************************************
Function 
*********************************************************************************************************
*/
void Error_Handler(void)
{

  while(1) 
  {
  }

}
/***  测试函数  空函数 仅作演示  *****/
void system_init(void);
void touch_display_handle(void)
{
}
void communication_handle(void)
{
}
void user_func(void)
{
}
void sensor_handle(void)
{
}
/**@Github  :liyinuoman2017  **/
/***********************************************************************************************************
* @名称	: 
* @描述	:
***********************************************************************************************************/
int main(void)
{
	/***系统初始化*****/
	system_init();	
	while(1)
	{
		/***触摸和显示处理*****/
		touch_display_handle();
		/***通信处理*****/		
		communication_handle();
		/***传感器处理*****/		
		sensor_handle();
	}
}
/**@Github  :liyinuoman2017  **/
/***********************************************************************************************************
* @名称	: 
* @描述	:时钟中断函数  1MS中断
***********************************************************************************************************/
static uint8_t pendsv_number = 0;
#define PENDSV_MAX (5)
void systick_callback(void)	
{
	static uint8_t clk = 0;
	/*** 设置pendSV调用号  ***/	
	pendsv_number = (clk++)%PENDSV_MAX;	
	/*** 设置pendSV挂起  ***/
	SCB->ICSR |=SCB_ICSR_PENDSVSET_Msk;	
}
/***********************************************************************************************************
* @名称	: 
* @描述	:用户回调函数
***********************************************************************************************************/
void pendsv_user0(void)
{
	user_func();	
};	
void pendsv_user1(void)
{

};
void pendsv_user2(void)
{

};
void pendsv_user3(void)
{

};
void pendsv_user4(void)
{

};

/***********************************************************************************************************
* @名称	: 
* @描述	: 跳转表
***********************************************************************************************************/
typedef void (*callback)(void);
callback pendsv_callback[PENDSV_MAX] =
{
	pendsv_user0,
	pendsv_user1,
	pendsv_user2,
	pendsv_user3,
	pendsv_user4,
};
/***********************************************************************************************************
* @名称	: 
* @描述	:pendsv 可悬挂系统调用
***********************************************************************************************************/
void pendsv_handler(void)
{
	/*** 检查 pendsv_number范围  ***/		
	if(pendsv_number < PENDSV_MAX)
	{
		/*** 执行跳转表中的函数 ***/
		pendsv_callback[pendsv_number]();
	}
}

/***********************************************END*****************************************************/



