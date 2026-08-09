/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */
CAN_FilterTypeDef CAN1_FilterConfig;
#include "miscdev.h"

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 9;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_5TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
  /* 配置 CAN 的筛选器 */
  CAN1_FilterConfig.FilterBank = 0; //过滤器编号为0
  CAN1_FilterConfig.FilterMode = CAN_FILTERMODE_IDMASK; //过滤器模式，使用标识符屏蔽模�??
  CAN1_FilterConfig.FilterScale = CAN_FILTERSCALE_32BIT; //过滤器的位宽�??32 �??

  /*过滤器的屏蔽和标识符�??,将所有的过滤参数都设置为 0x0000，即不进行过滤，接收�??有的数据�??*/
  CAN1_FilterConfig.FilterIdHigh = 0x0000;
  CAN1_FilterConfig.FilterIdLow = 0x0000;
  CAN1_FilterConfig.FilterMaskIdHigh = 0x0000;
  CAN1_FilterConfig.FilterMaskIdLow = 0x0000;

  CAN1_FilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0; //过滤器接收邮箱为FIFO0
  CAN1_FilterConfig.FilterActivation = CAN_FILTER_ENABLE; //使能过滤器，允许将过滤器应用于CAN1控制�??
  CAN1_FilterConfig.SlaveStartFilterBank = 14; //从机模式时的起始过滤器编号，此处设置�?? 14

  if(HAL_CAN_ConfigFilter(&hcan1, &CAN1_FilterConfig) != HAL_OK)
  {
      Error_Handler();
  }

  //启动CAN
  if(HAL_CAN_Start(&hcan1) != HAL_OK)
  {
	  Error_Handler();
  }
  // 启用 CAN 接收 FIFO0 中断
  if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
      Error_Handler();
  }
  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/* 发�?�函数部�?? */
CAN_TxHeaderTypeDef Tx_pHeader;

int CAN_TX_Message(uint8_t TxData[], uint8_t length)
{
    uint32_t TxMailboxNumber = 0x00000000U; // 存储本次发�?�所使用邮箱的邮箱号
    Tx_pHeader.StdId = 0x122; // 以此ID发松
    Tx_pHeader.ExtId = 0x0000; // 扩展ID(此处无用)
    Tx_pHeader.IDE = CAN_ID_STD; // 标准�??
    Tx_pHeader.RTR = CAN_RTR_DATA; // 数据�??
    Tx_pHeader.DLC = length; // 发�?�数据的长度
    Tx_pHeader.TransmitGlobalTime = DISABLE;
    if(HAL_CAN_AddTxMessage(&hcan1, &Tx_pHeader, TxData, &TxMailboxNumber) != HAL_OK)
    {
        return -1;
    }
    return 0;
}

/* 接收中断回调函数 */

CAN_RxHeaderTypeDef hCAN1_RxHeader; //CAN1接收消息

CAN_RxBuf_t g_can_rx_buf = {0};     // 新增这行

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t aRxData[8];
    CAN_RxHeaderTypeDef header;
    if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &header, aRxData) == HAL_OK)
    {
        uint8_t next = (g_can_rx_buf.tail + 1) % CAN_RX_BUF_SIZE;
        if(next != g_can_rx_buf.head)
        {
            g_can_rx_buf.buf[g_can_rx_buf.tail].StdId = header.StdId;
            g_can_rx_buf.buf[g_can_rx_buf.tail].DLC   = header.DLC;
            for(int i=0; i<header.DLC; i++)
                g_can_rx_buf.buf[g_can_rx_buf.tail].Data[i] = aRxData[i];
            g_can_rx_buf.tail = next;
        }
    }
}
/*
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t aRxData[8], i;
    if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &hCAN1_RxHeader, aRxData) == HAL_OK)
    {
        printf("\r\nGet Rx Message Success!!\r\n");
        printf("[ID]:0x%1lX [DLC]:%ld [Data]:", hCAN1_RxHeader.StdId, hCAN1_RxHeader.DLC);
        for(i=0; i<hCAN1_RxHeader.DLC; i++)
            printf("%X ", aRxData[i]);
        printf("\r\n");

        //根据ID和数据控制LED
        if(hCAN1_RxHeader.StdId == 0x100)
        {
        	if(aRxData[0] == 1)
        	{
        		turn_led(Led_R, ON);
        	    printf("LED ON\r\n");
        	}
        	else if(aRxData[0] == 0)
        	{
        		turn_led(Led_R, OFF);
        		printf("LED OFF\r\n");
        	}
        }
    }
}
*/
/* USER CODE END 1 */
