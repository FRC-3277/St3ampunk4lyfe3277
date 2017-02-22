#ifndef ArduinoMqtt_H
#define ArduinoMqtt_H
#include <iostream>
#include <cstring>

#include <SerialPort.h>
#include "WPILib.h"
#include "./LumberJack.h"

#include <Commands/Subsystem.h>

class ArduinoMqtt : public Subsystem {
private:
	SerialPort* mqttSerial;
	std::shared_ptr<LumberJack> lumberJack;
	char*  dataFromArduino, dataToArduino;

public:
	ArduinoMqtt();
	void InitDefaultCommand();
	void SubscribeAllTheData();
	void PublishAllTheData();
	void SetData(char* argData);
	char* GetData();
};

#endif  // ArduinoMqtt_H
