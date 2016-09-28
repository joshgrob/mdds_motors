  #include "Arduino.h"
#include "I2Cdev_ESP8266.h"

/** Default timeout value for read operations.
 * Set this to 0 to disable timeout detection.
 */
uint16_t I2Cdev::readTimeout = I2CDEV_DEFAULT_READ_TIMEOUT;

I2Cdev::I2Cdev()
{
}

/** Read single byte from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param data Container for byte value read from device
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Status of read operation (true = success)
 */
int8_t I2Cdev::readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint16_t timeout)
{
  return readBytes(devAddr, regAddr, 1, data, timeout);
}

/** Write one byte to an M24512DFM EEPROM.
 * @device_address I2C slave device address
 * @param data_address1 memory address MSB
 * @param data_address1 memory address LSB
 * @param count Number of bytes to write
 * @param data Buffer to copy new data from
 * @return byte
 */
uint8_t I2Cdev::M24512DFMreadByte(uint8_t device_address, uint8_t data_address1, uint8_t data_address2)
{
  uint8_t data;                                   // `data` will store the register data   
  Wire.beginTransmission(device_address);         // Initialize the Tx buffer
  Wire.write(data_address1);                      // Put slave register address in Tx buffer
  Wire.write(data_address2);                      // Put slave register address in Tx buffer
  Wire.endTransmission(false);                    // Send the Tx buffer, but send a restart to keep connection alive
  Wire.requestFrom(device_address, (size_t)1);    // Read one byte from slave register address 
  data = Wire.read();                             // Fill Rx buffer with result
  return data;                                    // Return data read from slave register
}

/** Read multiple bytes from an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register regAddr to read from
 * @param length Number of bytes to read
 * @param data Buffer to store read data in
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
 * @return Number of bytes read (-1 indicates failure)
 */
int8_t I2Cdev::readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, uint16_t timeout)
{
  uint32_t t1 = millis();
  uint8_t count = 0;

  Wire.beginTransmission(devAddr);
  Wire.write(regAddr);
  Wire.endTransmission(false);
  Wire.requestFrom(devAddr, (size_t)min(length, BUFFER_LENGTH));
  while (Wire.available())
  {
    data[count++] = Wire.read();
    if ((timeout > 0) && (millis() - t1) >= timeout && count < length) count = -1; // timeout
  }
  return count;
}

/** Write multiple bytes to an M24512DFM EEPROM.
 * @device_address I2C slave device address
 * @param starting data_address1 memory address MSB
 * @param starting data_address1 memory address LSB
 * @param count Number of bytes to write
 * @param data Buffer to copy new data from
 * @return void
 */
void I2Cdev::M24512DFMreadBytes(uint8_t device_address, uint8_t data_address1, uint8_t data_address2, uint8_t count, uint8_t *dest)
{  
  Wire.beginTransmission(device_address);            // Initialize the Tx buffer
  Wire.write(data_address1);                         // Put slave register address in Tx buffer
  Wire.write(data_address2);                         // Put slave register address in Tx buffer
  Wire.endTransmission(false);                       // Send the Tx buffer, but send a restart to keep connection alive
  uint8_t i = 0;
  Wire.requestFrom(device_address, (size_t)count);  // Read bytes from slave register address 
  while (Wire.available())
  {
    dest[i++] = Wire.read();
  }                                                   // Put read results in the Rx buffer
}

/** Write single byte to an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr Register address to write to
 * @param data New byte value to write
 * @return Status of operation (true = success)
 */
bool I2Cdev::writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data)
{
  return writeBytes(devAddr, regAddr, 1, &data);
}

/** Write a single byte to an M24512DFM EEPROM
 * @param device_address EEPROM I2C address
 * @param Starting memory address MSB
 * @param Starting memory address LSB
 * @param data variable to copy new data from
 * @return void
 */
void I2Cdev::M24512DFMwriteByte(uint8_t device_address, uint8_t data_address1, uint8_t data_address2, uint8_t  data)
{
  Wire.beginTransmission(device_address);   // Initialize the Tx buffer
  Wire.write(data_address1);                // Put slave register address in Tx buffer
  Wire.write(data_address2);                // Put slave register address in Tx buffer
  Wire.write(data);                         // Put data in Tx buffer
  Wire.endTransmission();                   // Send the Tx buffer
}

/** Write multiple bytes to an 8-bit device register.
 * @param devAddr I2C slave device address
 * @param regAddr First register address to write to
 * @param length Number of bytes to write
 * @param data Buffer to copy new data from
 * @return Status of operation (true = success)
 */
bool I2Cdev::writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data)
{
  uint8_t status = 0;
    
  Wire.beginTransmission(devAddr);
  Wire.write((uint8_t) regAddr);
  for (uint8_t i=0; i < length; i++)
  {
    Wire.write((uint8_t)data[i]);
  }
  status = Wire.endTransmission();
  return status;
}

/** Write multiple bytes to an M24512DFM EEPROM
 * @param device_address EEPROM I2C address
 * @param Starting memory address MSB
 * @param Starting memory address LSB
 * @param count Number of bytes to write
 * @param dest Buffer to copy new data from
 * @return void
 */
void I2Cdev::M24512DFMwriteBytes(uint8_t device_address, uint8_t data_address1, uint8_t data_address2, uint8_t count, uint8_t *dest)
{
  Wire.beginTransmission(device_address);   // Initialize the Tx buffer
  Wire.write(data_address1);                // Put slave register address in Tx buffer
  Wire.write(data_address2);                // Put slave register address in Tx buffer
  for(uint8_t i=0; i < count; i++)
  {
    Wire.write(dest[i]);                    // Put data in Tx buffer
  }
  Wire.endTransmission();                   // Send the Tx buffer
}
