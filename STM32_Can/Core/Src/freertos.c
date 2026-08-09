/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "can.h"
#include "miscdev.h"
#include "sht20.h"
#include "tim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
osThreadId_t appTaskHandle;
const osThreadAttr_t appTask_attributes = {
  .name = "appTask",
  .stack_size = 512 * 4,   /* SHT20采样+CAN+printf需要的栈比defaultTask大，给足一点 */
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

void StartAppTask(void *argument);////////////////////////////////

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  appTaskHandle = osThreadNew(StartAppTask, NULL, &appTask_attributes);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
void Servo_SetAngle(uint8_t angle);
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void StartAppTask(void *argument)
{
    uint8_t TxData[8];
    uint8_t length = 8;
    uint8_t res1;

    int      rv;
    float    temperature, humidity;
    uint16_t temp_int;
    uint16_t humi_int;

    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);//启动舵机PWM

    for (;;)
    {
        /* 处理CAN接收数据 */
        while (g_can_rx_buf.head != g_can_rx_buf.tail)
        {
            CAN_RxItem_t *item = &g_can_rx_buf.buf[g_can_rx_buf.head];

			if (item->StdId == 0x100)
			{
				uint8_t led_index = item->Data[0];
				uint8_t state = item->Data[1];

				if (led_index <= 2)
				{
					lednum_t led = (led_index == 0) ? Led_R :
										(led_index == 1) ? Led_G : Led_B;
					turn_led(led, state ? ON : OFF);
					printf("LED %d %s\r\n", led_index, state ? "ON" : "OFF");
				}
				else
				{
					printf("Unknown led_index=%d\r\n", led_index);
				}
			}
            /*舵机控制帧*/
            else if (item->StdId == 0x101)
            {
            	Servo_SetAngle(item->Data[0]);
            	printf("Servo angle set to %d \r\n",item->Data[0]);

            }

            g_can_rx_buf.head = (g_can_rx_buf.head + 1) % CAN_RX_BUF_SIZE;
        }

        /* 温湿度上报 */
        rv = sht20_sample_TrH(&temperature, &humidity);
        if (rv)
        {
            printf("ERROR: SHT20 sample data failure, rv=%d\r\n", rv);
        }
        else
        {
            printf("SHT20 sample temperature: %.2f relative humidity: %.1f%%\r\n", temperature, humidity);

            temp_int = (uint16_t)(temperature * 100);
            humi_int = (uint16_t)(humidity * 100);

            TxData[0] = temp_int >> 8;
            TxData[1] = temp_int & 0xFF;
            TxData[2] = humi_int >> 8;
            TxData[3] = humi_int & 0xFF;
            length = 4;

            res1 = CAN_TX_Message(TxData, length);
            if (res1 < 0)
            {
                printf("CAN TX error.\r\n");
            }
        }

        osDelay(1000);   /* 原来是 HAL_Delay(1000)，FreeRTOS环境下换成 osDelay 让出CPU给其他任务 */
    }
}
//舵机
void Servo_SetAngle(uint8_t angle)
{
    if (angle > 180) angle = 180;
    uint16_t pulse = 500 + (uint16_t)((uint32_t)angle * 2000 / 180);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pulse);
}
/* USER CODE END Application */

