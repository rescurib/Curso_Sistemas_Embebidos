# Lección 2: GPIO's
El módulo de entradas y salidas de propósito general es el módulo más simple en los microcontroladores y sin embargo si hay unas cuantas cosas que hay que entender antes de sacarle el máximo provecho. Para los que recien llegan a los STM32 puede resultar un poco confuso por todos los modos de operación y habilitación de reloj. Así que vayamos por partes.

Para el STM32F103C8T6 necesitamos tener a la mano el documento [RM0008](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf) que es nuestro manual de referencia y el [DS5319](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf) que es la datasheet para STM32F103x8 y STM32F103xB. 

## Habilitación de relojes de módulo

Lo sé, al principio parece una complicación innecesaria el tener que habilitar relojes para cada periferico. Si han trabajado con PICs esto no tenía que hacerse. ¿Por qué no tener un sólo reloj de sistema que no haya que habilitar individualmente? Bien, en realidad es una exelente idea el tener deshabilitados los relojes de los periféricos por defecto. Las razones son físicas. Como vimos en la guía, en los sistemas embebidos, la computadora es parte integral de sistema. En los microcontroladores los recursos son limitados y por lo tanto no podemos darnos el lujo de desperdiciarlos. Físicamente, el reloj es una señal electrica periodica que se propaga por pequeños conductores dentro de las entrañas del MCU. Esa señal consume energía eléctrica a su paso. Aún cuando un módulo no esté en uso, si el reloj no esta deshabilitado en él, seguirá consumiendo energía. Es por eso que es muy buena idea habilitarlo SÓLO en los módulos que vamos a usar. El módulo GPIO esta comunicado con procesador a través del bus AHB2, como podemos verificar en la pag. 11 de la datasheet del STM32F103x8:

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1Z-4J_d_h0YRNMuBG7lTNu0DV098r2NiS" width="500">
<p>

El reloj debe habilitarse individualmente para cada puerto. Por esta razón necesitamos hablar del modulo RCC (*Reset and Clock Control*). La documentación de este módulo comienza en la página 123 del RM0008. Es un módulo bastante complejo. Por ahora nos quedaremos con las configuraciones por defecto (aprenderemos a configurar el reloj del sistema más adelante) y nos concentraremos en la habilitación de los relojes periféricos. El registro que necesitamos para habilitar los relojes periféricos de los módulos GPIO es el *APB2 peripheral clock enable register* (**RCC_APB2ENR**) y la documentación se encuentra en la página 146:

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1PuvGeLJ-usLjvQjbCLa-AOCOw7SM2ai8" width="700">
<p>

Usando la documentación del modulo en el RM0003 podemos crear las siguientes estructuras y definiciones en C:

```C
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
```
Ejemplo, habilitar el reloj para el Puerto C (en donde esta el led de la Blue Pill):

```C
/* Habilitar reloj en GPIOC */
 RCC->APB2ENR |= (1<<4); // Setear bit 4: IOPCEN (pag. 146)
```

## Modos de Entrada/Salida
La segunda cosa que suele abrumar a los que comienzan con STM32 son los multiples modos de configuración de las entradas y salidas. Comenzaremos a hablar de todos los detalles y características de los pines I/O.

### Entradas digitales
En la pag. 163 del RM0008 se muestra el siguiente diagrama de las configuración para entrada digital:

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1a5fwK4xVnd_LMzWpixnK-jPWmJgBvelU" width="700">
<p>

Podemos observar que tenemos la opición de activar/desactivar resistores pull-up y pull-down. El modo pull-up nos permite asegurar que la entrada tendra un buen nivel de alto lógico. Esto es útil cuando estamos leyendo una señal digital que venga desde un circuito que no tenga el suficiente nivel voltaje. El pull-down nos es util cuando el circuito que estamos leyendo nos da una lectura de tierra en nivel bajo. El triggrt Schmitt es un circuito que nos permite tener lecturas digitales robustas al ruido (subidas y bajadas de voltaje aleatorias). En [este video](https://www.youtube.com/watch?v=Z4pt9Abn3dY) se explica de forma clara su funcionamiento. Si requieren profundizar en el tema puede consultar la pag. 809 del Principios de Electrónica de Malvino-Bates. La configuración se selecciona con los registros **GPIOx_CRL** y **GPIOx_CRH** (x=A..G) [pag. 171, RM0008]. Revisar tambien la tabla 20 de la pag. 161.

Un dato que puede ser útil a la hora de identificar fallas son los valores de voltaje que delimitan el 0 y el 1 lógicos. En la tabla 35, pag. 61 de DS5319 podemos consultar los valores para el voltaje minimo de nivel alto de entrada (V_IH) y el voltaje máximo de nivel bajo de entrada (V_IL), los cuales son:
* V_IH = 0.65*VDD | 2.145V con VDD = 3.3V
* V_IL = 0.35*VDD | 1.155V

### Salidas digitales
En la pag. 164 del RM0008 se muestra el siguiente diagrama de las configuración para salida digital:

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1Vzq-MB2fV7SFw3wXyTRhjUc12uOc6oUb" width="700">
<p>

Un P-MOS es un MOSFET de canal P y un N-MOS de canal N. En modo de conmutación, estos transitores se comportan de la siguiente manera:

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/PMOS_NMOS_conm.png" width="500">
<p>

#### Modo Push-Pull
El modo por defecto, y el más utilizado es el push-pull. El nombre hace referencia al empuje de corriente en alto y al *sinking* de corriente en bajo:

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/STM32_PUSH_PULL.png" width="700">
<p>

El control de salida se encarga de enviar los voltajes correspondientes a cada MOSFET para fase. Esto permite alimentar la salida con VDD durante el alto (1) y permitir leer tierra durante el bajo (0).

#### Modo Open Drain
En modo open drain al P-MOS se le envía alto todo el tiempo de manera que VDD este siempre desconectado. ¿En que situaciones esto es útil? Hay al menos dos situaciones comúnes en donde este modo es necesario. Una es para permitir la comunicación entre dos dispositivos que operan a distintos voltajes. Por ejemplo entre el STM32F103 (3.3V) y un integrado que opere a 1.8V:

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/Open_Drain_STM32.png" width="500">
<p>

El segundo uso más común de este modo es en protocolos de comunicación de cable único. En [este](https://www.youtube.com/watch?v=j9yx8LOslng) video subtitulado del canal del Texas Instruments se explica muy bien el uso de este modo en las implementaciones del protocolo I2C. 

### Registros de configuración y operación
Cada puerto del los STM32F10x tiene asociados 7 registros:

* CRL: configuration register low
* CRH: configuration register high
* IDR: input data register
* ODR: output data register
* BSRR: bit set/reset register
* BRR: bit reset register
* LCKR: configuration lock register

Usando la documentación del RM0008 podemos contruir las siguientes estructuras y definiciones en C:

```C
//---------------- Puertos ------------------
// Direcciones. (Reference Manual (RM0008), Table 3, pag. 51)
#define PORTA_BASE			0x40010800U
#define PORTB_BASE			0x40010C00U
#define PORTC_BASE			0x40011000U
#define PORTD_BASE			0x40011400U
#define PORTE_BASE			0x40011800U
//-------------------------------------------

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
```
Ejemplo: Configuración del pin PC13 como salida con Push-Pull:

```C
/* Configurar PC13 (LED) como salida push-pull */
GPIOC->CRH |=  (1<<20); // MODE13[1:0]: Salida, vel. max. 10MHz (pag. 172)
GPIOC->CRH &= ~(0b11<<22); // CNF13[1:0]: Push-Pull (pag. 172)
```
Encendido y apagado:

**NOTA**: El led en el board de la Blue Pill esta implementado como activo en bajo.
```C
GPIOC->ODR &= ~(1<<13); // Limpiar PC13 (encender led)
GPIOC->ODR |= 1<<13;    // Setear PC13 (apagar led)
```

## Prácticas
* **Práctica 2.0: Programa *mínimo* para blinkear el Led del Blue Pill**. Esta práctica está basada en el ejemplo de la sección 20.2 *The Really Minimal STM32 Application* de *Mastering STM32* de Carmine Noviello en la que se usa STM32Cube IDE pero sin útilizar ningun wizard que genere ningun código de startup. Aunque la aplicación es sencilla, se requiere entender lo escencial del funcionamiento del proceso de construción del toolchain arm-gcc.
* **Práctica 2.1: Botones y técnicas anti-rebote**. En esta práctica si usarémos el wizard de proyecto STM32 y mostrarémos el uso las librerías HAL de ST para GPIO. Lo imparte en esta práctica será hablar de las implementaciones basadas en programación orientada a objetos en C y técnicas para mitigar el ruido de lectura en los botones.
