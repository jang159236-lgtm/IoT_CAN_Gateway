/*
 * CDD.h
 *
 *  Created on: 2026年7月10日
 *      Author: liuyi
 */

#ifndef CDD_H_
#define CDD_H_

#include "CanIf.h"

void CDD_CanIf_TxConfirmation(PduIdType CanTxPduId, Std_ReturnType result);
void CDD_CanIf_RxIndication(PduIdType RxPduId, const PduInfoType * PduInfoPtr);

void CDD_CanTransmit(PduIdType CanIfTxPduId, const uint8_t * pdata, uint16_t dataLen);


#endif /* CDD_H_ */
