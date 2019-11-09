//头文件
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <AsyncMqttClient.h>
#include <ArduinoJson.h>
#include "init.h"
#include "pt.h"
#include "initfunction.h"
#include "modbus.h"
#include "function.h"
#include "parameter.h"


/*----------------------------------*/





//设置ap模式
void setAP(){
	//WiFi.mode(WIFI_AP);
	IPAddress softLocalIP(192,168,128,2);
	IPAddress softGateway(192,168,128,1);
	IPAddress softSubnet(255,255,255,0);
	WiFi.softAPConfig(softLocalIP, softGateway, softSubnet);
	WiFi.softAP(apssid, appasswd);
}
//设置sta模式
void setSta(){
	WiFi.disconnect();
	WiFi.hostname(nickname);
	WiFi.begin(stassid, stapasswd);
}
//配网主页
void homepage(){    
	// sprintf(htmltext, "<html><head><meta charset='utf-8'><title>网页配置</title></head><body><form action='/' method='POST'><fieldset><legend align='center'>网页配置</legend><table align='center'><tr><td>设备SN号</td><td><p>%s</p></td></tr><tr><td>设备名字</td><td><input type='text' name='name' value=%s></td></tr><tr><td>路由器热点SSID:</td><td><input type='text' name='ssid' value=%s></td></tr><tr><td>路由器密码:</td><td><input type='text' name='pwd' value=%s></td></tr><tr><td colspan='2' align='center'><button type='submit'>更新配置</button></td></tr></table></fieldset></form><fieldset><legend align='center'>固件更新</legend><table align='center'> <tr> <td colspan='2' align='center'> <button onclick='window.location.href=&quot/update&quot;'>固件升级</button></td></tr></table></fieldset></body></html>", SN, clientID, stassid, stapasswd);
	// htmltext = "hello";
	htmltext = "<html><head><meta charset='utf-8'><title>网页配置</title></head><body><form action='/' method='POST'><fieldset><legend align='center'>网页配置</legend><table align='center'><tr><td>设备SN号</td><td><p>1234567890</p></td></tr><tr><td>设备名字</td><td><input type='text' name='name' ></td></tr><tr><td>路由器热点SSID:</td><td><input type='text' name='ssid' ></td></tr><tr><td>路由器密码:</td><td><input type='text' name='pwd' ></td></tr><tr><td colspan='2' align='center'><button type='submit'>更新配置</button></td></tr></table></fieldset></form><fieldset><legend align='center'>固件更新</legend><table align='center'> <tr> <td colspan='2' align='center'> <button onclick='window.location.href=&quot/update&quot;'>固件升级</button></td></tr></table></fieldset></body></html>";
	espServer.send(200,"text/html", htmltext);
}
//获取参数
void getArgs(){
	String client_id = espServer.arg("name");
	String sta_ssid = espServer.arg("ssid");
	String sta_passwd = espServer.arg("pwd");
	client_id.trim();
	sta_ssid.trim();
	sta_passwd.trim(); 
	strcpy_P(clientID, client_id.c_str());
	strcpy_P(stassid, sta_ssid.c_str());
	strcpy_P(stapasswd, sta_passwd.c_str());
}

//获取rs485数据
//void getRS485data()
//{
//    runningdata = "{'data':'64dc5f2b9fc43323f05ffe0b878c87997708462311111111111111111111111111111111111111'}";
//}
//发送请求
void serverRequest()   //凡是涉及到Serial的都为串口测试用，生产中应删除。
{ 
	http.POST(runningdata);
	http.end();
	delay(1000);
}



/*-------------------------------------*/
void setup()
{
	initPara();
	Serial.begin(115200);
	setSta();
	WiFi.mode(WIFI_STA);
	serverInit();
	serverRequestInit();
	initMQTTserver();
	//mqttclient.connect(serverAddr, 1883);

}
void loop()
{
	threadRs485_entry(&thread_modbus);
	slaverSendMessageToMQTT();
	serverRequest();
}
