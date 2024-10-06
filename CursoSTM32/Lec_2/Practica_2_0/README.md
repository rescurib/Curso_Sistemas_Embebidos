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

### Instalación del GNU Toolchain en Linux

```
sudo apt update
sudo apt install gcc-arm-none-eabi
```

Compilar
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

Enlazar
```Bash
# ------------------ Flags de Enlace------------------
# -T LinkerScript.ld : Especifica el script de enlace (define el diseño de memoria)
# -Wl,--gc-sections  : Elimina secciones no utilizadas para reducir el tamaño del binario
# -----------------------------------------------------------
arm-none-eabi-ld main.o -T LinkerScript.ld -o LedBlinking.elf 
```

Flashear
```Bash
# Convertir archivo ELF a BIN
arm-none-eabi-objcopy -O binary LedBlinking.elf LedBlinking.bin

# Flashear usando ST-Link. Si es exitoso (&&), ejecturar reset
st-flash write LedBlinking.bin 0x08000000 && st-flash reset 
```

