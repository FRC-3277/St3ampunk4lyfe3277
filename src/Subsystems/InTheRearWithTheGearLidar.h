#ifndef InTheRearWithTheGearLidar_H
#define InTheRearWithTheGearLidar_H
#include <iostream>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "LumberJack.h"

using namespace std;
using  ms = chrono::milliseconds;
using get_time = chrono::steady_clock;

class InTheRearWithTheGearLidar : public Subsystem {
private:
	std::shared_ptr<I2C> i2c;

	static const int LIDAR_ADDR = 0x62;
	static const int LIDAR_CONFIG_REGISTER = 0x00;
	static const int LIDAR_DISTANCE_REGISTER = 0x8f;
	static const int HIGH_DISTANCE_REGISTER = 0x0f;
	static const int LO_DISTANCE_REGISTER = 0x10;

	chrono::steady_clock::time_point start_time = get_time::now();
	chrono::steady_clock::time_point end_time = get_time::now();
	int diff_time = chrono::duration_cast<ms>(end_time - start_time).count();

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
