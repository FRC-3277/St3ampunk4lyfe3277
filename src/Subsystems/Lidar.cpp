#include "Lidar.h"
#include "../RobotMap.h"
//Command Register
//Write 0x04 to Register 0x00: Take acquisition & correlation processing with DC correction

//0x01 - Mode/Status (control_reg[1]:)
//
//Bit	Function	Notes
//Bit 7	Eye Safe	This bit will go high if eye-safety protection has been activated
//Bit 6	Error Detection	Process error detected / measurement invalid
//Bit 5	Health	“1” if good, “0” if bad
//Bit 4	Secondary return	Secondary return detected above correlation noise floor threshold
//Bit 3	Signal not valid	Indicates that the signal correlation peak is equal to or below correlation record noise threshold
//Bit 2	Sig overflow flag	Overflow detected in correlation process associated with a signal acquisition
//Bit 1	Ref overflow flag	Overflow detected in correlation process associated with a reference acquisition
//Bit 0	Ready Status	“0” is ready for new command, “1” is busy with acquisition
//Health status indicates that the preamp is operating properly, transmit power is active and a reference pulse has been processed and has been stored.
Lidar::Lidar() : Subsystem("Lidar")
{
	I2CBus = new I2C(I2C::kMXP , Lidar::ADDRESS_DEFAULT);
	Wait(1.);
}

void Lidar::AquireDistance(Timer* m_timer)
{
	unsigned char distance[Lidar::READ_2_REGISTERS];
	unsigned char distanceRegister_1st[Lidar::WRITE_1_REGISTER];
	distanceRegister_1st[Lidar::WRITE_1_REGISTER-1] = Lidar::DISTANCE_1_2;

	printf("Time =  %f starting Lidar::AquireDistance\n", m_timer->Get());

	//do{Wait(.0001);} while (Busy());
	Wait(.0001);

	printf("Time =  %f acquiring distance\n", m_timer->Get());

	/***********acquire distance**********/		//	WriteBulk() also works
	if ( I2CBus->Write(Lidar::COMMAND, Lidar::ACQUIRE_DC_CORRECT) )printf ( "Write operation failed! line %d\n", __LINE__ ); // initiate distance acquisition with DC stabilization

	//do{Wait(.0001);} while (Busy());
	Wait(.0001);

	printf("Time =  %f reading distance\n", m_timer->Get());

	/**********read distance**********/     // Read() does not work
	if ( I2CBus->WriteBulk(distanceRegister_1st, Lidar::WRITE_1_REGISTER)) printf ( "WriteBulk distance failed! line %d\n", __LINE__ );
	else
	if ( I2CBus->ReadOnly(Lidar::READ_2_REGISTERS, distance)) printf ( "ReadOnly distance failed! line %d\n", __LINE__ );

	unsigned int dist = (unsigned int)(distance[0]<<8) + (unsigned int)(distance[1]);

	printf("Time =  %f, Distance= %d (0x%0x)\n", m_timer->Get(), dist, dist);
}

bool Lidar::Busy()
{
	unsigned char Status[Lidar::READ_1_REGISTER];
	unsigned char statusRegister[Lidar::WRITE_1_REGISTER];
	statusRegister[Lidar::WRITE_1_REGISTER-1] = Lidar::STATUS;

	/**********read status**********/
	if ( I2CBus->WriteBulk(statusRegister, Lidar::WRITE_1_REGISTER)) {printf ( "WriteBulk status failed! line %d\n", __LINE__ ); return true;}
	if ( I2CBus->ReadOnly(Lidar::READ_1_REGISTER, Status) ) {printf ( "ReadOnly status failed! line %d\n", __LINE__ ); return true;}
	//printf("Status at line %d %0x, bit0=%0x\n", __LINE__, Status[0], Status[0] & (unsigned char)0x01);
	return (Status[0] & (unsigned char)0x01); // bit 0 is LIDAR Lite v2 busy bit
};
