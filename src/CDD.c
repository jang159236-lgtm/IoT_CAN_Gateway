#include "CDD.h"
#include "FlexCAN_Ip.h"
#include "Platform_Types.h"
#include "Dio.h"          /* 新增：LED控制需要 */
#include "Dio_Cfg.h"      /* 新增：DioConf_DioChannel_LED1 */

/*void CDD_CanIf_TxConfirmation(PduIdType CanIfTxPduId, Std_ReturnType result)
{

}*/
extern volatile uint8 g_tx_confirm_count;
volatile uint8 g_rx0_count=0;

void CDD_CanIf_TxConfirmation(PduIdType CanTxPduId, Std_ReturnType result)
{
    g_tx_confirm_count++;
    (void)CanTxPduId;
    (void)result;
}
// --- 改成这个变量名，并且暴露给 main.c 使用 ---
volatile uint8 g_rx_data[8];
volatile uint8 g_rx_flag_can1 = 0;
volatile uint8 g_led_rx_flag = 0;

void CDD_CanIf_RxIndication(
    PduIdType RxPduId,
    const PduInfoType *PduInfoPtr
)
{
	if (RxPduId == 2)
	{
	        if ((PduInfoPtr != NULL_PTR) && (PduInfoPtr->SduLength > 0U))
	        {
	            /* 约定：数据第0字节 0x01=开灯，0x00=关灯，其它可以做别的动作 */
	            if (PduInfoPtr->SduDataPtr[0] == 0x01U)
	            {
	                Dio_WriteChannel(DioConf_DioChannel_LED1, STD_LOW);
	            }
	            else if (PduInfoPtr->SduDataPtr[0] == 0x00U)
	            {
	                Dio_WriteChannel(DioConf_DioChannel_LED1, STD_HIGH);
	            }
	        }
    }

    // 一旦 CAN1 收到数据（RxPduId 对应 1），置标志
    if(RxPduId == 1) {
        g_rx_flag_can1 = 1;
    }
}

void CDD_CanTransmit(PduIdType CanIfTxPduId, const uint8_t * pdata, uint16_t dataLen)
{
    if((pdata != NULL_PTR) && (dataLen <= 8))
    {
        PduInfoType PduInfo = {
            .SduDataPtr = (uint8_t*)pdata,
            .SduLength = dataLen
        };
        CanIf_Transmit(CanIfTxPduId, &PduInfo);
    }
}

ISR(CAN0_Wake_Up_IRQHandler)
{
    EXIT_INTERRUPT();
}
