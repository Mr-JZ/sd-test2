/*
 * retarget.c
 *
 *  Created on: Jul 12, 2021
 *      Author: Wuebbelmann
 */


#include "stm32l4xx_hal.h"

#ifdef STM32L4xx_HAL_UART_H

extern UART_HandleTypeDef huart2;

// this can be changed if another UART is wanted for stdio
static UART_HandleTypeDef* stdio = &huart2;

#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)

PUTCHAR_PROTOTYPE {
 HAL_UART_Transmit (stdio, (uint8_t *)&ch, 1, 0xFFFF);
 return ch;
}


GETCHAR_PROTOTYPE {
    uint8_t ch;
    HAL_UART_Receive (stdio, (uint8_t *)&ch, 1, 0xFFFF);
 return ch;
}


#define WRITEFUNC _write
#define READFUNC _read

int WRITEFUNC(int iFileHandle, char *pcBuffer, int iLength)
{

    HAL_UART_Transmit (stdio, (uint8_t *)pcBuffer, iLength, 0xFFFF);
    return iLength;
}


int READFUNC (int iFileHandle, char *pcBuffer, int iLength)
{
    HAL_UART_Receive (stdio, (uint8_t *)pcBuffer, iLength, 0xFFFF);
    return iLength;
}

#endif // STM32L4xx_HAL_UART_H
