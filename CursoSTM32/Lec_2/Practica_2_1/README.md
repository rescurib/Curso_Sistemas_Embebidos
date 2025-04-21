# Práctica 2.1: Encedido de leds con libreria ST

En esta práctica usaremos el generador de código STM32CubeMX y usaremos la librería de periféricos de ST. La aplicación en si misma será muy sencilla: un botón que controla en modo toggle a un LED verde, y un segundo botón que refleja su estado en un LED rojo:

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/CursoSTM32/Lec_2/Practica_2_1/P1_2_Circuit_BB.png" width="650">
<p>

Lo más valioso de esta práctica es la manera en la que lo vamos a hacer. Originalmente pensaba usar STM32CubeIDE pero recordé el propósito de este curso: enseñar a hacer dispositivos científicos e industrial de primer nivel. Hay muchos tutoriales que enseñan a usar IDEs. Desarrollar firmware usando gestores de dependencias como make y compilar desde terminal puede parecer innesariamente complicado, incluso arcaico, al principio. Es una paradoja del desarrollo embebido; aprender el duro camino de configurar un proyecto en make (o CMake) facilitará enormemente las cosas a mediano plazo (*build* automatizado, pruebas unitarias, analisis de sintaxis, contenedores y *pipelines* en la nube). Esto es difícil de ver en proyectos tan simples como el de esta práctica pero creeme, en proyectos grandes del mundo real valdrá cada hora que inviertas en aprender a hacer esto (también es mi trabajo encargarme de enseñarlo de la manera más clara y referenciada que pueda).

## GNU make

GNU Make es una herramienta de automatización de compilación utilizada para construir programas a partir de su código fuente. Su función principal es detectar qué partes de un programa necesitan recompilarse y ejecutar los comandos necesarios para hacerlo, todo esto definido en un archivo llamado Makefile. Así no perdemos tiempo en re-compilar código que no tenga cambios. Aunque su poder principal radica en la flexibilidad y la automatización que nos da el script del Makefile.

Para instalar en Linux (Debian y distros derivadas):
```bash
sudo apt install make
```
Aunque es buena idea asegurarnos que tengamos todas las herramientas de desarrollo con:
```bash
sudo apt install build-essential
```

Para instalar en Windows con MYSYS2, abrir la terminal UCRT y ejecutar:

```bash
pacman -Syu
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```
Para ambos sistemas estoy asumiendo que ya instalaron las herramientas de ARM que usamos en la práctica 2.0.

El Makefile es muy parecido a un lenguaje de scripting como Bash o Bat. Por ejemplo, hacemos un "Hola Mundo" de make creando un archivo con el nombre de Makefile (así, sin extención) con este contenido:

```make
hello:
	echo "Hola, make!"
```
**NOTA**: usar tab para las instrucciones.

Y ejecutamos con:

```bash
$ make hello
echo "Hola, make!"
Hola, make!
```
Observa que imprime tanto los comandos de consola como el resultado de ejecutar el comando.

De forma general, un script de make consiste en un conjunto de reglas asociados a *targets* con la siguiente estructura:
```make
targets: pre-requisitos
	comando
	comando
	comando
```
* Los *targets* son archivos (o una etiqueta para un conjunto de instrucciones), separados por espacios. Generalmente solo hay uno por regla.
* Los comandos son una serie de pasos (comandos de bash) que usamos para compilar, ensamblar, linkear, etc. Inician con un tab, nunca espacios.
* Los pre-requisitos son archivos de dependencias (código fuente, codigos objetos, scripts de linker, etc). Estos archivos necesitan existir para el target pueda ser creado.

Podemos crear varibles que nos facilitan la escritura de las reglas ya pueden empaqutar cosas como directorios muy largos, conjuntos de archivos y múltiples banderas de compilación.

### Script de make para la práctica anterior
En la práctica 2.0 utilizamos el cumpilador, el ensamblador y el linker para la arqutectura ARM así como tambien las utilidades para st-link, todo desde terminal paso a paso. Podemos crear un Makefile que automatice todo el proceso de la siguiente forma:

```bash
# -------------------------------------
#       Definición de Variables
# -------------------------------------
# Herramientas
CC      = arm-none-eabi-gcc
AS      = arm-none-eabi-as
LD      = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
FLASH   = st-flash

# Archivos
SRC     = main.c
ASM     = main.s
OBJ     = main.o
ELF     = LedBlinking.elf
BIN     = LedBlinking.bin
LD_SCRIPT = LinkerScript.ld

# Flags de compilación
CFLAGS  = -mcpu=cortex-m3 -mthumb -Wall -O0 -nostartfiles -nostdlib

# Flags de ensamblado
ASFLAGS = -mcpu=cortex-m3 -mthumb

# Dirección de memoria para flashear
FLASH_ADDR = 0x08000000

# -------------------------------------
#               Reglas
# -------------------------------------

all: $(BIN)

$(ASM): $(SRC)
	$(CC) $(CFLAGS) -S $< -o $@

$(OBJ): $(ASM)
	$(AS) $(ASFLAGS) $< -o $@

$(ELF): $(OBJ)
	$(LD) $< -T $(LD_SCRIPT) -o $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

flash: $(BIN)
	$(FLASH) write $(BIN) $(FLASH_ADDR) && $(FLASH) reset

clean:
	rm -f $(ASM) $(OBJ) $(ELF) $(BIN)

.PHONY: all flash clean
```
Observen que añadimos incluso reglas para remover archivos generados y también una regla para flashear. La directiva .PHONY sirve justamente para indicar de forma explícita que esos *targets* no son realmente archivos sino etiquetas de secuencias de comandos. 

Intenten correr nuevamente la práctica 2.0 con:

```bash
$ make all
$ make flash
```
Para entender a fondo como escribir Makefiles, recomiendo revisar la [documentación oficial de GNU make](https://www.gnu.org/software/make/manual/html_node/index.html).

## Creación de proyecto con STM32CubeMX
En este punto sería injusto crear desde cero un projecto funcional (listo para una aplicación real) desde 0 ya que hay muchas cosas de las que no hemos hablado como el *startup code* o la tabla vectorial (lo harémos y daré referencias en su momento), ya no mencionar la cureación de un Makefile que ponga todo en su lugar. Afortunadamente existen herramientas de generación de código de inicialización (startup code, linker script, Makefile...) que además proveen de librerías para el control de los periféricos del microcontrolador y funcionalidades/configuración del procesador ARM Cortex-M3. Este es el caso de STMCubeMX. No se debe confundir con STM32CubeIDE, que contiene en si el generador de código pero provee adempas de un entorno gráfico de desarrollo. STMCubeMX nos dejara todo listo para que solo nos encargamos del código de nuestra aplicación y le demos *make all*.

Descargamos STMCubeMX desde el [sitio de ST](https://www.st.com/en/development-tools/stm32cubemx.html) (disponible para Linux, Windows y Mac). Posiblemente requerirá registro. 

Un vez instalado y abierto el programa, primero ir a ACCESS TO MCU SELECTOR y buscar STM32F103C8T6 (el MCU de la tarjeta Blue Pill). Después de esperar un poco, aparecer la ventana principal del proyecto. La pestaña que debe estar abierta por defecto es Pinout Configuration. En la columna izquierda, desplegamos la pestaña vertical System Core y seleccionamos GPIO. Ahora acomodamos la vista del Pinout Overview hasta que se vea como en la captura y hacemos click los pines de interés. Se desplegaran las configuraciones posibles. En esta práctica:
* Entradas digitales: B0, B1
* Salidas digitales:  B12 y B13
  
En la ventana central podemos darle nombres de etiqueta a los pines (*User Label*). Así se vería nuestra configuración de pines en STM32CubeMX:
<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1NybCgF8aPjf_r8tBFaxDB1T-bPgkH48m" width="830">
<p>

Después de configurar los pines, es muy importante hacer la siguiente configuración de puerto JTAG. Por defecto, STM32CubeMX desactiva el puerto para depuración. Esto ocasionará errores al intentar leer/borrar la memoria o cargar. Afortunadamente esto es reversible y habrá un apéndice al final de la lección. Pero ahora vamos a evitarlo de la siguiente manera. Dentro de la misma pestaña *System Core*, da click en la sección *SYS* y en el campo *Debug* seleccionemos la opción *Serial Wire*: 

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=1CnKP3TW2kQLqSGFr6uhQMh7jMEAxaszg" width="600">
<p>



## Programa principal

La guía de usuario de la HAL y drivers de bajo nivel para los dispositivos STM32F1 esta en el documento [UM1850](https://www.st.com/resource/en/user_manual/um1850-description-of-stm32f1-hal-and-lowlayer-drivers-stmicroelectronics.pdf).

```C
/* USER CODE BEGIN WHILE */
while (1)
{
  /* Leer PB0 y hacer toggle de PB12 si está en alto */
  if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_SET)
  {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
    HAL_Delay(200); // Pequeño retardo para evitar múltiples toggles rápidos
  }

  /* Leer PB1 y copiar su estado a PB13 */
  GPIO_PinState pinState = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, pinState);

  /* USER CODE END WHILE */
}
```

## Compilación y flasheado

**PRO-TIP**: st-tools no es una aplicación soportada oficialmente por ST. Es recomendable usar STM32_Programmer_CLI. Tiene además muchas más opciones de configuración y está disponible de forma nativa para Linux, Windows y Mac.

Descargamos e instalamos  [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html). En caso de que no se haga por defecto, en Linux agregamos al path de esta forma:
```bash
echo 'export PATH="$PATH:/opt/stm32cubeprogrammer/bin"' >> ~/.bashrc
```
En Windows hay que agregar el directorio en donde está el ejecutable a la variable de entorno *PATH*. Hecho esto ahora podrá ejecutarse en terminal desde cualquier directorio.

### Cargar programa:
```bash
STM32_Programmer_CLI -c port=SWD -w build/BluePill_P2_1.bin 0x08000000 -v -rst
```

Para mayor comodidad, podemos agregar un *target* al Makefile para flashear:

```make
flash: $(BUILD_DIR)/$(PROJECT_NAME).bin
	STM32_Programmer_CLI -c port=SWD -w $< 0x08000000 -v -rst
```
## APÉNDICE: Desbloquear JTAG de la Blue Pill

Si olvidaste habilitar la interfaz de depuración serial, posiblemente estas viendo un mensaje de error como este:
```Bash
$ st-flash erase

st-flash 1.8.0

libusb: info [get_guid] no DeviceInterfaceGUID registered for 'USB\VID_174F&PID_1176\5&B3F4C82&0&7'

libusb: info [get_guid] no DeviceInterfaceGUID registered for 'USB\VID_8087&PID_0AAA\5&B3F4C82&0&10'

libusb: info [get_guid] no DeviceInterfaceGUID registered for 'USB\ROOT_HUB30\4&1D2E5277&0&0'

libusb: info [get_guid] no DeviceInterfaceGUID registered for 'USB\VID_174F&PID_1176&MI_00\6&29E09720&0&0000'

Failed to enter SWD mode
Failed to connect to target
Failed to parse flash type or unrecognized flash type
```

O usando STM32CubeProgrammer:
```Bash
no stm32 target found! if your product embeds debug authentication,
please perform a discovery using debug authentication
```
### Solución 
Presionar el botón de reset de la Blue Pill, ejecutar el siguiente comando (y soltar tan pronto se impriman las primeras letras):
```Bash
st-flash --connect-under-reset erase
```
y verificar con:
```Bash
st-info --probe
```

O con STM32_Programer_CLI (mismo proceso):
```Bash
STM32_Programmer_CLI -c port=SWD mode=UR -e all
```
y verificar con:
```Bash
STM32_Programmer_CLI -c port=SWD
```

