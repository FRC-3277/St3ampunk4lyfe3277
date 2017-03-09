/*
 * Abandoned because Arduino ethernet shield reserves pins needed for making SPI functional.  Sad day!
 */
#ifndef SpiCommunicator_H
#define SpiCommunicator_H

#include <SPI.h>
#include "WPILib.h"
#include "LumberJack.h"
#include <Commands/Subsystem.h>

class SpiCommunicator : public Subsystem {
private:
	SPI* spi;
	std::shared_ptr<LumberJack> lumberJack;

public:
	SpiCommunicator();
	void InitDefaultCommand();
	void Run();
	int TransferAndWait(uint8_t* what);
};

#endif  // SpiCommunicator_H
