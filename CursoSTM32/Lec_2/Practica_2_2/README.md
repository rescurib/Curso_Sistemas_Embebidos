# Práctica 2.2: Toggle con anti-rebote mejorado

Esta práctica tendrá el mismo circuito y función que la anterior, un led rojo controlado en modo toggle por el switch 1 y un led verde controlado en modo directo por el switch 2:

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/CursoSTM32/Lec_2/Practica_2_1/P1_2_Circuit_BB.png" width="600">
<p>

La diferencia es que implementarémos la operación toggle de una manera que tiene dos características muy utiles:
* No dependerá de *retardos bloqueantes*.
* El switch tendrá uno de los mejores filtros anti-rebote implementados por software.

Vayamos por partes. ¿Qué son los rebotes en el botón y por qué necesitamos mitigarlos en primer lugar?

## Rebotes mecánicos en los *push-buttons*

En la realidad física, las transiciones de estado nunca son limpias, sino que ocurren con *transientes*, es decir, con perturbaciones iniciales que eventualmente se estabilizan. En el caso de los push-buttons, estos transcientes ocurren principalmente porque al presionarlos o soltarlos, el contacto metálico rebota y cierra y abre el circuito hasta que se estabiliza. Las siguientes señales las tomé, del switch 1 del circuito mostrado, con un osciloscopio en modo de captura única y muestran algunos de estos rebotes:
<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=15YZivMvWPZrD1kXMdfTqFdUzCK8HrMYh" width="550">
</p>
<p align="center"><em>Figura 1: Rebotes en flanco de subida.</em></p>

<p align="center">
  <img src="https://drive.google.com/uc?export=view&id=1PTFuFFSp8C6vYdPZ5TV7vLegOqPadNUJ" width="550">
</p>
<p align="center"><em>Figura 2: Rebotes en flanco de bajada.</em></p>

Estos rebotes no siempre ocurren. Dependen de muchos factores incluyendo el modelo o el ejemplar de botón. Pero ocurren esporádicamente y el modo toggle o las operaciones de conteo de pulsaciones son particularmente sencibles a estos rebotes.

## Algoritmo antirebote

En la práctica anterior usamos el método antirebote más simple que es entrar a un retardo bloqueante después de detectar nivel alto en el pin y volver a leer el pin al finalizar el retardo para verificar el cambio de estado. Este método tiene la desventaja de que el microcontrolador no puede hacer nada mas durante ese retardo y tampoco puede adaptarse a transientes de diferente duración.

Jack Ganssle tiene un [excelente artículo](https://www.ganssle.com/debouncing-pt2.htm) dónde recopila y discute varios métodos de mitigación de rebotes. En esta práctica vamos a implementar el algoritmo que más recomienda:
```C
/**
  * @brief  Función anti-rebote.
  * @retval Verdadero cuando se detecta una transición de subida estable,
  *         Falso en caso contrario.
  */
bool sw_1_debounce(void)
{
    g_SW1_state = (g_SW1_state<<1) | !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) | 0xe000;

    if( g_SW1_state==0xf000 )
    {
       return true;
    }

    return false;
}
```
La función sw_1_debounce() se ejecuta de forma periodica (cada 2ms en esta práctica). Aunque esta función antirebote tiene muy pocas lineas, su funcionamiento no es muy evidente. Vamos a examinarla con la siguiente simulación hecha con [GNU Octave](https://octave.org/):

<p align="center">
  <img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/CursoSTM32/Lec_2/Practica_2_2/button_debounce_anim.gif" width="560">
</p>

El código con el que generé esta gráfica animada esta en el archivo [DebounceGanssleSim_GIF_v2.m](https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/CursoSTM32/Lec_2/Practica_2_2/DebounceGanssleSim_GIF_v2.m). Lo que podemos notar es que esta función se comporta como un detector de flacos de subida estables. La función retorna *True* sólo en el momento en que el último 1 llega a hacia los bits más significativos. El valor *0xe000* lo único que hace ajustar el tiempo de detección de estabilidad de manera fina.

## Programa principal

```C
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* Obtener tick de systema (ms) */
    uint32_t now = HAL_GetTick();

    if ( (now - last_tick) >= 2 ) // Intervalo de 2 ms.
    {
        /* Si el intervalo se cumple, ejecutar anti-rebote */
        last_tick = now;
        if ( sw_1_debounce() )
        {
          HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
        }
    }

    /* Leer PB1 y copiar su estado a PB13 */
    GPIO_PinState pinState = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, pinState);

    /* USER CODE END WHILE */
```



