//modbus数据结构
#pragma pack(1)  //让编译器将结构体数据强制连续排列，数据输出更紧凑
struct 
{
  union     //UN1  主机向从机写数据
  {
    struct
    {
      u8 devnum;            //设备号
      u8 funcode;           //功能码(0x10写)
      u8 idhigh;            //起始地址高八位
      u8 idlow;             //起始地址低八位
      u8 numhigh;           //寄存器数高八位
      u8 numlow;            //寄存器数低八位
      u8 datalen;           //数据字节长度
      s16 setTemp;          //设定温度
      s16 setSpeed;         //设定速度
      s16 setTimeHour;      //设定时间（小时）
      s16 setTimeMinute;    //设定时间（分钟）
      u16 tempMin;          //设定温度量程最小值
      u16 tempMax;          //设定温度量程最大值
      u16 speedMin;         //设定温度最小值
      u16 speedMax;         //设定温度最大值
      u16 setRunStop;        //设置运行状态
      s16 setCurrentMode;   //设置当前模式（1/2/3）
      u16 setPwrOffMem;    //设置掉电记忆(0/1)
    }__attribute__((aligned (1))) masterBuf;
    u8 masterPtr[40];
  } UN1;
  
  union       //UN2  当主机发送读取指令后从机向主机返回的参数
  {
    struct {
      u8 devnum;           //地址码
      u8 funcode;          //功能码
      u8 datalen;          //返回的数据长度
      u16 type;            //机器类型（全部两字节）
      u16 temp;            //当前温度
      u16 setTemp;         //温度设定值
      u16 speed;           //当前速度
      u16 setSpeed;        //速度设定值
      u16 setTimeHour;     //小时设定值
      u16 setTimeMinute;   //分钟设定值
      u16 timeHour;        //当前小时值
      u16 timeMinute;      //当前分钟值
      u16 tempRangeMin;    //温度量程最小值
      u16 tempRangeMax;    //温度量程最大值
      u16 speedMin;        //速度最小值
      u16 speedMax;        //速度最大值
      u16 alarm;           //故障告警（使用0-9位）
      u16 runStop;          //运行停止（到此处一共15个数据，共30字节）
      u16 currentMode;     //当前模式（协议2.2添加的）
      u16 powerOffMem;     //掉电记忆（协议2.2添加的）
      u16 checkcode;             //校验码
    }slaveBuf;                   //从机缓冲 modbus
    u8 slavePtr[40];             //从机返回的数据
  }UN2;
}RS485A;
#pragma pack()

/*
机器参数：仅是机器类型为100的设备参数列表，
保存了可读部分（即显示值）和可写部分（即设定值）参数值。
*/
struct  
{                   
  u16 machineType;
  s16 paraTemp;
  s16 setTemp;     //缺省值为50
  u16 paraSpeed;
  u16 setSpeed;     //速度设定缺省值为100
  u16 setTimeHour;
  u16 setTimeMinute;
  u16 paraTimeHour;
  u16 paraTimeMinute;
  s16 TempRangeMin;
  s16 TempRangeMax;    //最大设定温度为320
  u16 paraSpeedMin; 
  u16 paraSpeedMax;
  u16 setSpeedMin;     //最小设定速度缺省值为100
  u16 setSpeedMax;    //最大设定速度缺省值为1500
  /*告警值，位操作*/
  u8 innerSensorAlarm;
  u8 innerSensorTempAlarm;
  u8 externalSensorAlarm;
  u8 externalSensorOverheat;
  u8 machineTempOverheat;
  u8 machineTempSensorAlarm;
  u8 motorStalling;
  u8 externalSensorDrop;
  u8 timingOver;
  u8 externalSensorUnplugged;
  /*****************/
  u16 paraRunStop;
  u16 paraCurrentMode;     //（协议2.2添加）
  u16 paraPwrOffMem;
  u16 setCurrentMode;
  u16 setPwrOffMem;
}MachinePara;



struct {
  time_t cpuTime;//CPU UNIX时间
  time_t startupTime;
  byte wifiPwrOnAlm;
  int mqttState;
  byte rs485Triged;
  byte startSmartconfig;
  byte alarm; 
  byte sosAlarm;
  byte paraRestore; 
  byte yunUpload;
  byte portMode;

  byte tempRemote;
  byte remoteSetReply;
  byte firstAlarmCount;  
  int controlDelayWIFI;
  byte wifisConnected;
}RunningPara;



union
{
  struct
  {
    char jiami[30];
    byte timeControlEn; //定时
    byte ntpEn;         //网络授时
    byte uploadEn;
    byte wxAlarmEn;
    byte ldctrlEn;      //联动控制使能
    byte alarmEn;       //报警总开关
    byte fileEn;        //数据文件记录

    byte controllerAlarmEn; //控制器内部报警
    byte relayStartUp;
    byte portMode;
    byte deviceID; 
    byte wifiMode;  //0STA 1AP 2STA+AP
    byte isDhcp;
    byte ip[4];
    byte dns[4];
    byte gateway[4];
    byte subnet[4];

    char dispValue[5][30];
    char stassid[20];
    char stapasswd[20];
    char apssid[20];
    char appasswd[20];
    char authname[20];
    char authpasswd[20];

    int wlinterval;//上传间隔
    char customuptemp[120];
    char customupurl[70];    
    char customupaddr[30];//CUSTOM上传
    char customupkey[45];
    
    int fileRecordInterval;
    char fileTemplate[10];
    int screenInterval;
    char screenTemplate[10];

    char openID[60];//微信OPENID
    char openID2[60];//微信OPENID
    char appid[60];//APP的UUID
    char usercode[10];
    char opencode[10];
    char nickname[20];
    char punycode[20];
    char concmds[3][50];
    byte conact[3];
  } Para;
  byte bytes[100];
}SavePara;
