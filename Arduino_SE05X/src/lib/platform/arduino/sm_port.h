/*
  sm_port.h
  Copyright (c) 2023 Arduino SA.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef SM_PORT_H_INC
#define SM_PORT_H_INC

#include <stdbool.h>

#ifndef FALSE
#define FALSE false
#endif

#ifndef TRUE
#define TRUE true
#endif

#ifdef ARDUINO_ARCH_ZEPHYR
#include <zephyr/kernel.h>

#define CONFIG_PLUGANDTRUST_APDU_BUFFER_SIZE 256

#define SM_MUTEX_DEFINE(x)  K_MUTEX_DEFINE(x)
#define SM_MUTEX_INIT(x)    (k_mutex_init(&x))
#define SM_MUTEX_DEINIT(x)  ((void)0)
#define SM_MUTEX_LOCK(x)    (k_mutex_lock(&x, K_MSEC(10)))
#define SM_MUTEX_UNLOCK(x)  (k_mutex_unlock(&x))

#define sm_malloc k_malloc
#define sm_free k_free

#else  // ARDUINO_ARCH_ZEPHYR
#define SM_MUTEX_DEFINE(x)
#define SM_MUTEX_INIT(x)
#define SM_MUTEX_DEINIT(x)
#define SM_MUTEX_LOCK(x)
#define SM_MUTEX_UNLOCK(x)

#define sm_malloc malloc
#define sm_free free

#endif// ARDUINO_ARCH_ZEPHYR

/*
 * 0: NONE
 * 1: ERROR
 * 2: WARNING
 * 3: INFO
 * 4: DEBUG
 * 5: APDU
 */
#define DEBUG_LEVEL 0

#if DEBUG_LEVEL > 0
    #define SMLOG_E smlog_print
#else
    #define SMLOG_E smlog_none
#endif

#if DEBUG_LEVEL > 1
    #define SMLOG_W smlog_print
#else
    #define SMLOG_W smlog_none
#endif

#if DEBUG_LEVEL > 2
    #define SMLOG_I smlog_print
#else
    #define SMLOG_I smlog_none
#endif

#if DEBUG_LEVEL > 3
    #define SMLOG_D smlog_print
#else
    #define SMLOG_D smlog_none
#endif

#if DEBUG_LEVEL > 4
    #define SMLOG_AU8_D(BUF, LEN)                                       \
        smlog_print("%s", ":");                                         \
        for (size_t bufIndex = 0; bufIndex < (size_t)LEN; bufIndex++) { \
            smlog_print("%02x ", BUF[bufIndex]);                        \
        }                                                               \
        smlog_print("%s","\n")

    #define SMLOG_MAU8_D(MSG, BUF, LEN)                                 \
        smlog_print("%s", MSG);                                         \
        smlog_print("%s", ":");                                         \
        for (size_t bufIndex = 0; bufIndex < (size_t)LEN; bufIndex++) { \
            smlog_print("%02x ", BUF[bufIndex]);                        \
        }                                                               \
        smlog_print("%s","\n")

#else
    #define SMLOG_AU8_D(BUF, LEN)
    #define SMLOG_MAU8_D(MSG, BUF, LEN)
#endif

#if defined(SE05X_ENABLE_GPIO) && defined(ARDUINO_ARCH_ZEPHYR)
#define SE050_ENA_PIN SE05X_ENABLE_GPIO
#elif defined(ARDUINO_PORTENTA_C33) && defined(ARDUINO_ARCH_RENESAS)
#define SE050_ENA_PIN 98
#elif defined(ARDUINO_PORTENTA_H7_M7) && defined(ARDUINO_ARCH_MBED)
#define SE050_ENA_PIN PI_12
#elif defined(ARDUINO_NICLA_VISION) && defined(ARDUINO_ARCH_MBED)
#define SE050_ENA_PIN PG_0
#else
#warning "No enable pin is defined for se05x"
#endif

#ifdef __cplusplus
extern "C" {
#endif
void smlog_print(const char *format, ...);
void smlog_none(const char *format, ...);
#ifdef __cplusplus
}
#endif

#endif // #ifndef SM_PORT_H_INC
