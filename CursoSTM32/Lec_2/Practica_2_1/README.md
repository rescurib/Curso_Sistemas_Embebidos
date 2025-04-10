# Práctica 2.1: Encedido de leds con libreria ST

En esta práctica usaremos el generador de código STM32CubeMX y usaremos la librería de periféricos de ST. La aplicación en si misma será muy sencilla: un botón que controla en modo toggle a un LED verde, y un segundo botón que refleja su estado en un LED rojo:

(Diagrama en Frizting)

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
En la práctica 2.0 utilizamos el cumpilador, el ensamlador y el linker para la arqutectura ARM así como tambien las utilizades del st-link, todo desde terminal paso a paso. Podemos crear un Makefile que automatice todo el proceso de la siguiente forma:

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
Observen que añadimos incluso reglas para remover archivos generados y también una regla para flashear. Intenten correr nuevamente la práctica 2.0 con:

```bash
$ make all
$ make flash
```
Para entender a fondo como escribir Makefiles, recomiendo revisar la [documentación oficial de GNU make](https://www.gnu.org/software/make/manual/html_node/index.html).

## Creación de proyecto con STM32CubeMX
Primero ir a ACCESS TO MCU SELECTOR y buscar STM32F103C8T6 (el MCU de la tarjeta Blue Pill).

* Entradas digitales: B0, B1
* Salidas digitales:  B8 y B9

La guía de usuario de la HAL y drivers de bajo nivel para los dispositivos STM32F1 esta en el documento [UM1850](https://www.st.com/resource/en/user_manual/um1850-description-of-stm32f1-hal-and-lowlayer-drivers-stmicroelectronics.pdf).
