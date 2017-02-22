#ifndef SpiTest_H
#define SpiTest_H

#include <SPI.h>
#include "WPILib.h"
#include "LumberJack.h"
#include <Commands/Subsystem.h>

class SpiTest : public Subsystem {
private:
	SPI* spi;
	std::shared_ptr<LumberJack> lumberJack;

public:
	SpiTest();
	void InitDefaultCommand();
	void Run();
	int TransferAndWait(uint8_t* what);
};

#endif  // SpiTest_H
