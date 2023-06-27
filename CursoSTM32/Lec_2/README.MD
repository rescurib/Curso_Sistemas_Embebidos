# Lección 2: GPIO's
El módulo de entradas y salidas de propósito general es el módulo más simple en los microcontroladores y sin embargo si hay unas cuantas cosas que hay que entender antes de sacarle el máximo provecho. Para los que recien llegan a los STM32 puede resultar un poco confuso por todos los modos de operación y habilitación de reloj. Así que vayamos por partes.

Para el STM32F103C8T6 necesitamos tener a la mano el documento [RM0008](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf) que es nuestro manual de referencia. 

## Habilitación de relojes de módulo

Lo sé, al principio parece una complicación innecesaria el tener que habilitar relojes para cada periferico. Si han trabajado con PICs esto no tenía que hacerse. ¿Por qué no tener un sólo reloj de sistema que no haya que habilitar individualmente? Bien, en realidad es una exelente idea el tener deshabilitados los relojes de los periféricos por defecto. Las razones son físicas. Como vimos en la guía, en los sistemas embebidos, la computadora es parte integral de sistema. En los microcontroladores los recursos son limitados y por lo tanto no podemos darnos el lujo de desperdiciarlos. Físicamente, el reloj es una señal electrica periodica que se propaga por pequeños conductores dentro de las entrañas del MCU. Esa señal consume energía eléctrica a su paso. Aún cuando un módulo no esté en uso, si el reloj no esta deshabilitado en él, seguirá consumiendo energía. Es por eso que es muy buena idea habilitarlo SÓLO en los módulos que vamos a usar. El módulo GPIO esta comunicado con procesador a través del bus AHB2, como podemos verificar en la pag. 11 de la datasheet del STM32F103x8:

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1Z-4J_d_h0YRNMuBG7lTNu0DV098r2NiS" width="500">
<p>

El reloj debe habilitarse individualmente para cada puerto. Por esta razón necesitamos hablar del modulo RCC (*Reset and Clock Control*). La documentación de este módulo comienza en la página 123 del RM0008. Es un módulo bastante complejo. Por ahora nos quedaremos con las configuraciones por defecto (aprenderemos a configurar el reloj del sistema más adelante) y nos concentraremos en la habilitación de los relojes periféricos. El registro que necesitamos para habilitar los relojes periféricos de los módulos GPIO es el *APB2 peripheral clock enable register* (RCC_APB2ENR) y la docuemntación se encuentra en la página 146:

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1PuvGeLJ-usLjvQjbCLa-AOCOw7SM2ai8" width="700">
<p>

## Modos de Entrada/Salida
La segunda cosa que suele abrumar a los que comienzan con STM32 son los multiples modos de configuración de las entradas y salidas. Comenzaremos a hablar de todos los detalles y características de los pines I/O.

### Entradas digitales
En la pag. 163 del RM0008 se muestra el siguiente diagrama de las configuración para entrada digital:
<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1a5fwK4xVnd_LMzWpixnK-jPWmJgBvelU" width="700">
<p>
Podemos observar que tenemos la opición de activar/desactivar resistores pull-up y pull-down. El modo pull-up nos permite asegurar que la entrada tendra un buen nivel de alto lógico. Esto es útil cuando estamos leyendo una señal digital que venga desde un circuito que no tenga el suficiente nivel voltaje. El pull-down nos es util cuando el circuito que estamos leyendo nos da una lectura de tierra en nivel bajo. El triggrt Schmitt es un circuito que nos permite tener lecturas digitales robustas al ruido (subidas y bajadas de voltaje aleatorias). En [este video](https://www.youtube.com/watch?v=Z4pt9Abn3dY) se explica de forma clara su funcionamiento. Si requieren profundizar en el tema puede consultar la pag. 809 del Pincipios de Electrónica de Malvino-Bates. La configuración se selecciona con el registro **GPIOx_CRL** (x=A..G) [pag. 171, RM0008].



***


