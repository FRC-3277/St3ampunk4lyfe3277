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
	try
	{
		lumberJack->dLog("updateDistance1");
		i2c->Write(LIDAR_CONFIG_REGISTER, (uint8_t)0x04); // Initiate measurement
		endTime = std::chrono::system_clock::now();
		elapsedTime = endTime - startTime;
		numberMillisecondsElapsed = chrono::duration_cast<ms>(elapsedTime).count();
		if(numberMillisecondsElapsed > 40 && lidarStep == 1)
		{
			lumberJack->dLog("updateDistance2");
			i2c->Read(LO_DISTANCE_REGISTER, 1, (uint8_t*)&loVal);
			lidarStep += 1;
		}
		else if(numberMillisecondsElapsed > 60 && lidarStep == 2)
		{
			lumberJack->dLog("updateDistance3");
			i2c->Read(HIGH_DISTANCE_REGISTER, 1, (uint8_t*)&hiVal);
			lidarStep += 1;
		}

		if(lidarStep == 3)
		{
			lumberJack->dLog("updateDistance4");
			if(loVal == -1 || hiVal == -1)
			{
				lumberJack->eLog("Lidar distance failure");
			}
			lumberJack->dLog("updateDistance5");
			distance = (hiVal << 8) + loVal;
			lumberJack->dLog("updateDistance6");
			lidarStep = 1;
			startTime = std::chrono::system_clock::now();
		}

		if(numberMillisecondsElapsed > 200)
		{
			// Reset if things go terribly wrong
			lidarStep = 1;
			startTime = std::chrono::system_clock::now();
		}
	}
	catch (exception& e)
	{
		lumberJack->eLog(e.what());
	}

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
