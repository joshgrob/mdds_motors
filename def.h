#ifndef def_h
#define def_h

#include "config.h"

#define VERSION                                 001

/*************************************************************************************************/
/*************                                                                     ***************/
/*************                           Motor Numbers                             ***************/
/*************                                                                     ***************/
/*************************************************************************************************/
#if defined(QUADP) || defined(QUADX) || defined(Y4)|| defined(VTAIL4)
  #define NUMBER_MOTOR                          4
#elif defined(Y6) || defined(HEX6) || defined(HEX6X) || defined(HEX6H) || defined(FPV_90DEG_HEX6X)
  #define NUMBER_MOTOR                          6
#elif defined(OCTOX8) || defined(OCTOFLATP) || defined(OCTOFLATX)
  #define NUMBER_MOTOR                          8
#endif

/*************************************************************************************************/
/*************                                                                     ***************/
/*************              IMU Orientations and Sensor Definitions                ***************/
/*************                                                                     ***************/
/*************************************************************************************************/
#if defined(PP_EM7180_MPU6500_AK8963_BMP280)
  #define SENTRAL
  
  // For GUI indication purposes only
  #define ACC_ORIENTATION(X, Y, Z)  {accADC[ROLL]  = Y; accADC[PITCH]  = X; accADC[YAW]  =  Z;}
  #define GYRO_ORIENTATION(X, Y, Z) {gyroADC[ROLL] =  X; gyroADC[PITCH] = -Y; gyroADC[YAW] = Z;}
  #define MAG_ORIENTATION(X, Y, Z)  {magADC[ROLL]  =  X; magADC[PITCH]  =  Y; magADC[YAW]  = Z;}
#endif
#if defined(SENTRAL)
  #define GYRO                                  1
  #define MAG                                   1
  #define ACC                                   1
  #define BARO                                  1

  // Sentral I2C EEPROM
  #define M24512DFM_DATA_ADDRESS                0x50
  #define M24512DFM_IDPAGE_ADDRESS              0x58

  // MPU LPF's
  #if defined(MPU9250_GYRO_LPF_3600HZ) || defined(MPU9250_GYRO_LPF_250HZ) || defined(MPU9250_GYRO_LPF_184HZ) \
    || defined(MPU9250_GYRO_LPF_92HZ) || defined(MPU9250_GYRO_LPF_41HZ) || defined(MPU9250_GYRO_LPF_20HZ) \
    || defined(MPU9250_GYRO_LPF_10HZ) || defined(MPU9250_GYRO_LPF_5HZ)
  
    #if defined(MPU9250_GYRO_LPF_3600HZ)
      #define MPU9250_GYRO_DLPF_CFG             0x07
    #endif
    #if defined(MPU9250_GYRO_LPF_250HZ)
      #define MPU9250_GYRO_DLPF_CFG             0x00
    #endif
    #if defined(MPU9250_GYRO_LPF_184HZ)
      #define MPU9250_GYRO_DLPF_CFG             0x01
    #endif
    #if defined(MPU9250_GYRO_LPF_92HZ)
      #define MPU9250_GYRO_DLPF_CFG             0x02
    #endif
    #if defined(MPU9250_GYRO_LPF_41HZ)
      #define MPU9250_GYRO_DLPF_CFG             0x03
    #endif
    #if defined(MPU9250_GYRO_LPF_20HZ)
      #define MPU9250_GYRO_DLPF_CFG             0x04
    #endif
    #if defined(MPU9250_GYRO_LPF_10HZ)
      #define MPU9250_GYRO_DLPF_CFG             0x05
    #endif
    #if defined(MPU9250_GYRO_LPF_5HZ)
      #define MPU9250_GYRO_DLPF_CFG             0x06
    #endif
  #else
      //Default settings LPF 184Hz
      #define MPU9250_GYRO_DLPF_CFG             0x01
  #endif
  
  #if defined(MPU9250_ACC_LPF_460HZ) || defined(MPU9250_ACC_LPF_184HZ) || defined(MPU9250_ACC_LPF_92HZ) \
    || defined(MPU9250_ACC_LPF_41HZ) || defined(MPU9250_ACC_LPF_20HZ) || defined(MPU9250_ACC_LPF_10HZ) \
    || defined(MPU9250_ACC_LPF_5HZ)
  
    #if defined(MPU9250_ACC_LPF_460HZ)
      #define MPU9250_ACC_DLPF_CFG              0x00
    #endif
    #if defined(MPU9250_ACC_LPF_184HZ)
      #define MPU9250_ACC_DLPF_CFG              0x01
    #endif
    #if defined(MPU9250_ACC_LPF_92HZ)
      #define MPU9250_ACC_DLPF_CFG              0x02
    #endif
    #if defined(MPU9250_ACC_LPF_41HZ)
      #define MPU9250_ACC_DLPF_CFG              0x03
    #endif
    #if defined(MPU9250_ACC_LPF_20HZ)
      #define MPU9250_ACC_DLPF_CFG              0x04
    #endif
    #if defined(MPU9250_ACC_LPF_10HZ)
      #define MPU9250_ACC_DLPF_CFG              0x05
    #endif
    #if defined(MPU9250_ACC_LPF_5HZ)
      #define MPU9250_ACC_DLPF_CFG              0x06
    #endif
  #else
      //Default settings LPF 460
      #define MPU9250_ACC_DLPF_CFG              0x00
  #endif
#endif // Sentral
#define GPS                                     0
#define SONAR                                   0
#define LIDAR                                   0


/*************************************************************************************************/
/*************                                                                     ***************/
/*************                       Multitype Definitions                         ***************/
/*************                                                                     ***************/
/*************************************************************************************************/
#if defined(QUADP)
  #define MULTITYPE                             2
#elif defined(QUADX)
  #define MULTITYPE                             3
#elif defined(Y6)
  #define MULTITYPE                             6
#elif defined(HEX6)
  #define MULTITYPE                             7
#elif defined(Y4)
  #define MULTITYPE                             9
#elif defined(HEX6X)
  #define MULTITYPE                             10
#elif defined(OCTOX8)
  #define MULTITYPE                             11
#elif defined(OCTOFLATP)
  #define MULTITYPE                             12
#elif defined(OCTOFLATX)
  #define MULTITYPE                             13
#elif defined (HELI_90_DEG)   
  #define MULTITYPE                             16      
#elif defined(VTAIL4)
 #define MULTITYPE                              17
#elif defined(HEX6H)
 #define MULTITYPE                              18
#elif defined(FPV_90DEG_HEX6X)
 #define MULTITYPE                              10
#endif

/*************************************************************************************************/
/*************                                                                     ***************/
/*************                    Output Channel Definitions                       ***************/
/*************                                                                     ***************/
/*************************************************************************************************/
#define MOTOR_0_PIN                     3
#define MOTOR_1_PIN                     0
#define MOTOR_2_PIN                     4
#define MOTOR_3_PIN                     5
#define MOTOR_4_PIN                     1
#define MOTOR_5_PIN                     2
#define MOTOR_6_PIN                     6
#define MOTOR_7_PIN                     7
#define OUTPUT_0_MOTOR                  5 //F
#define OUTPUT_1_MOTOR                  0 //A
#define OUTPUT_2_MOTOR                  1 //B
#define OUTPUT_3_MOTOR                  4 //E
#define OUTPUT_4_MOTOR                  6 //G
#define OUTPUT_5_MOTOR                  7 //H
#define OUTPUT_6_MOTOR                  2 //C
#define OUTPUT_7_MOTOR                  3 //D

/*"Pin" 0: E1(+), E2(-)
  "Pin" 1: F1(+), F2(-)
  "Pin" 2: G1(+), G2(-)
  "Pin" 3: H1(+), H2(-)
  "Pin" 4: A1(+), A2(-)
  "Pin" 5: B1(+), B2(-)
  "Pin" 6: C1(+), C2(-)
  "Pin" 7: D1(+), D2(-)  */

/*************************************************************************************************/
/*************                                                                     ***************/
/*************                          Misc Definitions                           ***************/
/*************                                                                     ***************/
/*************************************************************************************************/
// Stick handler definitions
#define BREAKPOINT                              1500
#define MINCHECK                                1100
#define MAXCHECK                                1900
#define ROL_LO                                  (1<<(2*ROLL))
#define ROL_CE                                  (3<<(2*ROLL))
#define ROL_HI                                  (2<<(2*ROLL))
#define PIT_LO                                  (1<<(2*PITCH))
#define PIT_CE                                  (3<<(2*PITCH))
#define PIT_HI                                  (2<<(2*PITCH))
#define YAW_LO                                  (1<<(2*YAW))
#define YAW_CE                                  (3<<(2*YAW))
#define YAW_HI                                  (2<<(2*YAW))
#define THR_LO                                  (1<<(2*THROTTLE))
#define THR_CE                                  (3<<(2*THROTTLE))
#define THR_HI                                  (2<<(2*THROTTLE))

// Altitude hold throttle neutral zone
#if !defined(ALT_HOLD_THROTTLE_NEUTRAL_ZONE)
  #define ALT_HOLD_THROTTLE_NEUTRAL_ZONE        40
#endif 

// World coordinate index definitions
#define LAT                                     0
#define LON                                     1
#define Z                                       2

/*************************************************************************************************/
/*************                                                                     ***************/
/*************                       Default PID Constants                         ***************/
/*************                                                                     ***************/
/*************************************************************************************************/
#define ROLL_P                                  33
#define ROLL_I                                  30
#define ROLL_D                                  23
#define PITCH_P                                 33
#define PITCH_I                                 30
#define PITCH_D                                 23
#define YAW_P                                   68
#define YAW_I                                   45
#define YAW_D                                   0
#define PIDALT_P                                64
#define PIDALT_I                                25
#define PIDALT_D                                24
#define PIDLEVEL_P                              90
#define PIDLEVEL_I                              10
#define PIDLEVEL_D                              100
#define PIDMAG_P                                40
#define PIDVEL_P                                0
#define PIDVEL_I                                0
#define PIDVEL_D                                0
#define RC_RATE                                 90
#define RC_EXPO                                 65
#define ROLL_PITCH_RATE                         0
#define YAW_RATE                                0
#define DYN_THR_PID                             0
#define THR_MID                                 50
#define THR_EXPO                                0
#define POSHOLD_P                               11
#define POSHOLD_I                               0
#define POSHOLD_IMAX                            20 // degrees
#define POSHOLD_RATE_P                          20
#define POSHOLD_RATE_I                          8
#define POSHOLD_RATE_D                          45
#define POSHOLD_RATE_IMAX                       20 // degrees
#define NAV_P                                   14
#define NAV_I                                   20
#define NAV_D                                   80
#define NAV_IMAX                                20 // degrees

/*************************************************************************************************/
/*************                                                                     ***************/
/*************                       Error Checking Section                        ***************/
/*************                                                                     ***************/
/*************************************************************************************************/
#ifndef NUMBER_MOTOR
  #error "NUMBER_MOTOR is not set, most likely you have not defined any type of multicopter"
#endif
#ifndef SENTRAL
  #error "Does this board have an EM7180?"
#endif
#ifdef RCOIP_RX
  #ifdef WIFI_DEBUG
    #error "Cannot use Wifi debug telemetry with RCOIP receiver!"
  #endif
#endif

#endif // def_h
