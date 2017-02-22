#include "SpiTest.h"
#include "../RobotMap.h"

SpiTest::SpiTest() : Subsystem("ExampleSubsystem") {
	spi = new SPI(SPI::Port:: kOnboardCS0);
	lumberJack.reset(new LumberJack());
}

void SpiTest::InitDefaultCommand() {

}

void SpiTest::Run()
{
	//SPI.setClockDivider(SPI_CLOCK_DIV8); // ~754 KHz 1.420 MHz 1.516 MHz
	spi->SetClockRate(1420000);
}

int  SpiTest::TransferAndWait(uint8_t* what)
{
int a = spi->Write(what, 1);
//delayMicroseconds (20);
lumberJack->dLog(to_string(a));
return a;
} // end of transferAndWait
