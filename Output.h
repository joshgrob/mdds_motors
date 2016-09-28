#ifndef Output_h
#define Output_h

#include "def.h"
#include "Types.h"
#include "Alarms.h"
#include "I2Cdev_ESP8266.h"

#define PCA9685A_ADDRESS                0x40
#define PCA9685A_MODE1                  0x00
#define PCA9685A_MODE2                  0x01
#define PCA9685A_PRE_SCALE              0xFE
#define PCA9685A_LED0_ON_L              0x06
#define PCA9685A_LED8_ON_L              0x26


extern int16_t                          rcData[RC_CHANS];
extern int16_t                          rcCommand[4];
extern int16_t                          motor[NUMBER_MOTOR];
extern uint8_t                          Output_Channel[8];
extern int16_t                          axisPID[3];
extern int16_t                          headFreeModeHold;
extern int32_t                          debug[4];
extern struct flags_struct              f;
extern struct conf_t                    conf;
extern struct motor_data                up_data, down_data, right_data, left_data, front_data, back_data;

class Output
{
  public:
                                        Output();
     void                               writeMotors();
     void                               initOutput();
     void                               mixTable();
  private:
     void                               writeAllMotors(int16_t mc);
     void                               _setPWMBytes(uint8_t pwm_byte[], Motor_data *m_data, uint8_t pos);
};

#endif // Output_h
