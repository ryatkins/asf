/**
 * \file
 *
 * \brief SAM DA1 Xplained Pro test configuration.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef CONF_TEST_H_INCLUDED
#define CONF_TEST_H_INCLUDED

#define CONF_STDIO_USART          EDBG_CDC_MODULE
#define CONF_STDIO_MUX_SETTING    EDBG_CDC_SERCOM_MUX_SETTING
#define CONF_STDIO_PINMUX_PAD0    EDBG_CDC_SERCOM_PINMUX_PAD0
#define CONF_STDIO_PINMUX_PAD1    EDBG_CDC_SERCOM_PINMUX_PAD1
#define CONF_STDIO_PINMUX_PAD2    EDBG_CDC_SERCOM_PINMUX_PAD2
#define CONF_STDIO_PINMUX_PAD3    EDBG_CDC_SERCOM_PINMUX_PAD3
#define CONF_STDIO_BAUDRATE       38400

/* I2S module used for test */
#define CONF_TEST_I2S             I2S

/* Test RX or control signals, must add hw connection on board:
 * SCK0 -> SCK1, FS0 -> FS1. */
#define CONF_TEST_CTRL_RX         true

/* SCK0 */
#define CONF_TEST_SCK_TX_PIN      PIN_PA10G_I2S_SCK0
#define CONF_TEST_SCK_TX_MUX      MUX_PA10G_I2S_SCK0
/* FS0 */
#define CONF_TEST_FS_TX_PIN       PIN_PA11G_I2S_FS0
#define CONF_TEST_FS_TX_MUX       MUX_PA11G_I2S_FS0
/* SCK1 */
#define CONF_TEST_SCK_RX_PIN      PIN_PB11G_I2S_SCK1
#define CONF_TEST_SCK_RX_MUX      MUX_PB11G_I2S_SCK1
/* FS1 */
#define CONF_TEST_FS_RX_PIN       PIN_PB12G_I2S_FS1
#define CONF_TEST_FS_RX_MUX       MUX_PB12G_I2S_FS1


#endif /* CONF_TEST_H_INCLUDED */
