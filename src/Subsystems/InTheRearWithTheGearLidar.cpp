#include <string>
#include <iostream>

#include <I2C.h>
#include "InTheRearWithTheGearLidar.h"
#include "../RobotMap.h"

#include <include/lidar_lite.h>

using namespace std;

Lidar_Lite::Lidar_Lite (int bus){
  err = 0;
  adapter_num = bus;
  snprintf(filename, 19, "/dev/i2c-%d", adapter_num);
}

Lidar_Lite::~Lidar_Lite(void){
  printf("Ending Lidar-Lite Session");
  if (i2c_bus > 0){
   int e = close(i2c_bus);
  }
}

int Lidar_Lite::connect( void ) {
  printf("Connecting to %s", filename);
  i2c_bus = open(filename, O_RDWR);
  if (i2c_bus < 0){
    err = errno;
    printf("Connect Error: %d", err);
    return -1;
  }
  if (ioctl(i2c_bus, I2C_SLAVE, 0x62) < 0) {
    err = errno;
    printf("Bus Error: %d", err);
    return -1;
  }
  return 0;
}


int Lidar_Lite::writeAndWait(int writeRegister, int value){
  res = i2c_smbus_write_byte_data(i2c_bus, writeRegister, value);
  usleep(10000);
  if (res < 0){
    err = errno;
    printf("Write Error %d", err);
    return -1;
  } else {
    return 0;
  }
}

int Lidar_Lite::readAndWait(int readRegister){
  res = i2c_smbus_read_byte_data(i2c_bus, readRegister);
  usleep(10000);
  if (res < 0){
    err = errno;
    printf("Read Error: %d", err);
    return -1;
  } else {
    return 0;
  }
}

int Lidar_Lite::getDistance( void ){
  int buf[2];
  int e = 0;
  e = writeAndWait(0x00,0x04);
  if (e < 0){
    return e;
  }
  e = readAndWait(0x8f);
  if (e < 0){
    return e;
  } else {
    buf[0] = res;
  }
  e = readAndWait(0x10);
  if (e < 0){
    return e;
  } else {
    buf[1] = res;
  }
  return (buf[0] << 8) + buf[1];
}

int Lidar_Lite::getError(void){
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
