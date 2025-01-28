/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
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

#include <stdint.h>
#define PERIPH_BASE 		0x40000000UL
#define APB1PERIPH_BASE 	PERIPH_BASE
#define APB2PERIPH_BASE 	(PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE		(PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE		(PERIPH_BASE + 0x10000000UL)

#define GPIOA_BASE			(AHB1PERIPH_BASE + 0x0000UL)
#define GPIOD_BASE			(AHB1PERIPH_BASE + 0x0C00UL)
#define RCC_BASE			(AHB1PERIPH_BASE + 0x3800UL)

typedef struct
{
	volatile uint32_t CR;
	uint32_t RV1[11];
	volatile uint32_t AHB1;
	volatile uint32_t AHB2;
	uint32_t RV2[2];
	volatile uint32_t APB1;
	volatile uint32_t APB2;
}RCC_OFF;

#define RCC					((RCC_OFF *)RCC_BASE)

typedef struct
{
	volatile uint32_t MODE;
	volatile uint32_t TYPE;
	volatile uint32_t SPEED;
	volatile uint32_t IN;
	volatile uint32_t OUT;
	volatile uint32_t BSRR;
	volatile uint32_t PU;
}GPIO_OFF;

#define PA					((GPIO_OFF *)GPIOA_BASE)
#define PD					((GPIO_OFF *)GPIOD_BASE)

void Clock_Init(void)
{
	RCC->CR |= (1<<0);
	RCC->AHB1 |= (1<<0) | (1<<2);
}
void Delay_Init(uint32_t time)
{
	uint32_t i;
	while(time--)
	{
		for(i = 0; i < 1000; i++);
	}
}

void GPIO_Init(void)
{
	Clock_Init();
	PA->MODE |= (1<<6); //GPIOA.3 mode output
	PA->TYPE &= ~(1<<3); //GPIOA.3 pushpull output
	PA->SPEED |= (1<<6); //GPIOA.3 medium speed
	PD->PU |= (1<<20); //GPIOD.10 pullup
}
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	Clock_Init();
	GPIO_Init();
	PA->OUT |= (1<<3);
    /* Loop forever */
	for(;;)
	{
		if((PD->IN & (1<<10))==0)
		{
			Delay_Init(20);
			if((PD->IN & (1<<10))==0)
			{
				PA->OUT ^= (1<<3);
			}
		}
	}
}
