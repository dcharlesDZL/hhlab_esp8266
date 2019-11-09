//初始化参数
void initPara()
{
    apssid = "hhlab";
    appasswd = "hhlab123456";
    clientID = "hhlabhardware";
    nickname = "hhlab_abc";
    stassid = "iPhone11";
    stapasswd = "douzhengli123";
    SN = "1234567890";
    serverAddr = "http://101.132.151.192/";
    serverURL = "";
    uploadContent = "abc";
}
//初始化服务器，开发板做服务器
void serverInit(){
    espServer.on("/", HTTP_GET, homepage);
    espServer.onNotFound(homepage); 
    espServer.begin();
}
//初始化向后台服务器请求
void serverRequestInit()
{
    String addr = serverAddr;//HTTP请求对格式要求很严格，必须符合语法要求
    String url = serverURL;
    String content = uploadContent;
    http.begin(addr);
}
//连接mqtt服务器
void initMQTTserver()
{
	mqttclient.disconnect();
	mqttclient.setServer(mqttServer, mqttPort);
	mqttclient.connect();
}

//设备参数初始化
void initPara()
{

}