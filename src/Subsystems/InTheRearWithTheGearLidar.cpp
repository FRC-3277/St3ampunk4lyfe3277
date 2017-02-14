#include <string>
#include <iostream>

#include "InTheRearWithTheGearLidar.h"
#include "../RobotMap.h"

InTheRearWithTheGearLidar::InTheRearWithTheGearLidar() : Subsystem("InTheRearWithTheGearLidar") {
	lumberJack.reset(new LumberJack());
	// initialize the LidarLite
	i2c.reset(new I2C(I2C::Port::kOnboard, LIDAR_ADDR));
	lumberJack->dLog("Constructor");
}

void InTheRearWithTheGearLidar::InitDefaultCommand() {
}

// Update distance variable. See the Quick Start Guide for documentation
int InTheRearWithTheGearLidar::updateDistance()
{
	int loVal = 0, hiVal = 0;

	i2c->Write(LIDAR_CONFIG_REGISTER, (uint8_t)0x04); // Initiate measurement
	this_thread::sleep_for(40ms); // Delay for measurement to be taken
	//i2c->Read(LIDAR_DISTANCE_REGISTER, 2, &distance); // Read in
	i2c->Read(LO_DISTANCE_REGISTER, 1, (uint8_t*)&loVal);
	this_thread::sleep_for(10ms); // Delay to prevent over polling
	i2c->Read(HIGH_DISTANCE_REGISTER, 1, (uint8_t*)&loVal);
	this_thread::sleep_for(10ms); // Delay to prevent over polling

	if(loVal == -1 || hiVal == -1)
	{
		//TODO: Enable once merged with Encoder branch
		//lumberJack->eLog("Lidar distance failure");
	}
	distance = (hiVal << 8) + loVal;
	lumberJack->dLog("updateDistance");

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
			this_thread::sleep_for(10ms);
		}
		catch (exception& e)
		{
			//TODO: Enable this once merged with Encoder Branch
			//lumberJack->eLog((string&)e.what());
		}
	}
}

int InTheRearWithTheGearLidar::getDistance()
{
	return distance;
}
