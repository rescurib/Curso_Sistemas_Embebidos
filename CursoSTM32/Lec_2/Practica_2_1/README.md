# Práctica 2.1: Encedido de led con libreria ST

## Make

```bash
pacman -Syu
pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain
```

## Creación de proyecto con STM32CubeMX
Primero ir a ACCESS TO MCU SELECTOR y buscar STM32F103C8T6 (el MCU de la tarjeta Blue Pill).

Entradas digitales: B0, B1
Salidas digitales:  B8 y B9
