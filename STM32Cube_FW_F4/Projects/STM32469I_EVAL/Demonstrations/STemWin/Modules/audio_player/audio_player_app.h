/**
  ******************************************************************************
  * @file    audioplayer_app.h
  * @author  MCD Application Team
  * @brief   header of audio player application file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIO_PLAYER_APP_H
#define __AUDIO_PLAYER_APP_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "../Common/audio_if.h"

/* #define AUDIO_USE_SPIRIT_EQUALIZER */ /* Equalizer support removed for this version */
#ifdef AUDIO_USE_SPIRIT_EQUALIZER
#undef AUDIO_USE_SPIRIT_EQUALIZER /* Make sure Audio Equalizer support is disabled even if exported outside this file */
#endif

#if defined(AUDIO_USE_SPIRIT_EQUALIZER)
#include "spiritEQ.h"
#include "spiritLdCtrl.h"
#endif /* AUDIO_USE_SPIRIT_EQUALIZER */

/* Exported constants --------------------------------------------------------*/
#define MUTE_OFF                      0x00
#define MUTE_ON                       0x01
#define DEFAULT_AUDIO_VOLUME          50

#define CALIBRATION_AUDIOPLAYER_SETTING_BKP   RTC_BKP_DR0

#if defined(AUDIO_USE_SPIRIT_EQUALIZER)
#define CALIBRATION_AUDIOPLAYER_EQU1_BKP      RTC_BKP_DR1
#define CALIBRATION_AUDIOPLAYER_EQU2_BKP      RTC_BKP_DR2
#define CALIBRATION_AUDIOPLAYER_EQU3_BKP      RTC_BKP_DR3
#define CALIBRATION_AUDIOPLAYER_EQU4_BKP      RTC_BKP_DR4
#define CALIBRATION_AUDIOPLAYER_EQU5_BKP      RTC_BKP_DR5
#define CALIBRATION_AUDIOPLAYER_LOUD_BKP      RTC_BKP_DR6
#endif /* AUDIO_USE_SPIRIT_EQUALIZER */

#if defined(AUDIO_USE_SPIRIT_EQUALIZER)
#define EQUI_DB_TO_PERC(x)       (((int16_t)(x + SPIRIT_EQ_MAX_GAIN_DB) * 100)/40)
#define PERC_TO_EQUI_DB(x)       (((int16_t)(x - 50) * SPIRIT_EQ_MAX_GAIN_DB) / 50)
#define PERC_TO_LDNS_DB(x)       (1 << (SPIRIT_LDCTRL_GAIN_Q_BITS + (int16_t)(50 - x) *  8 / 100 ))  
   
/* Equalizer Band Configuration */
#define SET_BAND_PRMS(band, _fltType, _centerHz, _widthHz, _gainDb) \
  (band)->fltType = _fltType; \
  (band)->centerHz = _centerHz; \
  (band)->widthHz = _widthHz; \
  (band)->gainDb = _gainDb;
#endif /* AUDIO_USE_SPIRIT_EQUALIZER */

typedef enum
{
  AUDIOPLAYER_ERROR_NONE = 0, 
  AUDIOPLAYER_ERROR_IO,
  AUDIOPLAYER_ERROR_HW, 
  AUDIOPLAYER_ERROR_MEM, 
  AUDIOPLAYER_ERROR_FORMAT_NOTSUPPORTED,   
  
}AUDIOPLAYER_ErrorTypdef;

#define AUDIOPLAYER_StateTypdef  OUT_StateTypdef
/* Exported types ------------------------------------------------------------*/


/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Init(uint8_t volume);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Play(uint32_t frequency);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Stop(void);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Pause(void);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Resume(void);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Mute(uint8_t state);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_GetFileInfo(char* file, WAV_InfoTypedef* info);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_SelectFile(char* file);
AUDIOPLAYER_StateTypdef  AUDIOPLAYER_GetState(void);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_Process(void);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_DeInit(void);
uint32_t                 AUDIOPLAYER_GetProgress (void);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_SetVolume(uint32_t volume);
uint32_t                 AUDIOPLAYER_GetVolume(void);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_NotifyEndOfFile(void);
AUDIOPLAYER_ErrorTypdef  AUDIOPLAYER_SetPosition(uint32_t position);

#if defined(AUDIO_USE_SPIRIT_EQUALIZER)
void AUDIO_SetEq(uint8_t BandNum, int16_t NewGainValue);
void AUDIO_SetEqParams(uint32_t loudness_perc);
void AUDIO_SetLoudnessGain(int16_t NewGainValue);
#endif /* AUDIO_USE_SPIRIT_EQUALIZER */

#ifdef __cplusplus
}
#endif

#endif /*__AUDIO_PLAYER_APP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
