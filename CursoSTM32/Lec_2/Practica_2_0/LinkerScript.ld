/* Layout de memoria para un STM32F103C8 */

MEMORY
{
 FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
 SRAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
 }

ENTRY(main)

/* output sections */
SECTIONS
{
   /* Programar códifo en FLASH */
   .text : ALIGN(4)
   {
     *(.isr_vector) /* Tabla vectorial */
     *(.text)       /* Codigo del programa */
     KEEP(*(.isr_vector))
   } >FLASH

   /* Initialized global and static variables into SRAM */
   .data :
   {
     *(.data)
   } >SRAM
}