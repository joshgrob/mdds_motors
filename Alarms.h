#ifndef Alarms_h
#define Alarms_h

#include "def.h"
#include "Types.h"
#include "Filters.h"

#define VBAT_TIMEOUT                  25000 // 40Hz
#define LEDPIN_PINMODE                pinMode (5, OUTPUT);
#define LEDPIN_ON                     digitalWrite(5, HIGH);
#define LEDPIN_OFF                    digitalWrite(5, LOW);
#define LEDPIN_TOGGLE                 if (digitalRead(5)) digitalWrite(5, LOW); else digitalWrite(5, HIGH);
                                      
extern uint32_t                       currentTime;
extern uint16_t                       calibratingA;
extern uint8_t                        vbat;
extern uint8_t                        vbatMin;
extern struct flags_struct            f;
extern struct conf_t                  conf;

class Alarms
{
  public:
                                      Alarms();
     static void                      blink_redLED(uint8_t num, uint8_t ontime,uint8_t repeat);
     static void                      toggle_redLED();
     static void                      redLEDon();
     static void                      redLEDoff();
     static void                      Acc_cal_and_tilt_indicator();
     static void                      Armed_indicator();
     static void                      Vbat_update();
  private:
};

#endif // Alarms_h
