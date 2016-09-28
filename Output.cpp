#include "Arduino.h"
#include "Output.h"

Output::Output()
{
}

/**
* @fn: initOutput()
*
* @brief: Initializes the each PWM motor channel for the selected Multitype
* 
* @params:
* @returns:
*/
void Output::initOutput()
{  
  uint8_t oldmode;
  uint8_t newmode;
  uint8_t PWM_byte[32];
 
  // Reset PCA9685A
  I2Cdev::writeByte(PCA9685A_ADDRESS, PCA9685A_MODE1, 0x00);
  delay(10);

  // Read and store the MODE1 register contents
  I2Cdev::readByte(PCA9685A_ADDRESS, PCA9685A_MODE1, &oldmode);
  newmode = (oldmode & 0x7F) | 0x10; // sleep

  // Nitey-nite
  I2Cdev::writeByte(PCA9685A_ADDRESS, PCA9685A_MODE1, newmode);

  // Set prescaler to 3; 1526Hz
  I2Cdev::writeByte(PCA9685A_ADDRESS, PCA9685A_PRE_SCALE, 0x03);

  // Good morning!
  I2Cdev::writeByte(PCA9685A_ADDRESS, PCA9685A_MODE1, oldmode);
  delay(5);

  // Set register to auto-increment
  I2Cdev::writeByte(PCA9685A_ADDRESS, PCA9685A_MODE1, oldmode | 0xa1);

  // Turn on output enable
  pinMode(15, OUTPUT);
  digitalWrite(15, LOW);

  // Force to 0% duty cycle for "xIN2/Enable" input of the H-bridge
  // Does not need to change for speed control
  for (uint8_t i = 0; i < NUMBER_MOTOR; i++)
  {
    PWM_byte[4*i]     = 0x00;
    PWM_byte[4*i + 1] = 0x00;
    PWM_byte[4*i + 2] = 0x00;
    PWM_byte[4*i + 3] = 0x10;
  }
  
  // Refresh all output bytes in one burst write
  I2Cdev::writeBytes(PCA9685A_ADDRESS, PCA9685A_LED0_ON_L, 4*NUMBER_MOTOR, PWM_byte);

  // Write MINCOMMAND to all motors
  Output::writeAllMotors(MINCOMMAND);
  delay(300);
}

/**
* @fn: Output()
*
* @brief: Performs "analogWrite" of motor command to each motor PWM channel
* 
* @params:
* @returns:
*/
void Output::writeMotors()
{
  static uint8_t PWM_byte[32];

  //go through every motor direction with values set from request
  _setPWMBytes(PWM_byte, &up_data, 0);
  _setPWMBytes(PWM_byte, &down_data, 1);
  _setPWMBytes(PWM_byte, &left_data, 2);
  _setPWMBytes(PWM_byte, &right_data, 3);
  _setPWMBytes(PWM_byte, &front_data, 4);
  _setPWMBytes(PWM_byte, &back_data, 5);

  // Refresh all output bytes in one burst write
  I2Cdev::writeBytes(PCA9685A_ADDRESS, PCA9685A_LED8_ON_L, 4*NUMBER_MOTOR, PWM_byte);
}

/**
* @fn: writeAllMotors(int16_t mc)
*
* @brief: Writes the same motor command to all motor channels
* 
* @params: Motor command
* @returns:
*/
void Output::writeAllMotors(int16_t mc)
{
  // Sends commands to all motors
  for(uint8_t i = 0; i < NUMBER_MOTOR; i++)
  {
    motor[i]=mc;
  }
  Output::writeMotors();
}

void Output::_setPWMBytes(uint8_t pwm_byte[], Motor_data *m_data, uint8_t pos){
  
  union
  {
    uint16_t motor_val;
    uint8_t motor_val_byte[2];
  };

  if (m_data->state) 
  {
    motor_val = m_data->intensity;
  } else {
    motor_val = 0;
  }
  
  if (motor_val < 0) motor_val = 0;
    if (motor_val > 2000) motor_val = 2000;
    if (motor_val == 2000)
    {
      // Force to 100% duty cycle
      pwm_byte[4*pos] =     0x00;
      pwm_byte[4*pos + 1] = 0x10;
      pwm_byte[4*pos + 2] = 0x00;
      pwm_byte[4*pos + 3] = 0x00;
    }
    else if (motor_val == 0)
    {
      // Force to 0% duty cycle
      pwm_byte[4*pos] =     0x00;
      pwm_byte[4*pos + 1] = 0x00;
      pwm_byte[4*pos + 2] = 0x00;
      pwm_byte[4*pos + 3] = 0x10;
    }
    else
    {
      pwm_byte[4*pos] =     0x00;
      pwm_byte[4*pos + 1] = 0x00;
      pwm_byte[4*pos + 2] = motor_val_byte[0];
      pwm_byte[4*pos + 3] = motor_val_byte[1];
    }
}

/**
* @fn: mixTable()
*
* @brief: Translates throttle and PID commands into individual motor commands for the selected Multitype
* 
* @params:
* @returns:
*/
void Output::mixTable()
{
  int16_t maxMotor;
  uint8_t i;

  #define PIDMIX(X,Y,Z) rcCommand[THROTTLE] + axisPID[ROLL]*X + axisPID[PITCH]*Y + axisPID[YAW]*Z

    #ifdef QUADP
      motor[0] = PIDMIX( 0,+1,-1); //REAR
      motor[1] = PIDMIX(-1, 0,+1); //RIGHT
      motor[2] = PIDMIX(+1, 0,+1); //LEFT
      motor[3] = PIDMIX( 0,-1,-1); //FRONT
    #endif
    #ifdef QUADX
      motor[0] = PIDMIX(-1,+1,-1); //REAR_R
      motor[1] = PIDMIX(-1,-1,+1); //FRONT_R
      motor[2] = PIDMIX(+1,+1,+1); //REAR_L
      motor[3] = PIDMIX(+1,-1,-1); //FRONT_L
    #endif
    #ifdef Y4
      motor[0] = PIDMIX(+0,+1,-1);   //REAR_1 CW
      motor[1] = PIDMIX(-1,-1, 0); //FRONT_R CCW
      motor[2] = PIDMIX(+0,+1,+1);   //REAR_2 CCW
      motor[3] = PIDMIX(+1,-1, 0); //FRONT_L CW
    #endif
    #ifdef Y6
      motor[0] = PIDMIX(+0,+4/3,+1); //REAR
      motor[1] = PIDMIX(-1,-2/3,-1); //RIGHT
      motor[2] = PIDMIX(+1,-2/3,-1); //LEFT
      motor[3] = PIDMIX(+0,+4/3,-1); //UNDER_REAR
      motor[4] = PIDMIX(-1,-2/3,+1); //UNDER_RIGHT
      motor[5] = PIDMIX(+1,-2/3,+1); //UNDER_LEFT
    #endif
    #ifdef HEX6
      motor[0] = PIDMIX(-7/8,+1/2,+1); //REAR_R
      motor[1] = PIDMIX(-7/8,-1/2,-1); //FRONT_R
      motor[2] = PIDMIX(+7/8,+1/2,+1); //REAR_L
      motor[3] = PIDMIX(+7/8,-1/2,-1); //FRONT_L
      motor[4] = PIDMIX(+0  ,-1  ,+1); //FRONT
      motor[5] = PIDMIX(+0  ,+1  ,-1); //REAR
    #endif
    #ifdef HEX6X
      motor[0] = PIDMIX(-1/2,+7/8,+1); //REAR_R
      motor[1] = PIDMIX(-1/2,-7/8,+1); //FRONT_R
      motor[2] = PIDMIX(+1/2,+7/8,-1); //REAR_L
      motor[3] = PIDMIX(+1/2,-7/8,-1); //FRONT_L
      motor[4] = PIDMIX(-1  ,+0  ,-1); //RIGHT
      motor[5] = PIDMIX(+1  ,+0  ,+1); //LEFT
    #endif
    #ifdef FPV_90DEG_HEX6X
      motor[0] = PIDMIX(-1/2,  +1,  +1); //REAR_R
      motor[1] = PIDMIX(-3/4,  -1,  +1); //FRONT_R
      motor[2] = PIDMIX(+1/2,  +1,  -1); //REAR_L
      motor[3] = PIDMIX(+3/4,  -1,  -1); //FRONT_L
      motor[4] = PIDMIX(-7/8,   0,  -1); //RIGHT
      motor[5] = PIDMIX(+7/8,   0,  +1); //LEFT
    #endif
    #ifdef HEX6H
      motor[0] = PIDMIX(-1,+1,-1); //REAR_R
      motor[1] = PIDMIX(-1,-1,+1); //FRONT_R
      motor[2] = PIDMIX(+ 1,+1,+1); //REAR_L
      motor[3] = PIDMIX(+ 1,-1,-1); //FRONT_L
      motor[4] = PIDMIX(0 ,0 ,0); //RIGHT
      motor[5] = PIDMIX(0 ,0 ,0); //LEFT
    #endif
    #ifdef OCTOX8
      motor[0] = PIDMIX(-1,+1,-1); //REAR_R
      motor[1] = PIDMIX(-1,-1,+1); //FRONT_R
      motor[2] = PIDMIX(+1,+1,+1); //REAR_L
      motor[3] = PIDMIX(+1,-1,-1); //FRONT_L
      motor[4] = PIDMIX(-1,+1,+1); //UNDER_REAR_R
      motor[5] = PIDMIX(-1,-1,-1); //UNDER_FRONT_R
      motor[6] = PIDMIX(+1,+1,-1); //UNDER_REAR_L
      motor[7] = PIDMIX(+1,-1,+1); //UNDER_FRONT_L
    #endif
    #ifdef OCTOFLATP
      motor[0] = PIDMIX(+7/10,-7/10,+1); //FRONT_L
      motor[1] = PIDMIX(-7/10,-7/10,+1); //FRONT_R
      motor[2] = PIDMIX(-7/10,+7/10,+1); //REAR_R
      motor[3] = PIDMIX(+7/10,+7/10,+1); //REAR_L
      motor[4] = PIDMIX(+0   ,-1   ,-1); //FRONT
      motor[5] = PIDMIX(-1   ,+0   ,-1); //RIGHT
      motor[6] = PIDMIX(+0   ,+1   ,-1); //REAR
      motor[7] = PIDMIX(+1   ,+0   ,-1); //LEFT
    #endif
    #ifdef OCTOFLATX
      motor[0] = PIDMIX(+1  ,-1/2,+1); //MIDFRONT_L
      motor[1] = PIDMIX(-1/2,-1  ,+1); //FRONT_R
      motor[2] = PIDMIX(-1  ,+1/2,+1); //MIDREAR_R
      motor[3] = PIDMIX(+1/2,+1  ,+1); //REAR_L
      motor[4] = PIDMIX(+1/2,-1  ,-1); //FRONT_L
      motor[5] = PIDMIX(-1  ,-1/2,-1); //MIDFRONT_R
      motor[6] = PIDMIX(-1/2,+1  ,-1); //REAR_R
      motor[7] = PIDMIX(+1  ,+1/2,-1); //MIDREAR_L
    #endif
    #ifdef VTAIL4
      motor[0] = PIDMIX(+0,+1, +1); //REAR_R
      motor[1] = PIDMIX(-1, -1, +0); //FRONT_R
      motor[2] = PIDMIX(+0,+1, -1); //REAR_L
      motor[3] = PIDMIX(+1, -1, -0); //FRONT_L
    #endif
  #ifdef LEAVE_HEADROOM_FOR_MOTORS

    // Limit this leaving room for corrections to the first #n of all motors
    maxMotor=motor[0];
    for(i=1; i < LEAVE_HEADROOM_FOR_MOTORS; i++)
      if (motor[i]>maxMotor) maxMotor=motor[i];
    if (maxMotor > MAXTHROTTLE)
    {
      // This is a way to maintain stability if one or more motors reaches max
      for(i=0; i < LEAVE_HEADROOM_FOR_MOTORS; i++)
        motor[i] -= maxMotor - MAXTHROTTLE;
    }
    for (i = 0; i < NUMBER_MOTOR; i++)
    {
      motor[i] = constrain(motor[i], conf.minthrottle, MAXTHROTTLE);
      #if defined(ALTHOLD_FAST_THROTTLE_CHANGE)
        if (rcData[THROTTLE] < MINCHECK)
      #else
        if ((rcData[THROTTLE] < MINCHECK) && !f.BARO_MODE)
      #endif
      if (!f.ARMED)
        motor[i] = MINCOMMAND;
    }
  #else // LEAVE_HEADROOM_FOR_MOTORS
    maxMotor=motor[0];
    for(i=1; i< NUMBER_MOTOR; i++)
      if (motor[i]>maxMotor) maxMotor=motor[i];
    for(i=0; i< NUMBER_MOTOR; i++)
    {
      // This is a way to maintain stability if one or more motors reaches max
      if (maxMotor > MAXTHROTTLE)
        motor[i] -= maxMotor - MAXTHROTTLE;
      motor[i] = constrain(motor[i], conf.minthrottle, MAXTHROTTLE);
      #if defined(ALTHOLD_FAST_THROTTLE_CHANGE)
        if (rcData[THROTTLE] < MINCHECK)
      #else
        if ((rcData[THROTTLE] < MINCHECK) && !f.BARO_MODE)
      #endif
        #ifndef MOTOR_STOP
          motor[i] = conf.minthrottle;
        #else
          motor[i] = MINCOMMAND;
        #endif
      if (!f.ARMED)
        motor[i] = MINCOMMAND;
    }
  #endif // LEAVE_HEADROOM_FOR_MOTORS
}
