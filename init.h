//变量声明
char* apssid, *appasswd, *nickname,*SN, *clientID, *stassid, *stapasswd, *htmltext;
char* serverAddr, *serverURL, *uploadContent;
ESP8266WebServer espServer(80);
HTTPClient http;
String responseContent;
char *runningdata;
AsyncMqttClient mqttclient;