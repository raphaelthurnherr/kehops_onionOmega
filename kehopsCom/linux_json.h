#define MAX_MQTT_BUFF 8192

#include "../type.h"

// DEFINITION DES TYPES DE MESSAGE
typedef enum msgformat{
	EVENT_ACTION_ERROR,
	EVENT_ACTION_END,
	EVENT_ACTION_BEGIN,
	EVENT_ACTION_ABORT,
        EVENT_ACTION_RUN,
        RESP_FIRMWARE,
        RESP_WIFI_COMMAND,
        RESP_WIFI_DATA,
        RESP_WIFI_SCAN,
        RESP_WIFI_NETWORK_LIST, 
        RESP_DASH,
	RESP_STD_MESSAGE,
} t_msgformat;

// DEFINITION DES TYPES DE MESSAGE
typedef enum msgtype{
	ERR_TYPE,
	COMMAND,
	REQUEST,
	ACK,
	RESPONSE,
	EVENT,
        DATAFLOW,
} t_msgtype;

// DEFINITION DES PARAMETRES DE TYPE PARAMETRE
typedef enum msgparam{
        ERR_HEADER,     // Not use
	ERR_PARAM,     
	STOP,           // Not use
	MOVE,           // Not use
	MOTORS,
	DINPUT,
	DISTANCE,
	VOLTAGE,
	pPWM,
	pLED,
        pAOUT,
        pSERVO,
	STATUS,
        BUTTON,
        COLORS,
        CONFIG,
        SYSTEM,
        STEPPER,
}t_msgparam;


struct m2wd{
	int motor;
	int speed;
        int userSetPoint;
	int time;
	float cm;
};

struct mStepper{
	int motor;
	int userSetPoint;
	int step;
	int rotation;
        int angle;
        int time;
};

struct mDin{
	int id;
	char event_state[25];
};

struct mAin{
	int id;
	char event_state[25];
        int event_low;
        int event_high;
        int event_hyst;
};

struct mBroker{
	char address[128];
};

struct mStream{
	char state[25];
        char onEvent[25];
	int time;
};

struct mAppConf{
	char reset[25];
        char save[25];
};

struct mInfoID{
	char name[25];
        char group[25];
};


struct mPIDConfig{
        char PIDstate[25];
        float PID_Ki;
        float PID_Kp;
        float PID_Kd;
};

struct mMotConfig{
        int id;
	char inverted[25];
        int  minRPM;
        int  maxRPM;
        int  minPWM;
        struct mPIDConfig rpmRegulator;
};

struct mWheelConfig{
	int id;
	int diameter;
	int pulsesPerRot;
};

struct mStepperConfig{
        int id;
	char inverted[25];
        int  ratio;
        int  stepsPerRot;
};

struct mLedConfig{
        int id;
	char state[25];
	int power;
        char isServoMode[25];
};

struct mAoutConfig{
        int id;
	char state[25];
	int power;
};

struct mConfig{
        int motValueCnt;
        int ledValueCnt;
        int pwmValueCnt;
        int aoutValueCnt;
        int btnValueCnt;
        int dinValueCnt;
        int sonarValueCnt;
        int battValueCnt;
        int stepperValueCnt;
        int wheelValueCnt;
	struct mStream stream;
        struct mBroker broker;
        struct mAppConf action;
        struct mInfoID robot;
        struct mMotConfig motor[10];
        struct mWheelConfig wheel[10];
        struct mStepperConfig stepper[10];
        struct mLedConfig led[10];
        struct mLedConfig pwm[10];
        struct mAoutConfig Aout[10];
        struct mDin btn[10];
        struct mDin din[10];
        struct mAin sonar[10];
        struct mAin ain[10];
};

struct mDistance{
	int id;
	char event_state[50];
	int event_low;
	int event_high;
	int angle;
};

struct mBattery{
	int id;
	char event_state[50];
	int event_low;
	int event_high;
        int capacity;
};

struct mPwm{
	int id;
	char state[50];
	int angle;
};

struct mAout{
	int id;
	char state[50];
	int powerPercent;
        int value;
};

struct mLed{
	int id;
	char state[50];
	int powerPercent;
        int time;
        int blinkCount;
//        char isServoMode;
};


struct mServo{
	int id;
	int posPercent;
	int state;
};

struct mSystem{
	char name[32];
        int startUpTime;
        char firmwareVersion[32];
        char mcuVersion[32];
        char HWrevision[32];
        float battVoltage;
        int battPercent;
        int wan_online;
        int tx_message;
        int rx_message;   
};

struct wificonfig{
    char ssid[32];
    char key[64];
    char security[32];
};


typedef struct wifiCmd{
    int index;
    char name[15];
    char mode[15];
    struct wificonfig config;   
}WIFI_SETTING;

struct wifiMessage{
    struct wifiCmd command;
    int WifiDetected;
    APDATA scanResult;
};


struct mSystemCmd{
        char dashboardCommand[32];
        char firmwareCommand[32];
        struct wifiMessage wifi;
};

struct mColor{
        int value;
	int event_low;
	int event_high;
};

struct mRGB{
	int id;
        char event_state[50];
        struct mColor red;
        struct mColor green;
        struct mColor blue;
        struct mColor clear;
};

// Structure d'un message algoid recu
typedef struct JsonCommand{
	char msgTo[32];
	char msgFrom[32];
	int msgID;
	t_msgtype msgType;
	t_msgparam msgParam;
	unsigned char msgValueCnt;

	// UNION ???
	struct m2wd DCmotor[20];
        struct mStepper StepperMotor[20];
	struct mDin DINsens[20];
        struct mDin BTNsens[20];
	struct mDistance DISTsens[20];
	struct mBattery BATTsens[20];
	struct mLed PWMarray[20];
        struct mLed LEDarray[20]; // LED (internal board pwm)
        struct mAout Aout[20];
        struct mRGB RGBsens[20];
        struct mConfig Config;
        struct mSystemCmd System;
	// UNION ???
}ALGOID;

// Structure de r�ponse � un message algoid
typedef struct JsonResponse{
	int value;
	int responseType;

        struct mSystem SYSresponse;
	struct mDin DINresponse;
	struct mBattery BATTesponse;
	struct mDistance DISTresponse;
        struct mServo SERVOresponse;
	struct m2wd MOTresponse;
        struct mStepper STEPPERresponse;
        struct mLed PWMresponse;
        struct mAout AOUTresponse;
        struct mLed LEDresponse;
        struct mDin BTNresponse;
        struct mRGB RGBresponse; 
        struct mConfig CONFIGresponse;
        struct mSystemCmd SYSCMDresponse;
        char returnMessage[100];
}ALGOID_RESPONSE;

ALGOID message;    // Utilis� par main.c
ALGOID AlgoidMsgRXStack[10];

// Buffer de sortie pour les msgValue[
ALGOID_RESPONSE messageResponse[100];

//extern t_sysConfig sysConfig;

extern char GetAlgoidMsg(ALGOID *DestReceiveMessage,char *srcDataBuffer);

void jsonBuilder(char * buffer, int msgId, char* to, char * from, char * msgType,char * msgParam, unsigned char value, unsigned char count);
