/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "can.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "miscdev.h"
#include "sht20.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t TxData[8]; // 缓存待发送的信息
	uint8_t length = 8; // 待发送信息的长度
	uint8_t res1;
	uint8_t count=0;
	uint8_t i=0;

	int      rv;
	float    temperature, humidity;

	uint16_t temp_int;
	uint16_t humi_int;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_TIM6_Init();
  MX_TIM1_Init();
  MX_CAN1_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  init_relay();
  init_led();
  beep_start(2,300);
  /* Turn on relay after 1 second */
  HAL_Delay(1000);
  turn_relay(Relay1, ON);
  //sysled_hearbeat();
  printf("Welcome to ISKBoard!\r\n");


  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 /* // 处理CAN接收数据
	      while(g_can_rx_buf.head != g_can_rx_buf.tail)
	      {
	          CAN_RxItem_t *item = &g_can_rx_buf.buf[g_can_rx_buf.head];

	          if(item->StdId == 0x100)
	          {
	              if(item->Data[0] == 1)
	              {
	                  turn_led(Led_R, ON);
	                  printf("LED ON\r\n");
	              }
	              else if(item->Data[0] == 0)
	              {
	                  turn_led(Led_R, OFF);
	                  printf("LED OFF\r\n");
	              }
	          }

	          g_can_rx_buf.head = (g_can_rx_buf.head + 1) % CAN_RX_BUF_SIZE;
	      }
	     // 温湿度上报
	    rv = sht20_sample_TrH(&temperature, &humidity);
	    if( rv )
	    {
	        printf("ERROR: SHT20 sample data failure, rv=%d\r\n", rv);
	    }
	    else
	    {
	        printf("SHT20 sample temperature: %.2f relative humidity: %.1f%%\r\n", temperature, humidity);
	        // 通过CAN上报温湿度,放大100倍变成整数
	        temp_int = (uint16_t)(temperature * 100);
	        humi_int = (uint16_t)(humidity * 100);
	       // TxData[0] = 0x7B;
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
	    HAL_Delay(1000);*/


	  /*CAN上位测试
	  // 轮询方式发�?�CAN信息
	          printf("send data: ");
	          for(i=0;i<8;i++)
	          {
	              TxData[i]=count+1;
	              printf("%d\t", TxData[i]);
	          }
	          printf("\r\n");
	          res1 = CAN_TX_Message(TxData, length);
	          if (res1 < 0)
	          {
	              printf("CAN TX error.\r\n");
	              return -1;
	          }
	          count++;
	          HAL_Delay(1000);
	          */


/*
	  if( OFF == light_status )
	  {
	  adc_sample_lux_noisy(&lux, &noisy);
	  printf("Lux[%lu] Noisy[%lu]\r\n",lux,noisy);


	  if( lux<30 && noisy>800 )
	  {
	  printf("Turn Light on\r\n");
	  //turn_relay(Relay2,ON);
	  turn_led(Led_R,ON);
	  light_status =ON;
	  start =HAL_GetTick();}
	  }
	  else
	  {
		  if( time_after(HAL_GetTick(),start+15000)){
			  printf("Turn Light off\r\n");
			  //turn_relay(Relay2,OFF);
			  turn_led(Led_R,OFF);
			  HAL_Delay(200);
			  light_status = OFF;
	  }
	}
	  HAL_Delay(10);
*/



	  /*HAL_Delay(200);*/
	  /*toggle_led(Led_B);
	      for(int i=0; i<1000; i++)
	          udelay(3000);*/

	     /*adc_sample_lux_noisy(&lux, &noisy);
	      printf("Lux:%lu Noisy:%lu\r\n", lux, noisy);
	      HAL_Delay(2000);*/




	  /*
	  turn_led(Led_R, ON);
	  HAL_Delay(200);
	  turn_led(Led_R, OFF);
	  HAL_Delay(200);

	  toggle_led(Led_G);
	  HAL_Delay(200);
	  toggle_led(Led_G);
	  HAL_Delay(200);

	  blink_led(Led_B, 200);*/

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 18;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
