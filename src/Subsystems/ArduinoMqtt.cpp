#include "ArduinoMqtt.h"
#include "../RobotMap.h"

ArduinoMqtt::ArduinoMqtt() : Subsystem("ArduinoMqtt") {
	mqttSerial.reset(new SerialPort(57600, SerialPort::kUSB1));
	lumberJack.reset(new LumberJack());

}

void ArduinoMqtt::InitDefaultCommand() {

}

void ArduinoMqtt::SubscribeAllTheData()
{
	mqttSerial->Read(dataFromArduino, 100);
}

void ArduinoMqtt::PublishAllTheData()
{
	mqttSerial->Write((const char *)dataToArduino, 100);
}

void ArduinoMqtt::SetData(char* argData)
{
	memcpy(&dataToArduino, argData, sizeof(argData));
}

char* ArduinoMqtt::GetData()
{
	return dataFromArduino;
}
