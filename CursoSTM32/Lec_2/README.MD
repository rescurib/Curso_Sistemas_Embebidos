# Lección 2: GPIO's
El módulo de entradas y salidas de propósito general es el módulo más simple en los microcontroladores y sin embargo si hay unas cuantas cosas que hay que entender antes de sacarle el máximo provecho. Para los que recien llegan a los STM32 puede resultar un poco confuso por todos los modos de operación y habilitación de reloj. Así que vayamos por partes.

Para el STM32F103C8T6 necesitamos tener a la mano el documento [RM0008](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101xx-stm32f102xx-stm32f103xx-stm32f105xx-and-stm32f107xx-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf) que es nuestro manual de referencia. 

## Habilitación de relojes de módulo

Lo sé, al principio parece una complicación innecesaria el tener que habilitar relojes para cada periferico. Si han trabajado con PICs esto no tenía que hacerse. ¿Por qué no tener un sólo reloj de sistema que no haya que habilitar individualmente? Bien, en realidad es una exelente idea el tener deshabilitados los relojes de los periféricos por defecto. Las razones son físicas. Como vimos en la guía, en los sistemas embebidos, la computadora es parte integral de sistema. En los microcontroladores los recursos son limitados y por lo tanto no podemos darnos el lujo de desperdiciarlos. Físicamente, el reloj es una señal electrica periodica que se propaga por pequeños conductores dentro de las entrañas del MCU. Esa señal consume energía electrica a su paso. Aún cuando un módulo no esté en uso, si el reloj no esta deshabilitado en él, seguirá consumiendo energía. Es por eso que es muy buena idea habilitarlo SÓLO en los módulos que vamos a usar.

Por esta razón nececitamos hablar ahora del modulo RCC (*Reset and Clock Control*). La documentación de este módulo comienza en la página 123 del RM0008. Es un módulo bastante complejo. Por ahora nos quedaremos con las configuraciones por defecto (aprenderemos a configurar el reloj del sistema más adelante) y nos concentraremos en la habilitación de los relojes periféricos. El registro que necesitamos para habilitar los relojes periféricos de los módulos GPIO es el *APB2 peripheral clock enable register* (RCC_APB2ENR) y la docuemntación se encuentra en la página 146:

<p align="center">
<img src="https://drive.google.com/file/d/1PuvGeLJ-usLjvQjbCLa-AOCOw7SM2ai8/view?usp=sharing" width="700">
<p>
