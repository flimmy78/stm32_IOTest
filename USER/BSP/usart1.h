#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>

void USART_Config(USART_TypeDef* USARTx,uint32_t BaudRate);
void USARTx_printf(USART_TypeDef* USARTx, uint8_t *Data,...);
void USART1_IRQ(void);

#endif /* __USART1_H */
