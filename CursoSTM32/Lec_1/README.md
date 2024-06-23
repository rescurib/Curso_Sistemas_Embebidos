# Lección 1: Crash-Course de procesadores y mapa de memoria ARM Cortex-M

## Máquinas de Carga-Almacenamiento
Si quitamos los detalles de implementación, todas las computadoras son iguales. Cambian en tamaño, frecuencia de operación, arquitectura y un largo etc, pero en esencia, funcionan de la misma manera. Ver a las computadores con estos lentes se llama modelación abstracta. Estos modelos se ajustan a diferentes necesidades teóricas y prácticas. Por ejemplo, en los años 30´s (décadas antes de las computadoras electrónicas, Alan Turing necesitaba un modelo computacional abstracto para responder a la pregunta **¿hay cosas qué las computadoras no puedan hacer?**. Creó entonces lo que conocemos ahora como Máquina Turing ([aquí](https://youtu.be/iaXLDz_UeYY) hay una buena explicación del canal *Derivando*). Pero la Máquina de Turing es demasiado abstracta para nuestros propósitos. Necesitamos un punto medio. Algo suficientemente abstracto para olvidarnos de las características especificas de cada procesador pero lo suficientemente concreto para manejar conceptos útiles para la programación como memorias y direcciones. Aquí es dónde entra la **Load-Store Machine** (Máquina de Carga-Almacenamiento).

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/Carga_Almacenamiento_Diagrama.png">
<p>
  
Una Máquina de Carga-Almacenamiento consiste una unidad de control que se encarga de leer y ejecutar instrucciones, y 3 memorias separadas: registros, programa y memoria principal. La memoria de registros tiene un número fijo y pequeño de elementos de memoria. Las memorias principal y de programa tienen un número indefinido de elementos. En cada elemento de cualquiera de las memorias se pueden leer y escribir números enteros. Los elementos de memoria están identificados por un número (dirección) que no puede ser modificado. Cada instrucción es simplemente un número entero binario que codifica alguna de las siguientes acciones:

* Cargar elementos de la memoria principal hacia los elementos de los registros.
* Almacenar elementos de los registros en la memoria principal.
* Colocar números en los elementos de los registros.
* Operaciones lógicas entre los elementos de los registros.
* Operaciones aritméticas entre elementos de los registros.
* Brincar a una instrucción específica si un registro guarda un 0.

Restricciones:
* Los resultados de las operaciones aritméticas o lógicas no pueden colocarse directamente en la memoria principal, sólo en elementos de los registros.

Este modelo puede hacer lo que cualquier sistema de cómputo puede hacer. A diferencia de la Máquina de Turing, este modelo es directamente concretable a una arquitectura de carga-almacenamiento como lo son ARM o RISC-V. Pero antes de eso vamos a revisar una arquitectura de juguete que me he inventado para explicar de forma clara como funcionan los procesadores:

### Arquitectura de simple de 8 bits
Esta arquitectura de ejemplo tendra instrucciones de 12 bits y manejará datos de 8 bits. Comencemos con la ALU:
<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1NjGBa14ZjMFkQe5IUW2YNUp745HC9bTV" width="500">
<p>

Esta implementación maneja operandos y resultados de 8 bits (muy limitada, pero es suficiente para ejemplificar la idea del modelo). La ALU solo puede tomar operanodos y escribir el resultado directamente en los registros (ver diagrama del modelo de carga-almacenamiento). Los registros son una pequeña unidad de memoria, a modo de una cajonera para el módulo de control:

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1iN4L97yMrYPv-Pq5MonReqC6Br3rpe5T" width="300">
<p>

Ahora vayamos al programa. Un programa es simplemente un conjunto de números binarios que el procesador traduce a acciones concretas. En esta arqitectura de juguete tenemos 3 tipos de instrucciones. Tipo A: operación, Tipo B: carga-almacenamiento y salto. 

Comencemos con un ejemplo de ejecución una **Tipo A** (los valores de los registros estan previamente inicializados por una secuencias de instrucciones Tipo B que veremos más adelante):

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1dqk-is8mTuTmddhIbBJvISoL1b19roWK" width="700">
<p>
  
Este ejemplo realiza una operación de suma. Al ser uno de los operandos 0, esta operación es equivalente a un *movimiento* de dato entre registros. Esta es una observación importante porque en arquitecturas limitadas como esta, es necesario ingeniarse secuencias de instrucciones que realicen operaciones/tareas que no existan de forma explícita en el conjunto de instrucciones. 

Las instruciones de Tipo B para las operaciones de carga y almacenamiento tienen los siguientes campos de bits:

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1JDBeWwqiCjomtwIrB0XY74DgMoE3ESsV" width="500">
<p>

La siguiente animación muestra la ejecución de esta secuencia de instrucciones:

1. Cargar el contenido de la dirección 101100 de la memoria principal al registro 0.
2. Cargar el contenido de la dirección 101101 de la memoria principal al registro 1.
3. Sumar registro 9 con registro 1 y poner el resultado en el registro 2.
4. almacenar el registro 2 en la dirección 101101 de la memoria principal.

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=16TdFB5rAwYTOzWd9ITlYdMnceaN0dEir" width="700">
<p>

La secuencia de intrucciones del programa anterior esta almacenado en la memoria de programa. Cada instrucción ocupa una dirección especifica en ella. Para nuestro ejemplo, la memoria de programa se vería así:

| Dirección | Instrucción |
|:---------:|:-----------:|
|    0x0    |101000101100 |
|    0x1    |101001101101 | 
|    0x2    |011000001010 |
|    0x3    |110010101110 |

La idea fundamental aquí es: las instrucciones son *sólo números* en otra memoria. La diferencia esta en la interpretación de estos por parte del módulo de control. El orden de ejecución esta regulado por un elemento interno al modulo de control llamado **contador de programa**. Inicialmente comienza en cero y va incrementando en +1 en este modelo simple. Podemos modificar el valor del contador de programa con la instrucción de salto que también es de Tipo B:

|3 bits| 3 bits      | 6 bits |
|:----:|:-----------:|:------:|
| 111  | Dirección de registro | Dirección de salto en memoria de programa |

Cuando se ejecuta instrucción, el contador de programa se mueve la dirección especifica solo si el registro leido contiene un "00000000". En caso contrario, el contador no cambia de valor. Se deja como ejercicio escribir una secuencia de instrucciones de este modelo de ejemplo para ordenar la siguiente lista en la memoria principal [5,3,1,6]. 

### Bibliografía 
El objetivo de este modelo de juguete es construir una intución de los fundamentos de una máquina de carga-almacenemiento. Si has entendido todo hasta este punto, estas listo para aprender como funcionan los procesadores RISC del mundo real:

* *Computer Organization and Design*, RISC-V Edition, Patterson-Henessey
  - Ch. 2: Instructions: Language of the Computer
  - Ch. 3: The Procesor
* *The Definitive Guide to ARM Cortex-M3 and Cortex-M4 Processors*, 3ED, Joseph Yiu
  - Ch. 4: Architecture
  - Ch. 5: Instruction Set
    
## Mapa de memoria ARM Cortex-M3
Espero que hayas hecho las lecturas recomendadas porque ahora verémos el modelo carga-almacenamiento para la arquitectura ARM Cortex-M. 

La lista completa de registros para esta arquitectura es la siguiente:

| Nombre del Registro | Descripción                                                                 |
|---------------------|-----------------------------------------------------------------------------|
| R0-R12              | Registros de propósito general utilizados para varias manipulaciones y operaciones de datos. |
| SP (R13)            | Puntero de Pila, usado para operaciones de pila.                            |
| LR (R14)            | Registro de Enlace, contiene la dirección de retorno para llamadas a funciones. |
| PC (R15)            | Contador de Programa, apunta a la siguiente instrucción a ejecutar.         |
| APSR                | Registro de Estado del Programa de Aplicación, contiene el estado actual del programa. |
| IPSR                | Registro de Estado del Programa de Interrupción, contiene el número de tipo de excepción. |
| EPSR                | Registro de Estado del Programa de Ejecución, contiene información del estado de ejecución. |
| PRIMASK             | Registro de Máscara de Interrupción, deshabilita todas las excepciones excepto NMI cuando está establecido. |
| BASEPRI             | Registro de Máscara de Prioridad Base, define el umbral de prioridad para excepciones. |
| FAULTMASK           | Registro de Máscara de Fallos, deshabilita todas las excepciones cuando está establecido. |
| CONTROL             | Registro de Control, cambia el nivel de privilegio y la pila utilizada.     |

En la práctica la mayor parte del tiempo de depuración profunda sólo prestarás atención a los registros R0-R15 pero es bueno conocerlos todos porque eventualmente te toparás con problemas complejos que requerirán revisar el resto de los registros (tambien llamados Registros Especiales). Para una referencia completa a todos los registros revisa la Sección 4.2.2 *Registers* de *The Definitive Guide to ARM Cortex-M3 and Cortex-M4 Processors*.

Los procesadores Cortex-M3 usan la microarquitectura ARMv7-M. Los detalles de sus instrucciones se pueden encontrar en el [ARMv7-M Architecture Reference Manual](https://developer.arm.com/documentation/ddi0403/latest)

Los accesos de carga-almacenamiento pueden relizarse almacenando una dirección base (de la memoria principal) en un registro y un *offset* en otro registro (o también como un valor inmediato en la instrucción). Ya que los registros son de 32 bits, el procesador puede cargar o almacenar bytes en un espacio de memoria de 32GB. Este espacio de memoria se divide en varias secciones segun su función. Esto es lo que se conoce como **Mapa de Memoria**: 

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1uU8rWdbDEns2DtgpSQ57xA0fQGh9MCOC" width="800">
<p>

En los microcontoladores basados en ARM, sólo una pequeña parte de espacio de memoria esta implementado físicamente pero los valores de las direcciones base son respetadas. Por ejemplo, las regiones de memoria válidas para la Flash y la SRAM para un STM32F103C8 se definen de esta manera en un script de linker:

```
MEMORY
{
 FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
 SRAM (xrw) : ORIGIN = 0x20000000, LENGTH = 20K
}
```
Más adelate explicaré como funcionan estos scripts. Por ahora ya estamos listos para la siguiente lección: manejo de GPIOS.
