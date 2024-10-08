/*
 * main.c
 *
 *  Created on: 9 jul 2023
 *  Author: Rodolfo Escobar (basado en ejemplo de Carmine Noviello)
 */

#include "main.h"

/* Direcciones iniciales de memoria (comunes a todos los STM32 MCUs) */
#define FLASH_BASE 0x08000000
#define SRAM_BASE  0x20000000

// Poner SP (Stack Pointer) al final de la SRAM
#define SRAM_SIZE 20*1024 // STM32F103C8 tiene 20 KB de RAM
#define SRAM_END (SRAM_BASE + SRAM_SIZE)

/* Tabla de vectores (vector table) mínima */
/*************************************************************
 * NOTA: Es necesaria para el correcto inicio de este ejemplo.
 * Para entender porque, revisar: 
 *    Mastering STM32, Carmine Noviello
 *        - 7.1.1 Vector Table in STM32, pag. 174
 *************************************************************/
uint32_t *vector_table[] __attribute__((section(".isr_vector"))) = {
(uint32_t *)SRAM_END, // stack pointer inicial
(uint32_t *)main      // función main como Reset_Handler
 };
/*************************************************************/

void delay(uint32_t count) {
 while(count--);
}

int main() 
{
 /* Habilitar reloj en GPIOC */
 RCC->APB2ENR |= (1<<4); // Setear bit 4: IOPCEN (RM0008, pag. 146)

 /* Configurar PC13 (LED) como salida push-pull */
 GPIOC->CRH |=  (1<<20);    // MODE13[1:0]: Salida, vel. max. 10MHz (RM0008, pag. 172)
 GPIOC->CRH &= ~(0b11<<22); // CNF13[1:0]: Push-Pull (RM0008, pag. 172)

 while(1)
 {
  GPIOC->ODR |= 1<<13;    // Setear PC13
  delay(200000);
  GPIOC->ODR &= ~(1<<13); // Limpiar PC13
  delay(200000);
 }

}
