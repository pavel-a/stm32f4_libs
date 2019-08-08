This repo contains unofficial archive of STM32CubeF4 libraries (www.st.com) we are interested in.

See wiki for more details.

Versions:
* 1.24.1 - June? 2019
* 1.24 - Feb. 2019
* 1.23
* 1.21
* 1.19
* 1.18

**Release notes** are in STM32Cube_FW_F4/Release_Notes.html

[Official repository](https://github.com/STMicroelectronics/STM32CubeF4) - starts from version 1.24.1

[ST website to check for CubeMX pack updates](https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32cube-mcu-mpu-packages/stm32cubef4.html)

The STM32 libraries and demo projects have separate branches per the MCU family:
F0 for STM32F0xxx, F4 for STM32F4xxx, and so on.

To get a specific version, check it out so that directory STM32Cube_FW_F4 in the repo
maps to a directory named STM32Cube_FW_F4_Vx.y.z

For example, label F4_V1.18.0 goes to STM32Cube_FW_F4_V1.18.0


The root directory of the repo can map to ...[STM32Cube]/Repository/
so the complete path to the version would be 
   ...[STM32Cube]/Repository/STM32Cube_FW_F4_V1.18.0

**Patches** go into STM32Cube_FW_F4/patches/Vx.y directory, and are applied relative to STM32Cube_FW_F4 .
