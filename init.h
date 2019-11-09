//变量声明
char* apssid, *appasswd, *nickname,*SN, *clientID, *stassid, *stapasswd, *htmltext;
char *serverAddr, *serverURL, *uploadContent, *mqttServer, *wechatServer;
char *topic, * payload;
char modelname[20];
uint16_t mqttPort;
ESP8266WebServer espServer(80);
HTTPClient http;
String responseContent;
char *runningdata;
AsyncMqttClient mqttclient;
static struct pt thread_key, thread_modbus;
SoftwareSerial RS485;
void slaverDataDelivery();
StaticJsonDocument<200> jsonBuffer;
struct 
{
	struct 
	{
		u16 machinecode = 100;
		u8 paranum = 26;
		char name[11] = "CCLH_BASIC";
	}CCLH_BASIC;
	struct
	{
		u16 machinecode = 101;
		u8 paranum = 21;
	}RCLH_BASIC;

}MACHINE_TYPE;

//函数声明






//变量赋初值


