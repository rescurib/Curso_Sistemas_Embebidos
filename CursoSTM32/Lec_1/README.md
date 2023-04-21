# Lección 1: Crash-Course de procesadores y layout de memoria ARM Cortex-M

Si quitamos los detalles de implementación, todas las computadoras son iguales. Cambian en tamaño, frecuencia de operación, arquitectura y un largo etc, pero en esencia, funcionan de la misma manera. Ver a las computadores con estos lentes se llama modelación abstracta. Estos modelos se ajustan a diferentes necesidades teóricas y prácticas. Por ejemplo, en los años 30´s (décadas antes de las computadoras electrónicas, Alan Turing necesitaba un modelo computacional abstracto para responder a la pregunta **¿hay cosas qué las computadoras no puedan hacer?**. Creó entonces lo que conocemos ahora como Máquina Turing ([aquí](https://youtu.be/iaXLDz_UeYY) hay una buena explicación del canal *Derivando*). Pero la Máquina de Turing es demasiado abstracta para nuestros propósitos. Necesitamos un punto medio. Algo suficientemente abstracto para olvidarnos de las características especificas de cada procesador pero lo suficientemente concreto para manejar conceptos útiles para la programación como memorias y direcciones. Aquí es dónde entra la Load-Store Machine. 