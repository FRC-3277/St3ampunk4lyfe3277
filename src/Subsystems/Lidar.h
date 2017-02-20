#ifndef Lidar_H
#define Lidar_H

#include <I2C.h>
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "LumberJack.h"


class Lidar : public Subsystem {
public:
	Lidar();
	void AquireDistance(Timer*);
private:
	enum Address {ADDRESS_DEFAULT=0x62}; // default I2C bus address for the LIDAR Lite v2
	enum Register {COMMAND=0x00, STATUS=0x01, DISTANCE_1_2=0x8f};
	enum Command {ACQUIRE_DC_CORRECT=0x04};
	enum NumberOfRegistersToRead {READ_1_REGISTER=0x01, READ_2_REGISTERS=0x02};
	enum NumberOfRegistersToWrite {WRITE_1_REGISTER=0x01};
	I2C* I2CBus;
	bool Busy();
};

#endif  // Lidar_H
