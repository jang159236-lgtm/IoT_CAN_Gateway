/*
 * sht20.h
 *
 *  Created on: Jun 10, 2026
 *      Author: 11812
 */

#ifndef SRC_BOARD_SHT20_H_
#define SRC_BOARD_SHT20_H_


#include <sys/types.h>
#include <stdint.h>

extern int sht20_sample_TrH(float *temperature, float *humdity);

#endif /* SRC_BOARD_SHT20_H_ */
