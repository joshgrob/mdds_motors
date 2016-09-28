#ifndef types_h
#define types_h

/*************************************************************************************************/
/*************                                                                     ***************/
/*************                 Enumerators and Structure Variables                 ***************/
/*************                                                                     ***************/
/*************************************************************************************************/
enum rc
{
  ROLL,
  PITCH,
  YAW,
  THROTTLE,
  AUX1,
  AUX2,
  AUX3,
  AUX4
};

enum pid
{
  PIDROLL,
  PIDPITCH,
  PIDYAW,
  PIDALT,
  PIDPOS,
  PIDPOSR,
  PIDNAVR,
  PIDLEVEL,
  PIDMAG,
  PIDVEL,
  PIDDIM
};

const char pidnames[] PROGMEM =
  "ROLL;"
  "PITCH;"
  "YAW;"
  "ALT;"
  "Pos;"
  "PosR;"
  "NavR;"
  "LEVEL;"
  "MAG;"
  "VEL;"
;

enum box
{
  BOXARM,
  #if ACC
    BOXANGLE,
    BOXHORIZON,
  #endif
  #if BARO
    BOXBARO,
  #endif
  #if MAG
    BOXMAG,
    BOXHEADFREE,
    BOXHEADADJ,
  #endif
    BOXGPSHOME,
    BOXGPSHOLD,
  #ifdef OSD_SWITCH
    BOXOSD,
  #endif
  CHECKBOXITEMS
};

const char boxnames[] PROGMEM =
  "ARM;"
  #if ACC
    "ANGLE;"
    "HORIZON;"
  #endif
  #if BARO
    "BARO;"
  #endif
  #if MAG
    "MAG;"
    "HEADFREE;"
    "HEADADJ;"  
  #endif
  #if GPS
    "GPS HOME;"
    "GPS HOLD;"
  #endif
  #ifdef OSD_SWITCH
    "OSD SW;"
  #endif
;

const uint8_t boxids[] PROGMEM =
{
  0, //"ARM;"
  #if ACC
    1, //"ANGLE;"
    2, //"HORIZON;"
  #endif
  #if BARO
    3, //"BARO;"
  #endif
  #if MAG
    5, //"MAG;"
    6, //"HEADFREE;"
    7, //"HEADADJ;"  
  #endif
  #if GPS
    10, //"GPS HOME;"
    11, //"GPS HOLD;"
  #endif
  #ifdef OSD_SWITCH
    19, //"OSD_SWITCH;"
  #endif
};

struct flags_struct
{
  uint8_t OK_TO_ARM :1 ;
  uint8_t ARMED :1 ;
  uint8_t ACC_CALIBRATED :1 ;
  uint8_t NUNCHUKDATA :1 ;
  uint8_t ANGLE_MODE :1 ;
  uint8_t HORIZON_MODE :1 ;
  uint8_t MAG_MODE :1 ;
  uint8_t BARO_MODE :1 ;
  uint8_t GPS_HOME_MODE :1 ;
  uint8_t GPS_HOLD_MODE :1 ;
  uint8_t HEADFREE_MODE :1 ;
  uint8_t PASSTHRU_MODE :1 ;
  uint8_t GPS_FIX :1 ;
  uint8_t GPS_FIX_HOME :1 ;
  uint8_t SMALL_ANGLES_25 :1 ;
  uint8_t CALIBRATE_MAG :1 ;
  uint8_t VARIO_MODE :1;
};

struct global_conf_t
{
  uint8_t currentSet;
  int16_t accZero_max[3];
  int16_t accZero_min[3];
  int16_t magZero[3];
  int16_t grav;
  uint8_t checksum; // Last position in structure
};

struct conf_t
{
  uint8_t checkNewConf;
  uint8_t P8[PIDDIM], I8[PIDDIM], D8[PIDDIM];
  uint8_t rcRate8;
  uint8_t rcExpo8;
  uint8_t rollPitchRate;
  uint8_t yawRate;
  uint8_t dynThrPID;
  uint8_t thrMid8;
  uint8_t thrExpo8;
  int16_t angleTrim[2];
  uint16_t activate[CHECKBOXITEMS];
  uint8_t powerTrigger1;
  #ifdef TRI
    uint16_t tri_yaw_middle;
  #endif
  int16_t failsafe_throttle;
  #ifdef VBAT
    uint8_t vbatscale;
    uint8_t vbatlevel_warn1;
    uint8_t vbatlevel_warn2;
    uint8_t vbatlevel_crit;
    uint8_t no_vbat;
  #endif
  int16_t minthrottle;
  uint8_t  checksum; // Last position in structure
};

struct Sentral_WS_params
{
  uint8_t Sen_param[35][4];
};

struct biquad
{
  double a0;
  double a1;
  double a2;
  double b0;
  double b1;
  double b2;
};

struct biquad_reg
{
  double X1;
  double X2;
  double Y1;
  double Y2;
};

struct RCOIPv1ReplyReceiverStatus
{
    uint8_t version;
    uint8_t RSSI;
    uint8_t batteryVoltage;
};

typedef struct motor_data {
  uint8_t state;
  uint16_t intensity;
} Motor_data;
#endif // types_h
