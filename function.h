void slaverDataDelivery()
{
	MachinePara.machineType = RS485A.UN2.slaveBuf.type;
	MachinePara.paraTemp = RS485A.UN2.slaveBuf.temp;
	MachinePara.setTemp = RS485A.UN2.slaveBuf.speed;
	MachinePara.paraSpeed = RS485A.UN2.slaveBuf.setSpeed;
	MachinePara.setSpeed = RS485A.UN2.slaveBuf.setSpeed;
	MachinePara.setTimeHour = RS485A.UN2.slaveBuf.setTimeHour;
	MachinePara.setTimeMinute = RS485A.UN2.slaveBuf.setTimeMinute;
	MachinePara.paraTimeHour = RS485A.UN2.slaveBuf.timeHour;
	MachinePara.paraTimeMinute = RS485A.UN2.slaveBuf.timeMinute;
	MachinePara.TempRangeMin = RS485A.UN2.slaveBuf.tempRangeMin;
	MachinePara.TempRangeMax = RS485A.UN2.slaveBuf.tempRangeMax;
	MachinePara.paraSpeedMax = RS485A.UN2.slaveBuf.speedMax;
	MachinePara.paraSpeedMin = RS485A.UN2.slaveBuf.speedMin;
	/*�澯����*/
	MachinePara.innerSensorAlarm = (RS485A.UN2.slaveBuf.alarm >> 15) % 2;
	MachinePara.innerSensorTempAlarm = (RS485A.UN2.slaveBuf.alarm >> 14) % 2;
	MachinePara.externalSensorAlarm = (RS485A.UN2.slaveBuf.alarm >> 13) % 2;
	MachinePara.externalSensorOverheat = (RS485A.UN2.slaveBuf.alarm >> 12) % 2;
	MachinePara.machineTempOverheat = (RS485A.UN2.slaveBuf.alarm >> 11) % 2;
	MachinePara.machineTempSensorAlarm = (RS485A.UN2.slaveBuf.alarm >> 10) % 2;
	MachinePara.motorStalling = (RS485A.UN2.slaveBuf.alarm >> 9) % 2;
	MachinePara.externalSensorDrop = (RS485A.UN2.slaveBuf.alarm >> 8) % 2;
	MachinePara.timingOver = (RS485A.UN2.slaveBuf.alarm >> 7) % 2;
	MachinePara.externalSensorUnplugged = (RS485A.UN2.slaveBuf.alarm >> 6) % 2;
	/**********/
	MachinePara.paraRunStop = RS485A.UN2.slaveBuf.runStop;
	MachinePara.paraCurrentMode = RS485A.UN2.slaveBuf.currentMode;
	MachinePara.paraPwrOffMem = RS485A.UN2.slaveBuf.powerOffMem;
}
//��mqtt������Ϣ
void MQTTPub(char* topic, char* payload, uint8_t qos)
{
	if (mqttclient.connected())
	{
		mqttclient.publish(topic, qos, false, payload);
	}
}
//������ֵ����16���Ƶ�10���Ƶ�ת��
void hex2dec()
{
	//�������Ƿ�ʹ��δ֪
}
//��19���豸�в����豸����
void findMachineType(u16 machine_type)
{
	//����
}

//����õĲ���MachinePara���и���ת�����洢����������
char* packageData()
{
	char* str;
	if (MachinePara.machineType == 100) //���ڼ����ж��豸���͵ķ���
	{
		jsonBuffer["mt"] = "CCLH_BASIC";
		jsonBuffer["temp"] = (float)MachinePara.paraTemp / 10;
		jsonBuffer["setTemp"] = (float)MachinePara.setTemp / 10;
		jsonBuffer["speed"] = MachinePara.paraSpeed;
		jsonBuffer["setSpeed"] = MachinePara.setSpeed;
		jsonBuffer["setHour"] = MachinePara.setTimeHour;
		jsonBuffer["setMinute"] = MachinePara.setTimeMinute;
		jsonBuffer["hour"] = MachinePara.paraTimeHour;
		jsonBuffer["minute"] = MachinePara.paraTimeMinute;
		jsonBuffer["tempMin"] = MachinePara.TempRangeMin;
		jsonBuffer["tempMax"] = MachinePara.TempRangeMax;
		jsonBuffer["speedMin"] = MachinePara.paraSpeedMin;
		jsonBuffer["speedMax"] = MachinePara.paraSpeedMax;
		jsonBuffer["runStop"] = MachinePara.paraRunStop;
		jsonBuffer["mode"] = MachinePara.paraCurrentMode;
		jsonBuffer["pwrOffMem"] = MachinePara.paraPwrOffMem;
	}
	//char myJson[] = "{\"myChar\":\"hello\",\"myArray\":[13,14],\"myObject\":{\"myFloat\":3.1415926}}";
	serializeJson(jsonBuffer, str);
	return str;
}
char* getTopic()
{
	sprintf_P(topic, "%s/%s/appub", modelname, MACHINE_TYPE.CCLH_BASIC.name);
	return topic;
}
void slaverSendMessageToMQTT()
{
	topic = getTopic();
	payload = packageData();
	MQTTPub(topic, payload, 0);
}