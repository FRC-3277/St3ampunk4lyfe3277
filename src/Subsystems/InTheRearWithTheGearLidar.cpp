#include <string>
#include <iostream>

#include <I2C.h>
#include "InTheRearWithTheGearLidar.h"
#include "../RobotMap.h"

using namespace std;

InTheRearWithTheGearLidar::InTheRearWithTheGearLidar() : Subsystem("InTheRearWithTheGearLidar"){
  err = 0;
  startTime = std::chrono::system_clock::now();
}

InTheRearWithTheGearLidar::~InTheRearWithTheGearLidar(){
}

int InTheRearWithTheGearLidar::connect( void ) {
	lumberJack.reset(new LumberJack());
	i2c_bus = new I2C(I2C::Port::kOnboard, LIDAR_LITE_ADDRESS);

	return 0;
}

int InTheRearWithTheGearLidar::writeAndWait(int writeRegister, int value){
	bool status = false;
	status = i2c_bus->Write(writeRegister, value);
	return (int)status;
}

int InTheRearWithTheGearLidar::readAndWait(int readRegister){
	bool status = false;
	status = i2c_bus->Read(readRegister,  1, (uint8_t*)&res);
	return (int)status;
}

int InTheRearWithTheGearLidar::getDistance( void ){
	endTime = std::chrono::system_clock::now();
	elapsedTime = endTime - startTime;
	numberMillisecondsElapsed = chrono::duration_cast<ms>(elapsedTime).count();

	if(lidarStep == 1)
	{
	  e = writeAndWait(0x00,0x04);
	  if (e == 1){
		return e;
	  }
	  lidarStep += 1;
	  startTime = std::chrono::system_clock::now();
	  lumberJack->dLog("updateDistance1");
	}
	else if(numberMillisecondsElapsed > 10 && lidarStep == 2)
	{
	  e = readAndWait(0x8f);
	  if (e == 1){
		return e;
	  } else {
		  lumberJack->dLog("updateDistance2");
		  buf[0] = res;
	  }
	  lidarStep += 1;
	}
	else if(numberMillisecondsElapsed > 20 && lidarStep == 3)
	{
	  e = readAndWait(0x10);
	  if (e == 1){
		return e;
	  } else {
		  lumberJack->dLog("updateDistance3");
		  buf[1] = res;
	  }
	  lidarStep += 1;
	}

	if(numberMillisecondsElapsed > 100)
	{
		//reset
		startTime = std::chrono::system_clock::now();
		lidarStep = 1;
		lumberJack->dLog("Reset");
	}

	if(lidarStep == 4)
	{
		lidarStep = 1;
		startTime = std::chrono::system_clock::now();
		lumberJack->dLog("updateDistance4");
		return ((buf[0] << 8) + buf[1]);
	}
	else
	{
		return 0;
	}
}

int InTheRearWithTheGearLidar::getError(void){
  return err;
}

/*
InTheRearWithTheGearLidar::InTheRearWithTheGearLidar() : Subsystem("InTheRearWithTheGearLidar") {
	lumberJack.reset(new LumberJack());
	// initialize the LidarLite
	i2c.reset(new I2C(I2C::Port::kMXP, LIDAR_ADDR));
}

void InTheRearWithTheGearLidar::InitDefaultCommand() {
}

// Update distance variable. See the Quick Start Guide for documentation
int InTheRearWithTheGearLidar::updateDistance()
{
	try
	{
		i2c->Write(LIDAR_CONFIG_REGISTER, (uint8_t)0x04); // Initiate measurement
		endTime = std::chrono::system_clock::now();
		elapsedTime = endTime - startTime;
		numberMillisecondsElapsed = chrono::duration_cast<ms>(elapsedTime).count();
		if(numberMillisecondsElapsed > 40 && lidarStep == 1)
		{
			lumberJack->dLog("updateDistance1");
			i2c->Read(LO_DISTANCE_REGISTER, 1, (uint8_t*)&loVal);
			lidarStep += 1;
		}
		else if(numberMillisecondsElapsed > 60 && lidarStep == 2)
		{
			lumberJack->dLog("updateDistance2");
			i2c->Read(HIGH_DISTANCE_REGISTER, 1, (uint8_t*)&hiVal);
			lidarStep += 1;
		}

		if(lidarStep == 3)
		{
			lumberJack->dLog("updateDistance3");
			if(loVal == -1 || hiVal == -1)
			{
				lumberJack->eLog("Lidar distance failure");
			}
			distance = (hiVal << 8) + loVal;
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
*/
