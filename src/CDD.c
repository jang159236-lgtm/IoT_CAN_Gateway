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

volatile uint8 g_rx_data[8];
volatile uint8 g_rx_flag_can1 = 0;
volatile uint8 g_led_rx_flag = 0;

void CDD_CanIf_RxIndication(
    PduIdType RxPduId,
    const PduInfoType *PduInfoPtr
)
{
	if(RxPduId == 1)
	{
		g_rx_flag_can1 = 1;
	 }
	if (RxPduId == 2)
	{
		if ((PduInfoPtr != NULL_PTR) && (PduInfoPtr->SduLength >= 2U))
	    {
			uint8 led_index = PduInfoPtr->SduDataPtr[0];
			uint8 state     = PduInfoPtr->SduDataPtr[1];
			Dio_LevelType level = (state != 0U) ? STD_LOW : STD_HIGH;

			switch (led_index) {
			case 0U:
				Dio_WriteChannel(DioConf_DioChannel_LED1B, level);
				break;
			case 1U:
				Dio_WriteChannel(DioConf_DioChannel_LED2G, level);
				break;
			case 2U:
				Dio_WriteChannel(DioConf_DioChannel_LED3R, level);
				break;
			case 3U:
				Dio_WriteChannel(DioConf_DioChannel_LED4Y, level);
			default:
				break;
			}
			g_led_rx_flag = 1U;
	        }
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
