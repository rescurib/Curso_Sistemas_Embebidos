# Lección 1: Crash-Course de procesadores y layout de memoria ARM Cortex-M

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
Esta arquitectura de ejemplo tandra instrucciones de 12 bits y manejará datos de 8 bits. Comencemos con la ALU:
<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1NjGBa14ZjMFkQe5IUW2YNUp745HC9bTV" width="500">
<p>

Ejecución de intrucciones
<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1dqk-is8mTuTmddhIbBJvISoL1b19roWK" width="700">
<p>





  
