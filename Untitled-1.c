#include <ESP8266WiFi.h>
#include <Ticker.h>
#include <AsyncMqttClient.h>

#if ASYNC_TCP_SSL_ENABLED
#define MQTT_SECURE true
#define MQTT_SERVER_FINGERPRINT {0x7e, 0x36, 0x22, 0x01, 0xf9, 0x7e, 0x99, 0x2f, 0xc5, 0xdb, 0x3d, 0xbe, 0xac, 0x48, 0x67, 0x5b, 0x5d, 0x47, 0x94, 0xd2}
#define MQTT_PORT 8883
#else
#define MQTT_PORT 1883
#endif

#define WIFI_SSID "MyHome"
#define WIFI_PASSWORD "1234567"

const char* host = "xxxx.xxxx.net.br";
const char* mqtt_user = "user"; //usu¨¢rio do mosquitto
const char* mqtt_pwd = "12345"; //senha do mqtt

AsyncMqttClient mqttClient;
Ticker mqttReconnectTimer;

WiFiEventHandler wifiConnectHandler;
WiFiEventHandler wifiDisconnectHandler;
Ticker wifiReconnectTimer;
//=========================================
void connectToWifi()
{
	Serial.println("Connecting to Wi-Fi...");
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}
//=========================================
void onWifiConnect(const WiFiEventStationModeGotIP& event)
{
	Serial.println("Connected to Wi-Fi.");
	connectToMqtt();
}
//=========================================
void onWifiDisconnect(const WiFiEventStationModeDisconnected& event)
{
	Serial.println("Disconnected from Wi-Fi.");
	mqttReconnectTimer.detach(); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
	wifiReconnectTimer.once(2, connectToWifi);
}
//=========================================
void connectToMqtt()
{
	Serial.println("Connecting to MQTT...");
	mqttClient.connect();
}
//=========================================
void onMqttConnect(bool sessionPresent) // MQTT Subscribe
{
	String clientName;
	clientName += "LS";
	if (mqttClient.subscribe(clientName.c_str(), 2))
	{
		Serial.print(">>> [Mosquitto] Subscribe LS : ");
		Serial.println(clientName);
	}

}
//=========================================
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
	Serial.println("Disconnected from MQTT.");

	if (WiFi.isConnected())
	{
		mqttReconnectTimer.once(2, connectToMqtt);
	}
}
//=========================================
/ void onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
	Serial.println("Subscribe acknowledged.");
	Serial.print(" packetId: ");
	Serial.println(packetId);
	Serial.print(" qos: ");
	Serial.println(qos);
}/

/void onMqttUnsubscribe(uint16_t packetId)
{
	Serial.println("Unsubscribe acknowledged.");
	Serial.print(" packetId: ");
	Serial.println(packetId);
} /
//=========================================
void onMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
	char message_buff[150];
	int i;
	for (i = 0; i < len; i++) {
		message_buff[i] = payload[i];
	}
	message_buff[i] = '\0';
	String msgString = String(message_buff);
	Serial.println(msgString);

}
//=========================================
/ void onMqttPublish(uint16_t packetId) {
	Serial.println("Publish acknowledged.");
	Serial.print(" packetId: ");
	Serial.println(packetId);
} /
//=========================================
void setup() {
	Serial.begin(115200);
	Serial.println();
	Serial.println();

	wifiConnectHandler = WiFi.onStationModeGotIP(onWifiConnect);
	wifiDisconnectHandler = WiFi.onStationModeDisconnected(onWifiDisconnect);
	mqttClient.onConnect(onMqttConnect);
	mqttClient.onDisconnect(onMqttDisconnect);
	mqttClient.onMessage(onMqttMessage);
	mqttClient.setServer(host, 1883);
	mqttClient.setCredentials(mqtt_user, mqtt_pwd);
	connectToWifi();

#if ASYNC_TCP_SSL_ENABLED
	mqttClient.setSecure(MQTT_SECURE);
	if (MQTT_SECURE) {
		mqttClient.addServerFingerprint((const uint8_t[])MQTT_SERVER_FINGERPRINT);
	}
#endif
}

void loop() {
}