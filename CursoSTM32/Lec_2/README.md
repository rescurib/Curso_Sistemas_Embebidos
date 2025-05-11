# Lección 2: GPIO's
El módulo de entradas y salidas de propósito general es el módulo más simple en los microcontroladores y sin embargo si hay unas cuantas cosas que hay que entender antes de sacarle el máximo provecho. Para los que recien llegan a los STM32 puede resultar un poco confuso por todos los modos de operación y habilitación de reloj. Así que vayamos por partes.

Para el STM32F103C8T6 necesitamos tener a la mano el documento [RM0008](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf) que es nuestro manual de referencia y el [DS5319](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf) que es la datasheet para STM32F103x8 y STM32F103xB. 

Aquí va algo **fundamental** en el desarrollo embebido: desde el punto de vista del *firmware*, la operación y configuración de los módulos hardware es SOLO lectura y escritura de registros. Dicho de otra forma, el procesador no ve *periféricos* sino meros **registros** a los cuales leer o escribir datos. Es por eso que se hará tanto énfasis en la documentación de los registros, no sólo para los GPIOs sino también para el resto de los periféricos.

## Habilitación de relojes de módulo

Lo sé, al principio parece una complicación innecesaria el tener que habilitar relojes para cada periferico. Si han trabajado con PICs esto no tenía que hacerse. ¿Por qué no tener un sólo reloj de sistema que no haya que habilitar individualmente? Bien, en realidad es una excelente idea el tener deshabilitados los relojes de los periféricos por defecto. Las razones son físicas. Como vimos en la guía, en los sistemas embebidos, la computadora es parte integral del sistema. En los microcontroladores los recursos son limitados y por lo tanto no podemos darnos el lujo de desperdiciarlos. Físicamente, el reloj es una señal eléctrica periódica que se propaga por pequeños conductores dentro de las entrañas del MCU. Esa señal consume energía eléctrica a su paso. Aún cuando un módulo no esté en uso, si el reloj no esta deshabilitado en él, seguirá consumiendo energía. Es por eso que es muy buena idea habilitarlo SÓLO en los módulos que vamos a usar. El módulo GPIO esta comunicado con procesador a través del bus AHB2, como podemos verificar en la pag. 11 de la datasheet del STM32F103x8:

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
// (Reference Manual (RM0008), Tabla 3, Reset and clock control RCC, pag. 50)
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
**NOTA**: Como recordatorio o si estás siguiendo mi guía, los conceptos que se estan usando en el código anterior son *estructuras*, *punteros* y *casteo*. Estos temas están en [*C in a Nutshell* 2Ed](https://www.oreilly.com/library/view/c-in-a/9781491924174/):
* Ch.  4: Type Conversions (cast operator, pag. 49)
* Ch.  5: Expressions and Operators (Shift operators, pag. 85)
* Ch.  9: Ponters (Explicit Pointer Conversions, pag. 59)
* Ch. 10: Structures, Unions, and Bit-Fields

Es importante entenderlos porque serán usandos constantemente.

**Ejemplo**, habilitar el reloj para el Puerto C (en donde esta el led de la Blue Pill):

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

Podemos observar varias características interesantes a nivel de hardware. Las entradas están protegidas con con diodos de manera que los voltajes de entrada son saturados al rango GND-3.3V (o 5V en los pines tolerantes). Tenemos tambien la opición de activar/desactivar resistores pull-up y pull-down. El modo pull-up nos permite asegurar que la entrada tendra un buen nivel de alto lógico. Esto es útil cuando estamos leyendo una señal digital que venga desde un circuito que no tenga el suficiente nivel voltaje. El pull-down nos es útil cuando el circuito que estamos leyendo no nos da una lectura de tierra en nivel bajo. Luego tenemos un *Schmitt Trigger*; un circuito que nos permite obtener lecturas digitales robustas al ruido (subidas y bajadas aleatorias de voltaje). En [este video](https://www.youtube.com/watch?v=Z4pt9Abn3dY) se explica de forma clara su funcionamiento. Si requieren profundizar en el tema puede consultar la pag. 809 del Principios de Electrónica de Malvino-Bates. La configuración se selecciona con los registros **GPIOx_CRL** y **GPIOx_CRH** (x=A..G) [pag. 171, RM0008]. Revisar tambien la tabla 20 de la pag. 161.

Un dato que puede ser útil a la hora de identificar fallas son los valores de voltaje que delimitan el 0 y el 1 lógicos. En la tabla 35, pag. 61 de DS5319 podemos consultar los valores para el voltaje minimo de nivel alto de entrada (V_IH) y el voltaje máximo de nivel bajo de entrada (V_IL), los cuales son:
* V_IH = 0.65*VDD | 2.145V con VDD = 3.3V
* V_IL = 0.35*VDD | 1.155V

El diagrama también muestra el siguiente registro relevante a las entradas:
* **Port input data register** (GPIOx_IDR) (x=A..G), pag. 172 (RM0008). Contiene los estados de los pines de entrada para un puerto *x*.

Otros dos registros muy importantes son:
* **Port configuration register low** (GPIOx_CRL) (x=A..G), pag. 171 (RM0008).
* **Port configuration register high** (GPIOx_CRH) (x=A..G), pag. 172 (RM008).

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

#### Velocidad de los pines GPIO
En los microcontroladores STM32, cada pin GPIO puede configurarse para operar a diferentes velocidades de conmutación. Esta configuración es válida cuando el pin se usa como salida, ya sea en modo push-pull, open-drain o con funciones alternativas. Estos cambios de velocidad afectan la pendiente (slew rate) de las señales generadas y, por tanto, el consumo de energía y la integridad de señal. Las opciones disponibles son:
* **Low speed (2 MHz)**. Útil para minimizar el ruido y consumo.
* **Medium speed (10 Mhz)**. Compromiso entre velocidad y consumo.
* **High Speed (50 MHz)**. Ideal para señales rápidas o interfaces de comunicación.
  
>[!NOTE]
>Aunque se llama "velocidad" y la documentación la refiere en unidades de frecuencia, en realidad esta configuración ajusta la corriente de salida del buffer, afectando la velocidad de cambio de nivel lógico (flanco de subida y bajada). No limita directamente la frecuencia a la que puedes cambiar el pin en software.

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1T1xUDSPKF7BPWATuPs9OaFBTxbMuB-zP" width="500">
<p>

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
// Direcciones. (Reference Manual (RM0008), Tabla 3, pag. 51)
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
/* Habilitar reloj en GPIOC */
RCC->APB2ENR |= (1<<4); // Setear bit 4: IOPCEN (pag. 147)

/* Configurar PC13 (LED) como salida push-pull */
GPIOC->CRH |=  (1<<20);    // MODE13[1:0]: Salida, vel. max. 10MHz (pag. 172)
GPIOC->CRH &= ~(0b11<<22); // CNF13[1:0]: Push-Pull (pag. 172)
```
Encendido y apagado:

**NOTA**: El led en el board de la Blue Pill esta implementado como activo en bajo.
```C
GPIOC->ODR &= ~(1<<13); // Limpiar PC13 (encender led)
GPIOC->ODR |= 1<<13;    // Setear PC13 (apagar led)
```
#### Tabla de configuración de bits de puerto
<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1hGsoBDoGMd64VvRen9jX6qP2hkSsSOaG" width="550">
<p>
La Tabla 20 de la página 161 resume las configuraciones de entrada salida y menciona también un detalle muy importante para la configuración de entradas. (La manera en la que esta escrita la tabla me parece un poco confusa asi que usaré la notación de la documentación de los registros: x = Puerto, y = num. de pin). Cuando los campos de GPIOx_CRL(x=A..G) MODEy[1:0] tienen el valor de "00" (input mode) y CNFy[1:0] = "10", los bits del registro ODR cumplen una función diferente; permite habiltar las resistencias internas de pull-up (ODRy = 1) o pull-down (ODRy = 0).

**Ejemplo**. Configuración de pin A1 como entrada digital con pull-up habilitado
```C
/* Habilitar reloj en GPIOA */
RCC->APB2ENR |= (1<<2);                // Setear bit 2: IOPAEN (pag. 147)

/* Configurar A1 como entrada con pull-up */
GPIOA->CRL &= ~(0xF << (1 * 4));       // Limpiar configuración previa
                                       // Al no setear bits, MODE1[1:0] = 00 (Entrada)
GPIOA->CRL |= (0b10 << ((1 * 4) + 2)); // CNF1 = 10 (Pull-up/Pull-down)
GPIOA->ODR |= (1 << 1);                // Activar pull-up en PA1

/* Lectura digital en A1 */
uint estado_pin_a1;
while(1)
{
  estado_pin_a1 = (GPIOA->IDR >> 1) & 0x01; // 9.2.3 Port input data register (pag. 172)
}
```

## Prácticas
* [**Práctica 2.0: Programa *mínimo* para blinkear el Led del Blue Pill**](https://github.com/rescurib/Curso_Sistemas_Embebidos/tree/main/CursoSTM32/Lec_2/Practica_2_0). Esta práctica está basada en el ejemplo de la sección 20.2 *The Really Minimal STM32 Application* de *Mastering STM32* de Carmine Noviello en la que se usa STM32Cube IDE pero sin útilizar ningun wizard que genere ningun código de startup. Será una aplicación sencilla pero la aprovecharemos para aprender lo escencial del proceso de construción con el toolchain para arm-gcc.
* [**Práctica 2.1: Botones y leds con HAL ST**](https://github.com/rescurib/Curso_Sistemas_Embebidos/tree/main/CursoSTM32/Lec_2/Practica_2_1). En esta práctica usarémos el generador de código de inicialización STM32CubeMX y mostrarémos el uso de las librerías HAL de ST para GPIO. También aprenderémos a usar GNU make. 
* [**Práctica 2.3: Toggle con anti-rebote mejorado**](https://github.com/rescurib/Curso_Sistemas_Embebidos/tree/main/CursoSTM32/Lec_2/Practica_2_2) Hablaremos de los rebotes mecánicos en los botones y de una técnica efectiva para mitigarlos por firmware.
