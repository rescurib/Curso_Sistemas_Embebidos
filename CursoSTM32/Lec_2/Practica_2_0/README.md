# Práctica 2.0
En esta práctica compilaremos y cargaremos a la Blue Pill un programa de blinkeo sencillo pero lo harémos sin utilizar el asistente de proyecto. 

## Con STMCube IDE

Primero creamos un proyecto haciendo click en File->New->C/C++ Project. Seleccionamos Project Type: Empty Project y Toolchain: MCU ARMG GCC.

<p align="center">
<img src="https://drive.google.com/uc?export=view&id=19SU_XpNq8IU88xGeL3euPZn8kl2klYrN" width="830">
<p>

Para este programa vamos a necesitar 3 archivos:
* main.c
* main.h
* LinkerScript.ld

Creamos los archivos en blanco en File->New->Source File, File->New->Header File y File->New->File from Template, respectivamente. 

## Sin IDE (gcc-arm-none-eabi desde terminal)

### Instalación del GNU Toolchain

**GCC** (GNU Compiler Collection) es un conjunto de compiladores de código abierto que soporta varios lenguajes de programación, incluyendo C y C++. **arm-none-eabi-gcc** es una variante específica del compilador GCC diseñada para la programación de microcontroladores ARM. *EABI* significa *"Embedded Application Binary Interface"*, lo que implica que está optimizado para entornos embebidos. El *none* en el prefijo significa también que no incluye las características para sistema operativo que se encontrarían en compiladores como arm-linux-gnueabi-gcc, que está diseñado para procesadores que corraran Linux.

En distros de Linux basadas en Debian:
```Bash
sudo apt update
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi openocd stlink-tools
```

En Windows la forma que recomiendo es instalar el entorno *UNIX-like* [MYSYS2](https://www.msys2.org/) Después instalar con Pacman:

```Bash
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-gcc arm-none-eabi-gcc arm-none-eabi-binutils openocd stlink-tools
```

Apartir de aquí, todos comandos de terminal que se mencionen aplicarán para ambos sistemas operativos.

se verifica instalación con:
```Bash
arm-none-eabi-gcc --version
openocd --version
st-info --version
```

**TIP**: ya que usaremos varios argumentos para cada comando, es bueno tener en cuenta los siguientes atajos de teclado para la terminal (también funcionan para la terminal de MYSYS2/MINGW64):
* Ctrl + <*flechas*>  -> Moverse entre argumentos
* Ctrl + w -> Borra argumento/commando antes del cursor

**REFERENCIA**: Leer *C in a Nutshell [2Ed.]*, Prinz- Crawford, Ch. 19: Compiling with GCC, Pag. 669

### Proceso de construcción de un programa en C

[Pendiente]

### Construcción de nuestro ejemplo de blinking mínimo

Compilar:
```Bash
# -------------------- Flags de Compilación --------------------
# -mcpu=cortex-m3: Especifica el CPU objetivo (Cortex-M3)
# -Wall          : Habilita todas las advertencias
# -O0            : Sin optimización para fines de depuración
# -nostartfiles  : No usar los archivos de inicio estándar 
# -nostdlib      : No usar biblioteca estándar de C durante enlace
# ---------------------------------------------------------------
arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Wall -O0 -nostartfiles -nostdlib -c main.c -o main.o
```

Enlazar:
```Bash
# ------------------ Flags de Enlace------------------
# -T LinkerScript.ld : Especifica el script de enlace (define el diseño de memoria)
# -Wl,--gc-sections  : Elimina secciones no utilizadas para reducir el tamaño del binario
# -----------------------------------------------------------
arm-none-eabi-ld main.o -T LinkerScript.ld -o LedBlinking.elf 
```

Flashear:
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

