/**
 *
 * \file
 *
 * \brief WILC1000 Station Mode Example.
 *
 * Copyright (c) 2018 Microchip Technology Inc. and its subsidiaries.
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

/** \mainpage
 * \section intro Introduction
 * This example demonstrates the use of the WILC1000 with the SAM Xplained Pro
 * board to behave as a station.<br>
 * It uses the following hardware:
 * - the SAM Xplained Pro.
 * - the WILC1000 on EXT1.
 *
 * \section files Main Files
 * - main.c : Initialize the WILC1000 and connect AP as a station mode.
 *
 * \section usage Usage
 * -# Configure below code in sta.h for AP information to be connected.
 * \code
 *    #define MAIN_WLAN_SSID         "DEMO_AP"
 * \endcode
 * -# To connect to an unsecured AP, define below in sta.h
 * \code
 *    #define 	STA_MODE_OPEN_SECURITY
 * \endcode
 * -# To connect to a WPA/WPA2 personal secured AP, define below in sta.h
 * \code
 *    #define  	STA_MODE_WPA_WPA2_PERSONAL_SECURITY
 *    #define MAIN_WLAN_PSK         "12345678"
 * \endcode
 * -# To connect to a WEP with 10 digit key secured AP, define below in sta.h
 * \code
 *   #define 	STA_MODE_WEP_SECURITY
 *   #define	WEP_SEC_TYPE_KEY_40
 *   #define	MAIN_WLAN_WEP_KEY_INDEX         1
 *   #define	MAIN_WLAN_WEP_AUTH_TYPE   	 	WEP_ANY
 *   #define	MAIN_WLAN_WEP_KEY               "1234567890"
 * \endcode
 * -# To connect to a WEP with 26 digit key secured AP, define below in sta.h
 * \code
 *   #define 	STA_MODE_WEP_SECURITY
 *   #define	WEP_SEC_TYPE_KEY_104
 *   #define	MAIN_WLAN_WEP_KEY_INDEX         1
 *   #define	MAIN_WLAN_WEP_AUTH_TYPE   	 	WEP_ANY
 *   #define	MAIN_WLAN_WEP_KEY               "1234567890abcdef1234567890"
 * \endcode
 * -# To connect to a WPA/WPA2 Enterprise secured AP, define below in sta.h
 * \code
 *   #define 	STA_MODE_WPA_WPA2_ENTERPRISE_SECURITY
 *   #define MAIN_WLAN_802_1X_USR_NAME       "atmeluser"
 *   #define MAIN_WLAN_802_1X_PWD            "12345678"
 * \endcode
 * -# Build the program and download it into the board.
 * -# On the computer, open and configure a terminal application as the follows.
 * \code
 *    Baud Rate : 115200
 *    Data : 8bit
 *    Parity bit : none
 *    Stop bit : 1bit
 *    Flow control : none
 * \endcode
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 * \code
 *    -- WILC station mode example --
 *    -- SAM4S_XPLAINED_PRO --
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    Connecting to XXXXXX.
 *    Wi-Fi connected
 *    Wi-Fi IP is xxx.xxx.xxx.xxx
 * \endcode
 *
 * \section compinfo Compilation Information
 * This software was written for the GNU GCC compiler using Atmel Studio 6.2
 * Other compilers may or may not work.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <A href="http://www.microchip.com">Microchip</A>.\n
 */

#include "asf.h"
#include "osprintf.h"
#include "sta.h"

#define MODE_STA_STACK_SIZE		(1024 / sizeof(portSTACK_TYPE))
#define MODE_STA_PRIORITY			(tskIDLE_PRIORITY + 1)

#define STRING_EOL    "\r\n"
#define STRING_HEADER "-- WILC station mode example --"STRING_EOL \
	"-- "BOARD_NAME " --"STRING_EOL	\
	"-- Compiled: "__DATE__ " "__TIME__ " --"STRING_EOL

/** SysTick counter to avoid busy wait delay. */
uint32_t ms_ticks = 0;

void fatal(int code, const char *msg);
void fatal(int code, const char *msg)
{
	for (;;) {
	}
}

#if configUSE_MALLOC_FAILED_HOOK
void vApplicationMallocFailedHook(void);
void vApplicationMallocFailedHook(void)
{
	for (;;) {
	}
}
#endif

#if configCHECK_FOR_STACK_OVERFLOW
void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName);
void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char *pcTaskName)
{
	/*TRACE("ERROR: STACK OVERFLOW");
	TRACE(pcTaskName);*/
	M2M_ERR("ERROR: STACK OVERFLOW");
	M2M_ERR(pcTaskName);
	for (;;) {
	}
}
#endif

static uint32_t fault_addr;
void hard_fault(uint32_t *args, uint32_t lr);
void hard_fault(uint32_t *args, uint32_t lr)
{
	fault_addr = args[6];
	osprintf("Hard fault at address 0x%X\r\n", fault_addr);
	for (;;) {
	}
}

void HardFault_Handler(void)
{
	__asm(
		"  mov r0, #4          \n"
		"  mov r1, lr          \n"
		"  tst r0, r1          \n"
		"  beq using_msp       \n"
		"  mrs r0, psp         \n"
		"  b call_c            \n"
		"using_msp:            \n"
		"  mrs r0, msp         \n"
		"call_c:               \n"
		"  ldr r2, =hard_fault \n"
		"  bx r2               \n"
	);
}

/**
 * \brief Configure UART console.
 */
static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_STDIO_BAUDRATE,
#ifdef CONF_STDIO_CHAR_LENGTH
		.charlength = CONF_STDIO_CHAR_LENGTH,
#endif
		.paritytype = CONF_STDIO_PARITY,
#ifdef CONF_STDIO_STOP_BITS
		.stopbits = CONF_STDIO_STOP_BITS
#endif
	};

	/* Configure UART console. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	osprintf_init(CONF_STDIO_USART_MODULE, &uart_serial_options);
}


/**
 * \brief Main application function.
 *
 * Application entry point.
 *
 * \return program return value.
 */
int main(void)
{
	/* Initialize the board. */
	sysclk_init();
	board_init();

	/* Initialize the UART console. */
	configure_console();
	puts(STRING_HEADER);

	/* Create main task. */
	xTaskCreate(mode_sta, (signed char *)"STAMode", MODE_STA_STACK_SIZE, 0, MODE_STA_PRIORITY, 0);
	vTaskStartScheduler();
	
	while (1) {
	}
	
	return 0;
}
