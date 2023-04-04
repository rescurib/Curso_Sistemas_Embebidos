# **Lección 0**: ARM Cortex-M y microcontrotroladores STM32

Si tienes experiencia programando microcontroladores PIC o AVR, es posible que te sientas intimidado al revisar la documentación de los fabricantes de microcontroladores basados en ARM Cortex-M. Creo que una de las razones por las que los microcontroladores PIC son tan populares en las escuelas es porque se pueden aprender a utilizar consultando un solo archivo de datasheet. Aunque la documentación para los microcontroladores ARM Cortex-M puede ser más extensa y dispersa, una vez que te familiarices con ella, podrás aprovechar al máximo la potencia y versatilidad de estos microcontroladores.

## Familia de núcleos ARM Cortex-M
El ARM Cortex-M es una familia de procesadores ARM RISC de 32 bits **licenciados** por ARM Limited. Estos núcleos están optimizados para circuitos integrados de bajo costo y eficiencia energética. Esto significa que diferentes marcas pueden comprar la licencia para incomporar estos núcleos a sus microcontroladores. 

El número en el nombre de los Cortex-M hace referencia a las distintas necesidades para las que fueron diseñados: 

|     Core    | Descripción |
| :-----------: | ----------- |
|         M0  | Procesador muy pequeño (a partir de 12 000 compuertas) de bajo costo y muy bajo consumo de energía. Microcontroladores y aplicaciones profundamente integradas.|
|  M0+  | El procesador de mayor eficiencia energética para sistemas integrados pequeños. Tamaño y modelo de programador similares al procesador Cortex-M0, pero con características adicionales como interfaz de E/S de ciclo único y reubicaciones de tablas vectoriales.|
|  M1  | Un diseño de procesador pequeño optimizado para FPGAs. Poporciona implementación de memoria estrechamente acoplada (TCM) utilizando bloques de memoria en los FPGA. Mismo conjunto de instrucciones que el Cortex-M0.|
|  M3  | Un procesador integrado pequeño pero potente para microcontroladores de bajo consumo que tiene un rico conjunto de instrucciones que le permite manejar tareas complejas más rápido. Tiene un divisor de hardware e instrucciones Multiplicar-Acumular (MAC). Además, también tiene características integrales de depuración y rastreo para permitir desarrollar sus aplicaciones más rápido.|
|  M4  | Proporciona todas las características del Cortex-M3, con instrucciones adicionales destinadas a tareas de procesamiento de señales digitales (DSP), como datos múltiples / instrucción única (SIMD) y operaciones MAC de ciclo único más rápidas. Además, tiene una unidad de punto flotante de precisión simple opcional que admite el estándar de punto flotante IEEE 754.|
|  M7  | Procesador de alto rendimiento para microcontroladores de gama alta y aplicaciones de procesamiento intensivo. Tiene todas las funciones disponibles en Cortex-M4, con soporte adicional para punto flotante de doble precisión, así como funciones de memoria adicionales como caché y memoria estrechamente acoplada (TCM).|

## Familia de microcontroladores STM32

Los microcontroladores STM32 son una familia de microcontroladores de 32 bits basados en procesadores ARM Cortex-M, fabricados por la compañía STMicroelectronics. Las familias no sólo difieren en el tipo de núcleo ARM Cortex-M sino en el tipo de periféricos, frecuencia de reloj, rangos de memoria, características de consumo de potencia y opciones de conectividad.

Esta tabla muestra como se clasifican algunas de estas familias:

<p align="center">
<img src="https://www.digikey.com.mx/-/media/Images/Product%20Highlights/S/STMicroelectronics/STM32%20Microcontrollers/v2/stm32-overview.jpg" width="970">
<p>

STMicroelectronics ofrece una amplia gama de herramientas de desarrollo, documentación y soporte para ayudar a los desarrolladores. Pueden consultar más información en [STM32 MCU Developer Zone](https://www.st.com/content/st_com/en/stm32-mcu-developer-zone.html).

Los nombres de los dispositivos STM32 se leen de la siguiente manera:



<p align="center">
<img src="https://stm32world.com/images/thumb/d/de/STM32_Naming.png/800px-STM32_Naming.png">
<p>

### STM32CubeIDE

STM32CubeIDE es un entorno de desarrollo integrado (IDE) gratuito basado en Eclipse para programar microcontroladores STM32. Incluye un conjunto completo de herramientas de desarrollo: editor de código, compilador, depurador y un conjunto de bibliotecas y controladores predefinidos. STM32CubeIDE es compatible con varios sistemas operativos, incluyendo Windows, Linux y macOS, y se integra perfectamente con otras herramientas de desarrollo de STMicroelectronics, como STM32CubeMX (generador de código). Es fácil de usar y tiene una interfaz intuitiva. 

<div align="center">
  <a href="https://www.youtube.com/watch?v=m9_4bL8vJIM"><img src="https://img.youtube.com/vi/m9_4bL8vJIM/0.jpg" alt="IMAGE ALT TEXT"></a>
</div>

## Tarjeta de desarollo STM32F103C8T6 (Blue Pill)

La Blue Pill es una tarjeta de desarrollo de bajo costo basada en el microcontrolador STM32F103C8T6 de STMicroelectronics. Esta tarjeta es muy popular entre la comunidad de desarrolladores debido a su bajo costo, facilidad de uso y gran cantidad de recursos disponibles en línea. La Blue Pill cuenta con una amplia variedad de pines GPIO, UART, SPI, I2C y USB, lo que la hace ideal para una amplia gama de proyectos.

<p align="center">
<img src="https://www.luisllamas.es/wp-content/uploads/2018/03/stm32f103-blue-pill-pinout.png" width="800">
<p>

Pueden comprarlas en [Mercado Libre](https://articulo.mercadolibre.com.mx/MLM-658947311-placa-de-desarrollo-stm32-stm32f103c8t6-stlink-st-link-v2-_JM) con todo y ST-Link.

¡Ahora estamos listos para empezar el curso!
