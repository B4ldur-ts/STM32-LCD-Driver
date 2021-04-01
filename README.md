# STM32-LCD-Driver

A simple LCD driver for the ST7066U or other compatible Displays (e.g. HD44780). Optimized for the STM32-Family.

## Instructions

Put the files into the "src"-folder. Adjust your settings like your connections in the settings.h. Switch between 4Bit and 8Bit Mode by commenting the specific lines out. This library is suited for the g0 aswell as the f0-Series. Adjust accordingly.
To use this library with the buitlin HAL-function use the unspecified .c-File. For use without it the specified one.
