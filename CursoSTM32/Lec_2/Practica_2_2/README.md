# Práctica 2.2: Toggle con anti-rebote mejorado

Esta práctica tendrá el mismo circuito y función que la anterior, un led rojo controlado en modo toggle por el switch 1 y un led verde controlado en modo directo por el switch 2:

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/CursoSTM32/Lec_2/Practica_2_1/P1_2_Circuit_BB.png" width="650">
<p>

La diferencia es que implementarémos la operación toggle de una manera que tiene dos características muy utiles:
* No dependerá de *retardos bloqueantes*.
* El switch tendrá uno de los mejores filtros anti-rebote implementados por software.

Vayamos por partes. ¿Qué son los rebotes en el botón y por qué necesitamos mitigarlos en primer lugar?
