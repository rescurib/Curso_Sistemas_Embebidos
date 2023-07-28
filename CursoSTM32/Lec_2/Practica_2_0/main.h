/*
 * main.h
 *
 *  Created on: 9 jul 2023
 *  Author: Rodolfo Escobar (basado en ejemplo Carmine Noviello)
 */

#ifndef MAIN_H_
#define MAIN_H_

typedef unsigned long uint32_t;

// ----------------- Relojes ---------------------
// Dirección (Datasheet, pag. 33, Figure 11)
#define RCC_BASE 0x40021000U

// Estructura de registros
// (Reference Manual (RM0008), Table 19, pags. 156-158)
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;
}RCC_RegDef;

#define RCC   ((RCC_RegDef*)RCC_BASE)
//------------------------------------------------

//------------------ Puertos ---------------------
// Direcciones. (Reference Manual (RM0008), Table 3, pag. 51)
#define PORTA_BASE			0x40010800U
#define PORTB_BASE			0x40010C00U
#define PORTC_BASE			0x40011000U
#define PORTD_BASE			0x40011400U
#define PORTE_BASE			0x40011800U
//------------------------------------------------

// Estructura de registros GPIO
// (Reference Manual (RM0008), Sec. 9.2, pag. 171)
typedef struct
{
	volatile uint32_t CRL; //Configuration Register Low  (pag. 171)
	volatile uint32_t CRH; //Configuration Register High (pag. 172)
	volatile uint32_t IDR; //Input Data Register (pag. 172)
	volatile uint32_t ODR; //Output Data Register (pag. 173)
	volatile uint32_t BSRR;//Bit Set/Reset Register(pag. 173)
	volatile uint32_t BRR; //Bit Reset Register (pag. 174)
	volatile uint32_t LCKR;//Configuration Lock Register (pag. 174)
}GPIO_RegDef;

#define GPIOA ((GPIO_RegDef*)PORTA_BASE)
#define GPIOB ((GPIO_RegDef*)PORTB_BASE)
#define GPIOC ((GPIO_RegDef*)PORTC_BASE)
#define GPIOD ((GPIO_RegDef*)PORTD_BASE)
#define GPIOE ((GPIO_RegDef*)PORTE_BASE)

/* Funciones de usuario */
int main(void);
void delay(uint32_t count);

#endif /* MAIN_H_ */
