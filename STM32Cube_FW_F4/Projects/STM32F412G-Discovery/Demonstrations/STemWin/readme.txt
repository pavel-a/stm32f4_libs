/**
  @page Demo   STM32412G-DISCO Demonstration Firmware
 
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Demonstrations/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of STM32412G-DISCO Demonstration
  ******************************************************************************
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  @endverbatim

@par Demo Description

The STM32Cube Demonstration platform comes on top of the STM32CubeTM as a firmware
package that offers a full set of software components based on a modules architecture
allowing re-using them separately in standalone applications. All these modules are
managed by the STM32Cube Demonstration kernel allowing to dynamically adding new
modules and access to common resources (storage, graphical components and widgets,
memory management, Real-Time operating system)

The STM32Cube Demonstration platform is built around the powerful graphical library
STemWin and the FreeRTOS real time operating system and uses almost the whole STM32
capability to offer a large scope of usage based on the STM32Cube HAL BSP and several
middleware components.

@par Demo Description

The STM32 F4 demonstration is running on STM32412G-DISCO boards RevC. 

  
Below you find an overview of the different offered module in the demonstration:

 + Video player
 --------------
 The video player module provides a video solution based on the STM32F4xx and STemWin
 movie API. It supports playing movie in AVI format.
 
 + Audio player
 --------------
 The audio player module provides a complete audio solution based on the STM32F4xx and
 delivers a high-quality music experience. It supports playing music in WAV format but may
 be extended to support other compressed formats such as MP3 and WMA audio formats.
 The Module supports background mode feature.
 
  + Audio recorder
 -----------------
 The audio recorder module allows recording audio and playing it back.
 
 + Analog Clock
 ------------
 The analog clock module shows the the time and gives the possibility to set the time.
  
 + USB Devices
 ------------ 
 The USB device module includes mass storage device application using the MicroSD
 memory.
 
 + System Info
 --------------  
 The system info module provides information about the core, supported boards, 
 CPU speed and demonstration version.  
      
@par Hardware and Software environment

  - This application runs on STM32F412xx devices.  

  - This example has been tested with STMicroelectronics STM32412G_DISCO
    boards RevC and can be easily tailored to any other supported device 
    and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files
 - Open STM32 ST-Link Utility V4.1.0, click on "External Loader" from the bar menu then check "N25Q128A_STM32412G-DISCO" box 
 - Connect the STM32412G-DISCO board to PC with USB cable through CN6
 - Use "STM32CubeDemo_STM32412G-DISCO_VX.Y.Z.hex" file with STM32 ST-Link Utility to program both internal Flash and external QSPI memory
 - Run the demonstration
 - copy the audio and video files provided under "Utilities/Media/" in the SD Card
 - Plug SD Card on CN13 connector 
     
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 
