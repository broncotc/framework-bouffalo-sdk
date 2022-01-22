/*
 * Copyright (c) 2020 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __BL_DAC_AUDIO_H__
#define __BL_DAC_AUDIO_H__

#include <stdint.h>
#include <bl602_dma.h>
#include <bl_dma.h>
#include "bl602_dac.h"

typedef int (*audio_callback_rx_ready_t)(void *usrdata, uint8_t *audiodata, int len, int is_overflow);
typedef int (*audio_callback_tx_ready_t)(void *uerdata, uint8_t *audiodata, int len, int is_underrun);

typedef struct {
    uint8_t pingpang;
    DMA_LLI_Ctrl_Type lli_list[2];
    uint8_t *lli_tx_buffer;
    uint32_t lli_tx_buffer_size;

    int is_underrun;
    audio_callback_tx_ready_t usr_cb;
    void *p_usr_arg;

} bl_audio_dac_dev_t;

int bl_audio_dac_init (bl_audio_dac_dev_t *p_dev);

int bl_audio_dac_deinit (bl_audio_dac_dev_t *p_dev);

int bl_audio_dac_start (bl_audio_dac_dev_t *p_dev);

int bl_audio_dac_stop (bl_audio_dac_dev_t *p_dev);

int bl_audio_dac_tx_buffer_config (bl_audio_dac_dev_t *p_dev,
                                   void **ptr_mem,
                                   uint32_t bufsize);

int bl_audio_dac_rx_buffer_config (bl_audio_dac_dev_t *p_dev,
                                   void **ptr_mem,
                                   uint32_t bufsize);

int bl_audio_dac_tx_ready_config(bl_audio_dac_dev_t *p_dev,
                                 audio_callback_tx_ready_t cb,
                                 void *p_arg);

int bl_audio_dac_rx_ready_config(bl_audio_dac_dev_t *p_dev,
                                 audio_callback_rx_ready_t cb,
                                 void *p_arg);

int bl_audio_dac_samplerate_set (bl_audio_dac_dev_t *p_dev,
                                 GPIP_DAC_MOD_Type samplerate);

#endif
