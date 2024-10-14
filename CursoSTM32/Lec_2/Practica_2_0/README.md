# Práctica 2.0
En esta práctica compilaremos y cargaremos a la Blue Pill un programa de blinkeo sencillo pero lo harémos sin utilizar el asistente de proyecto. 

## Con STMCube IDE
**Creación del proyecto**

Primero creamos un proyecto haciendo click en `File->New->C/C++ Project`. Seleccionamos Project Type: Empty Project y Toolchain: MCU ARMG GCC.

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=19SU_XpNq8IU88xGeL3euPZn8kl2klYrN" width="830">
<p>

Para este programa vamos a necesitar 3 archivos:
* main.c
* main.h
* LinkerScript.ld

Creamos los archivos en blanco en `File->New->Source File`, `File->New->Header File` y `File->New->File from Template`, respectivamente. 

**Compilar (*Build*) el Proyecto**

Para compilar el proyecto y generar el binario:

1. Haz clic derecho sobre el nombre de tu proyecto en el `Project Explorer`.
2. Selecciona `Build Project` o presiona `Ctrl+B`.
3. En la consola verás la salida del proceso de compilación. Asegúrate de que no haya errores.

**Flashear el Código a la Placa (ST-Link)**

1. Conecta tu Blue Pill a tu computadora utilizando un programador ST-Link.
2. En STM32CubeIDE, haz clic en el menú superior `Run -> Debug Configurations`.
3. Selecciona `STM32 MCU C/C++ Application` bajo la opción de `GDB OpenOCD Debugging`.
4. En la pestaña `Debugger`, asegúrate de que esté seleccionada la opción `ST-LINK (OpenOCD)` en el campo `Interface`.
5. Haz clic en `Apply` y luego en `Debug` para flashear el código y comenzar a depurar.
6. Si prefieres ejecutar el código sin depuración, selecciona `Run -> Run As -> STM32 MCU C/C++ Application`.

## Sin IDE (gcc-arm-none-eabi desde terminal)

### Instalación del GNU Toolchain

**GCC** (GNU Compiler Collection) es un conjunto de compiladores de código abierto que soporta varios lenguajes de programación, incluyendo C y C++. **arm-none-eabi-gcc** es una variante específica del compilador GCC diseñada para la programación de microcontroladores ARM. *EABI* significa *"Embedded Application Binary Interface"*, lo que implica que está optimizado para entornos embebidos. El *none* en el prefijo significa también que no incluye las características para sistema operativo que se encontrarían en compiladores como arm-linux-gnueabi-gcc, que está diseñado para procesadores que corraran Linux.

En distros de Linux basadas en Debian:
```Bash
sudo apt update
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi openocd stlink-tools
```

En Windows la forma que recomiendo es instalar el entorno *UNIX-like* [MYSYS2](https://www.msys2.org/) Eligiendo el [*ambiente*](https://www.msys2.org/docs/environments/) UCRT64, instalar con Pacman:

```Bash
pacman -Syuu
pacman -S mingw-w64-ucrt-x86_64-arm-none-eabi-gcc mingw-w64-ucrt-x86_64-arm-none-eabi-binutils mingw-w64-ucrt-x86_64-openocd mingw-w64-ucrt-x86_64-stlink
```
NOTA: Puedes usar la consola UCRT64 pero si quieres usar el GNU toolchain desde CMD, debes añadir a la variable de entorno de sistema PATH este directorio: C:\msys64\ucrt64\bin

Apartir de aquí, todos comandos de terminal que se mencionen aplicarán para ambos sistemas operativos.

se verifica instalación con:
```Bash
arm-none-eabi-gcc --version
openocd --version
st-info --version
```

**TIP**: ya que usaremos varios argumentos para cada comando, es bueno tener en cuenta los siguientes atajos de teclado para la terminal (también funcionan para las terminales de MYSYS2):
* Ctrl + <*flechas*>  -> Moverse entre argumentos
* Ctrl + w -> Borra argumento/commando antes del cursor

**REFERENCIA**: Leer *C in a Nutshell [2Ed.]*, Prinz- Crawford, Ch. 19: Compiling with GCC, Pag. 669

### Proceso de construcción de un programa en C

El término *build* en el desarrollo de programas en C/C++ se refiere al conjunto de actividades y pasos necesarios para convertir el código fuente en un *artefacto* ejecutable, en este caso, un binario flasheable que el microcontrolador pueda ejecutar correctamente. El proceso completo puede resumirse en el siguiente diagrama:

<p align="center">
<img src="https://github.com/rescurib/Curso_Sistemas_Embebidos/blob/main/Diagramas/C_Build_Process.png">
<p>

Hay algunos pasos, como el preprocesamiento de macros, que no aparecen explicitamente en el diagrama para facilitar el entendimiento de la imagen completa. Por ahora vamos a concentrarnos en los más importantes:

* **Compilación**. Aunque se suele usar esta palabra para referse al *build process* entero, en realidad la compilación es el proceso que toma como entrada el código fuente en C y produce código en ensamblador.
* **Ensamble**. El proceso que toma como entrada los archivos en ensamblador y produce *objetos* de código máquina.
* **Enlazado**. El proceso de combinar los archivos objeto generados por el compilador en un único archivo ejecutable. Esto se logra con algo llamado resolución de *símbolos*.

Para entender a detalle este proceso, recomiendo las siguientes lecturas en este orden:

1. **Computer Organization and Design [RISC-V ED]**, Patterson-Henessey
    * 2.12 *Translating and Starting a Program*
    * 2.13 *A C Sort Example to Put it All Together*
2. **Mastering STM32 [2Ed]**, Carmine Noviello
    * 20.1.3 *Understanding Compilation and Linking Processes*
    * *20.2 The Really Minimal STM32 Application*

### Construcción de nuestro ejemplo de blinking mínimo

**Compilar**:
```Bash
# -------------------- Flags de Compilación --------------------
# -mcpu=cortex-m3: Especifica el CPU objetivo (Cortex-M3)
# -mthumb        : Conjunto de instrucciones Thumb
# -Wall          : Habilita todas las advertencias
# -O0            : Sin optimización para fines de depuración
# -nostartfiles  : No usar los archivos de inicio estándar 
# -nostdlib      : No usar biblioteca estándar de C durante enlace
# ---------------------------------------------------------------
arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Wall -O0 -nostartfiles -nostdlib -S main.c -o main.s
```
Si abrimos el archivo main.s, podremos ver nuestro programa traducido a instrucciones de ensamblador. Aquí va un pequeño segmento:
```assembly
delay:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	str	r0, [r7, #4]
	nop
```
**Ensamblar**:
```Bash
# -------------------- Flags de Ensamble --------------------
# -mcpu=cortex-m3: Especifica el CPU objetivo (Cortex-M3)
# -mthumb        : Conjunto de instrucciones Thumb
# ---------------------------------------------------------------
arm-none-eabi-as -mcpu=cortex-m3 -mthumb main.s -o main.o
```
Ya que los archivos objeto (.o) contien código máquina, no pueden visualizarse como texto plano. Una manera de inspeccionarlos es con la herramienta [arm-none-eabi-objdump](https://manpages.debian.org/bookworm/binutils-arm-none-eabi/arm-none-eabi-objdump.1.en.html):

```Bash
arm-none-eabi-objdump -s main.o
```

Lo que nos arrojará algo como esto:

```
main.o:     file format elf32-littlearm
Contents of section .text:
 0000 80b483b0 00af7860 00bf7b68 5a1e7a60  ......x`..{hZ.z`
 0010 002bfad1 00bf00bf 0c37bd46 80bc7047  .+.......7.F..pG
 0020 80b500af 124b9b69 114a43f0 10039361  .....K.i.JC....a
 0030 104b5b68 0f4a43f4 80135360 0d4b5b68  .K[h.JC...S`.K[h
 0040 0c4a23f4 40035360 0a4bdb68 094a43f4  .J#.@.S`.K.h.JC.
 0050 0053d360 0848fff7 feff064b db68054a  .S.`.H.....K.h.J
 0060 23f40053 d3600448 fff7feff 00bfebe7  #..S.`.H........
 0070 00100240 00100140 400d0300           ...@...@@...
```
Los 2 bytes más a la izquierda representan la posición en memoria. Estas son direcciones relativas porque este punto del *build* todos los archivos .o iniciaran en la dirección 0.

**Enlazar**:
```Bash
# ------------------ Flags de Enlace------------------
# -T LinkerScript.ld : Especifica el script de enlace (define el diseño de memoria)
# -Wl,--gc-sections  : Elimina secciones no utilizadas para reducir el tamaño del binario
# -----------------------------------------------------------
arm-none-eabi-ld main.o -T LinkerScript.ld -o LedBlinking.elf 
```
El archivo .elf contiene tambien código máquina pero con los símbolos resueltos. Si usamos nuevamente objdump notaremos algo peculiar:
```
.\LedBlinking.elf:     file format elf32-littlearm
Contents of section .text:
 8000000 00500020 29000008 80b483b0 00af7860  .P. ).........x`
 8000010 00bf7b68 5a1e7a60 002bfad1 00bf00bf  ..{hZ.z`.+......
 8000020 0c37bd46 80bc7047 80b500af 124b9b69  .7.F..pG.....K.i
 8000030 114a43f0 10039361 104b5b68 0f4a43f4  .JC....a.K[h.JC.
 8000040 80135360 0d4b5b68 0c4a23f4 40035360  ..S`.K[h.J#.@.S`
 8000050 0a4bdb68 094a43f4 0053d360 0848fff7  .K.h.JC..S.`.H..
 8000060 d3ff064b db68054a 23f40053 d3600448  ...K.h.J#..S.`.H
 8000070 fff7caff 00bfebe7 00100240 00100140  ...........@...@
 8000080 400d0300                             @...
````
¡La dirección del código comienza en 0x8000000! Justo como marca la documentación donde debería comenzar la región de memoria para la Flash.

**Flashear**:
```Bash
# Convertir archivo ELF a BIN
arm-none-eabi-objcopy -O binary LedBlinking.elf LedBlinking.bin

# Flashear usando ST-Link. Si es exitoso (&&), ejecturar reset
st-flash write LedBlinking.bin 0x08000000 && st-flash reset 
```
O de forma alternativa, también se puede usar OpenOCD:

```Bash
openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "init; reset halt; program LedBlinking.bin 0x08000000 verify; reset run; shutdown"
```
[OpenOCD](https://openocd.org/pages/documentation.html), u Open On-Chip Debugger, es una herramienta de software libre diseñada para la depuración y programación de dispositivos embebidos. Su principal función es facilitar la depuración de microcontroladores y sistemas integrados, permitiendo interactuar con el hardware a través de protocolos como JTAG y SWD. Hablaremos de él más adelante en el curso.

### Gestores de dependencias y *build systems*

En este punto se lo que deben estar pensando; *¿cómo es posible mantener un proyecto de firmware grande con tantos comandos y argumentos?* Pues bien, afortunadamente existen gestores de dependencias como [make](https://www.gnu.org/software/make/) y [CMake](https://cmake.org/) que permiten mantener y automatizar la contrucción de código en C/C++ a través de scripts. Usaremos make en futuras prácticas. Si quieren adelantarse, pueden revisar *C in a Nutshell [2Ed.]*, Prinz- Crawford, Ch. 20: Using make to Build C Programs, Pag. 695. 

