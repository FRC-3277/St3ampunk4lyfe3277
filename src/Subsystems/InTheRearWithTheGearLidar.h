#ifndef InTheRearWithTheGearLidar_H
#define InTheRearWithTheGearLidar_H
#include <iostream>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
// Chrono lib thread sleep made crashy bot for unknown reasons.  This is a cross platform alternative.
#ifdef __linux__
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#else
#include <windows.h>
#endif

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "LumberJack.h"

using namespace std;
using  ms = chrono::milliseconds;

//#include <linux/i2c-dev.h>
//#include <sys/ioctl.h>
#include <cstdlib>
#include <cstdio>
//#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define LIDAR_LITE_ADDRESS = 0x62
#define LIDAR_LITE_DIST_WRITE_REG = 0x00
#define LIDAR_LITE_DIST_WRITE_VAL = 0x04
#define LIDAR_LITE_DIST_READ_REG = 0x8f
#define LIDAR_LITE_DIST_READ_REG_2 = 0x98

class InTheRearWithTheGearLidar{
private:
	I2C* i2c_bus;
    int adapter_num;
    char filename[20];
    int res;
    std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	std::chrono::duration<float> elapsedTime;
	int numberMillisecondsElapsed = 0;
	int lidarStep = 1;
	int buf[2];
	int e = 0;

public:
    int err;
    InTheRearWithTheGearLidar();
    ~InTheRearWithTheGearLidar();
    int connect(void);
    int writeAndWait(int, int);
    int readAndWait(int);
    int getDistance(void);
    int getError(void);
};

#endif
/*
class InTheRearWithTheGearLidar : public Subsystem {
private:
	std::shared_ptr<I2C> i2c;

	static const int LIDAR_ADDR = 0x62;
	static const int LIDAR_CONFIG_REGISTER = 0x00;
	static const int LIDAR_DISTANCE_REGISTER = 0x8f;
	static const int HIGH_DISTANCE_REGISTER = 0x0f;
	static const int LO_DISTANCE_REGISTER = 0x10;

	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;
	std::chrono::duration<float> elapsedTime;
	int numberMillisecondsElapsed = 0;
	int loVal = 0, hiVal = 0;
	int lidarStep = 1;
	int distance = 0;

	std::shared_ptr<LumberJack> lumberJack;

public:
	InTheRearWithTheGearLidar();
	void InitDefaultCommand();
	int updateDistance();
	void neverEndingUpdater();
	int getDistance();
};

#endif  // InTheRearWithTheGearLidar_H
*/
