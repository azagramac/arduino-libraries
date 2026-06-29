/*
  sm_i2c.cpp
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

#ifdef __cplusplus
extern "C" {
#endif

#include "lib/platform/arduino/sm_i2c.h"
#include "lib/platform/arduino/sm_port.h"

#ifdef __cplusplus
}
#endif

#include <Wire.h>

#if defined(ARDUINO_PORTENTA_C33) && defined(ARDUINO_ARCH_ZEPHYR)
HardwareI2C *CryptoWire = &Wire2;
#elif defined(ARDUINO_PORTENTA_H7_M7) && defined(ARDUINO_ARCH_ZEPHYR)
HardwareI2C *CryptoWire = &Wire1;
#elif defined(ARDUINO_NICLA_VISION) && defined(ARDUINO_ARCH_ZEPHYR)
HardwareI2C *CryptoWire = &Wire1;
#elif defined(ARDUINO_PORTENTA_C33) && defined(ARDUINO_ARCH_RENESAS)
HardwareI2C *CryptoWire = &Wire3;
#elif defined(ARDUINO_NICLA_VISION) && defined(ARDUINO_ARCH_MBED)
HardwareI2C *CryptoWire = &Wire1;
#elif defined(ARDUINO_PORTENTA_H7_M7) && defined(ARDUINO_ARCH_MBED)
HardwareI2C *CryptoWire = &Wire1;
#endif

i2c_error_t axI2CInit(void **conn_ctx, const char *pDevName) {
    (void)pDevName;

    *conn_ctx = CryptoWire;

#if defined(ARDUINO_ARCH_MBED)
    CryptoWire->setClock(400000);
#elif defined(ARDUINO_ARCH_RENESAS)
    CryptoWire->setClock(1000000);
#endif

    CryptoWire->begin();

    return I2C_OK;
}

void axI2CTerm(void *conn_ctx, int mode) {
    (void)mode;

    HardwareI2C *wire = static_cast<HardwareI2C*>(conn_ctx);

    wire->end();
}

i2c_error_t axI2CWrite(void *conn_ctx, unsigned char bus, unsigned char addr, unsigned char *pTx, unsigned short txLen) {
    (void)bus;
    HardwareI2C *wire = static_cast<HardwareI2C*>(conn_ctx);

    addr = addr >> 1;
    wire->beginTransmission(addr);
    wire->write(pTx, txLen);
    if (wire->endTransmission() != 0) {
        return I2C_FAILED;
    }

    return I2C_OK;
}

i2c_error_t axI2CRead(void *conn_ctx, unsigned char bus, unsigned char addr, unsigned char *pRx, unsigned short rxLen) {
    (void)bus;
    addr = addr >> 1;

    HardwareI2C *wire = static_cast<HardwareI2C*>(conn_ctx);

    if(wire->requestFrom((uint8_t)addr, (size_t)rxLen, true) == 0) {
        return I2C_FAILED;
    }

    for (size_t i = 0; CryptoWire->available(); i++) {
        pRx[i] = CryptoWire->read();
    }
    return I2C_OK;
}
