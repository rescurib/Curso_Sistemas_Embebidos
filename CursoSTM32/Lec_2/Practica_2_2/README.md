# Práctica 2.2: Toggle con anti-rebote mejorado

Esta práctica tendrá el mismo circuito y función que la anterior, un led rojo controlado en modo toggle por el switch 1 y un led verde controlado en modo directo por el switch 2:

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/CursoSTM32/Lec_2/Practica_2_1/P1_2_Circuit_BB.png" width="650">
<p>

La diferencia es que implementarémos la operación toggle de una manera que tiene dos características muy utiles:
* No dependerá de *retardos bloqueantes*.
* El switch tendrá uno de los mejores filtros anti-rebote implementados por software.

Vayamos por partes. ¿Qué son los rebotes en el botón y por qué necesitamos mitigarlos en primer lugar?

## Rebotes mecánicos en los *push-buttons*

En la realidad física, las transiciones de estado nunca son limpias, sino que ocurren con *transientes*, es decir, con perturbaciones iniciales que eventualmente se estabilizan. En el caso de los push-buttons, estos transcientes ocurren principalmente porque al presionarlos o soltarlos, el contacto metálico rebota y cierra y abre el circuito hasta que se estabiliza. Las siguientes señales las tomé, del switch 1 del circuito mostrado, con un osciloscopio en modo de captura única y muestran algunos de estos rebotes:
<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=15YZivMvWPZrD1kXMdfTqFdUzCK8HrMYh" width="830">
</p>
<p align="center"><em>Figura 1: Rebotes en flanco de subida.</em></p>

<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=1PTFuFFSp8C6vYdPZ5TV7vLegOqPadNUJ" width="830">
</p>
<p align="center"><em>Figura 2: Rebotes en flanco de bajada.</em></p>

Estos rebotes no siempre ocurren. Dependen de muchos factores incluyendo el modelo o el ejemplar de botón. Pero ocurren esporádicamente y el modo toggle o las operaciones de conteo de pulsaciones son particularmente sencibles a estos rebotes.

## Métodos antirebote

En la práctica anterior usamos el método antirebote más simple que es entrar a un retardo bloqueante después de detectar nivel alto en el pin y volver a leer el pin al finalizar el retardo para verificar el cambio de estado. Este método tiene la desventaja de que el microcontrolador no puede hacer nada mas durante ese retardo y tampoco puede adaptarse a transientes de diferente duración.

Jack Ganssle tiene un [excelente artículo](https://www.ganssle.com/debouncing-pt2.htm) dónde recopila y discute varios métodos de mitigación de rebotes. En esta práctica vamos a interpretar el algoritmo que más recomienda:
```C
// lorem
```



