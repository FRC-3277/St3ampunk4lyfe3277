#include "ArduinoMqtt.h"
#include "../RobotMap.h"

ArduinoMqtt::ArduinoMqtt() : Subsystem("ArduinoMqtt") {
	mqttSerial = new SerialPort(9600, SerialPort::kOnboard);
	lumberJack.reset(new LumberJack());
}

void ArduinoMqtt::InitDefaultCommand() {

}

void ArduinoMqtt::SubscribeAllTheData()
{
	try
	{
		mqttSerial->Read(dataFromArduino, 5);
	}
	catch(const std::exception& e)
	{
		lumberJack->dLog(e.what());
	}
}

void ArduinoMqtt::PublishAllTheData()
{
	mqttSerial->Write((const char *)dataToArduino, 5);
}

void ArduinoMqtt::SetData(char* argData)
{
	memcpy(&dataToArduino, argData, sizeof(argData));
}

char* ArduinoMqtt::GetData()
{
	return dataFromArduino;
}
