#include <string>
#include <iostream>

#include "InTheRearWithTheGearLidar.h"
#include "../RobotMap.h"

InTheRearWithTheGearLidar::InTheRearWithTheGearLidar() : Subsystem("InTheRearWithTheGearLidar") {
	lumberJack.reset(new LumberJack());
	// initialize the LidarLite
	i2c.reset(new I2C(I2C::Port::kMXP, LIDAR_ADDR));
	lumberJack->dLog("Constructor");
}

void InTheRearWithTheGearLidar::InitDefaultCommand() {
}

// Update distance variable. See the Quick Start Guide for documentation
int InTheRearWithTheGearLidar::updateDistance()
{
	int loVal = 0, hiVal = 0;
	lumberJack->dLog("updateDistance1");
	i2c->Write(LIDAR_CONFIG_REGISTER, (uint8_t)0x04); // Initiate measurement
	//this_thread::sleep_for(chrono::milliseconds(40)); // Delay for measurement to be taken
	Sleep(40);
	//i2c->Read(LIDAR_DISTANCE_REGISTER, 2, &distance); // Read in
	lumberJack->dLog("updateDistance2");
	i2c->Read(LO_DISTANCE_REGISTER, 1, (uint8_t*)&loVal);
	//this_thread::sleep_for(chrono::milliseconds(10)); // Delay to prevent over polling
	Sleep(10);
	lumberJack->dLog("updateDistance3");
	i2c->Read(HIGH_DISTANCE_REGISTER, 1, (uint8_t*)&loVal);
	//this_thread::sleep_for(chrono::milliseconds(10)); // Delay to prevent over polling
	Sleep(10);

	lumberJack->dLog("updateDistance4");
	if(loVal == -1 || hiVal == -1)
	{
		lumberJack->eLog("Lidar distance failure");
	}
	lumberJack->dLog("updateDistance5");
	distance = (hiVal << 8) + loVal;
	lumberJack->dLog("updateDistance6");

	return distance;
}

void InTheRearWithTheGearLidar::neverEndingUpdater()
{
	lumberJack->dLog("neverEndingUpdater");
	while (true)
	{
		try
		{
			distance = updateDistance();
			//this_thread::sleep_for(chrono::milliseconds(10));
			Sleep(10);
		}
		catch (exception& e)
		{
			lumberJack->eLog(e.what());
		}
	}
}

int InTheRearWithTheGearLidar::getDistance()
{
	return distance;
}
