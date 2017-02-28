#include <Subsystems/SpiCommunicator.h>
#include "../RobotMap.h"

SpiCommunicator::SpiCommunicator() : Subsystem("ExampleSubsystem") {
	spi = new SPI(SPI::Port::kOnboardCS0);
	lumberJack.reset(new LumberJack());
	spi->SetChipSelectActiveHigh();
}

void SpiCommunicator::InitDefaultCommand() {

}

void SpiCommunicator::Run()
{
	//SPI.setClockDivider(SPI_CLOCK_DIV8); // ~754 KHz 1.420 MHz 1.516 MHz
	spi->SetClockRate(1420000);
}

int  SpiCommunicator::TransferAndWait(uint8_t* what)
{
	spi->SetChipSelectActiveLow();
	int a = spi->Write(what, 5);
	spi->SetChipSelectActiveHigh();
	//delayMicroseconds (20);
	lumberJack->dLog(to_string(a));
	return a;
} // end of transferAndWait
