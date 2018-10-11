#ifndef __COMMON_H__
#define __COMMON_H__

#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

/**
 * ��־����
 */
#define LOG_SWITCH 1

#if LOG_SWITCH
	#define LOG(fmt, x...)		printf(fmt, ##x)
	#define LOGln(fmt, x...)	printf(fmt"\r\n", ##x)
#else
	#define LOG(fmt, ...)
	#define LOGln(fmt, x...)
#endif




#define TRUE		1
#define FALSE		0

// STM32 Ĭ���Ǵ��ģʽ
#define IS_BIG_ENDIAN 0
#if IS_BIG_ENDIAN
	#define BigLittleSwap16(A) A
	#define BigLittleSwap32(A) A
#else
	#define BigLittleSwap16(A)  ((((u16)(A) & 0xff00) >> 8) | \
								(((u16)(A) & 0x00ff) << 8))

	#define BigLittleSwap32(A)  ((((u32)(A) & 0xff000000) >> 24) | \
								(((u32)(A) & 0x00ff0000) >> 8) | \
								(((u32)(A) & 0x0000ff00) << 8) | \
								(((u32)(A) & 0x000000ff) << 24))							
#endif

#define GET_1BIT(d, x) (((d) >> (x)) & 0x01)
#define GET_1BYTE(d, x) (((d) >> ((x) * 8)) & 0xFF)

void log_array(const u8 *array, u16 size);

#endif


