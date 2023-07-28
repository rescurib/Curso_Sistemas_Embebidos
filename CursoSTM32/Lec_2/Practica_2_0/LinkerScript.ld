/* Layout de memoria para un STM32F103C8 */

MEMORY
{
 FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
 SRAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
}

ENTRY(main)

/* Secciones de salida */
SECTIONS
{
   /* Poner código en FLASH */
   .text : ALIGN(4)
   {
     *(.isr_vector) /* Tabla vectorial */
     *(.text)       /* Código del programa */
     KEEP(*(.isr_vector))
   } >FLASH

   /* Poner variables globales y estáticas inicializadas en SRAM */
   .data :
   {
     *(.data)
   } >SRAM
}
