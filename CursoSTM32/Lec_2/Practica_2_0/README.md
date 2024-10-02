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

[pendiente]


```
sudo apt update
sudo apt install gcc-arm-none-eabi
```

Para compilar
```
arm-none-eabi-gcc main.o -T LinkerScript.ld -o output.elf
```
