

#ifndef _I2CDEV_H_
#define _I2CDEV_H_

#include <Wire.h>

#define I2CDEV_DEFAULT_READ_TIMEOUT    1000
#define BUFFER_LENGTH                  128

extern int32_t                         debug[4];

class I2Cdev {
    public:
                                       I2Cdev();
         static int8_t                 readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout=I2Cdev::readTimeout);
         static uint8_t                M24512DFMreadByte(uint8_t device_address, uint8_t data_address1, uint8_t data_address2);
         static int8_t                 readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout=I2Cdev::readTimeout);
         static void                   M24512DFMreadBytes(uint8_t device_address, uint8_t data_address1, uint8_t data_address2, uint8_t count, uint8_t *dest);
 
         static bool                   writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
         static void                   M24512DFMwriteByte(uint8_t device_address, uint8_t data_address1, uint8_t data_address2, uint8_t  data);
         static bool                   writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
         static void                   M24512DFMwriteBytes(uint8_t device_address, uint8_t data_address1, uint8_t data_address2, uint8_t count, uint8_t *dest);

        static uint16_t                readTimeout;
};

#endif //_I2CDEV_H_
