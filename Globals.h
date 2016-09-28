#ifndef Globals_h
#define Globals_h

#include "def.h"
#include "Types.h"

const char                              *build_date = __DATE__;
uint32_t                                currentTime = 0;
uint32_t                                previousTime = 0;
uint32_t                                previousDebugTime = 0; // Diagnostic; remove when complete
uint32_t                                cycleTime = 0; // Main loop time (us)
uint16_t                                calibratingA = 0; // Acc calibration
uint16_t                                calibratingB = 0; //Baro calibration
uint8_t                                 datastatus, algorithmstatus, Sentral_WS_valid; // EM7180 specific
int16_t                                 gyroADC[3], acc[3], accADC[3];
int16_t                                 accLIN[3], accSmooth[3];
int32_t                                 magADC[3];
int16_t                                 magHold, headFreeModeHold; // [-180;+180]
uint8_t                                 vbat; // 0-255 ->0-15V
uint8_t                                 vbatMin = VBATNOMINAL;
uint8_t                                 rcOptions[CHECKBOXITEMS];
float                                   baroPressure;
float                                   baroPressureSum;
int32_t                                 BaroAlt = 0; //In cm
int32_t                                 EstAlt = 0; //In cm
int16_t                                 AltCtrl = 0;
uint8_t                                 isAltHoldChanged = 0;
int32_t                                 BaroPID = 0;
int32_t                                 errorAltitudeI = 0;
int16_t                                 vario = 0; // In cm/s
int16_t                                 heading = 0;
int32_t                                 debug[4]; // GUI diagnostic
int16_t                                 i2c_errors_count = 0;
uint16_t                                intPowerMeterSum, intPowerTrigger1; // MSP-related (depricated)
int16_t                                 failsafeEvents = 0;
volatile int16_t                        failsafeCnt = 0;
volatile uint32_t                       startPulse = 0;
byte                                    packetBuffer[PACKET_SIZE];
RCOIPv1ReplyReceiverStatus              RX_Reply;
uint32_t                                rawRC[10] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};
int16_t                                 rcData[RC_CHANS]; //Interval [1000;2000]
int16_t                                 rcCommand[4]; // Thr:[1000;2000] YPR:[-500;+500]
int16_t                                 lookupPitchRollRC[6]; // Expo & RC rate (P,R) lookup
int16_t                                 lookupThrottleRC[11]; // Expo & mid throttle lookup
uint8_t                                 dynP8[3], dynD8[3];
uint16_t                                rssi; //Range: [0;1023] (depricated)
int16_t                                 gyroData[3] = {0,0,0};
int16_t                                 angle[2] = {0,0}; // P,R Euler angles 1 deg = 10
float                                   qt[4] = {1.0f, 0.0f, 0.0f, 0.0f}; // Quaternion
int16_t                                 axisPID[3];
uint8_t                                 PWM_PIN[8] = {MOTOR_0_PIN, MOTOR_1_PIN, MOTOR_2_PIN, MOTOR_3_PIN, MOTOR_4_PIN, MOTOR_5_PIN, MOTOR_6_PIN, MOTOR_7_PIN};
uint8_t                                 Output_Channel[8] = {OUTPUT_0_MOTOR, OUTPUT_1_MOTOR, OUTPUT_2_MOTOR, OUTPUT_3_MOTOR, OUTPUT_4_MOTOR, OUTPUT_5_MOTOR, OUTPUT_6_MOTOR, OUTPUT_7_MOTOR};
int16_t                                 motor[NUMBER_MOTOR];
int16_t                                 GPS_angle[2] = {0, 0};
uint8_t                                 rcDelayCommand; // Number of times a stick combination must be asserted for action
uint8_t                                 rcSticks; // Single YPRT stick position indicator
uint8_t                                 axis;
int32_t                                 errorGyro, errorAngle;
int32_t                                 AccErr, GyroErr, Beta;
int32_t                                 PTerm, ITerm;
int32_t                                 PTermACC = 0, ITermACC = 0, PTermGYRO = 0, ITermGYRO = 0;
int32_t                                 errorGyroI[3] = {0,0,0};
int32_t                                 GyroErr1[2] = {0,0};
int32_t                                 GyroErr2[2] = {0,0};
int32_t                                 errorAngleI[2] = {0,0};
int32_t                                 AccErrLim = 0;
uint32_t                                rcTime  = 0;
int16_t                                 initialThrottleHold;
int16_t                                 Last_rcCommand_THROTTLE;
uint8_t                                 initialVbat;
int64_t                                 a_acc[3] = {0, 0, 0}, b_acc[3] = {0, 0, 0};
flags_struct                            f;
global_conf_t                           global_conf;
conf_t                                  conf;
Sentral_WS_params                       WS_params;

#endif // Globals_h

