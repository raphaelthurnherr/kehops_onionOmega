/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   type.h
 * Author: raph-pnp
 *
 * Created on 18. octobre 2018, 12:01
 */

#ifndef TYPE_H
#define TYPE_H

#ifdef __cplusplus
extern "C" {
#endif
#include"../buggy_descriptor.h"

typedef struct tSystem{
	char name[32];
        long startUpTime;
        char firmwareVersion[32];
        char mcuVersion[32];
        char HWrevision[32];
        float battVoltage;
        int wan_online;
}t_system;    
    
    
// -----------------------------
// EVENEMENTS
// -----------------------------
struct s_eventAnalog{
	int enable;
	int low;
	int high;
	int hysteresis;
};

struct s_eventBool{
	int enable;
};


// --------------------------------------
// HIGH LEVEL
// --------------------------------------



struct s_pid{
    char  enable;
    float Kp;
    float Ki;
    float Kd;
};

struct s_wheel_meas{
    int  distance;
    int  rpm;
    int  speed_cmS;
    int  speed_percent;
};

struct dc_wheel_data{
    float _MMPP;
    float _MAXSPEED_CMSEC;
    float startValue;
    float stopValue;
};

struct s_motor_config{
    char dc_motor_name[25];
    int dc_motor_id;
    char inverted;   
    int powerMin;   
};

struct s_counter_config{
    int freqCounter_id;
    int pulseCounter_id;
};

struct dcwheel_settarget{
    int time;
    int distanceCM;
    int angle;
    int rotation;
};

// --------------------------------------
struct stepwheel_settarget{
    int steps;
    int time;
    int distanceCM;
    int angle;
    int rotation;
};

struct dc_wheel_config{
    struct s_pid pidReg;
    struct s_motor_config motor;
    struct s_counter_config encoder;
    int diameter;           // Config of wheel diameter in mm
    int pulsesPerRot;       // Config number of pulses per rotation of encoder
    int rpmMax;             // Config max supperted RPM of Wheel (motor)
    int rpmMin;             // Config min supported RPM of Wheel (motor)
};

struct s_stepper_config{
    int stepper_motor_id;
    char stepper_name[25];
    char inverted;   
    int steps;   
    int ratio;
};


struct robot_stepper_sp{
    int userSpeedSetPoint;
    char direction;    
    int steps;  
};

struct robot_motor_sp{
    int userSpeedSetPoint;
    int direction;    
};

struct stepper_wheel_config{
    struct s_pid pidReg;
    struct s_stepper_config motor;
    int diameter;           // Config of wheel diameter in mm
    int rpmMax;             // Config max supperted RPM of Wheel (motor)
    int rpmMin;             // Config min supported RPM of Wheel (motor)
};

typedef struct robotDCWheel{
    struct robot_motor_sp motor;
    struct dcwheel_settarget target;
    struct dc_wheel_config config;
    struct s_wheel_meas measure;
    struct dc_wheel_data data;
}robot_dcwheel;

typedef struct robotStepperWheel{
    struct stepwheel_settarget target;
    struct robot_stepper_sp motor;
    struct stepper_wheel_config config;
    struct s_wheel_meas measure;
}robot_stepperwheel;



// AIN & BATTERY  

struct s_son_config{
    int  distanceSensor_id;
    char name[25];
};

struct s_ain_config{
    int  ain_id;
    char name[25];
};

struct s_ain_meas{
    int  voltage_mV;
    int  capacity;
};

struct s_sonar_meas{
    int  distance_cm;
};

typedef struct robotAin{
    struct s_ain_config config;
    struct s_ain_meas measure;
    struct s_eventAnalog event;
}robot_ain;

typedef struct robotSonar{
    struct s_son_config config;
    struct s_sonar_meas measure;
    struct s_eventAnalog event;
}robot_sonar;


// BUTTONS

struct s_button_config{
    int  din_id;
    char name[25];
};

struct s_button_meas{
    int  state;
};

struct s_color_meas{
    int  value;
};

struct s_color_data{
        struct s_color_meas measure;
        struct s_eventAnalog event;
};

struct s_rgb_config{ 
    int rgbID;
    char name[25];
};

struct s_gfx_action{
    int  timeOut;
};

struct s_gfx_config{ 
    int gfx_id;
    char name[25];
    struct s_eventBool hid;
};

struct s_rgb_meas{
    struct s_color_data red;
    struct s_color_data green;
    struct s_color_data blue;
    struct s_color_data clear;
};

struct s_prox_meas{
    int  state;
};

struct s_prox_config{
    int  din_id;
    char name[25];
};

typedef struct robotButton{
    struct s_button_config config;
    struct s_button_meas measure;
    struct s_eventBool event;
    
}robot_button;

typedef struct robotProx{
    struct s_prox_config config;
    struct s_prox_meas measure;
    struct s_eventBool event;
}robot_prox;

// COmmunication & MQTT 

struct mqtt_stream{
    int  state;
    int  time_ms;
    int  onEvent;
    int  topic;
};

struct mqtt_broker{
    char address[128];
};

struct s_mqtt{
    struct mqtt_broker broker;
    struct mqtt_stream stream;
};

struct s_udp_bc{
    int  state;
    int  time_ms;
};


struct s_udp{
    struct s_udp_bc broadcast;
};

struct sys_comm{
    struct s_mqtt mqtt;
    struct s_udp udp;
};


// DOUT, PWM and LEDS

struct s_pwm_action{
    int  blinkCount;
    int  blinkTime;
};



struct s_pwm_config{
    int  dout_id;
    char name[25];
    int  mode;
    int  defaultPower;
    int  defaultState;
};

struct s_aout_config{
    int  aout_id;
    char name[25];
    int  mode;
    int  defaultPower;
    int  defaultState;
};

typedef struct robotPwm{
    int state;
    int power;
    struct s_pwm_config config;
    struct s_pwm_action action;
}robot_pwm;

typedef struct robotAnalog{
    int state;
    int power;
    int value;
    struct s_aout_config config;
    //struct s_aout_action action;
}robot_aout;

typedef struct robotRgb{
    struct s_rgb_meas color;
    struct s_rgb_config config;
    struct s_eventBool event;
}robot_rgb;

typedef struct robotGfx{
    char text[64];
    char border[25];
    char icon[25];
    struct s_gfx_config config;
    struct s_gfx_action action;
}robot_gfx;


typedef struct robotKehops{
    robot_ain analogInput[MAXAIN];
    robot_button button[MAXBTN];
    robot_stepperwheel stepperWheel[MAXSTEPPER];
    robot_dcwheel dcWheel[MAXMOTOR];
    robot_pwm led[MAXLED];
    robot_pwm pwm[MAXPWM];
    robot_aout aout[MAXAOUT];
    robot_prox proximity[MAXDIN];
    robot_sonar sonar[MAXSONAR];
    robot_rgb rgb[MAXRGBC];
    robot_gfx gfx[MAXGFX];
}robot_kehops;


struct tInfosys{
	char name[32];
        char group[32];
        long startUpTime;
        char firmwareVersion[32];
        char mcuVersion[32];
        char HWrevision[32];
        float battVoltage;
        int wan_online;
};

struct app_kehops{
    char resetConfig;
};


typedef struct systemApp{
    struct app_kehops kehops;
    struct tInfosys info;
}t_sysApp;


struct authType{
    char mode [15];   // Encryption PSK, PSK2
};

struct wpaType{
    char type [15];   // Encryption PSK, PSK2
};

struct wifiEncrypt{
    char enable[15];
    int authCnt;
    int wpaCnt;
    struct authType authentification[10];
    struct wpaType wpa[10];
};


struct accesspoint_data{
    char ssid[32];          // Nom du réseau
    char key[32];          // mOT DE PASSE
    char active[15];
    struct wifiEncrypt encryption;    //  Encryption activée ON/OFF
    
};  

typedef struct wifiData{
    int wifiDetected;
    struct accesspoint_data list[25];
}APDATA;
        
typedef struct systemConf{
    struct sys_comm communication;
    APDATA wifi;
}t_sysConf;

#ifdef __cplusplus
}
#endif

#endif /* TYPE_H */

