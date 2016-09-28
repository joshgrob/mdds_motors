#ifndef config_h
#define config_h

/*************************************************************************************************/
/*************                                                                     ***************/
/*************                     SECTION  1 - BASIC SETUP                        ***************/
/*************                                                                     ***************/
/*************************************************************************************************/
/**************************              Loop Cycletime               ****************************/

    #define CYCLETIME_TARGET              2000

/**************************            Type of Multicopter            ****************************/
    /* Uncomment one Multitype only */
    //#define                                 QUADP
    //#define                                 QUADX
    //#define                                 Y4
    //#define                                 Y6
    //#define                                 HEX6
    //#define                                 HEX6X
    #define                                 FPV_90DEG_HEX6X
    //#define                                 HEX6H
    //#define                                 OCTOX8
    //#define                                 OCTOFLATP
    //#define                                 OCTOFLATX
    //#define                                 VTAIL4

/********************        ESP8266/EM7180 Flight Controller Boards        **********************/
    /* Add boards as they become available */
    #define PP_EM7180_MPU6500_AK8963_BMP280 // Pesky Products MS6500+AK8963+BMP280+EM7180
    
/**************************             Motor Output Pins             ****************************/

/**************************          Radio Control Receiver           ****************************/
    /* Uncomment one receiver type only */
    #define PPM_RX
    //#define RCOIP_RX
    
    #if defined(PPM_RX)
      #define RC_CHANS                    6
      #define RX_PIN                      14

      /* Channel order for GUI*/
      #define RC_THR                      4
      #define RC_PITCH                    2
      #define RC_ROLL                     1
      #define RC_YAW                      3
      #define RC_AUX1                     5
      #define RC_AUX2                     6
      #define RC_AUX3                     0
      #define RC_AUX4                     0
      #define RC_AUX5                     0
      #define RC_AUX6                     0

      /* Pulse order in cPPM pulse train*/
      #define PULSE_POS_ROLL              0
      #define PULSE_POS_PITCH             1
      #define PULSE_POS_YAW               3
      #define PULSE_POS_THR               2
      #define PULSE_POS_AUX1              4
      #define PULSE_POS_AUX2              5
      #define PULSE_POS_AUX3              6
      #define PULSE_POS_AUX4              7
      #define PULSE_POS_AUX5              8
      #define PULSE_POS_AUX6              9
    #endif
    #define PACKET_SIZE                 RC_CHANS + 1
    #if defined(RCOIP_RX)
      #define RC_CHANS                    10
      #define RC_THR                      2
      #define RC_PITCH                    4
      #define RC_ROLL                     3
      #define RC_YAW                      1
      #define RC_AUX1                     5
      #define RC_AUX2                     6
      #define RC_AUX3                     7
      #define RC_AUX4                     8
      #define RC_AUX5                     9
      #define RC_AUX6                     10
    #endif
    
/**************************             Motor Minthrottle             ****************************/

    /* Set the minimum throttle command sent to the ESC (Electronic Speed Controller) */
    #define MINTHROTTLE                 1000 // Brushed
    
/**************************             Motor Maxthrottle             ****************************/

    /* Maximum value for the ESCs to reach full power; this value can be increased up to 2000 */
    #define MAXTHROTTLE                 2000 // Brushed

/**************************             Motor Mincommand              ****************************/

    /* This is the default output to each motor channel prior to arming */
    #define MINCOMMAND                  1000

/*************************************************************************************************/
/*************                                                                     ***************/
/*************                    SECTION  3 - EXTENDED SETUP                      ***************/
/*************                                                                     ***************/
/*************************************************************************************************/

/**************************               Comm Port Speed             ****************************/
    #define SERIAL0_COM_SPEED           115200
    #define SERIAL1_COM_SPEED           115200

/**************************            Gyro/Accel Filters             ****************************/

    /* MPU9250 Gyro low pass filter setting. Uncomment only one option */
    #define MPU9250_GYRO_LPF_184HZ // (Default)
    //#define MPU9250_GYRO_LPF_92HZ
    //#define MPU9250_GYRO_LPF_41HZ
    //#define MPU9250_GYRO_LPF_20HZ
    //#define MPU9250_GYRO_LPF_10HZ
    //#define MPU9250_GYRO_LPF_5HZ

    /* MPU9250 Acc low pass filter setting. Uncomment only one option */
    //#define MPU9250_ACC_LPF_460HZ  (Default)
    //#define MPU9250_ACC_LPF_184HZ
    //#define MPU9250_ACC_LPF_92HZ
    //#define MPU9250_ACC_LPF_41HZ
    #define MPU9250_ACC_LPF_20HZ
    //#define MPU9250_ACC_LPF_10HZ
    //#define MPU9250_ACC_LPF_5HZ

/**************************          Sentral Calibrations             ****************************/

      /* Define as 0 to suppress Acc scale/offset corrections */
      #define ACCEL_CAL                   1
      //#define ACCEL_CAL                   0
      
      /* Define as 0 to suppress Sentral "Warm Start" heading correction */
      #define SENTRAL_WARM_START          1
      //#define SENTRAL_WARM_START          0

/*************************************************************************************************/
/*************                                                                     ***************/
/*************                   SECTION  4 - OPTIONAL FEATURES                    ***************/
/*************                                                                     ***************/
/*************************************************************************************************/
/**************************                 TX-related                ****************************/

      /* Introduce a deadband at stick center position*/
      //#define DEADBAND                    6

/**************************                 Arm/Disarm                ****************************/

    #define ALLOW_ARM_DISARM_VIA_TX_YAW
    //#define ALLOW_ARM_DISARM_VIA_TX_ROLL

/**************************               Altitude Hold               ****************************/

      /* Defines an additional deadband for the throttle stick while in altitude hold.
         Move the throttle out of the deadband to raise/lower altitude setpoint. Move
         the throttle back into the deadband to resume altitude hold. Default = 40 */
      #define ALT_HOLD_THROTTLE_NEUTRAL_ZONE 100 

      /* Defines the correction slope for altitude hold voltage sag compensation.
         More negative values give more aggressive compensation */
      #define ALTHOLD_VOLTAGE_COMP_SLOPE     -30.0f // -24.3 original

/********************                 Magnetic Declination                 ***********************/

      /* Magnetic decliniation data: http://magnetic-declination.com/
         Units are decimal degrees (Not DMS)*/
         
      //#define MAG_DECLINIATION            3.96f // For Budapest Hungary.
      //#define MAG_DECLINIATION            13.80f // For Sunnyvale, CA USA.
      //#define MAG_DECLINIATION            14.30f // For Kelseyville, CA USA.
      #define MAG_DECLINIATION            14.05f // Composite between Sunnyvale and Kelseyville
      #define AIRFRAME_HEADING_ERROR      0.0f // Board-frame angular mounting error

/**************************             Failsafe settings             ****************************/

      //#define FAILSAFE                      // Uncomment  to activate the failsafe function
      #define FAILSAFE_DELAY              10  // Guard time for failsafe activation (10 = 1s)
      #define FAILSAFE_OFF_DELAY          200 // Time for Landing before motors stop (200 = 20s)
      #define FAILSAFE_THROTTLE           (MINTHROTTLE + 200) // Throttle level used for landing

/**************************              Battery Monitor              ****************************/

    /* for V BAT monitoring */
    //#define VBAT // uncomment this line to activate the vbat code
    #define VBATSCALE                     131
    #define VBATNOMINAL                   63.0f // 3.7V (0=0V, 255=15V)
    #define VBATLEVEL_WARN1               107 // 10,7V
    #define VBATLEVEL_WARN2               99 // 9.9V
    #define VBATLEVEL_CRIT                93 //  9.3V
    #define NO_VBAT                       16 //(*) Avoid beeping without any battery

/*************************************************************************************************/
/*************                                                                     ***************/
/*************                   SECTION  5 - EXTENDED FEATURES                    ***************/
/*************                                                                     ***************/
/*************************************************************************************************/
/**************************                  Presets                  ****************************/
    /* Some radios have not the neutral point at 1500us. Custom values ca be set here */
    #define MIDRC                         1500

/**************************         Serial Command Handling           ****************************/
    /* Legacy MultiWii Serial Protocol (MSP) settings */
    //#define SUPPRESS_ALL_SERIAL_MSP // Saves approx 2700 bytes
    //#define SUPPRESS_OTHER_SERIAL_COMMANDS // Saves  approx 0 to 100 bytes
    
/**************************           WiFi Debug Telemetry            ****************************/
    /* Can only be used with cPPM Receiver */
    #define WIFI_DEBUG

/**************************            End Configuration              ****************************/
#endif
