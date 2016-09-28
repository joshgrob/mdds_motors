#include "Arduino.h"
#include "Alarms.h"

Alarms::Alarms()
{
}

/**
* @fn: blink_redLED(uint8_t num, uint8_t ontime,uint8_t repeat);
*
* @brief: Flashes red LED indicator; blocking function, do not use in main loop
* 
* @params: Blinks per ccle, on time, number of cycles
* @returns:
*/
void Alarms::blink_redLED(uint8_t num, uint8_t ontime,uint8_t repeat) 
{
  uint8_t i, r;
  for(r=0; r<repeat; r++)
  {
    for(i=0; i<num; i++)
    {
      Alarms::toggle_redLED();
      delay(ontime);
    }
    //wait 60 ms
    delay(60);
  }
}

/**
* @fn: Acc_cal_and_tilt_indicator();
*
* @brief: Flashes red LED when Acc is not cal'd or IMU is tilted > 25 deg
* 
* @params:
* @returns:
*/
void Alarms::Acc_cal_and_tilt_indicator()
{
  static uint32_t calibratedAccTime;
  
  if((currentTime - calibratedAccTime) > 100000)
  { 
    //ACC is not calibrated or pitch/roll > 25deg
    if (!f.SMALL_ANGLES_25)
    {
      f.ACC_CALIBRATED = 0;
      Alarms::toggle_redLED();
      calibratedAccTime = currentTime;
    } else
    {
      f.ACC_CALIBRATED = 1;
    }
  }
}

/**
* @fn: Armed_indicator();
*
* @brief: Turns on red LED when controller goes armed
* 
* @params:
* @returns:
*/
void Alarms::Armed_indicator()
{
  if(calibratingA>0 && ACC)
  {
  } else
  {
    if (f.ACC_CALIBRATED)
    {
      Alarms::redLEDoff();
    }
    if (f.ARMED)
    {
      Alarms::redLEDon();
    }
  }
}

/**
* @fn: Vbat_update();
*
* @brief: Updates vbat monitor
* 
* @params:
* @returns:
*/
void Alarms::Vbat_update()
{
  //                                          a0                      a1                   a2                    b0                     b1                    b2
  //static biquad     vbat_coeff[1] = {{1.000000000000000000, -1.668885251934074440,  0.722749973439289040, 0.147850669876442464, -0.241836618247670498, 0.147850669876442464},}; // Least aggressive
  //static biquad     vbat_coeff[1] = {{1.000000000000000000, -1.779356902468178350, 0.804660413744820113, 0.148332993972378618, -0.271362476668115471, 0.148332993972378618},}; // More aggressive
  static biquad     vbat_coeff[1] = {{1.000000000000000000, -1.890287492671003160, 0.896951439414127028, 0.151725216727916362, -0.296786486712708852, 0.151725216727916362},}; // Most aggressive
  static biquad_reg vbat_reg = {0.0f, 0.0f, 0.0f, 0.0f};
  static uint8_t    BatV;
  uint32_t          VBAT_currentT = micros();
  static uint32_t   VBAT_previousT = 0;

  // Timeout block
  if((VBAT_currentT - VBAT_previousT) < VBAT_TIMEOUT) return;
  VBAT_previousT = VBAT_currentT;
  BatV = (uint8_t)((float)(analogRead(A0))*0.07194010417f);
  vbat = Filters::RunIIRBiquadForm1(BatV, vbat_coeff, &vbat_reg, 1);
  //debug[2] = vbat;
  if(f.ARMED)
  {
    #if defined(VBAT)
      if((vbat > conf.no_vbat) && (vbat < vbatMin))
      {
        vbatMin = vbat;
      }
    #endif
  }
}

/**
* @fn: LED On, off, toggle functions
*
* @brief: Fast direct manipulation functions for green/yellow LED
* 
* @params:
* @returns:
*/
void Alarms::redLEDon()
{
  LEDPIN_ON;
}

void Alarms::redLEDoff()
{
  LEDPIN_OFF;
}

void Alarms::toggle_redLED()
{
  LEDPIN_TOGGLE;
}
